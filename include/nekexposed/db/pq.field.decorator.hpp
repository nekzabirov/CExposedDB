//
// Created by Nekbakht Zabirov on 29.09.2025.
//

#pragma once

#include <pqxx/pqxx>
#include <optional>
#include "nekexposed/value/value.hpp"
#include "nekexposed/value/timestamp.value.hpp"
#include "nekexposed/value/array.value.hpp"

namespace nekexposed::db
{
    /*template <typename T>
    class PQFieldDecorator
    {
    public:
        // Accept field from const rows too
        explicit PQFieldDecorator(pqxx::field& field) : field_(field)
        {
        }

        [[nodiscard]] std::optional<T> as() const
        {
            if (field_.is_null()) return std::nullopt;

            return field_.as<T>();
        }

    private:
        pqxx::field& field_;
    };*/

    /*template<>
    inline std::optional<value::Timestamp> PQFieldDecorator<value::Timestamp>::as() const
    {
        const auto str = field_.as<std::string>();
        return value::parse(str);
    }*/

    template <typename T>
    class PQParser
    {
    public:
        virtual ~PQParser() = default;

        std::optional<T> parse(const pqxx::row& row) const
        {
            const pqxx::field field = row.at(getKey());

            if (field.is_null()) return std::nullopt;

            return value::parse<T>(field);
        }

        void parse(const pqxx::row& row, T& result) const
        {
            if (const auto res = parse(row); res.has_value())
            {
                result = res.value();
            }
        }

    private:
        [[nodiscard]] std::string virtual getKey() const = 0;
    };
}