#pragma once

#include "base.hpp"
#include "value.hpp"
#include "concepts.hpp"
#include <string>
#include <vector>
#include <array>

namespace nekpostgresql::sql
{
    // Класс представляющий колонку в SQL запросе
    class Column : public SqlExpression
    {
    public:
        explicit Column(const std::string_view name)
        {
            append(name);
            name_ = std::string(name);
        }

        template <typename T>
        [[nodiscard]] Column& operator=(const T& value)
        {
            append(" = ");
            append(Value::format(value));
            return *this;
        }

        // Операторы сравнения
        template <typename T>
        [[nodiscard]] Column& operator==(const T& value)
        {
            append(" = ");
            append(Value::format(value));
            return *this;
        }

        template <typename T>
        [[nodiscard]] Column& operator!=(const T& value)
        {
            append(" != ");
            append(Value::format(value));
            return *this;
        }

        template <typename T>
        [[nodiscard]] Column& operator<(const T& value)
        {
            append(" < ");
            append(Value::format(value));
            return *this;
        }

        template <typename T>
        [[nodiscard]] Column& operator<=(const T& value)
        {
            append(" <= ");
            append(Value::format(value));
            return *this;
        }

        template <typename T>
        [[nodiscard]] Column& operator>(const T& value)
        {
            append(" > ");
            append(Value::format(value));
            return *this;
        }

        template <typename T>
        [[nodiscard]] Column& operator>=(const T& value)
        {
            append(" >= ");
            append(Value::format(value));
            return *this;
        }

        // Логические операторы
        [[nodiscard]] Column& operator&&(const Column& other)
        {
            if (other.empty()) return *this;
            if (this->empty()) return *this;

            append("(");
            append(this->to_sql());
            append(" AND ");
            append(other.to_sql());
            append(")");
            return *this;
        }

        [[nodiscard]] Column& operator||(const Column& other)
        {
            if (other.empty()) return *this;
            if (this->empty()) return *this;

            append("(");
            append(this->to_sql());
            append(" OR ");
            append(other.to_sql());
            append(")");
            return *this;
        }

        // Pattern matching
        [[nodiscard]] Column& like(const std::string_view pattern)
        {
            append(" LIKE ");
            append(Value::format(pattern));
            return *this;
        }

        [[nodiscard]] Column& ilike(std::string_view pattern)
        {
            append(" ILIKE ");
            append(Value::format(pattern));
            return *this;
        }

        // NULL проверки
        [[nodiscard]] Column& is_null()
        {
            append(" IS NULL");
            return *this;
        }

        [[nodiscard]] Column& is_not_null()
        {
            append(" IS NOT NULL");
            return *this;
        }

        // IN оператор
        template <typename Container>
            requires concepts::Container<Container>
        [[nodiscard]] Column& in(const Container& values)
        {
            append(" IN (");

            bool first = true;
            for (const auto& val : values)
            {
                if (!first) append(", ");
                first = false;
                append(Value::format(val));
            }

            append(")");
            return *this;
        }

        // BETWEEN оператор
        template <typename T>
        [[nodiscard]] Column& between(const T& lower, const T& upper)
        {
            append(" BETWEEN ");
            append(Value::format(lower));
            append(" AND ");
            append(Value::format(upper));
            return *this;
        }

        // Агрегатные функции
        [[nodiscard]] Column& count()
        {
            append("COUNT(");
            append(this->to_sql());
            append(")");
            return *this;
        }

        [[nodiscard]] Column& sum()
        {
            append("SUM(");
            append(this->to_sql());
            append(")");
            return *this;
        }

        [[nodiscard]] Column& avg()
        {
            append("AVG(");
            append(this->to_sql());
            append(")");
            return *this;
        }

        [[nodiscard]] Column& min()
        {
            append("MIN(");
            append(this->to_sql());
            append(")");
            return *this;
        }

        [[nodiscard]] Column& max()
        {
            append("MAX(");
            append(this->to_sql());
            append(")");
            return *this;
        }

        // DISTINCT
        [[nodiscard]] Column& distinct()
        {
            append("DISTINCT ");
            append(this->to_sql());
            return *this;
        }

        // AS (алиас)
        [[nodiscard]] Column& as(const std::string_view alias)
        {
            append(" AS ");
            append(alias);
            return *this;
        }

        // CAST
        [[nodiscard]] Column& cast(const std::string_view type)
        {
            append("CAST(");
            append(this->to_sql());
            append(" AS ");
            append(type);
            append(")");
            return *this;
        }

        // DESC/ASC для ORDER BY
        [[nodiscard]] Column& asc()
        {
            append(" ASC");
            return *this;
        }

        [[nodiscard]] Column& desc()
        {
            append(" DESC");
            return *this;
        }

        // Получить имя колонки
        [[nodiscard]] const std::string& name() const
        {
            return name_;
        }

    private:
        std::string name_;
    };

    // Фабричная функция
    [[nodiscard]] inline Column col(const std::string_view name)
    {
        return Column(name);
    }

    // Специальные колонки
    [[nodiscard]] inline Column all()
    {
        return Column("*");
    }

    [[nodiscard]] inline Column count_all()
    {
        return Column("COUNT(*)");
    }
} // namespace nekpostgresql::sql
