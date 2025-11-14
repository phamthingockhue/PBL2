#include "QuanLyChiTietGD.h"
#include <iostream>
using namespace std;

void QuanLyChiTietGD::capNhatSoDuVi(long long soTienGD) {
	for (int i = 0; i < dsChiTietGD.get_size(); ++i) {
		ChiTietGD* ct = dsChiTietGD[i];
		if (!ct) continue;

		Vi* vi = ct->getVi();
		DanhMuc* dm = ct->getDanhMuc();

		if (!vi || !dm) continue;

		if (dm->getLoaiDM() == "Chi") {
			vi->truTien(soTienGD);
		}
		else {
			vi->congTien(soTienGD);
		}
	}
}

Vi* QuanLyChiTietGD::timVi(const int& mavi) {
	for (int i = 0; i < dm.dsVi.get_size(); ++i) {
		if (dm.dsVi[i].getMaVi() == mavi)
			return &dm.dsVi[i];
	}
	return nullptr;
}

GiaoDich* QuanLyChiTietGD::timHoacTaoGDTheoNgay(const string& magd) {
	for (int i = 0; i < dm.dsGiaoDich.get_size(); ++i) {
		if (dm.dsGiaoDich[i].getMaGD() == magd)
			return &dm.dsGiaoDich[i];
	}

	cout << "Tạo mã giao dịch mới cho ngày: " << magd << endl;
	GiaoDich gdMoi(magd);
	dm.dsGiaoDich.push_back(gdMoi);
	return &dm.dsGiaoDich.back();
}

DanhMuc* QuanLyChiTietGD::timDM(const int& madm) {
	for (int i = 0; i < dm.dsDanhMuc.get_size(); ++i) {
		if (dm.dsDanhMuc[i]->getMaDM() == madm)
			return dm.dsDanhMuc[i];
	}
	return nullptr;
}


void QuanLyChiTietGD::themChiTietGD(const ChiTietGD& ctgd) {
	ChiTietGD* newCt = new ChiTietGD(ctgd);
	dsChiTietGD.push_back(newCt);
}

QuanLyChiTietGD::~QuanLyChiTietGD() {
	for (int i = 0; i < dsChiTietGD.get_size(); ++i) {
		delete dsChiTietGD[i];
	}
	dsChiTietGD.clear();
}