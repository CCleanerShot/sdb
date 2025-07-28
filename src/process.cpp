#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <editline/readline.h>
#include <libsdb/error.hpp>
#include <libsdb/libsdb.hpp>
#include <libsdb/process.hpp>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#pragma region STATIC_METHODS
std::unique_ptr<sdb::process> sdb::process::attach(pid_t pid) {
    if(pid == 0) {
        error::send("Invalid pid");
    }

    long ptrace_result = ptrace(PTRACE_ATTACH, pid, /*addr=*/nullptr, /*data=*/nullptr);

    if(ptrace_result < 0) {
        error::send_errno("Could not attach");
    }

    std::unique_ptr<process> proc (new process(pid, false));
    proc->wait_on_signal();
    return proc;
}

std::unique_ptr<sdb::process> sdb::process::launch(std::filesystem::path path) {
    pid_t pid = fork();

    if(pid < 0) {
        error::send_errno("Forking failed");
    }

    if(pid == 0) {
        long ptrace_result = ptrace(PTRACE_TRACEME, pid, /*addr=*/nullptr, /*data=*/nullptr);

        if(ptrace_result < 0) {
            error::send_errno("Tracing failed");
        }

        int execlp_result = execlp(path.c_str(), path.c_str(), nullptr);

        if(execlp_result < 0) {
            error::send_errno("Exec failed");
        }

    }
    
    std::unique_ptr<process> proc (new process(pid, true));
    proc->wait_on_signal();
    
    return proc;
}
#pragma endregion

#pragma region CLASS_METHODS
sdb::process::~process() {
    if(pid_ != 0) {
        int status;

        if(state_ == process_state::running) {
            kill(pid_, SIGSTOP);
            waitpid(pid_, &status, 0);
        }

        ptrace(PTRACE_DETACH, pid_, nullptr, nullptr);
        kill(pid_, SIGCONT);

        if(terminate_on_end_) {
            kill(pid_, SIGKILL);
            waitpid(pid_, &status, 0);
        }
    }
}

void sdb::process::resume() {
    long ptrace_result = ptrace(PTRACE_CONT, pid_, nullptr, nullptr);

    if(ptrace_result < 0) {
        error::send_errno("Could not resume");
    }

    state_ = process_state::running;
}

sdb::stop_reason::stop_reason(int wait_status) {
    if(WIFEXITED(wait_status)) {
        reason = process_state::exited;
        info = WEXITSTATUS(wait_status);
    } 
    
    else if(WIFSIGNALED(wait_status)) {
        reason = process_state::terminated;
        info = WTERMSIG(wait_status);
    }

    else if(WIFSTOPPED(wait_status)) {
        reason = process_state::exited;
        info = WSTOPSIG(wait_status);
    }
}

sdb::stop_reason sdb::process::wait_on_signal() {
    int wait_status;
    int options = 0;
    pid_t waitpid_result = waitpid(pid_, &wait_status, options);

    if(waitpid_result < 0) {
        error::send_errno("Waiting failed");
    }

    stop_reason reason(wait_status);
    state_ = reason.reason;
    return reason;
}
#pragma endregion
