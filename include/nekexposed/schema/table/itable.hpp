//
// Created by Nekbakht Zabirov on 23.09.2025.
//
#pragma once

#include <string>
#include <string_view>
#include <array>
#include "nekexposed/sql/table.hpp"
#include "nekexposed/schema/column/icolumn.hpp"

namespace nekpostgresql::table
{
    template <size_t N>
    struct fixed_string
    {
        static_assert(N > 0, "fixed_string size must be > 0");
        char data[N]{};

        explicit constexpr fixed_string(const char (&s)[N]) noexcept
        {
            for (size_t i = 0; i < N; i++)
            {
                data[i] = s[i];
            }
        }

        [[nodiscard]] constexpr std::string_view view() const noexcept
        {
            return {data, N - 1}; // exclude trailing '\0'
        }
    };

    template <size_t N>
    fixed_string(const char (&)[N]) -> fixed_string<N>;

    template <typename T, size_t NCols, fixed_string NAME>
    class ITable : public sql::Table
    {
    public:
        static constexpr auto TABLE_NAME = NAME.data;
        static constexpr auto COLUMN_SIZE = NCols;

        inline static std::array<const column::IColumnBase<T>*, NCols> COLUMNS{}; // zero-initialized

        const std::string& name() const override
        {
            return TABLE_NAME;
        }

    private:
        friend class column::IColumnBase<T>;

        inline static size_t COLUMN_COUNT = 0;

        // Append a single column; ignores extra registrations beyond NCols
        static void registerColumn(const column::IColumnBase<T>* column) noexcept
        {
            if (COLUMN_COUNT < NCols)
            {
                COLUMNS[COLUMN_COUNT++] = column;
            }
        }

        // Append from a range (initializer_list, array, vector, etc.)
        template <typename Range>
        static void registerColumns(const Range& cols) noexcept
        {
            for (auto* c : cols)
            {
                if (COLUMN_COUNT >= NCols) break;
                COLUMNS[COLUMN_COUNT++] = c;
            }
        }

        // Optional: reset for testing or re-init
        static void resetColumns() noexcept
        {
            COLUMNS.fill(nullptr);
            COLUMN_COUNT = 0;
        }
    };
}
