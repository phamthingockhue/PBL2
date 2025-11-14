#pragma once
#include "DanhMuc.h"

class DanhMucChi : public DanhMuc {
public:
    using DanhMuc::DanhMuc;
    string getLoaiDM() const override { return "Chi"; }
};
