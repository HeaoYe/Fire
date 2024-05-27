#include <Fire/Fire.hpp>

int main() {
    Fire::Logger::Initialize();
    Fire::ThreadPool *tp = new Fire::ThreadPool {};

    auto *p = Fire::Task::CreateTask([]() {
        FIRE_INFO("Task Test");
    });
    auto *p1 = Fire::Task::CreateTask([]() {
        for (int i = 0; i < 100; i ++) {
            volatile float d;
            for (int j = 0; j < 20000; j ++) {
                d = std::min(0.999999, std::max(acos(i / 1001.f) / sqrt(sqrt(sqrt(exp(acos(i / 1001.f))))) / exp(sin(i) / cos(i) / acos(i / 1001.f) * sin(i)), 0.00001));
            }
            FIRE_INFO("Task Test 1 {}", d)
        }
    });
    auto *p2 = Fire::Task::CreateTask([]() {
        for (int i = 0; i < 100; i ++) {
            volatile float d;
            for (int j = 0; j < 20000; j ++) {
                d = std::min(0.999999, std::max(acos(i / 1001.f) / sqrt(sqrt(sqrt(exp(acos(i / 1001.f))))) / exp(sin(i) / cos(i) / acos(i / 1001.f) * sin(i)), 0.00001));
            }
            FIRE_INFO("Task Test 2 {}", d)
        }
    });
    tp->addTask(p);
    auto ps = std::vector<Fire::TaskPtr>({ p1, p2 });
    tp->addTasks(ps);
    p2->wait();
    p2->wait();
    p2->reset();
    tp->addTask(p2);
    FIRE_WARN("AAAA")
    p2->wait();
    auto pf = Fire::ParallelFor2D(*tp, 900, 1000, 700, 710, [](int i, int k) {
        volatile float d;
        for (int j = 0; j < 20000; j ++) {
            d = std::min(0.999999, std::max(acos(i / 1001.f) / sqrt(sqrt(sqrt(exp(acos(i / 1001.f))))) / exp(sin(i) / cos(i) / acos(i / 1001.f) * sin(i)), 0.00001));
        }
        FIRE_INFO("Task Test PF {}-{} {}", i, k, d)
    });
    pf->wait();
    FIRE_WARN("BBBBBB")
    delete tp;
    Fire::Task::FreeTask(p);
    Fire::Task::FreeTask(p1);
    Fire::Task::FreeTask(p2);
    Fire::Task::FreeTask(pf);

    Fire::Point2r point1 { 3, 2 };
    Fire::Point2r point2 { 1, 2 };
    auto point3 = point1 + point2;
    FIRE_WARN("{} {}", point3.x, point3.y)

    Fire::Vector3r vector1 { 2, 4.2, 1.2 };
    Fire::Vector3r vector2 { 1.2, -.2, 3.2};
    auto vector3 = Fire::Real(3) * vector1 * vector2;
    FIRE_WARN("{} {} {}", vector3.x, vector3.y, vector3.z)

    Fire::Logger::Destory();
    return 0;
}
