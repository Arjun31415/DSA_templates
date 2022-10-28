/**
 * @file hld.cpp
 * @author Arjun
 * @brief Heavy Light Decomposition on Trees
 * supporting path queries and updates.
 * Implemented using Segment Tree with lazy Propagation.
 * Working solution code for CSES Path Queries -II
 * https://cses.fi/problemset/task/2134/
 * @version 0.1
 * @date 2021-06-05
 *
 */

#include <iostream>
#include <math.h>
#include <vector>
#define int long long
#define lc(x) (x << 1)
#define rc(x) ((x << 1) | 1)
#define pb push_back
#define vi vector<int>
using namespace std;

#define debug
/**
 * @brief debugging helper functions
 *
 */
#ifdef debug
void tracearr(vi a)
{
	for (int i = 0; i < a.size(); i++)
	{
		cerr << i << "th index " << a[i] << endl;
	}
	cerr << endl;
}

void tracearr(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cerr << i << "th index " << a[i] << endl;
	}
	cerr << endl;
}
const int inf = INT64_MAX;
#define trace(x) cerr << #x << ": " << x << " " << endl;
#define trace3(x, y, z)                                                        \
	cerr << #x << ": " << x << " " << #y << ": " << y << " " << #z << ": "     \
		 << z << " " << endl;
#define trace2(x, y) cerr << #x << ": " << x << " " << #y << ": " << y << endl;
#else
void tracearr(int *a, int n) { return; }
void tracearr(vi a) { return; }
void trace2d(vector<vi> a) { return; }

#define trace(x)
#define trace3(x, y, z)
#define trace2(x, y)
#endif
// maximum number of nodes
const int N = 2e5 + 10;
// Log2(N)
const int LOGN = 20;

int U[N], V[N], W[N], baseArray[N], level[N], sub[N];
// stores the parent of the chain.
// For a heavy edge chainparent and chainhead will be the same.
// But for a light edge the chain parent will be the parent
// node and the chainhead will be the first node of the light chain
int chainParent[N];

// Stores the chainHead for each chain which is the first edge in that chain
int chainHead[N];

// buffer length. Used to find the maximum size of Basearray.
int blen = 1;

// Each chain is given a number.
// chainNo[i]--It stores the chain number for the ith node
int chainNo[N];

// stores the position in the linearized array for each node in the Tree.
int pos[N];

// the number of chains, both heavy and light in the tree
int nchain;

// U[i], V[i]-- represents a single edge i going from node U[i] to V[i]
// W[u]-- represents the node weight/value of the node j
vector<int> g[N];
// g[U[i]].push_back(i);
// g[V[i]].push_back(i);
/**
 * @brief finds the vertex on the opposite end of node x considering edge e
 *
 * @param x a node/vertex in the edge list
 * @param e edge number
 * @return the opposite vertex
 */
int adj(int x, int e)
{
	// returns node adjacent to x on the edge e.
	return x ^ U[e] ^ V[e];
}
// u is the node and ee is the edge which u came from
//  chainNo stores the which chain the node is part of
/**
 * @brief heavy light decomposition for an edge list graph
 *
 * @param u current node
 * @param ee parent edge ,i.e. edge number through which we came to u
 */
void HLD(int u, int ee)
{ // edge list graph.graph is 1-based.
	// uncomment the below line for edge weights in basearray
	// baseArray[blen] = W[ee];

	// this line is for node weights in basearray
	baseArray[blen] = W[u];
	pos[u] = blen;
	blen++;
	chainNo[u] = nchain;
	int sc = -1, mx = 0;
	for (auto e : g[u])
	{
		if (e == ee) continue;
		int w = adj(u, e);
		if (sub[w] > mx) sc = e, mx = sub[w];
	}
	if (sc == -1) return;
	HLD(adj(u, sc), sc);
	for (auto e : g[u])
	{
		if (e == ee || e == sc) continue;
		int w = adj(u, e);
		nchain++;
		chainParent[nchain] = u;
		chainHead[nchain] = w;
		HLD(w, e);
	}
}
vector<vi> parent;
vi out, in;
int tim = 0;
int l;

/**
 * @brief calulates the 2^j parent of each node in the tree.
 * ALWAYS call parent_calc(root,root)
 * otherwise it will mess up the parent array
 *
 * @param cur  current node
 * @param par parent node
 */
void parent_calc(int cur, int par)
{
	// int par;
	sub[cur] = 1;
	parent[cur][0] = par;
	level[cur] = level[par] + 1;
	in[cur] = (++tim);
	for (int i = 1; i <= l; i++)
	{

		int two_i_minus_1 = parent[cur][i - 1];
		parent.at(cur).at(i) = parent[(two_i_minus_1)][i - 1];
	}
	for (auto e : g[cur])
	{
		if (adj(cur, e) == par) continue;
		int w = adj(cur, e);
		parent_calc(w, cur);
		sub[cur] += sub[w];
	}
	out[cur] = (++tim);
}
/**
 * @brief literally what it says
 *
 * @param u first node
 * @param v second node
 * @return true when u is ancestor of v
 * @return false when u is not an ancestor of v
 */
bool is_first_anc_of_second(int u, int v)
{

	return in[u] <= in[v] && out[u] >= out[v];
}
/**
 * @brief finds the LCA using binary jumping in O(log2(N))
 *
 * @param u a node
 * @param v another node
 * @return int the LCA of u and v
 */
int find_lca(int u, int v)
{
	if (is_first_anc_of_second(u, v)) return u;

	if (is_first_anc_of_second(v, u)) return v;

	for (int i = l; i >= 0; --i)
		if (!is_first_anc_of_second(parent[u][i], v)) u = parent[u][i];
	return parent[u][0];
}
/**
 * @brief returns the distance between two nodes in the tree
 *
 * @param u a node
 * @param v another node
 * @return int the distance between u and v (no. of edges)
 */
int d(int u, int v)
{
	return (level[u] + level[v] - 2 * level[find_lca(u, v)]);
}

/**
 * @brief a structure to store data
 *
 */
struct Data
{

	// use required attributes here mn stores the answer and is intialized with
	// -inf because it is max queries
	int mn = -inf;

	// Default Values
	//  since max queries are to be done (on positive numbers) default value of
	//  mn is aasigned 0, but instead if min queries are to be done assign
	//  mn=INT_MAX. for other cases give appropriate values

	/**
	 * @brief Construct a new Data object with default value -inf f
	 *      or max queries. Give appropriate values for other types of queries
	 *
	 */
	Data() : mn(-inf){};
};

/**
 * @brief a 1 based indexed segment tree.
 *  N is the size of the base array a
 *
 */
struct SegTree
{
	// size of the base array
	int N;
	// segment tree
	vector<Data> st;
	// for lazy propagation
	vector<bool> cLazy;
	// value to be added
	vector<int> lazy;
	// base array a
	vector<int> a;
	void propagate(int node, int L, int R);
	void build(int node, int L, int R);
	void init(int n, vi a);
	/**
	 * @brief initialize the segment tree
	 *
	 * @param n is the size of the base array
	 */
	void init(int n)
	{
		N = n;
		st.resize(4 * N + 5);
		cLazy.assign(4 * N + 5, false);
		lazy.assign(4 * N + 5, 0);
	}

	void merge(Data &cur, Data &l, Data &r);
	/**
	 * @brief return the answer for the range [i,j]
	 *
	 * @param node the current node which is to be considered
	 * @param L the left limit of the node
	 * @param R the right limit of the node
	 * @param i the left limit of the Query
	 * @param j the right limit of the Query
	 * @return Data has the answer for the range [i,j]
	 */
	Data Query(int node, int L, int R, int i, int j)
	{
		if (cLazy[node]) propagate(node, L, R);
		if (j < L || i > R) return Data();
		if (i <= L && R <= j) return st[node];
		int M = (L + R) / 2;
		Data left = Query(lc(node), L, M, i, j);
		Data right = Query(rc(node), M + 1, R, i, j);
		Data cur;
		merge(cur, left, right);
		return cur;
	}

	/**
	 * @brief point query at position pos
	 *
	 * @param node the current node which is to be considered
	 * @param L the left limit of the node
	 * @param R the right limit of the node
	 * @param pos the postion at which the query is to be done
	 * @return Data having the result at postion pos
	 */
	Data pQuery(int node, int L, int R, int pos)
	{
		if (cLazy[node]) propagate(node, L, R);
		if (L == R) return st[node];
		int M = L + (R - L) / 2;
		if (pos <= M) return pQuery(lc(node), L, M, pos);
		else return pQuery(rc(node), M + 1, R, pos);
	}
	/**
	 * @brief range update using lazy propagation
	 *
	 * @param node
	 * @param node the current node which is to be considered
	 * @param L the left limit of the node
	 * @param R the right limit of the node
	 * @param i the left limit of the Query
	 * @param j the right limit of the Query
	 * @param val set a[k]+=val for k in the range [i,j]
	 */
	void Update(int node, int L, int R, int i, int j, int val)
	{
		if (cLazy[node]) propagate(node, L, R);
		if (j < L || i > R) return;
		if (i <= L && R <= j)
		{
			cLazy[node] = 1;
			lazy[node] += val;
			propagate(node, L, R);
			return;
		}
		int M = L + (R - L) / 2;
		Update(lc(node), L, M, i, j, val);
		Update(rc(node), M + 1, R, i, j, val);
		merge(st[node], st[lc(node)], st[rc(node)]);
	}

	/**
	 * @brief point update at position pos
	 *
	 * @param node the current node which is to be considered
	 * @param L the left limit of the node
	 * @param R the right limit of the node
	 * @param pos the postion at which the update is to be done
	 */
	void pUpdate(int node, int L, int R, int pos, int val)
	{
		if (cLazy[node]) propagate(node, L, R);
		if (L == R)
		{
			cLazy[node] = 1;
			lazy[node] = val;
			propagate(node, L, R);
			return;
		}
		int M = L + (R - L) / 2;
		if (pos <= M) pUpdate(lc(node), L, M, pos, val);
		else pUpdate(rc(node), M + 1, R, pos, val);
		merge(st[node], st[lc(node)], st[rc(node)]);
	}

	Data query(int pos);

	Data query(int l, int r);

	void update(int pos, int val);

	void update(int l, int r, int val);

} ST;
/**
 * @brief Handle lazy propagation appriopriately
 *
 * @param node node for which lazy propagation is to be updated/propagated
 * @param L  left range of the node
 * @param R  right range of the node
 */
void SegTree::propagate(int node, int L, int R)
{
	if (lazy[node] == 0) return;
	st[node].mn += lazy[node];
	if (L != R)
	{
		cLazy[lc(node)] = 1;
		cLazy[rc(node)] = 1;
		lazy[lc(node)] += lazy[node];
		lazy[rc(node)] += lazy[node];
	}

	cLazy[node] = 0;
	lazy[node] = 0;
}
/**
 * @brief Write required merge functions and write the result in cur
 *
 * @param cur stores the result
 * @param l operand 1
 * @param r operand 2
 */
void SegTree::merge(Data &cur, Data &l, Data &r) { cur.mn = max(l.mn, r.mn); }
/**
 * @brief build the segment tree recursively starting from node 'node'
 * st[node] stores the info in the range [L,R] in the base array a
 * @param node the node which is to be built
 * @param L the left limit of the node
 * @param R  the right limit of the node
 */

void SegTree::build(int node, int L, int R)
{
	if (L == R)
	{
		st[node].mn = a[L];
		return;
	}
	int M = L + (R - L) / 2;
	build(lc(node), L, M);
	build(rc(node), M + 1, R);
	merge(st[node], st[lc(node)], st[rc(node)]);
}

/**
 * @brief initalize the segment tree and also builds it
 *
 * @param n size of the base array
 * @param a the base array itself
 */

void SegTree::init(int n, vi a)
{
	init(n);
	this->a = std::move(a);
	build(1, 1, N);
}
/**
 * @brief point query
 *
 * @param pos position at which query is done
 * @return Data having the result
 */
Data SegTree::query(int pos) { return pQuery(1, 1, N, pos); }

/**
 * @brief range query
 *
 * @param l left limit of the Query
 * @param r  right limit of the Query
 * @return Data having the result in [l,r]
 */

Data SegTree::query(int l, int r) { return Query(1, 1, N, l, r); }
/**
 * @brief point update at pos and set a[pos]+=val
 *
 * @param pos position at which basearray is to be modified
 * @param val the value to be added at that position
 */
void SegTree::update(int pos, int val) { pUpdate(1, 1, N, pos, val); }

/**
 * @brief range update in [l,r]
 *
 * @param l left limit of the update
 * @param r right limit of the update
 * @param val value to be added to all elements in the range [l,r]
 */
void SegTree::update(int l, int r, int val) { Update(1, 1, N, l, r, val); }
/**
 * @brief Query ranging from node "from" to node "to"
 * where "to" is the ancestor of "from". returns the result for the
 * path from->to by querying the segment tree
 *
 * @param from a node in the tree
 * @param to another node in the tree and the ancestor of "from"
 *
 * @return int the result for this path
 */
int queryUp(int from, int to)
{
	int curr = from;
	int ans = 0;
	while (chainNo[curr] != chainNo[to])
	{
		if (pos[curr] == pos[chainHead[chainNo[curr]]])
			ans = max(ans, ST.query(pos[curr]).mn);
		else
			ans =
				max(ans, ST.query(pos[chainHead[chainNo[curr]]], pos[curr]).mn);
		curr = parent[chainHead[chainNo[curr]]][0];
	}
	ans = max(ans, ST.query(pos[to], pos[curr]).mn);

	return ans;
}

/**
 * @brief returns the query for the path from a-->b by
 * querying the segment tree
 * @param a a node in the tree
 * @param b another node in the tree
 * @return int the result for the path a-->b
 */

int path_query(int a, int b)
{
	return max(queryUp(a, find_lca(a, b)), queryUp(b, find_lca(a, b)));
}

/**
 * @brief preprocess the required arrays and also initalize themselves
 * assignes parent,in and out default values.Calls the various functions
 * to populate the parent array, perform HLD and
 * initialize the segment tree
 *
 *
 * @param n number of nodes in the Tree
 */
void preprocess(int n)
{
	l = log2(n) + 2;
	parent.assign(n + 1, vi(2 + l, 0));

	in.resize(n + 1), out.resize(n + 1);
	parent_calc(1, 1);
	chainHead[nchain] = chainParent[nchain] = 1;
	HLD(1, 0);
	ST.init(blen - 1, vector<int>(baseArray, baseArray + blen));
}
/**
 * @brief main driver code
 *
 * @return int32_t exit code
 */
signed main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0), std::cout.tie(0);

	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
		cin >> W[i];
	for (int i = 1; i <= n - 1; i++)
	{
		cin >> U[i] >> V[i];
		g[U[i]].push_back(i);
		g[V[i]].push_back(i);
	}
	preprocess(n);
	// tracearr(baseArray, n + 1);
	while (q--)
	{
		int opt;
		cin >> opt;
		if (opt == 1)
		{

			int s, x;
			cin >> s >> x;
			ST.update(pos[s], x - W[s]);
			W[s] = x;
		}
		else
		{

			int a, b;
			cin >> a >> b;
			cout << path_query(a, b);
			cout << " ";
		}
	}
}
