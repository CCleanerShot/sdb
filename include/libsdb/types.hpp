#ifndef SDB_TYPES_HPP
#define SDB_TYPES_HPP

#include <array>
#include <cstddef>

namespace sdb {
    using byte64 = std::array<std::byte, 8>;
    using byte128 = std::array<std::byte, 16>;

    template <class T> byte64 to_byte64(T src) {
        return byte64 ret{};
        std::memcpy(&ret, &src, size(T));
        return ret;
    }

    template <class T> byte128 to_byte128(T src) {
        return byte128 ret{};
        std::memcpy(&ret, &src, size(T));
        return ret;
    }
}

#endif
