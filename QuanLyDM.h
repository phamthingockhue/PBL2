#include "MyVector.h"

class QuanLyDM {
private:
	MyVector<DanhMuc*>* dsDanhMuc;
public:
	QuanLyDM(MyVector<DanhMuc*>* dsdm)
	{
		dsDanhMuc = dsdm;
	}
	void inDanhSachDM() const {
		string line_sep = "+-" + string(7, '-') + "-+-" + string(20, '-') + "-+-" + string(18, '-') + "-+";
		cout << line_sep << endl;
		cout << "| " << left << setw(7) << "Ma DM" << " | "
			<< left << setw(20) << "Ten DM" << " | "
			<< left << setw(18) << "Loai DM" << " |" << endl;
		cout << line_sep << endl;

		for (size_t i = 0; i < dsDanhMuc->get_size(); ++i) {
			cout << "| " << left << setw(7) << (*dsDanhMuc)[i]->getMaDM() << " | "
				<< left << setw(20) << (*dsDanhMuc)[i]->getTenDM() << " | "
				<< left << setw(18) << (*dsDanhMuc)[i]->getLoaiDM() << " |" << endl;
		}
		cout << line_sep << endl;
	}
	DanhMuc* TimDM(int maDM) {
		for (auto dmuc : *dsDanhMuc)
			if (dmuc->getMaDM() == maDM) return dmuc;
		return nullptr;
	}

};