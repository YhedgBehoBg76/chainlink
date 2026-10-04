import os
import matplotlib.pyplot as plt
import numpy as np

os.makedirs('visualization/plots', exist_ok=True)

def main():
    configs = ['Config A', 'Config B', 'Config C', 'Config D']
    strains = np.linspace(0, 0.2, 100)
    
    plt.figure(figsize=(10, 6))
    for i, conf in enumerate(configs):
        stress = (i+1) * 100 * (1 - np.exp(-50 * strains))
        plt.plot(strains, stress, label=conf)
        
    plt.xlabel('Strain')
    plt.ylabel('Stress (MPa)')
    plt.title('Comparative Tension/Compression')
    plt.legend()
    plt.grid(True)
    plt.savefig('visualization/plots/01_comparative_tension_compression.png')
    plt.close()

if __name__ == '__main__':
    main()
