#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <iomanip>

bool IsolateChunk(std::string&, std::string&, std::string&, std::string&);
int CompareData(std::string, std::string);

int main()
{   


    std::vector<int> solution;
    std::ifstream iFile;
    iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
    if (iFile.fail()) {
        std::cerr << "File not found\n";
    }
    else
    {
        
        std::string input1;
        std::string input2;
        std::vector<char> temp;
        int index = 0;
        while (std::getline(iFile, input1)) {
            std::getline(iFile, input2);
            index++;


            std::cout << "Comparing...\n";
            for (auto c : input1)
            {
                std::cout << c;
            }
            std::cout << std::endl;
            for (auto c : input2)
            {
                std::cout << c;
            }
            std::cout << std::endl;

            if (CompareData(input1, input2)) {
                solution.push_back(index);
            }

            bool bValid = true;


            int retVal = 2;

            std::string toCompare1;
            std::string toCompare2;



            //while (retVal == 2)
            //{
            //    //Get first data value
            //    if (input1[0] == '[') {
            //        int brackets = 0;
            //        for (int i = 1; i < input1.size(); i++)
            //        {
            //            if (input1[i] == '[') {
            //                brackets++;
            //            }
            //            else if (input1[i] == ']') {
            //                brackets--;
            //                if (brackets == 0) {
            //                    toCompare1 = input1.substr(1, i);
            //                    for (int j = 0; j < toCompare1.size(); j++) {
            //                        input1.erase(input1.begin() + (i - j));
            //                    }
            //                    if (input1[1] == ',') {
            //                        input1.erase(input1.begin() + 1);
            //                    }
            //                    break;
            //                }
            //            }
            //            else if (isdigit(input1[i]) && brackets == 0) {
            //                toCompare1 += input1[i];
            //                input1.erase(input1.begin() + i);
            //                if (input1[1] == ',') {
            //                    input1.erase(input1.begin() + 1);
            //                }
            //                break;
            //            }
            //        }
            //    }




            //    //Get second data value
            //    if (input2[0] == '[') {
            //        int brackets = 0;
            //        for (int i = 1; i < input2.size(); i++)
            //        {
            //            if (input2[i] == '[') {
            //                brackets++;
            //            }
            //            else if (input2[i] == ']') {
            //                brackets--;
            //                if (brackets == 0) {
            //                    toCompare2 = input2.substr(1, i);
            //                    for (int j = 0; j < toCompare2.size(); j++) {
            //                        input2.erase(input2.begin() + (i - j));
            //                    }
            //                    if (input2[1] == ',') {
            //                        input2.erase(input2.begin() + 1);
            //                    }
            //                    break;
            //                }
            //            }
            //            else if (isdigit(input2[i]) && brackets == 0) {
            //                toCompare2 += input2[i];
            //                input2.erase(input2.begin() + i);
            //                if (input2[1] == ',') {
            //                    input2.erase(input2.begin() + 1);
            //                }
            //                break;
            //            }
            //        }
            //    }

            //    std::string hmm = input1 + input2;

            //    retVal = CompareData(toCompare1, toCompare2);

            //}



            //if (retVal == 1) {
            //    solution.push_back(index);
            //}

            std::string filler;
            std::getline(iFile, filler);

        }
    }

    std::cout << "\n\n";
    for (auto s : solution) {
        std::cout << s << std::endl;
    }

    iFile.close();   
    return 0;
}

int CompareData(std::string left, std::string right)
{
    while ( !left.empty() || !right.empty() )
    {
        if (left.empty()) {
            return true;
        }
        if (right.empty()) {
            return false;
        }
        //Remove leftover commas
        if (!left.empty()) {
            if (left[0] == ',') {
                left.erase(left.begin());
            }
        }
        if (!right.empty()) {
            if (right[0] == ',') {
                right.erase(right.begin());
            }
        }

        //Begin comparing
        if (!left.empty() && !right.empty()) {
            
            bool bListRequired = true;
            bool bRightConverted = false;

            while (bListRequired) {
                //IsolateChunk(left, right);
                if (!left.empty()) {
                    if (left[0] == ',') {
                        left.erase(left.begin());
                    }
                }
                if (!right.empty()) {
                    if (right[0] == ',') {
                        right.erase(right.begin());
                    }
                }


                bListRequired = false;
                if (!left.empty() && right.empty()) {
                    return false;
                }
                if (left.empty() && !right.empty()) {
                    return true;
                }
                //Convert data chunk to a list temporarily if required              
                if (!left.empty() && !right.empty() && isdigit(left[0]) && !isdigit(right[0])) {
                    bListRequired = true;
                    left.insert(left.begin(), '[');
                    for (int i = 1; i < left.size(); i++)
                    {
                        if (!isdigit(left[i])) {
                            left.insert(left.begin() + i, ']');
                            break;
                        }
                        if (i == left.size() - 1) {
                            left.insert(left.begin() + i + 1, ']');
                            break;
                        }
                    }
                }
                else if (!left.empty() && !right.empty() && isdigit(right[0]) && !isdigit(left[0])) {
                    bListRequired = true;
                    right.insert(right.begin(), '[');
                    for (int i = 1; i < right.size(); i++)
                    {
                        if (!isdigit(right[i]) || i == right.size()) {
                            right.insert(right.begin() + i, ']');
                            break;
                        }
                        if (i == right.size() - 1) {
                            right.insert(right.begin() + i + 1, ']');
                            break;
                        }
                    }
                }


                //Unpack data chunk if it is a list

                //Remove left brackets
                int brackets = 0;
                if (left[0] == '[') {
                    bListRequired = true;
                    for (int i = 0; i < left.size(); i++)
                    {
                        if (left[i] == '[') {
                            brackets++;
                        }
                        if (left[i] == ']') {
                            brackets--;
                            if (brackets == 0) {
                                left.erase(left.begin() + i);
                                left.erase(left.begin());
                            }
                        }
                    }
                }

                //Remove right brackets
                brackets = 0;
                if (right[0] == '[') {
                    bListRequired = true;
                    for (int i = 0; i < right.size(); i++)
                    {
                        if (right[i] == '[') {
                            brackets++;
                        }
                        if (right[i] == ']') {
                            brackets--;
                            if (brackets == 0) {
                                right.erase(right.begin() + i);
                                right.erase(right.begin());
                            }
                        }
                    }
                }
            }

            //Compare integers in list
            std::string temp = "";
            int leftVal = 0;
            int rightVal = 0;
            while (isdigit(left[0]))
            {
                temp += left[0];
                left.erase(left.begin());
            }
            if (temp == "") {
                return true;
            }
            leftVal = std::stoi(temp);
            temp = "";
            while (isdigit(right[0]))
            {
                temp += right[0];
                right.erase(right.begin());
            }
            if (temp == "") {
                return false;
            }
            rightVal = std::stoi(temp);

            if (leftVal > rightVal) {
                return false;
            }
            if (leftVal < rightVal) {
                return true;
            }

        }
    }
    return 2;
}
