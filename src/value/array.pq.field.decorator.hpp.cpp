//
// Created by Nekbakht Zabirov on 10.11.2025.
//

#include <nekexposed/db/pq.field.decorator.hpp>
#include <sstream>

namespace nekexposed::value
{
    template <>
    [[nodiscard]] inline std::string format(const std::vector<std::string>& value)
    {
        std::ostringstream oss;

        oss << "'{";
        for (std::size_t i = 0; i < value.size(); ++i)
        {
            if (i > 0) oss << ", ";

            oss << "'" << value[i] << "'";
        }
        oss << "}'";

        return oss.str();
    }
}