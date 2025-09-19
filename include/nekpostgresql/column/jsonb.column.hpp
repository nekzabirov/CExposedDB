//
// Created by Nekbakht Zabirov on 17.09.2025.
//

#ifndef CPOSTGRESQL_INTEGER_COLUMN_HPP
#define CPOSTGRESQL_INTEGER_COLUMN_HPP

#include <string>
#include "icolumn.hpp"

using jsonb = std::string;

template <typename TableType>
class JsonbColumn final : public IColumn<TableType, jsonb>
{
public:
    explicit JsonbColumn(const char* name)
        : IColumn<TableType, jsonb>(name)
    {
    }

    std::string format(const jsonb& value) const override;
};

#endif //CPOSTGRESQL_INTEGER_COLUMN_HPP
