#include<iostream>
#include<iomanip>
#include<limits>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<getopt.h>
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

float getArrVal()
{
    float x;
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
			std::cout << std::setw(8) << std::left << array[i*columns+j];
        }
        std::cout<<std::endl;
    }
}

float* ArrayManual(int size)
{
    float* arrManual = new float[size];
    int i;
    std::cout << "Manual number input!" << std::endl;
    for (i = 0; i < size; i++){
            arrManual[i] = getArrVal();
        }
    return arrManual;
}

float* ArrayRand(int size)
{
    float* arrRand = new float[size];
    int i;
    std::cout << "Parameter --rand found, numbers will be random!" << std::endl;
	float Max = 50;
	float Min = -50;
		for (i = 0; i < size; i++){
            arrRand[i] = ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
        }
    return arrRand;
}

void variants(float array[], int rows,int columns)
{
    float Svalue;
    float *arrVariants = new float[9];
    int *skipOverArr = new int[3];
    bool skipOver=false;
    int i,j,k=0,z=0,m,Scol,Srow,Spos;
    skipOverArr[0] = -1;
    for (m = 0; m < 3; m++)// go through everything 3x
    {
        Svalue = 99999;
        for (i = 0; i < rows; i++) //array go
        {
            for (j = 0; j < columns; j++)//array go
            {
                if (array[i*columns+j] <= Svalue) //check if current element is smaller than previous smallest
                {
                    //add check if any of the positions were used already
                    for(int n = 0; n < m; n++) {
                        if(i*columns+j == skipOverArr[n]) {
                            skipOver = true;
                        }
                    }
                    if (skipOver == false) {
                        Svalue = array[i*columns+j];
                        Srow = i+1;
                        Scol = j+1;
                        Spos = i*columns+j;
                        //std::cout << "New small value:" << Svalue << " " << Srow << Scol << std::endl;
                    }
                    skipOver=false;
                }
            }
        }
        skipOverArr[m] = Spos;
        arrVariants[k] = Svalue;
        arrVariants[k+1] = Srow;
        arrVariants[k+2] = Scol;
        std::cout << arrVariants[k] << " row: " << arrVariants[k+1] << " column: " << arrVariants[k+2] << std::endl;
        k=k+3;
    }
}

int ProcessArgs(int argc, char** argv)
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
            return 1;
            break;
        case '?': // Unrecognized option
            std::cout << "Unrecognised parameter!\n--rand/--r For random numbers.\n<none> For manual input.\n";
            return 2;
            break;
        default:
            break;
        }
    }
}

int main(int argc, char **argv)
{
    std::cout << std::fixed;
    std::cout << std::setprecision(2);//set decimal point 2 0's
    int x;
    int rows,columns;
    x=ProcessArgs(argc, argv);
    if (x==2) {
        std::cout << "Exiting!";
        return 0;
    }
    std::cout << "Enter Row count for array: ";
    rows=getNumber();
    while (rows <= 0) {
        std::cout << "Wrong Input. Try Again: ";
        rows=getNumber();
    }
    std::cout << "Enter Column count for array: ";
    columns=getNumber();
    while (columns <= 0) {
        std::cout << "Wrong Input. Try Again: ";
        columns=getNumber();
    }
    int size=rows*columns;//define array size
    float* array;
    //create new array
    if(x==-1) {
        array=ArrayManual(size);
    } else {
        array=ArrayRand(size);
    }
    std::cout << std::endl;
    outputArray(rows,columns,array);
    //varianta uzd
    std::cout << std::endl;
    std::cout << "1. Varianta uzdevuma masivs: " << std::endl;
    variants(array,rows,columns);
    delete[] array;
    return 0;
}
