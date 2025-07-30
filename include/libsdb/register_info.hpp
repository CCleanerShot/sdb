#ifndef SDB_REGISTER_INFO_HPP
#define SDB_REGISTER_INFO_HPP

#include <cstddef>
#include <cstdint>
#include <string_view>
#include <sys/user.h>

namespace sdb {
    enum class register_format {
        unit,
        double_float,
        long_double,
        vector
    };

    enum class register_id {

    };

    enum class register_type {
        gpr,
        sub_gpr,
        fpr,
        dr
    };

    struct register_info {
        register_id id;
        std::string_view name;
        std::int32_t dwarf_id;
        std::size_t size;
        std::size_t offset;
        register_type type;
        register_format format;
    };

    inline constexpr const register_info g_register_infos[] = {

    };
}

#endif

