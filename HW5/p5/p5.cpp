#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
using namespace std;

const int N = 112500;
const int M = 100000;
//const int N = 18;
//const int M = 16;
const int SAT = 9;

int J = 0;

random_device rd;
mt19937 g(rd());

struct Var{
    int id;
    bool is_bar;
};

struct Nine_SAT{
    vector<Var> c;
    map<int, int> mp;
    Nine_SAT():c(SAT){
        //cout<<"construct";
    };
};

void localcorrect(const vector<Nine_SAT> &formula, vector<bool> &v, int lc_id){
    J++;
    const auto &s1 = formula[lc_id];
    for(int i=0;i<s1.c.size();i++){
        v[s1.c[i].id] = g() % 2;
    }
    for(int i=0;i<formula.size();i++){
        auto &s = formula[i];
        bool is_able = false;
        for(int j=0;j<s.c.size();j++){
            if(v[s.c[j].id] == s.c[j].is_bar){
                is_able = true;
                break;
            }
        }
        if(!is_able){
            localcorrect(formula, v, i);
        }
    }
}

vector<bool> k_SAT_ALGO(const vector<Nine_SAT> &formula){
    vector<bool> v(N);
    for(int i=0;i<N;i++){
        v[i] = g() % 2;
    }
    for(int i=0;i<formula.size();i++){
        auto &s = formula[i];
        bool is_able = false;
        for(int j=0;j<s.c.size();j++){
            if(v[s.c[j].id] == s.c[j].is_bar){
                is_able = true;
                break;
            }
        }
        if(!is_able){
            localcorrect(formula, v, i);
        }
    }
    // check ans
    for(int i=0;i<formula.size();i++){
        auto &s = formula[i];
        bool is_able = false;
        for(int j=0;j<s.c.size();j++){
            if(v[s.c[j].id] == s.c[j].is_bar){
                is_able = true;
                break;
            }
        }
        if(!is_able){
            cerr<<"error: is_able = false"<<endl;
            exit(1);
        }
    }
    return v;
}
vector<Nine_SAT> build_formula(vector<int> &rnd_base){
    shuffle(rnd_base.begin(), rnd_base.end(), g);

    vector<Nine_SAT> formula(M);
    for(int i=0;i<rnd_base.size();i++){
        formula[i/9].c[i%9].id = rnd_base[i];
        formula[i/9].mp[rnd_base[i]]++;
    }
    
    for(int i=0;i<formula.size();i++){
        Nine_SAT &s = formula[i];
        for(auto &e:s.mp){
            while(e.second > 1){
                int rnd_id = g() % M;
                while(formula[rnd_id].mp.find(e.first) != formula[rnd_id].mp.end()){
                    rnd_id = g() % M;
                    
                }
                int rnd_vid = g() % SAT;
                int v = formula[rnd_id].c[rnd_vid].id;
                while(formula[i].mp.find(v) != formula[i].mp.end()){
                    rnd_vid = g() % SAT;
                    v = formula[rnd_id].c[rnd_vid].id;
                }
                //cout<<"local correct: ("<<i<<", "<<e.first<<"), ("<<rnd_id<<", "<<v<<")"<<endl;
                for(int j=0;j<SAT;j++){
                    if(s.c[j].id == e.first){
                        swap(s.c[j], formula[rnd_id].c[rnd_vid]);
                        e.second--;
                        formula[rnd_id].mp[v]--;
                        formula[rnd_id].mp[e.first]++;
                        s.mp[v]++;
                        break;
                    }
                }
            }
        }
    }

    for(auto &s:formula){
        // assign bar and check share variable
        map<int, int> check;
        for(int i=0;i<s.c.size();i++){
            check[s.c[i].id]++;
            s.c[i].is_bar = g() % 2;
        }
        for(auto e:check){
            if(e.second > 1){
                cerr<<"error: e.first = "<<e.first<<endl;
                exit(1);
            }
        }
    }

    return formula;
}

void PRINT_FORMULA(const vector<Nine_SAT> &formula){
    for(auto &s:formula){
        for(int i=0;i<s.c.size();i++){
            cout<<"("<<s.c[i].id<<", "<<s.c[i].is_bar<<")\n";
        }
    }
}

void PRINT_ANS(const vector<bool> &v){
    for(int e:v){
        cout<<e<<" ";
    }
    cout<<'\n';
}


int main(){
    
    // compute random SAT
    vector<int> rnd_base;
    for(int i=0;i<N;i++){
        for(int j=0;j<8;j++){
            rnd_base.emplace_back(i);
        }
    }

    map<int, int> dis;
    for(int g=0;g<100;g++){
        J = 0;
        vector<Nine_SAT> formula = build_formula(rnd_base);

        vector<bool> v = k_SAT_ALGO(formula);

        dis[J/10]++;
        cout<<"J = "<<J<<endl;
    }
    for(auto e:dis){
        cout<<e.first * 10<<"~"<<(e.first+1) * 10 <<" "<<e.second<<'\n';
    }

    return 0;
}
