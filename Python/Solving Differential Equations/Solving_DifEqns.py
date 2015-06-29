#!/usr/bin/env python
"""
SCMP112 - Intro to Research Computing with Python
Homework # 4: Numerical Integration - Zombie Apocalypse ODE
Tomas Mawyin
"""
"""
--- QUESTION # 1 --- 
Zombie apocalyse ODE will sove a system of ODEs to determine the number of regular people, zombie killers, or zombies in a population of 500 people. We start with 9 zombie killers in the population and we vary the initial number of zombies to see how the dynamics work. We are interested in finding out how many people turn into zombies or killers at the end of the breakdown.

S: number of regular people who can't kill zombies
Z: number of zombies
K: number of zombie killers
"""

import numpy as np
import scipy.integrate as intg
import matplotlib.pyplot as plt

# Define Ratios
B = 0.02    # Rate people turn into zombies
E = 0.015   # Rate at which zombie killers teach regular people how to kill zombies
A = 0.03    # Rate at which zombies are killed, by K
C = 0.01    # Rate at which zombie killers are turned into zombies

# Define sytem of ODE equations
def system(y,t):
	# Function values
    S = y[0]
    K = y[1]
    Z = y[2]
	# Equations
    dSdt = -B*S*Z - E*S*K
    dKdt = -C*K*Z + E*S*K
    dZdt = B*S*Z + C*K*Z - A*K*Z
    return [dSdt, dKdt, dZdt]

# Initial Conditions and time setup
Z0 = 8      # Initial number of zombies (varies)
K0 = 9      # Initial number of zombie killers
S0 = 491-Z0 # Initial number of "regular" people
y0 = [S0,K0,Z0]
t = np.linspace(0.0, 4.0, 1000) # time [days]

# Solving ODE system
soln = intg.odeint(system,y0,t)
S = soln[:, 0]
K = soln[:, 1]
Z = soln[:, 2]

# Plotting results
fig = plt.figure()
ax = fig.add_subplot(111)
ax.plot(t,S, linewidth = 2, label = 'Regular People')
ax.plot(t,K, linewidth = 2, label = 'Killers')
ax.plot(t,Z, linewidth = 2, label = 'Zombies')

# Beautifying the plot- adding labels and title
ax.grid()
ax.set_title('Zombie Apocalypse with %d zombies' %(Z0))
ax.set_xlabel('Days from Outbreak')
ax.set_ylabel('Population')
ax.legend()
plt.tight_layout()
fig.savefig('Apocalyse_with_%d_zombies.eps'%(Z0), format='eps')
plt.show()

##*** EXTRA: INTERACTIVE PLOTTING - UNCOMMENT TO SEE DYNAMICS :) ***
# plt.ion()
# plt.show()
# for i in xrange(31):
#     # Setup initial conditions
#     Z0 = i      # Initial number of zombies (varies)
#     K0 = 9      # Initial number of zombie killers
#     S0 = 491-Z0 # Initial number of "regular" people
#     y0 = [S0,K0,Z0]
#     t = np.linspace(0.0, 4.0, 1000) # time [days]
#      
#     # Solving the ODEs
#     soln = intg.odeint(system,y0,t)
#     S = soln[:, 0]
#     K = soln[:, 1]
#     Z = soln[:, 2]
#      
#     # Plotting results
#     plt.plot(t,S, linewidth = 2, label = 'Regular People')
#     plt.plot(t,K, linewidth = 2, label = 'Killers')
#     plt.plot(t,Z, linewidth = 2, label = 'Zombies')
#     plt.grid()
#     plt.title('Zombie Apocalypse with %d zombies' %(Z0))
#     plt.xlabel('Days from Outbreak')
#     plt.ylabel('Population')
#     plt.legend()
#     plt.tight_layout()
#     plt.draw()
#     plt.pause(0.5)
#     plt.clf()

##*** EXTRA: ANIMATION - UNCOMMENT TO SAVE ANIMATION :) ***
# # Specifying the animation writer and metadata
# ffwriter = an.writers['ffmpeg']
# metadata = dict(title = 'Zombie Apolcalyse', artist = 'Tomas_Mawyin',comment='Created for SCMP112 HW4')
# writer = ffwriter(fps=10, metadata=metadata)
# 
# fig = plt.figure()
# s, = plt.plot([],[],'-b', linewidth = 2)
# k, = plt.plot([],[],'-g', linewidth = 2)
# z, = plt.plot([],[],'-r', linewidth = 2)
# 
# # Specifying limits and plot labels
# plt.xlim(0, 4)
# plt.ylim(0, 500)
# plt.xlabel('Days from outbreak')
# plt.ylabel('Population')
# plt.tight_layout()
# 
# # Creating animation and saving file
# with writer.saving(fig, "ZombieApocalyse.mp4", 100):
#     for i in xrange(31):
#         # Setup initial conditions
#         Z0 = i      # Initial number of zombies (varies)
#         K0 = 9      # Initial number of zombie killers
#         S0 = 491-Z0 # Initial number of "regular" people
#         y0 = [S0,K0,Z0]
#         t = np.linspace(0.0, 4.0, 1000) # time [days]
#            
#         # Solving the ODEs
#         soln = intg.odeint(system,y0,t)
#         S = soln[:, 0]
#         K = soln[:, 1]
#         Z = soln[:, 2]
#         
#         # Plotting for animation       
#         s.set_data(t, S)
#         k.set_data(t, K)
#         z.set_data(t, Z)
#         txt = plt.text(2,300,'Zombies = %d'%(Z0))
#         writer.grab_frame()
#         txt.remove()
