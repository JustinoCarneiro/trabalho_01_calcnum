
#include "backend/bissecao/bissecao.h"
#include "backend/posicao_falsa/posicao_falsa.h"
#include "backend/newton_raphson/newton_raphson.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Funções matemáticas do problema
double f(double a, double d) {
    if (d <= 0) return NAN;
    return (a*d) - (d*log(d));
}

double df(double a, double d) {
    return a - 1 - log(d);
}

void gera_quadro_resposta(const vector<double>& valores_a, double tolerancia) {
    cout << fixed << setprecision(6);
    cout << "==========================================================================\n";
    cout << "|  a   | Metodo           |   Raiz (d)  | Iteracoes |   Status   |\n";
    cout << "==========================================================================\n";

    for (double a : valores_a) {
        // Funções para Newton-Raphson
        auto func = [a](double d) { return f(a, d); };
        auto dfunc = [a](double d) { return df(a, d); };

        // Newton-Raphson
        NewtonRaphson newton(func, dfunc, tolerancia, 100);
        SolutionReport r_newton = newton.solucao(2.5);

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

        // Bisseção
        Bissecao bissecao(func, tolerancia, 100);
        SolutionReport r_bissec = bissecao.encontrar_raiz(0.1, 10.0);
        
        string raiz_bissec = (r_bissec.raiz && !isnan(r_bissec.raiz.value()))
                             ? to_string(r_bissec.raiz.value()).substr(0, 10)
                             : "----";
        string status_bissec = (r_bissec.status != SolutionStatus::SUCCESS)
                               ? "Falhou"
                               : (r_bissec.raiz.value() > 2.0 ? "Perigo!" : "Seguro");

        cout << "| " << setw(5) << a
             << "| " << setw(17) << "Bissecao"
             << "| " << setw(12) << raiz_bissec
             << "| " << setw(10) << (r_bissec.status == SolutionStatus::SUCCESS ? to_string(r_bissec.iter) : "--")
             << "| " << setw(10) << status_bissec << "|\n";

        // Posição Falsa
        PosicaoFalsa posicaoFalsa(func, tolerancia, 100);
        SolutionReport r_posfal = posicaoFalsa.encontrar_raiz(0.1, 10.0);
        
        string raiz_pf = (r_posfal.raiz && !isnan(r_posfal.raiz.value()))
                         ? to_string(r_posfal.raiz.value()).substr(0, 10)
                         : "----";
        string status_pf = (r_posfal.status != SolutionStatus::SUCCESS)
                           ? "Falhou"
                           : (r_posfal.raiz.value() > 2.0 ? "Perigo!" : "Seguro");

        cout << "| " << setw(5) << a
             << "| " << setw(17) << "Posicao Falsa"
             << "| " << setw(12) << raiz_pf
             << "| " << setw(10) << (r_posfal.status == SolutionStatus::SUCCESS ? to_string(r_posfal.iter) : "--")
             << "| " << setw(10) << status_pf << "|\n";

        cout << "--------------------------------------------------------------------------\n";
    }
}

int main() {
    vector<double> valores_a = {1.1, 1.2, 1.4, 1.6, 1.8, 2.0};
    double tolerancia = 0.0001;
    gera_quadro_resposta(valores_a, tolerancia);

    return 0;
}
