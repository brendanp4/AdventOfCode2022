#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <stack>

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

        std::vector<std::string> crates;
        std::vector<int> instruction;
        std::vector<std::vector<int>> instructions;
        std::string input;


        while (std::getline(iFile, input)) {
            
            if (input[0] == '[') {
                std::string temp = "";
                int i = 0;
                for (auto c : input) {
                    if ((i - 1) % 4 == 0) {
                        temp += c;
                    }
                    i++;
                }
                crates.push_back(temp);
            }

            if (input[0] == 'm') {
                std::string temp = "";
                for (auto c : input) {
                    
                    if (isdigit(c)) {
                        temp += c;
                    }
                    else
                    {
                        if (!temp.empty()) {
                            instruction.push_back(std::stoi(temp));
                        }
                        temp = "";
                    }
                }
                if (!temp.empty()) {
                    instruction.push_back(std::stoi(temp));
                }
                instructions.push_back(instruction);
                instruction.clear();


            }
        }


        //Create stacks
        std::vector<std::stack<char>> crateStacks;
        for (int i = crates.size() - 1; i >= 0; i--) {
            for (int j = 0; j < crates[0].size(); j++) {
                if (i == crates.size() - 1) {
                    std::stack<char> temp;
                    temp.push(crates[i][j]);
                    crateStacks.push_back(temp);
                }
                else {
                    if (crates[i][j] != ' ') {
                        crateStacks[j].push(crates[i][j]);
                    }
                }
                
            }
        }

        


        //Move stacks -- Day1
        /*for (int i = 0; i < instructions.size(); i++) {

            int numCrates = instructions[i][0];
            int from = instructions[i][1] - 1;
            int to = instructions[i][2] - 1;

            for (int j = 0; j < numCrates; j++) {
                char temp = crateStacks[from].top();
                crateStacks[from].pop();
                crateStacks[to].push(temp);
            }
        }*/
        //Move stacks -- Day2
        for (int i = 0; i < instructions.size(); i++) {

            int numCrates = instructions[i][0];
            int from = instructions[i][1] - 1;
            int to = instructions[i][2] - 1;

            std::stack<char> temp;

            for (int j = 0; j < numCrates; j++) {
                temp.push(crateStacks[from].top());
                crateStacks[from].pop();
            }

            while (!temp.empty())
            {
                crateStacks[to].push(temp.top());
                temp.pop();
            }

        }


        //Get max height
        int max = 0;
        for (auto s : crateStacks) {
            if (s.size() > max) {
                max = s.size();
            }
        }


        //Display crates
        int inc = max;
        for (int i = 0; i < inc; i++) {
            for (int j = 0; j < crateStacks.size(); j++) {
                if (crateStacks[j].size() == max) {
                    std::cout << crateStacks[j].top();
                    crateStacks[j].pop();
                }
                else
                {
                    std::cout << " ";
                }
            }
            max--;
            std::cout << std::endl;
        }

    }
    iFile.close();



    std::cout << "Total score: " << std::to_string(total) << "\n";
    
    
    
    return 0;
}
