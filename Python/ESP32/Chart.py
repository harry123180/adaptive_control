"""
這個程式負責Real-time的繪圖
"""
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import WIFI
IP = '172.20.10.3'
# Parameters
x_len = 200         # Number of points to display
y_range = [0, 4196]  # Range of possible Y values to display

# Create figure for plotting
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = list(range(0, 200))
ys = [0] * x_len
ax.set_ylim(y_range)

# Initialize communication with TMP102
WIFI.init(IP)

# Create a blank line. We will update the line in animate
line, = ax.plot(xs, ys)

# Add labels
plt.title('WIFI Communication voltage' )
plt.xlabel('Samples')
plt.ylabel('voltage(12bit)')

# This function is called periodically from FuncAnimation
def animate(i, ys):

    # Read temperature (Celsius) from TMP102
    temp_c = round(WIFI.read_vol(), 2)

    # Add y to list
    ys.append(temp_c)

    # Limit y list to set number of items
    ys = ys[-x_len:]

    # Update line with new Y values
    line.set_ydata(ys)

    return line,

# Set up plot to call animate() function periodically
ani = animation.FuncAnimation(fig,
    animate,
    fargs=(ys,),
    interval=50,
    blit=True)
plt.show()