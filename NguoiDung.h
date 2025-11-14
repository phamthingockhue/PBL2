#pragma once
#include <string>
using namespace std;

class NguoiDung {
private:
    string id;
    string ten;
    string matKhau;
public:
    NguoiDung() : id(""), ten(""), matKhau("") {}
    NguoiDung(const string& _id, const string& _ten, const string& _mk)
        : id(_id), ten(_ten), matKhau(_mk) 
    {}

    string getID() { return id; }
    string getTen() { return ten; }
    string getMatKhau() { return matKhau; }

    void setID(string _id) { id = _id; }
    void setTen(string _ten) { ten = _ten; }
    void setMatKhau(string _mk) { matKhau = _mk; }
};