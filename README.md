# Parallel Programming with OpenMP: Quantum State Vector Simulator

This project demonstrates **shared-memory parallel programming using OpenMP** in C++.  
A quantum state-vector simulator is used as the application to study **parallelism, scalability, and performance trade-offs** on multi-core CPUs.

The focus of this project is on **OpenMP-based parallelization, performance analysis, and efficiency**, rather than quantum computing theory itself.

📄 **Project Report:** `OpenMP_Quantum_Simulator_Report.pdf`

---

## Project Objectives

- Apply **OpenMP parallel programming concepts** to a computationally intensive workload
- Identify parallelizable regions while avoiding race conditions
- Measure **speedup, efficiency, and scalability**
- Study the impact of:
  - Number of OpenMP threads
  - Problem size (number of qubits)
  - Circuit depth (layers)

---

## Repository Structure

### `src/`
C++ source code implementing the OpenMP-parallel quantum simulator:
- `quantum_circuit.h` – Core data structures and function declarations
- `quantum_circuit.cpp` – OpenMP-parallelized quantum gate implementations
- `simple_quantum_circuit.cpp` – Benchmark driver and experiment harness

---

### `scripts/`
- `run_benchmark.sh` – Automates compilation and execution across different thread counts

---

## OpenMP Parallelization Strategy

- Used **OpenMP `parallel for`** to distribute state-vector updates
- Single-qubit gates parallelized using data-parallel loop decomposition
- Two-qubit (CNOT) gates implemented with race-condition-safe memory access
- Performance evaluated across varying thread counts and problem sizes

---

## Authors

- **Nabin K. Singh**  
  M.S. Student, Electrical and Computer Engineering  
  The University of Alabama in Huntsville (UAH)

- **Atit Pokharel**  
  Ph.D. Student, Electrical and Computer Engineering  
  The University of Alabama in Huntsville (UAH)


## Build and Run

### Compile
```bash
g++ -O3 -fopenmp src/simple_quantum_circuit.cpp src/quantum_circuit.cpp -o simulator
