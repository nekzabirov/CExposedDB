#pragma once

#include <concepts>
#include <string>
#include <type_traits>
#include <ranges>

namespace nekpostgresql::sql::concepts {

// Концепт для типов, которые можно сериализовать в SQL
template<typename T>
concept SqlSerializable = requires(T t) {
    { std::to_string(t) } -> std::convertible_to<std::string>;
} || std::is_same_v<T, std::string> || std::is_same_v<T, const char*> || std::is_same_v<T, std::string_view>;

// Концепт для SQL выражений
template<typename T>
concept SqlExpression = requires(T t) {
    { t.to_sql() } -> std::convertible_to<std::string>;
};

// Концепт для контейнеров
template<typename T>
concept Container = std::ranges::range<T>;

// Концепт для nullable типов
template<typename T>
concept Nullable = requires(T t) {
    typename T::value_type;
    { t.has_value() } -> std::convertible_to<bool>;
    { t.value() };
};

} // namespace nekpostgresql::sql::concepts
