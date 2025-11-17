#include "QuanLyGD.h"
#include <iomanip>

void QuanLyGD::thongKeTheoThang(string nam)
{
    MyVector<GiaoDich> dsnam;
    for (int i = 0; i < dsGiaoDich.get_size(); i++)
    {
        if (dsGiaoDich[i].getMaGD().substr(0, 4) == nam)
        {
            dsnam.push_back(dsGiaoDich[i]);
        }
    }
    cout << "\n--- CHI TIET GIAO DICH THEO THANG CUA NAM " << nam << "--- \n";
    string line_sep = "+-" + string(10, '-') + "-+-" + string(15, '-') + "-+-" + string(15, '-') + "-+";
    cout << line_sep << endl;
    cout << "| " << left << setw(10) << "Thang" << " | "
        << left << setw(15) << "Tong Thu" << " | "
        << left << setw(15) << "Tong Chi" << " |" << endl;
    cout << line_sep << endl;

    for (int k = 1; k <= 12; k++)
    {
        long long tongThu = 0, tongChi = 0;
        for (int j = 0; j < dsnam.get_size(); j++)
        {
            if (stoi(dsnam[j].getMaGD().substr(4, 2)) == k)
            {
                tongChi += dsnam[j].getTongChi();
                tongThu += dsnam[j].getTongThu();
            }
        }
        cout << "| " << left << setw(10) << k << " | "
            << left << setw(15) << tongThu << " | "
            << left << setw(15) << tongChi << " |" << endl;
    }
    cout << line_sep << endl;
}
