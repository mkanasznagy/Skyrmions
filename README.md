# Skyrmions

Skyrmions are topological excitations, that were originally proposed by Skyrme to describe particles (hadrons). In the paper Scientific Reports 5, 7692 (2015) (http://www.nature.com/articles/srep07692), we proposed to create skyrmion excitations in a quantum emulator of ultracold atoms that are in the superfluid state and have an order parameter of non-trivial topology. The system is described in detail in the text.

How to use the code:

The code consists of three parts: 

(1) Initialization using a MATLAB routine, found in the folder 'initialization'. One can set up the system parameters (temperature, number of lattice sites etc.) in initializeGPE.m, and then run the function initializeGPE(filenameBase), where the string filenameBase should contain the name base of the files.

This routine generates three files: 
- filenameBase_[...]_Filenames: contains the name of some files that the C++ simulation (2)
- filenameBase_[...]_SystemParameters: contains all parameters of the system, that are read by the 
- filenameBase_[...]_RunFile: runfile for running the simulation on the cluster
The beginning of the files '[...]' is set up by this routine, and contains some of the relevant parameters (see paper).

(2) C++ solver that calculates the ground state of the skyrmion in the topologically non-trivial state. This part of the code can be found in the main folder.
The code can be compiled using the makefile that is provided, producing the executable 'imagTimeGPESolver'. 

The simulation can be run as './imagTimeGPESolver filenameBase_[...]_SystemParameters'.

(3) Visualization of the results using a MATLAB window that plots all relevant physical results. The control panel can be started by clicking on the 'SkyrmionsControlPanel.fig' file. One can set up the path to the control panel to the file containing the simulation results. The radio buttons allow one to set up the parameters of the plot, and then plot the results or save them. See a screenshot on control_panel.png.
