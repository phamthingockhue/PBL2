#include "GiaoDich.h"

class QuanLyGD
{
private: 
	MyVector<GiaoDich> dsGiaoDich;
public:
	void thongKeTheoThang(string);
	void setDSGD(MyVector<GiaoDich> dsgd)
	{
		dsGiaoDich = dsgd;
	}
	MyVector<GiaoDich> getDSGD()
	{
		return dsGiaoDich;
	}
};