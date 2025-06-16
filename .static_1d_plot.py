import numpy as np 
import matplotlib.pyplot as plt 
import sys

if len(sys.argv) !=2:
    print("One argument required: rule number (eg. 22)")
    exit()

rule = int(sys.argv[1])

data = np.loadtxt(f"1d_states/1d_rule_{rule}.txt")

fig, ax = plt.subplots(figsize =(len(data[0]), len((data.T)[0])), dpi = 50)
ax.imshow(data, cmap = 'Greys', aspect = 'equal', interpolation = 'none', )
ax.axis('off')
plt.tight_layout()
plt.savefig(f"1d_plots/1d_rule_{rule}.png")
plt.close()