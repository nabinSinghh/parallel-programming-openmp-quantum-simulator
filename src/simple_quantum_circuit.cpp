#include "quantum_circuit.h"
#include <iostream>
#include <omp.h>
#include <vector>
#include <random>
#include <cstdlib>   // std::atoi
#include <cmath>     // M_PI

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// VQC Benchmark
void run_benchmark(int n_qubits, int layers, int training_rounds) {
    std::cout << "\nVQC Benchmark (" << n_qubits << " qubits)\n";
    std::cout << "Threads: " << omp_get_max_threads() << "\n";
    std::cout << "Simulating " << training_rounds << " training rounds (forward passes only.)\n";

    double total_start_time = omp_get_wtime();
    std::mt19937 gen(42); // random number generator
    std::uniform_real_distribution<> dis(0.0, 2.0 * M_PI); // uniform distribution for VQC parameters

    for (int round = 0; round < training_rounds; ++round) {
        double round_start = omp_get_wtime();

        // reset state for each forward pass
        State psi = make_zero_state(n_qubits);

        for (int layer = 0; layer < layers; ++layer) { // for each layer
            // Parametrized gate to all: RX
            for (int i = 0; i < n_qubits; ++i) {
                double theta = dis(gen);
                apply_single_qubit_gate(psi, n_qubits, i, make_RX(theta));
            }

            // Parametrized gate RY
            for (int i = 0; i < n_qubits; ++i) {
                double theta = dis(gen);
                apply_single_qubit_gate(psi, n_qubits, i, make_RY(theta));
            }

            // RZ
            for (int i = 0; i < n_qubits; ++i) {
                double theta = dis(gen);
                apply_single_qubit_gate(psi, n_qubits, i, make_RZ(theta));
            }

            // All to all entanglement
            for (int i = 0; i < n_qubits; ++i) {
                for (int j = 0; j < n_qubits; ++j) {
                    if (i != j) {
                        apply_cx(psi, n_qubits, i, j);
                    }
                }
            }
        }

        double round_end = omp_get_wtime();
        std::cout << "Round " << (round + 1) << "/" << training_rounds
                  << " complete. Time: " << (round_end - round_start) << " s\n";
    }

    double total_end_time = omp_get_wtime();
    std::cout << "\nRun Complete.\n";
    std::cout << "Total Time: " << (total_end_time - total_start_time) << " seconds.\n";
    std::cout << "Average Time per Round: "
              << (total_end_time - total_start_time) / training_rounds << " seconds.\n";
}

// main
int main(int argc, char* argv[]) {
    // default cases
    int n_qubits = 20;
    int layers   = 6;
    int rounds   = 10;

    if (argc > 1) n_qubits = std::atoi(argv[1]);
    if (argc > 2) layers   = std::atoi(argv[2]);
    if (argc > 3) rounds   = std::atoi(argv[3]);

    run_benchmark(n_qubits, layers, rounds);
    return 0;
}
