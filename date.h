#pragma once

class Date
{
public:
    Date(int year = 1900,int month = 1,int day = 1);
    ~Date(){}
    bool IsValid();
    int GetMonthDay(int year,int month);
    bool IsLeapYear(int year);
    void Show();

    Date& operator=(const Date& d);
    bool operator==(const Date& d);
    bool operator>=(const Date& d);
    bool operator<=(const Date& d);
    bool operator!=(const Date& d);
    bool operator>(const Date& d);
    bool operator<(const Date& d);
    Date operator+(int day);
    Date& operator+=(int day);
    Date operator-(int day);
    Date& operator-=(int day);
    int operator-(const Date& d);//日期-日期 返回天数
    Date& operator++();//默认前置
    Date operator++(int);//用参数标志后置++
    Date& operator--();
    Date operator--(int);

private:
    int _year;
    int _month;
    int _day;
};


//构造函数：完成成员变量的初始化
//析构函数：完成清理(当前类型不需要清理，如果有malloc的成员变量，就去要清理free掉)
//拷贝构造：创建一个对象，其内容和同类型参数相同
//运算符重载：运算一个已经存在的变量
//            operator= : 不写系统会生成一个默认的，完成依次的值拷贝
