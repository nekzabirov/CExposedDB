//
// Created by Nekbakht Zabirov on 23.09.2025.
//

#pragma once
#include "icolumn.hpp"
#include <vector>

namespace nekexposed::column
{
    template <class TABLE, typename V>
    class ArrayColumn final : public IColumn<TABLE, std::vector<V>>
    {
    public:
        explicit ArrayColumn(const std::string& key) : IColumn<TABLE, std::vector<V>>(key)
        {
        }
    };
}
