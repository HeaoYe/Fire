#include "core/logger.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Fire {
    void Logger::Initialize() {
        if (g_logger) {
            return;
        }
        g_logger = new Logger();
    }

    void Logger::Destory() {
        if (!g_logger) {
            return;
        }
        delete g_logger;
        g_logger = nullptr;
        spdlog::shutdown();
    }

    Logger::Logger() {
        spd_logger = spdlog::stdout_color_mt("Fire");
        spd_logger->set_level(level);
    }

    Logger::~Logger() {
        spd_logger.reset();
    }

    void Logger::setLevel(spdlog::level::level_enum level) {
        spd_logger->set_level(level);
    }

    Logger *g_logger = nullptr;

    void SetLogLevel(spdlog::level::level_enum level) {
        if (!g_logger) {
            Logger::Initialize();
        }
        g_logger->setLevel(level);
    }
}
