#include <iostream>
#include "QuanLyND.h"
#include "DataManager.h"
#include <filesystem>
#include <conio.h>
using namespace std;
namespace fs = filesystem;

NguoiDung* QuanLyND::xacThuc(const string& userid, const string& password) {
    for (size_t i = 0; i < dsNguoiDung->get_size(); i++) {
        NguoiDung& nd = (*dsNguoiDung)[i];
        if (nd.getID() == userid && nd.getMatKhau() == password) {
            return &nd;
        }
    }
    return nullptr;
}

bool QuanLyND::DangKy(const string& userid, const string& name, const string& password) {
    NguoiDung newUser(userid, name, password);
    dsNguoiDung->push_back(newUser);
    return true;
}

int QuanLyND::KiemTraMK(const string& userid, const string& password)
{
    for (int i = 0; i < dsNguoiDung->get_size(); i++)
    {
        if ((*dsNguoiDung)[i].getID() == userid)
        {
            return ((*dsNguoiDung)[i].getMatKhau() == password) ? i : -1;
        }
    }
    return -1;
}

void QuanLyND::DoiMK(int index, const string& mk)
{
    if (index >= 0 && index < dsNguoiDung->get_size())
    {
        (*dsNguoiDung)[index].setMatKhau(mk);
    }
}

void QuanLyND::XoaTaiKhoan(int index)
{
    if (index >= 0 && index < dsNguoiDung->get_size())
    {
        dsNguoiDung->erase(index);
    }
}

string QuanLyND::AnMK()
{
    string pass = "";
    char ch;

    while (true) {
        ch = _getch();

        if (ch == 13) break;
        else if (ch == 8)
        {
            if (!pass.empty())
            {
                pass.pop_back();
                cout << "\b \b";
            }
        }
        else {
            pass.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return pass;
}
