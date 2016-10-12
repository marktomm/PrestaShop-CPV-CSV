#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>

#define DIVISION_MODULO 1000000

using namespace std;

bool isDivision(int cpv_code) {
    return (0 == cpv_code % DIVISION_MODULO ? true : false);
}

int firstNotZero(int cpv_code) {
    int modulo = 10;
    int i = 0;
    while(true) {
        ++i;
        
        if(cpv_code % modulo)
            return i;
        
        modulo *= 10;
    }
}

int getParent(int cpv_code, vector<int>& codes,int zrs_cnt = 0) {
    int tr_zrs_cnt = 0;
    if(zrs_cnt == 0) {
        tr_zrs_cnt = firstNotZero(cpv_code);
    } else {
        tr_zrs_cnt = zrs_cnt;
    }
    
    if(tr_zrs_cnt == 0) {
        cout << "error z: " << cpv_code << endl;
    }
    
    int modulo = pow(10, tr_zrs_cnt);
    int substract = cpv_code % modulo;

    int result = cpv_code - substract;

    if(result == cpv_code) {
        cout << "error: " << result << endl;
    }

    if(find(codes.begin(), codes.end(), result) != codes.end() && result != cpv_code) {
        return result;
    } else {
        return getParent(cpv_code, codes, tr_zrs_cnt+1);
    }
}

int main() {
    ifstream ifs ("just_cpv_codes", std::ifstream::in);
    vector<int> cpv_codes;
    
    while(true) {
        int dig;
        ifs >> dig;
        cpv_codes.push_back(dig);
        
        if(ifs.eof())
            break;
    }
    
    
    ifstream ifs2 ("c_ru_just_names", std::ifstream::in);
    vector<string> cpv_names;
    
    while(true) {
        string str;
        getline(ifs2, str);
        cpv_names.push_back(str);
        
        if(ifs2.eof())
            break;
    }
    
    vector<string> cpv_list;
    int it = 0;
    int id = 3;
    for(auto&& i : cpv_codes) {
        stringstream ss;
        string name = cpv_names[it++];
        if(isDivision(i)) {
            if(i < 10000000) {
                ss << id++ << "?1?\"0" << i << "\"?Home?" << name;
            } else {
                ss << id++ << "?1?\"" << i << "\"?Home?" << name;
            }
        } else {
            if(i < 10000000) {
                if(getParent(i, cpv_codes) < 10000000) {
                    ss << id++ << "?1?\"0" << i << "\"?\"0" << getParent(i, cpv_codes) << "\"?" << name;
                } else {
                    ss << id++ << "?1?\"0" << i << "\"?\"" << getParent(i, cpv_codes) << "\"?" << name;
                }
            } else {
                if(getParent(i, cpv_codes) < 10000000) {
                    ss << id++ << "?1?\"" << i << "\"?\"0" << getParent(i, cpv_codes) << "\"?" << name;
                } else {
                    ss << id++ << "?1?\"" << i << "\"?\"" << getParent(i, cpv_codes) << "\"?" << name;
                }
            }
        }
        
        cpv_list.push_back(ss.str());
    }
    
    for(auto&& i : cpv_list) {
        cout << i << endl;
    }
    
    return 0;
}