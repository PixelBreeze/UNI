// reading a text file
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <regex>
#include <Windows.h>

using namespace std;

void moveConsole(){
    for(int i=0; i<11; i++)
        std::cout<<std::endl;
}

void pressKey(){
    std::cout << "Press ENTER to continue...";
    std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
    std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
}
//remove spaces in line
string delSpaces(std::string line)
{
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    return line;
}

void findString(string array[][5],string input,int c,int pos){
    bool found = false;
    for( int i=0 ; i<c ; i++ ) {
        if (input.compare(array[i][pos]) == 0) {
            for( int j=0 ; j<5 ; j++ ) {
                std::cout<<array[i][j]<<" ";
            }
            found = true;
            std::cout<<std::endl;
        }
    }
    if(! found) {
        std::cout<<"Students netika atrasts!"<<std::endl;
    } else {
        std::cout<<std::endl;
    }

}

void outputArray(string array[][5],int row) {
    std::string header[5]={"Vārds","Uzvārds","Dzimšanas Dat.","Apliecības Nr.","Vidējā Atzīme"};
    for (int k=0; k<5; k++) {
        std::cout<<"* "<<std::setw(19)<< std::left<<header[k];
    }
    std::cout<<std::endl;
    for( int i=0 ; i<row ; i++ ) {
        for( int j=0 ; j<5 ; j++ ){
            std::cout<<"| "<<std::setw(18) << std::left <<array[i][j];
        }
        std::cout<<std::endl;
    }
}

//create sorted array and pass to output.
void sortArray(string array[][5],int rows) {
    std::string sortedArray[rows][5];
    int currentRow=0;
    double smallest=11;
    for (int i = 0; i < rows; i++) {
        for(int j = 0; j < rows; j++) {
            double current = ::atof(array[j][4].c_str());
            if(smallest >= current && current <= 10) {
                smallest = current;
                currentRow = j;
            }
        }
        for(int k = 0; k < 5; k++) {
            sortedArray[i][k] = array[currentRow][k];
        }
        smallest = 11;
        array[currentRow][4]="12";
    }
    for( int i=0 ; i<rows ; i++ ) {
        for( int j=0 ; j<5 ; j++ ){
            array[i][j]=sortedArray[i][j];
        }
    }
    std::cout<<"\nDati tika sakāroti!\n";
    pressKey();
}

//validates each item from line
bool processItem(string item, int c) {
    bool result = false,hasNumb=false; //must be false
    switch(c) {
        //name
        case 0 :
            //std::cout << "name: ";
            hasNumb = std::any_of(item.begin(), item.end(), ::isdigit);
            if (! hasNumb) {
                result = true;
            }
            break;
            //surname
        case 1 :
            //std::cout << "surname: ";
            hasNumb = std::any_of(item.begin(), item.end(), ::isdigit);
            if (! hasNumb) {
                result = true;
            }
            break;
            //DoB
        case 2 : {
            //std::cout << "DoB: ";
            int c=0,numbItem=0;
            std::string subItem;
            std::regex regexPattern ("\\d{2}\\.\\d{2}\\.\\d{4}\\.");
            if (std::regex_match (item, regexPattern)) {
                //std::cout << "date matched\n";
                std::string delimiter = ".";
                size_t pos = 0;
                while ((pos = item.find(delimiter)) != std::string::npos) {
                    subItem = item.substr(0, pos);
                    numbItem = std::stoi(subItem);
                    switch(c) {
                        case 0 :
                            if (numbItem > 31 || numbItem < 1) {
                                return false;
                            }
                            break;
                        case 1 :
                            if (numbItem > 12 || numbItem < 1) {
                                return false;
                            }
                            break;
                        case 2 :
                            if (numbItem > 2018 || numbItem < 1500) {
                                return false;
                            }
                            break;
                    }
                    item.erase(0, pos + delimiter.length());
                    c++;
                }
                result = true;
            }
            break;
        }
            //ID
        case 3 : {
            //std::cout << "ID: ";
            std::regex regexPattern ("^[0-9]{3}[A-Z]{3}[0-9]{3}$");
            if (std::regex_match (item, regexPattern)) {
                //std::cout << "ID Matched\n";
                return true;
            }
            break;
        }
            //mark
        case 4 :{
            //std::cout << "avgMark: ";
            std::regex regexPattern ("^\\d{1,2}\\.\\d{2}$");
            if (std::regex_match (item, regexPattern)) {
                //std::cout << "Mark Matched\n";
                double mark = ::atof(item.c_str());
                if (mark >= 0 && mark <= 10 ) {
                    return true;
                }
            }
            break;
        }
    }
    return result;
}

//validate the length based on delimiter count and check if not empty tag
bool processLine(std::string line) {
    int lngth = 0;
    string item;
    //split string
    std::string delimiter = ";";
    size_t pos = 0;
    while ((pos = line.find(delimiter)) != std::string::npos) {
        item = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        if (item.length() != 0) {
            lngth++;
        }
    }
    //std::cout << lngth <<std::endl;
    if (lngth == 5) { return true;}
    else { return false; }
}

int main () {
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);
    std::cout<<u8"171RDB271 Ernests Šutko 2.grupa"<<std::endl;
    //variables
    string line,fline,item;
    string filename;
    ofstream errFile;
    errFile.open ("err.txt");
    bool fileOpen=false,valid=false,validItem=false,failed=false,run=true;
    int col=0,row=0;
    //2d array supports 100 lines
    string lineData [100][5];
    //open file. while file not open try again.
    while(! fileOpen) {
        std::cout << "Ievadiet faila nosaukumu: ";
        std::cin >> filename;
        ifstream myfile(filename);
        if (myfile.is_open()) {
            fileOpen = true;
        }
        else cout << "Nebija iespējams atvērt failu vai fails netika atrasts.\nMeiģiniet velreiz." << std::endl;
    }
    //readfile
    ifstream dataFile(filename);
    while ( std::getline(dataFile, line)) {
        fline = delSpaces(line);
        if (fline == "") continue;
        //cout << line << '\n';
        valid = processLine(fline);
        //if there are exact number of delimiters = 5
        if (valid) {
            //split string
            std::string delimiter = "";
            size_t pos = 0;
            //cout << "ROW: " << row << '\n';
            while ((pos = fline.find(delimiter)) != std::string::npos) {
                item = fline.substr(0, pos);
                //cout << "current column: " << col << " item is: " << item << '\n';
                validItem = processItem(item, col);
                if (validItem) {
                    //insert formatted item string into array of lines
                    string fItem = delSpaces(item);
                    lineData[row][col] = fItem;
                    col++;
                } else {
                    col=0;
                    failed = true;
                    //insert whole line into err.txt and don't move rows, set col 0, exit while
                    break;
                }
                fline.erase(0, pos + delimiter.length());
            }
            if (! failed) {
                col = 0;
                row++;
            } else {
                fline = delSpaces(line);
                errFile << fline <<"\n";
            }
            failed = false;
        } else {
            fline = delSpaces(line);
            errFile << fline <<"\n";
        }
    }
    std::cout << "\nPareizas līnijas apstrādātas: " <<row<<"\n\n";
    outputArray(lineData,row);
    dataFile.close();
    errFile.close();
    //function calls for tasks a,b,c
    while(run) {
        string inp;
        std::cout<<"\n1. Atrast studentu, kura apliecības numurs atbilst lietotāja ievadītajam."
        <<"\n2. Meklēt studentu pēc uzvārda."
        <<"\n3. Sakārtot datus par studentiem augošā secībā pēc vidējās atzīmes."
        <<"\n4. Iziet."<<std::endl;
        std::cout<<"\nIzvēlieties darbības nr: ";
        std::cin>>inp;
        bool hasNumb = std::any_of(inp.begin(), inp.end(), ::isdigit);
        if (!hasNumb) {
            inp = "0";
        }
        int task = std::stoi(inp);
        switch(task) {
            case 1: {
                std::cout<<"\nIevadiet studenta apliecības nr: ";
                string id;
                std::cin>>id;
                findString(lineData, id,row,3);
                pressKey();
                break;
            }
            case 2: {
                std::cout << "\nIevadiet studenta uzvārdu: ";
                string surname;
                std::cin >> surname;
                findString(lineData, surname, row, 1);
                pressKey();
                break;
            }
            case 3:
                sortArray(lineData,row);
                break;
            case 4: {
                run = false;
                break;
            }
            default:
                std::cout<<"Šādas darbības nav!"<<std::endl;
                pressKey();
                break;
        }
        if (run)  {
            moveConsole();
            outputArray(lineData,row);
        }
    }
    return 0;
}
