//
// Created by Nekbakht Zabirov on 13.09.2025.
//

#include <../include/nekexposed/db/pqexecutor.hpp>

namespace nekpostgresql
{
    PQExecutor::~PQExecutor() noexcept
    {
        delete transaction_;

        if (on_release_)
        {
            on_release_(conn_);
        }
    }

    void PQExecutor::nontransaction() noexcept
    {
        delete transaction_;

        transaction_ = new pqxx::nontransaction(*conn_);
    }

    void PQExecutor::transaction() noexcept
    {
        delete transaction_;

        transaction_ = new pqxx::work(*conn_);
    }

    pqxx::result PQExecutor::exec(const std::string_view& query) const
    {
        if (!transaction_)
        {
            throw std::runtime_error("transaction is not started");
        }

        return transaction_->exec(query.data());
    }

    void PQExecutor::commit() const
    {
        if (!transaction_)
        {
            throw std::runtime_error("transaction is not started");
        }

        transaction_->commit();
    }
}
