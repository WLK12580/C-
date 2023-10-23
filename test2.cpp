#include<iostream>
#include<vector>
#include<string>
using namespace std;
int main(){
    
    string str="ads3sl123*56DF789ld34567AB";
    for(int i=0;i<str.size();i++){
        if('0'<=str[i]<='9' || str[i]=='*'){
            continue;
        }else{
            str[i]=' ';
        }
    }
    int pos=str.find("_");
    string str1=str.substr()

}