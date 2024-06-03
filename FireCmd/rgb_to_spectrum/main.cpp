#define FIRE_USE_DOUBLE_AS_FLOAT

#include <Fire/spectrum/color/colorspace.hpp>
#include <Fire/spectrum/color/rgb_to_spectrum.hpp>
#include <Fire/core/thread/thread_pool.hpp>
#include <Fire/core/thread/parallel_for.hpp>
#include <Fire/core/logger.hpp>

using namespace Fire;

Fire::ThreadPool *g_thread_pool;
static constexpr SizeT gauss_newton_iteration_step = 25;
static constexpr int cie_sample_count_highp = 95;
static constexpr int resolution = g_rgb_to_spectrum_table_resolution;
static constexpr int cie_fine_sample_count  = (cie_sample_count_highp - 1) * 3 + 1;
static constexpr double rgb_to_spectrum_epsilon =  1e-4;

static constexpr double cie_x[cie_sample_count_highp] = {
    0.000129900000, 0.000232100000, 0.000414900000, 0.000741600000, 0.001368000000,
    0.002236000000, 0.004243000000, 0.007650000000, 0.014310000000, 0.023190000000,
    0.043510000000, 0.077630000000, 0.134380000000, 0.214770000000, 0.283900000000,
    0.328500000000, 0.348280000000, 0.348060000000, 0.336200000000, 0.318700000000,
    0.290800000000, 0.251100000000, 0.195360000000, 0.142100000000, 0.095640000000,
    0.057950010000, 0.032010000000, 0.014700000000, 0.004900000000, 0.002400000000,
    0.009300000000, 0.029100000000, 0.063270000000, 0.109600000000, 0.165500000000,
    0.225749900000, 0.290400000000, 0.359700000000, 0.433449900000, 0.512050100000,
    0.594500000000, 0.678400000000, 0.762100000000, 0.842500000000, 0.916300000000,
    0.978600000000, 1.026300000000, 1.056700000000, 1.062200000000, 1.045600000000,
    1.002600000000, 0.938400000000, 0.854449900000, 0.751400000000, 0.642400000000,
    0.541900000000, 0.447900000000, 0.360800000000, 0.283500000000, 0.218700000000,
    0.164900000000, 0.121200000000, 0.087400000000, 0.063600000000, 0.046770000000,
    0.032900000000, 0.022700000000, 0.015840000000, 0.011359160000, 0.008110916000,
    0.005790346000, 0.004109457000, 0.002899327000, 0.002049190000, 0.001439971000,
    0.000999949300, 0.000690078600, 0.000476021300, 0.000332301100, 0.000234826100,
    0.000166150500, 0.000117413000, 0.000083075270, 0.000058706520, 0.000041509940,
    0.000029353260, 0.000020673830, 0.000014559770, 0.000010253980, 0.000007221456,
    0.000005085868, 0.000003581652, 0.000002522525, 0.000001776509, 0.000001251141
};

static constexpr double cie_y[cie_sample_count_highp] = {
    0.000003917000, 0.000006965000, 0.000012390000, 0.000022020000, 0.000039000000,
    0.000064000000, 0.000120000000, 0.000217000000, 0.000396000000, 0.000640000000,
    0.001210000000, 0.002180000000, 0.004000000000, 0.007300000000, 0.011600000000,
    0.016840000000, 0.023000000000, 0.029800000000, 0.038000000000, 0.048000000000,
    0.060000000000, 0.073900000000, 0.090980000000, 0.112600000000, 0.139020000000,
    0.169300000000, 0.208020000000, 0.258600000000, 0.323000000000, 0.407300000000,
    0.503000000000, 0.608200000000, 0.710000000000, 0.793200000000, 0.862000000000,
    0.914850100000, 0.954000000000, 0.980300000000, 0.994950100000, 1.000000000000,
    0.995000000000, 0.978600000000, 0.952000000000, 0.915400000000, 0.870000000000,
    0.816300000000, 0.757000000000, 0.694900000000, 0.631000000000, 0.566800000000,
    0.503000000000, 0.441200000000, 0.381000000000, 0.321000000000, 0.265000000000,
    0.217000000000, 0.175000000000, 0.138200000000, 0.107000000000, 0.081600000000,
    0.061000000000, 0.044580000000, 0.032000000000, 0.023200000000, 0.017000000000,
    0.011920000000, 0.008210000000, 0.005723000000, 0.004102000000, 0.002929000000,
    0.002091000000, 0.001484000000, 0.001047000000, 0.000740000000, 0.000520000000,
    0.000361100000, 0.000249200000, 0.000171900000, 0.000120000000, 0.000084800000,
    0.000060000000, 0.000042400000, 0.000030000000, 0.000021200000, 0.000014990000,
    0.000010600000, 0.000007465700, 0.000005257800, 0.000003702900, 0.000002607800,
    0.000001836600, 0.000001293400, 0.000000910930, 0.000000641530, 0.000000451810
};

static constexpr double cie_z[cie_sample_count_highp] = {
    0.000606100000, 0.001086000000, 0.001946000000, 0.003486000000, 0.006450001000,
    0.010549990000, 0.020050010000, 0.036210000000, 0.067850010000, 0.110200000000,
    0.207400000000, 0.371300000000, 0.645600000000, 1.039050100000, 1.385600000000,
    1.622960000000, 1.747060000000, 1.782600000000, 1.772110000000, 1.744100000000,
    1.669200000000, 1.528100000000, 1.287640000000, 1.041900000000, 0.812950100000,
    0.616200000000, 0.465180000000, 0.353300000000, 0.272000000000, 0.212300000000,
    0.158200000000, 0.111700000000, 0.078249990000, 0.057250010000, 0.042160000000,
    0.029840000000, 0.020300000000, 0.013400000000, 0.008749999000, 0.005749999000,
    0.003900000000, 0.002749999000, 0.002100000000, 0.001800000000, 0.001650001000,
    0.001400000000, 0.001100000000, 0.001000000000, 0.000800000000, 0.000600000000,
    0.000340000000, 0.000240000000, 0.000190000000, 0.000100000000, 0.000049999990,
    0.000030000000, 0.000020000000, 0.000010000000, 0.000000000000, 0.000000000000,
    0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000,
    0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000,
    0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000,
    0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000,
    0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000,
    0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000,
    0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000
};

#define N(x) (x / 10566.864005283874576)
static constexpr double cie_d65[cie_sample_count_highp] = {
    N(46.6383), N(49.3637), N(52.0891), N(51.0323), N(49.9755), N(52.3118), N(54.6482),
    N(68.7015), N(82.7549), N(87.1204), N(91.486),  N(92.4589), N(93.4318), N(90.057),
    N(86.6823), N(95.7736), N(104.865), N(110.936), N(117.008), N(117.41),  N(117.812),
    N(116.336), N(114.861), N(115.392), N(115.923), N(112.367), N(108.811), N(109.082),
    N(109.354), N(108.578), N(107.802), N(106.296), N(104.79),  N(106.239), N(107.689),
    N(106.047), N(104.405), N(104.225), N(104.046), N(102.023), N(100.0),   N(98.1671),
    N(96.3342), N(96.0611), N(95.788),  N(92.2368), N(88.6856), N(89.3459), N(90.0062),
    N(89.8026), N(89.5991), N(88.6489), N(87.6987), N(85.4936), N(83.2886), N(83.4939),
    N(83.6992), N(81.863),  N(80.0268), N(80.1207), N(80.2146), N(81.2462), N(82.2778),
    N(80.281),  N(78.2842), N(74.0027), N(69.7213), N(70.6652), N(71.6091), N(72.979),
    N(74.349),  N(67.9765), N(61.604),  N(65.7448), N(69.8856), N(72.4863), N(75.087),
    N(69.3398), N(63.5927), N(55.0054), N(46.4182), N(56.6118), N(66.8054), N(65.0941),
    N(63.3828), N(63.8434), N(64.304),  N(61.8779), N(59.4519), N(55.7054), N(51.959),
    N(54.6998), N(57.4406), N(58.8765), N(60.3125)
};
#undef N

#define N(x) (x / 10536.3)
static constexpr double cie_d60[cie_sample_count_highp] = {
    N(38.683115),  N(41.014457),  N(42.717548),  N(42.264182),  N(41.454941),
    N(41.763698),  N(46.605319),  N(59.226938),  N(72.278594),  N(78.231500),
    N(80.440600),  N(82.739580),  N(82.915027),  N(79.009168),  N(77.676264),
    N(85.163609),  N(95.681274),  N(103.267764), N(107.954821), N(109.777964),
    N(109.559187), N(108.418402), N(107.758141), N(109.071548), N(109.671404),
    N(106.734741), N(103.707873), N(103.981942), N(105.232199), N(105.235867),
    N(104.427667), N(103.052881), N(102.522934), N(104.371416), N(106.052671),
    N(104.948900), N(103.315154), N(103.416286), N(103.538599), N(102.099304),
    N(100.000000), N(97.992725),  N(96.751421),  N(97.102402),  N(96.712823),
    N(93.174457),  N(89.921479),  N(90.351933),  N(91.999793),  N(92.384009),
    N(92.098710),  N(91.722859),  N(90.646003),  N(88.327552),  N(86.526483),
    N(87.034239),  N(87.579186),  N(85.884584),  N(83.976140),  N(83.743140),
    N(84.724074),  N(86.450818),  N(87.493491),  N(86.546330),  N(83.483070),
    N(78.268785),  N(74.172451),  N(74.275184),  N(76.620385),  N(79.423856),
    N(79.051849),  N(71.763360),  N(65.471371),  N(67.984085),  N(74.106079),
    N(78.556612),  N(79.527120),  N(75.584935),  N(67.307163),  N(55.275106),
    N(49.273538),  N(59.008629),  N(70.892412),  N(70.950115),  N(67.163996),
    N(67.445480),  N(68.171371),  N(66.466636),  N(62.989809),  N(58.067786),
    N(54.990892),  N(56.915942),  N(60.825601),  N(62.987850)
};
#undef N

static constexpr double xyz_to_srgb[3][3] = {
    { 3.240479, -1.537150, -0.498535 },
    { -0.969256, 1.875991, 0.041556 },
    { 0.055648, -0.204043, 1.057311 },
};

static constexpr double srgb_to_xyz[3][3] = {
    { 0.412453, 0.357580, 0.180423 },
    { 0.212671, 0.715160, 0.072169 },
    { 0.019334, 0.119193, 0.950227 }
};

static constexpr double xyz_to_dcip3[3][3] = {
    { 2.4931748, -0.93126315, -0.40265882 },
    { -0.82950425, 1.7626965, 0.023625137 },
    { 0.035853732, -0.07618918, 0.9570952 }
};

static constexpr double dcip3_to_xyz[3][3] = {
    { 0.48663378, 0.26566276, 0.19817366 },
    { 0.22900413, 0.69172573, 0.079269454 },
    { 0., 0.04511256, 1.0437145 }
};

static constexpr double xyz_to_rec2020[3][3] = {
    { 1.7166511880, -0.3556707838, -0.2533662814 },
    { -0.6666843518, 1.6164812366, 0.0157685458 },
    { 0.0176398574, -0.0427706133, 0.9421031212 }
};

static constexpr double rec2020_to_xyz[3][3] = {
    { 0.6369580483, 0.1446169036, 0.1688809752 },
    { 0.2627002120, 0.6779980715, 0.0593017165 },
    { 0.0000000000, 0.0280726930, 1.0609850577 }
};

static constexpr double xyz_to_aces2065_1[3][3] = {
    { 1.0498110175, 0.0000000000, -0.0000974845 },
    { -0.4959030231, 1.3733130458, 0.0982400361 },
    { 0.0000000000, 0.0000000000, 0.9912520182 }
};

static constexpr double aces2065_1_to_xyz[3][3] = {
    { 0.9525523959, 0.0000000000, 0.0000936786 },
    { 0.3439664498, 0.7281660966, -0.0721325464 },
    { 0.0000000000, 0.0000000000, 1.0088251844 }
};

double cie_interp(const double *data, double x) {
    x -= g_lambda_min;
    x *= double(cie_sample_count_highp - 1) / (g_lambda_max - g_lambda_min);
    int offset = (int)x;
    if (offset < 0)
        offset = 0;
    if (offset > cie_sample_count_highp - 2)
        offset = cie_sample_count_highp - 2;
    double weight = x - offset;
    return (1.0 - weight) * data[offset] + weight * data[offset + 1];
}

double sigmoid(double x) {
    return 0.5 * x / std::sqrt(1.0 + x * x) + 0.5;
}

double smoothstep(double x) {
    return x * x * (3.0 - 2.0 * x);
}

double sqr(double x) {
    return x * x;
}

// LU decomposition & triangular solving code lifted from Wikipedia

/* INPUT: A - array of pointers to rows of a square matrix having dimension N
*        Tol - small tolerance number to detect failure when the matrix is near
* degenerate OUTPUT: Matrix A is changed, it contains both matrices L-E and U
* as A=(L-E)+U such that P*A=L*U. The permutation matrix is not stored as a
* matrix, but in an integer vector P of size N+1 containing column indexes
* where the permutation matrix has "1". The last element P[N]=S+N, where S is
* the number of row exchanges needed for determinant computation, det(P)=(-1)^S
*/
int LUPDecompose(double **A, int N, double Tol, int *P) {
    int i, j, k, imax;
    double maxA, *ptr, absA;

    for (i = 0; i <= N; i++)
        P[i] = i;  // Unit permutation matrix, P[N] initialized with N

    for (i = 0; i < N; i++) {
        maxA = 0.0;
        imax = i;

        for (k = i; k < N; k++)
            if ((absA = fabs(A[k][i])) > maxA) {
                maxA = absA;
                imax = k;
            }

        if (maxA < Tol)
            return 0;  // failure, matrix is degenerate

        if (imax != i) {
            // pivoting P
            j = P[i];
            P[i] = P[imax];
            P[imax] = j;

            // pivoting rows of A
            ptr = A[i];
            A[i] = A[imax];
            A[imax] = ptr;

            // counting pivots starting from N (for determinant)
            P[N]++;
        }

        for (j = i + 1; j < N; j++) {
            A[j][i] /= A[i][i];

            for (k = i + 1; k < N; k++)
                A[j][k] -= A[j][i] * A[i][k];
        }
    }

    return 1;  // decomposition done
}

/* INPUT: A,P filled in LUPDecompose; b - rhs vector; N - dimension
* OUTPUT: x - solution vector of A*x=b
*/
void LUPSolve(double **const A, const int *P, const double *b, int N, double *x) {
    for (int i = 0; i < N; i++) {
        x[i] = b[P[i]];

        for (int k = 0; k < i; k++)
            x[i] -= A[i][k] * x[k];
    }

    for (int i = N - 1; i >= 0; i--) {
        for (int k = i + 1; k < N; k++)
            x[i] -= A[i][k] * x[k];

        x[i] = x[i] / A[i][i];
    }
}

struct TableData {
    static const constexpr int buffer_size = 3 * resolution * resolution * resolution * 3;

    double lambda_table[cie_fine_sample_count];
    double rgb_table[3][cie_fine_sample_count];
    double xyz_whitepoint[3];
    double rgb_to_xyz[3][3];
    double xyz_to_rgb[3][3];
    const double *illuminant;
    double coefficients_buffer[buffer_size];
    ZNodeArray<double> z_nodes;
    CoefficientArray<double> coefficients;
};

enum class RGBColorSpaceType {
    esRGB,
    eDCI_P3,
    eRec2020,
    eACES2065_1,
};

std::string to_string(RGBColorSpaceType colorspace) {
    switch (colorspace) {
    case RGBColorSpaceType::esRGB:
        return "sRGB";
    case RGBColorSpaceType::eDCI_P3:
        return "DCI_P3";
    case RGBColorSpaceType::eRec2020:
        return "Rec2020";
    case RGBColorSpaceType::eACES2065_1:
        return "ACES2065_1";
    }
}

void cie_lab(double *p, TableData *data) {
    double X = 0.0, Y = 0.0, Z = 0.0, Xw = data->xyz_whitepoint[0], Yw = data->xyz_whitepoint[1],
        Zw = data->xyz_whitepoint[2];

    for (int j = 0; j < 3; ++j) {
        X += p[j] * data->rgb_to_xyz[0][j];
        Y += p[j] * data->rgb_to_xyz[1][j];
        Z += p[j] * data->rgb_to_xyz[2][j];
    }

    auto f = [](double t) -> double {
        double delta = 6.0 / 29.0;
        if (t > delta * delta * delta)
            return cbrt(t);
        else
            return t / (delta * delta * 3.0) + (4.0 / 29.0);
    };

    p[0] = 116.0 * f(Y / Yw) - 16.0;
    p[1] = 500.0 * (f(X / Xw) - f(Y / Yw));
    p[2] = 200.0 * (f(Y / Yw) - f(Z / Zw));
}

void eval_residual(const double *coeffs, const double *rgb, double *residual, TableData *data) {
    double out[3] = {0.0, 0.0, 0.0};

    for (int i = 0; i < cie_fine_sample_count; ++i) {
        /* Scale lambda to 0..1 range */
        double lambda =
            (data->lambda_table[i] - g_lambda_min) / (g_lambda_max - g_lambda_min);

        /* Polynomial */
        double x = 0.0;
        for (int i = 0; i < 3; ++i)
            x = x * lambda + coeffs[i];

        /* Sigmoid */
        double s = sigmoid(x);

        /* Integrate against precomputed curves */
        for (int j = 0; j < 3; ++j)
            out[j] += data->rgb_table[j][i] * s;
    }
    cie_lab(out, data);
    memcpy(residual, rgb, sizeof(double) * 3);
    cie_lab(residual, data);

    for (int j = 0; j < 3; ++j)
        residual[j] -= out[j];
}

void eval_jacobian(const double *coeffs, const double *rgb, double **jac, TableData *data) {
    double r0[3], r1[3], tmp[3];

    for (int i = 0; i < 3; ++i) {
        memcpy(tmp, coeffs, sizeof(double) * 3);
        tmp[i] -= rgb_to_spectrum_epsilon;
        eval_residual(tmp, rgb, r0, data);

        memcpy(tmp, coeffs, sizeof(double) * 3);
        tmp[i] += rgb_to_spectrum_epsilon;
        eval_residual(tmp, rgb, r1, data);

        for (int j = 0; j < 3; ++j)
            jac[j][i] = (r1[j] - r0[j]) * 1.0 / (2 * rgb_to_spectrum_epsilon);
    }
}

void gauss_newton(const double rgb[3], double coeffs[3], TableData *data, int it) {
    double r = 0;
    for (size_t i = 0; i < it; i++) {
        double J0[3], J1[3], J2[3], *J[3] = {J0, J1, J2};

        double residual[3];

        eval_residual(coeffs, rgb, residual, data);
        eval_jacobian(coeffs, rgb, J, data);

        int P[4];
        int rv = LUPDecompose(J, 3, 1e-15, P);
        if (rv != 1) {
            FIRE_ERROR("RGB {} {} {}", rgb[0], rgb[1], rgb[2])
            FIRE_ERROR("-> {} {} {}", coeffs[0], coeffs[1], coeffs[2])
            throw std::runtime_error("LU decomposition failed!");
        }

        double x[3];
        LUPSolve(J, P, residual, 3, x);

        r = 0.0;
        for (int j = 0; j < 3; ++j) {
            coeffs[j] -= x[j];
            r += residual[j] * residual[j];
        }
        double max = std::max(std::max(coeffs[0], coeffs[1]), coeffs[2]);

        if (max > 200) {
            for (int j = 0; j < 3; ++j)
                coeffs[j] *= 200 / max;
        }

        if (r < 1e-6)
            break;
    }
}

static TableData *ComputeColorapce(RGBColorSpaceType colorspace, int it) {
    auto *data = new TableData {};

    switch (colorspace) {
    case RGBColorSpaceType::esRGB:
        data->illuminant = cie_d65;
        memcpy(data->xyz_to_rgb, xyz_to_srgb, sizeof(double) * 9);
        memcpy(data->rgb_to_xyz, srgb_to_xyz, sizeof(double) * 9);
        break;
    case RGBColorSpaceType::eDCI_P3:
        data->illuminant = cie_d65;
        memcpy(data->xyz_to_rgb, xyz_to_dcip3, sizeof(double) * 9);
        memcpy(data->rgb_to_xyz, dcip3_to_xyz, sizeof(double) * 9);
        break;
    case RGBColorSpaceType::eRec2020:
        data->illuminant = cie_d65;
        memcpy(data->xyz_to_rgb, xyz_to_rec2020, sizeof(double) * 9);
        memcpy(data->rgb_to_xyz, rec2020_to_xyz, sizeof(double) * 9);
        break;
    case RGBColorSpaceType::eACES2065_1:
        data->illuminant = cie_d60;
        memcpy(data->xyz_to_rgb, xyz_to_aces2065_1, sizeof(double) * 9);
        memcpy(data->rgb_to_xyz, aces2065_1_to_xyz, sizeof(double) * 9);
        break;
    }

    double h = double(g_lambda_max - g_lambda_min) / double(cie_fine_sample_count - 1);

    for (int i = 0; i < cie_fine_sample_count; ++i) {
        double lambda = g_lambda_min + i * h;

        double xyz[3] = {
            cie_interp(cie_x, lambda),
            cie_interp(cie_y, lambda),
            cie_interp(cie_z, lambda)
        };
        double I = cie_interp(data->illuminant, lambda);

        double weight = 3.0 / 8.0 * h;
        if (i == 0 || i == cie_fine_sample_count - 1) {
        } else if ((i - 1) % 3 == 2) {
            weight *= 2.f;
        } else {
            weight *= 3.f;
        }

        data->lambda_table[i] = lambda;
        for (size_t k = 0; k < 3; k ++) {
            for (size_t j = 0; j < 3; j ++) {
                data->rgb_table[k][i] += data->xyz_to_rgb[k][j] * xyz[j] * I * weight;
            }
        }

        for (size_t i = 0; i < 3; i ++) {
            data->xyz_whitepoint[i] += xyz[i] * I * weight;
        }
    }

    for (int k = 0; k < resolution; ++k) {
        data->z_nodes[k] = (float)smoothstep(smoothstep(k / double(resolution - 1)));
    }

    for (size_t l = 0; l < 3; l ++) {
        auto task = ParallelFor(*g_thread_pool, 0, resolution, [&](size_t j) {
            FIRE_INFO("ColorSpace: {} L: {} J: {}", to_string(colorspace), l, j)
            const double y = double(j) / double(resolution - 1);
            for (size_t i = 0; i < resolution; i ++) {
                const double x = i / double(resolution - 1);
                double coeffs[3], rgb[3];
                memset(coeffs, 0, sizeof(double) * 3);

                int start = resolution / 5;

                for (size_t k = start; k < resolution; k ++) {
                    double b = data->z_nodes[k];

                    rgb[l] = b;
                    rgb[(l + 1) % 3] = x * b;
                    rgb[(l + 2) % 3] = y * b;

                    gauss_newton(rgb, coeffs, data, it);

                    double c0 = 360.0, c1 = 1.0 / (830.0 - 360.0);
                    double A = coeffs[0], B = coeffs[1], C = coeffs[2];

                    int idx = ((l * resolution + k) * resolution + j) * resolution + i;

                    data->coefficients_buffer[3 * idx + 0] = double(A * (sqr(c1)));
                    data->coefficients_buffer[3 * idx + 1] = double(B * c1 - 2 * A * c0 * (sqr(c1)));
                    data->coefficients_buffer[3 * idx + 2] = double(C - B * c0 * c1 + A * (sqr(c0 * c1)));
                }

                memset(coeffs, 0, sizeof(double) * 3);
                for (int k = start; k >= 0; -- k) {
                    double b = data->z_nodes[k];

                    rgb[l] = b;
                    rgb[(l + 1) % 3] = x * b;
                    rgb[(l + 2) % 3] = y * b;

                    gauss_newton(rgb, coeffs, data, it);

                    double c0 = 360.0, c1 = 1.0 / (830.0 - 360.0);
                    double A = coeffs[0], B = coeffs[1], C = coeffs[2];

                    int idx = ((l * resolution + k) * resolution + j) * resolution + i;

                    data->coefficients_buffer[3 * idx + 0] = double(A * (sqr(c1)));
                    data->coefficients_buffer[3 * idx + 1] = double(B * c1 - 2 * A * c0 * (sqr(c1)));
                    data->coefficients_buffer[3 * idx + 2] = double(C - B * c0 * c1 + A * (sqr(c0 * c1)));
                }
            }
        });
        task->wait();
        delete task;
    }

    const double *ptr = data->coefficients_buffer;
    for (size_t maxc = 0; maxc < 3; maxc ++) {
        for (size_t z = 0; z < resolution; z ++) {
            for (size_t y = 0; y < resolution; y ++) {
                for (size_t x = 0; x < resolution; x ++) {
                    for (size_t c = 0; c < 3; c ++) {
                        data->coefficients[maxc][z][y][x][c] = *ptr;
                        ptr ++;
                    }
                }
            }
        }
    }
    return data;
}

static void WriteToFile(RGBColorSpaceType colorspace, const TableData *data, bool minimal = true) {
    std::string filename = std::string("rgb_to_spectrum_table_") + to_string(colorspace) + std::string(".cpp");
    FILE *f;
    fopen_s(&f, filename.c_str(), "w");
    if (f == nullptr) {
        throw std::runtime_error("Could not create file!");
    }

    std::stringstream ss;
    ss << "g_precompute_table_" << to_string(colorspace);
    auto table_name = ss.str();

    fprintf(f, "#include \"spectrum/color/rgb_to_spectrum.hpp\"\n");
    if (!minimal) {
        fprintf(f, "\nnamespace Fire {\n");
        fprintf(f, "    RGBToSpectrumTable<Real> %s {\n", table_name.c_str());
        fprintf(f, "        {\n");
        for (size_t i = 0; i < resolution; i ++) {
            fprintf(f, "            Real(%.9g),\n", data->z_nodes[i]);
        }
        fprintf(f, "        },\n");
        fprintf(f, "        {\n");
    } else {
        fprintf(f, "namespace Fire{");
        fprintf(f, "RGBToSpectrumTable<Real>%s{{", table_name.c_str());
        for (size_t i = 0; i < resolution; i ++) {
            fprintf(f, "Real(%.9g),", data->z_nodes[i]);
        }
        fprintf(f, "},{");
    }
    const double *ptr = data->coefficients_buffer;
    if (!minimal) {
        for (size_t maxc = 0; maxc < 3; maxc ++) {
            fprintf(f, "            {\n");
            for (size_t z = 0; z < resolution; z ++) {
                fprintf(f, "                {\n");
                for (size_t y = 0; y < resolution; y ++) {
                    fprintf(f, "                    {\n");
                    for (size_t x = 0; x < resolution; x ++) {
                        fprintf(f, "                        { ");
                        for (size_t c = 0; c < 3; c ++) {
                            fprintf(f, "Real(%.9g), ", *ptr);
                            ptr ++;
                        }
                        fprintf(f, "},\n");
                    }
                    fprintf(f, "                        },\n");
                }
                fprintf(f, "                },\n");
            }
            fprintf(f, "            },\n");
        }
        fprintf(f, "        }\n\n");
        fprintf(f, "    };\n\n");
        fprintf(f, "}\n");
    } else {
        for (size_t maxc = 0; maxc < 3; maxc ++) {
            fprintf(f, "{");
            for (size_t z = 0; z < resolution; z ++) {
                fprintf(f, "{");
                for (size_t y = 0; y < resolution; y ++) {
                    fprintf(f, "{");
                    for (size_t x = 0; x < resolution; x ++) {
                        fprintf(f, "{");
                        for (size_t c = 0; c < 3; c ++) {
                            fprintf(f, "Real(%.9g),", *ptr);
                            ptr ++;
                        }
                        fprintf(f, "},");
                    }
                    fprintf(f, "},");
                }
                fprintf(f, "},");
            }
            fprintf(f, "},");
        }
        fprintf(f, "}");
        fprintf(f, "};");
        fprintf(f, "}");
    }
    fclose(f);
}

int main() {
    Logger::Initialize();

    Int core_count = std::thread::hardware_concurrency();
    g_thread_pool = new ThreadPool(core_count * 1.5);
    FIRE_INFO("Active {} Threads on {} Cores", g_thread_pool->getThreadCount(), core_count);

    auto *sRGB_data = ComputeColorapce(RGBColorSpaceType::esRGB, gauss_newton_iteration_step);
    WriteToFile(RGBColorSpaceType::esRGB, sRGB_data);
    delete sRGB_data;

    auto *DCI_P3_data = ComputeColorapce(RGBColorSpaceType::eDCI_P3, gauss_newton_iteration_step);
    WriteToFile(RGBColorSpaceType::eDCI_P3, DCI_P3_data);
    delete DCI_P3_data;

    auto *Rec2020_data = ComputeColorapce(RGBColorSpaceType::eRec2020, gauss_newton_iteration_step);
    WriteToFile(RGBColorSpaceType::eRec2020, Rec2020_data);
    delete Rec2020_data;

    auto *ACES2065_1_data = ComputeColorapce(RGBColorSpaceType::eACES2065_1, gauss_newton_iteration_step);
    WriteToFile(RGBColorSpaceType::eACES2065_1, ACES2065_1_data);
    delete ACES2065_1_data;

    Logger::Destory();
}

namespace Fire {
    Fire::RGBToSpectrumTable<Real> g_precompute_table_sRGB;
    Fire::RGBToSpectrumTable<Real> g_precompute_table_DCI_P3;
    Fire::RGBToSpectrumTable<Real> g_precompute_table_Rec2020;
    Fire::RGBToSpectrumTable<Real> g_precompute_table_ACES2065_1;
}
