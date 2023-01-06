#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int main()
{   
    std::vector<std::vector<int>> treeGrid;
    int total = 0;
    std::ifstream iFile;
    iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
    if (iFile.fail()) {
        std::cerr << "File not found\n";
    }
    else
    {
        int i = 0;
        std::string input;
        while (std::getline(iFile, input)) {
            std::vector<int> temp;
            for (auto c : input) {
                int num = c - 48;
                temp.push_back(c - 48);
            }
            treeGrid.push_back(temp);
        }
    }
    iFile.close();

    int highestLtr = -1;
    int highestRtl = -1;
    int highestUtd = -1;
    int highestDtu = -1;

    bool bLtrFound = false;
    bool bRtlFound = false;
    bool bUtdFound = false;
    bool bDtuFound = false;

    int rows = treeGrid.size();
    int cols = treeGrid[0].size();

    //Tree grid visible map
    std::vector<std::vector<int>> vTreeGrid;
    vTreeGrid.resize(rows, std::vector<int>(cols,4));

    //Tree grid scenic value
    std::vector<std::vector<int>> sTreeGrid;
    sTreeGrid.resize(rows, std::vector<int>(cols, 1));

    //Find visible trees
    for (int i = 0; i < rows; i++) {
        highestLtr = -1;
        highestRtl = -1;
        highestUtd = -1;
        highestDtu = -1;

        int hIndexLR = 0;
        int hIndexRL = 0;
        int hIndexUD = 0;
        int hIndexDU = 0;
        for (int j = 0; j < cols; j++) {
            


            int ltrX = i;
            int ltrY = j;

            int rtlX = i;
            int rtlY = cols - j - 1;

            int utdX = i;
            int utdY = j;

            int dtuX = i;
            int dtuY = cols - j - 1;

            //Left to right
            if (treeGrid[ltrX][ltrY] > highestLtr) {
                highestLtr = treeGrid[ltrX][ltrY];
                sTreeGrid[ltrX][ltrY] *= ltrY;
                hIndexLR = ltrY;
            }
            else if(treeGrid[ltrX][ltrY] == highestLtr) {
                vTreeGrid[ltrX][ltrY]--;
                sTreeGrid[ltrX][ltrY] *= ltrY - hIndexLR;
                hIndexLR = ltrY;
            }
            else{
                vTreeGrid[ltrX][ltrY]--;
                for (int k = ltrY - 1; k >= 0; k--) {
                    if (treeGrid[ltrX][ltrY] <= treeGrid[ltrX][k]) {
                        sTreeGrid[ltrX][ltrY] *= ltrY - k;
                        break;
                    }
                }
            }

            //Right to left
            if (treeGrid[rtlX][rtlY] > highestRtl) {
                highestRtl = treeGrid[rtlX][rtlY];
                sTreeGrid[rtlX][rtlY] *= abs(rtlY - (cols - 1));
                hIndexRL = rtlY;
            }
            else if (treeGrid[rtlX][rtlY] == highestRtl) {
                vTreeGrid[rtlX][rtlY]--;
                sTreeGrid[rtlX][rtlY] *= hIndexRL - rtlY;
                hIndexRL = rtlY;
            }
            else
            {
                vTreeGrid[rtlX][rtlY]--;
                for (int k = rtlY + 1; k < cols; k++) {
                    if (treeGrid[rtlX][rtlY] <= treeGrid[rtlX][k]) {
                        sTreeGrid[rtlX][rtlY] *= k - rtlY;
                        break;
                    }
                }
            }

            //Up to down
            if (treeGrid[utdY][utdX] > highestUtd) {
                highestUtd = treeGrid[utdY][utdX];
                sTreeGrid[utdY][utdX] *= utdY;
                hIndexUD = utdY;
            }
            else if (treeGrid[utdY][utdX] == highestUtd) {
                vTreeGrid[utdY][utdX]--;
                sTreeGrid[utdY][utdX] *= utdY - hIndexUD;
                hIndexUD = utdY;
            }
            else
            {
                vTreeGrid[utdY][utdX]--;
                for (int k = utdY - 1; k >= 0; k--) {
                    if (treeGrid[utdY][utdX] <= treeGrid[k][utdX]) {
                        sTreeGrid[utdY][utdX] *= utdY - k;
                        break;
                    }
                }
            }

            //Down to up
            if (treeGrid[dtuY][dtuX] > highestDtu) {
                highestDtu = treeGrid[dtuY][dtuX];
                sTreeGrid[dtuY][dtuX] *= abs(dtuY - (cols - 1));
                hIndexDU = dtuY;
            }
            else if (treeGrid[dtuY][dtuX] == highestDtu) {
                vTreeGrid[dtuY][dtuX]--;
                sTreeGrid[dtuY][dtuX] *= hIndexDU - dtuY;
                hIndexDU = dtuY;
            }
            else
            {
                vTreeGrid[dtuY][dtuX]--;
                for (int k = dtuY + 1; k < rows; k++) {
                    if (treeGrid[dtuY][dtuX] <= treeGrid[k][dtuX]) {
                        sTreeGrid[dtuY][dtuX] *= k - dtuY;
                        break;
                    }
                }
            }
        }
    }

    int totalVisible = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (vTreeGrid[i][j]) {
                totalVisible++;
            }
        }
    }

    int highestTree = 0;
    int hRow = 0;
    int hCol = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (sTreeGrid[i][j] > highestTree) {
                highestTree = sTreeGrid[i][j];
                hRow = i;
                hCol = j;
            }
        }
    }


    std::cout << "Visible trees: " << totalVisible << std::endl;
    std::cout << "The tree with the greatest coverage is located at: Row " << hRow + 1 << "," << " Col " << hCol + 1 << std::endl;
    std::cout << "Coverage: " << highestTree << std::endl;

    return 0;
}
