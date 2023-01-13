#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct Area {
    std::pair<int, int> signal;
    int distance;
};

int main()
{
    std::vector<Area*> useful;
    std::ifstream iFile;
    iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
    if (iFile.fail()) {
        std::cerr << "File not found\n";
    }
    else
    {
        std::string input;
        std::vector<int> coords;
        while (std::getline(iFile, input)) {
            input += " ";
            std::string temp = "";
            for (auto c : input)
            {
                if (isdigit(c) || c == '-') {
                    temp += c;
                }
                else
                {
                    if (!temp.empty()) {
                        coords.push_back(std::stoi(temp));
                    }
                    temp = "";
                }
            }
            int distance = abs(coords[0] - coords[2]) + abs(coords[1] - coords[3]);
            Area* area = new Area();
            area->signal = { coords[0],coords[1] };
            area->distance = distance;
            useful.push_back(area);

            //if (coords[2] >= 0 && coords[3] >= 0 && coords[2] <= 4000000 && coords[3] <= 4000000) {
            //    int hmm = 0;
            //}

            coords.clear();
        }
    }




    int minLeft = INT_MAX;
    int maxRight = INT_MIN;

    int row = 0;
    for (int i = 0; i <= 4000000; i++) {
        row = i;
        std::vector<std::pair<int, int>> covered;
        for (auto a : useful) {
            int x = a->signal.first;
            int y = a->signal.second;
            int d = a->distance;
            int min = y - d;
            int max = y + d;
            if (row >= min && row <= max) {
                //Row of interest is covered here;
                int left = (x - d) + (abs(row - y));
                int right = (x + d) - (abs(row - y));

                //if (covered.empty()) {
                    covered.push_back({ left,right });
                //}
                //else
                //{
                //    bool inserted = false;
                //    for (auto p : covered) {
                //        if (left >= p.first && right <= p.second) {
                //            inserted = true;
                //            break;
                //        }
                //        else if (left >= p.first) {
                //            p.second = right;
                //            inserted = true;
                //            break;
                //        }
                //        else if (right <= p.second) {
                //            p.first = left;
                //            inserted = true;
                //            break;
                //        }
                //    }
                //    if (!inserted) {
                //        covered.push_back({ left,right });
                //    }
                //}
                //if (left < minLeft) {
                //    minLeft = left;
                //}
                //if (right > maxRight) {
                //    maxRight = right;
                //}
            }
        }

        if (row == 11) {
            int letssee = 1;
        }
        
        std::sort(covered.begin(), covered.end());
        for (int j = 0; j < covered.size() - 1; j++) {
            if (covered[j].first >= covered[j + 1].first && covered[j].second <= covered[j + 1].second) {
                covered.erase(covered.begin() + j);
                j = -1;
            }
            else if (covered[j + 1].first >= covered[j].first && covered[j + 1].second <= covered[j].second) {
                covered.erase(covered.begin() + j + 1);
                j = -1;
            }
            else if (covered[j].first >= covered[j + 1].first && covered[j].first <= covered[j + 1].second) {
                covered[j + 1].second = covered[j].second;
                covered.erase(covered.begin() + j);
                j = -1;
            }
            else if (covered[j].second <= covered[j + 1].second && covered[j].second >= covered[j + 1].first) {
                covered[j + 1].first = covered[j].first;
                covered.erase(covered.begin() + j);
                j = -1;
            }
        }
        
        
        //int taken = 0;
        //for (auto p : covered) {
        //    taken += p.second - p.first;
        //}
        //std::cout << "Row " << row << " there are: " << taken << " positions where a beacon cannot be\n";

        for (int k = 0; k < covered.size(); k++) {
            if (true) {
                int col = covered[k].first - 1;
                if (col >= 0 && col <= 4000000) {
                    long long frequency = (static_cast<long long>(col) * 4000000) + static_cast<long long>(row);
                    std::cout << "Tuning frequency: " << frequency << std::endl;
                    std::cout << "Column: " << col << " Row: " << row << std::endl;
                }
                col = covered[k].second + 1;
                if (col >= 0 && col <= 4000000) {
                    long long frequency = (static_cast<long long>(col) * 4000000) + static_cast<long long>(row);
                    std::cout << "Tuning frequency: " << frequency << std::endl;
                    std::cout << "Column: " << col << " Row: " << row << std::endl;
                }
            }
        }

    }





    iFile.close();
    return 0;
}
