#include<iostream>
using namespace std;


double h(int i){
    return 3.3 * i;
}

int main(){
    double i, f, g;
    cout<<"n\t\tf\t\th\t\trelative error\n";
    for(int t=0;t<10;t++){
        cin>>i>>f>>g;
        double fit = h(i);
        cout<<i<<"\t\t"<<f<<"\t\t"<<fit<<"\t\t"<<abs(fit-f)/f<<'\n';
    }

    return 0;
}
