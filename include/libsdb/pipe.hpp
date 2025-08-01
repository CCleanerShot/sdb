#ifndef SDB_PIPE_HPP
#define SDB_PIPE_HPP

#include <cstddef>
#include <vector>

namespace sdb {
    class pipe {
    public:
        ~pipe();
        void close_read();
        void close_write();
        int get_read() const { return fds_[read_fd]; }
        int get_write() const { return fds_[write_fd]; }
        explicit pipe(bool close_on_exec);
        std::vector<std::byte> read();
        int release_read();
        int release_write();
        void write(std::byte* from, std::size_t bytes);
    private:
        static constexpr unsigned read_fd = 0;
        static constexpr unsigned write_fd = 1;
        int fds_[2];
    };
}

#endif
