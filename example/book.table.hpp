//
// Created by Nekbakht Zabirov on 17.09.2025.
//

#ifndef CPOSTGRESQL_BOOK_TABLE_HPP
#define CPOSTGRESQL_BOOK_TABLE_HPP

#include <nekpostgresql/table.hpp>

#include "nekpostgresql/column/string.column.hpp"
#include "nekpostgresql/column/uuid.column.hpp"

class BookTable : public Table<BookTable>
{
public:
    static constexpr std::string tableName = "books";

    inline static UuidColumn<BookTable> uuid{"uuid"};
    inline static StringColumn<BookTable> name{"name"};
    inline static StringColumn<BookTable> author_id{"author_id"};
};

#endif //CPOSTGRESQL_BOOK_TABLE_HPP