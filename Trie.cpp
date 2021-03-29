//List of Problems - https : //leetcode.com/list/xysqsyp7/s

#include <stdlib.h>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

namespace stringTrie
{
    class Node
    {

    public:
        Node *children[26] = {};
        // end tells us that whether at this node a string has been completed or not
        bool end;

        //cnt variable at each node is keeping a count of
        //strings which passes through that node while
        //inserting the string into trie.

        //A string is being added into this trie character by character
        //So, lets say the character representation at a node from
        //root of the trie to that node is abc (I.e.node is at level 3),
        //so cnt at this node will give the no of strings which have
        //prefix charcters representation as abc like the nos with
        //charcters representation abcdef...., abcff......, abceeghx.... Etc.

        int cnt;
        Node()
        {
            end = 0, cnt = 0;
        }
    };
    class Trie
    {
        Node *root;

    public:
        Trie()
        {
            root = new Node();
        }
        Trie(vector<string> &a)
        {
            insert(a);
        }
        void insert(string &s)
        {
            Node *cur = root;
            for (char &c : s)
            {
                if (!cur->children[c - 'a'])
                {
                    cur->children[c - 'a'] = new Node();
                }
                cur = cur->children[c - 'a'];
                cur->cnt++;
            }
            cur->end = true;
        }
        void insert(vector<string> &a)
        {
            for (string s : a)
                insert(s);
        }
        void remove(string &x)
        {
            Node *cur = root;
            for (char &c : x)
            {
                cur = cur->children[c - 'a'];
                cur->cnt--;
            }
            cur->end = false;
        }
        void remove(vector<string> &s)
        {
            for (auto &x : s)
                remove(x);
        }
        bool found(string &s)
        {
            Node *cur = root;
            for (char c : s)
            {
                if (!cur->children[c - 'a'])
                    return 0;
                cur = cur->children[c - 'a'];
            }
            return cur->end;
        }
    };
}

/* How to use -
    Trie *t=new Trie({"sidhosd","sdfhgdfh"});
    bool k=t->find("sidhosd")

*/
// problems -
// 1.https://leetcode.com/problems/word-search-ii/ requires Trie and dfs

namespace intTrie
{
    class Node
    {

    public:
        Node *children[2] = {};
        bool end;

        // cnt variable at each node is keeping a count of integers
        // which passes through that node while inserting the integer
        // into trie.An integer is being added into this trie based
        // on its bit representation.So, lets say the bit representation
        // at a node from root of the trie to that node is 101(I.e.node is at level 3),
        // so cnt at this node will give the no of integers which have prefix bit
        // representation as 101 like the nos with bit representation
        // 10101...., 10111......, 1010000.... Etc.

        int cnt;
        Node()
        {
            end = 0, cnt = 0;
        }
    };
    class Trie
    {
        Node *root;
        int bits;

    public:
        Trie()
        {
            root = new Node();
            bits = 31;
        }
        Trie(vector<int> &a)
        {
            root = new Node();
            insert(a);
        }
        Trie(vector<int> &a, int bits)
        {
            this->bits = bits;
            root = new Node();
            insert(a);
        }
        void set_no_bits(int a)
        {
            bits = a;
        }
        void insert(int &x)
        {
            Node *cur = root;
            for (int i = bits; i >= 0; i--)
            {
                bool b = (x >> i) & 1;
                if (!cur->children[b])
                {
                    cur->children[b] = new Node();
                }
                cur = cur->children[b];
                cur->cnt++;
            }
            cur->end = true;
        }
        void insert(vector<int> &a)
        {
            for (auto s : a)
                insert(s);
        }
        void remove(int &x)
        {
            Node *cur = root;
            for (int i = bits; i >= 0; i--)
            {
                bool b = (x >> i) & 1;
                cur = cur->children[b];
                cur->cnt--;
            }
            cur->end = false;
        }
        void remove(vector<int> &s)
        {
            for (auto &x : s)
                remove(x);
        }
        bool found(int &s)
        {
            Node *cur = root;
            for (int i = bits; i >= 0; i--)
            {
                bool b = (s >> i) & 1;
                if (!cur->children[b])
                    return 0;
                cur = cur->children[b];
            }
            return cur->end;
        }
        int maxxor(int x)
        {
            Node *cur = root;
            unsigned int ans = 0;
            for (int i = bits; i >= 0; i--)
            {
                bool b = (x >> i) & 1;
                if (cur->children[!b] and cur->children[!b]->cnt > 0)
                {
                    ans += (1LL << i);
                    cur = cur->children[!b];
                }
                else
                    cur = cur->children[b];
            }
            return ans;
        }
        int maxxor(vector<int> &s)
        {
            int ans = -1;
            for (auto x : s)
                ans = max(ans, maxxor(x));

            return ans;
        }
    };
    // problems-
    // 1.https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/
    // 2.http://codeforces.com/contest/706/problem/D
}