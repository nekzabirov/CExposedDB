//
// Created by Nekbakht Zabirov on 23.09.2025.
//

#pragma once

#include <string>
#include <utility>
#include "nekexposed/sql/column.hpp"

namespace nekexposed::column
{
    template <class TABLE>
    class IColumnBase : public sql::Column
    {
    public:
        explicit IColumnBase(std::string key) : Column(key), key_(std::move(key))
        {
            TABLE::registerColumn(this);
        }

        ~IColumnBase() override = default;

        [[nodiscard]] constexpr std::string key() const
        {
            return key_;
        }

        [[nodiscard]] constexpr std::string fullKey() const
        {
            return std::string(TABLE::TABLE_NAME.data) + "." + key_;
        }

    protected:
        std::string key_;
    };

    template <class TABLE, typename V>
    class IColumn : public IColumnBase<TABLE>
    {
    public:
        using value_type = V;
        using table = TABLE;
        constexpr static auto TABLE_NAME = TABLE::TABLE_NAME;

        explicit IColumn(std::string key) : IColumnBase<TABLE>(key)
        {
        }

        ~IColumn() override = default;

    private:
        std::string key_;
    };
}
