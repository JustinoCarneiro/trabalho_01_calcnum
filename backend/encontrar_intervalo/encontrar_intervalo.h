#ifndef INTERVALO_FINDER_H
#define INTERVALO_FINDER_H

#include <functional>
#include <utility> 

std::pair<double, double> encontrar_intervalo(const std::function<double(double)>& func);

#endif