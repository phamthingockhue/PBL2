#pragma once
#include "MyVector.h"
#include "Vi.h"

class QuanLyVi {
private:
	MyVector<Vi>* dsVi;
public:
	QuanLyVi(MyVector<Vi>* dsv)
	{
		dsVi = dsv;
	}

	void inDanhSachVi(){
		string line_sep = "+-" + string(7, '-') + "-+-" + string(20, '-') + "-+-" + string(18, '-') + "-+";
		cout << line_sep << endl;
		cout << "| " << left << setw(7) << "Ma Vi" << " | "
			<< left << setw(20) << "Ten Vi" << " | "
			<< left << setw(18) << "So Du Vi (kVND)" << " |" << endl;
		cout << line_sep << endl;

		for (int i = 0; i < dsVi->get_size(); ++i) {
			cout << "| " << left << setw(7) << (*dsVi)[i].getMaVi() << " | "
				<< left << setw(20) << (*dsVi)[i].getTenVi() << " | "
				<< left << setw(18) << (*dsVi)[i].getSoDu() << " |" << endl;
		}
		cout << line_sep << endl;
	}
	Vi* TimVi(int maVi) {
		for (int i = 0; i < dsVi->get_size(); i++)
		{
			if ((*dsVi)[i].getMaVi() == maVi) return &(*dsVi)[i];
		}
		return nullptr;
	}

	void capNhatSoDu(int maVi, long long soTien, const string& loaiDM) {
		for (int i = 0; i < dsVi->get_size(); i++) {
			if ((*dsVi)[i].getMaVi() == maVi) {
				if (loaiDM == "Thu") (*dsVi)[i].setSoDu((*dsVi)[i].getSoDu() + soTien);
				else if (loaiDM == "Chi") (*dsVi)[i].setSoDu((*dsVi)[i].getSoDu() - soTien);
				return;
			}
		}
	}
};

