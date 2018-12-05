// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <regex>
using namespace std;

string delSpaces(std::string line)
{
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    return line;
}

bool processItem(string item, int c) {
    bool result = false,hasNumb=false; //must be false
    switch(c) {
        //name
        case 0 :
            std::cout << "name ";
            hasNumb = std::any_of(item.begin(), item.end(), ::isdigit);
            if (hasNumb == false) {
                result = true;
            }
            break;
            //surname
        case 1 :
            std::cout << "surname ";
            hasNumb = std::any_of(item.begin(), item.end(), ::isdigit);
            if (hasNumb == false) {
                result = true;
            }
            break;
            //DoB
        case 2 : {
            std::cout << "DoB ";
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
        case 3 :
            std::cout << "ID ";
            result = true;
            //validID();
            break;
            //mark
        case 4 :{
            std::cout << "avgMark ";
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
    std::cout << item <<std::endl;
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
    std::cout << lngth <<std::endl;
    if (lngth == 5) { return true;}
    else { return false; }
}

int main () {
    string line,fline,item;
    string filename;
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
    ifstream myfile(filename);
    while ( std::getline(myfile, line)) {
        fline = delSpaces(line);
        if (fline == "") continue;
        cout << line << '\n';
        valid = processLine(fline);
        if (valid == true) {
            cout << "true" << '\n';
            //split string
            std::string delimiter = ";";
            size_t pos = 0;
            cout << "ROW: " << row << '\n';
            while ((pos = fline.find(delimiter)) != std::string::npos) {
                item = fline.substr(0, pos);
                cout << "current column: " << col << " item is: " << item << '\n';
                validItem = processItem(item, col);
                if (validItem == true) {
                    cout << "Item OK" << '\n';
                    lineData[row][col] = item;
                    col++;
                } else {
                    col=0;
                    failed = true;
                    cout << "Item BAD " << '\n';
                    //insert whole line into err.txt and dont move rows, set col 0, exit while
                    break;
                }
                fline.erase(0, pos + delimiter.length());
            }
            if (failed == false) {
                col = 0;
                row++;
            }
            //insert line ?
            //lineData[row][col] = item;
        } else {
            cout << "false" << '\n';
            //write the line into err.txt
        }
    }
    myfile.close();
    return 0;
}
//move array over to main due to not able to change column and array get intitialized multiple times.
//if true i am going to put the same line in the array / if false scrap it and not increase line count
