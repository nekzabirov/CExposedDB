//
// Created by Nekbakht Zabirov on 23.09.2025.
//

#pragma once
#include "icolumn.hpp"

namespace nekpostgresql::column
{
    template <class TABLE>
    class IntColumn final : public IColumn<TABLE, bool>
    {
    public:
        explicit IntColumn(const std::string& key) : IColumn<TABLE, bool>(key)
        {
        }
    };
}
