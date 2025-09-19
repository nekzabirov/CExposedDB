//
// Created by Nekbakht Zabirov on 19.09.2025.
//

#pragma once

#include <mutex>
#include <condition_variable>
#include "nekpostgresql/pqexecutor.hpp"
#include <memory>
#include <queue>

namespace nekpostgresql
{
    namespace constants
    {
        constexpr auto ENV_DATABASE_URL = "DATABASE_URL";
        constexpr auto ENV_MAX_POOL_CONNECTIONS = "MAX_POOL_CONNECTIONS";
        constexpr auto DEFAULT_MAX_POOL_CONNECTIONS = 5;
        constexpr auto LOG_TAG = "DBClient";
    }

    class DBClient
    {
    public:
        static DBClient& getInstance()
        {
            const char* dbUrl = std::getenv(constants::ENV_DATABASE_URL);

            if (!dbUrl)
            {
                throw std::runtime_error("DATABASE_URL environment variable not set!");
            }

            const char* maxPoolConnStr     = std::getenv(constants::ENV_MAX_POOL_CONNECTIONS);
            const int   maxPoolConnections = maxPoolConnStr ? std::stoi(maxPoolConnStr) : 50;

            static DBClient instance(dbUrl, maxPoolConnections);

            return instance;
        }

        std::unique_ptr<PQExecutor> createExecutor();

    private:
        explicit DBClient(const std::string& dbUrl, int maxPoolSize = 10);

        std::queue<pqxx::connection*> connections;
        std::mutex mutex;
        std::condition_variable cv;

        void pushConnection(pqxx::connection* conn);
    };
}
