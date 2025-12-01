#include <iomanip>
#include "QuanLyCTGD.h"

void QuanLyCTGD::inDanhSachCTGDTheoNgay(string magd) 
{
    string line = "+-" + string(10, '-') + "-+-"
        + string(10, '-') + "-+-"
        + string(20, '-') + "-+-"
        + string(20, '-') + "-+-"
        + string(30, '-') + "-+-"
        + string(15, '-') + "-+";

    cout << "\n--- CHI TIET GIAO DICH NGAY: " << magd << " ---\n";
    cout << line << endl;

    cout << "| " << left << setw(10) << "Ma GD" << " | "
        << left << setw(10) << "Ma CT" << " | "
        << left << setw(20) << "Ten Vi" << " | "
        << left << setw(20) << "Danh Muc" << " | "
        << left << setw(30) << "Mo Ta" << " | "
        << right << setw(15) << "So Tien" << " |" << endl;
    cout << line << endl;

    bool found = false;
    for (int i = 0; i < dsChiTietGD->get_size(); i++)
    {
		if ((*dsChiTietGD)[i]->getMaGD() == magd)
		{
			ChiTietGD* ct = (*dsChiTietGD)[i];
			string tenVi = (ct->getVi()) ? ct->getVi()->getTenVi() : "---";
			string tenDM = (ct->getDanhMuc()) ? ct->getDanhMuc()->getTenDM() : "---";

			cout << "| " << left << setw(10) << ct->getMaGD() << " | "
				<< left << setw(10) << ct->getMaCTGD() << " | "
				<< left << setw(20) << tenVi << " | "
				<< left << setw(20) << tenDM << " | "
				<< left << setw(30) << ct->getMoTa() << " | "
				<< right << setw(15) << ct->getSoTienGD() << " |" << endl;
		}
    }
    cout << line << endl;
}

ChiTietGD* QuanLyCTGD::taoChiTiet(string maGD, int maVi, int maDM, string moTa, long long soTien) {
	ChiTietGD* ct = new ChiTietGD(maGD, maVi, maDM, moTa, soTien);
	dsChiTietGD->push_back(ct);
	return ct;
}

void QuanLyCTGD::themChiTiet(ChiTietGD& ct) {
	dsChiTietGD->push_back(&ct);
}

void QuanLyCTGD::capNhatMaGD(const string& oldID, const string& newID) {
	for (auto& ct : *dsChiTietGD)
		if (ct->getMaGD() == oldID) ct->setMaGD(newID);
}

void QuanLyCTGD::xoaCTGD(int maCTGD) {
	for (int i = 0; i < dsChiTietGD->get_size(); i++) {
		if ((*dsChiTietGD)[i]->getMaCTGD() == maCTGD) {
			dsChiTietGD->erase(i);
			return;
		}
	}
}

void QuanLyCTGD::suaMaGiaoDich_CTGD(string oldMaGD, string newMaGD)
{
	for (int i = 0; i < dsChiTietGD->get_size(); i++)
	{
		if ((*dsChiTietGD)[i]->getMaGD() == oldMaGD)
		{
			(*dsChiTietGD)[i]->setMaGD(newMaGD);
		}
	}
}

bool QuanLyCTGD::suaCTGD(int maCTGD, string newMaGD, string newMoTa, long long newSoTien) {
	for (int i = 0; i < dsChiTietGD->get_size(); i++)
	{
		if ((*dsChiTietGD)[i]->getMaCTGD() == maCTGD)
		{
			(*dsChiTietGD)[i]->setMaGD(newMaGD);
			(*dsChiTietGD)[i]->setMota(newMoTa);
			(*dsChiTietGD)[i]->setSoTienGD(newSoTien);
		}
	}
	return true;
}

ChiTietGD* QuanLyCTGD::timCTGD(int maCTGD)
{
	for (int i = 0; i < dsChiTietGD->get_size(); i++)
	{
		if ((*dsChiTietGD)[i]->getMaCTGD() == maCTGD) return (*dsChiTietGD)[i];
	}
	return nullptr;
}