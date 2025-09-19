//
// Created by Nekbakht Zabirov on 16.09.2025.
//

#ifndef CPOSTGRESQL_TABLE_HPP
#define CPOSTGRESQL_TABLE_HPP

#include <array>
#include <iostream>
#include "column/icolumn.hpp"
#include <string>

template <typename Derived, std::size_t MaxColumns = 100>
class Table
{
public:
    // Static array to hold all columns for this table type
    static inline std::array<const ColumnBase<Derived>*, MaxColumns> columns{};
    
    // Method to register columns (called from Column constructor)
    static void registerColumn(const ColumnBase<Derived>* col)
    {
        if (column_count < MaxColumns) {
            columns[column_count++] = col;
        }
    }
    
    // Get table name (can be overridden in derived classes)
    static std::string getTableName()
    {
        return Derived::tableName;
    }

    static inline std::size_t column_count = 0;
};

#endif //CPOSTGRESQL_TABLE_HPP
