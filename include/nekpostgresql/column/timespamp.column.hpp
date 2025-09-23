//
// Created by Nekbakht Zabirov on 23.09.2025.
//

#pragma once
#include "icolumn.hpp"
#include <chrono>

namespace nekpostgresql::column
{
    using timestamp = std::chrono::system_clock::time_point;

    template <class TABLE>
    class TimestampColumn final : public IColumn<TABLE, timestamp>
    {
    public:
        explicit TimestampColumn(const std::string& key) : IColumn<TABLE, timestamp>(key)
        {
        }

        timestamp parse(const pqxx::field& field) override
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
