import numpy as np
import sys
import matplotlib.pyplot as plt
import matplotlib.animation as animation

if len(sys.argv) != 2:
    print("One argument required: number of steps/frame (use the same as for the simulation itself)")
    exit()

num = int(sys.argv[1])

fps = 30
n_seconds = 5
snapshots = []

for i in range(1, num + 1):
    grid = np.loadtxt("2d_states/2d_state_{:04d}.txt".format(i))
    snapshots.append(grid)

# First set up the figure, the axis, and the plot element we want to animate
fig = plt.figure(figsize=(8, 8))

initial_frame = snapshots[0]
img = plt.imshow(initial_frame, interpolation='none', aspect='auto', vmin=0, vmax=1)
plt.gca().axis('off')
plt.tight_layout()


def animate_func(i):
    img.set_array(snapshots[i])
    return [img]


anim = animation.FuncAnimation(
    fig,
    animate_func,
    frames=num - 1,
    interval=1 / fps,  # in ms
)

anim.save(f'2d_plots/animation_{num}_steps.gif', writer=animation.PillowWriter(fps=240))
