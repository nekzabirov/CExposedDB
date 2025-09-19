//
// Created by Nekbakht Zabirov on 17.09.2025.
//

#ifndef CPOSTGRESQL_INTEGER_COLUMN_HPP
#define CPOSTGRESQL_INTEGER_COLUMN_HPP

#include <chrono>
#include "icolumn.hpp"

namespace nekpostgresql
{
    using timestamp = std::chrono::system_clock::time_point;

    template <typename TableType>
    class TimeStampColumn final : public IColumn<TableType, timestamp>
    {
    public:
        explicit TimeStampColumn(const char* name)
            : IColumn<TableType, timestamp>(name)
        {
        }

        [[nodiscard]] std::string format(const timestamp& value) const override
        {
            const std::time_t t = std::chrono::system_clock::to_time_t(value);
            std::stringstream ss;
            ss << std::put_time(std::gmtime(&t), "'%Y-%m-%d %H:%M:%S UTC'");
            return ss.str();
        }

        [[nodiscard]] timestamp parse(const pqxx::field& field) const override
        {
            const std::string& result = field.as<std::string>();

            std::tm            tm = {};
            std::istringstream ss(result);
            ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

            if (ss.fail())
            {
                throw std::runtime_error("Failed to parse timestamp");
            }

            const std::time_t time_c = std::mktime(&tm);

            return std::chrono::system_clock::from_time_t(time_c);
        }
    };
}

#endif //CPOSTGRESQL_INTEGER_COLUMN_HPP
