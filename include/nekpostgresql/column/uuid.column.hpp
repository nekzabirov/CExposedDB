//
// Created by Nekbakht Zabirov on 17.09.2025.
//

#ifndef CPOSTGRESQL_UUID_COLUMN_HPP
#define CPOSTGRESQL_UUID_COLUMN_HPP

#include <string>
#include "icolumn.hpp"

using uuid = std::string;

template <typename TableType>
class UuidColumn final : public IColumn<TableType, uuid>
{
public:
    explicit UuidColumn(const char* name)
        : IColumn<TableType, uuid>(name)
    {
    }

    [[nodiscard]] std::string format(const uuid& value) const override
    {
        return "'" + value + "'";
    }
};

#endif //CPOSTGRESQL_UUID_COLUMN_HPP
