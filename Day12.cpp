#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <curses.h>

int main()
{

    std::vector<std::vector<char>> map;
    std::vector<std::vector<int>> visited;
    //std::pair<int, int> start(0, 0);
    std::pair<int, int> end(0, 0);

    std::vector<std::pair<int, int>> starts;
    std::vector<int> candidates;

    std::ifstream iFile;
    iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
    if (iFile.fail()) {
        std::cerr << "File not found\n";
    }
    else
    {
        std::string input;
        std::vector<char> temp;
        int i = 0;
        while (std::getline(iFile, input)) {
            int j = 0;
            for (auto c : input) {
                if (c == 'S' || c == 'a') {
                    starts.push_back({ i,j });
                    c = 'a';
                }
                if (c == 'E') {
                    end = { i,j };
                    c = 'z';
                }
                temp.push_back(c);
                j++;
            }
            i++;
            map.push_back(temp);
            temp.clear();
        }
    }
    iFile.close();


    

    bool bFinish = false;

    initscr();
    noecho();


    start_color();

    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);

    int i = 0;
    while (!bFinish)
    {
        if (i < 1) {
            

            for (int k = 0; k < starts.size(); k++) {

                attron(COLOR_PAIR(4));
                //Print the terrain map
                for (int i = 0; i < map.size(); i++)
                {
                    for (int j = 0; j < map[0].size(); j++)
                    {
                        mvaddch(i, j, map[i][j]);
                    }
                }
                refresh();


                visited.resize(map.size(), std::vector<int>(map[0].size(), 0));
                for (auto& v : visited) {
                    std::fill(v.begin(), v.end(), 0);
                }
                std::pair<int,int> start = starts[k];
                visited[start.first][start.second] = 1;
                std::queue<std::pair<int, int>> positions;

                positions.push(start);
                bool bFound = false;
                int counter = 0;
                while (!bFound)
                {
                    std::queue<std::pair<int, int>> toCheck;
                    while (!positions.empty())
                    {

                        //38  64

                        //28 16

                        std::pair<int, int> temp = positions.front();

                        //Set color to yellow - checking char
                        mvchgat(temp.first, temp.second, 1, 3, 1, NULL);
                        refresh();
                        //while (getch() != 'n')
                        //{
                        //    //Do nothing
                        //}
                        positions.pop();
                        if (temp == end) {
                            int pLength = visited[temp.first][temp.second] - 1;
                            bFound = true;
                            break;
                        }

                        //Check left

                        // Check if left is in bounds
                        if (temp.second > 0) {
                            // Check if left is traversable from current position (left character is at most one larger than current character)
                            if (map[temp.first][temp.second - 1] <= map[temp.first][temp.second] + 1) {
                                // Check if current path to left is shorter than the path already
                                // OR if the point is unvisited
                                if (/*(visited[temp.first][temp.second] + 1) < visited[temp.first][temp.second - 1] ||*/ visited[temp.first][temp.second - 1] == 0) {
                                    visited[temp.first][temp.second - 1] = visited[temp.first][temp.second] + 1;
                                    toCheck.push({ temp.first,temp.second - 1 });
                                    mvchgat(temp.first, temp.second, 1, 3, 3, NULL);

                                    counter++;
                                }
                            }
                        }

                        //Check right
                        // Check if right is in bounds
                        if (temp.second < map[0].size() - 1) {
                            // Check if right is traversable from current position (right character is at most one larger than current character)
                            if (map[temp.first][temp.second + 1] <= map[temp.first][temp.second] + 1) {
                                if (/*(visited[temp.first][temp.second] + 1) < visited[temp.first][temp.second + 1] ||*/ visited[temp.first][temp.second + 1] == 0) { // Check if shortest path to right is higher than this path
                                    visited[temp.first][temp.second + 1] = visited[temp.first][temp.second] + 1;
                                    toCheck.push({ temp.first,temp.second + 1 });
                                    mvchgat(temp.first, temp.second, 1, 3, 3, NULL);

                                    counter++;
                                }
                            }
                        }

                        //Check up
                        // Check if up is in bounds
                        if (temp.first > 0) {
                            // Check if up is traversable from current position (up character is at most one larger than current character)
                            if (map[temp.first - 1][temp.second] <= map[temp.first][temp.second] + 1) {
                                if (/*(visited[temp.first][temp.second] + 1) < visited[temp.first - 1][temp.second] ||*/ visited[temp.first - 1][temp.second] == 0) { // Check if shortest path to up is higher than this path
                                    visited[temp.first - 1][temp.second] = visited[temp.first][temp.second] + 1;
                                    toCheck.push({ temp.first - 1,temp.second });
                                    mvchgat(temp.first, temp.second, 1, 3, 3, NULL);

                                    counter++;
                                }
                            }
                        }

                        //Check down
                        // Check if down is in bounds
                        if (temp.first < map.size() - 1) {
                            // Check if down is traversable from current position (down character is at most one larger than current character)
                            if (map[temp.first + 1][temp.second] <= map[temp.first][temp.second] + 1) {
                                if (/*(visited[temp.first][temp.second] + 1) < visited[temp.first + 1][temp.second] ||*/ visited[temp.first + 1][temp.second] == 0) { // Check if shortest path to right is higher than this path
                                    visited[temp.first + 1][temp.second] = visited[temp.first][temp.second] + 1;
                                    toCheck.push({ temp.first + 1,temp.second });
                                    mvchgat(temp.first, temp.second, 1, 3, 3, NULL);

                                    counter++;
                                }
                            }
                        }

                        //map[temp.first][temp.second] = '.';

                        refresh();

                    }
                    positions = toCheck;
                    if (positions.empty()) {
                        bFound = true;
                    }

                }


                refresh();


                std::vector<std::vector<int>> path;
                path.resize(map.size(), std::vector<int>(map[0].size(), 0));


                char check = map[0][0];

                std::string output = "Steps: " + std::to_string(visited[end.first][end.second] - 1);

                std::pair<int, int> temp = end;
                int hello = 0;
                while (temp != start)
                {
                    hello++;
                    if (visited[temp.first][temp.second] == 7) {
                        int hmm = 0;
                    }
                    //Check left
                    if ((temp.second > 0) && (visited[temp.first][temp.second - 1] == (visited[temp.first][temp.second] - 1)) && ((map[temp.first][temp.second] - 1) <= map[temp.first][temp.second - 1])) {
                        //if () {
                        temp.second--;
                        path[temp.first][temp.second] = 1;
                        mvchgat(temp.first, temp.second, 1, 3, 2, NULL);
                        //}
                    }
                    //Check right
                    else if ((temp.second < map[0].size() - 1) && (visited[temp.first][temp.second + 1] == (visited[temp.first][temp.second] - 1)) && ((map[temp.first][temp.second] - 1) <= map[temp.first][temp.second + 1])) {
                        //if () {
                        temp.second++;
                        path[temp.first][temp.second] = 1;
                        mvchgat(temp.first, temp.second, 1, 3, 2, NULL);
                        //}
                    }
                    //Check up
                    else if ((temp.first > 0) && (visited[temp.first - 1][temp.second] == (visited[temp.first][temp.second] - 1)) && ((map[temp.first][temp.second] - 1) <= map[temp.first - 1][temp.second])) {
                        //if () {
                        temp.first--;
                        path[temp.first][temp.second] = 1;
                        mvchgat(temp.first, temp.second, 1, 3, 2, NULL);
                        //}
                    }

                    //Check down
                    else if ((temp.first < map.size() - 1) && (visited[temp.first + 1][temp.second] == (visited[temp.first][temp.second] - 1)) && ((map[temp.first][temp.second] - 1) <= map[temp.first + 1][temp.second])) {
                        //if () {
                        temp.first++;
                        path[temp.first][temp.second] = 1;
                        mvchgat(temp.first, temp.second, 1, 3, 2, NULL);
                        //}
                    }
                    else
                    {
                        break;
                    }
                    refresh();
                }

                int finished = hello;
                if (hello > 1) {
                    candidates.push_back(hello);
                }


            }

            int shortestPath = INT_MAX;
            for (auto n : candidates)
            {
                if (n < shortestPath) {
                    shortestPath = n;
                }
            }
        }
        refresh();
        i++;
    }
    
    endwin();
    return 0;
}
