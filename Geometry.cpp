
#define _USE_MATH_DEFINES
#include <bits\stdc++.h>
#include <type_traits>
#include <utility>
#include <cmath>
using namespace std;
#define ss second
#define ff first
#define pb push_back
#define mp make_pair
typedef long long ll;
#define all(A) A.begin(), A.end()
#define trace(x) cerr << #x << ": " << x << " " << endl;
#define sign(x) (x > 0) - (x < 0)
#define epsilon 1e-9
template <typename T>
class Point
{
public:
	T x, y, z;

	Point()
	{
		x = y = z = 0;
	}
	Point(T x, T y, T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Point(T x, T y)
	{
		this->x = x;
		this->y = y;
		this->z = 0;
	}
	void setx(T x)
	{
		this->x = x;
	}
	void sety(T y)
	{
		this->y = y;
	}
	void setz(T z)
	{
		this->z = z;
	}
	void set(T x = 0, T y = 0, T z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Point operator*(T value)
	{
		return Point(x * value, y * value, z * value);
	}
	Point operator/(T value)
	{
		return Point(x / value, y / value, z / value);
	}

	Point operator+(const Point<T> &b)
	{
		return Point(this->x + b.x, this->y + b.y, this->z + b.z);
	}
	Point operator-(const Point<T> &b)
	{
		return Point(this->x - b.x, this->y - b.y, this->z - b.z);
	}
	T distance(const Point<T> &p)
	{
		return sqrt((this->x - p.x) * (this->x - p.x) + (this->y - p.y) * (this->y - p.y) + (this->z - p.z) * (this->z - p.z));
	}
	T slope2D()
	{
		return (this->y) / (this->x);
	}
	T slope2D(const Point<T> &other)
	{
		return (this->y - other.y) / (this->x - other.x);
	}
	T angle2D()
	{
		return arctan(this->slope2D());
	}
	void operator=(const Point<T> b)
	{
		this->x = b.x;
		this->y = b.y;
		this->z = b.z;
	}
	Point &operator+=(const Point<T> b)
	{
		return (*this = *this + b);
	}
	Point &operator-=(const Point<T> &b)
	{
		*this = *this - b;
		return *this;
	}
	Point &operator*=(T val)
	{
		*this = (*this) * val;
		return *this;
	}
	Point &operator/=(T val)
	{
		*this = (*this) / val;
		return *this;
	}
	bool operator==(const Point<T> &other)
	{
		if (std::is_floating_point<T>::value)
			return (abs(this->x - other.x) <= epsilon && abs(this->y - other.y) <= epsilon && abs(this->z - other.z) <= epsilon);
		return ((this->x == other.x) && (this->y == other.y) && (this->z == other.z));
	}
	bool operator!=(const Point<T> &other)
	{
		return (!(*this == other));
	}
	T modulus()
	{
		return abs(sqrt(x * x + y * y + z * z));
	}
	bool operator<(const Point<T> &b)
	{
		if (this->x == b.x)
			return this->y < b.y;
		else
			return this->x < b.x;
	}
};
template <typename T, char iterations = 3>
// calulates the inverse square root of a number,
// using fast inverse square root algorithm found in Quake III
inline T inv_sqrt(T x)
{
	static_assert(std::is_floating_point<T>::value, "T must be floating Point");
	static_assert(iterations >= 1 and iterations <= 5, "itarations must lie between [1 , 5] and must be integer values");
	typedef typename std::conditional<sizeof(T) == 8, std::int64_t, std::int32_t>::type Tint;
	T y = x;
	T x2 = y * 0.5;
	Tint i = *(Tint *)&y;
	i = (sizeof(T) == 8 ? 0x5fe6eb50c7b537a9 : 0x5f3759df) - (i >> 1);
	y = *(T *)&i;
	y = y * (1.5 - (x2 * y * y));
	if (iterations == 2)
		y = y * (1.5 - (x2 * y * y));
	if (iterations == 3)
		y = y * (1.5 - (x2 * y * y));
	if (iterations == 4)
		y = y * (1.5 - (x2 * y * y));
	if (iterations == 5)
		y = y * (1.5 - (x2 * y * y));
	return y;
}
double rad_to_deg(double val)
{
	return val * 180 / M_PI;
}
double deg_to_rad(double val)
{
	return val * M_PI / 180;
}
template <typename T>
T dot(Point<T> a, Point<T> b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
template <typename T>
float ang(Point<T> a, Point<T> b, bool deg = true)
{
	return (acos(dot(a, b) * inv_sqrt(dot(a, a) * dot(b, b))) * (deg == true ? 180 / M_PI : 1));
}
template <typename T>
Point<T> cross(Point<T> a, Point<T> b)
{
	T x0 = a.x, y0 = a.y, z0 = a.z;
	T x1 = b.x, y1 = b.y, z1 = b.z;
	// adding 0.00 to avoid -0 output
	return Point<T>(y0 * z1 - z0 * y1 + 0.00, z0 * x1 - x0 * z1 + 0.00, x0 * y1 - y0 * x1 + 0.00);
}
template <typename T>

int intersection(Point<T> p0, Point<T> p1, Point<T> p2, Point<T> p3, Point<T> &intx)
{
	/**
   *  @brief Return the intersection of two line segments .
   *  @param  p0  Start of first line segment.
   *  @param  p1   End of first line segment.
   *  @param  p2  Start of second line segment.
   *  @param  p3   End of second line segment.
   *  @param  intx  the intersection Point.
   *  @return  Returns 1 if the lines intersect,2 if lines are collinear,3 if lines are parallel,otherwise 0
   *  It is based on an algorithm in Andre LeMothe's "Tricks of the Windows Game Programming Gurus"
   *  the refrence Point will store null
   *  intx stores the intersection Point if it exists else
   *  will be intialized to null
  */
	double p0_x = p0.x, p0_y = p0.y;
	double p1_x = p1.x, p1_y = p1.y;
	double p2_x = p2.x, p2_y = p2.y;
	double p3_x = p3.x, p3_y = p3.y;
	double s1_x, s1_y, s2_x, s2_y;
	s1_x = p1_x - p0_x;
	s1_y = p1_y - p0_y;
	s2_x = p3_x - p2_x;
	s2_y = p3_y - p2_y;

	double s, t;
	double den = (-s2_x * s1_y + s1_x * s2_y);

	if (den == 0 or abs(den) <= epsilon)
	{

		// parallel or collinear lines
		// if they are collinear then their slope will be the same for any two pair of Points
		if (p0.slope2D(p1) == p1.slope2D(p2) && p2.slope2D(p3) == p3.slope2D(p0) && p1.slope2D(p0) == p0.slope2D(p3))
			return 2;
		return 3;
	}
	s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / den;
	t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / den;

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		// Collision detected
		intx.x = p0_x + (t * s1_x);
		intx.y = p0_y + (t * s1_y);

		return 1;
	}
	return 0; // No collision
}
template <typename T>
double signed_area_of_parallelogram(Point<T> a, Point<T> b, Point<T> c)
{
	return (cross(b - a, c - b).z);
}
template <typename T>
double area_of_triangle(Point<T> a, Point<T> b, Point<T> c)
{
	return abs(signed_area_of_parallelogram(a, b, c) * 0.5);
}
template <typename T>
int direction(Point<T> a, Point<T> b, Point<T> c)
{
	long long t = signed_area_of_parallelogram(a, b, c);
	return (sign(t));
}
template <typename T>
double area_of_polygon(Point<T> a[], int n)
{
	double area = 0;
	for (int i = 0; i < n; i++)
	{
		area -= (a[(i + 1) % n].x - a[i].x) * (a[(i + 1) % n].y + a[i].y);
		// i= n-1, a(0)->a(n-1)
	}
	area /= 2;
	return abs(area);
}
template <typename T>
double area_of_polygon(vector<Point<T>> a, int n = 0)
{
	if (n == 0)
		n = a.size();
	double area = 0;
	for (int i = 0; i < n; i++)
	{
		area -= (a.at((i + 1) % n).x - a.at(i).x) * (a.at((i + 1) % n).y + a[i].y);
		// i= n-1, a(0)->a(n-1)
	}
	area /= 2;
	return abs(area);
}
template <typename T>
// counterclockwise direction of Points and must be convex polygon
bool check_Point_in_polygon(Point<T> a[], int n, Point<T> p)
{
	// query time O(log n)
	int l = 1, r = n - 2;
	while (l < r)
	{
		int x = (l + r) / 2;
		if (direction(a[0], a[x + 1], p) == 1) // counterclockwise turn
			l = x + 1;
		else if (direction(a[0], a[x], a[p]) == -1)
			r = x - 1;
		else
		{
			//the Point lies between the vectors l and r
			l = r = x;
		}
	}
	if (area_of_triangle(a[0], a[l], a[+1]) == area_of_triangle(a[0], a[l], p) + area_of_triangle(a[l], a[l + 1], p) + area_of_triangle(a[l + 1]), a[0], a[p])
		return true;
	return false;
}
template <typename T>
vector<Point<T>> minkowski_sum(vector<Point<T>> a, vector<Point<T>> b, bool remove_redundant = true)
{
	int l = 0;
	int n = a.size();
	int m = b.size();
	for (int i = 0; i < n; i++)
	{
		if (a[i].x < a[l].x || (a[i].x == a[l].x && a[i].y < a[l].y))
			l = i;
	}
	int r = 0;
	for (int i = 0; i < n; i++)
	{
		if (b[i].x < b[l].x || (b[i].x == b[l].x && b[i].y < b[l].y))
			r = i;
	}
	vector<Point<T>> v;
	for (int i = 0; i < m + n; i++)
	{
		v.push_back(a[l] + b[r]);
		if (cross(a[(l + 1) % n] - a[l], b[(r + 1) % m] - b[r]).z > 0)
			l = (l + 1) % n;
		else
			r = (r + 1) % m;
	}
	if (!remove_redundant)
		return v;
	unordered_set<int> mark;

	for (int i = 0; i < n + m; i++)
	{
		if (direction(v[i], v[(i + 1) % (n + m)], v[(i + 2) % (n + m)]) == 0)
		{
			// redundant Point
			mark.insert((i + 1) % (n + m));
		}
	}

	vector<Point<T>> vv;

	for (int i = 0; i < n + m; i++)
	{
		if (!mark.count(i))
		{
			vv.push_back(v[i]);
		}
	}
	return vv;
}
template <typename T>
// remove the redundant Points present in a polygon represented by a vector<Point<T>>

// give n as -1 if you do not wish to give the size of the vector
vector<Point<T>> remove_redundant(vector<Point<T>> v, int n)
{
	unordered_set<int> mark;
	if (n == -1)
		int n = v.size();

	for (int i = 0; i < n; i++)
	{
		if (direction(v[i], v[(i + 1) % (n)], v[(i + 2) % (n)]) == 0)
		{
			// redundant Point
			mark.insert((i + 1) % (n));
		}
	}

	vector<Point<T>> vv;

	for (int i = 0; i < n; i++)
	{
		if (!mark.count(i))
		{
			vv.push_back(v[i]);
		}
	}
	return vv;
}
template <typename T>
int max_Points_in_circle(vector<Point<T>> v, double r)
{
	int n = v.size();
	int ans = 1;
	for (int i = 0; i < n; i++)
	{
		vector<pair<double, pair<bool, int>>> ang_enex_ind;
		//          angle        entry,index
		// false <- entry
		// true<- exist
		int cur = 1;
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				continue;
			else
			{
				double d = sqrt((double)dot(v[j] - v[i], v[j] - v[i]));
				if (d > 2 * r)
					continue;
				double ang1 = atan(((double)(v[j] - v[i]).y) / (double)(v[j] - v[i]).x);
				if ((v[j] - v[i]).x < 0)
					ang1 += M_PI;
				double ang2 = acos(d / (2 * r));
				double ang_entry = (8 * M_PI + ang1 - ang2);
				ang_entry -= 2 * M_PI * floor(ang_entry / (2 * M_PI));
				double ang_exit = (8 * M_PI + ang1 + ang2);
				ang_exit -= 2 * M_PI * floor(ang_exit / (2 * M_PI));
				if (ang_exit < ang_entry)
					cur++;
				ang_enex_ind.pb(mp(ang_entry, mp(false, j)));
				ang_enex_ind.pb(mp(ang_exit, mp(true, j)));
			}
		}
		sort(all(ang_enex_ind));
		for (auto it : ang_enex_ind)
		{
			ans = max(ans, cur);
			if (it.ss.ff == false)
				cur++;
			else
				cur--;
			ans = max(ans, cur);
		}
	}
	return ans;
}
template <typename T>
vector<Point<T>> convex_hull_jarvis_march(vector<Point<T>> a)
{
	int n = a.size();
	if (n <= 2)
		return a;
	int start = 0;
	// getting the leftmost bottom most Point
	for (int i = 1; i < n; i++)
	{
		if (a[i].x < a[start].x || (a[i].x == a[start].x && a[i].y < a[start].y))
			start = i;
	}
	vector<Point<T>> ans;
	ans.pb(a[start]);
	while (420)
	{
		int pt = 0;
		for (int i = 0; i < n; i++)
		{
			if (a[i] == ans.back())
				continue;
			if ((direction(ans.back(), a[pt], a[i]) == -1) or
				(direction(ans.back(), a[pt], a[i]) == 0 and
				 (dot(a[i] - ans.back(), a[i] - ans.back()) >
				  dot(a[pt] - ans.back(), a[i] - ans.back()))))
			{
				pt = i;
			}
		}
		if (a[pt] == ans.front())
			break;
		else
			ans.push_back(a[pt]);
	}
	return ans;
}
static Point<int> polar_angle_Point;
template <typename T>
bool cmp(const Point<T> &a, const Point<T> &b)
{
	if (direction(polar_angle_Point, a, b) == 1)
		return true;
	else if (direction(polar_angle_Point, a, b) == -1)
		return 0;
	else
		return (dot(polar_angle_Point - a, polar_angle_Point - a) <
				dot(polar_angle_Point - b, polar_angle_Point - b));
}
template <typename T>
vector<Point<T>> convex_hull_graham_scan(vector<Point<T>> a)
{
	int n = a.size();
	if (n <= 2)
		return a;
	// store the leftmost bottommost Point in a[0]
	for (int i = 1; i < n; i++)
	{
		if (a[i].x < a[0].x || (a[i].x == a[0].x && a[i].y < a[0].y))
			swap(a[i], a[0]);
	}
	polar_angle_Point = a[0];
	sort(a.begin() + 1, a.end(), cmp<T>);
	vector<Point<T>> ans;
	ans.push_back(a[0]);
	ans.pb(a[1]);
	for (int i = 2; i < n; i++)
	{
		while (direction(ans[(int)ans.size() - 2],
						 ans[(int)ans.size() - 1],
						 a[i]) != 1)
			ans.pop_back();
		ans.push_back(a[i]);
	}
	return ans;
}
// using rotating callipers
template <typename T>
int diameter_of_convex_hull(vector<Point<T>> v)
{
	int n = v.size();
	int pt1 = 0, pt2 = 1;
	while (cross(v[(pt1 + 1) % n] - v[pt1], v[(pt2 + 1) % n] - v[pt2]).z > 0)
	{
		pt2++;
		pt2 %= n;
	}
	// now pt1 and pt2 are parallel to each other
	// pt1 and pt2 are on antipodal Points
	// use appropriate distance formulae for calculation
	ll ans = abs(v[pt2].y - v[pt1].y);
	ll st1 = pt1, st2 = pt2;
	//trace2(pt1, pt2);
	do
	{
		if (cross(v[(pt1 + 1) % n] - v[pt1], v[(pt2 + 1) % n] - v[pt2]).z > 0)
		{
			pt2++;
			pt2 %= n;
		}
		else
		{
			pt1++;
			pt1 %= n;
		}
		// use appropriate distance formulae for calculation
		ans = max(ans, abs(v[pt1].y - v[pt2].y));
		//trace2(pt1, pt2);
		//trace2((st1 != pt1), (st2 != pt2));
	} while (st1 != pt1 || st2 != pt2);
	cerr << endl;
	return ans;
}
// line sweep
template <typename T>
class DS
{

public:
	set<Point<T>> st;
	priority_queue<Point<T>> hp;
	long long d;
	bool ins(Point<T> a)
	{
		hp.push(Point<T>(-a.x, a.y));
		st.insert(Point<T>(a.y, a.x));
		return true;
	}
	bool del(Point<T> a)
	{
		while (-hp.top().x < a.x - d)
		{
			auto it = st.find(Point<T>(hp.top().y, -hp.top().x));
			st.erase(it);
			hp.pop();
		}
		return true;
	}
	vector<Point<T>> query(Point<T> a)
	{
		auto it = st.lower_bound(Point<T>(a.y - d, 0));
		auto end = st.upper_bound(Point<T>(a.y + d, 0));
		vector<Point<T>> ans;
		while (it != end)
		{
			ans.push_back(Point<T>((*it).y, (*it).x));
		}
		return ans;
	}
};
int main()
{
	int n, m;
	cin >> n >> m;

	vector<Point<int>> a(n), b(m);
	for (int i = 0; i < n; i++)
	{
		cin >> a[i].x >> a[i].y;
	}
	for (int i = 0; i < m; i++)
	{
		cin >> b[i].x >> b[i].y;
	}
	auto v = minkowski_sum(a, b, true);
	cout << "\n";

	for (auto &vv : v)
	{
		cout << vv.x << " " << vv.y << endl;
	}
}