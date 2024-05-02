#include <iostream>
#include <set>
#include <random>
#include <map>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

struct Djset{
	int djset[1003];
    Djset(int n){
        for(int i=1;i<=n;i++){
            djset[i] = -1;
        }
    }
    int find(int x){
        if(djset[x] < 0){
            return x;
        }
        djset[x] = find(djset[x]);
        return djset[x];
    }
    bool combine(int a, int b){
        a = find(a);
        b = find(b);
        if(a == b) return false;
        if(djset[a] > djset[b]){
            swap(a, b);
        }
        djset[a] += djset[b];
        djset[b] = a;
        return true;
    }
};

vector<pair<int, int>> v;

void build(int n){
    v.clear();
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            v.emplace_back(i, j);
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(v.begin(), v.end(), g);

}

int f(int n){

    Djset dj(n);
    int com = n;
    int edge_id = 0;

    while(n > 1){
        auto e = v[edge_id++];
        n -= dj.combine(e.first, e.second);
    }
    return edge_id;
}

int g(int n){
    vector<bool> vis(n, 0);

    int com = n;
    int edge_id = 0;

    while(n != 0){
        auto e = v[edge_id++];
        if(vis[e.first] == 0){
            n--;
            vis[e.first] = 1;
        }
        if(vis[e.second] == 0){
            n--;
            vis[e.second] = 1;
        }
    }
    return edge_id;
}


int main(){
    map<int, double> res;
    map<int, double> res2;
    for(int j=0;j<100;j++){
        for(int i=100;i<=1000;i+=100){
            build(i);
            res[i] += f(i);
            res2[i] += g(i);
            /*if(j % 10 == 0){
                cout<<i<<"\t"<<res[i]<<"\t"<<res2[i]<<'\n';
            }*/
        }
    }
    cout<<"i\tf(i)\tg(i)\n";
    for(int i=100;i<=1000;i+=100){
        res[i] /= 100;
        res2[i] /= 100;
        cout<<i<<"\t"<<res[i]<<"\t"<<res2[i]<<'\n';
    }
	return 0;
}
