#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include "pbPlots.h"
#include "supportLib.h"
double f(double x1, double x2);
double gOn(double x1);
double gOff(double x1);
double R, L, C, d, frequency, Vin, h = 0.00001;//Input Data

double f(double x1,double x2){
    double fx;
    fx = (x2/C) - (x1/(C*R));
    return fx;
}

double gOn(double x1){
    double gx;
    gx = (Vin - x1)/L;
    return gx;
}

double gOff(double x1){
    double gx;
    gx = -(x1)/L;
    return gx;
}

int main(){
	double time, T, timeStart = 0, timeEnd = 0.01; //the graph to be plotted is from 0 msec to 10 msec. Change the value of timeEnd to plot graphs for different time intervals
	int tempVar, count = 1, cycleNumber = 0;
	int n = (timeEnd/h) + 1;  //The number of steps to be calculaed
	
	//Variables for Runge-Kutta Method.
	double x1, x2, f1, f2, f3, f4, g1, g2, g3, g4;
	double iL [n]; //Array of the inductor current values to be plotted.
	double Vc [n]; //Capacitor voltage values.
	double t [n]; //Time values (for time axis).
	
	//Asking the user to enter the values.
	printf("Enter the following data\n");
	printf("Input voltage, Vin: ");
	scanf("%lf", &Vin);
	printf("Load Resistance, R: ");
	scanf("%lf", &R);
	printf("Inductance, L: ");
	scanf("%lf", &L);
	printf("Capacitance, C: ");
	scanf("%lf", &C);
	printf("Duty ratio, d: ");
	scanf("%lf", &d);
	printf("Frequency, f: ");
	scanf("%lf", &frequency);
	T = 1.0/frequency;
	
	//Calculating the initial values of Vc and iL.
	x1 = (d*Vin);
	x2 = (x1/R)-(x1*(1-d)/(2.0*L*frequency));
	Vc [0] = x1;
	iL [0] = x2;
	t[0] = 0;
	time = timeStart;

	while(time <= timeEnd){
        tempVar = 0;
        while(tempVar < T/h){
            //When the switch is ON.
            if(time <= (cycleNumber*T) + d*T){
                f1 = h*f(x1, x2);
                g1 = h*gOn(x1);
                f2 = h*f((x1 + f1/2), (x2 + g1/2));
                g2 = h*gOn(x1 + f1/2);
                f3 = h*f((x1 + f2/2), (x2 + g2/2));
                g3 = h*gOn(x1 + f2/2);
                f4 = h*f((x1 + f3), (x2 + g3));
                g4 = h*gOn(x1 + f3);
                x1 += (1.0/6.0)*(f1 + 2*f2 + 2*f3 + f4);
                x2 += (1.0/6.0)*(g1 + 2*g2 + 2*g3 + g4);
            }
            //When the switch is OFF.
            else{
                f1 = h*f(x1, x2);
                g1 = h*gOff(x1);
                f2 = h*f((x1 + f1/2), (x2 + g1/2));
                g2 = h*gOff(x1 + f1/2);
                f3 = h*f((x1 + f2/2), (x2 + g2/2));
                g3 = h*gOff(x1 + f2/2);
                f4 = h*f((x1 + f3), (x2 + g3));
                g4 = h*gOff(x1 + f3);
                x1 += (1.0/6.0)*(f1 + 2*f2 + 2*f3 + f4);
                x2 += (1.0/6.0)*(g1 + 2*g2 + 2*g3 + g4);
            }
            iL[count] = floor(10000*x2)/10000;  //Rounding off the values upto 4 decimal places.
            Vc[count] = floor(10000*x1)/10000;
            time += h;
            t[count] = time*1000;
            count += 1;
            
	    //Checking if the time has reached its end.
	    if(time > timeEnd){
                break;
            }
            tempVar += 1;
        }
        cycleNumber += 1;
	}

    RGBABitmapImageReference *canvasReference1 = CreateRGBABitmapImageReference();
    DrawScatterPlot(canvasReference1, 2160, 1080, t, n, iL, n);
    size_t length1;
    double *pngdata1 = ConvertToPNG(&length1, canvasReference1->image);
    WriteToFile(pngdata1, length1, "inductor current.png");  //The graph for iL vs t will be saved as inductor current.png
    DeleteImage(canvasReference1->image);

    RGBABitmapImageReference *canvasReference2 = CreateRGBABitmapImageReference();
    DrawScatterPlot(canvasReference2, 2160, 1080, t, n, Vc, n);
    size_t length2;
    double *pngdata2 = ConvertToPNG(&length2, canvasReference2->image);
    WriteToFile(pngdata2, length2, "capacitor voltage.png");  //The graph for Vc vs t will be saved as capacitor voltage.png
    DeleteImage(canvasReference2->image);
    return 0;
}
