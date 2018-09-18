#include<iostream>
#include<iomanip>
#include<limits>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

double getNumber(){
    double x;
    cout << "Ievadiet skaitli: ";
    while(!(cin >> x)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nepareiza ievade.  Meiginat velreiz: ";
    }
    cout << "Jus ievadijat: " << x << endl;
    return x;
}
double calcA(double x) {
    double result = (x - 2*pow(x,2))/(x + 2*pow(x,2));
    return result; 
}
double calcB(double x) {
    double result = sqrt(15*x+21*pow(x,2));
    return result; 

}

int main()
{
    bool run;
    double a, b, result;
    std::cout << std::fixed;
    std::cout << std::setprecision(3);//set decimal point 3 0's
    run = true;
    char choice;
    while (run == true) {
        double x = getNumber();
        a = calcA(x);
        std::cout << "A: " << a << endl;
        if(15*x+21*pow(x,2)>=0)  {
            b = calcB(x);
            std::cout << "B: " << b << endl;
        } else {
            cout << "Nevar vilkt kvadratsakni no - skaitla."<< endl;
            continue;
        }
        if (b > 10) { //if C true f1 else f2
            result = 3 * pow(b, 2) - pow(a, 4);
            std::cout << "f1 y: " << result << endl;//f1 result
        }
        else {
            result = (a + b) / 2;
            std::cout << "f2 y: " << result << endl;//f2 result
        }
        //continue task?
        cout << "Vai atkartot uzdevumu?(Y/N)" << endl;
        cin >> choice;
        if (choice == 'N' || choice == 'n') {
            run = false;
        }
    }
}
