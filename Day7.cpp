#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Node
{
    Node()  {}
    Node(int size, std::string name, Node* parent, bool bDir) : m_size(size),m_name(name),parent(parent),m_bDir(bDir) {}
    int m_size = 0;
    std::string m_name = "none";
    bool m_bDir = true;
    Node* parent = nullptr;
    std::vector<Node*> children;
};

int CalculateSizes(Node*);
int GetSum(Node*, int, int&);
void GetNodeToDelete(Node*, int, std::vector<Node*>&);

int main()
{
    Node* Root = new Node(0,"/",nullptr,true);


    int total = 0;
    std::ifstream iFile;
    iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
    if (iFile.fail()) {
        std::cerr << "File not found\n";
    }
    else
    {
        std::string input;
        Node* temp = Root;
        while (std::getline(iFile, input)) {
            std::string name = "";
            if (input[0] == '$') {
                if (input[2] == 'c') {
                    name = input.substr(5, input.size() - 1);
                    if (name == "..") {
                        temp = temp->parent;
                    }
                    else
                    {
                        for (auto n : temp->children) {
                            if (n->m_name == name) {
                                temp = n;
                            }
                        }
                    }
                }
                else if (input[2] == 'l') {
                  //Do nothing
                }
            }
            else
            {
                int size = 0;
                bool bDir = false;
                if (isdigit(input[0])) {
                    std::string temp = "";
                    for (int i = 0; i < input.size(); i++) {
                        if (isdigit(input[i])) {
                            temp += input[i];
                        }
                        else
                        {
                            size = std::stoi(temp);
                            name = input.substr(i + 1, input.size() - 1);
                            break;
                        }
                    }
                }
                else
                {
                    name = input.substr(4, input.size() - 1);
                    bDir = true;
                }
                Node* nNode = new Node(size, name,temp,bDir);
                temp->children.push_back(nNode);
            }
        }
    }
    iFile.close();


    //Traverse tree and get calculate size
    CalculateSizes(Root);


    //Day1
    int max = 100000;
    int sum = 0;
    GetSum(Root, max, sum);
    std::cout << "Sum of all directories with size greater than " << max << " is: " << sum << std::endl;


    //Day2
    int totalSpace = 70000000;
    int spaceNeeded = 30000000;
    int curSpace = totalSpace - Root->m_size;
    int toFree = spaceNeeded - curSpace;
    std::vector<Node*> candidates;
    GetNodeToDelete(Root, toFree, candidates);

    int min = INT_MAX;
    std::string dir = "none";
    for (auto n : candidates) {
        if (n->m_size <= min) {
            min = n->m_size;
            dir = n->m_name;
        }
    }
    std::cout << toFree << " bytes needed for update" << std::endl;
    std::cout << "Delete directory: " << dir << " to free up " << min << " bytes" << std::endl;

    return 0;
}

int CalculateSizes(Node* root)
{
    if (root->children.empty()) {
        return root->m_size;
    }
    else
    {
        for (auto n : root->children)
        {
            root->m_size += CalculateSizes(n);
        }
    }
    return root->m_size;
}

int GetSum(Node* root, int max, int& sum)
{
    if (root->children.empty()) {
        if (root->m_size <= max) {
            return root->m_size;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        for (auto n : root->children)
        {
            if (n->m_bDir) {
                sum += GetSum(n,max,sum);
            }
        }
    }
    if (root->m_size <= max) {
        return root->m_size;
    }
    else
    {
        return 0;
    }
}

void GetNodeToDelete(Node* root, int space, std::vector<Node*>& candidates)
{
    if (root->children.empty()) {
        if (root->m_size >= space) {
            candidates.push_back(root);
        }
    }
    else
    {
        for (auto n : root->children)
        {
            GetNodeToDelete(n, space, candidates);
            if (n->m_bDir && n->m_size >= space) {
                candidates.push_back(n);
            }
        }
    }
}
