#include "XuLyThaoTac.h"
#include <iostream>
#include <limits>
#include <cstdlib> 
#include <ctime>
#include <filesystem>
#include <iomanip>
using namespace std;
namespace fs = filesystem;

XuLyThaoTac::XuLyThaoTac()
{
    dm.setBasePath("D:/projects/finance_app/data/");
    try {
        if (!fs::exists(dm.getBasePath())) {
            fs::create_directories(dm.getBasePath());
        }
    }
    catch (const std::exception& e) {
        cerr << "Loi filesystem: " << e.what() << "\n";
    }

    dm.loadNguoiDung(dm.getBasePath() + "users.txt", dm.getDsNguoiDung());
    qlND = new QuanLyND(&dm.getDsNguoiDung());
    qlDM = new QuanLyDM(&dm.getDsDanhMuc());
    qlVi = new QuanLyVi(&dm.getDsVi());
    qlGD = new QuanLyGD(&dm.getDsGiaoDich(), &dm.getDsChiTietGD());
    qlCTGD = new QuanLyCTGD(&dm.getDsChiTietGD());
}

XuLyThaoTac::~XuLyThaoTac()
{
    delete qlND;
    delete qlDM;
    delete qlVi;
    delete qlGD;
    delete qlCTGD;
}

void XuLyThaoTac::run() 
{
    while (true) {
        showLoginMenu();
    }
}

// ==================== HELPER FUNCTIONS ====================

bool XuLyThaoTac::checkEscPressed() {
    if (_kbhit()) {
        char ch = _getch();
        if (ch == 27) { // ESC key
            return true;
        }
    }
    return false;
}

bool XuLyThaoTac::kiemTraNgayHopLe(const string& ngay) {
    if (ngay.length() != 8) return false;
    for (char c : ngay) {
        if (!isdigit(c)) return false;
    }
    int year = stoi(ngay.substr(0, 4));
    int month = stoi(ngay.substr(4, 2));
    int day = stoi(ngay.substr(6, 2));
    
    if (year<=0 ) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    
    return true;
}

MyVector<string> XuLyThaoTac::locGDTheoKhoangTG(const string& tuNgay, const string& denNgay) {
    MyVector<string> result;
    for (int i = 0; i < dm.getDsGiaoDich().get_size(); i++) {
        string maGD = dm.getDsGiaoDich()[i].getMaGD();
        if (maGD >= tuNgay && maGD <= denNgay) {
            result.push_back(maGD);
        }
    }
    return result;
}

MyVector<ChiTietGD*> XuLyThaoTac::locCTGDTheoKhoangTG(const string& tuNgay, const string& denNgay) {
    MyVector<ChiTietGD*> result;
    for (int i = 0; i < dm.getDsChiTietGD().get_size(); i++) {
        string maGD = dm.getDsChiTietGD()[i]->getMaGD();
        if (maGD >= tuNgay && maGD <= denNgay) {
            result.push_back(dm.getDsChiTietGD()[i]);
        }
    }
    return result;
}

void XuLyThaoTac::hienThiDSGDDaLoc(const MyVector<string>& dsNgay) {
    if (dsNgay.get_size() == 0) {
        cout << "\nKhong tim thay giao dich nao trong khoang thoi gian nay!\n";
        return;
    }
    
    string line = "+-" + string(12, '-') + "-+-" + string(15, '-') + "-+-" + string(15, '-') + "-+";
    cout << "\n--- DANH SACH GIAO DICH DA LOC ---\n";
    cout << line << endl;
    cout << "| " << left << setw(12) << "Ma GD" << " | "
         << left << setw(15) << "Tong Thu" << " | "
         << left << setw(15) << "Tong Chi" << " |" << endl;
    cout << line << endl;

    for (int i = dsNgay.get_size() - 1; i >= 0; i--) {
        GiaoDich* gd = qlGD->tim_GD(dsNgay[i]);
        if (gd) {
            cout << "| " << left << setw(12) << gd->getMaGD() << " | "
                 << right << setw(15) << gd->getTongThu() << " | "
                 << right << setw(15) << gd->getTongChi() << " |" << endl;
        }
    }
    cout << line << endl;
}

void XuLyThaoTac::hienThiDSCTGDDaLoc(const MyVector<ChiTietGD*>& dsCT) {
    if (dsCT.get_size() == 0) {
        cout << "\nKhong tim thay chi tiet giao dich nao trong khoang thoi gian nay!\n";
        return;
    }
    
    string line = "+-" + string(10, '-') + "-+-" + string(10, '-') + "-+-"
                + string(20, '-') + "-+-" + string(20, '-') + "-+-"
                + string(30, '-') + "-+-" + string(15, '-') + "-+";

    cout << "\n--- DANH SACH CHI TIET GIAO DICH DA LOC ---\n";
    cout << line << endl;
    cout << "| " << left << setw(10) << "Ma GD" << " | "
         << left << setw(10) << "Ma CT" << " | "
         << left << setw(20) << "Ten Vi" << " | "
         << left << setw(20) << "Danh Muc" << " | "
         << left << setw(30) << "Mo Ta" << " | "
         << right << setw(15) << "So Tien" << " |" << endl;
    cout << line << endl;

    for (int i = dsCT.get_size() - 1; i >= 0; i--) {
        ChiTietGD* ct = dsCT[i];
        string tenVi = (ct->getVi()) ? ct->getVi()->getTenVi() : "---";
        string tenDM = (ct->getDanhMuc()) ? ct->getDanhMuc()->getTenDM() : "---";

        cout << "| " << left << setw(10) << ct->getMaGD() << " | "
             << left << setw(10) << ct->getMaCTGD() << " | "
             << left << setw(20) << tenVi << " | "
             << left << setw(20) << tenDM << " | "
             << left << setw(30) << ct->getMoTa() << " | "
             << right << setw(15) << ct->getSoTienGD() << " |" << endl;
    }
    cout << line << endl;
}

// ==================== MENUS ====================

void XuLyThaoTac::showLoginMenu() {
    cout << string(65, '=') << endl;
    cout << "              PBL2: DU AN CO SO LAP TRINH              " << endl;
    cout << "           DE TAI: UNG DUNG QUAN LY CHI TIEU           " << endl;
    cout << string(65, '=') << endl;

    cout << "| " << left << setw(30) << "Ho va Ten"
        << " | " << left << setw(15) << "MSSV"
        << " | " << left << setw(10) << "Lop" << " |" << endl;

    cout << "| " << string(30, '-')
        << " | " << string(15, '-')
        << " | " << string(10, '-') << " |" << endl;

    cout << "| " << left << setw(30) << "Pham Thi Ngoc Khue"
        << " | " << left << setw(15) << "102240375"
        << " | " << left << setw(10) << "99B" << " |" << endl;

    cout << "| " << left << setw(30) << "Dau Thuy Ngan"
        << " | " << left << setw(15) << "102240382"
        << " | " << left << setw(10) << "99B" << " |" << endl;

    cout << string(65, '=') << endl;

    string line_sep = "+-" + string(30, '-') + "-+";
    cout << line_sep << endl;
    cout << "| " << "       QUAN LY CHI TIEU       " << " |" << endl;
    cout << line_sep << endl;
    cout << "| " << left << setw(30) << " 1. Dang nhap" << " |" << endl;
    cout << "| " << left << setw(30) << " 2. Dang ky" << " |" << endl;
    cout << "| " << left << setw(30) << " 0. Thoat" << " |" << endl;
    cout << line_sep << endl;
    int choice = getInput<int>("Chon: ");

    switch (choice) {
    case 1:
        XuLyDangNhap();
        break;
    case 2:
        XuLyDangKy();
        break;
    case 0:
        cout << "Tam biet!\n";
        exit(0);
    default:
        cout << "Lua chon khong hop le.\n";
        break;
    }
}

void XuLyThaoTac::showMainMenu() {
    int choice;
    do {
        string line_sep = "+-" + string(45, '-') + "-+";
        cout << line_sep << endl;
        string title = "MENU CHINH";

        int pad_left = (45 - title.length()) / 2;
        int pad_right = 45 - title.length() - pad_left;
        cout << "| " << string(pad_left, ' ') << title << string(pad_right, ' ') << " |" << endl;
        cout << line_sep << endl;
        cout << "| " << left << setw(45) << " 1. Quan ly giao dich" << " |" << endl;
        cout << "| " << left << setw(45) << " 2. Bao cao & Thong ke" << " |" << endl;
        cout << "| " << left << setw(45) << " 3. Xem danh muc" << " |" << endl;
        cout << "| " << left << setw(45) << " 4. Xem vi" << " |" << endl;
        cout << "| " << left << setw(45) << " 5. Quan ly nguoi dung" << " |" << endl;
        cout << "| " << left << setw(45) << " 0. Dang xuat" << " |" << endl;
        cout << line_sep << endl;
        cout << "Chon: ";
        choice = getInput<int>("");

        switch (choice) {
        case 1:
            clearScreen();
            showMenuQuanLyGD();
            break;
        case 2:
            clearScreen();
            showMenuBaoCao();
            break;
        case 3: {
            clearScreen();
            cout << "\n--- DANH MUC ---\n";
            qlDM->inDanhSachDM();
            cout << "\nNhan Enter de tro ve menu...";
            cin.get();
            clearScreen();
            break;
        }
        case 4: {
            clearScreen();
            cout << "\n--- DANH SACH VI ---\n";
            qlVi->inDanhSachVi();
            cout << "\nNhan Enter de tro ve menu...";
            cin.get();
            clearScreen();
            break;
        }
        case 5:
            clearScreen();
            showMenuQuanLyNguoiDung();
            if (nguoiDungHienTai == nullptr)
            {
                return;
            }
            break;
        case 0: {
            clearScreen();
            cout << "Dang xuat va luu du lieu...\n";
            dm.saveDataNguoiDung(nguoiDungHienTai);
            nguoiDungHienTai = nullptr;
            clearScreen();
            return;
        }
        default:
            clearScreen();
            cout << "Lua chon khong hop le.\n";
            clearScreen();
        }
    } while (choice != 0);
}

void XuLyThaoTac::showMenuQuanLyGD() {
    int choice;
    do {
        string line_sep = "+-" + string(45, '-') + "-+";
        cout << line_sep << endl;
        string title = "QUAN LY GIAO DICH";
        int width = 45;
        int leftPadding = (width - title.length()) / 2;
        int rightPadding = width - title.length() - leftPadding;
        cout << "| " 
            << string(leftPadding, ' ') 
            << title 
            << string(rightPadding, ' ')
            << " |" << endl;
        cout << line_sep << endl;
        cout << "| " << left << setw(45) << " 1. Them giao dich" << " |" << endl;
        cout << "| " << left << setw(45) << " 2. Sua giao dich" << " |" << endl;
        cout << "| " << left << setw(45) << " 3. Xoa giao dich" << " |" << endl;
        cout << "| " << left << setw(45) << " 4. Sua chi tiet giao dich" << " |" << endl;
        cout << "| " << left << setw(45) << " 5. Xoa chi tiet giao dich" << " |" << endl;
        cout << "| " << left << setw(45) << " 0. Quay lai menu chinh" << " |" << endl;
        cout << line_sep << endl;
        cout << "(Nhan ESC bat ky luc nao de huy thao tac)\n";
        choice = getInput<int>("Chon: ");

        switch (choice) {
        case 1:
            clearScreen();
            XuLyThemGD();
            cout << "\nNhan Enter de tro ve menu...";
            cin.get();
            clearScreen();
            break;
        case 2:
            clearScreen();
            XuLyChinhSuaGD();
            cout << "\nNhan Enter de tro ve menu...";
            cin.get();
            clearScreen();
            break;
        case 3:
            clearScreen();
            XuLyXoaGD();
            cout << "\nNhan Enter de tro ve menu...";
            cin.get();
            clearScreen();
            break;
        case 4:
            clearScreen();
            XuLyChinhSuaCTGD();
            cout << "\nNhan Enter de tro ve menu...";
            cin.get();
            clearScreen();
            break;
        case 5:
            clearScreen();
            XuLyXoaCTGD();
            cout << "\nNhan Enter de tro ve menu...";
            cin.get();
            clearScreen();
            break;
        case 0:
            clearScreen();
            return;
        default:
            clearScreen();
            cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 0);
}

void XuLyThaoTac::showMenuBaoCao() {
    int choice;
    do {
       string line_sep = "+-" + string(45, '-') + "-+";
        cout << line_sep << endl;
        string title = "BAO CAO & THONG KE";
        int width = 45;
        int leftPadding = (width - title.length()) / 2;
        int rightPadding = width - title.length() - leftPadding;
        cout << "| " 
            << string(leftPadding, ' ') 
            << title 
            << string(rightPadding, ' ')
            << " |" << endl;
        cout << line_sep << endl;
        cout << "| " << left << setw(45) << " 1. Xem danh sach giao dich" << " |" << endl;
        cout << "| " << left << setw(45) << " 2. Xem chi tiet giao dich theo ngay" << " |" << endl;
        cout << "| " << left << setw(45) << " 3. Thong ke theo thang" << " |" << endl;
        cout << "| " << left << setw(45) << " 0. Quay lai menu chinh" << " |" << endl;
        cout << line_sep << endl;
        choice = getInput<int>("Chon: ");

        switch (choice) {
        case 1: {
            clearScreen();
            qlGD->inDanhSachGD();
            cout << "\nNhan Enter de tro ve menu...";
            cin.get();
            clearScreen();
            break;
        }
        case 2: {
            clearScreen();
            cout << "Vui long nhap ngay theo dinh dang (YYYYMMDD): ";
            string magd;
            getline(cin, magd);
            qlCTGD->inDanhSachCTGDTheoNgay(magd);
            cout << "\nNhan Enter de tro ve menu...";
            cin.get();
            clearScreen();
            break;
        }
        case 3: {
            clearScreen();
            string nam;
            cout << "Nhap nam can xem: ";
            getline(cin, nam);
            qlGD->thongKeTheoThang(nam);
            cout << "\nNhan Enter de tro ve menu...";
            cin.get();
            clearScreen();
            break;
        }
        case 0:
            clearScreen();
            return;
        default:
            clearScreen();
            cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 0);
}

void XuLyThaoTac::showMenuQuanLyNguoiDung() {
    int choice;
    do {
        string line_sep = "+-" + string(45, '-') + "-+";
        cout << line_sep << endl;
        string title = "QUAN LY NGUOI DUNG";
        int width = 45;
        int leftPadding = (width - title.length()) / 2;
        int rightPadding = width - title.length() - leftPadding;
        cout << "| " 
            << string(leftPadding, ' ') 
            << title 
            << string(rightPadding, ' ')
            << " |" << endl;
        cout << line_sep << endl;
        cout << "| " << left << setw(45) << " 1. Xem thong tin tai khoan" << " |" << endl;
        cout << "| " << left << setw(45) << " 2. Doi mat khau" << " |" << endl;
        cout << "| " << left << setw(45) << " 3. Xoa tai khoan" << " |" << endl;
        cout << "| " << left << setw(45) << " 0. Quay lai menu chinh" << " |" << endl;
        cout << line_sep << endl;
        choice = getInput<int>("Chon: ");

        switch (choice) {
        case 1:
            clearScreen();
            XuLyXemThongTinTaiKhoan();
            cout << "\nNhan Enter de tro ve menu...";
            cin.get();
            clearScreen();
            break;
        case 2:
            clearScreen();
            XuLySuaMK();
            cout << "\nNhan Enter de tro ve menu...";
            cin.get();
            clearScreen();
            break;
        case 3: {
            clearScreen();
            bool daXoa = XuLyXoaTK();
            if (daXoa) {
                cout << "\nNhan Enter de thoat...";
                cin.get();
                nguoiDungHienTai = nullptr;
                clearScreen();
                return;
            }
            else {
                cout << "\nNhan Enter de tro ve menu...";
                cin.get();
                clearScreen();
            }
            break;
        }
        case 0:
            clearScreen();
            return;
        default:
            clearScreen();
            cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 0);
}

// ==================== HANDLERS ====================

void XuLyThaoTac::XuLyDangNhap() {
    clearScreen();
    cout << "--- DANG NHAP ---\n";
    string tenDangNhap = getInput<string>("Ten dang nhap: ");
    cout << "Nhap mat khau: ";
    string matKhau = qlND->AnMK();

    nguoiDungHienTai = qlND->xacThuc(tenDangNhap, matKhau);

    if (nguoiDungHienTai) {
        cout << "Dang nhap thanh cong! Xin chao, " << nguoiDungHienTai->getTen() << "!\n";
        dm.loadDataNguoiDung(nguoiDungHienTai);

        cout << "\nNhan Enter de tiep tuc...";
        cin.get();

        clearScreen();
        showMainMenu();
    }
    else {
        cout << "Sai ten dang nhap hoac mat khau.\n";
    }
    cout << "\nNhan Enter de quay lai...";
    cin.get();

    clearScreen();
}

void XuLyThaoTac::XuLyDangKy() {
    clearScreen();
    cout << "--- DANG KY ---\n";
    string tenDangNhap = getInput<string>("Ten dang nhap: ");
    for (int i = 0; i < dm.getDsNguoiDung().get_size(); i++)
    {
        if (dm.getDsNguoiDung()[i].getID() == tenDangNhap)
        {
            cout << "Ten dang nhap da ton tai.\n";
            return;
        }
    }
    string tenHienThi = getInput<string>("Ten hien thi: ");
    cout << "Mat khau: ";
    string matKhau = qlND->AnMK();

    if (qlND->DangKy(tenDangNhap, tenHienThi, matKhau)) {
        cout << "Dang ky thanh cong! Ban co the dang nhap ngay.\n";
        string userFolder = dm.getBasePath() + "user_" + tenDangNhap + "/";
        if (!fs::exists(userFolder)) {
            fs::create_directory(userFolder);
            cout << "Da tao thu muc cho nguoi dung moi." << endl;
        }
        dm.default_user_folder(userFolder);
        dm.saveNguoiDung(dm.getBasePath() + "users.txt", dm.getDsNguoiDung());
    }
    cout << "\nNhan Enter tiep tuc...";
    cin.get();

    clearScreen();
}

void XuLyThaoTac::XuLyThemGD() {
    clearScreen();
    cout << "--- THEM GIAO DICH ---\n";
    cout << "(Nhan ESC de huy)\n\n";
    
    int vitri;
    time_t now = time(0);
    tm gio;
    localtime_s(&gio, &now);
    cout << "Hom nay la ngay: "
        << (1900 + gio.tm_year) << "-"
        << right << setfill('0') << setw(2) << (1 + gio.tm_mon) << "-"
        << setw(2) << gio.tm_mday << endl;
    cout << setfill(' ');

    cout << endl << "Nhac nho: 'Vui long nhap thoi gian giao dich dung dinh dang (YYYYMMDD)'" << endl << endl;
    
    bool escaped = false;
    string maGD = getInputWithEsc("Nhap thoi gian giao dich (YYYYMMDD): ", escaped);
    
    if (escaped) {
        cout << "\n(!) Da huy thao tac!\n";
        return;
    }
    
    while (maGD == "" || !kiemTraNgayHopLe(maGD))
    {
        cout << "Ma giao dich khong hop le!" << endl;
        maGD = getInputWithEsc("Nhap thoi gian giao dich (YYYYMMDD): ", escaped);
        if (escaped) {
            cout << "\n(!) Da huy thao tac!\n";
            return;
        }
    }
    
    GiaoDich* gd_cha = nullptr;
    for (size_t i = 0; i < dm.getDsGiaoDich().get_size(); ++i) {
        if (dm.getDsGiaoDich()[i].getMaGD() == maGD) {
            gd_cha = &dm.getDsGiaoDich()[i];
            for (int j = 0; j < dm.getDsChiTietGD().get_size(); j++)
            {
                if (dm.getDsChiTietGD()[j]->getMaGD() == maGD)
                {
                    gd_cha->themChiTiet(dm.getDsChiTietGD()[j]);
                }
            }
            vitri = i;
            break;
        }
    }

    if (gd_cha == nullptr) {
        GiaoDich gdMoi(maGD);
        dm.getDsGiaoDich().push_back(gdMoi);
        gd_cha = &dm.getDsGiaoDich().back();
        cout << "Tao Giao dich moi cho ngay: " << maGD << endl;
        vitri = dm.getDsGiaoDich().get_size() - 1;
    }
    else {
        cout << "Them chi tiet vao giao dich: " << maGD << endl;
    }
    
    while (true) {
        cout << "\n--DANH SACH VI---\n";
        qlVi->inDanhSachVi();
        
        int maVi;
        cout << "Nhap ma vi (hoac -1 de huy): ";
        cin >> maVi;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (maVi == -1) {
            cout << "\n(!) Da huy them chi tiet!\n";
            break;
        }
        
        Vi* vi = qlVi->TimVi(maVi);
        if (!vi) { 
            cout << "Ma vi khong hop le!" << endl; 
            continue;
        }

        cout << "\n--- DANH SACH DANH MUC ---\n";
        qlDM->inDanhSachDM();
        
        int maDM;
        cout << "Nhap ma danh muc (hoac -1 de huy): ";
        cin >> maDM;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (maDM == -1) {
            cout << "\n(!) Da huy them chi tiet!\n";
            break;
        }
        
        DanhMuc* danhmuc = qlDM->TimDM(maDM);
        if (!danhmuc) { 
            cout << "Ma danh muc khong hop le!" << endl; 
            continue;
        }

        string moTa = getInput<string>("Nhap mo ta: ");
        long long soTien = getInput<long long>("Nhap so tien giao dich: ");

        if (soTien <= 0)
        {
            cout << "So tien khong hop le" << endl;
            continue;
        }

        ChiTietGD* ct = qlCTGD->taoChiTiet(maGD, maVi, maDM, moTa, soTien);
        ct->setVi(vi);
        ct->setDM(danhmuc);

        gd_cha->themChiTiet(ct);

        qlVi->capNhatSoDu(maVi, soTien, danhmuc->getLoaiDM());

        string xn;
        cout << "Them chi tiet khac? (y/n): ";
        cin >> xn;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (xn == "n" || xn == "N") break;
    }
    
    gd_cha->capNhatTongTien();
    dm.getDsGiaoDich()[vitri].setTongThu(gd_cha->getTongThu());
    dm.getDsGiaoDich()[vitri].setTongChi(gd_cha->getTongChi());
    dm.saveDataNguoiDung(nguoiDungHienTai);
    cout << "Luu lai toan bo du lieu..." << endl;
}

void XuLyThaoTac::XuLyChinhSuaGD()
{
    cout << "\n--- CHINH SUA NGAY GIAO DICH ---\n";
    cout << "(Nhan ESC de huy)\n\n";
    
    // Loc theo khoang thoi gian
    bool escaped = false;
    string tuNgay = getInputWithEsc("Nhap ngay bat dau (YYYYMMDD): ", escaped);
    if (escaped) {
        cout << "\n(!) Da huy thao tac!\n";
        return;
    }
    
    if (!kiemTraNgayHopLe(tuNgay)) {
        cout << "Ngay khong hop le!\n";
        return;
    }
    
    string denNgay = getInputWithEsc("Nhap ngay ket thuc (YYYYMMDD): ", escaped);
    if (escaped) {
        cout << "\n(!) Da huy thao tac!\n";
        return;
    }
    
    if (!kiemTraNgayHopLe(denNgay)) {
        cout << "Ngay khong hop le!\n";
        return;
    }
    
    MyVector<string> dsLoc = locGDTheoKhoangTG(tuNgay, denNgay);
    hienThiDSGDDaLoc(dsLoc);
    
    if (dsLoc.get_size() == 0) return;
    
    string maGD = getInputWithEsc("\nNhap ma giao dich can sua (YYYYMMDD): ", escaped);
    if (escaped) {
        cout << "\n(!) Da huy thao tac!\n";
        return;
    }

    // Kiem tra ma cu co ton tai khong
    if (qlGD->tim_GD(maGD) == nullptr) {
        cout << "(!) Loi: Khong tim thay giao dich ngay " << maGD << "!\n";
        return;
    }
    
    string newID = getInputWithEsc("Nhap ma giao dich moi (yyyymmdd): ", escaped);
    if (escaped) {
        cout << "\n(!) Da huy thao tac!\n";
        return;
    }
    
    if (!kiemTraNgayHopLe(newID)) {
        cout << "Ngay khong hop le!\n";
        return;
    }

    // Goi ham xu ly logic (Gop hoac Doi ten)
    if (qlGD->doiNgayGiaoDich(maGD, newID)) {
        qlCTGD->suaMaGiaoDich_CTGD(maGD, newID);
        dm.saveDataNguoiDung(nguoiDungHienTai);
        cout << "\n(v) Cap nhat thanh cong!\n";
    }
    else {
        cout << "\n(!) Cap nhat that bai!\n";
    }
}

void XuLyThaoTac::XuLyChinhSuaCTGD()
{
    cout << "\n--- CHINH SUA CHI TIET GIAO DICH ---\n";
    cout << "(Nhan ESC de huy)\n\n";
    
    // Loc theo khoang thoi gian
    bool escaped = false;
    string tuNgay = getInputWithEsc("Nhap ngay bat dau (YYYYMMDD): ", escaped);
    if (escaped) {
        cout << "\n(!) Da huy thao tac!\n";
        return;
    }
    
    if (!kiemTraNgayHopLe(tuNgay)) {
        cout << "Ngay khong hop le!\n";
        return;
    }
    
    string denNgay = getInputWithEsc("Nhap ngay ket thuc (YYYYMMDD): ", escaped);
    if (escaped) {
        cout << "\n(!) Da huy thao tac!\n";
        return;
    }
    
    if (!kiemTraNgayHopLe(denNgay)) {
        cout << "Ngay khong hop le!\n";
        return;
    }
    
    MyVector<ChiTietGD*> dsLoc = locCTGDTheoKhoangTG(tuNgay, denNgay);
    hienThiDSCTGDDaLoc(dsLoc);
    
    if (dsLoc.get_size() == 0) return;

    int idCanSua;
    cout << "\nNhap Ma CTGD can sua (hoac -1 de huy): ";
    if (!(cin >> idCanSua)) {
        cout << "Loi: Vui long nhap dung dinh dang so!\n";
        cin.clear(); cin.ignore(10000, '\n');
        return;
    }
    cin.ignore();
    
    if (idCanSua == -1) {
        cout << "\n(!) Da huy thao tac!\n";
        return;
    }

    ChiTietGD* ct = qlCTGD->timCTGD(idCanSua);

    if (ct == nullptr) {
        cout << "Khong tim thay CTGD co ma: " << idCanSua << "\n";
        return;
    }
    
    string oldMaGD = ct->getMaGD();
    long long oldSoTien = ct->getSoTienGD();
    int maVi = ct->getMaVi();
    DanhMuc* dmuc = ct->getDanhMuc();
    string loaiDM = (dmuc) ? dmuc->getLoaiDM() : "";
    
    cout << "\n(Huong dan: Nhan Enter neu muon GIU NGUYEN gia tri trong ngoac)\n";
    cout << "--------------------------------------------------\n";

    string newMaGD = inputString("-> Ngay (yyyymmdd)", ct->getMaGD());

    long long newSoTien = inputLong("-> So tien (VND)", ct->getSoTienGD());

    string newMoTa = inputString("-> Mo ta", ct->getMoTa());

    cout << "--------------------------------------------------\n";

    // Goi ham xu ly
    if (qlCTGD->suaCTGD(idCanSua, newMaGD, newMoTa, newSoTien))
    {
        if (oldSoTien != newSoTien && !loaiDM.empty())
        {
            string loai = (loaiDM == "Thu") ? "Chi" : "Thu";
            //Cap nhat so tien cu ra
            qlVi->capNhatSoDu(maVi, oldSoTien, loai);

            //Cap nhat so tien moi vao
            qlVi->capNhatSoDu(maVi, newSoTien, loaiDM);
        }

        MyVector<string> daysToRefresh;
        daysToRefresh.push_back(oldMaGD);
        if (oldMaGD != newMaGD) {
            daysToRefresh.push_back(newMaGD);
            if (qlGD->tim_GD(newMaGD) == nullptr) {
                qlGD->taoGD(newMaGD);
                cout << "(Tu dong tao giao dich moi cho ngay " << newMaGD << ")\n";
            }
        }

        for (int k = 0; k < daysToRefresh.get_size(); k++)
        {
            string targetDate = daysToRefresh[k];
            GiaoDich* gdTarget = qlGD->tim_GD(targetDate);

            if (gdTarget)
            {
                gdTarget->getDsChiTiet().clear();

                for (int i = 0; i < dm.getDsChiTietGD().get_size(); i++)
                {
                    if (dm.getDsChiTietGD()[i]->getMaGD() == targetDate)
                    {
                        gdTarget->themChiTiet(dm.getDsChiTietGD()[i]);
                    }
                }

                gdTarget->capNhatTongTien();
            }
        }

        if (oldMaGD != newMaGD) {
            GiaoDich* oldGD = qlGD->tim_GD(oldMaGD);
            if (oldGD && oldGD->getTongThu() == 0 && oldGD->getTongChi() == 0) {
                qlGD->xoaGiaoDich(oldMaGD);
            }
        }
        dm.saveDataNguoiDung(nguoiDungHienTai);
        cout << "\n(v) CAP NHAT THANH CONG!\n";
    }
    else
    {
        cout << "\n(!) CAP NHAT THAT BAI!\n";
    }
}

void XuLyThaoTac::XuLyXoaGD()
{
    cout << "\n--- XOA GIAO DICH THEO NGAY ---\n";
    cout << "(Nhan ESC de huy)\n\n";
    
    // Loc theo khoang thoi gian
    bool escaped = false;
    string tuNgay = getInputWithEsc("Nhap ngay bat dau (YYYYMMDD): ", escaped);
    if (escaped) {
        cout << "\n(!) Da huy thao tac!\n";
        return;
    }
    
    if (!kiemTraNgayHopLe(tuNgay)) {
        cout << "Ngay khong hop le!\n";
        return;
    }
    
    string denNgay = getInputWithEsc("Nhap ngay ket thuc (YYYYMMDD): ", escaped);
    if (escaped) {
        cout << "\n(!) Da huy thao tac!\n";
        return;
    }
    
    if (!kiemTraNgayHopLe(denNgay)) {
        cout << "Ngay khong hop le!\n";
        return;
    }
    
    MyVector<string> dsLoc = locGDTheoKhoangTG(tuNgay, denNgay);
    hienThiDSGDDaLoc(dsLoc);
    
    if (dsLoc.get_size() == 0) return;
    
    string magd = getInputWithEsc("\nNhap ngay giao dich can xoa (yyyymmdd): ", escaped);
    if (escaped) {
        cout << "\n(!) Da huy thao tac!\n";
        return;
    }
    
    if (qlGD->tim_GD(magd) == nullptr)
    {
        cout << "Khong tim thay ma giao dich tren!" << endl;
        return;
    }
    
    char xacNhan;
    cout << "Ban co chac chan muon xoa? (y/n): ";
    cin >> xacNhan;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (xacNhan != 'y' && xacNhan != 'Y') {
        cout << "\n(!) Da huy xoa!\n";
        return;
    }
    
    qlGD->xoaGiaoDich(magd);
    for (int i = dm.getDsChiTietGD().get_size() - 1; i >= 0; i--)
    {
        if (dm.getDsChiTietGD()[i]->getMaGD() == magd)
        {
            int index = dm.getDsChiTietGD()[i]->getMaCTGD();
            string loai_tam = dm.getDsChiTietGD()[i]->getDanhMuc()->getLoaiDM();
            string loai = (loai_tam == "Thu") ? "Chi" : "Thu";

            qlVi->capNhatSoDu(dm.getDsChiTietGD()[i]->getMaVi(), dm.getDsChiTietGD()[i]->getSoTienGD(), loai);
            qlCTGD->xoaCTGD(index);
        }
    }
    cout << "Da xoa giao dich" << endl;
    dm.saveDataNguoiDung(nguoiDungHienTai);
}

void XuLyThaoTac::XuLyXoaCTGD()
{
    cout << "\n--- XOA CHI TIET GIAO DICH ---\n";
    cout << "(Nhan ESC de huy)\n\n";
    
    // Loc theo khoang thoi gian
    bool escaped = false;
    string tuNgay = getInputWithEsc("Nhap ngay bat dau (YYYYMMDD): ", escaped);
    if (escaped) {
        cout << "\n(!) Da huy thao tac!\n";
        return;
    }
    
    if (!kiemTraNgayHopLe(tuNgay)) {
        cout << "Ngay khong hop le!\n";
        return;
    }
    
    string denNgay = getInputWithEsc("Nhap ngay ket thuc (YYYYMMDD): ", escaped);
    if (escaped) {
        cout << "\n(!) Da huy thao tac!\n";
        return;
    }
    
    if (!kiemTraNgayHopLe(denNgay)) {
        cout << "Ngay khong hop le!\n";
        return;
    }
    
    MyVector<ChiTietGD*> dsLoc = locCTGDTheoKhoangTG(tuNgay, denNgay);
    hienThiDSCTGDDaLoc(dsLoc);
    
    if (dsLoc.get_size() == 0) return;
    
    int mact;
    cout << "\nNhap ma chi tiet giao dich can xoa (hoac -1 de huy): ";
    cin >> mact;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (mact == -1) {
        cout << "\n(!) Da huy thao tac!\n";
        return;
    }
    
    ChiTietGD* ct = qlCTGD->timCTGD(mact);
    if (ct == nullptr)
    {
        cout << "Khong tim thay ma chi tiet giao dich tren" << endl;
        return;
    }
    
    GiaoDich* gdCha = qlGD->tim_GD(ct->getMaGD());
    if(gdCha == nullptr) {
        cout << "\n(x) Loi: Khong tim thay giao dich cha (" << ct->getMaGD() << ") cho chi tiet nay.\n";
        return;
    }
    
    char xacNhan;
    cout << "Ban co chac chan muon xoa? (y/n): ";
    cin >> xacNhan;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (xacNhan != 'y' && xacNhan != 'Y') {
        cout << "\n(!) Da huy xoa!\n";
        return;
    }
    
    string loaiHienTai = ct->getDanhMuc()->getLoaiDM();
    string loaiDaoNguoc = (loaiHienTai == "Thu") ? "Chi" : "Thu";
    qlVi->capNhatSoDu(ct->getMaVi(), ct->getSoTienGD(), loaiDaoNguoc);
    gdCha->xoaCTGD(ct);       
    qlCTGD->xoaCTGD(mact);
    gdCha->capNhatTongTien();
    dm.saveDataNguoiDung(nguoiDungHienTai);
    cout << "Xoa chi tiet giao dich thanh cong!" << endl;
}

void XuLyThaoTac::XuLySuaMK()
{
    string id = nguoiDungHienTai->getID();
    cout << "Nhap mat khau hien tai: ";
    string pass = qlND->AnMK();
    int index = qlND->KiemTraMK(id, pass);
    if (index != -1)
    {
        string mk;
        cout << "Nhap mat khau moi: ";
        mk = qlND->AnMK();
        qlND->DoiMK(index, mk);
        cout << "Doi mat khau thanh cong!" << endl;
        dm.saveNguoiDung(dm.getBasePath() + "users.txt", dm.getDsNguoiDung());
    }
    else
    {
        cout << "Sai mat khau!!" << endl;
    }
}

bool XuLyThaoTac::XuLyXoaTK()
{
    string id = nguoiDungHienTai->getID();
    cout << "Nhap mat khau de xac nhan: ";
    string pass = qlND->AnMK();
    int index = qlND->KiemTraMK(id, pass);
    if (index != -1)
    {
        char temp;
        cout << "Xac nhan xoa tai khoan!! (y/n): ";
        cin >> temp;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (temp == 'y' || temp == 'Y')
        {
            qlND->XoaTaiKhoan(index);
            cout << "Xoa nguoi dung thanh cong!" << endl;
            try {
                if (fs::exists(dm.getBasePath() + "user_" + id + "/"))
                {
                    fs::remove_all(dm.getBasePath() + "user_" + id + "/");
                    cout << "Da xoa thu muc " << endl;
                }
            }
            catch (const std::exception& e) {
                cout << "Loi khi xoa thu muc: " << e.what() << endl;
            }
            nguoiDungHienTai = nullptr;
            dm.saveNguoiDung(dm.getBasePath() + "users.txt", dm.getDsNguoiDung());
            return true;
        }
        else
        {
            cout << "Huy xoa tai khoan.\n";
            return false;
        }
    }
    else
    {
        cout << "Sai mat khau, yeu cau bi huy bo!!" << endl;
        return false;
    }
}

void XuLyThaoTac::XuLyXemThongTinTaiKhoan()
{
    if (nguoiDungHienTai == nullptr) return;
    
    string line_sep = "+-" + string(40, '-') + "-+";
    cout << "\n" << line_sep << endl;
    cout << "| " << left << setw(40) << "   THONG TIN TAI KHOAN   " << " |" << endl;
    cout << line_sep << endl;
    cout << "| " << left << setw(20) << "ID:" << left << setw(20) << nguoiDungHienTai->getID() << " |" << endl;
    cout << "| " << left << setw(20) << "Ten hien thi:" << left << setw(20) << nguoiDungHienTai->getTen() << " |" << endl;
    cout << line_sep << endl;
}

// ==================== HELPERS ====================

template <typename T>
T XuLyThaoTac::getInput(const string& prompt) {
    T value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        else {
            cout << "Nhap sai! Vui long nhap dung dinh dang.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

template<>
string XuLyThaoTac::getInput<string>(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}


string XuLyThaoTac::getInputWithEsc(const string& prompt, bool& escaped) {
    escaped = false;
    string result = "";
    cout << prompt;
    
    while (true) {
        char c = _getch();
        
        if (c == 27) { 
            escaped = true;
            cout << "\n"; 
            return ""; 
        }

        if (c == '\r' || c == '\n') { 
            cout << "\n";
            return result;
        }
        if ((c == '\b' || c == 127) && !result.empty()) { 
            result.pop_back();
            cout << "\b \b"; 
            continue;
        }

        if (isprint(c)) { 
            result += c;
            cout << c; 
        }
    }
}

long long XuLyThaoTac::inputLong(string prompt, long long oldVal) {
    string temp;
    cout << prompt << " (" << oldVal << "): ";
    getline(cin, temp);
    if (temp.empty()) return oldVal;
    try {
        return stoll(temp);
    }
    catch (...) {
        return oldVal;
    }
}

string XuLyThaoTac::inputString(string prompt, string oldVal) {
    string newVal;
    cout << prompt << " (" << oldVal << "): ";
    getline(cin, newVal);
    if (newVal.empty()) return oldVal;
    return newVal;
}

void XuLyThaoTac::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
