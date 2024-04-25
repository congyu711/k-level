#include<bits/stdc++.h>
using namespace std;

int main(int argc, char **argv)
{
    mt19937 gen(time(nullptr));
    if(argc<3)
    {
        cerr<<"./gen `NumberofLines` k\n";
    }
    const int n = atoi(argv[1]);
    const int k = atoi(argv[2]);
    ofstream fout("data.in");
    fout<<"/* format: a b ==> y=ax-b */\n";
    fout<<n<<' '<<k<<'\n';
    for(int i=0;i<n;i++)
    {
        fout<<gen()%20000000<<' '<<gen()%20000000<<'\n';
    }
}