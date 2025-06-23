
#include "../bissecao/bissecao.h"
#include "../newton_raphson/newton_raphson.h"
#include "../posicao_falsa/posicao_falsa.h"
#include "../encontrar_intervalo/encontrar_intervalo.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <string>
// teste para a = 1  e intevalo [2, 3]
double ff(double a, double d) {
    return (a*d) - (d*log(d));
}

double dff(double a, double d) {
    return a - 1 - log(d);
}
double ddff(double d) {
    return 1/d;
}

void newton_raphson_solution_teste(double a, function<double(double)> func,
                                              function<double(double)> dfunc,
                                              function<double(double)> ddfunc,
                                              pair<double, double> intervalo) {

    double chute = (intervalo.first + intervalo.second) / 2.0;
    NewtonRaphson newton(func, dfunc, ddfunc, 0.00001, 100);
    SolutionReport r_newton = newton.solucao(chute);
    string raiz_newton = (r_newton.raiz && !isnan(r_newton.raiz.value()))
                                ? to_string(r_newton.raiz.value()).substr(0, 10)
                                : "----";
    string status_newton = (r_newton.status != SolutionStatus::SUCCESS)
                                ? "Falhou"
                                : (r_newton.raiz.value() > 2.0 ? "Perigo!" : "Seguro");

    cout << "| " << setw(5) << a
                << "| " << setw(17) << "Newton-Raphson"
                << "| " << setw(12) << raiz_newton
                << "| " << setw(10) << (r_newton.status == SolutionStatus::SUCCESS ? to_string(r_newton.iter) : "--")
                << "| " << setw(10) << status_newton << "|\n";
}

void bissecao_solution_teste(double a, function<double(double)> func, pair<double, double>intervalo) {
    Bissecao bissecao(func, 0.00001, 100);
    SolutionReport r_bissecao =  bissecao.encontrar_raiz(2, 3);
    string raiz_bissec = (r_bissecao.raiz && !isnan(r_bissecao.raiz.value()))
                                ? to_string(r_bissecao.raiz.value()).substr(0, 10)
                                : "----";
    string status_bissec = (r_bissecao.status != SolutionStatus::SUCCESS)
                                ? "Falhou"
                                : (r_bissecao.raiz.value() > 2.0 ? "Perigo!" : "Seguro");

    cout << "| " << setw(5) << a
        << "| " << setw(17) << "Bissecao"
        << "| " << setw(12) << raiz_bissec
        << "| " << setw(10) << (r_bissecao.status == SolutionStatus::SUCCESS ? to_string(r_bissecao.iter) : "--")
        << "| " << setw(10) << status_bissec << "|\n";
}

void posicao_falsa_solution_teste(double a, function<double(double)> func, pair<double, double> intervalo) {
    PosicaoFalsa posicaoFalsa(func, 0.00001, 100);
    SolutionReport r_pos_fal = posicaoFalsa.encontrar_raiz(intervalo.first, intervalo.second);
    string raiz_pf = (r_pos_fal.raiz && !isnan(r_pos_fal.raiz.value()))
                            ? to_string(r_pos_fal.raiz.value()).substr(0, 10)
                            : "----";
    string status_pf = (r_pos_fal.status != SolutionStatus::SUCCESS)
                            ? "Falhou"
                            : (r_pos_fal.raiz.value() > 2.0 ? "Perigo!" : "Seguro");
    cout << "| " << setw(5) << a
    << "| " << setw(17) << "Posicao Falsa"
    << "| " << setw(12) << raiz_pf
    << "| " << setw(10) << (r_pos_fal.status == SolutionStatus::SUCCESS ? to_string(r_pos_fal.iter) : "--")
    << "| " << setw(10) << status_pf << "|\n";

}

void teste_metodos_a1() {
    float a = 1.0;
    auto func = [a](double d) { return ff(a, d); };
    auto dfunc = [a](double d) { return dff(a, d); };
    auto ddfunc = [a](double d) { return ddff(d); };
    pair<double, double> intervalo = {2, 3};
    std::cout << "teste para a = 1 e intevalo [2, 3]:" << std::endl;

    newton_raphson_solution_teste(a, func, dfunc, ddfunc, intervalo);
    bissecao_solution_teste(a, func, intervalo);
    posicao_falsa_solution_teste(a, func, intervalo);

    std::cout << "como visto \"a\" = 1 esta fora dos padroes\n";

}