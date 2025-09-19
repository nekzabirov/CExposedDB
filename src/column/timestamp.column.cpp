//
// Created by Nekbakht Zabirov on 17.09.2025.
//

#include <nekpostgresql/column/timestamp.column.hpp>

template <typename TableType>
std::string TimeStampColumn<TableType>::format(const timestamp& value) const
{
    const std::time_t t = std::chrono::system_clock::to_time_t(value);
    std::stringstream ss;
    ss << std::put_time(std::gmtime(&t), "'%Y-%m-%d %H:%M:%S UTC'");
    return ss.str();
}

template <typename TableType>
timestamp TimeStampColumn<TableType>::parse(const pqxx::field& field) const
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
