#include "QuanLyVi.h"

Vi* QuanLyVi::TimVi(int maVi)
{
    for (int i = 0; i < dsVi.get_size(); i++)
    {
        if (dsVi[i].getMaVi() == maVi) return &dsVi[i];
    }
    return nullptr;
}