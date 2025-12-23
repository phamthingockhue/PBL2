#include "DataManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

void DataManager::setBasePath(const string& path) { basePath = path; }
string DataManager::getBasePath() const { return basePath; }

void DataManager::default_user_folder(const string& userFolder) {
    // file vi mac dinh
    ofstream fvi(userFolder + "vi.txt", ios::trunc);
    if (fvi.is_open()) {
        fvi << "1,Tien mat,0\n";
        fvi << "2,Ngan hang,0\n";
        fvi << "3,ShopeePay,0\n";
        fvi.close();
    }

    // file danh muc mac dinh
    ofstream fdm(userFolder + "danhmuc.txt", ios::trunc);
    if (fdm.is_open()) {
        fdm << "1,An uong,Chi\n";
        fdm << "2,Di lai,Chi\n";
        fdm << "3,Mua sam,Chi\n";
        fdm << "4,Luong,Thu\n";
        fdm << "5,Khac,Thu\n";
        fdm.close();
    }

    // tao file rong cho giao dich va chi tiet gd
    ofstream(userFolder + "giaodich.txt").close();
    ofstream(userFolder + "chitietgd.txt").close();
}

void DataManager::loadNguoiDung(const string& tenFile, MyVector<NguoiDung>& dsNguoiDung) {
    dsNguoiDung.clear();
    ifstream fin(tenFile);
    if (!fin.is_open())
    {
        cout << "Khong mo duoc file" << endl;
        return;
    }
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        stringstream ss(line);
        string id, ten, matKhau;
        getline(ss, id, ',');
        getline(ss, ten, ',');
        getline(ss, matKhau, ',');

        dsNguoiDung.push_back(NguoiDung(id, ten, matKhau));
    }
    fin.close();
}

void DataManager::loadVi(const string& tenFile, MyVector<Vi>& dsVi) {
    ifstream fin(tenFile);
    if (!fin.is_open()) return;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string maViStr, tenVi, soDuStr;
        getline(ss, maViStr, ','); int maVi = stoi(maViStr);
        getline(ss, tenVi, ',');
        getline(ss, soDuStr, ','); long long soDu = stoll(soDuStr);

        dsVi.push_back(Vi(maVi, tenVi, soDu));
    }
    fin.close();
}

void DataManager::loadDanhMuc(const string& tenFile, MyVector<DanhMuc*>& dsDanhMuc) {
    ifstream fin(tenFile);
    if (!fin.is_open()) return;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string maDMStr, tenDM, loaiDMStr;
        getline(ss, maDMStr, ','); int maDM = stoi(maDMStr);
        getline(ss, tenDM, ',');
        getline(ss, loaiDMStr, ','); string loaiDM = loaiDMStr;

        if (loaiDM == "Chi") {
            dsDanhMuc.push_back(new DanhMucChi(maDM, tenDM));
        }
        else if (loaiDM == "Thu") {
            dsDanhMuc.push_back(new DanhMucThu(maDM, tenDM));
        }
    }
    fin.close();
}

void DataManager::loadGiaoDich(const string& tenFile, MyVector<GiaoDich>& dsGiaoDich) {
    ifstream fin(tenFile);
    if (!fin.is_open()) return;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string maGD, tongThu_tam, tongChi_tam;
        getline(ss, maGD, ',');
        getline(ss, tongThu_tam, ','); long long tongThu = stoll(tongThu_tam);
        getline(ss, tongChi_tam, ','); long long tongChi = stoll(tongChi_tam);

        dsGiaoDich.push_back(GiaoDich(maGD, tongThu, tongChi));
    }
    fin.close();
}

void DataManager::loadChiTietGD(const string& tenFile, MyVector<ChiTietGD*>& dsChiTietGD) {
    ifstream fin(tenFile);
    if (!fin.is_open()) return;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string maGD, maCTGDStr, maViStr, maDMStr, moTa, soTienGDStr;
        getline(ss, maGD, ',');
        getline(ss, maCTGDStr, ','); int maCTGD = stoi(maCTGDStr);
        getline(ss, maViStr, ','); int maVi = stoi(maViStr);
        getline(ss, maDMStr, ','); int maDM = stoi(maDMStr);
        getline(ss, moTa, ',');
        getline(ss, soTienGDStr, ','); long long soTienGD = stoll(soTienGDStr);

        dsChiTietGD.push_back(new ChiTietGD(maGD, maCTGD, maVi, maDM, moTa, soTienGD));

    }
    fin.close();
}

void DataManager::saveNguoiDung(const string& tenFile, MyVector<NguoiDung>& dsNguoiDung) {
    ofstream fout(tenFile, ios::trunc);
    if (!fout.is_open()) return;
    for (size_t i = 0; i < dsNguoiDung.get_size(); i++) {
        NguoiDung& nd = dsNguoiDung[i];
        fout << nd.getID() << ","
            << nd.getTen() << ","
            << nd.getMatKhau();
        if (i < dsNguoiDung.get_size() - 1) fout << "\n";
    }
    fout.close();

}
void DataManager::saveVi(const string& tenFile, MyVector<Vi>& dsVi) {
    ofstream fout(tenFile, ios::trunc);
    if (!fout.is_open()) return;
    for (size_t i = 0; i < dsVi.get_size(); i++) {
        Vi& vi = dsVi[i];
        fout << vi.getMaVi() << ","
            << vi.getTenVi() << ","
            << vi.getSoDu();
        if (i < dsVi.get_size() - 1) fout << "\n";
    }
    fout.close();
}
void DataManager::saveDanhMuc(const string& tenFile, MyVector<DanhMuc*>& dsDanhMuc) {
    ofstream fout(tenFile, ios::trunc);
    if (!fout.is_open()) return;
    for (size_t i = 0; i < dsDanhMuc.get_size(); i++) {
        DanhMuc* dm = dsDanhMuc[i];
        fout << dm->getMaDM() << ","
            << dm->getTenDM() << ","
            << dm->getLoaiDM();
        if (i < dsDanhMuc.get_size() - 1) fout << "\n";
    }
    fout.close();
}
void DataManager::saveGiaoDich(const string& tenFile, MyVector<GiaoDich>& dsGiaoDich) {
    sapXepGD();
    ofstream fout(tenFile, ios::trunc);
    if (!fout.is_open()) return;
    for (size_t i = 0; i < dsGiaoDich.get_size(); i++) {
        GiaoDich& gd = dsGiaoDich[i];
        fout << gd.getMaGD() << ","
            << gd.getTongThu() << ","
            << gd.getTongChi();
        if (i < dsGiaoDich.get_size() - 1) fout << "\n";
    }
    fout.close();
}
void DataManager::saveChiTietGD(const string& tenFile, MyVector<ChiTietGD*>& dsChiTietGD) {
    sapXepChiTietGD();
    ofstream fout(tenFile, ios::trunc);
    if (!fout.is_open()) return;
    for (size_t i = 0; i < dsChiTietGD.get_size(); i++) {
        ChiTietGD* ct = dsChiTietGD[i];
        fout << ct->getMaGD() << ","
            << ct->getMaCTGD() << ","
            << ct->getMaVi() << ","
            << ct->getMaDM() << ","
            << ct->getMoTa() << ","
            << ct->getSoTienGD();
        if (i < dsChiTietGD.get_size() - 1) fout << "\n";
    }
    fout.close();
}

bool DataManager::loadDataNguoiDung(NguoiDung* nd) {

    string userFolder = basePath + "user_" + nd->getID() + "/";

    dsVi.clear();
    dsDanhMuc.clear();
    dsGiaoDich.clear();
    dsChiTietGD.clear();

    loadVi(userFolder + "vi.txt", dsVi);
    loadDanhMuc(userFolder + "danhmuc.txt", dsDanhMuc);
    loadGiaoDich(userFolder + "giaodich.txt", dsGiaoDich);
    loadChiTietGD(userFolder + "chitietgd.txt", dsChiTietGD);
    linkDuLieu();
    return true;
}

bool DataManager::saveDataNguoiDung(NguoiDung* nd) {
    string userFolder = basePath + "user_" + nd->getID() + "/";

    saveVi(userFolder + "vi.txt", dsVi);
    saveDanhMuc(userFolder + "danhmuc.txt", dsDanhMuc);
    saveGiaoDich(userFolder + "giaodich.txt", dsGiaoDich);
    saveChiTietGD(userFolder + "chitietgd.txt", dsChiTietGD);
    return true;
}

void DataManager::linkDuLieu() {
    for (size_t i = 0; i < dsChiTietGD.get_size(); i++) {
        ChiTietGD* ct = dsChiTietGD[i];

        for (size_t j = 0; j < dsVi.get_size(); j++) {
            if (dsVi[j].getMaVi() == ct->getMaVi()) {
                ct->setVi(&dsVi[j]);
                break;
            }
        }
        for (size_t k = 0; k < dsDanhMuc.get_size(); k++) {
            if (dsDanhMuc[k]->getMaDM() == ct->getMaDM()) {
                ct->setDM(dsDanhMuc[k]);
                break;
            }
        }
    }
}

void DataManager::sapXepChiTietGD() {
    int n = dsChiTietGD.get_size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            string date1 = dsChiTietGD[i]->getMaGD();
            string date2 = dsChiTietGD[j]->getMaGD();

            int id1 = dsChiTietGD[i]->getMaCTGD();
            int id2 = dsChiTietGD[j]->getMaCTGD();

            bool canSwap = false;

            if (date1 < date2) {
                canSwap = true;
            }
            else if (date1 == date2 && id1 > id2) {
                canSwap = true;
            }
            if (canSwap) {
                ChiTietGD* temp = dsChiTietGD[i];
                dsChiTietGD[i] = dsChiTietGD[j];
                dsChiTietGD[j] = temp;
            }
        }
    }
}

void DataManager::sapXepGD() {
    int n = dsGiaoDich.get_size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (dsGiaoDich[i].getMaGD() < dsGiaoDich[j].getMaGD()) {
                GiaoDich temp = dsGiaoDich[i];
                dsGiaoDich[i] = dsGiaoDich[j];
                dsGiaoDich[j] = temp;
            }
        }
    }
}
