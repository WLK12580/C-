#include <stdio.h>

#include <iostream>
#include <string>
// enum Person {
//   AGE,
//   HEIGH,
// };

enum Student { AGE, HEIGH };
enum class Ecl{
    UNKOWN,
    HAVE,
    DONE
};
class Base{
    public:
    void display(){
        std::cout<<"base dispaly"<<std::endl;
    }
};
class Subclass:public Base{

};

int main(){
    Ecl CL;
    CL=Ecl::DONE;
    std::cout<<int(CL)<<std::endl;
    Subclass SUBC;
    SUBC.display();
    return 0;
}
