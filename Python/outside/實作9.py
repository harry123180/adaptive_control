import pygmt
import xarray as xr
import numpy as np

minlon, maxlon = 120., 122.1
minlat, maxlat = 21.8, 25.6

# Load sample earth relief data
grid = pygmt.datasets.load_earth_relief(resolution="03s", region=[minlon, maxlon, minlat, maxlat])

frame =  ["xa1f0.25","ya1f0.25", "z2000+lmeters", "wSEnZ"]

pygmt.makecpt(
        cmap='geo',
        series=f'-6000/4000/100',
        continuous=True
    )
fig = pygmt.Figure()
fig.grdview(
    grid=grid,
    region=[minlon, maxlon, minlat, maxlat, -6000, 4000],
    perspective=[150, 30],
    frame=frame,
    projection="M15c",
    zsize="4c",
    surftype="i",
    plane="-6000+gazure",
    shading=0,
    # Set the contour pen thickness to "0.1p"
    contourpen="1p",
)
fig.basemap(
    perspective=True,
    rose="jTL+w3c+l+o-2c/-1c" #map directional rose at the top left corner
)

fig.colorbar(perspective=True, frame=["a2000", "x+l'Elevation in (m)'", "y+lm"])
fig.savefig("topo-plot_3d.png", crop=True, dpi=300)