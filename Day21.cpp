#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct Monkey {
    std::string name = "none";
    long long value = 0;
    std::string leftName = "none";
    std::string rightName = "none";
    char operation = '0';
    Monkey* left = nullptr;
    Monkey* right = nullptr;
};


void ConnectMonkeys(Monkey* root, std::vector<Monkey*> monkeys);
long long Calculate(Monkey* root);
int count = 0;
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
        while (std::getline(iFile, input)) {
            Monkey* temp = new Monkey;
            temp->name = input.substr(0, 4);
            if (isdigit(input[6])) {
                temp->value = static_cast<long long>( std::stoi( input.substr(6, input.size()) ) );
            }
            else
            {
                temp->leftName = input.substr(6, 4);
                temp->rightName = input.substr(13, 4);
                temp->operation = input[11];
            }
            monkeys.push_back(temp);
        }
    }

    Monkey* root = nullptr;
    for (auto m : monkeys) {
        if (m->name == "root") {
            root = m;
            break;
        }
    }
    if (root != nullptr) {
        ConnectMonkeys(root, monkeys);
        Calculate(root);
        std::cout << "Value: " << root->value << std::endl;
    }

    iFile.close();
    return 0;
}

void ConnectMonkeys(Monkey* root, std::vector<Monkey*> monkeys)
{
    if (root->value != 0) {
        return;
    }
    else
    {
        for (auto m : monkeys) {
            if (root->leftName == m->name) {
                root->left = m;
                ConnectMonkeys(m, monkeys);
            }
            if (root->rightName == m->name) {
                root->right = m;
                ConnectMonkeys(m, monkeys);
            }
        }
    }
}

long long Calculate(Monkey* root)
{





    if (root->value != 0) {
        return root->value;
    }
    else
    {
        long long leftOp = Calculate(root->left);
        long long rightOp = Calculate(root->right);
        if (leftOp < 0) {
            int hmm = 0;
        }
        if (rightOp < 0) {
            int hmm = 0;
        }
        switch (root->operation)
        {
        case '+':
            root->value = leftOp + rightOp;
            break;
        case '-':
            root->value = leftOp - rightOp;
            break;
        case '*':
            root->value = leftOp * rightOp;
            break;
        case '/':
            root->value = leftOp / rightOp;
            break;
        case '=':
            //
            break;
        default:
            std::cerr << "Error!\n";
            break;
        }
        
    }
}
