#pragma once
#include "GiaoDich.h"
#include "MyVector.h"
using namespace std;

class QuanLyCTGD;
class QuanLyGD
{
private:
	MyVector<GiaoDich>* dsGiaoDich;
public:
	QuanLyGD(MyVector<GiaoDich>* dsgd, MyVector<ChiTietGD*>* dsct)
	{
		dsGiaoDich = dsgd;
		for (int i = 0; i < dsGiaoDich->get_size(); i++)
		{
			string maHienTai = (*dsGiaoDich)[i].getMaGD();
			for (int j = 0; j < dsct->get_size(); j++)
			{
				if ((*dsct)[j]->getMaGD() == maHienTai)
				{
					(*dsGiaoDich)[i].themChiTiet((*dsct)[j]);
				}
			}
		}
	}

	void inDanhSachGD(); 
	GiaoDich* taoGD(const string& maGD); 
	void xoaGiaoDich(const string& maGD);
	int tonTaiGiaoDich(const string& maGD);
	bool doiNgayGiaoDich(const string& oldID, const string& newID);
	void thongKeTheoThang(string);
	GiaoDich* tim_GD(const string& magd);
};