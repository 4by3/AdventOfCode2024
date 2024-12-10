// 1 star

// Hashmap approach. I define hashmap when iterating through 2D array, then find unique location by checking
// antinode location is in bounds and if location doesn't have '#' in the original array.

#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>

using namespace std;

void parse(const string& input, vector<string>& arr)
{
    string line;
    int lineNum = 0;
    stringstream iss(input);
    while (getline(iss, line))
    {
        arr.push_back(line);
    }
}

int locations(vector<string> arr)
{
    int result = 0;

    unordered_map<char, vector<pair<int, int>>> hashmap;
    for (int i = 0; i < arr.size(); i++)
    {
        vector<int> temp;
        for (int j = 0; j < arr[i].length(); j++)
        {
            if (arr[i][j] != '.')
            {
                hashmap[arr[i][j]].push_back(make_pair(i, j));
            }
        }
        
    }


    // Values i and j here represent location 1 and location 2
    for (const auto& key : hashmap)
    {
        for (int i = 0; i < key.second.size(); i++)
        {
            for (int j = 0; j < key.second.size(); j++)
            {
                if (i != j)
                {
                    int verticalNode;
                    int horizontalNode;
                    if (key.second[i].first < key.second[j].first)
                    {
                        verticalNode = key.second[i].first - abs(key.second[i].first - key.second[j].first);
                    }
                    else
                    {
                        verticalNode = key.second[i].first + abs(key.second[i].first - key.second[j].first);
                    }
                    if (verticalNode < 0 || verticalNode >= arr.size())
                    {
                        continue;
                    }

                    if (key.second[i].second < key.second[j].second)
                    {
                        horizontalNode = key.second[i].second - abs(key.second[i].second - key.second[j].second);
                    }
                    else
                    {
                        horizontalNode = key.second[i].second + abs(key.second[i].second - key.second[j].second);
                    }
                    if (horizontalNode < 0 || horizontalNode >= arr[verticalNode].size())
                    {
                        continue;
                    }
                    if (arr[verticalNode][horizontalNode] != '#')
                    {
                        result++;
                        arr[verticalNode][horizontalNode] = '#';
                    }
                }
            }
        }
    }
    return result;
}

int main()
{
    string input = R"(....h.....Q..............Y........................
...............................Y........C.........
...............m..........x................B......
........................Y..............qB.........
......g4.........................h..Y.....q...c...
................n.....R...........................
.......................................w........5.
........g...m...........................w5........
..n...........R.1................W.......q.5......
.........h...n.................e..................
...............................R..........B....C..
.........4................................5.e.....
.......0..4......n.......x..w.....................
.......g.....m........x..b.....W.....B.......w....
..............m........................3......C...
........q...0.......h....................C.3......
..................3.....................D.........
...............R..........3.............X.........
..............................W............k2.....
..........7............................2..........
...............A.............................X...2
.......................c...x......................
....................................d.............
.....1......................d.....................
...........1...........................e..........
.........0.7K.........................2.........W.
...b......0.....A.................................
......................1....ic.....................
......b......................i....................
..Q.....b..........................A..E...........
...7.........................V....................
........A.....................v......d............
........v............c...................8E.......
..............................V........8.....E..N.
......................6...........................
.......I....M....................V................
...G......................a.......8...............
.........r.9........a...i..................X......
...............r..i...............e............N..
.....H...........k....9.....6...............8.....
.v.....................6................V.........
.........v.......a........k..........D............
Ha..........k.........K........E.......d..........
...............y.MG..............6....D...........
.........H..G...M......9.K..............N.........
.......G.........................K................
...............M.........I.......D................
..................................................
....r....y................9.......................
....y................................N............)";
    vector<string> arr;
    parse(input, arr);
    cout << "Number of antinodes: " << locations(arr) << endl;

    return 0;
}