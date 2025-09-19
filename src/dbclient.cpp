//
// Created by Nekbakht Zabirov on 19.09.2025.
//

#include <memory>

#include "nekpostgresql/dbclient.hpp"

namespace nekpostgresql
{
    std::unique_ptr<PQExecutor> DBClient::createExecutor()
    {
        std::unique_lock lock(mutex);

        cv.wait(lock, [this] { return !connections.empty(); });

        auto* conn = connections.front();
        connections.pop();

        auto callback = [this](pqxx::connection* c) { this->pushConnection(c); };
        return std::make_unique<PQExecutor>(conn, std::move(callback));
    }

    DBClient::DBClient(const std::string& dbUrl, const int maxPoolSize)
    {
        for (int i = 0; i < maxPoolSize; ++i)
        {
            auto* newConn = new pqxx::connection(dbUrl);
            pushConnection(newConn);
        }
    }

    void DBClient::pushConnection(pqxx::connection* conn)
    {
        std::lock_guard lock(mutex);
        connections.push(conn);
        cv.notify_one();
    }
}
