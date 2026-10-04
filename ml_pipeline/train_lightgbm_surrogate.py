import os
import pandas as pd
import numpy as np
import lightgbm as lgb
import shap
import joblib
import matplotlib.pyplot as plt
from sklearn.model_selection import KFold
from sklearn.metrics import mean_squared_error, accuracy_score

os.makedirs('visualization/plots', exist_ok=True)
os.makedirs('ml_pipeline/models', exist_ok=True)

def generate_mock_data(n_samples=1000):
    np.random.seed(42)
    wire_diam = np.random.uniform(1.0, 5.0, n_samples)
    link_width = np.random.uniform(10.0, 50.0, n_samples)
    link_height = np.random.uniform(10.0, 50.0, n_samples)
    yield_strength = np.random.uniform(200, 1000, n_samples)
    
    X = pd.DataFrame({
        'wire_diam': wire_diam,
        'link_width': link_width,
        'link_height': link_height,
        'yield_strength': yield_strength
    })
    
    T_ult = wire_diam * 100 + yield_strength * 0.5 + np.random.normal(0, 10, n_samples)
    E_abs_max = (link_width * link_height) / wire_diam + np.random.normal(0, 5, n_samples)
    Rupture = (T_ult > 700).astype(int)
    
    y = pd.DataFrame({
        'T_ult': T_ult,
        'E_abs_max': E_abs_max,
        'Rupture': Rupture
    })
    
    return X, y

def main():
    data_path = 'data/simulation_results.csv'
    if os.path.exists(data_path):
        df = pd.read_csv(data_path)
        X = df[['wire_diam', 'link_width', 'link_height', 'yield_strength']]
        y = df[['T_ult', 'E_abs_max', 'Rupture']]
    else:
        X, y = generate_mock_data()
        
    kf = KFold(n_splits=5, shuffle=True, random_state=42)
    
    models_T_ult = []
    models_E_abs_max = []
    models_Rupture = []
    
    for train_index, test_index in kf.split(X):
        X_train, X_test = X.iloc[train_index], X.iloc[test_index]
        y_train, y_test = y.iloc[train_index], y.iloc[test_index]
        
        model_T_ult = lgb.LGBMRegressor(random_state=42)
        model_T_ult.fit(X_train, y_train['T_ult'])
        models_T_ult.append(model_T_ult)
        
        model_E_abs_max = lgb.LGBMRegressor(random_state=42)
        model_E_abs_max.fit(X_train, y_train['E_abs_max'])
        models_E_abs_max.append(model_E_abs_max)
        
        model_Rupture = lgb.LGBMClassifier(random_state=42)
        model_Rupture.fit(X_train, y_train['Rupture'])
        models_Rupture.append(model_Rupture)
        
    joblib.dump(models_T_ult[0], 'ml_pipeline/models/model_T_ult.pkl')
    joblib.dump(models_E_abs_max[0], 'ml_pipeline/models/model_E_abs_max.pkl')
    joblib.dump(models_Rupture[0], 'ml_pipeline/models/model_Rupture.pkl')
    
    explainer = shap.TreeExplainer(models_T_ult[0])
    shap_values = explainer.shap_values(X)
    shap.summary_plot(shap_values, X, show=False)
    plt.savefig('visualization/plots/shap_T_ult.png')
    plt.close()

if __name__ == '__main__':
    main()
