//
// Created by Nekbakht Zabirov on 10.11.2025.
//

#pragma once

#include <nekexposed/db/pq.field.decorator.hpp>
#include <sstream>

namespace nekexposed::value
{
    template <>
    [[nodiscard]] inline std::string format(const std::vector<std::string>& value)
    {
        if (value.empty())
        {
            return "ARRAY[]::text[]";
        }

        std::ostringstream oss;

        oss << "'{";
        for (std::size_t i = 0; i < value.size(); ++i)
        {
            if (i > 0) oss << ", ";

            oss << "\"" << value[i] << "\"";
        }
        oss << "}'";

        return oss.str();
    }

    template <>
    [[nodiscard]] inline std::vector<std::string> parse(const pqxx::field& field)
    {
        const auto value = field.as_sql_array<std::string>();

        std::vector<std::string> result;

        result.reserve(value.size());
        for (int i = 0; i < value.size(); ++i)
            result.push_back(value[i]);

        return result;
    }
}
