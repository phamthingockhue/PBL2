#pragma once
#include "DataManager.h"
#include "QuanLyND.h"
#include "QuanLyChiTietGD.h"
#include "DanhMuc.h"
#include "QuanLyVi.h"
#include "GiaoDich.h"
#include <string>

class XuLyThaoTac {
private:
    DataManager dm;
    QuanLyND nd;
    NguoiDung* nguoiDungHienTai = nullptr;

    // --- Menus ---

    void showLoginMenu();
    void showMainMenu();

    // --- Handlers ---
    void XuLyDangNhap();
    void XuLyDangKy();
    void XuLyThemGD();
    //void XuLyXemDSGD();
    //void XuLyXemThongKe();


    // --- Helpers ---
    int getIntInput(const std::string& prompt);
    std::string getStringInput(const std::string& prompt);
    //wait->enter
    //display danhsach
    void clearScreen();
    string timLoaiDM(int);
    Vi* timVi(int);
    DanhMuc* timDanhMuc(int);
public:
    XuLyThaoTac();
    void run();
};
