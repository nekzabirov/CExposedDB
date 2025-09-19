//
// Created by Nekbakht Zabirov on 17.09.2025.
//

#ifndef CPOSTGRESQL_STRING_COLUMN_HPP
#define CPOSTGRESQL_STRING_COLUMN_HPP

#include <string>
#include "icolumn.hpp"

namespace nekpostgresql
{
    template<typename TableType>
    class StringColumn final : public IColumn<TableType, std::string>
    {
    public:
        explicit StringColumn(const char* name)
            : IColumn<TableType, std::string>(name)
        {
        }

        [[nodiscard]] std::string format(const std::string& value) const override
        {
            return "'" + value + "'";
        }
    };
}

#endif //CPOSTGRESQL_STRING_COLUMN_HPP