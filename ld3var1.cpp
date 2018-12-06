// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <regex>
using namespace std;

//remove spaces in line
string delSpaces(std::string line)
{
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    return line;
}

void outputArray(string array[][5]) {
    for( int i=0 ; i<6 ; i++ ) {
        for( int j=0 ; j<5 ; j++ ){
            std::cout<<array[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

//validates each item from line
bool processItem(string item, int c) {
    bool result = false,hasNumb=false; //must be false
    switch(c) {
        //name
        case 0 :
            //std::cout << "name: ";
            hasNumb = std::any_of(item.begin(), item.end(), ::isdigit);
            if (hasNumb == false) {
                result = true;
            }
            break;
            //surname
        case 1 :
            //std::cout << "surname: ";
            hasNumb = std::any_of(item.begin(), item.end(), ::isdigit);
            if (hasNumb == false) {
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
            std::regex regexPattern ("^[0-9]{3}[a-zA-Z]{3}[0-9]{3}$");
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
    std::cout<<"171RDB271 Ernests Sutko 2.grupa"<<std::endl;
    //variables
    string line,fline,item;
    string filename;
    ofstream errFile;
    errFile.open ("err.txt");
    bool fileOpen=false,valid=false,validItem=false,failed=false;
    int col=0,row=0;
    //2d array supports 100 lines
    string lineData [100][5];
    //open file. while file not open try again.
    while(fileOpen == false) {
        std::cout << "Enter File Name: ";
        std::cin >> filename;
        ifstream myfile(filename);
        if (myfile.is_open()) {
            fileOpen = true;
        }
        else cout << "Unable to open file or file not found. Try again." << std::endl;
    }
    //readfile
    ifstream dataFile(filename);
    while ( std::getline(dataFile, line)) {
        fline = delSpaces(line);
        if (fline == "") continue;
        //cout << line << '\n';
        valid = processLine(fline);
        //if there are exact number of delimiters = 5
        if (valid == true) {
            //split string
            std::string delimiter = ";";
            size_t pos = 0;
            //cout << "ROW: " << row << '\n';
            while ((pos = fline.find(delimiter)) != std::string::npos) {
                item = fline.substr(0, pos);
                //cout << "current column: " << col << " item is: " << item << '\n';
                validItem = processItem(item, col);
                if (validItem == true) {
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
            if (failed == false) {
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
    std::cout << "\nSuccessful lines passed: " <<row<<"\n\n";
    outputArray(lineData);
    dataFile.close();
    errFile.close();
    //functions for tasks a,b,c
    return 0;
}
