#pragma once
#include<string>
#include<map>
using namespace std;
class Value{
public:
    Value();
    Value(bool value);
    Value(int value);
    Value(double value);
    Value(const char* value);
    Value(const string & value);
    

    //注意记住为什么重载赋值运算符：
    /*
    Value v1;v1=126;Value v2;v2="hello";
    */
    //为了定义一个不知道需要赋值为什么类型的对象，
    //即定义一个空对象，后面又可以随意赋值给它任何类型
    Value& operator = (bool value);
    Value& operator = (int value);
    Value& operator = (double value);
    Value& operator = (const char* value);
    Value& operator = (const string & value);

    // 解决Value给bool,int,double等变量赋值问题
    operator bool();
    operator int();
    operator double();
    operator string();

    
private:
    string m_value;
};

typedef map<string,Value> Section;

class IniFile{

public:
    IniFile();
    bool load(const string&filename);
    bool save(const string&filename);
   
    Value&get(const string&section,const string&key);

    string str();
    void show();

    void set(const string&section,const string&key,const Value& value);
    bool has(const string&section,const string&key);
    bool has(const string&section);
    void remove(const string&section,const string&key);
    void remove(const string&section);
    void clear();


    //重载[]是为了取值能够像取数组值那样方便
    Section&operator [](const string&section){
        return m_sections[section];
    }
private:
    string trim(string s);

private:
    string m_filename;
    std::map<string,Section>m_sections;



};







