import os
import numpy as np
import pandas as pd
import lightgbm as lgb
import joblib
import matplotlib.pyplot as plt

os.makedirs('visualization/plots', exist_ok=True)

def generate_candidates(n=100000):
    np.random.seed(123)
    wire_diam = np.random.uniform(1.0, 5.0, n)
    link_width = np.random.uniform(10.0, 50.0, n)
    link_height = np.random.uniform(10.0, 50.0, n)
    yield_strength = np.random.uniform(200, 1000, n)
    
    X = pd.DataFrame({
        'wire_diam': wire_diam,
        'link_width': link_width,
        'link_height': link_height,
        'yield_strength': yield_strength
    })
    
    Areal_Mass = (wire_diam**2) / (link_width * link_height)
    return X, Areal_Mass

def identify_pareto(costs):
    is_efficient = np.ones(costs.shape[0], dtype=bool)
    for i, c in enumerate(costs):
        if is_efficient[i]:
            is_efficient[is_efficient] = np.any(costs[is_efficient] < c, axis=1)
            is_efficient[i] = True
    return is_efficient

def main():
    X_candidates, areal_mass = generate_candidates(100000)
    
    try:
        model_T_ult = joblib.load('ml_pipeline/models/model_T_ult.pkl')
        model_E_abs_max = joblib.load('ml_pipeline/models/model_E_abs_max.pkl')
    except FileNotFoundError:
        print("Models not found, using dummy predictions.")
        model_T_ult = lgb.LGBMRegressor().fit(np.random.rand(10,4), np.random.rand(10))
        model_E_abs_max = lgb.LGBMRegressor().fit(np.random.rand(10,4), np.random.rand(10))
        
    pred_T_ult = model_T_ult.predict(X_candidates)
    pred_E_abs_max = model_E_abs_max.predict(X_candidates)
    
    costs = np.column_stack((areal_mass, -pred_T_ult))
    pareto_mask = identify_pareto(costs)
    
    plt.figure(figsize=(10, 6))
    plt.scatter(areal_mass, pred_T_ult, c='blue', alpha=0.1, label='Candidates')
    plt.scatter(areal_mass[pareto_mask], pred_T_ult[pareto_mask], c='red', label='Pareto Frontier')
    plt.xlabel('Areal Mass')
    plt.ylabel('T_ult')
    plt.title('Pareto Frontier')
    plt.legend()
    plt.savefig('visualization/plots/04_lightgbm_shap_and_pareto.png')
    plt.close()

if __name__ == '__main__':
    main()
