#include<bits/stdc++.h>
using namespace std;

#include"klevel.cc"
using kpq::line;

int main()
{
    vector<line> lines;
    ofstream fout("!klevelmain.out");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int n;
    cin >> n;
    // int k=n*0.2;
    double a, b;
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b;
        lines.push_back(line(a, b));
    }
    auto res = klevel::klevel(20,&lines);
    for(auto e:res)
    {
        // fout<<e.first<<' ';
        // fout<<" y="<<lines[e.second].a<<"x-"<<lines[e.second].b<<'\n';
        fout<<e<<'\n';
    }
}