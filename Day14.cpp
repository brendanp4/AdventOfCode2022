#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main()
{


    std::vector<std::vector<char>> map;
    map.resize(200, std::vector<char>(900, '.'));
    std::ifstream iFile;
    iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
    if (iFile.fail()) {
        std::cerr << "File not found\n";
    }
    else
    {
        int floor = 0;

        std::string input1;
        while (std::getline(iFile, input1)) {
            std::string tempCol = "";
            std::string tempRow = "";

            input1 += " ";

            int curRow = 0;
            int curCol = 0;
            int prevRow = -1;
            int prevCol = -1;

            bool col = true;
            for (int i = 0; i < input1.size(); i++)
            {
                if (isdigit(input1[i])) {
                    col ? tempCol += input1[i] : tempRow += input1[i];
                }
                else
                {
                    if (input1[i] == ',') {
                        col = false;
                    }
                    if (input1[i] == '>') {
                        col = true;
                    }
                    if (!tempCol.empty()) {
                        curCol = std::stoi(tempCol);
                        tempCol = "";
                    }
                    if (!tempRow.empty()) {
                        curRow = std::stoi(tempRow);
                        tempRow = "";

                        if (curRow > floor) {
                            floor = curRow;
                        }

                        if (prevRow == -1 && prevCol == -1) {
                            map[curRow][curCol] = '#';
                            prevRow = curRow;
                            prevCol = curCol;
                        }
                        else {
                            if (curRow == prevRow) {
                                int length = abs(curCol - prevCol);
                                for (int j = 0; j < length; j++)
                                {
                                    ((curCol - prevCol) > 0) ? prevCol++ : prevCol--;
                                    map[curRow][prevCol] = '#';
                                }
                            }
                            if (curCol == prevCol) {
                                int length = abs(curRow - prevRow);
                                for (int j = 0; j < length; j++)
                                {
                                    ((curRow - prevRow) > 0) ? prevRow++ : prevRow--;
                                    map[prevRow][curCol] = '#';
                                }
                            }
                        }


                    }

                }
            }
        }


        //Day 2
        //-------------------------------------//
        floor += 2;

        for (int i = 0; i < map[0].size(); i++)
        {
            map[floor][i] = '#';
        }
        //-------------------------------------//

        bool bAbyss = false;
        int sandRow = 0;
        int sandCol = 500;
        bool bStopped = false;
        int numSand = 0;

        while (!bAbyss)
        {
            
            while (!bStopped)
            {
                //Day 1
                //bAbyss = true;
                //for (int i = sandRow; i < map.size(); i++) {
                //    if (map[i][sandCol] == '#') {
                //        bAbyss = false;
                //    }
                //}

                //Day 2
                bAbyss = false;

                if (bAbyss) {
                    break;
                }
                //Check down
                if (map[sandRow + 1][sandCol] == '.') {
                    sandRow++;
                }
                //Check left
                else if (map[sandRow + 1][sandCol - 1] == '.') {
                    sandRow++;
                    sandCol--;
                }
                //Check right
                else if (map[sandRow + 1][sandCol + 1] == '.') {
                    sandRow++;
                    sandCol++;
                }
                else
                {
                    numSand++;
                    bStopped = true;
                    if (sandRow == 0 && sandCol == 500) {
                        bAbyss = true;
                    }
                    else
                    {
                        map[sandRow][sandCol] = 'o';
                        sandRow = 0;
                        sandCol = 500;
                    }
                    
                }
            }
            bStopped = false;
        }


        std::cout << "Sand fallen: " << numSand << std::endl;

    }


    iFile.close();
    return 0;
}
