#pragma once
#include "DataManager.h"
#include "QuanLyND.h"
#include "QuanLyChiTietGD.h"
#include "QuanLyVi.h"
#include "QuanLyGD.h"
#include "QuanLyDM.h"
#include "DanhMuc.h"
#include "GiaoDich.h"
#include <string>

class XuLyThaoTac {
private:
    DataManager dm;
    QuanLyND nd;
    QuanLyGD gd;
    QuanLyVi vi;
    QuanLyDM dmuc;
    NguoiDung* nguoiDungHienTai = nullptr;

    // --- Menus ---

    void showLoginMenu();
    void showMainMenu();

    // --- Handlers ---
    void XuLyDangNhap();
    void XuLyDangKy();
    void XuLyThemGD();
    void XuLySuaMK();
    bool XuLyXoaTK();


    // --- Helpers ---
    int getIntInput(const std::string& prompt);
    std::string getStringInput(const std::string& prompt);
    //wait->enter
    //display danhsach
    void clearScreen();
public:
    XuLyThaoTac();
    void run();
};
