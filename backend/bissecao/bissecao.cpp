
#include "bissecao.h"
#include <cmath>

using namespace std;

Bissecao::Bissecao(
    function<double(double)> f,
    double tol,
    int max_iter) {
    v_f = f;
    v_tol = tol;
    v_max_iter = max_iter;
}

SolutionReport Bissecao::encontrar_raiz(double a, double b) const {
    double x_meio;
    int i = 0;

    while ((b - a) > v_tol && i < v_max_iter) {
        x_meio = a + (b - a) / 2.0;

        if (abs(v_f(x_meio)) == 0.0) {
            break;
        } else if (v_f(a) * v_f(x_meio) < 0) {
            b = x_meio;
        } else {
            a = x_meio;
        }
        i++;
    }

    if ((b - a) <= v_tol) {
        return {
            SolutionStatus::SUCCESS,
            a + (b - a) / 2.0,
            i,
            "Sucesso: A solução convergiu para a tolerância desejada."
        };
    } else {
        return {
            SolutionStatus::FAILURE_MAX_ITERATIONS_REACHED,
            nullopt,
            v_max_iter,
            "Falha: Número máximo de iterações foi atingido."
        };
    }
}

void Bissecao::setTol(double tol) {
    v_tol = tol;
}

void Bissecao::setMaxIter(int max_iter) {
    v_max_iter = max_iter;
}