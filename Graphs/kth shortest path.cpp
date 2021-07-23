// https://cses.fi/problemset/task/1196
//  Also read Yen's Algorithm and Epstein's Algorithm

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define int long long
#define all(a) a.begin(), a.end()
#define pb push_back
#define pii pair<int, int>
#define vi vector<int>
#define pqb priority_queue<int>
#define FIO                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
template <typename T>
void print(vector<T> &a, int l, int u, string separator = " ")
{
    for (int i = l; i < u; i++)
        cout << a[i] << separator;
    cout << "\n";
}
template <typename T>
void print(vector<T> &a, string separator = " ") { print(a, 0, a.size(), separator); }
const int N = 1e5 + 10;
int n, m, k;
vector<pii> adj[N];
// best[i] stores the cost of the paths ending in i in sorted order and there are atmost k of them
pqb best[N];
// Time Complexity : O(mklog(mk))
signed main()
{
    FIO;
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({v, w});
    }
    best[1].push(0);
    // q stores the current {weight_till_now,node_we_came_from} in ascensing order
    priority_queue<pii, vector<pii>, greater<pii>> q;
    // push initial distance
    q.push({0, 1});
    while (!q.empty())
    {
        // get the shortest distance till now and the node we went to ,to get this distance
        auto [d, u] = q.top();
        q.pop();
        // if this distance is more than the largest distance in the best possible distances of u then continue
        if (d > best[u].top())
            continue;
        // otherwise this distance may yeild a better distance considering the nodes neighbouring to 'u'
        // v <- neighbouring node
        // w <- edge weight
        for (auto [v, w] : adj[u])
        {
            // the distance travelled to v
            int temp = d + w;
            // if the size of set of best distances is less than k then we can add this to the set and
            // also push the next {dst,node} pair into the q
            if (best[v].size() < k)
                best[v].push(temp), q.push({temp, v});
            // Now if the size of best is greater than k,
            // then only insert if the current distance is better than the largest distance in the queue
            else if (temp < best[v].top())
                best[v].pop(), best[v].push(temp), q.push({temp, v});
        }
    }
    vi ans;
    ans.reserve(best[n].size());
    while (!best[n].empty())
        ans.pb(best[n].top()), best[n].pop();
    reverse(all(ans));
    print(ans, " ");
    return 0;
}