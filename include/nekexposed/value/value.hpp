//
// Created by Nekbakht Zabirov on 30.09.2025.
//

#pragma once

#include <string>
#include <vector>
#include <pqxx/pqxx>

namespace nekexposed::value
{
    // Специальные значения
    struct Null {};
    struct Default {};
    struct CurrentTimestamp {};
    struct CurrentDate {};

    inline constexpr Null null_value{};
    inline constexpr Default default_value{};
    inline constexpr CurrentTimestamp current_timestamp{};
    inline constexpr CurrentDate current_date{};

    // Экранирование строки для PostgreSQL
    [[nodiscard]] inline std::string escape_string(const std::string& str) {
        std::string result;
        result.reserve(str.size() + 2);
        result.push_back('\'');

        for (char c : str) {
            if (c == '\'') {
                result.push_back('\'');
                result.push_back('\'');
            } else if (c == '\\') {
                result.push_back('\\');
                result.push_back('\\');
            } else {
                result.push_back(c);
            }
        }

        result.push_back('\'');
        return result;
    }

    template<typename T>
    [[nodiscard]] std::string format(const T& value)
    {
        return std::to_string(value);
    }

    // Строковые типы с экранированием
    [[nodiscard]] inline std::string format(const std::string& value) {
        return escape_string(value);
    }

    [[nodiscard]] inline std::string format(const std::string_view value) {
        return escape_string(std::string(value));
    }

    [[nodiscard]] inline std::string format(const char* value) {
        return escape_string(std::string(value));
    }

    // Массивы PostgreSQL
    template<typename T, std::size_t N>
    [[nodiscard]] std::string format(const std::array<T, N>& arr) {
        std::string result = "ARRAY[";
        for (std::size_t i = 0; i < N; ++i) {
            if (i > 0) result += ", ";
            result += format(arr[i]);
        }
        result += "]";
        return result;
    }

    template<typename T>
    [[nodiscard]] std::string format(const std::vector<T>& vec) {
        if (vec.empty())
        {
            return "ARRAY[]::text[]";
        }
        std::string result = "ARRAY[";
        for (std::size_t i = 0; i < vec.size(); ++i) {
            if (i > 0) result += ", ";
            result += format(vec[i]);
        }
        result += "]";
        return result;
    }

    template <>
    [[nodiscard]] inline std::string format(const bool& value)
    {
        return value ? "true" : "false";
    }

    template<typename T>
    [[nodiscard]] T parse(const pqxx::field& field)
    {
        return field.as<T>();
    }
}