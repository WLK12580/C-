#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<string> vec;
    string str=" hello world my c++";
    string temp="";
    for(int i=0;i<str.size()-1;i++){
        if(str[i]!=' '){
            temp+=str[i];
            if(str[i+1]==' '){
                vec.push_back(temp);
                std::cout<<temp<<std::endl;
                temp.clear();
            }
            if(i+1==str.size()-1){
                temp+=str[str.size()-1];
                vec.push_back(temp);
                std::cout<<temp<<std::endl;
                temp.clear();

            }
        }
    }

    return 0;
}