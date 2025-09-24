//
// Created by Nekbakht Zabirov on 24.09.2025.
//

#pragma once

#include "sql.hpp"
#include "value.sql.hpp"

namespace nekpostgresql::sql
{
    class ExecuteSql : public Sql
    {
    public:
        ExecuteSql()
        = default;

        ExecuteSql& insertInto(const std::string& table, const std::initializer_list<ColumnSql>& columns)
        {
            *this << "INSERT INTO " << table;
            *this << " (";
            for (int i = 0; i < columns.size(); i++)
            {
                *this << columns.begin()[i].str();
                if (i != columns.size() - 1)
                {
                    *this << ", ";
                }
            }
            *this << ")";

            return *this;
        }

        template <typename... V>
        ExecuteSql& values(const V&... vals)
        {
            *this << " VALUES (";
            bool first = true;
            auto append = [&](auto&& v) {
                if (!first) { *this << ", "; }
                first = false;
                *this << value::format(v);
            };
            (append(vals), ...);
            *this << ")";
            return *this;
        }

        ExecuteSql& onConflict(const std::initializer_list<ColumnSql>& columns)
        {
            *this << " ON CONFLICT (";
            for (int i = 0; i < columns.size(); i++)
            {
                *this << columns.begin()[i].str();
                if (i != columns.size() - 1)
                {
                    *this << ", ";
                }
            }
            *this << ")";
            return *this;
        }

        template <typename... V>
        ExecuteSql& onConflict(const V&... vals) {
            return onConflict({vals...});
        }

        ExecuteSql& doUpdate() {
            *this << " DO UPDATE ";
            return *this;
        }

        ExecuteSql& set(const std::initializer_list<ColumnSql>& columns)
        {
            *this << " SET ";
            for (int i = 0; i < columns.size(); i++)
            {
                *this << columns.begin()[i].str();
                if (i != columns.size() - 1)
                {
                    *this << ", ";
                }
            }
            return *this;
        }

        template <typename... V>
        ExecuteSql& set(const V&... vals)
        {
            return set({vals...});
        }

        ExecuteSql& returning(const std::initializer_list<ColumnSql>& columns)
        {
            *this << " RETURNING ";
            for (int i = 0; i < columns.size(); i++)
            {
                *this << columns.begin()[i].str();
                if (i != columns.size() - 1)
                {
                    *this << ", ";
                }
            }
            return *this;
        }

        template <typename... V>
        ExecuteSql& returning(const V&... vals)
        {
            return returning({vals...});
        }

    };
}
