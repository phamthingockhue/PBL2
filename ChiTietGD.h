#pragma once
#include <string>
using namespace std;
class Vi;
class DanhMuc;

class ChiTietGD {
private:
    string maGD;
    unsigned int maCTGD;
    int maVi;
    int maDM;
    string moTa;
    long long soTienGD;
    static unsigned int demCTGD;
    Vi* vi;
    DanhMuc* danhMuc;

public:
    ChiTietGD() : maGD(""), maCTGD(0), maVi(0), maDM(0), moTa(""), soTienGD(0), vi(nullptr), danhMuc(nullptr)
    {
        maCTGD = demCTGD++;
    }

    ChiTietGD(const string& _maGD, int _maVi, int _maDM,
        const string& _moTa, long long _soTienGD)
        : maGD(_maGD), maVi(_maVi), maDM(_maDM),
        moTa(_moTa), soTienGD(_soTienGD),
        vi(nullptr), danhMuc(nullptr)
    {
        maCTGD = demCTGD++;
    }

    ChiTietGD(const string& _maGD, unsigned int _maCTGD, int _maVi, int _maDM,
        const string& _moTa, long long _soTienGD)
        : maGD(_maGD), maCTGD(_maCTGD), maVi(_maVi), maDM(_maDM),
        moTa(_moTa), soTienGD(_soTienGD),
        vi(nullptr), danhMuc(nullptr)
    {
        if (maCTGD >= demCTGD)
        {
            demCTGD = maCTGD + 1;
        }
    }

    string getMaGD() { return maGD; }
    int getMaCTGD() { return maCTGD; }
    int getMaVi() { return maVi; }
    int getMaDM() { return maDM; }
    string getMoTa() { return moTa; }
    long long getSoTienGD() { return soTienGD; }

    Vi* getVi() { return vi; }
    DanhMuc* getDanhMuc() { return danhMuc; }

    void setMaGD(const string& magd) { maGD = magd; }
    void setMaCTGD(int _maCTGD) { maCTGD = _maCTGD; }
    void setMaVi(int _mavi) { maVi = _mavi; }
    void setMaDM(int _madm) { maDM = _madm; }
    void setMota(string _mota) { moTa = _mota; }
    void setSoTienGD(long long _tien) { soTienGD = _tien; }
    void setVi(Vi* _vi) { vi = _vi; }
    void setDM(DanhMuc* _dm) { danhMuc = _dm; }
};