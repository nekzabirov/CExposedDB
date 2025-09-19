//
// Created by Nekbakht Zabirov on 17.09.2025.
//

#ifndef CPOSTGRESQL_INTEGER_COLUMN_HPP
#define CPOSTGRESQL_INTEGER_COLUMN_HPP
#include "icolumn.hpp"

template <typename TableType>
class IntegerColumn final : public Column<TableType, int>
{
public:
    explicit IntegerColumn(const char* name)
        : Column<TableType, int>(name)
    {
    }
};

#endif //CPOSTGRESQL_INTEGER_COLUMN_HPP
