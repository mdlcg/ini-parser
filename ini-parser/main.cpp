#include <iostream>
#include "IniFile.h"
using namespace std;

int main()
{

    IniFile ini;
    ini.load("main.ini");
    const string &ip = ini["server"]["ip"];
    int port = ini["server"]["port"];

    ini.show();
    ini.save("temp.ini");

    return 0;
}
