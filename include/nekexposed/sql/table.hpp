#pragma once

#include "column.hpp"
#include <string>
#include <vector>
#include <memory>

namespace nekexposed::sql
{
    // Базовый класс для таблиц
    class Table : public SqlExpression
    {
    public:
        Table() = default;

        explicit Table(const std::string_view name) : name_(name)
        {
        }

        [[nodiscard]] virtual std::string name() const
        {
            return name_;
        }

        [[nodiscard]] std::string qualified_name(const std::string_view schema = "") const
        {
            if (schema.empty())
            {
                return name_;
            }
            return std::string(schema) + "." + name_;
        }

    protected:
        std::string name_;
    };
} // namespace nekexposed::sql
