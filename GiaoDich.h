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

    size_t getSoLuongChiTiet() const { return dsChiTiet.get_size(); }
    ChiTietGD* getChiTietGD(int index) 
    {
        return dsChiTiet[index];
    }

    void setTongThu(long long _tien) { tongThu = _tien; }
    void setTongChi(long long _tien) { tongChi = _tien; }

    void themChiTiet(ChiTietGD* ctgd);

    MyVector<ChiTietGD*> getDsChiTiet() { return dsChiTiet; }

    void capNhatTongTien() {
        for (int i = 0; i < dsChiTiet.get_size(); i++) {
            DanhMuc* dm = dsChiTiet[i]->getDanhMuc(); 
            if (dm == nullptr) continue; 

            if (dm->getLoaiDM() == "Thu") 
            {
                this->tongThu += dsChiTiet[i]->getSoTienGD();
            }
            else 
            { 
                this->tongChi += dsChiTiet[i]->getSoTienGD();
            }
        }
    }
};

