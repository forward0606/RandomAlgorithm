#include<iostream>
using namespace std;


double h(int i){
    return 3.3 * i;
}

int main(){
    double i, f, g;
    cout<<"n\t\tf\t\tg\n";
    for(int t=0;t<10;t++){
        cin>>i>>f>>g;
        cout<<i<<"\t\t"<<f<<"\t\t"<<g<<'\n';
    }

    return 0;
}
