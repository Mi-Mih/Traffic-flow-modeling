#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<vector<int> > map;
    string line;
    ifstream in("C:/Users/miham/source/repos/traffic/input.txt");
    for (int i = 0; getline(in, line); i++) {
        vector<int> vec; //создаем одномерный вектор
        for (int j = 0; j < line.size(); j++) {
            vec.push_back( line[j] -'0');
        }
        map.push_back(vec);
    }
    in.close();
    int row = map[0].size();
    int column = map[1].size();

    return 0;
}
