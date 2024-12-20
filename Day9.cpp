// Not getting correct output...

#include <iostream>
#include <optional>
#include <vector>

using namespace std;


long long freeSpace(string input)
{
    long long result = 0;
    while (input.length() != 0)
    {
        // parse and transform
        vector<optional<int>> arr;
        int i = 0;
        while (i < 19 && i != input.length())
        {
            int block = i / 2;
            if (i % 2 == 0)
            {
                for (int p = int(input[i] - '0'); p != 0; p--)
                {
                    arr.push_back(block);
                }
            }
            else
            {
                for (int p = int(input[i] - '0'); p != 0; p--)
                {
                    arr.push_back(nullopt);
                }
            }
            i++;
        }

        // move file blocks
        int l = 0;
        while (l < arr.size())
        {
            if (arr[l].has_value())
            {
                l++;
            }
            else
            {
                // pop nullopt
                while (!arr.back().has_value())
                {
                    arr.pop_back();
                }
                if (l != arr.size())
                {
                    arr[l] = arr.back();
                    arr.pop_back();
                }
            }
        }
        // compact
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i].has_value()) {
                result += i * arr[i].value();
            }
        }

        // next input
        input.erase(0, i);  
    }     
    return result; 
}


int main()
{
    string input = "2333133121414131402331";

    cout << "Filesystem checksum: " << freeSpace(input) << endl;

    return 0;
}