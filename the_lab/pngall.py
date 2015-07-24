# Python script to turn all output data into png images
# Assumes that all data is in a folder called data and files are
# labelled with the convention output<time>.dat

import numpy as np
import matplotlib.pyplot as plt
import glob
import string as str

output_files = glob.glob("./data/*.dat")

for file in output_files:
    data = np.loadtxt(file)
    image_file = str.replace(file, "./data", "./images")
    image_file = str.replace(image_file, ".dat", ".png")
    fig, ax = plt.subplots(nrows = 1, ncols=1)
    cax = ax.imshow(data)
    cbar = fig.colorbar(cax)
    cbar.set_clim(0.5, 3)
    fig.savefig(image_file)
    plt.close(fig)
