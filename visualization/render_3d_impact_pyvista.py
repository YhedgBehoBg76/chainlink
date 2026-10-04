import os
import pyvista as pv
import numpy as np

os.makedirs('visualization/plots', exist_ok=True)

def main():
    # Attempt to start xvfb if pyvista provides it, else proceed off screen
    try:
        pv.start_xvfb()
    except (AttributeError, OSError):
        pass
        
    plotter = pv.Plotter(off_screen=True)
    
    plane = pv.Plane(i_size=10, j_size=10, i_resolution=20, j_resolution=20)
    sphere = pv.Sphere(radius=1.5, center=(0, 0, 2))
    
    plotter.add_mesh(plane, color='gray', show_edges=True)
    plotter.add_mesh(sphere, color='red')
    
    plotter.add_text("Scenario A - Impact t=0.01s", position='upper_left', font_size=12)
    
    plotter.screenshot('visualization/plots/02_3d_impact_pyvista.png')
    
    # plotter.export_html('visualization/plots/03_interactive_3d_impact.html') # Disabled due to Python 3.8 incompatibility with trame
    
if __name__ == '__main__':
    main()
