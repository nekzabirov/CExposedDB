#ifndef CPOSTGRESQL_COLUMN_HPP
#define CPOSTGRESQL_COLUMN_HPP

#include <pqxx/pqxx>

namespace nekpostgresql
{
    template <typename TableType>
    class ColumnBase
    {
    protected:
        explicit ColumnBase(const char* name) : name_(name)
        {
            TableType::registerColumn(this);
        }

    public:
        virtual ~ColumnBase() = default;
        [[nodiscard]] const char* getName() const { return name_; }

    private:
        const char* name_;
    };

    template <typename TableType, typename V>
    class IColumn : public ColumnBase<TableType>
    {
    public:
        using value_type = V;

        explicit IColumn(const char* name) : ColumnBase<TableType>(name)
        {
        }

        virtual V parse(const pqxx::field& field) const
        {
            return field.as<V>();
        }

        virtual std::string format(const V& value) const
        {
            return "";
        }
    };
}

#endif //CPOSTGRESQL_COLUMN_HPP
