#pragma once
#include <string>
#include "MyVector.h"
#include "ChiTietGD.h"
#include "DanhMuc.h"
#include <iostream>
using namespace std;

class GiaoDich {
private:
    string maGD;
    long long tongThu;
    long long tongChi;
    MyVector<ChiTietGD*> dsChiTiet;

public:
    GiaoDich() : maGD(""), tongThu(0), tongChi(0) {}
    GiaoDich(const string& _maGD) : maGD(_maGD), tongThu(0), tongChi(0) {}
    GiaoDich(const string& _maGD, long long _tongThu, long long _tongChi)
        : maGD(_maGD), tongThu(_tongThu), tongChi(_tongChi)
    {}

    string getMaGD() { return maGD; }
    long long getTongThu() { return tongThu; }
    long long getTongChi() { return tongChi; }
    MyVector<ChiTietGD*>& getDsChiTiet() { return dsChiTiet; }

    void setMaGD(string _maGD) { maGD = _maGD; }
    void setTongThu(long long _tien) { tongThu = _tien; }
    void setTongChi(long long _tien) { tongChi = _tien; }
    void setDsChiTiet(MyVector<ChiTietGD*> ds) { dsChiTiet = ds; }

    void themChiTiet(ChiTietGD* ctgd);
    void capNhatTongTien();
    void capNhatMaGDCuaChiTiet(string newID);
    void gopGiaoDich(GiaoDich& gdCu);
    void xoaCTGD(ChiTietGD* ct);
};
