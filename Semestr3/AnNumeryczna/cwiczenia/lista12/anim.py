import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation

l = 12.0
g = 9.80665
θ = np.array([np.pi/3.0, 0.0])
a = 0.0
b = 10.0
t = a
r = 1.0
fps = 30
N = int((b-a) * fps)
h = 1/fps
timer = 0.0

def f(t, θ): 
  return np.array([θ[1], -g/l * np.sin(θ[0])])


def RK(t, θ, h, f):
    K1 = f(t, θ)
    K2 = f(t+h/2  , θ+h*K1/2)
    K3 = f(t+h/2  , θ+h*K2/2)
    K4 = f(t+h    , θ+h*K3  )
    return θ + h/6*(K1+2*(K2+K3)+K4)

fig = plt.figure()
fig.set_dpi(100)
fig.set_size_inches(10, 10)

ax = plt.axes(xlim=(-20, 20), ylim=(-20, 20))
circle = plt.Circle((0,0), radius = 0.30, color = 'black')
line, = ax.plot([], [], lw=2)
sTime = plt.text(-15,17,'czas: ')
sTheta = plt.text(-15,15, 'theta: ')
sAccel = plt.text(-15, 13, "theta': ")

def init():
    global θ
    circle.center = (l*np.sin(θ[0]), -l*np.cos(θ[0]))
    line.set_data([0, circle.center[0]],[0, circle.center[1]])
    ax.add_patch(circle)
    return circle,line,

def animate(i):

    x, y = circle.center
    global t, θ, h, timer

    θ = RK(t, θ, h, f)
    t = t + h
    circle.center = (l*np.sin(θ[0]), -l*np.cos(θ[0]))
    line.set_data([0, circle.center[0]],[0, circle.center[1]])
    sTime.set_text('czas: ' + "%.3f" % (timer))
    sTheta.set_text('theta: ' + "%.3f" % (θ[0]))
    sAccel.set_text("theta': " + "%.3f" % (θ[1]))
    timer += h
    return circle, line, sTime, sTheta, sAccel

anim = animation.FuncAnimation(fig, animate, 
                               init_func=init, 
                               frames=N, 
                               interval=int(1000.0/fps),
                               blit=True)
#anim.save('/tmp/anim.mp4', fps=fps, extra_args=['-vcodec', 'libx264'])
plt.show()
