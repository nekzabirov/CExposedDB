//
// Created by Nekbakht Zabirov on 17.09.2025.
//

#include <nekpostgresql/column/string.column.hpp>

template <typename TableType>
std::string StringColumn<TableType>::format(const std::string& value) const
{
    return "'" + value + "'";
}