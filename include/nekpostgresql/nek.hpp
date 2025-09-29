//
// Created by Nekbakht Zabirov on 23.09.2025.
//

#pragma once

#include "nekpostgresql/sql/sql.hpp"
#include "nekpostgresql/sql/column.sql.hpp"
#include "nekpostgresql/sql/query.sql.hpp"
#include "schema/table/itable.hpp"
#include "nekpostgresql/schema/column/icolumn.hpp"
#include "nekpostgresql/schema/column/string.column.hpp"
#include "nekpostgresql/schema/column/bool.column.hpp"
#include "nekpostgresql/schema/column/int.column.hpp"
#include "nekpostgresql/schema/column/float.column.hpp"
#include "nekpostgresql/schema/column/timespamp.column.hpp"
#include "nekpostgresql/sql/execute.sql.hpp"
#include "nekpostgresql/sql/value.sql.hpp"
#include "nekpostgresql/sql/table.sql.hpp"

namespace nekpostgresql::sql
{
    template <typename... Col>
    QuerySql select(const Col&... columns)
    {
        return QuerySql().select(columns...);
    }

    inline ExecuteSql insertInto(const std::string& table, const std::initializer_list<ColumnSql>& columns)
    {
        return ExecuteSql().insertInto(table, columns);
    }
}