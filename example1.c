#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include "pbPlots.h"
#include "supportLib.h"
float f(float x1, float x2);
float gOn(float x1);
float gOff(float x1);
float R, L, C, d, frequency, Vin, h = 0.00001;//Input Data

float f(float x1,float x2){
    float fx;
    fx = (x2/C) - (x1/(C*R));
    return fx;
}

float gOn(float x1){
    float gx;
    gx = (Vin - x1)/L;
    return gx;
}

float gOff(float x1){
    float gx;
    gx = -(x1)/L;
    return gx;
}

int main(){
	float time, T, timeStart = 0, timeEnd = 0.01; //the graph to be plotted is from 0 msec to 10 msec. Change this value to plot graphs for different time intervals
	int tempVar, count = 1, cycleNumber = 1;
	//Variables for Runge-Kutta Method.
	float x1, x2, f1, f2, f3, f4, g1, g2, g3, g4;
	double iL [1001] = {};//Array of the inductor current values to be plotted.
	double Vc [1001] = {};//Capacitor voltage values.
	double t [1001] = {} ;//Time values (for time axis).
	printf("Enter the following data\n");
	printf("Input voltage, Vin: ");
	scanf("%f", &Vin);
	printf("Load Resistance, R: ");
	scanf("%f", &R);
	printf("Inductance, L: ");
	scanf("%f", &L);
	printf("Capacitance, C: ");
	scanf("%f", &C);
	printf("Duty ratio, d: ");
	scanf("%f", &d);
	printf("Frequency, f: ");
	scanf("%f", &frequency);
	T = 1.0/frequency;
	x1 = (d*Vin);
	x2 = (x1/R)-(x1*(1-d)/(2.0*L*frequency));
	Vc [0] = x1;
	iL [0] = x2;
	time = timeStart;

	while(time <= timeEnd){
        tempVar = 0;
        while(tempVar <= T/h){
            //When the switch is ON.
            if(time < cycleNumber*d*T){
                f1 = h*f(x1, x2);
                f2 = h*f((x1 + f1/2), (x2 + g1/2));
                f3 = h*f((x1 + f2/2), (x2 + g2/2));
                f4 = h*f((x1 + f3), (x2 + g3));
                g1 = h*gOn(x1);
                g2 = h*gOn(x1 + f1/2);
                g3 = h*gOn(x1 + f2/2);
                g4 = h*gOn(x1 + f3);
                x1 += (1/6)*(f1 + 2*f2 + 2*f3 +f4);
                x2 += (1/6)*(g1 +2*g2 + 2*g3 +g4);
            }
            //When the switch is OFF.
            else{
                f1 = h*f(x1, x2);
                f2 = h*f((x1 + f1/2), (x2 + g1/2));
                f3 = h*f((x1 + f2/2), (x2 + g2/2));
                f4 = h*f((x1 + f3), (x2 + g3));
                g1 = h*gOff(x1);
                g2 = h*gOff(x1 + f1/2);
                g3 = h*gOff(x1 + f2/2);
                g4 = h*gOff(x1 + f3);
                x1 += (1/6)*(f1 + 2*f2 + 2*f3 +f4);
                x2 += (1/6)*(g1 +2*g2 + 2*g3 +g4);
            }
            iL[count] = x1;
            Vc[count] = x2;
            t[count] = time*1000;
            count +=1;
            time += h;
            if(time > timeEnd){
                break;
            }
            tempVar+=1;
        }
        cycleNumber += 1;
	}

    RGBABitmapImageReference *canvasReference1 = CreateRGBABitmapImageReference();
	DrawScatterPlot(canvasReference1, 1080, 720, t, 1001, iL, 1001);
    size_t length1;
    double *pngdata1 = ConvertToPNG(&length1, canvasReference1->image);
    WriteToFile(pngdata1, length1, "inductor current.png");
    DeleteImage(canvasReference1->image);

	RGBABitmapImageReference *canvasReference2 = CreateRGBABitmapImageReference();
	DrawScatterPlot(canvasReference2, 1080, 720, t, 1001, Vc, 1001);
    size_t length2;
    double *pngdata2 = ConvertToPNG(&length2, canvasReference2->image);
    WriteToFile(pngdata2, length2, "capacitor voltage.png");
    DeleteImage(canvasReference2->image);
	return 0;
}


