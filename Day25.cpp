#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

std::string ToSnafu(long long num);

int main()
{
    std::vector<long long> nums;
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
            long long temp = 0;
            for (int i = input.size() - 1; i >= 0 ; i--)
            {
                long long pos = input.size() - 1 - i;
                pos = static_cast<long long>(pow(5, pos));
                if (isdigit(input[i])) {
                    temp += (input[i] - 48) * pos;
                }
                else if (input[i] == '-') {
                    temp += (-1) * pos;
                }
                else if (input[i] == '=') {
                    temp += (-2) * pos;
                }
            }
            nums.push_back(temp);
        }

    }

    long long sum = 0;
    for (auto n : nums) {
        sum += n;
    }



    std::cout << std::left << std::setw(15) << "Sum (decimal): " << sum << std::endl;
    std::cout << std::left << std::setw(15) << "Sum (SNAFU): " << ToSnafu(sum) << std::endl;

    iFile.close();
    return 0;
}

std::string ToSnafu(long long num)
{
    std::string snafu = "";
    while (num > 0)
    {
        long long temp = num % 5;
        if (temp == 3) {
            snafu += "=";
            num += 2;
        }
        else if (temp == 4) {
            snafu += "-";
            num += 1;
        }
        else {
            snafu += std::to_string(temp);
        }
        num /= 5;
    }
    std::reverse(snafu.begin(), snafu.end());
    return snafu;
}
