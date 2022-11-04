#include "IniFile.h"
#include <sstream>  //
#include <fstream>  //
#include <iostream> //

Value::Value()
{
}
Value::Value(bool value)
{
    *this = value;
}
Value::Value(int value)
{
    // stringstream ss;
    // ss << value;        // value存入stringstream对象ss中
    // m_value = ss.str(); // stringstream对象ss转为字符串，再存入m_value中
    // // 上述过程包含了int类型转为字符串的功能实现
    *this = value;
}
Value::Value(double value)
{
    *this = value;
    // stringstream ss; // 原理同上面一样
    // ss << value;
    // m_value = ss.str();
}

Value::Value(const char *value) : m_value(value)
{ // 初始化列表的方式
    // m_value=value;
    *this = value;
}
Value::Value(const string &value)
{ // 普通方式
    //  m_value = value;
    *this = value;
}

Value &Value::operator=(bool value)
{
    m_value = value ? "true" : "false";
    return *this;
}
Value &Value::operator=(int value)
{
    stringstream ss;
    ss << value;
    m_value = ss.str();
    return *this;
}
Value &Value::operator=(double value)
{
    stringstream ss;
    ss << value;
    m_value = ss.str();
    return *this;
}
Value &Value::operator=(const char *value)
{
    m_value = value;
    return *this;
}
Value &Value::operator=(const string &value)
{
    m_value = value;
    return *this;
}

Value::operator bool()
{
    return m_value == "true";
}
Value::operator int()
{
    return std::atoi(m_value.c_str());
}
Value::operator double()
{
    return std::atof(m_value.c_str());
}
Value::operator string()
{
    return m_value;
}

IniFile::IniFile()
{
}
bool IniFile::load(const string &filename)
{
    m_filename = filename;
    ifstream fin(filename);
    if (fin.fail())
    {
        return false;
    }
    string line;
    string section;
    while (std::getline(fin, line))
    {
        line = trim(line);
        if (line == "")
            continue;
        if (line[0] == '[')
        {
            int pos = line.find_first_of(']');
            // string section = line.substr(0,pos); //调试修改
            section = line.substr(1, pos - 1);
            section = trim(section);
            m_sections[section] = Section();
        }
        else
        {
            int pos = line.find_first_of('=');
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1, line.length() - pos);
            key = trim(key);
            value = trim(value);
            m_sections[section][key] = value;
        }
    }
    fin.close();
    return true;
}

string IniFile::trim(string s)
{
    if (s.empty())
        return s;
    s.erase(0, s.find_first_not_of(" \n\r"));
    s.erase(s.find_last_not_of(" \n\r") + 1);
    return s;
}
Value &IniFile::get(const string &section, const string &key)
{
    return m_sections[section][key];
}

void IniFile::set(const string &section, const string &key, const Value &value)
{
    m_sections[section][key] = value;
}

bool IniFile::has(const string &section, const string &key)
{
    std::map<string, Section>::const_iterator it = m_sections.find(section);
    if (it != m_sections.end())
    {
        return (it->second.find(key) != it->second.end());
    }
    return false;
}
bool IniFile::has(const string &section)
{
    return (m_sections.find(section) != m_sections.end());
}
void IniFile::remove(const string &section, const string &key)
{
    std::map<string, Section>::iterator it = m_sections.find(section);
    if (it != m_sections.end())
    {
        it->second.erase(key);
    }
}
void IniFile::remove(const string &section)
{
    m_sections.erase(section);
}
void IniFile::clear()
{
    m_sections.clear();
}
string IniFile::str()
{
    stringstream ss;
    for (std::map<string, Section>::iterator it = m_sections.begin();
         it != m_sections.end(); it++)
    {
        ss << "[" << it->first << "]" << endl;
        for (std::map<string, Value>::iterator iter = it->second.begin();
             iter != it->second.end(); iter++)
        {
            ss << iter->first << " = " << string(iter->second) << std::endl;
        }
        ss << std::endl;
    }
    return ss.str();
}
void IniFile::show()
{
    std::cout << str();
}
bool IniFile::save(const string &filename)
{
    ofstream fout(filename);
    if (fout.fail())
    {
        return false;
    }
    fout << str();
    fout.close();
    return true;
}