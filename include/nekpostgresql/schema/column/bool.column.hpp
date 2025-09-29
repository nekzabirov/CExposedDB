//
// Created by Nekbakht Zabirov on 23.09.2025.
//

#pragma once
#include "icolumn.hpp"

namespace nekpostgresql::column
{
    template <class TABLE>
    class BoolColumn final : public IColumn<TABLE, bool>
    {
    public:
        explicit BoolColumn(const std::string& key) : IColumn<TABLE, bool>(key)
        {
        }
    };
}
