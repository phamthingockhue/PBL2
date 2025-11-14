#pragma once
#include "ChiTietGD.h"
#include "MyVector.h"
#include "Vi.h"
#include "DanhMuc.h"
#include "DataManager.h"

class QuanLyChiTietGD
{
private:
	MyVector<ChiTietGD*> dsChiTietGD;
	DataManager dm;
public:
	QuanLyChiTietGD(DataManager dataManager) : dm(dataManager) {}
	Vi* timVi(const int&);
	GiaoDich* timHoacTaoGDTheoNgay(const string&);
	DanhMuc* timDM(const int&);
	void themChiTietGD(const ChiTietGD&);
	void capNhatSoDuVi(long long);
	~QuanLyChiTietGD();
	// xoa chi tiet gd
};

