#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "MyVector.h"
#include "NguoiDung.h"


class QuanLyND
{
private:
    MyVector<NguoiDung> dsNguoiDung;
public:
    QuanLyND() {}
    ~QuanLyND() {}
    QuanLyND(MyVector<NguoiDung>& dsNguoiDung)
        : dsNguoiDung(dsNguoiDung)
    {}
    NguoiDung* xacThuc(const string&, const string&);
    bool DangKy(const string&, const string& , const string&);
    string AnMK();
    int KiemTraMK(const string&, const string&);
    void DoiMK(int, const string&);
    void XoaTaiKhoan(int);
    MyVector<NguoiDung> getDsNguoiDung() const {
        return dsNguoiDung;
    }
    void setDsNguoiDung(MyVector<NguoiDung> ds) {
        dsNguoiDung = ds;
    }
};
