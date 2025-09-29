//
// Created by Nekbakht Zabirov on 29.09.2025.
//

#pragma once

#include <pqxx/pqxx>
#include <optional>
#include "nekexposed/value/timestamp.value.hpp"

namespace nekexposed::db
{
    template <typename T>
    class PQFieldDecorator
    {
    public:
        explicit PQFieldDecorator(pqxx::field field) : field_(std::move(field)) {}

        std::optional<T> as(const std::string& key) const
        {
            if (field_.is_null()) return std::nullopt;

            return field_.as<T>(key);
        }

        std::optional<T> operator[](const std::string& key) const
        {
            return as(key);
        }

    private:
        pqxx::field field_;
    };

    template<>
    inline std::optional<value::Timestamp> PQFieldDecorator<value::Timestamp>::as(const std::string&) const
    {
        const auto str = field_.as<std::string>();
        return value::parse(str);
    }

    template <typename T>
    class PQParser
    {
    public:
        virtual ~PQParser() = default;

        std::optional<T> parse(const pqxx::row& row) const
        {
            const auto field = row.at(getKey());

            return PQFieldDecorator<T>(field).as(getKey());
        }

    private:
        [[nodiscard]] std::string virtual getKey() const = 0;
    };
}