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

void GiaoDich::capNhatMaGDCuaChiTiet(string newID) {
    maGD = newID; 
    for (int i = 0; i < dsChiTiet.get_size(); i++) 
    {
        dsChiTiet[i]->setMaGD(newID);
    }
}

void GiaoDich::gopGiaoDich(GiaoDich& gdCu)
{
    this->tongThu += gdCu.tongThu;
    this->tongChi += gdCu.tongChi;
    MyVector<ChiTietGD*>& listCon = gdCu.getDsChiTiet();

    for (int i = 0; i < listCon.get_size(); i++)
    {
        ChiTietGD* ct = listCon[i];
        ct->setMaGD(this->maGD);
        this->themChiTiet(ct);
    }
    listCon.clear();
}

void GiaoDich::xoaCTGD(ChiTietGD* ct)
{
    for (int i = 0; i < dsChiTiet.get_size(); i++)
    {
        if (dsChiTiet[i] == ct)
        {
            dsChiTiet.erase(i);
            return;
        }
    }
}