#pragma once
#include "DanhMuc.h"

class DanhMucThu : public DanhMuc {
public:
    using DanhMuc::DanhMuc;
    string getLoaiDM() const override { return "Thu"; }
};