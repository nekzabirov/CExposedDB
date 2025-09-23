// ... existing code ...
#pragma once

#include <sstream>

namespace nekpostgresql::sql
{
    class Sql
    {
    public:
        Sql() = default;

        Sql(const Sql& other)
        {
            ss_ << other.ss_.str();
        }

        Sql& operator=(const Sql& other)
        {
            if (this != &other)
            {
                ss_.str("");
                ss_.clear();
                ss_ << other.ss_.str();
            }
            return *this;
        }

        explicit operator std::string() const
        {
            return ss_.str();
        }

        Sql& operator<<(const std::string_view& str)
        {
            ss_ << str;

            return *this;
        }

        Sql& operator<<(const Sql& sql)
        {
            ss_ << std::string(sql);

            return *this;
        }

        std::string str() const
        {
            return ss_.str();
        }

        

    protected:
        std::stringstream ss_;
    };
}

// ... existing code ...
