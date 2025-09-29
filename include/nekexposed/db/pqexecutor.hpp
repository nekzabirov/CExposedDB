//
// Created by Nekbakht Zabirov on 12.09.2025.
//

#pragma once

#include <pqxx/pqxx>
#include <string_view>
#include <utility>
#include <functional>

namespace nekpostgresql
{
    using callback_t = std::function<void(pqxx::connection*)>;

    class PQExecutor
    {
    public:
        explicit PQExecutor(pqxx::connection* conn, callback_t cb) : conn_(conn), on_release_(std::move(cb))
        {
        }

        ~PQExecutor() noexcept;

        void nontransaction() noexcept;

        void transaction() noexcept;

        template <typename... TYPE>
        [[nodiscard]] pqxx::internal::result_iteration<TYPE...> query(const std::string_view& query) const
        {
            if (!transaction_)
            {
                throw std::runtime_error("transaction is not started");
            }

            return transaction_->query<TYPE...>(query.data());
        }

        [[nodiscard]] pqxx::result exec(const std::string_view& query) const;

        void commit() const;

    private:
        pqxx::connection* conn_;

        pqxx::transaction_base* transaction_ = nullptr;

        callback_t on_release_ = nullptr;
    };
}
