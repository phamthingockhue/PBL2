#include <iostream>
#include <fstream>
#include <sstream> 
#include "QuanLyNguoiDung.h"
using namespace std;

void QuanLyNguoiDung::DocFile(string TenFile)
{
    ifstream users_in(TenFile);
    if (!users_in.is_open()) {
        cout << "Khong mo duoc file!" << endl;
        return;
    }
    string line;
    while (getline(users_in, line)) {
        stringstream ss(line);
        string Id, Ten, Mk, Email;

        getline(ss, Id, ',');
        getline(ss, Ten, ',');
        getline(ss, Mk, ',');
        getline(ss, Email, ',');

        if (!Id.empty() && Id[0] == ' ') Id.erase(0, 1);
        if (!Ten.empty() && Ten[0] == ' ') Ten.erase(0, 1);
        if (!Mk.empty() && Mk[0] == ' ') Mk.erase(0, 1);
        if (!Email.empty() && Email[0] == ' ') Email.erase(0, 1);

        ds.push_back(NguoiDung(Id, Ten, Mk, Email));
    }
    users_in.close();
}

void QuanLyNguoiDung::XuatFile(string TenFile)
{
    ofstream users_out(TenFile);
    if (!users_out.is_open()) return;

    for (NguoiDung list : ds)
    {
        users_out << list.getID() << ", "
            << list.getTen() << ", "
            << list.getMatKhau() << ", "
            << list.getEmail() << endl;
    }
    users_out.close();
}

int QuanLyNguoiDung::TimID()
{
    string temp;
    cout << "Nhap ID Nguoi Dung: ";
    cin >> temp;
    for (int i = 0; i < ds.size(); i++)
    {
        if (temp == ds[i].getID()) return i;
    }
    return -1;
}

void QuanLyNguoiDung::ThemNguoiDung()
{
    string Id, Ten, Mk, Email;
    cout << "Nhap ma ND: ";
    cin >> Id;
    for (int i = 0; i < ds.size(); i++)
    {
        if (Id == ds[i].getID())
        {
            cout << "Ma nguoi dung da ton tai!!" << endl;
            return;
        }
    }
    cin.ignore();
    cout << "Nhap ten ND: ";
    getline(cin, Ten);
    cout << "Nhap mat khau: ";
    getline(cin, Mk);
    cout << "Nhap Email: ";
    getline(cin, Email);
    NguoiDung temp(Id, Ten, Mk, Email);
    ds.push_back(temp);

    ofstream users_out("DSNguoiDung.txt", ios::app);
    users_out << Id << ", "
        << Ten << ", "
        << Mk << ", "
        << Email << endl;
    users_out.close();

    cout << "Nguoi dung da duoc tao!" << endl << endl;
}

bool QuanLyNguoiDung::KiemTraMK(int index)
{
    string temp;
    cout << "Nhap Mat Khau: ";
    cin >> temp;
    if (ds[index].getMatKhau() == temp) return true;
    return false;
}

NguoiDung QuanLyNguoiDung::SaoChep(int index)
{
    return ds[index];
}

void QuanLyNguoiDung::XoaNguoiDung()
{
    int index = TimID();
    if (index != -1)
    {
        if (KiemTraMK(index))
        {
            ds.erase(ds.begin() + index);
            XuatFile("DSNguoiDung.txt");
            cout << "Da xoa nguoi dung!!" << endl << endl;
            return;
        }
        else
        {
            cout << "Mat khau khong hop le!!" << endl << endl;
            return;
        }
    }
    else
    {
        cout << "Khong tim thay ID" << endl << endl;
        return;
    }
}

void QuanLyNguoiDung::SuaNguoiDung()
{
    int index = TimID();
    if (index != -1)
    {
        if (KiemTraMK(index))
        {
            NguoiDung temp1 = SaoChep(index);
            int choice;
            string Id, Ten, Mk, Email;
            cout << "< CAP NHAT THONG TIN NGUOI DUNG >" << endl;
            cout << "Nhap thong tin ban muon sua: " << endl << "1: Sua ten nguoi dung" << endl << "2: Sua mat khau" << endl << "3: Sua Email" << endl << "4: Thoat!" << endl;
            cin >> choice;
            cin.ignore();
            NguoiDung update = temp1;
            switch (choice) {
            case 1:
                cout << "Nhap ten moi: ";
                getline(cin, Ten);
                update.setTen(Ten);
                break;
            case 2:
                cout << "Nhap mat khau moi: ";
                cin >> Mk;
                update.setMatKhau(Mk);
                break;
            case 3:
                cout << "Nhap email moi: ";
                cin >> Email;
                update.setEmail(Email);
                break;
            case 4:
                cout << "Da Thoat" << endl << endl;
                break;
            default:
                cout << "Du lieu muon sua khong hop le!!" << endl << endl;
                return;
            }
            ds[index] = update;
            XuatFile("DSNguoiDung.txt");
            cout << "Da cap nhat thong tin thanh cong!" << endl << endl;
        }
        else
        {
            cout << "Mat khau khong hop le!!" << endl << endl;
            return;
        }
    }
    else
    {
        cout << "Khong tim thay ID" << endl << endl;
        return;
    }
}

void QuanLyNguoiDung::XemND() const
{
    cout << endl << "< DANH SACH NGUOI DUNG >" << endl;
    for (int i = 0; i < ds.size(); i++)
    {
        string hiddenPassword = string(ds[i].getMatKhau().length(), '*');
        cout << "Ma nguoi dung: " << ds[i].getID() << endl
            << "Ten nguoi dung: " << ds[i].getTen() << endl
            << "Mat khau: " << hiddenPassword << endl
            << "Email: " << ds[i].getEmail() << endl << endl;
    }
}