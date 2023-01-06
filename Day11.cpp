#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <functional>

struct Item
{
    Item(int w) : worryLevel(static_cast<unsigned long long>(w)){}
    unsigned long long worryLevel = 0;
};

struct Monkey
{
    std::queue<Item*> items;
    std::function<void(Item&)> operation;

    int divisor = 0;
    int throwToIfTrue = 0;
    int throwToIfFalse = 0;

    unsigned long long itemsInspected = 0;
};

void Play(Monkey* monkey,std::vector<Monkey*>& monkeys,int totalProduct) {
    int size = monkey->items.size();

    for (int i = 0; i < size; i++) {
        //Inspect
        monkey->itemsInspected++;

        Item* temp = monkey->items.front();
        monkey->items.pop();

        //Apply operation
        monkey->operation(*temp);

        //Stress relief - day 1
        /*temp->worryLevel /= 3;*/

        //Stress relief - day 2
        temp->worryLevel %= totalProduct;

        //Throw item
        if (temp->worryLevel % static_cast<unsigned long long>(monkey->divisor) == 0) {
            monkeys[monkey->throwToIfTrue]->items.push(temp);
        }
        else {
            monkeys[monkey->throwToIfFalse]->items.push(temp);
        }
    }
}

int main()
{   
    std::vector<Monkey*> monkeys;


    std::ifstream iFile;
    iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
    if (iFile.fail()) {
        std::cerr << "File not found\n";
    }
    else
    {
        std::string input;
        std::string items;
        std::string funct;
        std::string testD;
        std::string testT;
        std::string testF;

        while (std::getline(iFile, input)) {
            //Get rest of input
            std::getline(iFile, items);
            std::getline(iFile, funct);
            std::getline(iFile, testD);
            std::getline(iFile, testT);
            std::getline(iFile, testF);

            //Initialize new monkey
            Monkey* monkey = new Monkey();

            //Get items
            std::string temp = "";
            for (auto c : items) {
                if (isdigit(c)) {
                    temp += c;
                }
                else
                {
                    if (!temp.empty()) {
                        Item* item = new Item(std::stoi(temp));
                        monkey->items.push(item);
                    }
                    temp = "";
                }
            }
            Item* item = new Item(std::stoi(temp));
            monkey->items.push(item);


            //Get operation
            bool old = false;
            int operand = 0;

            funct = funct.substr(19, funct.size() - 1);
            char math = funct[4];
            funct = funct.substr(6, funct.size() - 1);

            funct == "old" ? old = true : operand = std::stoi(funct);

            monkey->operation = [&monkey,math,operand,old](Item& item) {
                switch (math)
                {
                case '+':
                    old ? item.worryLevel += item.worryLevel : item.worryLevel += static_cast<unsigned long long>(operand);
                    break;
                case '-':
                    old ? item.worryLevel -= item.worryLevel : item.worryLevel -= static_cast<unsigned long long>(operand);
                    break;
                case '*':
                    old ? item.worryLevel *= item.worryLevel : item.worryLevel *= static_cast<unsigned long long>(operand);
                    break;
                case '/':
                    old ? item.worryLevel /= item.worryLevel : item.worryLevel /= static_cast<unsigned long long>(operand);
                    break;
                default:
                    std::cerr << "Invalid operator" << std::endl;
                    break;
                }
            };

            //Get divisor
            temp = "";
            for (auto c : testD) {
                if (isdigit(c)) {
                    temp += c;
                }
            }
            monkey->divisor = std::stoi(temp);

            //Get monkey receiver for true
            temp = "";
            for (auto c : testT) {
                if (isdigit(c)) {
                    temp += c;
                }
            }
            monkey->throwToIfTrue = std::stoi(temp);

            //Get monkey receiver for false
            temp = "";
            for (auto c : testF) {
                if (isdigit(c)) {
                    temp += c;
                }
            }
            monkey->throwToIfFalse = std::stoi(temp);

            monkeys.push_back(monkey);
            std::getline(iFile,input);
        }
    }
    iFile.close();


    //Get product of every monkeys divisor(for day 2)
    int totalProduct = 1;
    for (auto m : monkeys) {
        totalProduct *= m->divisor;
    }


    int numRounds = 10000;

    for (int i = 0; i < numRounds; i++) {
        for (auto m : monkeys) {
            Play(m, monkeys,totalProduct);
        }

        //Display worry levels and items inspected
        if ((i + 1) % 1000 == 0 /*|| (i + 1) % 20 == 0*/ || i == 0) {
            std::cout << "\n===== After round " << i + 1 << " =====" << std::endl;
            int k = 0;
            //for (auto m : monkeys) {
            //    std::cout << "Monkey " << k << ":";
            //    k++;
            //    std::queue<Item*> temp = m->items;
            //    int size = temp.size();
            //    for (int j = 0; j < size; j++) {
            //        std::cout << " " << temp.front()->worryLevel;
            //        temp.pop();
            //    }
            //    std::cout << "\n";
            //}

            for (auto m : monkeys) {
                std::cout << "Monkey " << k << " inspected items " << m->itemsInspected << " times." << std::endl;
                k++;
            }

        }
    }

    //Find 2 max values 
    unsigned long long max = 0;
    unsigned long long max2 = 0;
    std::cout << "\n\n";
    int i = 0;
    for (auto m : monkeys) {
        if (m->itemsInspected >= max) {
            max2 = max;
            max = m->itemsInspected;
        }
        else if (m->itemsInspected >= max2) {
            max2 = m->itemsInspected;
        }
        std::cout << "Monkey " << i << " inspected items " << m->itemsInspected <<" times." << std::endl;
        i++;
    }

    //Calculate monkey business
    unsigned long long monkeyBusiness = max * max2;

    std::cout << "\nThere was: " << monkeyBusiness << " monkey business" << std::endl;

    return 0;
}
