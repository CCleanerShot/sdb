#ifndef SDB_BIT_HPP
#define SDB_BIT_HPP

#include <string>

namespace sdb {
    template<class T> std::byte* as_bytes(T& from) {
        return reinterpret_cast<std::byte*>(&from);
    }

    template<class T> const std::byte* as_bytes(const T& from) {
        return reinterpret_cast<const std::byte*>(&from);
    }

    template<class T> T from_bytes(const std::byte* bytes) {
        T ret;
        std::memcpy(&ret, bytes, sizeof(T));
        return ret;
    }
}

#endif
