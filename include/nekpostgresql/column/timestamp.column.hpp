//
// Created by Nekbakht Zabirov on 17.09.2025.
//

#ifndef CPOSTGRESQL_INTEGER_COLUMN_HPP
#define CPOSTGRESQL_INTEGER_COLUMN_HPP

#include <chrono>
#include "icolumn.hpp"

namespace nekpostgresql
{
    using timestamp = std::chrono::system_clock::time_point;

    template <typename TableType>
    class TimeStampColumn final : public IColumn<TableType, timestamp>
    {
    public:
        explicit TimeStampColumn(const char* name)
            : IColumn<TableType, timestamp>(name)
        {
        }

        [[nodiscard]] std::string format(const timestamp& value) const override;

        [[nodiscard]] timestamp parse(const pqxx::field& field) const override;
    };
}

#endif //CPOSTGRESQL_INTEGER_COLUMN_HPP
