//
// Created by Nekbakht Zabirov on 23.09.2025.
//

#pragma once
#include "icolumn.hpp"
#include <chrono>

namespace nekexposed::column
{
    using timestamp = std::chrono::system_clock::time_point;

    template <class TABLE>
    class TimestampColumn final : public IColumn<TABLE, timestamp>
    {
    public:
        explicit TimestampColumn(const std::string& key) : IColumn<TABLE, timestamp>(key)
        {
        }
    };
}
