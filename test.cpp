#include<iostream>

class Shape{
public:
    virtual int getArea()=0; //主要返回值；
    void setWidth(int wid){
        width=wid;
    }
    void setHeight(int hig){
        height=hig;
    }
    virtual ~Shape(){};
public:
    int width=0;
    int height=0;
};
class Rectangle:public Shape{
public:

    int getArea(){
        return width*height;
    }
};
class Triangle:public Shape{
public:
    int getArea(){
        return width*height/2;
    }
};
int main(){
    Triangle tri;
    tri.setHeight(5);
    tri.setWidth(7);

    Rectangle rec;
    rec.setHeight(10);
    rec.setWidth(20);


    std::cout<<rec.getArea()<<std::endl;
    std::cout<<tri.getArea()<<std::endl;
    return 0;
}