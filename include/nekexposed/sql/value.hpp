#pragma once

#include "base.hpp"
#include "concepts.hpp"
#include <string>
#include <optional>
#include <chrono>
#include <vector>
#include <array>
#include <iomanip>
#include <sstream>

namespace nekpostgresql::sql {

// Класс для форматирования значений в SQL
class Value {
public:
    // Числовые типы
    template<std::integral T>
    [[nodiscard]] static std::string format(T value) {
        if constexpr (std::is_same_v<T, bool>) {
            return value ? "TRUE" : "FALSE";
        } else {
            return std::to_string(value);
        }
    }
    
    template<std::floating_point T>
    [[nodiscard]] static std::string format(T value) {
        return std::to_string(value);
    }
    
    // Строковые типы с экранированием
    [[nodiscard]] static std::string format(const std::string& value) {
        return escape_string(value);
    }
    
    [[nodiscard]] static std::string format(std::string_view value) {
        return escape_string(std::string(value));
    }
    
    [[nodiscard]] static std::string format(const char* value) {
        return escape_string(std::string(value));
    }
    
    // Optional типы
    template<typename T>
    [[nodiscard]] static std::string format(const std::optional<T>& value) {
        if (value.has_value()) {
            return format(value.value());
        }
        return "NULL";
    }
    
    // Время
    [[nodiscard]] static std::string format(const std::chrono::system_clock::time_point& tp) {
        auto time_t = std::chrono::system_clock::to_time_t(tp);
        std::tm tm = *std::localtime(&time_t);
        
        std::ostringstream oss;
        oss << "TIMESTAMP '"
            << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
            << "'";
        return oss.str();
    }
    
    // Массивы PostgreSQL
    template<typename T, std::size_t N>
    [[nodiscard]] static std::string format(const std::array<T, N>& arr) {
        std::string result = "ARRAY[";
        for (std::size_t i = 0; i < N; ++i) {
            if (i > 0) result += ", ";
            result += format(arr[i]);
        }
        result += "]";
        return result;
    }
    
    template<typename T>
    [[nodiscard]] static std::string format(const std::vector<T>& vec) {
        std::string result = "ARRAY[";
        for (std::size_t i = 0; i < vec.size(); ++i) {
            if (i > 0) result += ", ";
            result += format(vec[i]);
        }
        result += "]";
        return result;
    }
    
private:
    // Экранирование строки для PostgreSQL
    [[nodiscard]] static std::string escape_string(const std::string& str) {
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
};

// Специальные значения
struct Null {};
struct Default {};
struct CurrentTimestamp {};
struct CurrentDate {};

inline constexpr Null null_value{};
inline constexpr Default default_value{};
inline constexpr CurrentTimestamp current_timestamp{};
inline constexpr CurrentDate current_date{};
} // namespace nekpostgresql::sql
