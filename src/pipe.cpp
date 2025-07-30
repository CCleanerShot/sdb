#include <utility>
#include <fcntl.h>
#include <libsdb/pipe.hpp>
#include <libsdb/error.hpp>
#include <unistd.h>

#pragma region STATIC_METHODS
sdb::pipe::~pipe() {
    close_read();
    close_write();
}

void sdb::pipe::close_read() {
    if(fds_[read_fd] != -1) {
        close(fds_[read_fd]);
        fds_[read_fd] = -1;
    }
}

void sdb::pipe::close_write() {
    if(fds_[write_fd] != -1) {
        close(fds_[write_fd]);
        fds_[write_fd] = -1;
    }
}

sdb::pipe::pipe(bool close_on_exec) {
    int pipe2_result = pipe2(fds_, close_on_exec ? O_CLOEXEC : 0);

    if(pipe2_result < 0) {
        error::send_errno("Pipe creation failed");
    }
}

std::vector<std::byte> sdb::pipe::read() {
    char buf[1024];
    int chars_read = ::read(fds_[read_fd], buf, sizeof(buf));
   
    if(chars_read < 0) {
        error::send_errno("Could not read from pipe");
    }
    
    auto bytes = reinterpret_cast<std::byte*>(buf);
    return std::vector<std::byte>(bytes, bytes + chars_read);
}

int sdb::pipe::release_read() {
    return std::exchange(fds_[read_fd], -1);
}

int sdb::pipe::release_write() {
    return std::exchange(fds_[write_fd], -1);
}

void sdb::pipe::write(std::byte* from, std::size_t bytes) {
    int write_result = ::write(fds_[write_fd], from, bytes);

    if(write_result < 0) {
        error::send_errno("Could not write to pipe");
    }
}
#pragma endregion
