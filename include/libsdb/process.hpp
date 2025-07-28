#ifndef SDB_PROCESS_HPP
#define SDB_PROCESS_HPP

#include <cstdint>
#include <filesystem>
#include <memory>
#include <sys/types.h>

namespace sdb {
    enum class process_state {
        stopped,
        running,
        exited,
        terminated
    };
    
    struct stop_reason {
        stop_reason(int wait_status);

        process_state reason;
        std::uint8_t info;
    };


    class process {
        public:
            static std::unique_ptr<process> attach(pid_t pid);
            static std::unique_ptr<process> launch(std::filesystem::path path);

            ~process();
            pid_t pid() const { return pid_; }
            void resume();
            process_state state() const { return state_; }
            stop_reason wait_on_signal();

        private:
            process(pid_t pid, bool terminate_on_end) : pid_(pid), terminate_on_end_(terminate_on_end_) {}
            pid_t pid_ = 0;
            process_state state_ = process_state::stopped;
            bool terminate_on_end_ = true;

        process() = delete;
        process(const process&) = delete;
        process& operator=(const process&) = delete;
    };
}

#endif
