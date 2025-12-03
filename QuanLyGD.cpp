#include "QuanLyGD.h"
#include "QuanLyCTGD.h"
#include <iostream>
#include <iomanip>

void QuanLyGD::inDanhSachGD() {
	string line = "+-" + string(12, '-') + "-+-"
		+ string(15, '-') + "-+-"
		+ string(15, '-') + "-+";

	cout << "\n--- DANH SACH GIAO DICH ---\n";
	cout << line << endl;

	// 2. In Tiêu đề
	cout << "| " << left << setw(12) << "Ma GD" << " | "
		<< left << setw(15) << "Tong Thu" << " | "
		<< left << setw(15) << "Tong Chi" << " |" << endl;
	cout << line << endl;

	for (int i = dsGiaoDich->get_size() - 1; i >= 0; i--)
	{
		cout << "| " << left << setw(12) << (*dsGiaoDich)[i].getMaGD() << " | "
			<< right << setw(15) << (*dsGiaoDich)[i].getTongThu() << " | "
			<< right << setw(15) << (*dsGiaoDich)[i].getTongChi() << " |" << endl;
	}
	cout << line << endl;
}

GiaoDich* QuanLyGD::taoGD(const string& maGD) {
	GiaoDich gdMoi(maGD);
	dsGiaoDich->push_back(gdMoi);
	return &dsGiaoDich->back();
}


void QuanLyGD::xoaGiaoDich(const string& maGD) {
	for (int i = 0; i < dsGiaoDich->get_size(); i++) {
		if ((*dsGiaoDich)[i].getMaGD() == maGD) {
			dsGiaoDich->erase(i);
			return;
		}
	}
}

int QuanLyGD::tonTaiGiaoDich(const string& maGD)
{
	for (int i = 0; i < dsGiaoDich->get_size(); i++)
	{
		if ((*dsGiaoDich)[i].getMaGD() == maGD) return i;
	}
	return -1;
}

bool QuanLyGD::doiNgayGiaoDich(const string& oldID, const string& newID) 
{
	if (oldID == newID) {
		cout << "Ma trung nhau. Khong thuc hien thay doi!\n";
		return true;
	}
	int check_old = tonTaiGiaoDich(oldID);
	if (check_old == -1) return false;
	int check_new = tonTaiGiaoDich(newID);
	if (check_new == -1)
	{
		(*dsGiaoDich)[check_old].capNhatMaGDCuaChiTiet(newID);
	}
	else
	{
		(*dsGiaoDich)[check_new].gopGiaoDich((*dsGiaoDich)[check_old]);
		dsGiaoDich->erase(check_old);
	}
	return true;
}

void QuanLyGD::thongKeTheoThang(string nam)
{
	MyVector<GiaoDich> dsnam;
	for (int i = 0; i < dsGiaoDich->get_size(); i++)
	{
		if ((*dsGiaoDich)[i].getMaGD().substr(0, 4) == nam)
		{
			dsnam.push_back((*dsGiaoDich)[i]);
		}
	}
	cout << "\n--- CHI TIET GIAO DICH THEO THANG CUA NAM " << nam << "--- \n";
	string line_sep = "+-" + string(10, '-') + "-+-" + string(15, '-') + "-+-" + string(15, '-') + "-+-" + string(15, '-') + "-+";
	cout << line_sep << endl;

	cout << "| " << left << setw(10) << "Thang"
		<< " | " << left << setw(15) << "Tong Thu"
		<< " | " << left << setw(15) << "Tong Chi"
		<< " | " << left << setw(15) << "Chenh lech" << " |" << endl;

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
		long long chenhLech = tongThu - tongChi;

		cout << "| " << left << setw(10) << k
			<< " | " << left << setw(15) << tongThu
			<< " | " << left << setw(15) << tongChi
			<< " | " << left << setw(15) << chenhLech << " |" << endl;
	}
	cout << line_sep << endl;
}

GiaoDich* QuanLyGD::tim_GD(const string& magd)
{
	for (int i = 0; i < dsGiaoDich->get_size(); i++)
	{
		if ((*dsGiaoDich)[i].getMaGD() == magd) return &(*dsGiaoDich)[i];
	}
	return nullptr;
}