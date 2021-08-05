//
// Created by mhuelsberg on 05.08.21.
//

#include "cpuinfo.h"

#include <cstring>
#include <cpuid.h>
#include <fstream>
#include <boost/algorithm/string.hpp>
namespace bo = boost;
#include <experimental/filesystem>
namespace fs = experimental::filesystem;
#include "tools/string.h"

string getCPUInfo(){
    char CPUBrandString[0x40];
    unsigned int CPUInfo[4] = {0,0,0,0};

    __cpuid(0x80000000, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
    unsigned int nExIds = CPUInfo[0];

    memset(CPUBrandString, 0, sizeof(CPUBrandString));

    for (unsigned int i = 0x80000000; i <= nExIds; ++i)
    {
        __cpuid(i, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);

        if (i == 0x80000002)
            memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000003)
            memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000004)
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
    }
    return string(CPUBrandString);
}

string getRAMInfo(){

    string memTotal = "not found";
    string linux_file = "/proc/meminfo";
    if(!fs::exists(linux_file)){
        return memTotal;
    }
    ifstream f;
    f.open("/proc/meminfo");
    string line;
    string keyword = "MemTotal";
    while(getline(f, line)){
        if(line.find(keyword) != string::npos){
            vector<string> linesplit;
            bo::split(linesplit, line, bo::is_any_of(" "));
            auto new_end = remove_if(linesplit.begin(), linesplit.end(), str_is_empty);
            linesplit.erase(new_end, linesplit.end());
            memTotal = linesplit[1] + " " + linesplit[2];
            break;
        }
    }
    f.close();
    return memTotal;
}

string getHostName(){
    char hostname[HOST_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    return string(hostname);
}

string getUserName(){
    char username[LOGIN_NAME_MAX];
    getlogin_r(username, LOGIN_NAME_MAX);
    return string(username);
}
