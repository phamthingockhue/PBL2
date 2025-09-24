#include <iostream>
#include <string>
using namespace std;

class NguoiDung
{
private:
	string MaND;
	string TenND;
	string MatKhau;
	string Email;
public:
	NguoiDung();
	NguoiDung(const string&, const string&, const string&, const string&);
	string getID() const;
	string getTen() const;
	string getMatKhau() const;
	string getEmail() const;
	void setTen(string&);
	void setMatKhau(string&);
	void setEmail(string&);
};
