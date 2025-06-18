#include "encontrar_intervalo.h"
#include <cmath>

using namespace std;

pair<double, double> encontrar_intervalo(const function<double(double)>& func) {
    double x0 = 1.0;
    double passo = 0.5;
    int max_passos = 100;

    double f_x0 = func(x0);
    if (isnan(f_x0)) return {NAN, NAN};

    double x1 = x0;
    for (int i = 0; i < max_passos; ++i) {
        x1 += passo;
        double f_x1 = func(x1);
        if (isnan(f_x1)) continue;

        if (f_x0 * f_x1 < 0) {
            x0 = x1-passo;
            return {x0, x1};
        }
    }

    x1 = x0;
    passo *= -1;
     for (int i = 0; i < max_passos; ++i) {
        x1 += passo;
        if (x1 <= 0) continue;
        
        double f_x1 = func(x1);
        if (isnan(f_x1)) continue;

        if (f_x0 * f_x1 < 0) {
            x0 = x1 + (-passo);
            return {x1, x0};
        }
    }

    return {NAN, NAN};
}