
#ifndef BISSECAO_H
#define BISSECAO_H

#include <functional>
#include "../returns.h"

class Bissecao {
public:
    Bissecao(
        std::function<double(double)> f,
        double tol,
        int max_iter
    );

    SolutionReport encontrar_raiz(double a, double b) const;

    void setTol(double nova);
    void setMaxIter(int new_max_iter);

private:
    std::function<double(double)> v_f;
    double v_tol;
    int v_max_iter;
};

#endif // BISSECAO_H
