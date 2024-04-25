#define RANGE_MAX 1e10

#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-6;
typedef pair<double, double> point;
class line
{
    // y=ax-b
public:
    double a, b;
    line(double _a, double _b) : a(_a), b(_b) {}
    double gety(double x)
    {
        return x * a - b;
    }
    bool operator==(const line &y) const
    {
        return a == y.a && b == y.b;
    }
};
inline double getx(const line &_l1, const line &_l2)
{
    if (fabs(_l1.a - _l2.a) < 1e-5)
        return RANGE_MAX;
    return (double)(_l1.b - _l2.b) / (_l1.a - _l2.a);
}
vector<line> lines;
int main()
{
    ifstream fin("data.in");
    ofstream fout("!klevelbf.out");
    fin.ignore(numeric_limits<streamsize>::max(), '\n');
    int n,k;
    fin >> n >>k;
    vector<int> res;
    double a, b;
    for (int i = 0; i < n; i++)
    {
        fin >> a >> b;
        lines.push_back(line(a, b));
    }
    double t = -1e10;
    vector<int> idxs(n);
    for (int i = 0; i < n; i++)
        idxs[i] = i;
    sort(idxs.begin(), idxs.end(), [&](int a, int b)
         { return lines[a].gety(t + eps) > lines[b].gety(t + eps); });
    fout << idxs[k - 1] << endl;
    int top = idxs[k - 1];
    while (1)
    {
        double tt = 1e10;
        int nxt = -1;
        for (int i = 0; i < n; i++)
        {
            if (i == top)
                continue;
            double x = getx(lines[i], lines[top]);
            if (x > t && x < tt)
            {
                nxt = i;
                tt = x;
            }
        }
        if (nxt == -1)
            break;
        fout << nxt << '\n';
        top = nxt;
        t = tt;
    }
}
