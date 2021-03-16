#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <array>

struct inflatable
{
    char fname[20];//也可以写成std::string fname;
    float volume;
    double price;
};

int main()
{
    //数组初始化规则；
    int yams[3];
    yams[0] = 7;
    yams[1] = 8;
    yams[2] = 6;
    int yamcosts[3] = { 20, 35, 5 };
    double earnings[4]{ 1.2e4, 1.6e4, 1.1e4, 1.7e4 };//初始化可省略“=”；
    int counts[10] = {};//将所有元素设置为0；

    //字符串；
    char bird[11] = "Mr. Cheeps";
    char fish[] = "Bubbles";

    const int arsize = 20;
    char name[arsize];
    std::cout << "Enter your name： " << std::endl;
    std::cin.getline(name, arsize); //getline（）将包含arsize个元素读入到name数组中；

    //sring类位于std中,必须使用std::string,或者using namespace std;
    std::string str1;
    std::string str2 = "panther";
    int len1 = str1.size();

    //结构体；
    inflatable guest =
    {
        "Glorious Gloria" ,//fname value
        1.88,              //volume value
        23.99              //price value
    };
    std::cout << guest.fname << " " << guest.volume << std::endl;
    inflatable gifts[100];//创建100个这样的结构数组；

    //vector & array
    std::vector<double> a2(4); //vector格式使用
    a2[0] = 1.0 / 3.0;
    a2[1] = 1.0 / 5.0;
    a2[2] = 1.0 / 7.0;
    a2[3] = 1.0 / 9.0;
    
    std::array<double, 4> a3 = {1.2, 2.4, 3.6, 4.8};//array类格式
    std::array<double, 4> a4;
    a4 = a3;
}





