#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    int m, n;
    cin >> m;
    cin >> n;

    map<string, char> table;

    for (int i = 0; i < m; ++i)
    {   
        string s1, s2;
        cin >> s1 >> s2;
        table[s2] = s1[0];
    }

    string c;
    cin >> c;
    
    string temp;
    for (int i = 0; i < c.length(); ++i)
    {   
        temp += c[i];
        if (table.count(temp))
        {
            cout << table[temp];
            temp = "";   
        }
    }

    return 0;
}
