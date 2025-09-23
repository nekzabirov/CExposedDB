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

    sql::QuerySql query;
    const auto sql = query.select(UserTable::first_name.sql(), UserTable::last_name.sql())
                          .from(UserTable::TABLE_NAME.data)
                          .where(UserTable::first_name.sql().iLike("A%"))
                          .limit(1)
                          .str();

    std::cout << sql << std::endl;

    return 0;
}
