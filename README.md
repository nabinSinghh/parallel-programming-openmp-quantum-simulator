# Parallel Programming with OpenMP: Quantum State Vector Simulator

This project demonstrates **shared-memory parallel programming using OpenMP** in C++.  
A quantum state-vector simulator is used as the application to study **parallelism, scalability, and performance trade-offs** on multi-core CPUs.

The focus of this project is on **OpenMP-based parallelization**, performance analysis, and efficiency—not on quantum computing theory itself.

📄 **Project Report:** `report/Parallel_prog_mini_project.pdf`

---

## Project Objectives

- Apply **OpenMP parallel programming concepts** in a non-trivial computational workload
- Identify parallelizable regions and eliminate data hazards
- Measure **speedup, efficiency, and cost**
- Study the impact of:
  - Number of threads
  - Problem size (qubits)
  - Circuit depth

---

## Repository Structure

### `src/`
C++ source code implementing the parallel simulator:
- `quantum_circuit.h` – Data structures and interfaces
- `quantum_circuit.cpp` – OpenMP-parallelized gate operations
- `simple_quantum_circuit.cpp` – Benchmark driver program

---

### `scripts/`
- `run_benchmark.sh` – Automates execution across different OpenMP thread counts

---

### `results/`
- `benchmark_results.txt` – Collected runtime measurements for analysis

---

### `report/`
- `Parallel_prog_mini_project.pdf` – Detailed report covering:
  - OpenMP parallelization strategy
  - Loop decomposition and scheduling
  - Synchronization considerations
  - Experimental results and scalability analysis

---

## OpenMP Parallelization Strategy

- Used **OpenMP `parallel for`** to distribute state-vector updates
- Single-qubit gates parallelized using data-parallel loops
- Two-qubit gates implemented with race-condition-safe memory access
- Performance evaluated under varying thread counts

---

## Build and Run

### Compile
```bash
g++ -O3 -fopenmp simple_quantum_circuit.cpp quantum_circuit.cpp -o simulator
