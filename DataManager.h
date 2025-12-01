#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "MyVector.h"

#include "NguoiDung.h"
#include "Vi.h"
#include "DanhMucChi.h"
#include "DanhMucThu.h"
#include "GiaoDich.h"
#include "ChiTietGD.h"


namespace fs = std::filesystem;

using namespace std;
class DataManager
{
private:
    string basePath;

public:
    MyVector<NguoiDung> dsNguoiDung;
    MyVector<Vi> dsVi;
    MyVector<DanhMuc*> dsDanhMuc;
    MyVector<GiaoDich> dsGiaoDich;
    MyVector<ChiTietGD*> dsChiTietGD;

    void setBasePath(const string& path);
    string getBasePath() const;

    void default_user_folder(const string& userFolder);

    DataManager() = default;
    DataManager(const string& _basePath) : basePath(_basePath) {}
    ~DataManager() {
        for (int i = 0; i < dsDanhMuc.get_size(); i++) {
            if (dsDanhMuc[i] != nullptr) {
                delete dsDanhMuc[i];
            }
        }
        for (int i = 0; i < dsChiTietGD.get_size(); i++) {
            if (dsChiTietGD[i] != nullptr) {
                delete dsChiTietGD[i];
            }
        }
    }

    void sapXepChiTietGD();
    void sapXepGD();

    void loadNguoiDung(const string& tenFile, MyVector<NguoiDung>& dsNguoiDung);
    void loadVi(const string& tenFile, MyVector<Vi>& dsVi);
    void loadDanhMuc(const string& tenFile, MyVector<DanhMuc*>& dsDanhMuc);
    void loadGiaoDich(const string& tenFile, MyVector<GiaoDich>& dsGiaoDich);
    void loadChiTietGD(const string& tenFile, MyVector<ChiTietGD*>& dsChiTietGD);

    void saveNguoiDung(const string& tenFile, MyVector<NguoiDung>& dsNguoiDung);
    void saveVi(const string& tenFile, MyVector<Vi>& dsVi);
    void saveDanhMuc(const string& tenFile, MyVector<DanhMuc*>& dsDanhMuc);
    void saveGiaoDich(const string& tenFile, MyVector<GiaoDich>& dsGiaoDich);
    void saveChiTietGD(const string& tenFile, MyVector<ChiTietGD*>& dsChiTietGD);

    bool loadDataNguoiDung(NguoiDung* nd);
    bool saveDataNguoiDung(NguoiDung* nd);

    void linkDuLieu();
};
