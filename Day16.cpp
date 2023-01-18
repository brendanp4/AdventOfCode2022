#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <map>
#include <stack>

struct Valve {
    int pressure = 0;
    std::string name = "none";
    std::vector<Valve*> connections;
};

int GetDistance(Valve* start, Valve* end);

int main()
{
    std::ifstream iFile;

    Valve* start = nullptr;
    std::map<std::pair<Valve*, Valve*>, int  > DistanceMap;

    iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
    if (iFile.fail()) {
        std::cerr << "File not found\n";
    }
    else
    {
        std::string input;
        std::vector<Valve*> valves;
        std::vector<Valve*> pressurizedValves;
        std::vector<std::vector<std::string>> children;
        int index = 0;
        while (std::getline(iFile, input)) {
            input += " ";
            Valve* temp = new Valve();
            temp->name = input.substr(6, 2);
            std::string pressure = "";
            std::string tChildren = "";
            std::vector<std::string> yaga;
            for (int i = 22; i < input.size(); i++) {
                if (isdigit(input[i])) {
                    pressure += input[i];
                }
                else if (!pressure.empty()) {
                    temp->pressure = std::stoi(pressure);
                    pressure = "";
                }
                if (isupper(input[i])) {
                    tChildren += input[i];
                }
                else
                {
                    if (!tChildren.empty()) {
                        yaga.push_back(tChildren);
                        tChildren = "";
                    }
                }
            }
            children.push_back(yaga);
            index++;
            valves.push_back(temp);
            if (temp->pressure > 0) {
                pressurizedValves.push_back(temp);
            }
            if (temp->name == "AA") {
                start = temp;
            }
            
        }
        

        for (int i = 0; i < children.size(); i++) {
            for (auto s : children[i]) {
                for (auto valve : valves) {
                    if (valve->name == s) {
                        valve->connections.push_back(valves[i]);
                    }
                }
            }
        }



       
       
       

       
       
        //Store distances for valves with pressure > 0 in a map for quick lookup 
        for (int i = 0; i < pressurizedValves.size(); i++) {
            for (int j = 0; j < pressurizedValves.size(); j++) {
                DistanceMap[{pressurizedValves[i],pressurizedValves[j]}] = GetDistance(pressurizedValves[i], pressurizedValves[j]);
            }
        }
        for (int i = 0; i < pressurizedValves.size(); i++) {
            DistanceMap[{start, pressurizedValves[i]}] = GetDistance(start, pressurizedValves[i]);
        }


        //Iterate over every permutation to find optimal route - releasing maximum amount of pressure
        //Works on sample input - too slow on real input(6! vs 15! permutations)
        long long result = 0;
        std::sort(pressurizedValves.begin(), pressurizedValves.end());
        Valve* tempStart = start;
        do
        {
            int minutes = 30;
            long long total = 0;
            int place = 0;
            for (int i = 0; i < pressurizedValves.size(); i++) {
                long long dist = static_cast<long long> (DistanceMap[{tempStart,pressurizedValves[i]}]);
                long long value = minutes - dist - 1;
                minutes = value;
                
                if (minutes < 0) {
                    break;
                }

                total += (pressurizedValves[i]->pressure * minutes);

                tempStart = pressurizedValves[i];
            }
            if (total > result) {
                result = total;
            }
            tempStart = start;
        } while (std::next_permutation(pressurizedValves.begin(),pressurizedValves.end()));

        std::cout << "Best result is: " << result << std::endl;


    }


    iFile.close();
    return 0;
}

int GetDistance(Valve* start, Valve* end)
{
    int distance = 0;
    std::queue<Valve*> valves;
    std::queue<Valve*> temp;
    valves.push(start);
    bool found = false;

    while (!found) {
        while (!valves.empty())
        {
            if (valves.front() == end) {
                found = true;
                return distance;
            }
            for (auto c : valves.front()->connections) {
                temp.push(c);
            }

            valves.pop();
            
        }
        valves = temp;
        distance++;
    }

    return distance;
}
