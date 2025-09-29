//
// Created by Nekbakht Zabirov on 23.09.2025.
//

#pragma once
#include "icolumn.hpp"

namespace nekexposed::column
{
    template <class TABLE>
    class StringColumn final : public IColumn<TABLE, std::string>
    {
    public:
        explicit StringColumn(const std::string& key) : IColumn<TABLE, std::string>(key)
        {
        }
    };
}
