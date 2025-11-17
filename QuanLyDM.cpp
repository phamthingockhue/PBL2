#include "QuanLyDM.h"

string QuanLyDM::TimLoaiDM(int madm)
{
    for (int i = 0; i < dsDM.get_size(); i++)
    {
        if (dsDM[i]->getMaDM() == madm) return dsDM[i]->getLoaiDM();
    }
    return "";
}
DanhMuc* QuanLyDM::TimDM(int madm)
{
    for (int i = 0; i < dsDM.get_size(); i++)
    {
        if (dsDM[i]->getMaDM() == madm) return dsDM[i];
    }
    return nullptr;
}