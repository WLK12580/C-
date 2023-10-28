#include<iostream>
#include<string>
int main(){
    std::string str="ab****cd*e";
    int j=0;
    bool flag=false;
    bool falgj=false;
    int count=0;
    for(int i=str.size()-1;i>=0;i--){
       if(str[i]=='*' && !falgj){
        j=i;
        flag=true;
        falgj=true;
        count++;
       }
       if(flag && str[i]!='*'){
        char temp=str[i];
        str[i]=str[j];
        str[j]=temp;
        i=j;
        flag=false;
        falgj=false;
       }
    }
    std::cout<<str<<"   number *="<< count<<std::endl;
    return 0;
}