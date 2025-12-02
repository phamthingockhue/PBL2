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
    dm.setBasePath("C:/finance_app/data/");
    try {
        if (!fs::exists(dm.getBasePath())) {
            fs::create_directories(dm.getBasePath());
        }
    }
    catch (const std::exception& e) {
        cerr << "Loi filesystem: " << e.what() << "\n";
    }

    dm.loadNguoiDung(dm.getBasePath() + "users.txt", dm.dsNguoiDung);
    qlND = new QuanLyND(&dm.dsNguoiDung);
    qlDM = new QuanLyDM(&dm.dsDanhMuc);
    qlVi = new QuanLyVi(&dm.dsVi);
    qlGD = new QuanLyGD(&dm.dsGiaoDich, &dm.dsChiTietGD);
    qlCTGD = new QuanLyCTGD(&dm.dsChiTietGD);
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
        cout << "| " << left << setw(40) << " 5. Xem giao dich" << " |" << endl;
        cout << "| " << left << setw(40) << " 6. Xem chi tiet giao dich theo ngay" << " | " << endl;
        cout << "| " << left << setw(40) << " 7. Chinh sua ngay giao dich" << " | " << endl;
        cout << "| " << left << setw(40) << " 8. Chinh sua chi tiet giao dich" << " | " << endl;
        cout << "| " << left << setw(40) << " 9. Thay doi mat khau" << " |" << endl;
        cout << "| " << left << setw(40) << " 10. Xoa tai khoan" << " |" << endl;
        cout << "| " << left << setw(40) << " 0. Dang xuat" << " |" << endl;
        cout << line_sep << endl;
        cout << "Chon: ";
        subChoice = getInput<int>("");

        switch (subChoice) {
        case 1:
        {
            clearScreen();
            cout << "\n--- DANH SACH VI ---\n";
            qlVi->inDanhSachVi();
            cout << "\nNhan Enter de tro ve menu...";
            cin.get();
            clearScreen();
            break;
        }
        case 2: {
            clearScreen();
            cout << "\n--- DANH MUC ---\n";
            qlDM->inDanhSachDM();
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
            qlGD->thongKeTheoThang(nam);

            cout << "\nNhan Enter de tro ve menu...";
            cin.get();

            clearScreen();
            break;
        }
        case 5:
        {
            clearScreen();
            qlGD->inDanhSachGD();
            cout << "\nNhan Enter de tro ve menu...";
            cin.get();

            clearScreen();
            break;
        }
        case 6:
        {
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
        case 7:
        {
            clearScreen();
            cout << "\n---CHINH SUA NGAY GIAO DICH---\n";
            string maGD;
            cout << "\nNhap ma giao dich can sua (YYYYMMDD): ";
            cin >> maGD;

            // Kiểm tra mã cũ có tồn tại không
            if (qlGD->timGD(maGD) == false) {
                cout << "(!) Loi: Khong tim thay giao dich ngay " << maGD << "!\n";
            }
            else {
                string newID;
                cout << "Nhap ma giao dich moi (yyyymmdd): ";
                cin >> newID;

                // Gọi hàm xử lý logic (Gộp hoặc Đổi tên)
                if (qlGD->doiNgayGiaoDich(maGD, newID)) {
                    qlCTGD->suaMaGiaoDich_CTGD(maGD, newID);
                    dm.saveDataNguoiDung(nguoiDungHienTai);
                    cout << "\n(v) Cap nhat thanh cong!\n";
                }
                else {
                    cout << "\n(!) Cap nhat that bai!\n";
                }
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nNhan Enter de tro ve menu...";
            cin.get();
            clearScreen();
            break;
        }
        case 8:
        {
            clearScreen();
            cout << "\n--- CHINH SUA CHI TIET GIAO DICH ---\n";

            int idCanSua;
            cout << "Nhap Ma CTGD can sua: ";
            if (!(cin >> idCanSua)) {
                cout << "Loi: Vui long nhap dung dinh dang so!\n";
                cin.clear(); cin.ignore(10000, '\n');
                cout << "\nNhan Enter de quay lai..."; cin.get(); break;
            }
            cin.ignore();

            ChiTietGD* ct = qlCTGD->timCTGD(idCanSua);

            if (ct == nullptr) cout << "Khong tim thay CTGD co ma: " << idCanSua << "\n";
            else {
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

                // Gọi hàm xử lý
                if (qlCTGD->suaCTGD(idCanSua, newMaGD, newMoTa, newSoTien))
                {
                    if (oldSoTien != newSoTien && !loaiDM.empty())
                    {
                        string loai = (loaiDM == "Thu") ? "Chi" : "Thu";
                        //Cập nhật số tiền cũ ra
                        qlVi->capNhatSoDu(maVi, oldSoTien, loai);

                        //Cập nhật số tiền mới vào
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

                            for (int i = 0; i < dm.dsChiTietGD.get_size(); i++)
                            {
                                if (dm.dsChiTietGD[i]->getMaGD() == targetDate)
                                {
                                    gdTarget->themChiTiet(dm.dsChiTietGD[i]);
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
                    cout << "\n(v) CAP NHAT THAT BAI!\n";
                }
            }

            cout << "\nNhan Enter de tro ve menu...";
            cin.get();

            clearScreen();
            break;

        }
        case 9:
        {
            clearScreen();
            XuLySuaMK();

            cout << "\nNhan Enter de tro ve menu...";
            cin.get();

            clearScreen();
            break;
        }
        case 10:
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
    for (int i = 0; i < dm.dsNguoiDung.get_size(); i++)
    {
        if (dm.dsNguoiDung[i].getID() == tenDangNhap)
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
        dm.saveNguoiDung(dm.getBasePath() + "users.txt", dm.dsNguoiDung);
    }
    cout << "\nNhan Enter tiep tuc...";
    cin.get();

    clearScreen();
}

void XuLyThaoTac::XuLyThemGD() {
    clearScreen();
    cout << "--- THEM GIAO DICH ---\n";
    int vitri;
    time_t now = time(0);
    tm gio;
    localtime_s(&gio, &now);
    cout << "Hom nay la ngay: "
        << (1900 + gio.tm_year) << "-"
        << right << setfill('0') << setw(2) << (1 + gio.tm_mon) << "-"
        << setw(2) << gio.tm_mday << endl;
    cout << setfill(' ');

    cout << endl << "Nhac nho nho: 'Vui long nhap thoi gian giao dich dung dinh dang (YYYYMMDD) '" << endl << endl;
    string maGD = getInput<string>("Nhap thoi gian giao dich (YYYYMMDD): ");
    while (maGD == "")
    {
        cout << "khong de ma giao dich trong!! " << endl;
        maGD = getInput<string>("Nhap thoi gian giao dich (YYYYMMDD): ");
    }
    GiaoDich* gd_cha = nullptr;
    for (size_t i = 0; i < dm.dsGiaoDich.get_size(); ++i) {
        if (dm.dsGiaoDich[i].getMaGD() == maGD) {
            gd_cha = &dm.dsGiaoDich[i];
            for (int i = 0; i < dm.dsChiTietGD.get_size(); i++)
            {
                if (dm.dsChiTietGD[i]->getMaGD() == maGD)
                {
                    gd_cha->themChiTiet(dm.dsChiTietGD[i]);
                }
            }
            vitri = i;
            break;
        }
    }

    if (gd_cha == nullptr) {
        GiaoDich gdMoi(maGD);
        dm.dsGiaoDich.push_back(gdMoi);
        gd_cha = &dm.dsGiaoDich.back();
        cout << "Tao Giao dich moi cho ngay: " << maGD << endl;
        vitri = dm.dsGiaoDich.get_size() - 1;
    }
    else {
        cout << "Them chi tiet vao giao dich: " << maGD << endl;
    }
    while (true) {
        cout << "\n--DANH SACH VI---\n";
        qlVi->inDanhSachVi();
        int maVi = getInput<int>("Nhap ma vi: ");
        Vi* vi = qlVi->TimVi(maVi);
        if (!vi) { cout << "Ma vi khong hop le!" << endl; return; }

        cout << "\n--- DANH SACH DANH MUC ---\n";
        qlDM->inDanhSachDM();
        int maDM = getInput<int>("Nhap ma danh muc: ");
        DanhMuc* danhmuc = qlDM->TimDM(maDM);
        if (!danhmuc) { cout << "Ma danh muc khong hop le!" << endl; return; }

        string moTa = getInput<string>("Nhap mo ta: ");
        long long soTien = getInput<int>("Nhap so tien giao dich: ");

        if (soTien <= 0)
        {
            cout << "So tien khong hop le" << endl;
            return;
        }

        ChiTietGD* ct = qlCTGD->taoChiTiet(maGD, maVi, maDM, moTa, soTien);
        ct->setVi(vi);
        ct->setDM(danhmuc);

        gd_cha->themChiTiet(ct);

        qlVi->capNhatSoDu(maVi, soTien, danhmuc->getLoaiDM());

        string xn;
        cout << "Them chi tiet khac? (y/n): ";
        cin >> xn;

        if (xn == "n" || xn == "N") break;

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
    string pass = qlND->AnMK();
    int index = qlND->KiemTraMK(id, pass);
    if (index != -1)
    {
        string mk;
        cout << "Nhap mat khau moi: ";
        mk = qlND->AnMK();
        qlND->DoiMK(index, mk);
        cout << "Doi mat khau thanh cong!" << endl;
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
    string pass = qlND->AnMK();
    int index = qlND->KiemTraMK(id, pass);
    if (index != -1)
    {
        char temp;
        cout << "Xac nhan xoa tai khoan!! (y/n): ";
        cin >> temp;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (temp == 'y')
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
            cout << "Nhap sai! Vui long nhap dung dinh dang so.\n";
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
    if (input.empty()) {
        getline(cin, input);
    }
    return input;
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
