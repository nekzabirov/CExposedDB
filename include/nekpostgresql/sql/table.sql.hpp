//
// Created by Nekbakht Zabirov on 28.09.2025.
//

#pragma once

#include "nekpostgresql/sql/sql.hpp"

namespace nekpostgresql::sql
{
    class TableSql : public Sql
    {
    public:
        explicit TableSql() = default;

        explicit TableSql(std::string name) : name(std::move(name))
        {
        }

        virtual std::string getName() const;

    private:
        std::string name;
    };
}
