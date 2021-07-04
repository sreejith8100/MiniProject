<h1> Read this document before using the code </h1>
This project uses an open source library called pbPlots for plotting 2-D graphs using C programming. To read more about pbPlots, <a href = https://github.com/InductiveComputerScience/pbPlots> click here</a>.
To use the code, either clone the repository using git clone, or copy the code from each file and create a new project in codeblocks or any other IDEs. There is a makefile already created and if any changes are made to the names of the file, please update those names in the makefile too.
The main code is in the file called <a href = https://github.com/sreejith8100/MiniProject/blob/main/example1.c >example1.c</a>. There are some further instructions in the code itself as comments. Try changing the values of the input data and analyse how the code works.
<h2> Abstract </h2>
One of the major issues in multi-converter power electronic systems is the constant power load (CPL) behavior of the tightly regulated converters. To have better system performance, the output of the converters should be tightly regulated. DC/DC converters when tightly regulated act as constant power loads. The current through a constant power load increases/decreases when the voltage across it decreases/increases, respectively. As a result, CPLs have negative impedance characteristics. This is a destabilizing effect known as negative impedance instability. To analyze this instability, a DC/DC buck converter is cascaded with another DC/DC buck converter which is tightly regulated. This is simulated in MATLAB and is verified using C program. Runge Kutta method of the fourth-order is used in the program to solve the second-order differential equation of the buck converter. Simulations and C program results are provided to verify the analysis.
<h2> Introduction </h2>
A DC/DC buck converter is a DC to DC power converter which steps down the input voltage while stepping up the current. DC/DC converters are more efficient compared to linear voltage regulators because of the reduced losses in the electronic switches. And linear voltage regulators are not suitable for high power applications.
<h3> Constant Power Load </h3>
It is a type of load in which the dynamic resistance is adjusted to increase the current inversely to the load voltage. as the voltage rises or falls, then the product of voltage and current in the load is a power that is constant. This is done to keep the power dissipated in the load constant as the voltage drops.
It is very important to study CPL as the nonlinear nature of CPLs adds complexity to the control and its negative incremental impedance characteristics not only induce instability at the point of load but also reduces the effective damping of the system. Low damping and instability caused by negative incremental impedance of CPLs in a system, are the real challenges. Hence we need to find a suitable method to make the system stable again.
<h3> Examples of CPL </h3>
1. Tightly regulated cascaded DC-DC converters: In a distributed multi-converter power architecture, if the dynamic response of the fed converter is faster than the feeding converter then the fed converter acts as a CPL that can cause stability issues. These are mostly used in PV systems.
2. Another common source of CPL is electric motors which consume a major portion of the energy produced in developed countries. When a motor operates in constant power mode, (P = τω = const) where τ is the torque and ω is the angular momentum, for a DC/AC inverter driving the electric motor with tightly regulated speeds, for the speed-torque having one to one characteristics, constant speed leads to constant torque and therefore it acts as a constant power load.
<h2> Objectives </h2>
* To analyze the working of buck converter both analytically and numerically (Runge-Kutta method).
* To verify the working of DC-DC buck converter feeding a constant power load (CPL).
* To verify the results of the analysis using C program.
<h2> Block Diagram </h2>
![image](https://user-images.githubusercontent.com/67676040/124379686-14805980-dcd6-11eb-986b-b3e7710a0ff4.png)
<h2> Methodology </h2>
* Simulation of buck converter feeding resistive load in MATLAB
* The differential equations of the buck converter are solved numerically using the fourth-order Runge Kutta method.
* A C program is written to solve the differential equations of the buck converter and plots of inductor current and the output voltage is obtained using an open-source library called pbPlots.
* The simulation results are thus verified using the C program results.  
* Simulation of buck converter feeding CPL is done in MATLAB
* A C program is written to plot the V-I characteristics of a buck converter feeding constant power load.
* Simulation results are verified with the program results.
The numerical method used to solve the differential equations of the system is <a href = https://www.geeksforgeeks.org/runge-kutta-4th-order-method-solve-differential-equation/>Runge Kutta Method</a>.
<h1>Conclusion</h1>
We analyzed the working of buck converters with a resistive load and with a Constant Power Load (CPL) and verified it using a C program. Hence we found out that a buck converter feeding a CPL behaves like a resistive load if the input voltage is less than the reference voltage given to the secondary buck converter. We also did a stability analysis in MATLAB and C program and found out that buck converter with a resistive load is stable because all the poles lie on the left-hand side of the imaginary axis. Whereas in the case of CPL, the system is unstable as poles are lying on the right-hand side of the imaginary axis. Hence we can conclude that buck converter feeding a constant power load is unstable.
