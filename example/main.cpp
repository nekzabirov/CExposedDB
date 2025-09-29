//
// Created by Nekbakht Zabirov on 16.09.2025.
//

#include "user.table.hpp"
#include <iostream>

#include "user.table.hpp"

#include <nekpostgresql/nek.hpp>

int main()
{
    std::cout << "=== PostgreSQL C++ ORM Demo ===" << std::endl;

    for (const auto columns : UserTable::COLUMNS)
    {
        std::cout << columns->fullKey() << std::endl;
    }

    sql::QuerySql query;
    const auto sql = query.select<UserTable::COLUMN_SIZE>(UserTable::COLUMNS)
                          .from(UserTable::TABLE_NAME.data)
                          .where(UserTable::first_name.iLike("A%"))
                          .limit(1)
                          .str();

    std::cout << sql << std::endl;

    return 0;
}
