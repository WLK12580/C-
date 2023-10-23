#include <iostream>

using namespace std;
std::string getMaxSubstr(const std::string &str){
    std::string ret_str="";
    int maxstrlen=0;
    int strlen=str.size();
    for(int i=0;i<strlen;i++){
        if(str[i]>'9'||str[i]<'0'){
            continue;
        }
        int j=i+1;
        while(j<strlen && str[j]>='0' && str[j]<='9' && str[j]>str[j-1]){
            j++;
        }
        if(j-i>maxstrlen){
            maxstrlen=j-i;
            ret_str=str.substr(i,maxstrlen);
        }
        i=j;
    }
    return ret_str;
}
int main(){
    string str="abc12324fffff12457890";
    string res_str=getMaxSubstr(str);
    std::cout<<res_str<<std::endl;

    return 0;
}