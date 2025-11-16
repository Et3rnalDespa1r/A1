#include <iostream>
#include <iomanip>
#include <cstdint>

double xr[3], yr[3], rr[3];

uint32_t seed_val = 123456789u;

inline double myrand() {
    seed_val = seed_val * 1103515245u + 12345u;
    return (seed_val >> 1) * (1.0 / 2147483648.0);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    for (int i = 0; i < 3; ++i) {
        if (!(std::cin >> xr[i] >> yr[i] >> rr[i])) {
            return 0;
        }
    }

    double minx = xr[0] - rr[0], maxx = xr[0] + rr[0];
    double miny = yr[0] - rr[0], maxy = yr[0] + rr[0];
    for (int i = 1; i < 3; ++i) {
        if (xr[i] - rr[i] < minx) minx = xr[i] - rr[i];
        if (xr[i] + rr[i] > maxx) maxx = xr[i] + rr[i];
        if (yr[i] - rr[i] < miny) miny = yr[i] - rr[i];
        if (yr[i] + rr[i] > maxy) maxy = yr[i] + rr[i];
    }

    double w = maxx - minx;
    double h = maxy - miny;

    if (w <= 0.0 || h <= 0.0) {
        std::cout.setf(std::ios::fixed);
        std::cout << std::setprecision(15) << 0.0;
        return 0;
    }

    const long long N = 3000000;
    long long inside = 0;

    for (long long i = 0; i < N; ++i) {
        double x = minx + w * myrand();
        double y = miny + h * myrand();
        bool ok = true;
        for (int j = 0; j < 3; ++j) {
            double dx = x - xr[j];
            double dy = y - yr[j];
            if (dx * dx + dy * dy > rr[j] * rr[j]) {
                ok = false;
                break;
            }
        }
        if (ok) ++inside;
    }

    double area_box = w * h;
    double ans = area_box * (double)inside / (double)N;

    std::cout.setf(std::ios::fixed);
    std::cout << std::setprecision(15) << ans;
    return 0;
}
