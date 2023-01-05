#include <iostream>
#include <fstream>
#include <string>
#include <map>

int FindMessage(std::string,int);

int main()
{
    int total = 0;
    std::ifstream iFile;
    iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
    if (iFile.fail()) {
        std::cerr << "File not found\n";
    }
    else
    {
        std::string input;
        while (std::getline(iFile, input)) {
            std::cout << "Message occurs after: " << std::to_string(FindMessage(input,14)) << " characters" << "\n";
        }
    }
    iFile.close();

    return 0;
}

int FindMessage(std::string input, int distinct)
{
    std::map<char, int> marker;
    for (int i = 0; i < input.size(); i++) {
        if (marker.count(input[i])) {
            i = marker[input[i]];
            marker.clear();
        }
        else
        {
            marker[input[i]] = i;
            if (marker.size() == distinct) {
                return i + 1;
            }
        }
    }
    return 0;
}
