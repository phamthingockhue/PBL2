#pragma once
#include "MyVector.h"
#include "NguoiDung.h"

class QuanLyND
{
private:
    MyVector<NguoiDung>* dsNguoiDung;
public:
    QuanLyND(MyVector<NguoiDung>* dsnd)
    {
        dsNguoiDung = dsnd;
    }
    ~QuanLyND() {}
    NguoiDung* xacThuc(const string& userid, const string& password);
    bool dangKy(const string& userid, const string& name, const string& password);
    string anMK();
    int kiemTraMK(const string& userid, const string& password);
    void doiMK(int index, const string& mk);
    void xoaTaiKhoan(int index);
};