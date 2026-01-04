#ifndef QUANTUM_CIRCUIT_H
#define QUANTUM_CIRCUIT_H

#include <complex>
#include <vector>

// type def
using Complex = std::complex<double>;
using State   = std::vector<Complex>;

struct Mat2 {
    Complex m[2][2];
};

// Gate Functions
Mat2 make_I();
Mat2 make_X();
Mat2 make_Y();
Mat2 make_Z();
Mat2 make_H();

Mat2 make_RX(double theta);
Mat2 make_RY(double theta);
Mat2 make_RZ(double theta);

// Operation Functions
// Initialize state |0...0> (zero state)
State make_zero_state(int n_qubits);

// single-qubit gate U to target qubit (single qubit gate)
void apply_single_qubit_gate(State &state, int n_qubits, int target, const Mat2 &U);

// CX (CNOT)
void apply_cx(State &state, int n_qubits, int control, int target);

// print probabilities
void print_probabilities(const State &state);

#endif
