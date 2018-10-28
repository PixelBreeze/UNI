#include<iostream>
#include<iomanip>
#include<limits>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <getopt.h>
#include<new>

int getNumber()
{
    int x;
    while(!(std::cin >> x)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong Input. Try Again: ";
    }
    return x;
}

void outputArray(int rows,int columns,float array[]) 
{
    int i,j;
    for (i = 0; i < rows; i++){
        for (j = 0; j < columns; j++) 
        {
			std::cout << (i+1) <<" "<< array[i*columns+j] << std::endl;
        }
    }
}

float* ArrayManual(int size)
{
    float* arrManual = new float[size];
    int i;
    std::cout << "Manual number input!" << std::endl;
    for (i = 0; i < size; i++){
            arrManual[i] = getNumber();
        }
    return arrManual;
}

float* ArrayRand(int size)
{
    float* arrRand = new float[size];
    int i;
    std::cout << "Parameter --rand found, numbers will be random!" << std::endl;
	float max = 50;
		for (i = 0; i < size; i++){
            arrRand[i] = max * ((float)rand()/(float)RAND_MAX) * 2 - max;
        }
    return arrRand;
}

/*void 1variants(float array[], int rows,int columns) {
    float Svalue = -50;
    float *arrVariants = new float[9];
    for (i = 0; i < size; i++){
        if (array[i] <= Svalue)
        array[i] = a;
    }
}*/

bool ProcessArgs(int argc, char** argv)
{
    const char* const short_opts = "r";
    const option long_opts[] = {
            {"rand", no_argument, nullptr, 'r'},
            {nullptr, no_argument, nullptr, 0}
    };
    while (true)
    {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);
        if (-1 == opt) {
            break;
        }
        switch (opt)
        {
        case 'r':
            return true;
            break;
        case '?': // Unrecognized option
            std::cout << "Unrecognised parameter!\n--rand/--r For random numbers.\n<none> For manual input.\n";
        break;
        default:
            return false;
            break;
        }
    }
}

int main(int argc, char **argv)
{
    std::cout << "Ernests Sutko 2.gr 171rdb271" <<std::endl;
    std::cout << std::fixed;
    std::cout << std::setprecision(2);//set decimal point 2 0's
    bool x;
    int rows,columns;
    x=ProcessArgs(argc, argv);
    std::cout << "Enter Row count for array: ";
    rows=getNumber();
    std::cout << "Enter Column count for array: ";
    columns=getNumber();
    int size=rows*columns;//define array size
    float* array;
    //create new array
    if(x==false) {
        array=ArrayManual(size);
    } else {
        array=ArrayRand(size);
    }
    outputArray(rows,columns,array);
    delete[] array;
    return 0;
}
