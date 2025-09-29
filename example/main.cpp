//
// Created by Nekbakht Zabirov on 16.09.2025.
//

#include <iostream>

#include <nekpostgresql/nek.hpp>

using namespace nekpostgresql;

using namespace nekpostgresql;

class UserTable final : public table::ITable<UserTable, 4, table::fixed_string("users")>
{
public:
    inline static column::IntColumn<UserTable> ID{"id"};

    inline static column::StringColumn<UserTable> FIRST_NAME{"first_name"};

    inline static column::StringColumn<UserTable> LAST_NAME{"last_name"};

    inline static column::IntColumn<UserTable> AGE{"age"};
};

int main()
{
    std::cout << "=== PostgreSQL C++ ORM Demo ===" << std::endl;

    {
        const auto query = sql::select()
                       .select(UserTable::ID, UserTable::FIRST_NAME, UserTable::LAST_NAME, UserTable::AGE)
                       .from<UserTable>()
                       .where(UserTable::AGE > 18)
                       .order_by(UserTable::FIRST_NAME, sql::SortDirection::ASC)
                       .limit(10)
                       .to_sql();

        std::cout << query << std::endl;
    }

    {
        const auto query = sql::insert()
                 .into<UserTable>(UserTable::FIRST_NAME, UserTable::LAST_NAME, UserTable::AGE)
                 .values("Jane", "Smith", 13)
                 .on_conflict(UserTable::FIRST_NAME)
                 .do_update_set(
                     UserTable::LAST_NAME == "Updated"
                 )
                 .returning_all()
                 .to_sql();

        std::cout << query << std::endl;
    }

    return 0;
}
