#include "XuLyThaoTac.h"
#include <iostream>
#include <limits>
#include <cstdlib> 
#include <ctime>
#include <filesystem>
#include <iomanip>
using namespace std;
namespace fs = filesystem;

XuLyThaoTac::XuLyThaoTac() : nd(dm.dsNguoiDung) {
    dm.setBasePath("C:/finance_app/data/");
    dm.loadNguoiDung(dm.getBasePath() + "users.txt", dm.dsNguoiDung);
}

void XuLyThaoTac::run() {
    while (true) {
        showLoginMenu();
    }
}

// ==================== MENUS ====================

void XuLyThaoTac::showLoginMenu() {
    string line_sep = "+-" + string(30, '-') + "-+";
    cout << line_sep << endl;
    cout << "| " << "       QUAN LY CHI TIEU       " << " |" << endl;
    cout << "| " << left << setw(30) << " 1. Dang nhap" << " |" << endl;
    cout << "| " << left << setw(30) << " 2. Dang ky" << " |" << endl;
    cout << "| " << left << setw(30) << " 0. Thoat" << " |" << endl;
    cout << line_sep << endl;
    int choice = getIntInput("Chon: ");

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
    int subChoice;
    do {
        string line_sep = "+-" + string(40, '-') + "-+";
        cout << line_sep << endl;
        string title = "MENU CHINH";

        int pad_left = (40 - title.length()) / 2;
        int pad_right = 40 - title.length() - pad_left;
        cout << "| " << string(pad_left, ' ') << title << string(pad_right, ' ') << " |" << endl;

        cout << "| " << left << setw(40) << " 1. Xem danh sach vi" << " |" << endl;
        cout << "| " << left << setw(40) << " 2. Xem danh muc" << " |" << endl;
        cout << "| " << left << setw(40) << " 3. Them giao dich" << " |" << endl;
        cout << "| " << left << setw(40) << " 4. Xem chi tiet giao dich theo thang" << " |" << endl;
        cout << "| " << left << setw(40) << " 5. Xem giao dich theo ngay" << " |" << endl;
        cout << "| " << left << setw(40) << " 6. Thay doi mat khau" << " |" << endl;
        cout << "| " << left << setw(40) << " 7. Xoa tai khoan" << " |" << endl;
        cout << "| " << left << setw(40) << " 0. Dang xuat" << " |" << endl;
        cout << line_sep << endl;
        cout << "Chon: ";
        subChoice = getIntInput("");

        switch (subChoice) {
        case 1: 
        {
            clearScreen();
            cout << "\n--- DANH SACH VI ---\n";
            string line_sep = "+-" + string(7, '-') + "-+-" + string(20, '-') + "-+-" + string(18, '-') + "-+";
            cout << line_sep << endl;

            cout << "| " << left << setw(7) << "Ma Vi" << " | "
                << left << setw(20) << "Ten Vi" << " | "
                << left << setw(18) << "So Du Vi (VND)" << " |" << endl;
            cout << line_sep << endl;

            for (int i = 0; i < dm.dsVi.get_size(); i++) {
                cout << "| " << left << setw(7) << dm.dsVi[i].getMaVi() << " | "
                    << left << setw(20) << dm.dsVi[i].getTenVi() << " | "
                    << left << setw(18) << dm.dsVi[i].getSoDu() << " |" << endl;
            }
            cout << line_sep << endl;

            cout << "\nNhan Enter de tro ve menu...";
            cin.get();

            clearScreen();
            break;
        }
        case 2: {
            clearScreen();
            cout << "\n--- DANH MUC ---\n";
            string line_sep = "+-" + string(12, '-') + "-+-" + string(20, '-') + "-+-" + string(10, '-') + "-+";
            
            cout << line_sep << endl;
            cout << "| " << left << setw(12) << "Ma Danh Muc" << " | "
                << left << setw(20) << "Ten Danh Muc" << " | "
                << left << setw(10) << "Loai" << " |" << endl;
            cout << line_sep << endl;

            for (int i = 0; i < dm.dsDanhMuc.get_size(); i++) {
                cout << "| " << left << setw(12) << dm.dsDanhMuc[i]->getMaDM() << " | "
                    << left << setw(20) << dm.dsDanhMuc[i]->getTenDM() << " | "
                    << left << setw(10) << dm.dsDanhMuc[i]->getLoaiDM() << " |" << endl;
            }
            cout << line_sep << endl;

            cout << "\nNhan Enter de tro ve menu...";
            cin.get();

            clearScreen();
            break;
        }
        case 3: {
            clearScreen();
            cout << "\n--- THEM GIAO DICH ---\n";
            XuLyThemGD();

            cout << "\nNhan Enter de tro ve menu...";
            cin.get();

            clearScreen();
            break;
        }
        case 4: 
        {
            clearScreen();
            string nam;
            cout << "Nhap so nam: ";
            getline(cin, nam);
            gd.setDSGD(dm.dsGiaoDich);
            gd.thongKeTheoThang(nam);

            cout << "\nNhan Enter de tro ve menu...";
            cin.get();

            clearScreen();
            break;
        }
        case 5:
        {
            clearScreen();
            cout << "\n--- GIAO DICH THEO NGAY ---\n";
            string line_sep = "+-" + string(10, '-') + "-+-" + string(15, '-') + "-+-" + string(15, '-') + "-+";
            
            cout << line_sep << endl;
            cout << "| " << left << setw(10) << "Ma GD" << " | "
                << left << setw(15) << "Tong Thu" << " | "
                << left << setw(15) << "Tong Chi" << " |" << endl;
            cout << line_sep << endl;

            for (int i = dm.dsGiaoDich.get_size() - 1; i >= 0; i--)
            {
                cout << "| " << left << setw(10) << dm.dsGiaoDich[i].getMaGD() << " | "
                    << left << setw(15) << dm.dsGiaoDich[i].getTongThu() << " | "
                    << left << setw(15) << dm.dsGiaoDich[i].getTongChi() << " |" << endl;
            }
            cout << line_sep << endl;

            cout << "\nNhan Enter de tro ve menu...";
            cin.get();

            clearScreen();
            break;
        }
        case 6: 
        {
            clearScreen();
            XuLySuaMK();

            cout << "\nNhan Enter de tro ve menu...";
            cin.get();

            clearScreen();
            break;
        }
        case 7:
        {
            clearScreen();
            bool daXoa = XuLyXoaTK();

            if (daXoa)
            {
                cout << "\nNhan Enter de tro ve man hinh dang nhap...";
                cin.get();
                clearScreen();
                return;
            }
            else
            {
                cout << "\nNhan Enter de tro ve menu...";
                cin.get();
                clearScreen();
                break;
            }
        }
        case 0: {
            clearScreen();
            cout << "Dang xuat va luu du lieu...\n";
            dm.saveDataNguoiDung(nguoiDungHienTai);
            nguoiDungHienTai = nullptr;
            clearScreen();
            return;
            break;
        }
        default:
            clearScreen();
            cout << "Lua chon khong hop le.\n";
            clearScreen();
        }
    } while (subChoice != 0);
}

// ==================== HANDLERS ====================

void XuLyThaoTac::XuLyDangNhap() {
    clearScreen();
    nd.setDsNguoiDung(dm.dsNguoiDung);
    cout << "--- DANG NHAP ---\n";
    string tenDangNhap = getStringInput("Ten dang nhap: ");
    cout << "Nhap mat khau: ";
    string matKhau = nd.AnMK();

    nguoiDungHienTai = nd.xacThuc(tenDangNhap, matKhau);

    if (nguoiDungHienTai) {
        cout << "Dang nhap thanh cong! Xin chao, " << nguoiDungHienTai->getTen() << "!\n";
        dm.loadDataNguoiDung(nguoiDungHienTai);

        cout << "\nNhan Enter de tro ve menu...";
        cin.get();

        clearScreen();
        showMainMenu();
    }
    else {
        cout << "Sai ten dang nhap hoac mat khau.\n";
    }
    cout << "\nNhan Enter de tro ve menu...";
    cin.get();

    clearScreen();
}

void XuLyThaoTac::XuLyDangKy() {
    clearScreen();
    nd.setDsNguoiDung(dm.dsNguoiDung);
    cout << "--- DANG KY ---\n";
    string tenDangNhap = getStringInput("Ten dang nhap: ");
    for (int i = 0; i < dm.dsNguoiDung.get_size(); i++)
    {
        if (dm.dsNguoiDung[i].getID() == tenDangNhap)
        {
            cout << "Ten dang nhap da ton tai.\n";
            return;
        }
    }
    string tenHienThi = getStringInput("Ten hien thi: ");
    cout << "Mat khau: ";
    string matKhau = nd.AnMK();

    if (nd.DangKy(tenDangNhap, tenHienThi, matKhau)) {
        cout << "Dang ky thanh cong! Ban co the dang nhap ngay.\n";
        string userFolder = dm.getBasePath() + "user_" + tenDangNhap + "/";
        if (!fs::exists(userFolder)) {
            fs::create_directory(userFolder);
            cout << "Da tao thu muc cho nguoi dung moi." << endl;
        }
        dm.default_user_folder(userFolder);
        dm.dsNguoiDung = nd.getDsNguoiDung();
        dm.saveNguoiDung(dm.getBasePath() + "users.txt", dm.dsNguoiDung);
    }
    cout << "\nNhan Enter de tro ve menu...";
    cin.get();

    clearScreen();
}

void XuLyThaoTac::XuLyThemGD() {
    clearScreen();
    cout << "--- THEM GIAO DICH ---\n";

    time_t now = time(0);
    tm gio;
    localtime_s(&gio, &now);
    cout << "Hom nay la ngay: "
        << (1900 + gio.tm_year) << "-"
        << setfill('0') << setw(2) << (1 + gio.tm_mon) << "-"
        << setfill('0') << setw(2) << gio.tm_mday << endl;
    cout << setfill(' ');
    
    cout << endl << "Nhac nho nho: 'Vui long nhap thoi gian giao dich theo dinh dang khong co dau -  '" << endl << endl;
    string magd = getStringInput("Nhap thoi gian giao dich (YYYY-MM-DD): ");
    while (magd == "")
    {
        cout << "khong de ma giao dich trong!! " << endl;
        magd = getStringInput("Nhap thoi gian giao dich (YYYY-MM-DD): ");
    }
    int vitri;

    vi.setVi(dm.dsVi);
    dmuc.setDM(dm.dsDanhMuc);

    GiaoDich* gd_cha = nullptr;
    for (size_t i = 0; i < dm.dsGiaoDich.get_size(); ++i) {
        if (dm.dsGiaoDich[i].getMaGD() == magd) {
            gd_cha = &dm.dsGiaoDich[i];
            vitri = i;
            break;
        }
    }

    if (gd_cha == nullptr) {
        GiaoDich gdMoi(magd);
        dm.dsGiaoDich.push_back(gdMoi);
        gd_cha = &dm.dsGiaoDich.back(); 
        cout << "Tao Giao dich moi cho ngay: " << magd << endl;
        vitri = dm.dsGiaoDich.get_size() - 1;
    }
    else 
    {
        cout << "Them chi tiet vao Giao dich ngay: " << magd << endl;
        if (gd_cha->getDsChiTiet().get_size() == 0)
        {
            for (int i = 0; i < dm.dsChiTietGD.get_size(); i++)
            {
                if (dm.dsChiTietGD[i]->getMaGD() == magd)
                {
                    ChiTietGD* ct = dm.dsChiTietGD[i];
                    ct->setVi(vi.TimVi(dm.dsChiTietGD[i]->getMaVi()));
                    ct->setDM(dmuc.TimDM(dm.dsChiTietGD[i]->getMaDM()));
                    gd_cha->themChiTiet(ct);
                }
            }
            gd_cha->capNhatTongTien();
        }
    }
    while (true) 
    {
        cout << "---THEM CHI TIET GIAO DICH---\n";
        cout << "\n--- DANH SACH VI ---\n";
        string vi_line_sep = "+-" + string(7, '-') + "-+-" + string(20, '-') + "-+-" + string(18, '-') + "-+";
        cout << vi_line_sep << endl;
        cout << "| " << left << setw(7) << "Ma Vi" << " | "
            << left << setw(20) << "Ten Vi" << " | "
            << left << setw(18) << "So Du Vi (VND)" << " |" << endl;
        cout << vi_line_sep << endl;

        for (size_t i = 0; i < dm.dsVi.get_size(); ++i) {
            cout << "| " << left << setw(7) << dm.dsVi[i].getMaVi() << " | "
                << left << setw(20) << dm.dsVi[i].getTenVi() << " | "
                << left << setw(18) << dm.dsVi[i].getSoDu() << " |" << endl;
        }
        cout << vi_line_sep << endl;

        int maVi = getIntInput("Nhap ma vi: ");

        Vi* Vi = vi.TimVi(maVi);
        if (Vi == nullptr) { cout << "ma vi khong hop le!" << endl; return; }

        cout << "\n--- DANH SACH DANH MUC ---\n";
        string dm_line_sep = "+-" + string(12, '-') + "-+-" + string(20, '-') + "-+-" + string(10, '-') + "-+";
        
        cout << dm_line_sep << endl;
        cout << "| " << left << setw(12) << "Ma Danh Muc" << " | "
            << left << setw(20) << "Ten Danh Muc" << " | "
            << left << setw(10) << "Loai" << " |" << endl;
        cout << dm_line_sep << endl;

        for (size_t i = 0; i < dm.dsDanhMuc.get_size(); ++i) {
            cout << "| " << left << setw(12) << dm.dsDanhMuc[i]->getMaDM() << " | "
                << left << setw(20) << dm.dsDanhMuc[i]->getTenDM() << " | "
                << left << setw(10) << dm.dsDanhMuc[i]->getLoaiDM() << " |" << endl;
        }
        cout << dm_line_sep << endl;

        int maDM = getIntInput("Nhap ma danh muc: ");
        DanhMuc* danhmuc = dmuc.TimDM(maDM);
        if (danhmuc == nullptr) { cout << "ma danh muc khong hop le!" << endl; return; }

        string moTa = getStringInput("Nhap mo ta: ");

        long long soTienGD = getIntInput("Nhap so tien giao dich: ");
        if (soTienGD <= 0) 
        {
            cout << "So tien khong hop le" << endl;
            return;
        }

        ChiTietGD* ct = new ChiTietGD(magd, maVi, maDM, moTa, soTienGD);
        ct->setVi(Vi);
        ct->setDM(danhmuc);

        gd_cha->themChiTiet(ct);
        dm.dsChiTietGD.push_back(ct);

        string loaiDM = dmuc.TimLoaiDM(maDM);

        for (int i = 0; i < dm.dsVi.get_size(); i++)
        {
            if (dm.dsVi[i].getMaVi() == maVi)
            {
                if (loaiDM == "Thu")

                {
                    dm.dsVi[i].setSoDu(dm.dsVi[i].getSoDu() + soTienGD);
                }
                else if (loaiDM == "Chi")
                {
                    dm.dsVi[i].setSoDu(dm.dsVi[i].getSoDu() - soTienGD);
                }
                else
                {
                    cout << "loai danh muc khong hop le" << endl;
                }
            }
        }
        cout << "Ban co muon them giao dich moi khong? (y/n): ";
        string xn;
        cin >> xn;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (xn == "n" || xn == "N")
        {
            break;
        }
        else if (xn == "y" || xn == "Y")
        {
            continue;
        }
        else
        {
            cout << "Lua chon khong hop le! Thoat khoi yeu cau them giao dich\n";
            break;
        }
    }
    gd_cha->capNhatTongTien();
    dm.dsGiaoDich[vitri].setTongThu(gd_cha->getTongThu());
    dm.dsGiaoDich[vitri].setTongChi(gd_cha->getTongChi());
    dm.saveDataNguoiDung(nguoiDungHienTai);
    cout << "Luu lai toan bo du lieu..." << endl;
}

void XuLyThaoTac::XuLySuaMK()
{
    string id = nguoiDungHienTai->getID();
    cout << "Nhap mat khau: ";
    string pass = nd.AnMK();
    int index = nd.KiemTraMK(id, pass);
    if (index != -1)
    {
        string mk;
        cout << "Nhap mat khau moi: ";
        mk = nd.AnMK();
        nd.DoiMK(index, mk);
        cout << "Doi mat khau thanh cong!" << endl;
        dm.dsNguoiDung = nd.getDsNguoiDung();
        dm.saveNguoiDung(dm.getBasePath() + "users.txt", dm.dsNguoiDung);
    }
    else
    {
        cout << "Sai mat khau!!" << endl;
        return;
    }
}

bool XuLyThaoTac::XuLyXoaTK()
{
    string id = nguoiDungHienTai->getID();
    cout << "Nhap mat khau: ";
    string pass = nd.AnMK();
    int index = nd.KiemTraMK(id, pass);
    if (index != -1)
    {
        char temp;
        cout << "Xac nhan xoa tai khoan!! (y/n): ";
        cin >> temp;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (temp == 'y')
        {
            nd.XoaTaiKhoan(index);
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
            dm.dsNguoiDung = nd.getDsNguoiDung();
            dm.saveNguoiDung(dm.getBasePath() + "users.txt", dm.dsNguoiDung);
            nguoiDungHienTai = nullptr;
            clearScreen();
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

// ==================== HELPERS ====================

int XuLyThaoTac::getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        else {
            cout << "Nhap sai! Vui long nhap so.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string XuLyThaoTac::getStringInput(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

void XuLyThaoTac::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
