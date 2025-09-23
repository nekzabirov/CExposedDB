//
// Created by Nekbakht Zabirov on 23.09.2025.
//

#pragma once

#include <pqxx/pqxx>
#include <string>
#include "nekpostgresql/sql/column.sql.hpp"

namespace nekpostgresql::column
{
    template <class TABLE, typename V>
    class IColumn
    {
    public:
        using value_type = V;
        using table = TABLE;
        constexpr static auto TABLE_NAME = TABLE::TABLE_NAME;

        explicit IColumn(const std::string& key) : key_(key)
        {
        }

        virtual ~IColumn() = default;

        constexpr std::string key() const
        {
            return key_;
        }

        constexpr std::string fullKey() const
        {
            return std::string(TABLE_NAME.data) + "." + key_;
        }

        constexpr sql::ColumnSql sql() const
        {
            return sql::ColumnSql(fullKey());
        }

        static V parse(const pqxx::field& field)
        {
            return field.as<V>();
        }

        V parse(const pqxx::row& row) const
        {
            return parse(row.at(fullKey()));
        }

    private:
        std::string key_;
    };
}
