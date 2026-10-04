# High-Performance Chain-Link Mesh Simulation & ML Optimization

This repository contains an end-to-end framework for simulating and optimizing high-tensile diamond chain-link wire meshes (сетка-рабица). It consists of two major components:
1. **C++20 HPC Simulation Core:** A highly-optimized, multi-threaded (OpenMP) explicit dynamic solver for 3D impact scenarios, tension/compression geometric mechanics, and global Latin Hypercube dataset generation.
2. **Python ML & Visualization Pipeline:** A Machine Learning suite powered by `LightGBM` and `SHAP` to train surrogate models on the C++ data, perform Pareto-frontier inverse design, and render comparative 3D visualizations via `PyVista`.

---

## 🛠️ 1. Building the C++ HPC Simulation Core

The C++ numerical core is written in Modern C++20 and requires a compiler supporting C++20 and OpenMP.

### 🐧 Linux (Ubuntu/Debian)
```bash
# 1. Install modern GCC and CMake
sudo apt update
sudo apt install build-essential cmake libomp-dev

# 2. Build the project
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j
```

### 🍎 macOS
macOS's default Apple Clang does not natively bundle OpenMP. The easiest way to compile the core is to install GCC via Homebrew.
```bash
# 1. Install CMake and GCC
brew install gcc cmake

# 2. Build the project forcing CMake to use the Homebrew GCC (e.g., g++-14)
mkdir build && cd build
CXX=g++-14 cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j
```

### 🪟 Windows
You must use a C++20 compatible compiler such as MSVC (Visual Studio 2022) or a modern MinGW-w64 distribution.
Open the **x64 Native Tools Command Prompt for VS** or a terminal with modern MinGW in the PATH:
```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

---

## 🏃 2. Running the C++ Simulation

Once built, execute the master driver to run the structural optimizations, compute stress-strain curves, run 3D explicit dynamic rock impacts, and generate the 10,000-sample dataset for the Machine Learning pipeline.

**Linux / macOS:**
```bash
./build/chainlink_sim
```

**Windows:**
```powershell
.\build\Release\chainlink_sim.exe
```
*(Note: If the C++ executable has not been run or is unavailable, the Python scripts will automatically fall back to generating synthetic/mock data for demonstration purposes).*

---

## 🐍 3. Python ML & Visualization Pipeline

The Python pipeline requires Python 3.9+ (Python 3.9+ is highly recommended to support interactive 3D HTML exports via `trame`).

### Environment Setup
```bash
# Create a virtual environment
python3 -m venv .venv

# Activate it (Linux/macOS)
source .venv/bin/activate
# Activate it (Windows)
# .\.venv\Scripts\Activate.ps1

# Install requirements
pip install -r requirements.txt
pip install trame trame-vuetify trame-vtk  # Required for PyVista 3D HTML exports
```

### Executing the Python Scripts
Run the scripts from the project root in the following sequential order:

**1. Train the LightGBM Surrogate:**
Trains the LightGBM regression/classification models using 5-fold CV and generates SHAP summary plots.
```bash
python ml_pipeline/train_lightgbm_surrogate.py
```

**2. Run Inverse Design and Pareto Frontier:**
Evaluates 100,000+ candidate meshes using the trained surrogate and calculates the Pareto frontier (minimizing Areal Mass vs maximizing T_ult).
```bash
python ml_pipeline/inverse_design_pareto.py
```

**3. Generate Stress-Strain Comparative Plots:**
Generates high-resolution Matplotlib tension/compression graphs comparing the different mesh configurations.
```bash
python visualization/plot_stress_strain.py
```

**4. Render 3D Impacts with PyVista:**
Renders the dynamic 3D impact scenarios (with and without progressive wire rupture).
```bash
python visualization/render_3d_impact_pyvista.py
```
*Outputs are saved to the `visualization/plots/` directory.*

---

## ⚡ 4. One-Command Execution (Linux/macOS)

If you are on a UNIX-like system with `make` installed, you can simply run the entire pipeline end-to-end (Build C++ -> Run C++ Sim -> Run Python ML -> Render Plots) with a single command:
```bash
make all
```
