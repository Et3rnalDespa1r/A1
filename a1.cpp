#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdint>
#include <algorithm>

struct Circle {
    double x, y, r;
};

uint32_t seed_val = 123456789u;

inline double myrand() {
    seed_val = seed_val * 1103515245u + 12345u;
    return (seed_val >> 1) * (1.0 / 2147483648.0);
}

double mc_area(const Circle c[3],
               double minx, double maxx,
               double miny, double maxy,
               long long N)
{
    double w = maxx - minx;
    double h = maxy - miny;
    if (w <= 0.0 || h <= 0.0) return 0.0;

    long long inside = 0;
    for (long long i = 0; i < N; ++i) {
        double x = minx + w * myrand();
        double y = miny + h * myrand();
        bool ok = true;
        for (int j = 0; j < 3; ++j) {
            double dx = x - c[j].x;
            double dy = y - c[j].y;
            if (dx * dx + dy * dy > c[j].r * c[j].r) {
                ok = false;
                break;
            }
        }
        if (ok) ++inside;
    }
    return (w * h) * (double)inside / (double)N;
}

int main() {
    Circle c[3];
    c[0] = {1.0, 1.0, 1.0};
    c[1] = {1.5, 2.0, std::sqrt(5.0) / 2.0};
    c[2] = {2.0, 1.5, std::sqrt(5.0) / 2.0};

    const double PI = 3.14159265358979323846;
    const double S_exact = 0.25 * PI + 1.25 * std::asin(0.8) - 1.0;

    double wide_minx = c[0].x - c[0].r;
    double wide_maxx = c[0].x + c[0].r;
    double wide_miny = c[0].y - c[0].r;
    double wide_maxy = c[0].y + c[0].r;
    for (int i = 1; i < 3; ++i) {
        wide_minx = std::min(wide_minx, c[i].x - c[i].r);
        wide_maxx = std::max(wide_maxx, c[i].x + c[i].r);
        wide_miny = std::min(wide_miny, c[i].y - c[i].r);
        wide_maxy = std::max(wide_maxy, c[i].y + c[i].r);
    }

    double narrow_minx = 1.0, narrow_maxx = 2.0;
    double narrow_miny = 1.0, narrow_maxy = 2.0;

    std::ofstream out("results.csv");
    out << "тип_прямоугольника,N,площадь,абсолютная_ошибка,относительная_ошибка\n";

    for (long long N = 100; N <= 100000; N += 500) {
        double Sw = mc_area(c, wide_minx, wide_maxx, wide_miny, wide_maxy, N);
        double abs_err_w = std::fabs(Sw - S_exact);
        double rel_err_w = abs_err_w / S_exact;
        out << "широкий," << N << "," << Sw << ","
            << abs_err_w << "," << rel_err_w << "\n";

        double Sn = mc_area(c, narrow_minx, narrow_maxx, narrow_miny, narrow_maxy, N);
        double abs_err_n = std::fabs(Sn - S_exact);
        double rel_err_n = abs_err_n / S_exact;
        out << "узкий," << N << "," << Sn << ","
            << abs_err_n << "," << rel_err_n << "\n";
    }

    std::cerr << "Готово. Данные записаны в results.csv\n";
    return 0;
}
