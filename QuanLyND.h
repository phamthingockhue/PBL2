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
    bool DangKy(const string& userid, const string& name, const string& password);
    string AnMK();
    int KiemTraMK(const string& userid, const string& password);
    void DoiMK(int index, const string& mk);
    void XoaTaiKhoan(int index);
};