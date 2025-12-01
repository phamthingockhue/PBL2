#pragma once
#include <string>
#include <iostream>
#include "MyVector.h"
#include "ChiTietGD.h"

class QuanLyCTGD {
private:
	MyVector<ChiTietGD*>* dsChiTietGD;
public:
	QuanLyCTGD(MyVector<ChiTietGD*>* dsct) 
	{
		dsChiTietGD = dsct;
	}
	void inDanhSachCTGDTheoNgay(string);
	ChiTietGD* taoChiTiet(string maGD, int maVi, int maDM, string moTa, long long soTien);
	void themChiTiet(ChiTietGD& ct);
	void capNhatMaGD(const string& oldID, const string& newID);
	void xoaCTGD(int maCTGD);
	bool suaCTGD(int maCTGD, string newMaGD, string newMoTa, long long newSoTien);
	void suaMaGiaoDich_CTGD(string oldMaGD, string newMaGD);
	ChiTietGD* timCTGD(int maCTGD);
};

