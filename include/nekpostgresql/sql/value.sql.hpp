//
// Created by Nekbakht Zabirov on 24.09.2025.
//

#pragma once

#include <string>

namespace nekpostgresql::sql::value
{
    template<typename T>
    std::string format(const T& value)
    {
        return std::to_string(value);
    }

    template<>
    inline std::string format<std::string>(const std::string& value)
    {
        return "'" + value + "'";
    }

    template<>
    inline std::string format<bool>(const bool& value)
    {
        return (value ? "true" : "false");
    }
}

