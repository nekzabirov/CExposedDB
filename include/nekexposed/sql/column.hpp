#pragma once

#include "base.hpp"
#include "value.hpp"
#include "concepts.hpp"
#include <string>

namespace nekexposed::sql
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
        [[nodiscard]] Column operator=(const T& value)
        {
            Column tmp(name_);
            tmp.append(" = ");
            tmp.append(Value::format(value));
            return tmp;
        }

        // Операторы сравнения
        template <typename T>
        [[nodiscard]] Column operator==(const T& value)
        {
            Column tmp(name_);
            tmp.append(" = ");
            tmp.append(Value::format(value));
            return tmp;
        }

        template <typename T>
        [[nodiscard]] Column operator!=(const T& value)
        {
            Column tmp(name_);
            tmp.append(" != ");
            tmp.append(Value::format(value));
            return tmp;
        }

        template <typename T>
        [[nodiscard]] Column operator<(const T& value)
        {
            Column tmp(name_);
            tmp.append(" != ");
            tmp.append(Value::format(value));
            return tmp;
        }

        template <typename T>
        [[nodiscard]] Column operator<=(const T& value)
        {
            Column tmp(name_);
            tmp.append(" <= ");
            tmp.append(Value::format(value));
            return tmp;
        }

        template <typename T>
        [[nodiscard]] Column operator>(const T& value)
        {
            Column tmp(name_);
            tmp.append(" > ");
            tmp.append(Value::format(value));
            return tmp;
        }

        template <typename T>
        [[nodiscard]] Column operator>=(const T& value)
        {
            Column tmp(name_);
            tmp.append(" >= ");
            tmp.append(Value::format(value));
            return tmp;
        }

        // Pattern matching
        [[nodiscard]] Column like(const std::string_view pattern) const
        {
            Column tmp(name_);
            tmp.append(" LIKE ");
            tmp.append(Value::format(pattern));
            return tmp;
        }

        [[nodiscard]] Column ilike(const std::string_view pattern) const
        {
            Column tmp(name_);
            tmp.append(" ILIKE ");
            tmp.append(Value::format(pattern));
            return tmp;
        }

        // NULL проверки
        [[nodiscard]] Column is_null() const
        {
            Column tmp(name_);
            tmp.append(" IS NULL");
            return tmp;
        }

        [[nodiscard]] Column is_not_null() const
        {
            Column tmp(name_);
            tmp.append(" IS NOT NULL");
            return tmp;
        }

        // IN оператор
        template <typename Container>
            requires concepts::Container<Container>
        [[nodiscard]] Column in(const Container& values)
        {
            Column tmp(name_);

            tmp.append(" IN (");

            bool first = true;
            for (const auto& val : values)
            {
                if (!first) tmp.append(", ");
                first = false;
                tmp.append(Value::format(val));
            }

            tmp.append(")");

            return tmp;
        }

        // BETWEEN оператор
        template <typename T>
        [[nodiscard]] Column between(const T& lower, const T& upper)
        {
            Column tmp(name_);
            tmp.append(" BETWEEN ");
            tmp.append(Value::format(lower));
            tmp.append(" AND ");
            tmp.append(Value::format(upper));
            return tmp;
        }

        // Агрегатные функции
        [[nodiscard]] Column count() const
        {
            Column tmp(name_);
            tmp.append("COUNT(");
            tmp.append(name_);
            tmp.append(")");
            return tmp;
        }

        [[nodiscard]] Column sum() const
        {
            Column tmp(name_);
            tmp.append("SUM(");
            tmp.append(name_);
            tmp.append(")");
            return tmp;
        }

        [[nodiscard]] Column avg() const
        {
            Column tmp(name_);
            tmp.append("AVG(");
            tmp.append(name_);
            tmp.append(")");
            return tmp;
        }

        [[nodiscard]] Column min() const
        {
            Column tmp(name_);
            tmp.append("MIN(");
            tmp.append(name_);
            tmp.append(")");
            return tmp;
        }

        [[nodiscard]] Column max() const
        {
            Column tmp(name_);
            tmp.append("MAX(");
            tmp.append(name_);
            tmp.append(")");
            return tmp;
        }

        // DISTINCT
        [[nodiscard]] Column distinct() const
        {
            Column tmp(name_);
            tmp.append("DISTINCT ");
            tmp.append(name_);
            return tmp;
        }

        // AS (алиас)
        [[nodiscard]] Column as(const std::string_view alias) const
        {
            Column tmp(name_);
            tmp.append(" AS ");
            tmp.append(alias);
            return tmp;
        }

        // CAST
        [[nodiscard]] Column cast(const std::string_view type) const
        {
            Column tmp(name_);
            tmp.append("CAST(");
            tmp.append(name_);
            tmp.append(" AS ");
            tmp.append(type);
            tmp.append(")");
            return tmp;
        }

        // DESC/ASC для ORDER BY
        [[nodiscard]] Column asc() const
        {
            Column tmp(name_);
            tmp.append(" ASC");
            return tmp;
        }

        [[nodiscard]] Column desc() const
        {
            Column tmp(name_);
            tmp.append(" DESC");
            return tmp;
        }

        // Логические операторы
        [[nodiscard]] Column& operator&&(const Column& other)
        {
            if (other.empty()) return *this;
            if (this->empty()) return *this;

            const auto str = this->to_sql();

            clear();

            append("(");
            append(str);
            append(" AND ");
            append(other.to_sql());
            append(")");

            return *this;
        }

        [[nodiscard]] Column& operator||(const Column& other)
        {
            if (other.empty()) return *this;
            if (this->empty()) return *this;

            const auto str = this->to_sql();

            clear();

            append("(");
            append(str);
            append(" || ");
            append(other.to_sql());
            append(")");

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
} // namespace nekexposed::sql
