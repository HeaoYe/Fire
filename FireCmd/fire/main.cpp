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

    Fire::Vector<float, 2> vec1 { 0, 2 };
    Fire::Vector<float, 2> vec2 { 1, 3 };
    auto vec3 = vec1 - vec2;
    vec3 *= 2.2;
    auto vec4 = -vec2;
    FIRE_WARN("{} {} {}", vec3.get(0), vec3.get(1), Dot(vec3, vec4))
    Fire::Vector<float, 3> vec1_3 { 0, 2 };
    Fire::Vector<float, 3> vec2_3 { 1, 3 };

    Fire::Scale<float, 3> scale3 { 1, 2, 2 };
    // Cross(vec1, vec2);   // error
    auto vec3_3 = Cross(vec1_3, vec2_3) / scale3;
    auto vec4_3 = Cross(vec2_3, vec1_3);
    FIRE_WARN("{} {} {}", vec3_3.get(0), vec3_3.get(1), vec3_3.get(2))
    FIRE_WARN("{} {} {}", vec4_3.get(0), vec4_3.get(1), vec4_3.get(2))

    Fire::Point<float, 3> point1 { 2, 1, 1 };
    Fire::Point<float, 3> point2 { 2, 1, 1 };
    point1 *= scale3;
    FIRE_WARN("{} {} {}", point1.get(0), point1.get(1), point1.get(2))
    auto vector_pp = point1 - point2;
    FIRE_WARN("{} {} {}", vector_pp.get(0), vector_pp.get(1), vector_pp.get(2))
    auto point3 = point2 + vector_pp;
    FIRE_WARN("{} {} {}", point3.get(0), point3.get(1), point3.get(2))
    FIRE_WARN("{} {}", Fire::Sqrt(-1.f), Fire::SafeSqrt(-1.f))

    Fire::Matrix<Fire::Real, 3, 3> mat = Fire::Matrix<Fire::Real, 3, 3>::IdentityMatrix();
    mat *= 2;
    auto res1 = Fire::Transpose(mat);
    auto res2 = Fire::Inverse(mat);
    auto res3 = res1 * res2;
    auto res4 = mat * vec4_3;
    Fire::Point3r res5 { res4 };

    auto wavelengths_sample = Fire::WavelengthsSample::GenerateUniformSample(0.2);
    Fire::ConstantSD csd { 1 };
    auto ss = Fire::SpectrumSample::FromSpectrumDistribution(csd, wavelengths_sample);
    ss.value += ss.value;
    ss.value *= ss.value;
    FIRE_WARN("{} {} {} {}", wavelengths_sample.getWavelength(0), wavelengths_sample.getWavelength(1), wavelengths_sample.getWavelength(2), wavelengths_sample.getWavelength(3))
    FIRE_WARN("{} {} {} {}", ss.value.get(0), ss.value.get(1), ss.value.get(2), ss.value.get(3))

    Fire::Logger::Destory();
    return 0;
}
