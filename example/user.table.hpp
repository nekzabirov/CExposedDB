//
// Created by Nekbakht Zabirov on 17.09.2025.
//

#ifndef CPOSTGRESQL_USER_TABLE_HPP
#define CPOSTGRESQL_USER_TABLE_HPP

#include <nekpostgresql/table.hpp>

class UserTable : public Table<UserTable>
{
public:
    static constexpr std::string tableName = "users";

    // Define columns as inline static members - they auto-register in parent's array
    inline static IColumn<UserTable, int> id{"id"};
    inline static IColumn<UserTable, std::string> name{"name"};
    inline static IColumn<UserTable, int> age{"age"};
};

#endif //CPOSTGRESQL_USER_TABLE_HPP