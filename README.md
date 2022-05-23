# Introduction
This was the second half of my proposal to the IEEE Empower a Billion Lives Competition in 2018. A Tertiary (load demand) controller was also developed to go along with this.

The goal of the competition was to reach the next billion people who didn't have access to  electricity in the 21st Century.

This was part of a vision where Renewable Power produced in a village is optimised and delivered by offloading some components to RL based agents thereby reducing the need for complex Microgrid equipment.

# A Secondary controller
* Here MADDPG is used to train 4 agents which try to stabilise the volatge at any instant of time (Secondary Voltage Control)
* A custom microgrid is created in MATLAB here to simulate the load of a village
* Python interfaces with MATLAB at every step to change the state of the system
* Based on the observed Voltages from MATLAB and target voltages, the agents learn to control their voltage profile, thereby stabilising the Grid
* Note: The time interval for secondary control is in the range of milliseconds


## Learnings
* Creating a custom MicroGrid in MATLAB
* Interfacing MATLAB and Python
* Using the interface as a custom environment due to lack of anything comarable in OpenAI Gym in 2018
* Training and optimising for the number of agents in MADDPG
