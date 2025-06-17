
#include "newton_raphson.h"
#include <cmath>
#include <limits>
#include <optional>

using namespace std;

NewtonRaphson::NewtonRaphson(
    function<double(double)> f,
    function<double(double)> df,
    double tol,
    int max_iter) {
    v_f = f;
    v_df = df;
    v_tol = tol;
    v_max_iter = max_iter;
}

SolutionReport NewtonRaphson::solucao(double chute_inicial) const {
    double x0 = chute_inicial;
    double x1 = 0.0;
    double e = v_tol+1;
    int i = 0;
    
    while(e > v_tol && i < v_max_iter){
        double valor_df = v_df(x0);

        if (abs(valor_df) < numeric_limits<double>::epsilon()) {
            return {
                SolutionStatus::FAILURE_DERIVATIVE_ZERO,
                nullopt,
                i,
                "Falha: A derivada se aproximou de zero."
            };
        }

        x1 = x0 - (v_f(x0) / valor_df);

        e = abs(x1 - x0);
        x0 = x1;
        i++;
    }

    if (e <= v_tol) {
        return {
                SolutionStatus::SUCCESS,
                x1,
                i + 1,
                "Sucesso: A solução convergiu para a tolerância desejada."
            };
    } else {
        return {
            SolutionStatus::FAILURE_MAX_ITERATIONS_REACHED,
            std::nullopt,
            v_max_iter,
            "Falha: Número máximo de iterações foi atingido."
        };
    }
}

void NewtonRaphson::setTol(double tol) {
    v_tol = tol;
}

void NewtonRaphson::setMaxIter(int max_iter) {
    v_max_iter = max_iter;
}
