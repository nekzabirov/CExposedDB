// timestamp.value.hpp
#pragma once
#include <string>

namespace nekexposed::value
{

    template <>
    [[nodiscard]] inline std::string format(const bool& value)
    {
        return value ? "true" : "false";
    }
}
