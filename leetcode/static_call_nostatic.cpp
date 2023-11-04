#pragma once
#include<iostream>
Person pn;
class Person{
public:
    Person(){};
    Person(const std::string &name):name_(name){};
    static std::string getStaticName(){
        return static_name_;
    }
    static std::string getNostaticName(const Person *per){
        return per->name_;
    }
    static std::string getNostaticName(){
        return pn.name_;
    }
private:
    static std::string static_name_;
    std::string name_;

};

std::string Person::static_name_="xiaoming";
int main(){
    Person per;
    Person pers("xiaowang");
    std::cout<<per.getStaticName()<<std::endl;
    std::cout<<pers.getNostaticName(&pers)<<std::endl;
    return 0;
}