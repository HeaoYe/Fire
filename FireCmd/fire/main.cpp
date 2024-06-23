#include <Fire/Fire.hpp>

int main() {
    Fire::Logger::Initialize();
    Fire::Illuminants::Initialize();
    Fire::ColorSpace::Initialize();
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

    Fire::Vector<Fire::Real, 2> vec1 { 0, 2 };
    Fire::Vector<Fire::Real, 2> vec2 { 1, 3 };
    auto vec3 = vec1 - vec2;
    vec3 *= 2.2;
    auto vec4 = -vec2;
    FIRE_WARN("{} {} {}", vec3.x, vec3.y, Dot(vec3, vec4))
    Fire::Vector<Fire::Real, 3> vec1_3 { 0, 2 };
    Fire::Vector<Fire::Real, 3> vec2_3 { 1, 3 };

    Fire::Scale<Fire::Real, 3> scale3 { 1, 2, 2 };
    // Cross(vec1, vec2);   // error
    auto vec3_3 = Cross(vec1_3, vec2_3) / scale3;
    auto vec4_3 = Cross(vec2_3, vec1_3);
    FIRE_WARN("{} {} {}", vec3_3.x, vec3_3.y, vec3_3.z)
    FIRE_WARN("{} {} {}", vec4_3.x, vec4_3.y, vec4_3.z)

    Fire::Point<Fire::Real, 3> point1 { 2, 1, 1 };
    Fire::Point<Fire::Real, 3> point2 { 2, 1, 1 };
    point1 *= scale3;
    FIRE_WARN("{} {} {}", point1.x, point1.y, point1.z)
    auto vector_pp = point1 - point2;
    FIRE_WARN("{} {} {}", vector_pp.x, vector_pp.y, vector_pp.z)
    auto point3 = point2 + vector_pp;
    FIRE_WARN("{} {} {}", point3.x, point3.y, point3.z)
    FIRE_WARN("{} {}", Fire::Sqrt(-1.f), Fire::SafeSqrt(-1.f))

    Fire::Matrix<Fire::Real, 3, 3> mat = Fire::Matrix<Fire::Real, 3, 3>::GenerateIdentity();
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

    Fire::Real c = 0.9;
    FIRE_WARN("{}", Fire::Sigmoid((c - 0.5) / std::sqrt(c * (1 - c))));

    auto sample_illum = Fire::SpectrumSample::FromSpectrumDistribution(Fire::g_cie_illuminant_D6500, wavelengths_sample);
    auto rgb = Fire::RGB::FromSpectrumSample(Fire::g_colorspace_sRGB, sample_illum);
    FIRE_INFO("{} {} {}", rgb.r, rgb.g, rgb.b);

    auto rgb_spectrum = Fire::RGBSigmoidPolynomialSD::FromRGB(Fire::g_colorspace_sRGB, { 0.7, 0.5, 0.8 });
    for (Fire::Int i = Fire::g_lambda_min; i <= Fire::g_lambda_max; i ++) {
        FIRE_INFO("{} ==> {}", i, rgb_spectrum.sample(i));
    }
    auto sample_rgb = Fire::SpectrumSample::FromSpectrumDistribution(rgb_spectrum, wavelengths_sample);
    auto rgb1 = Fire::RGB::FromSpectrumSample(Fire::g_colorspace_sRGB, sample_rgb);
    sample_rgb.value *= sample_illum.value;
    auto rgb2 = Fire::RGB::FromSpectrumSample(Fire::g_colorspace_sRGB, sample_rgb);
    FIRE_INFO("{} {} {}", rgb1.r, rgb1.g, rgb1.b);
    FIRE_INFO("{} {} {}", rgb2.r, rgb2.g, rgb2.b);

    FIRE_INFO("{} {} {}", Fire::Sin(Fire::RadianFromAngle(90)), Fire::Sin(Fire::RadianFromAngle(180)), Fire::Sin(Fire::RadianFromAngle(270)));

    auto film = Fire::Film::MakeFilm(1920, 1080);
    Fire::OrthographicCamera camera_o { film, 0.1, 10, Fire::RadianFromAngle(60) };
    auto ray_payload = camera_o.generateRay({ { 0.5, 0.55 }, { 0, 0 } });
    FIRE_INFO("{} {} {}", ray_payload->ray.origin.x, ray_payload->ray.origin.y, ray_payload->ray.origin.z)
    FIRE_INFO("{} {} {} {}", ray_payload->ray.direction.x, ray_payload->ray.direction.y, ray_payload->ray.direction.z, Length(ray_payload->ray.direction))
    Fire::PerspectiveCamera camera_p { film, 0.1, 10, Fire::RadianFromAngle(90) };
    ray_payload = camera_p.generateRay({ { 0.5, 1 }, { 0, 0 } });
    FIRE_INFO("{} {} {}", ray_payload->ray.origin.x, ray_payload->ray.origin.y, ray_payload->ray.origin.z)
    FIRE_INFO("{} {} {} {}", ray_payload->ray.direction.x, ray_payload->ray.direction.y, ray_payload->ray.direction.z, Length(ray_payload->ray.direction))

    Fire::ColorSpace::Destroy();
    Fire::Illuminants::Destroy();
    Fire::Logger::Destory();
    return 0;
}
