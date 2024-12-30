// 2 stars

// Originally went with using vector, then recursion and then hashmap for part 2 to save memory.

#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>

using namespace std;

void parse(const string& input, unordered_map<string, long long>& dict)
{
    string num;
    stringstream iss(input);
    while (iss >> num)
    {
        dict[num] += 1;
    }
}

long long stones(unordered_map<string, long long>& dict, int blinks)
{
    while (blinks > 0)
    {
        unordered_map<string, long long> currentDict;
        for (auto& pair : dict)
        {
            if (pair.first == "0")
            {
                currentDict["1"] += pair.second;
            }
            else if (pair.first.length() % 2 == 0)
            {
                string first = pair.first.substr(0, pair.first.length() / 2);
                string last = pair.first.substr(pair.first.length() / 2);
                // remove 0s infront of val
                last = to_string(stoll(last));
                currentDict[first] += pair.second;
                currentDict[last] += pair.second;
            }
            else
            {
                currentDict[to_string(stoll(pair.first) * 2024)] += pair.second;
            }
        }
        dict = currentDict;
        blinks--;
    }
    long long result = 0;
    for (auto& pair : dict)
    {
        result += pair.second;
    }
    return result;
}

/*
long long stonesRecursion(string num, int blinks)
{
    if (blinks == 0)
    {
        return 1;
    }
    if (num == "0")
    {
        return stonesRecursion("1", blinks - 1);
    }
    if (num.length() % 2 == 0)
    {
        string first = num.substr(0, num.length() / 2);
        string last = num.substr(num.length() / 2);
        last = to_string(stoll(last));
        return stonesRecursion(first, blinks - 1) + stonesRecursion(last, blinks - 1);
    }
    return stonesRecursion(to_string(stoll(num) * 2024), blinks - 1);
}

long long stones(vector<string>& dict, int blinks)
{
    long long result = 0;
    for (string num : dict)
    {
        result += stonesRecursion(num, blinks);
    }
    return result;
}

*/


int main()
{
    string input = "0 7 6618216 26481 885 42 202642 8791";
    unordered_map<string, long long> dict;
    parse(input, dict);
    cout << "Number of stones: " << stones(dict, 75) << endl;

    return 0;
}