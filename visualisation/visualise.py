import requests
import matplotlib.pyplot as plt
import numpy as np
import threading
import tkinter as tk

# Fetch link lengths from the server
links_resp = requests.get("http://127.0.0.1:8000/wabo/links")
links = links_resp.json()
L0 = links[0]["length"]
L1 = links[1]["length"]

# Initial joint values
theta0 = 0.0
theta1 = 0.0

# Figure setup
fig, ax = plt.subplots()
fig.canvas.manager.set_window_title("Kinematics Visualisation")
plt.subplots_adjust(left=0.1, bottom=0.25)

# Rectangle background
rect_width = L1 * 2
rect_height = rect_width
ax.add_patch(plt.Rectangle((0, -rect_height/2), rect_width, rect_height, fill=False, color='gray', lw=2))


# Tkinter sliders in a separate window
def start_slider_window():
    def on_theta0(val):
        global theta0
        theta0 = float(val)
        update_plot()

    def on_theta1(val):
        global theta1
        theta1 = float(val)
        update_plot()

    root = tk.Tk()
    root.title("Kinematics Sliders")
    tk.Label(root, text="Joint 0").pack()
    s0 = tk.Scale(root, from_=-3.14/4, to=3.14/4, resolution=0.01, orient=tk.HORIZONTAL, length=300, command=on_theta0)
    s0.set(theta0)
    s0.pack()
    tk.Label(root, text="Joint 1").pack()
    s1 = tk.Scale(root, from_=-3.14, to=3.14, resolution=0.01, orient=tk.HORIZONTAL, length=300, command=on_theta1)
    s1.set(theta1)
    s1.pack()
    root.mainloop()


# Plot base at (0, 0)
base_x = 0
base_y = 0

# Plot links and end effector
line1, = ax.plot([], [], 'o-', lw=4, color='blue')
line2, = ax.plot([], [], 'o-', lw=4, color='green')
end_eff, = ax.plot([], [], 'ro', markersize=8)

# Expand axes for clarity
ax.set_xlim(-L0-L1-0.2, L0+L1+0.2)
ax.set_ylim(-L0-L1-0.2, L0+L1+0.2)
ax.set_aspect('equal')


def update_plot():
    # Query server for cartesian position
    # resp = requests.get(
    #     "http://127.0.0.1:8000/wabo/cartesian",
    #     params={"joint_position": [theta0, theta1]}
    # )
    # pos = resp.json()

    ########################################
    # Forward kinematics for link positions


    computation_resp = requests.get(
        "http://127.0.0.1:8000/wabo/getkinematicresults",
        params={"joint_position": [theta0, theta1]}
    )
    computations = computation_resp.json()
    x0 = computations["x0"]
    x1 = computations["x1"]
    x2 = computations["x2"]
    y0 = computations["y0"]
    y1 = computations["y1"]
    y2 = computations["y2"]
    xpos = computations["xpos"]
    ypos = computations["ypos"]

    #########################################
    # Update plot data
    line1.set_data([x0, x1], [y0, y1])
    line2.set_data([x1, x2], [y1, y2])
    end_eff.set_data([xpos], [ypos])
    fig.canvas.draw_idle()
    #########################################


# Initial draw
update_plot()

# Start the tkinter slider window in a separate thread
threading.Thread(target=start_slider_window, daemon=True).start()

plt.show()
