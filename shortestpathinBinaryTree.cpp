#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

template <typename T> class Tree
{
    struct Node
    {
        T data;
        Node* left;
        Node* right;
    };
    Node* root;
    int nodes(Node *r)
    {
        if(r == nullptr) return 0;
        return 1 + nodes(r->left) + nodes(r->right);
    }
    void destruct(Node* r, std::unordered_set<Node*>& visited) {
        if (r == nullptr || visited.count(r)) return;
        
        visited.insert(r);
        destruct(r->right, visited);
        destruct(r->left, visited);
        
        delete r;
    }
    vector<string> search(Node* node, const string &goal)
    {
        if (node == nullptr)
        {
            return {};
        }
        if (node->left == nullptr && node->right == nullptr && node->data != goal)
        {
            return {};
        }
        vector <string> s, r;
        if(node->data == goal)
        {
            s.push_back(node->data);
            return s;
        }
        
        s = search(node->left, goal);
        r = search(node->right, goal);
        if(s.size() == 0 && r.size() == 0)
            return {};
        for(int i = 0; i < s.size(); i++)
        {
            s[i] = node->data + " " + s[i];
        }
        for(int i = 0; i < r.size(); i++)
        {
            r[i] = node->data + " " + r[i];
            s.push_back(r[i]);
        }
        return s;
    }
public:
    Tree()
    {
        root = new Node("5");
        root->left = new Node("3");
        root->right = new Node("12");
        root->left->right = new Node("7");
        root->right->left = new Node("9");
        root->right->right = new Node("21");
        root->left->right->right = root->right->right;
        root->left->left = root->right->right;
    }
    
    int nodes()
    {
        return nodes(root) + 1;
    }
    
    ~Tree()
    {
        std::unordered_set<Node*> visited;
        destruct(root, visited);
        root = nullptr;
    }
    
    void search(const string &goal)
    {
        vector<string> s = search(root, goal);
        vector<int> indx;
        if(s.size() == 0)
        {
            cout << "Invalid input or unreachable member" << endl;
            return;
        }
        cout << "Current paths: " << endl;
        for(int i = 0; i < s.size(); i++)
        {
            cout << s[i] << endl;
        }
        cout << "Shortest Path: " << endl;
        unsigned long int ind = 0, size = s[0].size();
        for(int i = 1; i < s.size(); i++)
        {
            if(s[i].size() < size)
            {
                size = s[i].size();
                ind = i;
            }
        }
        cout << s[ind] << endl;
    }
};

int main()
{
    Tree<string> tr;
    cout << tr.nodes() << endl;
    tr.search("21");
}
