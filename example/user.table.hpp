//
// Created by Nekbakht Zabirov on 17.09.2025.
//

#ifndef CPOSTGRESQL_USER_TABLE_HPP
#define CPOSTGRESQL_USER_TABLE_HPP

#include <string>
#include <nekpostgresql/table/itable.hpp>
#include <nekpostgresql/column/string.column.hpp>

using namespace nekpostgresql;

class UserTable : public table::ITable<UserTable, table::fixed_string("users")>
{
public:
    inline static column::StringColumn<UserTable> first_name{"first_name"};

    inline static column::StringColumn<UserTable> last_name{"last_name"};
};

#endif //CPOSTGRESQL_USER_TABLE_HPP