#pragma once

#include <Fire/core/macros.hpp>
#include <spdlog/spdlog.h>

namespace Fire {
    class FIRE_API Logger {
    public:
        static void Initialize();
        static void Destory();
    private:
        Logger();
        ~Logger();
    public:
        void setLevel(spdlog::level::level_enum level);

        template<typename... Args>
        void trace(Args &&... args) {
            spd_logger->trace(std::forward<Args>(args)...);
        }

        template<typename... Args>
        void debug(Args &&... args) {
            spd_logger->debug(std::forward<Args>(args)...);
        }

        template<typename... Args>
        void info(Args &&... args) {
            spd_logger->info(std::forward<Args>(args)...);
        }

        template<typename... Args>
        void warn(Args &&... args) {
            spd_logger->warn(std::forward<Args>(args)...);
        }

        template<typename... Args>
        void error(Args &&... args) {
            spd_logger->error(std::forward<Args>(args)...);
        }

        template<typename... Args>
        void fatal(Args &&... args) {
            spd_logger->critical(std::forward<Args>(args)...);
        }
    private:
        std::shared_ptr<spdlog::logger> spd_logger;
        spdlog::level::level_enum level = spdlog::level::info;
    };

    FIRE_API extern Logger *g_logger;

    FIRE_API void SetLogLevel(spdlog::level::level_enum level);
}

#define FIRE_TRACE(...) ::Fire::g_logger->trace(__VA_ARGS__);
#define FIRE_DEBUG(...) ::Fire::g_logger->debug(__VA_ARGS__);
#define FIRE_INFO(...) ::Fire::g_logger->info(__VA_ARGS__);
#define FIRE_WARN(...) ::Fire::g_logger->warn(__VA_ARGS__);
#define FIRE_ERROR(...) ::Fire::g_logger->error(__VA_ARGS__);
#define FIRE_FATAL(...) ::Fire::g_logger->fatal(__VA_ARGS__);
