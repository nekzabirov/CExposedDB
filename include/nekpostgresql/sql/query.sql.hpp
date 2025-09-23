//
// Created by Nekbakht Zabirov on 23.09.2025.
//

#pragma once

#include <initializer_list>
#include <string>
#include "sql.hpp"
#include "column.sql.hpp"

namespace nekpostgresql::sql
{
    class QuerySql : public Sql
    {
    public:
        QuerySql()
        {
        }

        QuerySql& select(const std::initializer_list<ColumnSql>& columns)
        {
            *this << "SELECT ";
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

        template <typename... Col>
        QuerySql& select(const Col&... columns)
        {
            return select({columns...});
        }

        QuerySql& from(const std::string& table)
        {
            *this << " FROM " << table << " as " << table;
            return *this;
        }

        QuerySql& where(const ColumnSql& condition)
        {
            *this << " WHERE " << condition;
            return *this;
        }

        QuerySql& limit(const int limit)
        {
            *this << " LIMIT " << std::to_string(limit);
            return *this;
        }

        QuerySql& offset(const int offset)
        {
            *this << " OFFSET " << std::to_string(offset);
            return *this;
        }

        QuerySql& orderBy(const ColumnSql& column)
        {
            *this << " ORDER BY " << column;
            return *this;
        }

        QuerySql& orderBy(const ColumnSql& column, const bool asc)
        {
            *this << " ORDER BY " << column << " " << (asc ? "ASC" : "DESC");
            return *this;
        }

        QuerySql& groupBy(const ColumnSql& column)
        {
            *this << " GROUP BY " << column;
            return *this;
        }
    };
}
