#include <iostream>
using namespace std;

int main() {
    int width, height;
    cout << "请输入长方形的宽度：";
    cin >> width;
    cout << "请输入长方形的高度：";
    cin >> height;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << "* ";
        }
        cout << endl;
    }

    return 0;
}