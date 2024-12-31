// 1 star

// Part 2 doesn't take in consideration edge case of regions inside of region

// Program works by scanning through matrix and if it sees upper case letter, it calls recursive function which adds 
// 1 to area and then checks up, down, left, right. If boundary detected, add 1 to perimeter, if finds its value, 
// call recursive function, if finds lower case value, do nothing since it means it is already checked.

// Part 2 uses 2 pointer. Begins with 4 sides and increases by 2 if either left or right pointer deviates from starting
// position from the recursive call.

#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>

using namespace std;

void parse(const string& input, vector<string>& arr)
{
    string line;
    stringstream iss(input);
    while (getline(iss, line))
    {
        arr.push_back(line);
    }
}


// pair first is area, pair second is perimeter

pair<long long, long long> recursion(vector<string>& arr, int i, int j)
{
    char val = arr[i][j];
    arr[i][j] = val + 32;
    pair<long long, long long> result;
    result.first++;
    // scan region and calculate perimeter by counting edges
    // up
    if (i - 1 >= 0)
    {
        if (arr[i - 1][j] == val)
        {
            auto temp = recursion(arr, i - 1, j);
            result.first += temp.first;
            result.second += temp.second;
        }
        else if (arr[i - 1][j] != val + 32)
        {
            result.second++;
        }
    }
    else
    {
        result.second++;
    }
    // down
    if (i + 1 < arr.size())
    {
        if (arr[i + 1][j] == val)
        {
            auto temp = recursion(arr, i + 1, j);
            result.first += temp.first;
            result.second += temp.second;
        }
        else if (arr[i + 1][j] != val + 32)
        {
            result.second++;
        }
    }
    else
    {
        result.second++;
    }
    // left
    if (j - 1 >= 0)
    {
        if (arr[i][j - 1] == val)
        {
            auto temp = recursion(arr, i, j - 1);
            result.first += temp.first;
            result.second += temp.second;
        }
        else if (arr[i][j - 1] != val + 32)
        {
            result.second++;
        }
    }
    else
    {
        result.second++;
    }
    // right
    if (j + 1 < arr[i].size())
    {
        if (arr[i][j + 1] == val)
        {
            auto temp = recursion(arr, i, j + 1);
            result.first += temp.first;
            result.second += temp.second;
        }
        else if (arr[i][j + 1] != val + 32)
        {
            result.second++;
        }
    }
    else
    {
        result.second++;
    }
    return result;
}

long long price(vector<string> arr)
{
    long long result = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr[i].length(); j++)
        {
            // if unique val
            if (!islower(arr[i][j]))
            {
                pair<long long, long long> temp = recursion(arr, i, j);
                result += temp.first * temp.second;
            }
        }
    }
    return result;
}



// Part 2


pair<long long, long long> recursionV2(vector<string>& arr, int i, int left, int right)
{
    if (i >= arr.size())
    {
        return make_pair(0, 0);
    }
    char val = arr[i - 1][left] - 32;
    long long sides = 0;
    // left
    if (arr[i][left] != val)
    {
        while (arr[i][left] != val)
        {
            if (left == right)
            {
                return make_pair(0, 0);
            }
            left++;
        }
        sides += 2;
    }
    else if (left - 1 >= 0 && arr[i][left - 1] == val)
        {
            while (left - 1 >= 0 && arr[i][left - 1] == val)
            {
                left--;
            }
            sides += 2;
        }
    // right
    if (arr[i][right] != val)
    {
        while (arr[i][right] != val)
        {
            right--;
        }
        sides += 2;
    }
    else if (right + 1 < arr[i].length() && arr[i][right + 1] == val)
    {
        while (right + 1 < arr[i].length() && arr[i][right + 1] == val)
        {
            right++;
        }
        sides += 2;
    }

    long long area = 0;
    // make row lower case
    for (int k = left; k <= right; k++)
    {
        arr[i][k] = val + 32;
        area++;
    }

    auto temp = recursionV2(arr, i + 1, left, right);
    return make_pair(area + temp.first, sides + temp.second);
}


long long priceV2(vector<string> arr)
{
    long long result = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr[i].length(); j++)
        {
            // if unique key marked by upper case char
            if (!islower(arr[i][j]))
            {
                int left = j;
                char val = arr[i][j];
                long long area = 0;
                while (j < arr[i].length() && arr[i][j] == val)
                {
                    area++;
                    arr[i][j] = val + 32;
                    j++;
                }
                auto temp = recursionV2(arr, i + 1, left, j--);
                result += (temp.first + area) * (temp.second + 4);
            }
        }
    }
    return result;
}




int main()
{
    string input = R"(AAAAAA
AAABBA
AAABBA
ABBAAA
ABBAAA
AAAAAA)";
    vector<string> arr;
    parse(input, arr);
    cout << "Price of fencing: " << price(arr) << endl;
    cout << "Price of fencing version 2: " << priceV2(arr) << endl;
    return 0;
}