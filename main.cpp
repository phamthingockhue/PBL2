#include "QuanLyNguoiDung.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	QuanLyNguoiDung QuanLyND;
    int choice;
    string TenFile = "DSNguoiDung.txt";
    QuanLyND.DocFile(TenFile);

    do {
        cout << endl << "<-- QUAN LY NGUOI DUNG -->" << endl
             << "1. Them nguoi dung moi" << endl
             << "2. Xoa nguoi dung" << endl
             << "3. Cap nhat thong tin nguoi dung" << endl
             << "4. Xem danh sach nguoi dung" << endl
             << "5. Thoat" << endl
             << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: 
            QuanLyND.ThemNguoiDung(); 
            break;
        case 2: 
            QuanLyND.XoaNguoiDung(); 
            break;
        case 3: 
            QuanLyND.SuaNguoiDung();
            break;
        case 4: 
            QuanLyND.XemND();
            break;
        case 5:
            cout << "Thoat danh muc nguoi dung";
            break;
        default: 
            cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 5);
    system("pause");
    return 0;
}