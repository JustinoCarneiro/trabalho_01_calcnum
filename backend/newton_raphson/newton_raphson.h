
#ifndef NEWTON_RAPHSON_H
#define NEWTON_RAPHSON_H

#include <functional>
#include "../returns.h"

using namespace std;

class NewtonRaphson {
public:
    NewtonRaphson(
        function<double(double)> f,
        function<double(double)> df,
        function<double(double)> ddf,
        double tol,
        int max_iter
    );

    SolutionReport solucao(double chute_inicial) const;

    void setTol(double nova);
    void setMaxIter(int new_max_iter);

private:
    function<double(double)> v_f;
    function<double(double)> v_df;
    function<double(double)> v_ddf;
    double v_tol;
    int v_max_iter;

    bool verificarContinuidade(
        const function<double(double)>& func,
        double inicio_intervalo,
        double fim_intervalo) const;
};

#endif
