// timestamp.value.hpp
#pragma once
#include <chrono>
#include <string>
#include <string_view>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <locale>

namespace nekexposed::value
{
    inline constexpr const char* kTimestampFormat = "%Y-%m-%d %H:%M:%S";

    using Timestamp = std::chrono::system_clock::time_point;

    inline std::tm to_local_tm(std::time_t tt) {
        std::tm tm{};
#if defined(_WIN32)
        localtime_s(&tm, &tt);
        return tm;
#elif defined(__unix__) || defined(__APPLE__)
        localtime_r(&tt, &tm);
        return tm;
#else
        const std::tm* ptm = std::localtime(&tt);
        if (ptm) tm = *ptm;
        return tm;
#endif
    }

    [[nodiscard]] inline std::string format(const Timestamp& value) {
        const std::time_t tt = std::chrono::system_clock::to_time_t(value);
        const std::tm tm = to_local_tm(tt);

        std::ostringstream oss;
        oss << "TIMESTAMP '"
            << std::put_time(&tm, kTimestampFormat)
            << "'";
        return oss.str();
    }

    // Renamed param to text; fix parsing with explicit std::get_time and state check
    [[nodiscard]] inline Timestamp parse(std::string_view text) {
        std::tm tm{};
        std::istringstream ss(std::string{text});
        ss.imbue(std::locale::classic());
        ss >> std::get_time(&tm, kTimestampFormat);
        if (!ss) {
            return Timestamp{}; // failure: epoch
        }
        return std::chrono::system_clock::from_time_t(std::mktime(&tm));
    }
}