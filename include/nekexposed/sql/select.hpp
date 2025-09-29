#pragma once

#include "base.hpp"
#include "column.hpp"
#include "table.hpp"
#include <string>
#include <stdexcept>

namespace nekexposed::sql {

// Типы JOIN операций
enum class JoinType {
    INNER,
    LEFT,
    RIGHT,
    FULL,
    CROSS
};

// Направление сортировки
enum class SortDirection {
    ASC,
    DESC
};

// Класс для построения SELECT запросов
class Select final : public SqlExpression {
public:
    Select() = default;
    
    // SELECT колонки
    template<typename... Columns>
    [[nodiscard]] Select& select(const Columns&... columns) {
        if (has_select_) {
            throw std::logic_error("SELECT already specified");
        }
        
        buffer_ << "SELECT ";
        append_columns(columns...);
        has_select_ = true;
        return *this;
    }
    
    // SELECT DISTINCT
    [[nodiscard]] Select& distinct() {
        if (!has_select_) {
            throw std::logic_error("DISTINCT must come after SELECT");
        }
        
        auto sql = buffer_.str();
        auto pos = sql.find("SELECT");
        if (pos != std::string::npos) {
            sql.insert(pos + 6, " DISTINCT");
            buffer_.str(sql);
        }
        return *this;
    }
    
    // FROM таблица
    [[nodiscard]] Select& from(const std::string_view table) {
        if (!has_select_) {
            throw std::logic_error("FROM must come after SELECT");
        }
        
        buffer_ << " FROM " << table;
        has_from_ = true;
        current_table_ = std::string(table);
        return *this;
    }
    
    // FROM с алиасом
    [[nodiscard]] Select& from(const std::string_view table, const std::string_view alias) {
        if (!has_select_) {
            throw std::logic_error("FROM must come after SELECT");
        }

        buffer_ << " FROM " << table << " AS " << alias;
        has_from_ = true;
        current_table_ = std::string(table);
        return *this;
    }

    template<typename Table>
    [[nodiscard]] Select& from() {
        return from(Table::TABLE_NAME);
    }

    // JOIN операции
    [[nodiscard]] Select& join(const std::string_view table, const JoinType type = JoinType::INNER) {
        if (!has_from_) {
            throw std::logic_error("JOIN must come after FROM");
        }
        
        switch (type) {
            case JoinType::INNER:
                buffer_ << " INNER JOIN ";
                break;
            case JoinType::LEFT:
                buffer_ << " LEFT JOIN ";
                break;
            case JoinType::RIGHT:
                buffer_ << " RIGHT JOIN ";
                break;
            case JoinType::FULL:
                buffer_ << " FULL OUTER JOIN ";
                break;
            case JoinType::CROSS:
                buffer_ << " CROSS JOIN ";
                break;
        }
        
        buffer_ << table;
        return *this;
    }
    
    // Shortcut методы для JOIN
    [[nodiscard]] Select& inner_join(const std::string_view table) {
        return join(table, JoinType::INNER);
    }
    
    [[nodiscard]] Select& left_join(const std::string_view table) {
        return join(table, JoinType::LEFT);
    }

    [[nodiscard]] Select& right_join(const std::string_view table) {
        return join(table, JoinType::RIGHT);
    }
    
    [[nodiscard]] Select& full_join(const std::string_view table) {
        return join(table, JoinType::FULL);
    }
    
    [[nodiscard]] Select& cross_join(const std::string_view table) {
        return join(table, JoinType::CROSS);
    }
    
    // ON условие для JOIN
    [[nodiscard]] Select& on(const Column& condition) {
        buffer_ << " ON " << condition.to_sql();
        return *this;
    }
    
    // WHERE условие
    [[nodiscard]] Select& where(const Column& condition) {
        if (!has_from_) {
            throw std::logic_error("WHERE must come after FROM");
        }
        
        buffer_ << " WHERE " << condition.to_sql();
        has_where_ = true;
        return *this;
    }
    
    // GROUP BY
    template<typename... Columns>
    [[nodiscard]] Select& group_by(const Columns&... columns) {
        buffer_ << " GROUP BY ";
        append_columns(columns...);
        has_group_by_ = true;
        return *this;
    }
    
    // HAVING
    [[nodiscard]] Select& having(const Column& condition) {
        if (!has_group_by_) {
            throw std::logic_error("HAVING must come after GROUP BY");
        }
        
        buffer_ << " HAVING " << condition.to_sql();
        return *this;
    }
    
    // ORDER BY
    [[nodiscard]] Select& order_by(const Column& column, const SortDirection dir = SortDirection::ASC) {
        if (!has_order_by_) {
            buffer_ << " ORDER BY ";
            has_order_by_ = true;
        } else {
            buffer_ << ", ";
        }
        
        buffer_ << column.to_sql();
        buffer_ << (dir == SortDirection::ASC ? " ASC" : " DESC");
        return *this;
    }
    
    // LIMIT
    [[nodiscard]] Select& limit(const std::size_t count) {
        if (count == 0) {
            throw std::invalid_argument("LIMIT must be > 0");
        }
        
        buffer_ << " LIMIT " << count;
        return *this;
    }
    
    // OFFSET
    [[nodiscard]] Select& offset(const std::size_t count) {
        buffer_ << " OFFSET " << count;
        return *this;
    }
    
    // UNION
    [[nodiscard]] Select& union_with(const Select& other) {
        buffer_ << " UNION " << other.to_sql();
        return *this;
    }
    
    [[nodiscard]] Select& union_all(const Select& other) {
        buffer_ << " UNION ALL " << other.to_sql();
        return *this;
    }
    
    // INTERSECT
    [[nodiscard]] Select& intersect(const Select& other) {
        buffer_ << " INTERSECT " << other.to_sql();
        return *this;
    }
    
    // EXCEPT
    [[nodiscard]] Select& except(const Select& other) {
        buffer_ << " EXCEPT " << other.to_sql();
        return *this;
    }
    
    // FOR UPDATE
    [[nodiscard]] Select& for_update() {
        buffer_ << " FOR UPDATE";
        return *this;
    }
    
    [[nodiscard]] Select& for_update_nowait() {
        buffer_ << " FOR UPDATE NOWAIT";
        return *this;
    }
    
    [[nodiscard]] Select& for_update_skip_locked() {
        buffer_ << " FOR UPDATE SKIP LOCKED";
        return *this;
    }
    
    // FOR SHARE
    [[nodiscard]] Select& for_share() {
        buffer_ << " FOR SHARE";
        return *this;
    }
    
private:
    // Helper для добавления колонок
    template<typename... Columns>
    void append_columns(const Columns&... columns) {
        bool first = true;
        ((buffer_ << (first ? "" : ", ") << columns.to_sql(), first = false), ...);
    }
    
    bool has_select_ = false;
    bool has_from_ = false;
    bool has_where_ = false;
    bool has_group_by_ = false;
    bool has_order_by_ = false;
    std::string current_table_;
};

// Фабричная функция
[[nodiscard]] inline Select select() {
    return Select{};
}

} // namespace nekexposed::sql
