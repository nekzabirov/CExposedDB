//
// Created by Nekbakht Zabirov on 17.09.2025.
//

#ifndef CPOSTGRESQL_USER_TABLE_HPP
#define CPOSTGRESQL_USER_TABLE_HPP

#include <string>
#include <nekpostgresql/table.hpp>
#include "nekpostgresql/column/string.column.hpp"
#include "nekpostgresql/column/integer.column.hpp"


class UserTable : public Table<UserTable>
{
public:
    static constexpr std::string tableName = "users";

    // Define columns as inline static members - they auto-register in parent's array
    inline static IntegerColumn<UserTable> id{"id"};
    inline static StringColumn<UserTable> name{"name"};
    inline static IntegerColumn<UserTable> age{"age"};
};

#endif //CPOSTGRESQL_USER_TABLE_HPP