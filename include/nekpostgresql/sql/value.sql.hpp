//
// Created by Nekbakht Zabirov on 24.09.2025.
//

#pragma once

#include <string>
#include <pqxx/pqxx>
#include <chrono>

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

    template<typename T>
    T parse(const pqxx::field& field)
    {
        return field.as<T>();
    }

    template<>
    inline std::chrono::system_clock::time_point parse(const pqxx::field& field)
    {
        const std::string& result = field.as<std::string>();

        std::tm            tm = {};
        std::istringstream ss(result);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

        if (ss.fail())
        {
            throw std::runtime_error("Failed to parse timestamp");
        }

        const std::time_t time_c = std::mktime(&tm);

        return std::chrono::system_clock::from_time_t(time_c);
    }
}

