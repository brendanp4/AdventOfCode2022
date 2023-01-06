#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

bool IsAdjacent(std::pair<int,int> head,std::pair<int,int> tail);

int main()
{   
    const int NUM_KNOTS = 10;
    std::vector<std::pair<int,int>> rope(NUM_KNOTS,std::make_pair(0,0));
    std::map<std::pair<int, int>, int> tailPositions;

    std::ifstream iFile;
    iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
    if (iFile.fail()) {
        std::cerr << "File not found\n";
    }
    else
    {
        std::string input;
        while (std::getline(iFile, input)) {
            int steps = std::stoi( input.substr(2, input.size() - 1) );
            for (int i = 0; i < steps; i++)
            {
                switch (input[0])
                {
                case 'R':
                    rope[0].first++;
                    break;
                case 'L':
                    rope[0].first--;
                    break;
                case 'U':
                    rope[0].second++;
                    break;
                case 'D':
                    rope[0].second--;
                    break;
                default:
                    std::cerr << "Error parsing instruction" << std::endl;
                    break;
                }
                for (int i = 1; i < rope.size(); i++) {
                    if (!IsAdjacent(rope[i - 1], rope[i])) {
                        //If tail is on head's col
                        if (rope[i - 1].first == rope[i].first) {
                            rope[i - 1].second > rope[i].second ? rope[i].second++ : rope[i].second--;
                        }
                        //If tail is on head's row
                        else if (rope[i - 1].second == rope[i].second) {
                            rope[i - 1].first > rope[i].first ? rope[i].first++ : rope[i].first--;
                        }
                        //Else move tail diagonally towards head
                        else
                        {
                            int xDist = rope[i - 1].first - rope[i].first;
                            int yDist = rope[i - 1].second - rope[i].second;
                            xDist > 0 ? rope[i].first++ : rope[i].first--;
                            yDist > 0 ? rope[i].second++ : rope[i].second--;
                        }
                    }
                }
                tailPositions[rope[rope.size() - 1]]++;
            }
            
        }
    }
    iFile.close();

    std::cout << "The tail visited: " << tailPositions.size() << " unique positions" << std::endl;

    return 0;
}

bool IsAdjacent(std::pair<int, int> head, std::pair<int, int> tail)
{
    if (abs(head.first - tail.first) <= 1 && abs(head.second - tail.second) <= 1) {
        return true;
    }
    return false;
}
