
#include "newton_raphson.h"
#include <cmath>
#include <limits>
#include <optional>

using namespace std;

NewtonRaphson::NewtonRaphson(
    function<double(double)> f,
    function<double(double)> df,
    function<double(double)> ddf,
    double tol,
    int max_iter) {
    v_f = f;
    v_df = df;
    v_ddf = ddf;
    v_tol = tol;
    v_max_iter = max_iter;
}

bool NewtonRaphson::verificarContinuidade(
    const function<double(double)>& func,
    double ini,
    double fim) const {
    
    const int qtd_passos = 1000;
    const double salto_lim = 1e6;
    
    double passo = (fim - ini) / qtd_passos;

    double y_ini = func(ini); 

    if (!isfinite(y_ini)) {
        return false;
    }

    for (int i = 1; i <= qtd_passos; ++i) {
        double x = ini + i * passo;
        double y_prox = func(x);

        if (!isfinite(y_prox)) {
            return false;
        }

        if (abs(y_prox - y_ini) > salto_lim) {
            return false;
        }
        
        y_ini = y_prox;
    }

    return true;
}

SolutionReport NewtonRaphson::solucao(double chute_inicial) const {
    double x0 = chute_inicial;
    double x1 = 0.0;
    double e = v_tol+1;
    int i = 0;
    
    double ini_interv = chute_inicial - 0.5;
    double fim_interv = chute_inicial + 0.5;

    if (!verificarContinuidade(v_f, ini_interv, fim_interv) ||
        !verificarContinuidade(v_df, ini_interv, fim_interv) ||
        !verificarContinuidade(v_ddf, ini_interv, fim_interv)) {
        
        return {
            SolutionStatus::FAILURE_DISCONTINUITY_DETECTED,
            nullopt,
            0,
            "Falha: Descontinuidade detectada em f, df ou ddf no intervalo de verificação."
        };
    }


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
            nullopt,
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
