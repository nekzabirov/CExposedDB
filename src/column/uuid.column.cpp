//
// Created by Nekbakht Zabirov on 17.09.2025.
//

#include <nekpostgresql/column/uuid.column.hpp>

template <typename TableType>
std::string UuidColumn<TableType>::format(const uuid& value) const
{
    return "'" + value + "'";
}
