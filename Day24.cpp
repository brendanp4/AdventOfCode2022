#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <map>


int main()
{
    std::vector<std::vector<char>> valley;
    std::vector<std::pair<char, std::pair<int, int>>> blizzards;
    std::ifstream iFile;
    iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
    if (iFile.fail()) {
        std::cerr << "File not found\n";
    }
    else
    {
        int row = 0;
        std::string input;
        while (std::getline(iFile, input)) {
            std::vector<char> temp;
            for (int col = 0; col < input.size(); col++){
                temp.push_back(input[col]);
                if (input[col] != '#' && input[col] != '.') {
                    blizzards.push_back({ input[col],{row,col} });
                }
            }
            valley.push_back(temp);
            row++;
        }
       
    }
    
    //Start and end position coordinates
    std::pair<int, int> start = { 0,1 };
    std::pair<int, int> end = { valley.size() - 1,valley[0].size() - 2 };
    
    //Counter for total moves made in getting to destination
    int numMoves = 0;
    //Queue to hold potential moves
    std::queue<std::pair<int, int>> moves;
    
    //First move is the start position
    moves.push(start);

    bool bFinished = false;
    int routes = 0;

    while (!bFinished) {
        std::queue<std::pair<int, int>> tMoves;     //Place all possible moves into a temporary queue
        std::map<std::pair<int, int>, int> uMoves;  //Hash table to ensure no duplicate moves
        //Reset valley
        for (int row = 1; row < valley.size() - 1; row++)
        {
            for (int col = 1; col < valley[0].size() - 1; col++)
            {
                valley[row][col] = '.';
            }
        }
        //Place blizzards in valley
        for (auto& b : blizzards) {
            //Move blizzard
            switch (b.first)
            {
            case '<':
                if (b.second.second - 1 == 0) {
                    b.second.second = valley[0].size() - 2;
                }
                else
                {
                    b.second.second -= 1;
                }
                break;
            case '>':
                if (b.second.second + 1 == valley[0].size() - 1) {
                    b.second.second = 1;
                    
                }
                else
                {
                    b.second.second += 1;
                }
                break;
            case '^':
                if (b.second.first - 1 == 0) {
                    b.second.first = valley.size() - 2;
                }
                else
                {
                    b.second.first -= 1;
                }
                break;
            case 'v':
                if (b.second.first + 1 == valley.size() - 1) {
                    b.second.first = 1;
                }
                else
                {
                    b.second.first += 1;
                }
                break;
            }
            //Place blizzard
            valley[b.second.first][b.second.second] = '*';
        }

        numMoves++;
        while (!moves.empty())
        {
            //Check possible moves
            std::pair<int, int> you = moves.front();
            moves.pop();

            //Check if destination has been reached
            if (you == end) {
                std::cout << "Moves to reach end: " << numMoves - 1 << std::endl;
                bFinished = true;
                routes++;
                break;
            }
            


            //Check if up is in bounds
            if (you.first - 1 >= 0) {
                //Check if it is a free square
                if (valley[you.first - 1][you.second] == '.') {
                    //You can move here
                    if (!uMoves.count({ you.first - 1,you.second })) {
                        tMoves.push({ you.first - 1,you.second });
                        uMoves[{you.first - 1, you.second}]++;
                    }
                }
            }
            //Check if down is in bounds
            if (you.first + 1 <= valley.size() - 1) {
                //Check if it is a free square
                if (valley[you.first + 1][you.second] == '.') {
                    //You can move here
                    if (!uMoves.count({ you.first + 1,you.second })) {
                        tMoves.push({ you.first + 1,you.second });
                        uMoves[{you.first + 1, you.second}]++;
                    }
                }
            }
            //Check if left is in bounds
            if (you.second - 1 >= 0) {
                //Check if it is a free square
                if (valley[you.first][you.second - 1] == '.') {
                    //You can move here
                    if (!uMoves.count({ you.first,you.second - 1 })) {
                        tMoves.push({ you.first,you.second - 1 });
                        uMoves[{you.first, you.second - 1}]++;
                    }
                }
            }
            //Check if right is in bounds
            if (you.second + 1 <= valley[0].size() - 1) {
                //Check if it is a free square
                if (valley[you.first][you.second + 1] == '.') {
                    //You can move here
                    if (!uMoves.count({ you.first,you.second + 1 })) {
                        tMoves.push({ you.first,you.second + 1 });
                        uMoves[{you.first, you.second + 1}]++;
                    }
                }
            }
            //Check if current position is safe
            if (valley[you.first][you.second] == '.') {
                //You can move here
                if (!uMoves.count({ you.first,you.second })) {
                    tMoves.push({ you.first,you.second });
                    uMoves[{you.first, you.second}]++;
                }
            }
        }
        moves = tMoves;
        if (bFinished && routes < 3) {
            bFinished = false;
            std::queue<std::pair<int, int>> empty;
            moves = empty;
            std::swap(start, end);
            moves.push(start);
        }
    }

    iFile.close();
    return 0;
}
