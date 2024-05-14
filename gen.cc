#include<bits/stdc++.h>
using namespace std;

int main(int argc, char **argv)
{
    mt19937 gen;
    std::uniform_real_distribution<> dist(100, 20000000);
    std::uniform_real_distribution<> dist2(100, 20000);
    if(argc<3)
    {
        cerr<<"./gen `NumberofLines` k\n";
    }
    const int n = atoi(argv[1]);
    const int k = atoi(argv[2]);
    gen.seed(atoi(argv[3]));
    ofstream fout("data.in");
    fout<<"/* format: a b ==> y=ax-b */\n";
    fout<<n<<' '<<k<<'\n';
    for(int i=0;i<n;i++)
    {
        fout<< std::fixed << std::setprecision(10)<<dist(gen)<<' '<<dist2(gen)<<'\n';
    }
}