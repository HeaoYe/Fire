#include <Fire/Fire.hpp>

int main() {
    Fire::Logger::Initialize();
    FIRE_WARN("HHH")
    FIRE_WARN("HHH")
    Fire::SetLogLevel(spdlog::level::err);
    FIRE_WARN("HHH")
    Fire::Logger::Destory();
    return 0;
}
