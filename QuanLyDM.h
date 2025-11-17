#pragma once
#include "DanhMuc.h"
#include "MyVector.h"
class QuanLyDM
{
private: 
	MyVector<DanhMuc*> dsDM;
public:
	string TimLoaiDM(int);
	DanhMuc* TimDM(int);
	void setDM(MyVector<DanhMuc*> dm)
	{
		dsDM = dm;
	}
	MyVector<DanhMuc*> getDM()
	{
		return dsDM;
	}
};

