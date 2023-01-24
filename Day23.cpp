#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <map>

int main()
{
    std::vector<std::vector<char>> garden;
    for (int i = 0; i < 75; i++) {
        std::vector<char> temp(300, '.');
        garden.push_back(temp);
    }
    std::ifstream iFile;
    iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
    if (iFile.fail()) {
        std::cerr << "File not found\n";
    }
    else
    {
        std::string input;
        while (std::getline(iFile, input)) {
            std::vector<char> temp(300, '.');
            for (int i = 0; i < input.size(); i++) {
                temp[125 + i] = input[i];
            }
            garden.push_back(temp);
        }
        for (int i = 0; i < 75; i++) {
            std::vector<char> temp(300, '.');
            garden.push_back(temp);
        }
    }
    
    std::queue<std::pair<int, int>> directions;
    std::pair<int, int> north = { -1,0 };
    std::pair<int, int> south = { 1,0 };
    std::pair<int, int> west = { 0,-1 };
    std::pair<int, int> east = { 0,1 };
    directions.push(north);
    directions.push(south);
    directions.push(west);
    directions.push(east);

    std::map<std::pair<int, int>,std::vector<std::pair<int,int>>> coords;

    bool bNoElvesMoved = false;
    int rounds = 0;
    while (!bNoElvesMoved) {
        rounds++;
        if (rounds % 100 == 0) {
            std::cout << rounds << std::endl;
        }
        bNoElvesMoved = true;
        for (int row = 0; row < garden.size(); row++) {
            for (int col = 0; col < garden[0].size(); col++) {
                if (garden[row][col] == '#') {
                    std::queue<std::pair<int, int>> temp = directions;
                    bool bMove = false;
                    if (garden[row - 1][col - 1] == '.' && garden[row - 1][col] == '.' && garden[row - 1][col + 1] == '.'
                        && garden[row][col - 1] == '.' && garden[row][col + 1] == '.'
                        && garden[row + 1][col - 1] == '.' && garden[row + 1][col] == '.' && garden[row + 1][col + 1] == '.') {
                        //Stay put
                        coords[{row, col}].push_back({ row,col });
                    }
                    else
                    {
                        
                        while (!temp.empty())
                        {
                            std::pair<int, int> direction = temp.front();
                            temp.pop();
                            if (direction.first == 0) {
                                if (garden[row - 1][col + direction.second] == '.' && garden[row][col + direction.second] == '.' && garden[row + 1][col + direction.second] == '.') {
                                    coords[{row, col + direction.second}].push_back({ row,col });
                                    bMove = true;
                                    bNoElvesMoved = false;

                                    break;
                                }
                            }
                            else
                            {
                                if (garden[row + direction.first][col - 1] == '.' && garden[row + direction.first][col] == '.' && garden[row + direction.first][col + 1] == '.') {
                                    coords[{row + direction.first, col}].push_back({ row,col });
                                    bMove = true;
                                    bNoElvesMoved = false;

                                    break;
                                }

                            }
                        }
                        if (!bMove) {
                            coords[{row, col}].push_back({ row,col });
                        }
                    }
                }
            }
        }

        std::vector<std::vector<char>> updatedGarden;
        updatedGarden.resize(300, std::vector<char>(300, '.'));

        for (auto const& entry : coords)
        {
            if (entry.second.size() == 1) {
                updatedGarden[entry.first.first][entry.first.second] = '#';
            }
            else
            {
                for (auto p : entry.second) {
                    updatedGarden[p.first][p.second] = '#';
                }
            }
        }
        garden = updatedGarden;
        directions.push(directions.front());
        directions.pop();
        coords.clear();
    }

    std::cout << "First round with no elf movement: " << rounds << std::endl;


    //Part 1:

    //int top = 0;
    //int bottom = INT_MIN;
    //int left = INT_MAX;
    //int right = INT_MIN;
    //
    //for (int row = 0; row < garden.size(); row++)
    //{
    //    for (int col = 0; col < garden[0].size(); col++) {
    //        if (garden[row][col] == '#') {
    //            if (top == 0) {
    //                top = row;
    //            }
    //            if (col < left) {
    //                left = col;
    //            }
    //            if (col > right) {
    //                right = col;
    //            }
    //            if (row > bottom) {
    //                bottom = row;
    //            }
    //        }
    //    }
    //}
    //
    //int emptySpace = 0;
    //for (int row = top; row <= bottom; row++)
    //{
    //    for (int col = left; col <= right; col++) {
    //        if (garden[row][col] == '.') {
    //            emptySpace++;
    //        }
    //    }
    //}
    //
    //std::cout << "Empty ground tiles: " << emptySpace << std::endl;

    iFile.close();
    return 0;
}

