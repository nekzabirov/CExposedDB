//
// Created by Nekbakht Zabirov on 17.09.2025.
//

#include <nekpostgresql/column/jsonb.column.hpp>

template <typename TableType>
std::string JsonbColumn<TableType>::format(const jsonb& value) const
{
    return std::format("'{}'::jsonb", value);
}
