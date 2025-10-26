# ZLab: A Generic C++ Numerical Methods Library (C++20)

ZLab is a lightweight, generic C++ library built to provide robust and stable numerical routines for linear algebra and scientific computing. Our focus is on clear code, modern C++ design, and reliable performance for common mathematical operations.

---

## Design and Core Principles

* **C++20 Concepts:** The library utilizes C++20 **Concepts** (`VectorConcept`, `MatrixConcept`) to rigorously enforce type constraints, resulting in clean function signatures and helpful compiler error messages.

* **Move Semantics:** Designed for efficiency, the codebase heavily employs **Move Semantics** to ensure large data structures (like matrices) are moved, not copied, during factorizations and algorithm assembly, minimizing runtime overhead.

* **BLAS-Style Foundation:** The API draws inspiration from standard high-performance routines (e.g., the versatile `gemv` for generalized matrix-vector multiplication), aiming for industry-standard operation naming.

---

## Current Capabilities

### Factorizations and Solvers

The primary focus is on stable, direct methods for linear systems:

* **QR Decomposition (MGS):** Implementation of the **Modified Gram-Schmidt (MGS)** process for the $A=QR$ factorization, with built-in tolerance checks for identifying ill-conditioned matrices.

* **Unified Solvers:** A single, robust routine (`linear_solver`) handles both:
    * **Exact Solutions** for square systems ($A\mathbf{x}=\mathbf{b}$).
    * **Least Squares Solutions** for overdetermined systems ($\min_{\mathbf{x}} \|A\mathbf{x} - \mathbf{b}\|$), leveraging the numerical stability of the QR decomposition.

---

### Advanced and Iterative Methods

* **Explicit Runge-Kutta Solver:** A highly generic, template-based solver for Ordinary Differential Equations (ODEs) driven by the standard Butcher Tableau structure.

---

## Compiling and Running (Using CMake Presets)

The project uses CMake with a pre-configured `CMakePresets.json` file, which simplifies building, testing, and running examples.

### 1. Initial Setup and Configuration

Use the `default-config` preset to configure the project. This command automatically sets the build directory to `../build` and enables C++20, and unit testing.

```bash
# Creates the build environment (e.g., Makefiles) in the 'build/' folder
cmake --preset default-config
```

### 2. Building the Project

Use the same preset name with the --build command to compile the library and the examples.

```bash
# Compiles the zlab library, the main application, and examples
cmake --build --preset default-config
```

### 3. Running Examples/Executables

Executables are placed inside the build directory. To run a specific example (like ode_demo), you can execute it directly from the build folder:

```bash
# Example: Run the ODE demo executable
./build/examples/ode_demo
```

### 4. Running Unit Tests

To run all unit tests (implemented via Google Test), use the test command with the designated preset:

```bash
# Runs tests defined in the 'unit-tests' preset
ctest --preset unit-tests
```

## Project Structure (For Developers)

The project is structured for easy integration:

* **Library Core (`zlab/`)**: The core directory is an independent component that can be added as a subdirectory to any external CMake project.
* **Unit Testing**: Code stability is ensured through comprehensive unit tests implemented using the **Google Test** framework.
* **Examples**: The dedicated `examples` subdirectory remains for demonstration and testing purposes.




