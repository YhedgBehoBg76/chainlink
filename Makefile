.PHONY: all build sim ml vis clean

all: build sim ml vis

build:
	mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && cmake --build . -j

sim: build
	./build/chainlink_sim

ml:
	python ml_pipeline/train_lightgbm_surrogate.py
	python ml_pipeline/inverse_design_pareto.py

vis:
	python visualization/plot_stress_strain.py
	python visualization/render_3d_impact_pyvista.py

clean:
	rm -rf build data/raw/* data/ml_dataset/* visualization/plots/*
