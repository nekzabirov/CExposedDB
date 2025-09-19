//
// Created by Nekbakht Zabirov on 17.09.2025.
//

#ifndef CPOSTGRESQL_INTEGER_COLUMN_HPP
#define CPOSTGRESQL_INTEGER_COLUMN_HPP
#include "icolumn.hpp"

namespace nekpostgresql
{
    template <typename TableType>
    class IntegerColumn final : public IColumn<TableType, int>
    {
    public:
        explicit IntegerColumn(const char* name)
            : IColumn<TableType, int>(name)
        {
        }

        [[nodiscard]] std::string format(const int& value) const override
        {
            return std::to_string(value);
        }
    };
}

#endif //CPOSTGRESQL_INTEGER_COLUMN_HPP
