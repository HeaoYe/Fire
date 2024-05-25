#include <Fire/Fire.hpp>

int main() {
    Fire::Logger::Initialize();
    Fire::ThreadPool *tp = new Fire::ThreadPool {};

    auto *p = new Fire::Task([]() {
        FIRE_INFO("Task Test");
    });
    auto *p1 = new Fire::Task([]() {
        for (int i = 0; i < 10; i ++) {
            FIRE_INFO("Task Test 1 {}", i)
        }
    });
    auto *p2 = new Fire::Task([]() {
        for (int i = 0; i < 1000; i ++) {
            FIRE_INFO("Task Test 2 {}", i)
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    });
    tp->addTask(p);
    auto ps = std::vector<Fire::TaskPtr>({p1, p2});
    tp->addTasks(ps);
    p2->wait();
    p2->wait();
    FIRE_WARN("AAAA")
    delete tp;

    struct A {};
    Fire::LockFreeQueue<A> tq;
    tq.enqueue(A {});
    auto a = tq.dequeue();

    FIRE_WARN("HHH")
    FIRE_WARN("HHH")
    Fire::SetLogLevel(spdlog::level::err);
    FIRE_WARN("HHH")
    Fire::Logger::Destory();
    return 0;
}
