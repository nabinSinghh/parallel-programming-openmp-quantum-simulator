#include "quantum_circuit.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <omp.h>
#include <utility>   // std::swap

// Gate Definitions
Mat2 make_I() {
    return Mat2{ { { Complex(1,0), Complex(0,0) },
                   { Complex(0,0), Complex(1,0) } } };
}

Mat2 make_X() {
    return Mat2{ { { Complex(0,0), Complex(1,0) },
                   { Complex(1,0), Complex(0,0) } } };
}

Mat2 make_Y() {
    return Mat2{ { { Complex(0,0), Complex(0,-1) },
                   { Complex(0,1), Complex(0, 0) } } };
}

Mat2 make_Z() {
    return Mat2{ { { Complex(1,0), Complex(0,0) },
                   { Complex(0,0), Complex(-1,0) } } };
}

Mat2 make_H() {
    const double inv_sqrt2 = 1.0 / std::sqrt(2.0);
    return Mat2{ { { Complex(inv_sqrt2,0),  Complex(inv_sqrt2,0) },
                   { Complex(inv_sqrt2,0),  Complex(-inv_sqrt2,0) } } };
}

// Rotational Gates
Mat2 make_RX(double theta) {
    double c = std::cos(theta / 2.0);
    double s = std::sin(theta / 2.0);
    return Mat2{ { { Complex(c, 0),  Complex(0, -s) },
                   { Complex(0, -s), Complex(c, 0) } } };
}

Mat2 make_RY(double theta) {
    double c = std::cos(theta / 2.0);
    double s = std::sin(theta / 2.0);
    return Mat2{ { { Complex(c, 0),  Complex(-s, 0) },
                   { Complex(s, 0),  Complex(c, 0) } } };
}

Mat2 make_RZ(double theta) {
    double c = std::cos(theta / 2.0);
    double s = std::sin(theta / 2.0);
    // e^{-i theta/2} = cos - i sin
    // e^{+i theta/2} = cos + i sin
    return Mat2{ { { Complex(c, -s), Complex(0, 0) },
                   { Complex(0, 0),  Complex(c, s) } } };
}

// Operation Functions
State make_zero_state(int n_qubits) {
    std::size_t dim = (1ULL << n_qubits);
    State psi(dim);

    // Parallel initialization for large arrays
    #pragma omp parallel for
    for (std::size_t i = 0; i < dim; ++i) {
        psi[i] = Complex(0,0);
    }

    psi[0] = Complex(1.0, 0.0);
    return psi;
}

void apply_single_qubit_gate(State &state, int n_qubits, int target, const Mat2 &U) {
    const std::size_t dim = state.size();
    // validation check
    if (dim != (1ULL << n_qubits)) return;

    const std::size_t step   = (1ULL << target);
    const std::size_t period = step * 2;

    // PARALLEL REGION:
    #pragma omp parallel for collapse(2)
    for (std::size_t base = 0; base < dim; base += period) {
        for (std::size_t i = 0; i < step; ++i) {
            std::size_t i0 = base + i;
            std::size_t i1 = base + i + step;

            Complex a0 = state[i0];
            Complex a1 = state[i1];

            // Matrix-Vector multiplication for single qubit gate
            Complex b0 = U.m[0][0] * a0 + U.m[0][1] * a1;
            Complex b1 = U.m[1][0] * a0 + U.m[1][1] * a1;

            state[i0] = b0;
            state[i1] = b1;
        }
    }
}

void apply_cx(State &state, int n_qubits, int control, int target) {
    (void)n_qubits; // n_qubits not required for this implementation

    const std::size_t dim = state.size();
    if (control == target) return;

    std::size_t control_mask = (1ULL << control);
    std::size_t target_mask  = (1ULL << target);

    // PARALLEL REGION:
    #pragma omp parallel for
    for (std::size_t idx = 0; idx < dim; ++idx) {
        if ((idx & control_mask) != 0) {
            std::size_t flipped_idx = idx ^ target_mask;
            // Ensure we swap only once per pair
            if (idx < flipped_idx) {
                std::swap(state[idx], state[flipped_idx]);
            }
        }
    }
}

void print_probabilities(const State &state) {
    const std::size_t dim = state.size();
    if (dim > 32) {
        std::cout << " (State vector too large to print: size=" << dim << ")\n";
        return;
    }

    std::cout << std::fixed << std::setprecision(4);
    for (std::size_t i = 0; i < dim; ++i) {
        double p = std::norm(state[i]);
        if (p > 1e-10) {
            std::cout << "|" << i << "> : " << p << "\n";
        }
    }
}
