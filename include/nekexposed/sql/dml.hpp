#pragma once

#include "base.hpp"
#include "column.hpp"
#include "value.hpp"
#include "select.hpp"
#include <vector>
#include <tuple>
#include <stdexcept>

namespace nekpostgresql::sql
{
    // Класс для INSERT операций
    class Insert final : public SqlExpression
    {
    public:
        Insert() = default;

        // INTO таблица с колонками
        template <typename... Columns>
        [[nodiscard]] Insert& into(const std::string_view table, const Columns&... columns)
        {
            buffer_ << "INSERT INTO " << table << " (";

            bool first = true;
            ((buffer_ << (first ? "" : ", ") << columns.name(), first = false), ...);

            buffer_ << ")";
            table_name_ = std::string(table);
            return *this;
        }

        template <class TABLE, typename... Columns>
        [[nodiscard]] Insert& into(const Columns&... columns)
        {
            buffer_ << "INSERT INTO " << TABLE::TABLE_NAME << " (";

            bool first = true;
            ((buffer_ << (first ? "" : ", ") << columns.name(), first = false), ...);

            buffer_ << ")";
            table_name_ = std::string(TABLE::TABLE_NAME);
            return *this;
        }

        // VALUES для одной строки
        template <typename... Values>
        [[nodiscard]] Insert& values(const Values&... vals)
        {
            if (!has_values_)
            {
                buffer_ << " VALUES ";
                has_values_ = true;
            }
            else
            {
                buffer_ << ", ";
            }

            buffer_ << "(";
            bool first = true;
            ((buffer_ << (first ? "" : ", ") << Value::format(vals), first = false), ...);
            buffer_ << ")";

            return *this;
        }

        // Batch VALUES для множественной вставки
        template <typename Container>
        [[nodiscard]] Insert& values_batch(const Container& rows)
        {
            buffer_ << " VALUES ";

            bool first_row = true;
            for (const auto& row : rows)
            {
                if (!first_row) buffer_ << ", ";
                first_row = false;

                buffer_ << "(";
                if constexpr (requires { std::tuple_size_v<std::decay_t<decltype(row)>>; })
                {
                    // Если row - это tuple
                    std::apply([this, first = true](const auto&... vals) mutable
                    {
                        ((buffer_ << (first ? "" : ", ") << Value::format(vals), first = false), ...);
                    }, row);
                }
                else
                {
                    // Если row - одиночное значение
                    buffer_ << Value::format(row);
                }
                buffer_ << ")";
            }

            has_values_ = true;
            return *this;
        }

        // ON CONFLICT
        template <typename... Columns>
        [[nodiscard]] Insert& on_conflict(const Columns&... columns)
        {
            buffer_ << " ON CONFLICT (";

            bool first = true;
            ((buffer_ << (first ? "" : ", ") << columns.name(), first = false), ...);

            buffer_ << ")";
            has_conflict_ = true;
            return *this;
        }

        // DO NOTHING
        [[nodiscard]] Insert& do_nothing()
        {
            if (!has_conflict_)
            {
                throw std::logic_error("DO NOTHING requires ON CONFLICT");
            }

            buffer_ << " DO NOTHING";
            return *this;
        }

        // DO UPDATE SET
        template <typename... Columns>
        [[nodiscard]] Insert& do_update_set(const Columns&... columns)
        {
            if (!has_conflict_)
            {
                throw std::logic_error("DO UPDATE requires ON CONFLICT");
            }

            buffer_ << " DO UPDATE SET ";
            bool first = true;
            ((buffer_ << (first ? "" : ", ") << columns.to_sql(), first = false), ...);

            return *this;
        }

        // RETURNING
        template <typename... Columns>
        [[nodiscard]] Insert& returning(const Columns&... columns)
        {
            buffer_ << " RETURNING ";

            bool first = true;
            ((buffer_ << (first ? "" : ", ") << columns.name(), first = false), ...);

            return *this;
        }

        // RETURNING *
        [[nodiscard]] Insert& returning_all()
        {
            buffer_ << " RETURNING *";
            return *this;
        }

    private:
        std::string table_name_;
        bool has_values_ = false;
        bool has_conflict_ = false;
    };

    // Класс для UPDATE операций
    class Update final : public SqlExpression
    {
    public:
        Update() = default;

        // UPDATE таблица
        [[nodiscard]] Update& table(const std::string_view table_name)
        {
            buffer_ << "UPDATE " << table_name;
            table_name_ = std::string(table_name);
            return *this;
        }

        // SET присваивания
        template <typename... Columns>
        [[nodiscard]] Update& set(const Columns&... columns)
        {
            buffer_ << " SET ";

            bool first = true;
            ((buffer_ << (first ? "" : ", ") << columns.to_sql(), first = false), ...);

            return *this;
        }

        // FROM (PostgreSQL specific)
        [[nodiscard]] Update& from(const std::string_view table)
        {
            buffer_ << " FROM " << table;
            return *this;
        }

        // WHERE условие
        [[nodiscard]] Update& where(const Column& condition)
        {
            buffer_ << " WHERE " << condition.to_sql();
            return *this;
        }

        // RETURNING
        template <typename... Columns>
        [[nodiscard]] Update& returning(const Columns&... columns)
        {
            buffer_ << " RETURNING ";

            bool first = true;
            ((buffer_ << (first ? "" : ", ") << columns.name(), first = false), ...);

            return *this;
        }

        // RETURNING *
        [[nodiscard]] Update& returning_all()
        {
            buffer_ << " RETURNING *";
            return *this;
        }

    private:
        std::string table_name_;
    };

    // Класс для DELETE операций
    class Delete final : public SqlExpression
    {
    public:
        Delete() = default;

        // DELETE FROM таблица
        [[nodiscard]] Delete& from(const std::string_view table)
        {
            buffer_ << "DELETE FROM " << table;
            table_name_ = std::string(table);
            return *this;
        }

        // USING (PostgreSQL specific)
        [[nodiscard]] Delete& using_(const std::string_view table)
        {
            buffer_ << " USING " << table;
            return *this;
        }

        // WHERE условие
        [[nodiscard]] Delete& where(const Column& condition)
        {
            buffer_ << " WHERE " << condition.to_sql();
            return *this;
        }

        // RETURNING
        template <typename... Columns>
        [[nodiscard]] Delete& returning(const Columns&... columns)
        {
            buffer_ << " RETURNING ";

            bool first = true;
            ((buffer_ << (first ? "" : ", ") << columns.name(), first = false), ...);

            return *this;
        }

        // RETURNING *
        [[nodiscard]] Delete& returning_all()
        {
            buffer_ << " RETURNING *";
            return *this;
        }

    private:
        std::string table_name_;
    };

    // Фабричная функция
    [[nodiscard]] inline Insert insert()
    {
        return Insert{};
    }
} // namespace nekpostgresql::sql
