//
// Created by Nekbakht Zabirov on 23.09.2025.
//

#pragma once

#include <string_view>
#include <initializer_list>
#include "nekpostgresql/column/icolumn.hpp"

namespace nekpostgresql::table
{
    template <size_t N>
    struct fixed_string
    {
        char data[N]; // массив символов фиксированной длины

        // Конструктор, который принимает строковый литерал
        explicit constexpr fixed_string(const char (&s)[N])
        {
            for (size_t i = 0; i < N; i++)
            {
                data[i] = s[i]; // посимвольно копируем "users\0"
            }
        }

        // Удобное преобразование в std::string_view
        explicit constexpr operator std::string_view() const
        {
            return {data, N - 1}; // N-1 — отбрасываем '\0'
        }
    };

    // deduction guide: позволяет писать fixed_string("users")
    template <size_t N>
    fixed_string(const char (&)[N]) -> fixed_string<N>;

    template <typename T, fixed_string NAME>
    class ITable
    {
    public:
        static constexpr auto TABLE_NAME = NAME;
    };
}
