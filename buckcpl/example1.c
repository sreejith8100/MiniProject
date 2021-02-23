#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include "pbPlots.h"
#include "supportLib.h"
double f(double x1, double x2);
double gOn(double x1, int Vin);
double gOff(double x1);
double R, L, C, d, frequency, Vref, h = 0.00005, counter = 0;//Input Data
int continueVar, points = 24, Vin;

double f(double x1,double x2){
    double fx;
    fx = (x2/C) - (x1/(C*R));
    return fx;
}

double gOn(double x1, int Vin){
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
    double X[points], Y[points];
	while(1){
        printf("Do you want to proceed?\nPress 1 to continue or press 0 to stop.\n");
        scanf("%d", &continueVar);
        if(continueVar==0){
            printf("\n---------------------------------------------------------\n");
            break;
        }
        else if(continueVar!=0 && continueVar!=1){
            printf("\nWrong entry\n");
            printf("---------------------------------------------------------\n");
            continue;
        }
        else{
                printf("-------------Enter the following data----------------\n");
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
                printf("Reference Voltage, Vref: ");
                scanf("%lf", &Vref);
                if(Vref <= 0 || R <= 0 || L <= 0 || d < 0 || d > 1 || f <= 0){
                    printf("\nPlease check the values entered and try again.\n");
                    printf("---------------------------------------------------------\n");
                    continue;
                }
                for( Vin = 0; Vin <= points; Vin++){
                        if(Vin == 0 || X[Vin - 1] <= Vref){
                            double time, T, timeEnd = 0.12, VcM, Vcm; //the graph to be plotted is from 0 sec to 1 sec. Change this value to plot graphs for different time intervals
                            int tempVar, count = 0, cycleNumber = 0, i, iter = 2300 ;
                            int n = (timeEnd/h)+1 - iter;
                            //Variables for Runge-Kutta Method.
                            double x1, x2, f1, f2, f3, f4, g1, g2, g3, g4;
                            double Vc [n]; // Capacitor voltage values.
                            T = 1.0/frequency;
                            x1 = (d*Vin);
                            x2 = (x1/R)-(x1*(1-d)/(2.0*L*frequency));
                            time = h;
                            while(time <= timeEnd){
                                tempVar = 0;
                                while(tempVar < T/h){
                                    // When the switch is ON.
                                    if(time <= (cycleNumber*T) + d*T){
                                        f1 = h*f(x1, x2);
                                        g1 = h*gOn(x1, Vin);
                                        f2 = h*f((x1 + f1/2), (x2 + g1/2));
                                        g2 = h*gOn(x1 + f1/2, Vin);
                                        f3 = h*f((x1 + f2/2), (x2 + g2/2));
                                        g3 = h*gOn(x1 + f2/2, Vin);
                                        f4 = h*f((x1 + f3), (x2 + g3));
                                        g4 = h*gOn(x1 + f3, Vin);
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
                                    if(counter >= iter){
                                        Vc[count - iter] = floor(10000*x1)/10000;
                                    }
                                    time += h;
                                    count += 1;
                                    counter +=1;
                                    if(time > timeEnd){
                                        break;
                                    }
                                    tempVar += 1;
                                }
                                cycleNumber += 1;
                            }
                            VcM = Vc[0];
                            Vcm = Vc[0];
                            for(i=1; i<n; i++)
                            {
                                if(Vc[i]>VcM)
                                {
                                    VcM = Vc[i];
                                }
                                if(Vc[i]<Vcm)
                                {
                                    Vcm = Vc[i];
                                }
                            }
                            X[Vin] = (Vcm + VcM)/2;
                            Y[Vin] = X[Vin]/R;
                        }
                        else{
                            X[Vin] = Vin;
                            Y[Vin] = (Vref*Vref)/(X[Vin]*R);
                        }
                    }
                    printf("Voltage (in Volts) \t | Current (in Amperes)\n");
                    printf("----------------------------------------------- \n");
                    for(int i = 0;i<points;i++){
                        printf("%lf \t \t | %lf \n",X[i],Y[i]);
                    }
                    printf("----------------------------------------------- \n");
                    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
                    series->xs = X;
                    series->xsLength = points;
                    series->ys = Y;
                    series->ysLength = points;
                    series->linearInterpolation = true;
                    series->lineType = L"solid";
                    series->lineTypeLength = wcslen(series->lineType);
                    series->lineThickness = 2;
                    series->color = GetBlack();
                    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
                    settings->width = 2160;
                    settings->height = 1080;
                    settings->autoBoundaries = true;
                    settings->autoPadding = true;
                    settings->title = L"Voltage vs Current of cascaded buck converters";
                    settings->titleLength = wcslen(settings->title);
                    settings->xLabel = L"Current(Amperes)";
                    settings->xLabelLength = wcslen(settings->xLabel);
                    settings->yLabel = L"Voltage (Volts)";
                    settings->yLabelLength = wcslen(settings->yLabel);
                    ScatterPlotSeries *s [] = {series};
                    settings->scatterPlotSeries = s;
                    settings->scatterPlotSeriesLength = 1;

                    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
                    DrawScatterPlotFromSettings(canvasReference, settings);
                    size_t length;
                    double *pngdata = ConvertToPNG(&length, canvasReference->image);
                    WriteToFile(pngdata, length, "constant power load.png");
                    DeleteImage(canvasReference->image);

                    printf("The VI graph is saved in a file named constant power load.png \n");
                }
        }
    return 0;
}

