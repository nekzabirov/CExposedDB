//
// Created by Nekbakht Zabirov on 23.09.2025.
//

#pragma once
#include "icolumn.hpp"

namespace nekexposed::column
{
    template <class TABLE>
    class FloatColumn final : public IColumn<TABLE, float>
    {
    public:
        explicit FloatColumn(const std::string& key) : IColumn<TABLE, bool>(key)
        {
        }
    };
}
