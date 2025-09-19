//
// Created by Nekbakht Zabirov on 17.09.2025.
//

#include "nekpostgresql/column/bool.column.hpp"

template <typename TableType>
std::string BoolColumn<TableType>::format(const bool& value) const
{
    return value ? "true" : "false";
}
