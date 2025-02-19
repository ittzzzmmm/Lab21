#include<iostream>
#include<string>
using namespace std;

int main(int argc, char* argv[]){
    if(argc==1){cout<<"Please input numbers to find average.";}
    else{
    double mean,sum=0;
    for(int i=1;i<argc;i++){
        sum+=stod(argv[i]);
        mean=sum/(argc-1);
    }
    cout<<"---------------------------------\n";
    cout << "Average of " << argc-1 << " numbers = " << mean<<'\n';
    cout<<"---------------------------------\n";
    }
}
