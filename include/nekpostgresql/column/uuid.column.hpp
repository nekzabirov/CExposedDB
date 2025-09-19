//
// Created by Nekbakht Zabirov on 17.09.2025.
//

#ifndef CPOSTGRESQL_INTEGER_COLUMN_HPP
#define CPOSTGRESQL_INTEGER_COLUMN_HPP

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

    std::string format(const uuid& value) const override;
};

#endif //CPOSTGRESQL_INTEGER_COLUMN_HPP
