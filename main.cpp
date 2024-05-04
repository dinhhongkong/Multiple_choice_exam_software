using namespace std;
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <direct.h> //Thu vien tao FOLDER
#include <fstream>
#include <ctime>
#include <cmath>
#include <thread>

#include "MODULE/define.h"
#include "MODULE/struct.h"
#include "MODULE/random.h"

#include "CONTROL/Button.h"
#include "CONTROL/EditText.h"
#include "CONTROL/RadioButon.h"
#include "CONTROL/Scan.h"
#include "CONTROL/local.h"

#include "MODULE/cauhoi.h"
#include "MODULE/diem.h"
#include "MODULE/baithi.h"
#include "MODULE/sinhvien.h"
#include "MODULE/monhoc.h"
#include "MODULE/lop.h"

#include "GRAPHIC/drawUI.h"
#include "GRAPHIC/displayHocSinh.h"
#include "GRAPHIC/displayGiaoVien.h"
#include "GRAPHIC/displayLogin.h"
// Bien dich thu cong bang tay qua lenh CMD
// g++ -std=c++17 main.cpp -o main -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lwinmm

int main()
{
    // 1600 * 900 la do phan giai man hinh 14 inch (Ti le 16/9)
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    mainWindow = initwindow(1600, 900, "THI TRAC NGHIEM", GetSystemMetrics(SM_CXSCREEN) / 2 - 800);

    hWnd = FindWindowA(nullptr, "THI TRAC NGHIEM");
    HICON iconApp = reinterpret_cast<HICON>(LoadImage(nullptr, "IMAGE\\icon_window.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE));
    reinterpret_cast<HICON>(SendMessage(hWnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(iconApp)));
    reinterpret_cast<HICON>(SendMessage(hWnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(iconApp)));

    mkdir("DATA");
    mkdir("DATA\\FileDSDiem");
    mkdir("DATA\\FileDSSinhVien");

    srand((int)time(0));

    dslop DanhSachLop;
    docFileDsLop(DanhSachLop);

    ListMonHoc listMH;
    Doc_File_Mon_Hoc(listMH);

    IDRandom *listID = Tao_MIN_MAX(listID, MIN_ID, MAX_ID);
    NodeCauHoi *rootCayCauHoi = nullptr;
    Doc_File_Cau_Hoi(rootCayCauHoi, listID);

    mangCauHoi arrCauHoi;

    Diem_Thi gvThiThu;

    drawLogin();
    while (true)
    {
        GetAsyncKeyState(VK_RBUTTON);
        KeyboardEvent();
        if (curMenu == DISPLAY_LOGIN)
        {
            displayLogin(listMH, DanhSachLop, listID, rootCayCauHoi, arrCauHoi);
        }
        else if (curMenu == DISPLAY_GIAOVIEN)
        {
            displayGV();
        }
        else if (curMenu == DISPLAY_DSMON)
        {
            DisplayMonHoc(rootCayCauHoi, listMH);
        }
        else if (curMenu == DISPLAY_DSLOP)
        {
            DisplayLop(DanhSachLop);
        }
        else if (curMenu == DISPLAY_DIEMMON || curMenu == LUACHON_MON)
        {
            // Lua chon 1 mon roi den tinh nang khac
            displayLuaChonMon(listMH);
        }
        else if (curMenu == LUACHON_LOP)
        {
            // Xem diem theo mon cho ca 1 lop
            displayLuaChonLop1(DanhSachLop, listMH.monHoc[luaChonMon]->MAMH, listMH.monHoc[luaChonMon]->TENMH);
        }
        else if (curMenu == DISLPAY_DIEM_THEO_SV)
        {
            // Chon lop roi chon sv, roi xem toan bo DIEM cac mon da thi
            displayLuaChonLop2(DanhSachLop, listMH);
        }
        else if (curMenu == DISPLAY_DSDIEMGV)
        {
            diplayDsDiem(listMH.monHoc[luaChonMon]->MAMH, DanhSachLop.arrLop[luaChonLop]);
        }
        else if (curMenu == CHUCNANG_CAUHOI)
        {
            displayChucNangCauHoi(rootCayCauHoi, listID, listMH);
        }
        else if (curMenu == DISPLAY_THITHU)
        {
            displayThietLapThiThu(listMH, rootCayCauHoi, arrCauHoi, gvThiThu);
        }
        else if (curMenu == VAO_THITHU)
        {
            displayThiThu(gvThiThu);
        }
        else if (curMenu == XEMBAI_THUTHU)
        {
            displayXemBaiThiThu(gvThiThu);
        }

        if (preMenu == VAO_THITHU)
        {
            timer.join();
            chamBai(gvThiThu);
            drawGV();
            windowDiemSo = initwindow(600, 500, "DIEM SO", GetSystemMetrics(SM_CXSCREEN) / 2 - 300, 200);
            Sleep(100);
            drawDiemVuaThi(gvThiThu.Diem);
            while (!btnQuaylai.click)
            {
                displayDiemVuaThi();
            }
            btnQuaylai.click = false;
            preMenu = -1;
        }
        Sleep(100);
    }
}