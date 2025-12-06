#pragma once

#include "DataManager.h"
#include "QuanLyND.h"
#include "QuanLyCTGD.h"
#include "QuanLyVi.h"
#include "QuanLyGD.h"
#include "QuanLyDM.h"
#include <string>

class XuLyThaoTac {
private:
    DataManager dm;

    QuanLyND* qlND;
    QuanLyDM* qlDM;
    QuanLyVi* qlVi;
    QuanLyGD* qlGD;
    QuanLyCTGD* qlCTGD;
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
    void XuLyChinhSuaGD();
    void XuLyChinhSuaCTGD();
    void XuLyXoaGD();
    void XuLyXoaCTGD();


    // --- Helpers ---
    // int getIntInput(const string& prompt);
    // string getStringInput(const string& prompt);
    long long inputLong(string prompt, long long oldVal);
    string inputString(string prompt, string oldval);

    template <typename T>
    static T getInput(const string& prompt);
    void clearScreen();
public:
    XuLyThaoTac();
    ~XuLyThaoTac();
    void run();
};
template<>
string XuLyThaoTac::getInput<string>(const string& prompt);
