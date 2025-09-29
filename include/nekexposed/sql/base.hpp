#pragma once

#include <string>
#include <sstream>
#include <string_view>
#include <memory>

namespace nekexposed::sql
{
    // Базовый класс для всех SQL выражений
    class SqlExpression
    {
    public:
        SqlExpression() = default;
        virtual ~SqlExpression() = default;

        // Основной метод для получения SQL строки
        [[nodiscard]] virtual std::string to_sql() const
        {
            return buffer_.str();
        }

        // Проверка на пустоту
        [[nodiscard]] bool empty() const noexcept
        {
            return buffer_.str().empty();
        }

        // Очистка буфера
        void clear() const
        {
            buffer_.str("");
            buffer_.clear();
        }

    protected:
        // Добавление в буфер
        template <typename T>
        void append(const T& value)
        {
            buffer_ << value;
        }

        void append(const std::string_view value) const
        {
            buffer_ << value;
        }

        mutable std::stringstream buffer_;
    };
} // namespace nekexposed::sql
