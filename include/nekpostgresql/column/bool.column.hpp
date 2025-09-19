//
// Created by Nekbakht Zabirov on 17.09.2025.
//

#ifndef CPOSTGRESQL_BOOL_COLUMN_HPP
#define CPOSTGRESQL_BOOL_COLUMN_HPP

#include "icolumn.hpp"

namespace nekpostgresql
{
    template <typename TableType>
    class BoolColumn final : public IColumn<TableType, bool>
    {
    public:
        explicit BoolColumn(const char* name)
            : IColumn<TableType, bool>(name)
        {
        }

        std::string format(const bool& value) const override;
    };
}

#endif //CPOSTGRESQL_BOOL_COLUMN_HPP
