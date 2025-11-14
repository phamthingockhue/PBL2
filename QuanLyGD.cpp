//#include "QuanLyGD.h"
//
//int QuanLyGD::TimGD(const string& ma)
//{
//    for (int i = dsGiaoDich.get_size() - 1; i >= 0; i--)
//    {
//        if (dsGiaoDich[i].getMaGD() == ma) return i;
//    }
//    return -1;
//}
//
//
//void QuanLyGD::capNhatTongTien(int& index)
//{
//    long long tongTien = 0;
//    for (size_t i = 0; i < danhSachChiTiet.get_size(); ++i) {
//        //           danhSachChiTiet[i].capNhatSoDuVi(0);
//        if (danhSachChiTiet[i].getDanhMuc()->getLoaiDM() == "Chi") {
//            tongTien -= danhSachChiTiet[i].getSoTienGD();
//        }
//        else {
//            tongTien += danhSachChiTiet[i].getSoTienGD();
//        }
//    }
//}