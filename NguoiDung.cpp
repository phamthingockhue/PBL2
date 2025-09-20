#include <iostream>
#include <string>
#include "NguoiDung.h"
using namespace std;

NguoiDung::NguoiDung() {};
NguoiDung::NguoiDung(const string& Id, const string& Ten, const string& MatKhau, const string& Email)
{
	this->MaND = Id;
	this->TenND = Ten;
	this->MatKhau = MatKhau;
	this->Email = Email;
}
string NguoiDung::getID() const
{
	return this->MaND;
}
string NguoiDung::getTen() const
{
	return this->TenND;
}
string NguoiDung::getMatKhau() const
{
	return this->MatKhau;
}
string NguoiDung::getEmail() const
{
	return this->Email;
}
void NguoiDung::setTen(string& Ten)
{
	this->TenND = Ten;
}
void NguoiDung::setMatKhau(string& Mk)
{
	this->MatKhau = Mk;
}
void NguoiDung::setEmail(string& Email)
{
	this->Email = Email;
}
