
#include "posicao_falsa.h"
#include <cmath>
#include <limits>

using namespace std;

PosicaoFalsa::PosicaoFalsa(
    function<double(double)> f,
    double tol,
    int max_iter) {
    v_f = f;
    v_tol = tol;
    v_max_iter = max_iter;
}

SolutionReport PosicaoFalsa::encontrar_raiz(double a, double b) const {
    double fa = v_f(a);
    double fb = v_f(b);
    double x = 0.0;
    int i = 0;

    while (i < v_max_iter) {
        double denominador = fb - fa;
        if (abs(denominador) < numeric_limits<double>::epsilon()) {
             return {
                SolutionStatus::FAILURE_STAGNATION,
                nullopt,
                i,
                "Falha: O método estagnou (f(b) - f(a) próximo de zero)."
            };
        }

        x = (a * fb - b * fa) / denominador;
        double fx = v_f(x);

        if (abs(fx) < v_tol) {
            return {
                SolutionStatus::SUCCESS,
                x,
                i + 1,
                "Sucesso: A função no ponto da raiz aproximada atingiu a tolerância."
            };
        }

        if (fa * fx < 0) {
            b = x;
            fb = fx;
        } else {
            a = x;
            fa = fx;
        }
        
        i++;
    }

    return {
        SolutionStatus::FAILURE_MAX_ITERATIONS_REACHED,
        nullopt,
        v_max_iter,
        "Falha: Número máximo de iterações foi atingido."
    };
}

void PosicaoFalsa::setTol(double tol) {
    v_tol = tol;
}

void PosicaoFalsa::setMaxIter(int max_iter) {
    v_max_iter = max_iter;
}