//
// Created by Nekbakht Zabirov on 16.09.2025.
//

#include "user.table.hpp"
#include <iostream>

#include "book.table.hpp"

int main()
{
    std::cout << "=== PostgreSQL C++ ORM Demo ===" << std::endl;

    std::cout << UserTable::getTableName() << " Columns:" << std::endl;
    for (int i = 0; i < UserTable::column_count; ++i)
    {
        const auto& column = UserTable::columns[i];
        std::cout << "UseTable -> Column: " << column->getName() << std::endl;
    }

    std::cout << std::endl;

    std::cout << "BookTable Columns:" << std::endl;
    for (int i = 0; i < BookTable::column_count; ++i)
    {
        const auto& column = BookTable::columns[i];
        std::cout << "BookTable -> Column: " << column->getName() << std::endl;
    }

    return 0;
}
