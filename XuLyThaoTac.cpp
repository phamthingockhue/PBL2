#include "XuLyThaoTac.h"
#include <iostream>
#include <limits>
#include <cstdlib> 
#include <ctime>
#include <filesystem>
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
    cout << "------------------------------\n";
    cout << "       QUAN LY CHI TIEU       \n";
    cout << "------------------------------\n";
    cout << "1. Dang nhap\n";
    cout << "2. Dang ky\n";
    cout << "0. Thoat\n";
    cout << "------------------------------\n";
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
        cout << "\n------------------------------\n";
        cout << " 1. Xem danh sach vi\n";
        cout << " 2. Xem danh muc\n";
        cout << " 3. Them giao dich\n";
        cout << " 4. Xem danh sach chi tiet giao dich\n";
        cout << " 5. Xem danh sach giao dich theo ngay\n";
        cout << " 6. Thay doi mat khau\n";
        cout << " 7. Xoa tai khoan\n";
        cout << " 0. Dang xuat\n";
        cout << "------------------------------\n";
        cout << "Chon: ";
        subChoice = getIntInput("");

        switch (subChoice) {
        case 1: 
        {
            cout << "\n--- DANH SACH VI ---\n";
            cout << "Ma Vi | Ten Vi | So Du Vi" << endl;
            for (int i = 0; i < dm.dsVi.get_size(); i++) {
                cout << dm.dsVi[i].getMaVi() << " | "
                    << dm.dsVi[i].getTenVi() << " | "
                    << dm.dsVi[i].getSoDu() << " VND\n";
            }
            break;
        }
        case 2: {
            cout << "\n--- DANH MUC ---\n";
            cout << "Ma Danh Muc | Ten Danh Muc | Loai Danh Muc" << endl;
            for (int i = 0; i < dm.dsDanhMuc.get_size(); i++) {
                cout << dm.dsDanhMuc[i]->getMaDM() << "     | "
                    << dm.dsDanhMuc[i]->getTenDM() << " | "
                    << dm.dsDanhMuc[i]->getLoaiDM() << endl;
            }
            break;
        }
        case 3: {
            cout << "\n--- THEM GIAO DICH ---\n";
            XuLyThemGD();
            break;
        }
        case 4: 
        {
            cout << "\n--- CHI TIET GIAO DICH ---\n";

            for (int i = dm.dsGiaoDich.get_size() - 1; i >= 0; i--)
            {
                GiaoDich giaoDich = dm.dsGiaoDich[i];
                cout << "Ma giao dich: " << giaoDich.getMaGD() << endl;
                cout << "Ma Chi Tiet GD | Ten Vi | Ten Danh Muc | Mo ta | So Tien GD" << endl;
                for (int j = dm.dsChiTietGD.get_size() - 1; j >= 0; j--)
                {
                    Vi* vi = dm.dsChiTietGD[j]->getVi();
                    DanhMuc* danhmuc = dm.dsChiTietGD[j]->getDanhMuc();

                    string tenVi = (vi != nullptr) ? vi->getTenVi() : "Loi vi";
                    string tenDanhMuc = (danhmuc != nullptr) ? danhmuc->getTenDM() : "Loi danh muc";

                    cout << dm.dsChiTietGD[j]->getMaGD() << " | "
                        << dm.dsChiTietGD[j]->getMaCTGD() << " | "
                        << tenVi << " | "
                        << tenDanhMuc << " | "
                        << dm.dsChiTietGD[j]->getMoTa() << " | "
                        << dm.dsChiTietGD[j]->getSoTienGD() << endl;
                }
                cout << endl;
            } 
            break;
        }
        case 5:
        {
            cout << "\n--- GIAO DICH THEO NGAY ---\n";
            cout << "Ma GD | Tong Thu | Tong Chi" << endl;
            for (int i = dm.dsGiaoDich.get_size() - 1; i >= 0; i--)
            {
                cout << dm.dsGiaoDich[i].getMaGD() << " | "
                    << dm.dsGiaoDich[i].getTongThu() << " | "
                    << dm.dsGiaoDich[i].getTongChi() << endl;
            }
            break;
        }
        case 6: 
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
                break;
            }
            break;
        }
        case 7:
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
                    return;
                }
                else
                {
                    cout << "Huy xoa tai khoan.\n";
                }
            }
            else
            {
                cout << "Sai mat khau, yeu cau bi huy bo!!" << endl;
            }
            break;
        }
        case 0: {
            cout << "Dang xuat va luu du lieu...\n";
            dm.saveDataNguoiDung(nguoiDungHienTai);
            nguoiDungHienTai = nullptr;
            clearScreen();
            return;
            break;
        }
        default:
            cout << "Lua chon khong hop le.\n";
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
        showMainMenu();
    }
    else {
        cout << "Sai ten dang nhap hoac mat khau.\n";
    }
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

    string tg = getStringInput("Nhap thoi gian giao dich (YYYY-MM-DD): ");

    GiaoDich* gd_cha = nullptr;
    for (size_t i = 0; i < dm.dsGiaoDich.get_size(); ++i) {
        if (dm.dsGiaoDich[i].getMaGD() == tg) {
            gd_cha = &dm.dsGiaoDich[i];
            break;
        }
    }
    if (gd_cha == nullptr) {
        GiaoDich gdMoi(tg);
        dm.dsGiaoDich.push_back(gdMoi);
        gd_cha = &dm.dsGiaoDich.back(); 
        cout << "Tao Giao dich moi cho ngay: " << tg << endl;
    }
    else {
        cout << "Them chi tiet vao Giao dich ngay: " << tg << endl;
    }
    while (true) {
        cout << "---THEM CHI TIET GIAO DICH---\n";
        cout << "\nDanh sach vi:\n";
        for (size_t i = 0; i < dm.dsVi.get_size(); ++i) {
            cout << dm.dsVi[i].getMaVi() << " | "
                << dm.dsVi[i].getTenVi() << " | "
                << dm.dsVi[i].getSoDu() << " VND\n";
        }
        int maVi = getIntInput("Nhap ma vi: ");
        if (maVi == 0) return;

        cout << "\nDanh sach danh muc:\n";
        for (size_t i = 0; i < dm.dsDanhMuc.get_size(); ++i) {
            cout << dm.dsDanhMuc[i]->getMaDM() << " | "
                << dm.dsDanhMuc[i]->getTenDM() << " | "
                << dm.dsDanhMuc[i]->getLoaiDM() << endl;
        }
        int maDM = getIntInput("Nhap ma danh muc: ");

        string moTa = getStringInput("Nhap mo ta: ");

        long long soTienGD = getIntInput("Nhap so tien giao dich: ");
        if (soTienGD <= 0) return;

        Vi* vi = timVi(maVi);
        DanhMuc* danhmuc = timDanhMuc(maDM);

        ChiTietGD ct(tg, maVi, maDM, moTa, soTienGD);
        ct.setVi(vi);
        ct.setDM(danhmuc);
        cout << "o1" << endl;
        dm.dsChiTietGD.push_back(&ct);
        gd_cha->capNhatTongTien();
        cout << "o2" << endl;
    
        string loaiDM = timLoaiDM(maDM);


        for (int i = 0; i < dm.dsVi.get_size(); i++)
        {
            if (dm.dsVi[i].getMaVi() == maVi)
            {
                if (loaiDM == "Thu")
                {
                    dm.dsVi[i].setSoDu(dm.dsVi[i].getSoDu() + soTienGD);
                }
                else
                {
                    dm.dsVi[i].setSoDu(dm.dsVi[i].getSoDu() - soTienGD);
                }
            }
        }
        cout << "o3" << endl;
        dm.saveDataNguoiDung(nguoiDungHienTai);
        cout << "Ban co muon them giao dich moi khong? (y/n)";
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

string XuLyThaoTac::timLoaiDM(int maDM)
{
    for (int i = 0; i < dm.dsDanhMuc.get_size(); i++)
    {
        if (dm.dsDanhMuc[i]->getMaDM() == maDM) return dm.dsDanhMuc[i]->getLoaiDM();
        break;
    }
    return "";
}

Vi* XuLyThaoTac::timVi(int mavi)
{
    for (int i = 0; i < dm.dsVi.get_size(); i++)
    {
        if (dm.dsVi[i].getMaVi() == mavi) return &dm.dsVi[i];
    }
    return nullptr;
}
DanhMuc* XuLyThaoTac::timDanhMuc(int madm)
{
    for (int i = 0; i < dm.dsDanhMuc.get_size(); i++)
    {
        if (dm.dsDanhMuc[i]->getMaDM() == madm) return dm.dsDanhMuc[i];
    }
    return nullptr;
}



