
#ifndef RETURNS_H
#define RETURNS_H

#include <optional>
#include <string>

enum class SolutionStatus {
    SUCCESS,
    FAILURE_NO_ROOT_IN_INTERVAL,
    FAILURE_MAX_ITERATIONS_REACHED,
    FAILURE_DERIVATIVE_ZERO,
    FAILURE_STAGNATION
};

struct SolutionReport {
    SolutionStatus status;
    std::optional<double> raiz; 
    int iter;
    std::string message;
};

#endif
