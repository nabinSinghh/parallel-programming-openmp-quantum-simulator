#!/bin/bash

# compile first
echo "Compiling..."
g++ -O3 -fopenmp src/simple_quantum_circuit.cpp src/quantum_circuit.cpp -o simple_quantum_circuit

OUTPUT_FILE="benchmark_results.txt" # output file

# clear it first if file exists
echo "Results:" > "$OUTPUT_FILE"

THREADS_LIST=(1 5 10 15 20 25 32)
ROUNDS=5 # Reduced for speed in automated runs, increase if needed

# Test Case 1: Varying Layers (Fixed 20 Qubits)
QUBITS_FIXED=20
LAYERS_LIST=(3 4 5 6 7 8)

echo "Test Case 1: Varying Layers (Fixed 20 Qubits)"
echo "" >> "$OUTPUT_FILE"
echo "TEST CASE 1: Fixed Qubits = $QUBITS_FIXED, Varying Layers" >> "$OUTPUT_FILE"
printf "%-10s %-10s %-10s %-20s\n" "Threads" "Qubits" "Layers" "Total Time (s)" >> "$OUTPUT_FILE"

for LAYERS in "${LAYERS_LIST[@]}"; do
  for THREADS in "${THREADS_LIST[@]}"; do
    echo "Running: Qubits=$QUBITS_FIXED, Layers=$LAYERS, Threads=$THREADS"
    RESULT=$(OMP_NUM_THREADS=$THREADS ./simple_quantum_circuit $QUBITS_FIXED $LAYERS $ROUNDS)
    TIME=$(echo "$RESULT" | grep "Total Time:" | awk '{print $3}')
    printf "%-10s %-10s %-10s %-20s\n" "$THREADS" "$QUBITS_FIXED" "$LAYERS" "$TIME" >> "$OUTPUT_FILE"
  done
  echo "" >> "$OUTPUT_FILE"
done

# Test Case 2: Varying Qubits (Fixed 6 Layers)
LAYERS_FIXED=6
QUBITS_LIST=(5 10 15 18 20 22)

echo "Test Case 2: Varying Qubits (Fixed 6 Layers)"
echo "" >> "$OUTPUT_FILE"
echo "TEST CASE 2: Fixed Layers = $LAYERS_FIXED, Varying Qubits" >> "$OUTPUT_FILE"
printf "%-10s %-10s %-10s %-20s\n" "Threads" "Qubits" "Layers" "Total Time (s)" >> "$OUTPUT_FILE"

for QUBITS in "${QUBITS_LIST[@]}"; do
  for THREADS in "${THREADS_LIST[@]}"; do
    echo "Running: Qubits=$QUBITS, Layers=$LAYERS_FIXED, Threads=$THREADS"
    RESULT=$(OMP_NUM_THREADS=$THREADS ./simple_quantum_circuit $QUBITS $LAYERS_FIXED $ROUNDS)
    TIME=$(echo "$RESULT" | grep "Total Time:" | awk '{print $3}')
    printf "%-10s %-10s %-10s %-20s\n" "$THREADS" "$QUBITS" "$LAYERS_FIXED" "$TIME" >> "$OUTPUT_FILE"
  done
  echo "" >> "$OUTPUT_FILE"
done

echo "Done. $OUTPUT_FILE"
