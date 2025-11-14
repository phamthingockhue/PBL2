#pragma once
#include <string>
using namespace std;

class DanhMuc {
protected:
    int maDM;
    string tenDM;
public:
    DanhMuc() : maDM(0), tenDM("") {}
    DanhMuc(int _id, const string& _ten)
        : maDM(_id), tenDM(_ten) {
    }

    virtual ~DanhMuc() = default;

    int getMaDM() { return maDM; }
    string getTenDM() { return tenDM; }
    virtual std::string getLoaiDM() const = 0;
};