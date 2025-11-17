#include "GiaoDich.h"

void GiaoDich::themChiTiet(ChiTietGD* ctgd)
{
	dsChiTiet.push_back(ctgd);
}

void GiaoDich::capNhatTongTien() 
{
    this->tongChi = 0;
    this->tongThu = 0;
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