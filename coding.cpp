#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;

class Node
{
public:
    int a;
    char c = '\0';
    Node *left = nullptr;
    Node *right = nullptr; 

    //переопределим конструктор для создания родителя
    Node (Node *L, Node *R)
    {
        left = L;
        right = R;
        a = L->a + R->a;
    }

    Node() {}
};

void BuildTable(Node *root, vector <bool> &code, map<char, vector<bool>> &table)
{   
    if (root->left)
    {
        code.push_back(0);
        BuildTable(root->left, code, table);
    }
    if (root->right)
    {
        code.push_back(1);
        BuildTable(root->right, code, table);
    }
    if (root->c)
    {
        if (code.empty())
        {
            code.push_back(0);
        }
        table[root->c] = code;
    }
    code.pop_back();
}

struct MyCompare
{
    bool operator () (Node *left, Node *right) const
    { return left->a < right->a; }
};


int main() {
    string s;
    getline(cin, s);

    //создаем словарь с частотами символов
    map<char, int> m;

    for (auto i: s) 
    {
        if (!m[i]) { m[i] = 1; }
        else { m[i]++; }
    }

    //создаем связный список с адресами узлов дерева
    list<Node*> lst;

    map<char, int>::iterator itr;
    for (itr = m.begin(); itr != m.end(); ++itr)
    {
        Node *ptr = new Node;
        ptr->a = itr->second; 
        ptr->c = itr->first;
        lst.push_back(ptr);
    }

    //создадим элементы бин дерева в цикле while
    while (lst.size() > 1)
    {
        lst.sort(MyCompare());

        Node *tmp_Left = lst.front();
        lst.pop_front();
        Node *tmp_Right = lst.front();
        lst.pop_front();

        Node *Parent = new Node(tmp_Left, tmp_Right);
        lst.push_back(Parent);
    }
    //оставшийся узел в списке lst - это корень дерева
    Node *root = lst.front();

    vector <bool> code;
    map<char, vector<bool>> table;

    BuildTable(root, code, table);

    cout << table.size() << " ";

    vector<bool> res;
    //распечатаем строку в кодированном виде
    for (int i = 0; i < s.length(); ++i)
    {
        char temp_c = s[i];
        vector<bool> temp_v = table[temp_c];

        for (auto x: temp_v)
        {
            res.push_back(x);
        }
    }
    cout << res.size() << endl;

    map<char, vector<bool>>::iterator map_itr;
    for (map_itr = table.begin(); map_itr != table.end(); ++map_itr)
    {   
        cout << map_itr->first << ": ";
        vector<bool> temp_v = map_itr->second;
        for (auto i: temp_v) 
        {
            cout << i;
        }
        cout << endl;
    }

    for (auto elem: res) { cout << elem; }

    return 0;
}
