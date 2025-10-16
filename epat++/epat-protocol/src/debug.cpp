#include "debug.h"
#include <chrono>
#include <iomanip>

namespace epat {
    namespace debug {
        std::string get_cur_time_str()
        {
            auto now = std::chrono::system_clock::now();
            auto now_c = std::chrono::system_clock::to_time_t(now);
            std::ostringstream oss;
            oss << std::put_time(std::localtime(&now_c), "%y%m%d%H%M%S");
            return oss.str();
        }
        std::ostream& get_log_file()
        {
            static std::fstream log_file_;
            if (!log_file_.is_open()) {
                log_file_.open("log" + get_cur_time_str() + ".txt", std::ios::out);
            }
            return log_file_;
        }
    }
}
