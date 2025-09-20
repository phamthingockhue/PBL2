#include "NguoiDung.h"
#include <Vector>
class QuanLyNguoiDung
{
private:
	vector<NguoiDung> ds;
public:
	void DocFile(string);
	void XuatFile(string);
	void ThemNguoiDung();
	int TimID();
	bool KiemTraMK(int);
	NguoiDung SaoChep(int);
	void XoaNguoiDung();
	void SuaNguoiDung();
	void XemND() const;
};

