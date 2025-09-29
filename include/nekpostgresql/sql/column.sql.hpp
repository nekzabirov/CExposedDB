//
// Created by Nekbakht Zabirov on 23.09.2025.
//

#pragma once

#include <string>
#include <optional>
#include "sql.hpp"
#include "value.sql.hpp"

namespace nekpostgresql::sql
{
    class ColumnSql : public Sql
    {
    public:
        explicit ColumnSql(const std::string& key)
        {
            *this << key;
        };

        template <typename T>
        ColumnSql& operator=(const T& value)
        {
            *this->append(value, "=");
            return *this;
        }

        ColumnSql& count()
        {
            std::stringstream ss;

            ss << "COUNT(" << str() << ")";

            this->ss_ = std::move(ss);

            return *this;
        }

        ColumnSql& as(std::string const& name)
        {
            ss_ << " as " << name;

            return *this;
        }

        ColumnSql& iLike(const std::string& value)
        {
            *this << " ILIKE " << "'" << value << "'";
            return *this;
        }

        ColumnSql& like(const std::string& value)
        {
            *this << " LIKE " << "'" << value << "'";
            return *this;
        }

        template <typename T>
        ColumnSql& operator==(const T& value)
        {
            this->append(value, "=");
            return *this;
        }

        template <typename T>
        ColumnSql& operator!=(const T& value)
        {
            *this->append(value, "!=");
            return *this;
        }

        template <typename T>
        ColumnSql& operator>(const T& value)
        {
            *this->append(value, ">");
            return *this;
        }

        template <typename T>
        ColumnSql& operator<(const T& value)
        {
            *this->append(value, "<");
            return *this;
        }

        template <typename T>
        ColumnSql& operator>=(const T& value)
        {
            *this->append(value, ">=");
            return *this;
        }

        template <typename T>
        ColumnSql& operator<=(const T& value)
        {
            *this->append(value, "<=");
            return *this;
        }

        ColumnSql& operator&&(const ColumnSql& other)
        {
            if (other.str().empty())
            {
                return *this;
            }

            std::stringstream ss;

            ss << "(" << str() << " AND " << other.str() << ")";

            this->ss_ = std::move(ss);

            return *this;
        }

        ColumnSql& operator||(const ColumnSql& other)
        {
            if (other.str().empty())
            {
                return *this;
            }

            std::stringstream ss;

            ss << "(" << str() << " OR " << other.str() << ")";

            this->ss_ = std::move(ss);

            return *this;
        }

    private:
        template <typename T>
        void append(const T& value, const std::string& op)
        {
            *this << " " << op << " " << value::format(value);
        }

        template <typename T>
        void append(const std::optional<T>& value, std::string op)
        {
            if (!value.has_value())
            {
                this->ss_.clear();
                return;
            }

            append(value.value(), op);
        }
    };
}
