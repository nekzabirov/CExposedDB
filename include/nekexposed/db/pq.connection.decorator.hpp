//
// Created by Nekbakht Zabirov on 29.09.2025.
//

#pragma once

#include <pqxx/pqxx>
#include <memory>

namespace nekexposed::db
{
    using callback_t = std::function<void(pqxx::connection*)>;

    class PQConnectionDecorator
    {
    public:
        explicit PQConnectionDecorator(pqxx::connection* conn, callback_t cb) : conn_(conn), on_release_(std::move(cb))
        {
        }

        ~PQConnectionDecorator() noexcept
        {
            if (on_release_)
            {
                on_release_(conn_);
            }
        }

        std::unique_ptr<pqxx::nontransaction> nontransaction() const
        {
            return std::make_unique<pqxx::nontransaction>(*conn_);
        }

        std::unique_ptr<pqxx::work> transaction() const
        {
            return std::make_unique<pqxx::work>(*conn_);
        }

    private:
        pqxx::connection* conn_;

        callback_t on_release_ = nullptr;
    };
}
