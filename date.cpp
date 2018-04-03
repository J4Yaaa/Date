#include "date.h"
#include <iostream>
#include <assert.h>
using namespace std;

Date::Date(int year,int month,int day):_year(year),_month(month),_day(day)
{
    if(!IsValid())  // -> this.IsValid()
    {
        assert(false);
    }
}

bool Date::IsValid()
{
    return (_year > 0 
       && _month > 0 && _month <= 12 
       &&_day > 0 && _day <= GetMonthDay(_year,_month));
}

int Date::GetMonthDay(int year,int month)
{
    int arr[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(month == 2 && IsLeapYear(year))
    {
        ++arr[2];
    }
    return arr[month];
}

bool Date::IsLeapYear(int year)
{
    return ((year % 4 == 0 && year % 100 != 0)
        || year % 400 == 0);
}

void Date::Show()
{
    cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
}

//  运算符重载经历以下几个步骤
//  (d1==d2)
//  d1.operator==(d2)
//  d1.operator==(&d1,d2)
//  bool Date::operator==(Date* this,const Date& d)
bool Date::operator==(const Date& d)
{
    if(_year == d._year && _month == d._month && _day == d._day)
        return true;
    return false;
}

//传值返回：会多调用一次拷贝构造函数
//传引用返回：直接返回，不需要调用拷贝构造
//            出了作用于变量还在，尽量使用传引用返回
Date& Date::operator=(const Date& d)
{
    if(this != &d)
    {
        _year = d._year;
        _month = d._month;
        _day = d._day;
    }
    return *this;
}

bool Date::operator>=(const Date& d)
{
    return !(*this < d);
}

bool Date::operator<=(const Date& d)
{
    return ((*this < d) || (*this == d));
}

bool Date::operator!=(const Date& d)
{
    return !(*this == d);
}

bool Date::operator>(const Date& d)
{
    return !(*this <= d);
}

bool Date::operator<(const Date& d)
{
    if((_year < d._year) ||
       (_year == d._year && _month < d._month) ||
       (_year == d._year && _month == d._month && _day < d._day))
        return true;
    return false;
}

Date Date::operator+(int day)
{
    if(day < 0)
    {
        return (*this) - (-day);
    }
    Date d(*this);
    d._day += day;
    while(d.IsValid() == false)
    {
        int month_day = GetMonthDay(d._year,d._month);
        d._day -= month_day;
        ++d._month;
        if(d._month > 12)
        {
            d._month = 1;
            ++d._year;
        }
    }
    return d;
}

Date& Date::operator+=(int day)
{
    *this = (*this + day);
    return *this;
}

Date Date::operator-(int day)
{
    if(day < 0)
    {
        return (*this) + (-day);
    }
    Date d(*this);
    d._day -= day;
    while(d.IsValid() == false)
    {
        --d._month;
        if(d._month == 0)
        {
            --d._year;
            d._month = 12;
        }
        int pre_month_day = GetMonthDay(d._year,d._month);
        d._day += pre_month_day;
    }
    return d;
}

Date& Date::operator-=(int day)
{
    *this = (*this - day);
    return *this;
}

//int Date::operator-(const Date& d)//日期-日期 返回天数
//{
//    int day_count = 0;
//    int month_count = 0;
//    int year_count = 0;
//    
//    day_count = _day - d._day;
//   
//    if(_month < d._month)
//    {
//        int i = _month;
//        for(i = _month ;i < d._month ;++i)
//        {
//            month_count += GetMonthDay(d._year,i);
//        }
//        month_count = 0 - month_count;
//    }
//    else if(_month > d._month)
//    {
//        int i = d._month;
//        for(i = d._month;i < _month; ++i)
//        {
//            month_count += GetMonthDay(_year,i);
//        }
//    }
//    
//    if(_year < d._year)
//    {
//        int i = _year;
//        for(i = _year + 1;i <= d._year;++i)
//        {
//            year_count += 365;
//            if(IsLeapYear(i) == true)
//            {
//                ++year_count;
//            }
//        }
//        year_count = 0- year_count;
//    }
//    else if(_year > d._year)
//    {
//        int i = d._year;
//        for(i = d._year + 1;i <= _year;++i)
//        {
//            year_count += 365;
//            if(IsLeapYear(i) == true)
//            {
//                ++year_count;
//            }
//        }
//    }
//    return day_count + month_count + year_count;
//}

int Date::operator-(const Date& d)//日期-日期 返回天数
{
    int flag = 1;
    Date max = (*this);
    Date min = d;
    if((*this) < d)
    {
        max = d;
        min = (*this);
        flag = -1;
    }
    int count = 0;
    while(max != min)
    {
        ++min;
        ++count;
    }
    return flag*count;
}

//  ++d1 ->  d1.operator++(&d1);
Date& Date::operator++()//默认前置
{
    *this += 1; // 只调用一个函数
    //*this = *this + 1; //调用两个函数，还要调用拷贝构造函数
    return *this;
}

//  d1++ ->  d1.operator++(&d1,0);
Date Date::operator++(int)//用参数标志后置++
{
    Date tmp(*this);
    *this += 1;
    return tmp;
}

Date& Date::operator--()
{
    *this -= 1;
    return *this;
}

Date Date::operator--(int)
{
    Date tmp(*this);
    *this -= 1;
    return tmp;
}

////////////////////////////////////////////////////
// 测试
////////////////////////////////////////////////////
#if 1

int main()
{
    Date d1(2018,3,20);
    d1.Show();
    Date d(d1+5);
    d.Show();
    d += 20;
    d.Show();
    Date d2;
    d2 = d1;
    d2.Show();
    cout<<"== except 1,actual "<<(d1 == d2)<<endl;
    cout<<">= except 1,actual "<<(d1 >= d2)<<endl;
    cout<<"<= except 1,actual "<<(d1 <= d2)<<endl;
    cout<<"!= except 0,actual "<<(d1 != d2)<<endl;
    cout<<"> except 0,actual "<<(d1 > d2)<<endl;
    cout<<"< except 0,actual "<<(d1 < d2)<<endl;

    d2 += 2;
    d2.Show();
    cout<<"== except 0,actual "<<(d1 == d2)<<endl;
    cout<<">= except 0,actual "<<(d1 >= d2)<<endl;
    cout<<"<= except 1,actual "<<(d1 <= d2)<<endl;
    cout<<"!= except 1,actual "<<(d1 != d2)<<endl;
    cout<<"> except 0,actual "<<(d1 > d2)<<endl;
    cout<<"< except 1,actual "<<(d1 < d2)<<endl;

    d2.Show();
    (d2++).Show();
    (++d2).Show();

    Date d3(2018,3,20);
    d3 = (d3 + (-100));
    d3.Show();
    (d3--).Show();
    (--d3).Show();

    Date d4(2018,3,21);
    Date d5(2000,5,21);
    d4.Show();
    d5.Show();
    cout<<"d4 - d5 = "<<(d4 - d5)<<endl;



    return 0;
}

#endif
