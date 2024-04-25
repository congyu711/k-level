#include<bits/stdc++.h>
using namespace std;

#include"klevel.cc"
using kpq::line;

int main()
{
    vector<line<double>> lines;
    ifstream fin("data.in");
    ofstream fout("!klevelmain.out");
    fin.ignore(numeric_limits<streamsize>::max(), '\n');
    int n,k;
    fin >> n >> k;
    // int k=n*0.2;
    double a, b;
    for (int i = 0; i < n; i++)
    {
        fin >> a >> b;
        lines.push_back(line(a, b));
    }
    auto res = klevel::klevel(k,&lines);
    for(auto e:res)
    {
        fout<<e<<'\n';
    }
}