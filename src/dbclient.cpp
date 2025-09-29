//
// Created by Nekbakht Zabirov on 19.09.2025.
//

#include <memory>

#include "../include/nekexposed/db/dbclient.hpp"

namespace nekexposed::db
{
    std::unique_ptr<PQConnectionDecorator> DBClient::getConn()
    {
        std::unique_lock lock(mutex);

        cv.wait(lock, [this] { return !connections.empty(); });

        auto* conn = connections.front();
        connections.pop();

        auto callback = [this](pqxx::connection* c) { this->pushConnection(c); };
        return std::make_unique<PQConnectionDecorator>(conn, std::move(callback));
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
