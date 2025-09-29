//
// Created by Nekbakht Zabirov on 23.09.2025.
//

#pragma once
#include "icolumn.hpp"

namespace nekexposed::column
{
    template <class TABLE>
    class IntColumn final : public IColumn<TABLE, int>
    {
    public:
        explicit IntColumn(const std::string& key) : IColumn<TABLE, int>(key)
        {
        }
    };
}