#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main()
{   
    int total = 0;

    int registerX = 1;
    int cycles = 0;
    int ticks = 0;

    int rows = 6;
    int cols = 40;
    std::vector<std::vector<char>> display;
    display.resize(rows, std::vector<char>(cols, '.'));

    std::ifstream iFile;
    iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
    if (iFile.fail()) {
        std::cerr << "File not found\n";
    }
    else
    {
        std::string input;
        int count = 3;
        while (std::getline(iFile, input)) {
            int val = 0;
            if (input == "noop") {
                cycles = 1;
            }
            else
            {
                cycles = 2;
                int neg = 1;
                std::string temp = "";
                for (auto c : input)
                {
                    if (c == '-') {
                        neg = -1;
                    }
                    if (isdigit(c)) {
                        temp += c;
                    }
                }
                val = std::stoi(temp) * neg;
            }
            while (cycles)
            {
                ticks++;

                //Day 1
                if (ticks == 20) {
                    std::cout << registerX * ticks << std::endl;
                    total += registerX * ticks;
                }
                else if((ticks - 20) % 40 == 0)
                {
                    std::cout << registerX * ticks << std::endl;
                    total += registerX * ticks;
                }

                //Day 2
                int row = (ticks - 1) / 40;
                int col = (ticks - 1) % 40;

                if (col >= registerX - 1 && col <= registerX + 1) {
                    display[row][col] = '#';
                }

                cycles--;
                if (cycles == 0) {
                    registerX += val;
                }
            }
        }
    }
    iFile.close();

    std::cout << "Total: " << total << std::endl;

    //Draw screen
    for (int i = 0; i < display.size(); i++) {
        for (int j = 0; j < display[0].size(); j++) {
            std::cout << display[i][j];
        }
        std::cout << "\n";
    }

    return 0;
}
