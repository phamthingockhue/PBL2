#pragma once

#include "DataManager.h"
#include "QuanLyND.h"
#include "QuanLyCTGD.h"
#include "QuanLyVi.h"
#include "QuanLyGD.h"
#include "QuanLyDM.h"
#include <string>
#include <conio.h>

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
    void showMenuQuanLyGD();
    void showMenuBaoCao();
    void showMenuQuanLyNguoiDung();

    void XuLyDangNhap();
    void XuLyDangKy();
    void XuLyThemGD();
    void XuLySuaMK();
    bool XuLyXoaTK();
    void XuLyChinhSuaGD();
    void XuLyChinhSuaCTGD();
    void XuLyXoaGD();
    void XuLyXoaCTGD();
    void XuLyXemThongTinTaiKhoan();

    MyVector<string> locGDTheoKhoangTG(const string& tuNgay, const string& denNgay);
    MyVector<ChiTietGD*> locCTGDTheoKhoangTG(const string& tuNgay, const string& denNgay);
    void hienThiDSGDDaLoc(const MyVector<string>& dsNgay);
    void hienThiDSCTGDDaLoc(const MyVector<ChiTietGD*>& dsCT);

    long long inputLong(string prompt, long long oldVal);
    string inputString(string prompt, string oldval);
    bool kiemTraNgayHopLe(const string& ngay);
    bool checkEscPressed();

    template <typename T>
    static T getInput(const string& prompt);

    string getInputWithEsc(const string& prompt, bool& escaped);

    void clearScreen();

public:
    XuLyThaoTac();
    ~XuLyThaoTac();
    void run();
};

template<>
string XuLyThaoTac::getInput<string>(const string& prompt);
