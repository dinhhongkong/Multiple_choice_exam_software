
void displaySinhVien(dslop DanhSachLop, listSV &danhSachSV, string maLop);

void displayGV()
{
    btnMonHoc.ButtonEffect();
    btnDsLop.ButtonEffect();
    btnDiemThi.ButtonEffect();
    btnCauHoiThi.ButtonEffect();
    btnThiThu.ButtonEffect();
    btnDangXuat.ButtonEffect();

    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (btnDangXuat.isMouseHover())
        {
            curMenu = DISPLAY_LOGIN;
            drawLogin();
        }
        else if (btnMonHoc.isMouseHover())
        {
            curMenu = DISPLAY_DSMON;
            drawList = true;
            MenuThemMon = true;
            drawMonHoc();
        }
        else if (btnDsLop.isMouseHover())
        {
            curMenu = DISPLAY_DSLOP;
            drawList = true;
            MenuThemLop = true;
            drawLop();
            Sleep(150);
        }
        else if (btnDiemThi.isMouseHover())
        {
            window1 = initwindow(600, 500, "XEM DIEM", GetSystemMetrics(SM_CXSCREEN) / 2 - 300, 200);
            setcurrentwindow(window1);
            drawChonXemDiem();
            while (true)
            {
                btnQuaylai.ButtonEffect();
                btnDiemSV.ButtonEffect();
                btnDiemLop.ButtonEffect();
                if (GetAsyncKeyState(VK_LBUTTON))
                {
                    if (btnQuaylai.isMouseHover())
                    {
                        closegraph(CURRENT_WINDOW);
                        setcurrentwindow(mainWindow);
                        break;
                    }
                    else if (btnDiemLop.isMouseHover())
                    {
                        closegraph(CURRENT_WINDOW);
                        setcurrentwindow(mainWindow);
                        preMenu = DISPLAY_GIAOVIEN;
                        curMenu = DISPLAY_DIEMMON;
                        MenuThemMon = false;
                        MenuThemLop = false;
                        drawMonHoc();
                        Sleep(150);
                        break;
                    }
                    else if (btnDiemSV.isMouseHover())
                    {
                        closegraph(CURRENT_WINDOW);
                        setcurrentwindow(mainWindow);
                        preMenu = DISPLAY_GIAOVIEN;
                        curMenu = DISLPAY_DIEM_THEO_SV;
                        MenuThemMon = false;
                        MenuThemLop = false;
                        drawLop();
                        Sleep(150);
                        break;
                    }
                }
                Sleep(75);
            }
        }
        else if (btnCauHoiThi.isMouseHover())
        {
            curMenu = CHUCNANG_CAUHOI;
            drawCauHoi();
            drawThemCauHoi();
            MenuThemMon = false;
        }
        else if (btnThiThu.isMouseHover())
        {
            curMenu = DISPLAY_THITHU;
            drawMonHoc();
            drawThietLapThi();
        }
    }
}

// ------------------------------------- CHON SINH VIEN DE XEM DIEM (GV) ---------------------
void displayChonSinhVien(dslop DanhSachLop, listSV &danhSachSV, string maLop, ListMonHoc listMH);
void ClickItemChonLop(dslop &DanhSachLop, ListMonHoc listMH)
{
    int x = -1, y = -1;
    x = mousex();
    y = mousey();
    static int LuaChon = -1; // Thanh sang khi di chuot qua ITEAM
    static int PreLuaChon = -1;

    LuaChon = (y - yDsLop[0]) / 50;

    if (x > xDsLop[0] && x < xDsLop[2] && y > yDsLop[0] && y < yDsLop[1])
    {
        // Khoi phuc ITEAM
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        if (PreLuaChon != -1 && PreLuaChon != LuaChon && PreLuaChon < listviewDS.size)
        {
            setcolor(WHITE);
            setfillstyle(1, BLACK);
            setbkcolor(BLACK);
            bar(xDsLop[0] + 5, yDsLop[0] + 20 + PreLuaChon * 50 - 10, xDsLop[2] - 5, yDsLop[0] + 20 + PreLuaChon * 50 + 30);
            outtextxy(xDsLop[0] + 70, yDsLop[0] + 20 + PreLuaChon * 50, &DanhSachLop.arrLop[listviewDS.idItem[PreLuaChon]].MALOP[0]);
            outtextxy(xDsLop[1] + 70, yDsLop[0] + 20 + PreLuaChon * 50, &DanhSachLop.arrLop[listviewDS.idItem[PreLuaChon]].TENLOP[0]);
        }

        PreLuaChon = LuaChon;
        // Ve ITEAM hien tai
        if (PreLuaChon != -1 && LuaChon < listviewDS.size)
        {
            setcolor(LIGHTGREEN);
            setfillstyle(1, RED);
            setbkcolor(RED);
            bar(xDsLop[0] + 5, yDsLop[0] + 20 + PreLuaChon * 50 - 10, xDsLop[2] - 5, yDsLop[0] + 20 + PreLuaChon * 50 + 30);
            outtextxy(xDsLop[0] + 70, yDsLop[0] + 20 + LuaChon * 50, &DanhSachLop.arrLop[listviewDS.idItem[LuaChon]].MALOP[0]);
            outtextxy(xDsLop[1] + 70, yDsLop[0] + 20 + LuaChon * 50, &DanhSachLop.arrLop[listviewDS.idItem[LuaChon]].TENLOP[0]);
        }
        setlinestyle(0, 0, 2);
        setcolor(WHITE);
        line(350, 200, 350, 760);

        // Bat su kien khi click vao ITEAM, khi click chuot trai hoac chuot phai
        if (GetAsyncKeyState(VK_LBUTTON) && LuaChon < listviewDS.size && curMenu == DISLPAY_DIEM_THEO_SV)
        {
            int viTri = listviewDS.idItem[LuaChon];
            drawSinhVien(DanhSachLop.arrLop[listviewDS.idItem[LuaChon]].TENLOP);
            drawList = true;
            Edit = nullptr;
            while (true)
            {
                KeyboardEvent();
                displayChonSinhVien(DanhSachLop, DanhSachLop.arrLop[viTri].dsSinhVien, DanhSachLop.arrLop[viTri].MALOP, listMH);
                if (btnQuaylai.click)
                {
                    btnQuaylai.click = false;
                    break;
                }
                Sleep(75);
            }
        }
    }
    else
    {
        // Khoi phuc ITEAM
        if (PreLuaChon != -1 && PreLuaChon < listviewDS.size)
        {
            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
            setcolor(WHITE);
            setfillstyle(1, BLACK);
            setbkcolor(BLACK);
            bar(xDsLop[0] + 5, yDsLop[0] + 20 + PreLuaChon * 50 - 10, xDsLop[2] - 5, yDsLop[0] + 20 + PreLuaChon * 50 + 30);
            outtextxy(xDsLop[0] + 70, yDsLop[0] + 20 + PreLuaChon * 50, &DanhSachLop.arrLop[listviewDS.idItem[PreLuaChon]].MALOP[0]);
            outtextxy(xDsLop[1] + 70, yDsLop[0] + 20 + PreLuaChon * 50, &DanhSachLop.arrLop[listviewDS.idItem[PreLuaChon]].TENLOP[0]);
        }
        LuaChon = -1;
        PreLuaChon = -1;
        setlinestyle(0, 0, 2);
        setcolor(WHITE);
        line(350, 200, 350, 760);
    }
    return;
}

void ClickChonSinhVien(dslop DanhSachLop, listSV &danhSachSV, string maLop, ListMonHoc listMH)
{
    int x = -1, y = -1;
    x = mousex();
    y = mousey();
    static int LuaChon = -1; // Thanh sang khi di chuot qua ITEAM
    static int PreLuaChon = -1;
    int soLuongSV = SizeListSV(danhSachSV);

    LuaChon = (y - yDsSV[0]) / 50;
    nodeSV *node = danhSachSV.First;

    if (x > xDsSV[0] && x < xDsSV[4] && y > yDsSV[0] && y < yDsSV[1])
    {
        // Khoi phuc ITEAM
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        if (PreLuaChon != -1 && PreLuaChon != LuaChon && PreLuaChon < listviewDS.size)
        {
            setcolor(WHITE);
            setfillstyle(1, BLACK);
            setbkcolor(BLACK);
            bar(0, yDsSV[0] + 20 + PreLuaChon * 50 - 10, xDsSV[0] - 5, yDsSV[0] + 20 + PreLuaChon * 50 + 30);
        }

        PreLuaChon = LuaChon;
        // Ve ITEAM hien tai
        if (PreLuaChon != -1 && LuaChon < listviewDS.size)
        {
            setcolor(LIGHTGREEN);
            setfillstyle(1, RED);
            setbkcolor(RED);
            readimagefile(troNgonTay, 0, yDsSV[0] + 20 + PreLuaChon * 50 - 10, xDsSV[0] - 5, yDsSV[0] + 20 + PreLuaChon * 50 + 30);
        }
        setlinestyle(0, 0, 2);
        setcolor(WHITE);
        line(250, 200, 250, 760);
        // Ve HO SV
        line(600, 200, 600, 760);
        // Ve TEN SV
        line(800, 200, 800, 760);
        // Bat su kien khi click vao ITEAM, khi click chuot trai hoac chuot phai

        if (GetAsyncKeyState(VK_LBUTTON) && LuaChon < listviewDS.size)
        {
            node = danhSachSV.First;
            for (int i = 0; i < listviewDS.idItem[LuaChon]; i++)
            {
                if (node == nullptr)
                {
                    break;
                }
                node = node->pNext;
            }
            drawDiemSV();
            listviewDS.size = 0;
            drawDsDiemSV(node->info.listDT, listMH);
            Edit = nullptr;
            while (true)
            {
                displayDiemSV(node->info, listMH, maLop);
                if (btnQuaylai.click)
                {
                    Sleep(100);
                    break;
                }
                Sleep(75);
            }
        }
    }
    else
    {
        // Khoi phuc ITEAM
        if (PreLuaChon != -1 && PreLuaChon < listviewDS.size)
        {
            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
            setcolor(WHITE);
            setfillstyle(1, BLACK);
            setbkcolor(BLACK);
            setcolor(WHITE);
            setfillstyle(1, BLACK);
            setbkcolor(BLACK);
            bar(0, yDsDiemSV[0] + 20 + PreLuaChon * 50 - 10, xDsSV[0] - 5, yDsSV[0] + 20 + PreLuaChon * 50 + 30);
        }
        LuaChon = -1;
        PreLuaChon = -1;
        setlinestyle(0, 0, 2);
        setcolor(WHITE);
    }
}

void displayChonSinhVien(dslop DanhSachLop, listSV &danhSachSV, string maLop, ListMonHoc listMH)
{
    static int checkTimKiem = 0;
    if (drawList == true)
    {
        drawDsSinhVien(danhSachSV);
        drawList = false;
        if (checkTimKiem < 0)
        {
            checkTimKiem = 0;
        }
    }
    if (edtimKiemSV.content.size() > checkTimKiem)
    {
        checkTimKiem++;
        drawList = true;
    }
    else if (edtimKiemSV.content.size() == checkTimKiem)
    {
        drawList = false;
    }
    else if (edtimKiemSV.content.size() < checkTimKiem)
    {
        checkTimKiem -= 2;
        drawList = true;
    }

    btnQuaylai.ButtonEffect();
    btnLui.ButtonEffect();
    btnTien.ButtonEffect();

    ClickChonSinhVien(DanhSachLop, danhSachSV, maLop, listMH);
    if (btnQuaylai.click)
    {
        drawSinhVien(maLop);
        drawDsSinhVien(danhSachSV);
        btnQuaylai.click = false;
    }

    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (btnQuaylai.isMouseHover())
        {
            curMenu = DISLPAY_DIEM_THEO_SV;
            drawLop();
            Sleep(200);
            drawList = true;
            edtimKiemSV.content = "";
            Edit = nullptr;
            btnQuaylai.click = true;
            listviewDS.click = false;
        }
        else if (edtimKiemSV.isMouseHover())
        {
            Edit = &edtimKiemSV;
        }
        else if (btnTien.isMouseHover())
        {
            drawList = true;
            btnTien.click = true;
        }
        else if (btnLui.isMouseHover())
        {
            drawList = true;
            btnLui.click = true;
        }
    }
}

//------------------------------------------------ CHUC NANG QUAN LI MON HOC ----------------------------------------
void ClickItemMonHoc(NodeCauHoi *root, ListMonHoc &listMH)
{
    int x = -1, y = -1;
    x = mousex();
    y = mousey();
    static int LuaChon = -1; // Thanh sang khi di chuot qua ITEAM
    static int PreLuaChon = -1;

    LuaChon = (y - yDsMon[0]) / 50;

    if (x > xDsMon[0] && x < xDsMon[2] && y > yDsMon[0] && y < yDsMon[1])
    {
        // Khoi phuc ITEAM
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        if (PreLuaChon != -1 && PreLuaChon != LuaChon && PreLuaChon < listviewDS.size)
        {
            setcolor(WHITE);
            setfillstyle(1, BLACK);
            setbkcolor(BLACK);
            bar(xDsMon[0] + 5, yDsMon[0] + 20 + PreLuaChon * 50 - 10, xDsMon[2] - 5, yDsMon[0] + 20 + PreLuaChon * 50 + 30);
            outtextxy(xDsMon[0] + 40, yDsMon[0] + 20 + PreLuaChon * 50, &listMH.monHoc[listviewDS.idItem[PreLuaChon]]->MAMH[0]);
            outtextxy(xDsMon[1] + 40, yDsMon[0] + 20 + PreLuaChon * 50, &listMH.monHoc[listviewDS.idItem[PreLuaChon]]->TENMH[0]);
        }

        PreLuaChon = LuaChon;
        // Ve ITEAM hien tai
        if (PreLuaChon != -1 && LuaChon < listviewDS.size)
        {
            setcolor(LIGHTGREEN);
            setfillstyle(1, RED);
            setbkcolor(RED);
            bar(xDsMon[0] + 5, yDsMon[0] + 20 + PreLuaChon * 50 - 10, xDsMon[2] - 5, yDsMon[0] + 20 + PreLuaChon * 50 + 30);
            outtextxy(xDsMon[0] + 40, yDsMon[0] + 20 + LuaChon * 50, &listMH.monHoc[listviewDS.idItem[LuaChon]]->MAMH[0]);
            outtextxy(xDsMon[1] + 40, yDsMon[0] + 20 + LuaChon * 50, &listMH.monHoc[listviewDS.idItem[LuaChon]]->TENMH[0]);
        }
        setlinestyle(0, 0, 2);
        setcolor(WHITE);
        line(300, 200, 300, 760);

        // Bat su kien khi o giao dien danh sach mon (Co the them & hieu chinh)
        if (GetAsyncKeyState(VK_RBUTTON) && LuaChon < listviewDS.size && curMenu == DISPLAY_DSMON)
        {
            Sleep(20);
            themMaMon.content = listMH.monHoc[listviewDS.idItem[LuaChon]]->MAMH;
            themTenMon.content = listMH.monHoc[listviewDS.idItem[LuaChon]]->TENMH;
            drawHieuChinhMonHoc();
            while (true)
            {
                KeyboardEvent();
                btnHieuChinh.ButtonEffect();
                btnXoaVinhVien.ButtonEffect();
                btnThoat.ButtonEffect();
                btnQuaylai.ButtonEffect();
                GetAsyncKeyState(VK_RBUTTON); // Xoa bo nho dem chuot trai
                if (GetAsyncKeyState(VK_LBUTTON))
                {
                    if (btnXoaVinhVien.isMouseHover())
                    {
                        AllocConsole();
                        if (MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Ban co chac chan muon xoa?", "Thong bao", MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
                        {
                            if (Xoa_Mon_Hoc(root, listMH, listviewDS.idItem[LuaChon]))
                            {
                                Luu_File_Mon_Hoc(listMH);
                                drawList = true;
                                themMaMon.content = "";
                                themTenMon.content = "";
                                MenuThemMon = true;
                                DrawThemMonHoc();
                                break;
                            }
                        }
                    }
                    else if (btnHieuChinh.isMouseHover())
                    {
                        if (themMaMon.content.size() == 0)
                        {
                            AllocConsole();
                            MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Khong duoc de trong MA MON!", "Thong bao", MB_ICONASTERISK | MB_OK);
                            Edit = &themMaMon;
                        }
                        else if (themTenMon.content.size() == 0)
                        {
                            AllocConsole();
                            MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Khong duoc de trong TEN MON!", "Thong bao", MB_ICONASTERISK | MB_OK);
                            Edit = &themTenMon;
                        }
                        else if (Hieu_Chinh_Mon_Hoc(root, listMH, listviewDS.idItem[LuaChon], themMaMon.ToString(), themTenMon.ToString()))
                        {
                            Luu_File_Mon_Hoc(listMH);
                            drawDSMonHoc(listMH);
                            themMaMon.content = "";
                            themTenMon.content = "";
                            MenuThemMon = true;
                            DrawThemMonHoc();
                            break;
                        }
                    }
                    else if (btnThoat.isMouseHover())
                    {
                        setfillstyle(1, BLACK);
                        bar(1005, 0, 1600, 765);
                        themMaMon.content = "";
                        themTenMon.content = "";
                        MenuThemMon = true;
                        Sleep(100);
                        DrawThemMonHoc();
                        break;
                    }
                    else if (themMaMon.isMouseHover())
                    {
                        Edit = &themMaMon;
                    }
                    else if (themTenMon.isMouseHover())
                    {
                        Edit = &themTenMon;
                    }
                    else if (btnQuaylai.isMouseHover())
                    {
                        curMenu = DISPLAY_GIAOVIEN;
                        drawGV();
                        Edit = nullptr;
                        themMaMon.content = "";
                        themTenMon.content = "";
                        timKiemMon.content = "";
                        soTrangMon = 1;
                        break;
                    }
                }
                Sleep(75);
            }
        }

        else if (GetAsyncKeyState(VK_LBUTTON) && LuaChon < listviewDS.size && curMenu == DISPLAY_THITHU)
        {
            edChonMonThi.content = listMH.monHoc[listviewDS.idItem[LuaChon]]->MAMH;
            outtextTenMon = listMH.monHoc[listviewDS.idItem[LuaChon]]->TENMH;
            edChonMonThi.draw();
            setfillstyle(WIDE_DOT_FILL, CYAN);
            bar(1052, 250, 1550, 300);
            setcolor(YELLOW);
            settextstyle(0, 0, 2);
            outtextxy(1300 - textwidth(&outtextTenMon[0]) / 2, 260, &outtextTenMon[0]);
            setfillstyle(1, BLACK);
            bar(1052, 540, 1550, 600);
            int dem = 0;
            demSoCauTheoMaMon(root, listMH.monHoc[listviewDS.idItem[LuaChon]]->MAMH, dem);
            string tongSoCau = "So cau hoi hien co: " + to_string(dem);
            settextstyle(10, 0, 3);
            outtextxy(1300 - textwidth(&tongSoCau[0]) / 2, 560, &tongSoCau[0]);
        }
        else if (GetAsyncKeyState(VK_LBUTTON) && LuaChon < listviewDS.size && curMenu == DISPLAY_DIEMMON)
        {
            curMenu = LUACHON_LOP;
            drawList = true;
            drawLop();
            luaChonMon = listviewDS.idItem[LuaChon];
            outtextTenMon = listMH.monHoc[listviewDS.idItem[LuaChon]]->TENMH;
        }
        else if (GetAsyncKeyState(VK_LBUTTON) && LuaChon < listviewDS.size && curMenu == LUACHON_MON)
        {
            curMenu = CHUCNANG_CAUHOI;
            edChonMaMon.content = listMH.monHoc[listviewDS.idItem[LuaChon]]->MAMH;
            outtextTenMon = "Mon: " + listMH.monHoc[listviewDS.idItem[LuaChon]]->TENMH;
            drawCauHoi();
            if (chucNangThemCauHoi)
            {
                drawThemCauHoi();
            }
            else
            {
                drawHieuChinhCauHoi(Truy_Xuat_Ten_Mon(listMH, listMH.monHoc[listviewDS.idItem[LuaChon]]->MAMH));
            }

            drawList = true;
            luaChonMon = listviewDS.idItem[LuaChon];
        }
    }
    else
    {
        // Khoi phuc ITEAM
        if (PreLuaChon != -1 && PreLuaChon < listviewDS.size)
        {
            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
            setcolor(WHITE);
            setfillstyle(1, BLACK);
            setbkcolor(BLACK);
            bar(xDsMon[0] + 5, yDsMon[0] + 20 + PreLuaChon * 50 - 10, xDsMon[2] - 5, yDsMon[0] + 20 + PreLuaChon * 50 + 30);
            outtextxy(xDsMon[0] + 40, yDsMon[0] + 20 + PreLuaChon * 50, &listMH.monHoc[listviewDS.idItem[PreLuaChon]]->MAMH[0]);
            outtextxy(xDsMon[1] + 40, yDsMon[0] + 20 + PreLuaChon * 50, &listMH.monHoc[listviewDS.idItem[PreLuaChon]]->TENMH[0]);
        }
        LuaChon = -1;
        PreLuaChon = -1;
        setlinestyle(0, 0, 2);
        setcolor(WHITE);
        line(300, 200, 300, 760);
    }
}

void DisplayMonHoc(NodeCauHoi *r, ListMonHoc &listMH)
{
    // Tim kiem theo nhap tu ban phim, xuat ra man hinh luon
    static int checkTimKiem = 0;
    if (drawList == true)
    {
        drawDSMonHoc(listMH);
        drawList = false;
        if (checkTimKiem < 0)
        {
            checkTimKiem = 0;
        }
    }
    if (timKiemMon.content.size() > checkTimKiem)
    {
        checkTimKiem++;
        drawList = true;
    }
    else if (timKiemMon.content.size() == checkTimKiem)
    {
        drawList = false;
    }
    else if (timKiemMon.content.size() < checkTimKiem)
    {
        checkTimKiem -= 2;
        drawList = true;
    }

    ClickItemMonHoc(r, listMH);

    btnQuaylai.ButtonEffect();
    btnTien.ButtonEffect();
    btnLui.ButtonEffect();

    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (btnQuaylai.isMouseHover())
        {
            curMenu = DISPLAY_GIAOVIEN;
            drawGV();
            MenuThemMon = true;
            Edit = nullptr;
            themMaMon.content = "";
            themTenMon.content = "";
            timKiemMon.content = "";
            drawList = true;
            soTrangMon = 1;
        }
        else if (timKiemMon.isMouseHover())
        {
            Edit = &timKiemMon;
        }
        else if (btnTien.isMouseHover())
        {
            drawList = true;
            btnTien.click = true;
            btnLui.click = false;
        }
        else if (btnLui.isMouseHover())
        {
            drawList = true;
            btnTien.click = false;
            btnLui.click = true;
        }
    }

    if (MenuThemMon)
    {
        btnThem.ButtonEffect();
        if (GetAsyncKeyState(VK_LBUTTON))
        {
            if (themMaMon.isMouseHover())
            {
                Edit = &themMaMon;
            }
            else if (themTenMon.isMouseHover())
            {
                Edit = &themTenMon;
            }
            else if (btnThem.isMouseHover())
            {
                if (themMaMon.content.size() == 0)
                {
                    AllocConsole();
                    MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Khong duoc de trong MA MON!", "Thong bao", MB_ICONASTERISK | MB_OK);
                    Edit = &themMaMon;
                }
                else if (themTenMon.content.size() == 0)
                {
                    AllocConsole();
                    MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Khong duoc de trong TEN MON!", "Thong bao", MB_ICONASTERISK | MB_OK);
                    Edit = &themTenMon;
                }
                else
                {
                    // Them mon hoc
                    Mon_Hoc mh;
                    mh.MAMH = themMaMon.ToString();
                    mh.TENMH = themTenMon.ToString();

                    if (Them_Mon_Hoc(listMH, mh))
                    {
                        Luu_File_Mon_Hoc(listMH);
                        drawList = true;
                        themMaMon.content = "";
                        themTenMon.content = "";
                        themMaMon.draw();
                        themTenMon.draw();
                    }
                }
            }
        }
    }
}

//------------------------------------------------ CHUC NANG QUAN Ly LOP HOC ----------------------------------------
void ClickItemLop(dslop &DanhSachLop, string maMon = "", string tenMon = "")
{
    int x = -1, y = -1;
    x = mousex();
    y = mousey();
    static int LuaChon = -1; // Thanh sang khi di chuot qua ITEAM
    static int PreLuaChon = -1;

    LuaChon = (y - yDsLop[0]) / 50;

    if (x > xDsLop[0] && x < xDsLop[2] && y > yDsLop[0] && y < yDsLop[1])
    {
        // Khoi phuc ITEAM
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        if (PreLuaChon != -1 && PreLuaChon != LuaChon && PreLuaChon < listviewDS.size)
        {
            setcolor(WHITE);
            setfillstyle(1, BLACK);
            setbkcolor(BLACK);
            bar(xDsLop[0] + 5, yDsLop[0] + 20 + PreLuaChon * 50 - 10, xDsLop[2] - 5, yDsLop[0] + 20 + PreLuaChon * 50 + 30);
            outtextxy(xDsLop[0] + 70, yDsLop[0] + 20 + PreLuaChon * 50, &DanhSachLop.arrLop[listviewDS.idItem[PreLuaChon]].MALOP[0]);
            outtextxy(xDsLop[1] + 70, yDsLop[0] + 20 + PreLuaChon * 50, &DanhSachLop.arrLop[listviewDS.idItem[PreLuaChon]].TENLOP[0]);
        }

        PreLuaChon = LuaChon;
        // Ve ITEAM hien tai
        if (PreLuaChon != -1 && LuaChon < listviewDS.size)
        {
            setcolor(LIGHTGREEN);
            setfillstyle(1, RED);
            setbkcolor(RED);
            bar(xDsLop[0] + 5, yDsLop[0] + 20 + PreLuaChon * 50 - 10, xDsLop[2] - 5, yDsLop[0] + 20 + PreLuaChon * 50 + 30);
            outtextxy(xDsLop[0] + 70, yDsLop[0] + 20 + LuaChon * 50, &DanhSachLop.arrLop[listviewDS.idItem[LuaChon]].MALOP[0]);
            outtextxy(xDsLop[1] + 70, yDsLop[0] + 20 + LuaChon * 50, &DanhSachLop.arrLop[listviewDS.idItem[LuaChon]].TENLOP[0]);
        }
        setlinestyle(0, 0, 2);
        setcolor(WHITE);
        line(350, 200, 350, 760);

        // Bat su kien khi click vao ITEAM, khi click chuot trai hoac chuot phai
        if (GetAsyncKeyState(VK_RBUTTON) && LuaChon < listviewDS.size && curMenu == DISPLAY_DSLOP)
        {
            Sleep(20);
            themMaLop.content = DanhSachLop.arrLop[listviewDS.idItem[LuaChon]].MALOP;
            themTenLop.content = DanhSachLop.arrLop[listviewDS.idItem[LuaChon]].TENLOP;
            drawHieuChinhLop();
            while (true)
            {
                KeyboardEvent();
                btnHieuChinh.ButtonEffect();
                btnXoaVinhVien.ButtonEffect();
                btnThoat.ButtonEffect();
                btnQuaylai.ButtonEffect();
                GetAsyncKeyState(VK_RBUTTON); // Xoa bo nho dem chuot trai
                if (GetAsyncKeyState(VK_LBUTTON))
                {
                    if (btnXoaVinhVien.isMouseHover())
                    {
                        AllocConsole();
                        if (MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Ban chac chan muon xoa?", "Thong bao", MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
                        {
                            xoaLop(DanhSachLop, listviewDS.idItem[LuaChon]);
                            ghiFileDSlop(DanhSachLop);
                            drawDSLop(DanhSachLop);

                            MenuThemLop = true;
                            setfillstyle(1, BLACK);
                            bar(1005, 0, 1600, 765);
                            themMaLop.content = "";
                            themTenLop.content = "";
                            drawThemLop();
                            break;
                        }
                    }
                    else if (btnQuaylai.isMouseHover())
                    {
                        curMenu = DISPLAY_GIAOVIEN;
                        MenuThemLop = true;
                        drawGV();
                        Edit = nullptr;
                        themMaLop.content = "";
                        themTenLop.content = "";
                        timKiemLop.content = "";
                        soTrangLop = 1;
                        break;
                    }
                    else if (btnHieuChinh.isMouseHover())
                    {
                        if (themMaLop.content.size() == 0)
                        {
                            AllocConsole();
                            MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Khong duoc de trong MA LOP!", "Thong bao", MB_ICONASTERISK | MB_OK);
                            Edit = &themMaLop;
                        }
                        else if (themTenLop.content.size() == 0)
                        {
                            AllocConsole();
                            MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Khong duoc de trong TEN LOP!", "Thong bao", MB_ICONASTERISK | MB_OK);
                            Edit = &themTenLop;
                        }
                        else if (chinhSuaLop(DanhSachLop, listviewDS.idItem[LuaChon], themMaLop.ToString(), themTenLop.ToString()))
                        {
                            ghiFileDSlop(DanhSachLop);
                            drawDSLop(DanhSachLop);
                            MenuThemLop = true;
                            setfillstyle(1, BLACK);
                            bar(1005, 0, 1600, 765);
                            themMaLop.content = "";
                            themTenLop.content = "";
                            Sleep(100);
                            drawThemLop();
                            break;
                        }
                    }
                    else if (btnThoat.isMouseHover())
                    {
                        MenuThemLop = true;
                        setfillstyle(1, BLACK);
                        bar(1005, 0, 1600, 765);
                        themMaLop.content = "";
                        themTenLop.content = "";
                        Sleep(100);
                        drawThemLop();
                        break;
                    }
                    else if (themMaLop.isMouseHover())
                    {
                        Edit = &themMaLop;
                    }
                    else if (themTenLop.isMouseHover())
                    {
                        Edit = &themTenLop;
                    }
                }
                Sleep(75);
            }
        }
        else if (GetAsyncKeyState(VK_LBUTTON) && LuaChon < listviewDS.size && curMenu == DISPLAY_DSLOP)
        {
            MenuThemLop = false;
            drawSinhVien(DanhSachLop.arrLop[listviewDS.idItem[LuaChon]].TENLOP);
            curMenu = DISPLAY_DSSV;
            drawThemSinhVien();
            listviewDS.click = true;
            drawList = true;
            int viTri = listviewDS.idItem[LuaChon];
            while (true)
            {
                KeyboardEvent();
                displaySinhVien(DanhSachLop, DanhSachLop.arrLop[viTri].dsSinhVien, DanhSachLop.arrLop[viTri].MALOP);
                if (btnQuaylai.click)
                {
                    btnQuaylai.click = false;
                    MenuThemLop = true;
                    drawThemLop();
                    break;
                }
                Sleep(100);
            }
        }

        else if (GetAsyncKeyState(VK_LBUTTON) && LuaChon < listviewDS.size && curMenu == LUACHON_LOP)
        {
            drawBangDiem(tenMon, DanhSachLop.arrLop[listviewDS.idItem[LuaChon]].TENLOP);
            drawDsDiem(maMon, DanhSachLop.arrLop[listviewDS.idItem[LuaChon]]);
            curMenu = DISPLAY_DSDIEMGV;
            luaChonLop = listviewDS.idItem[LuaChon];
            Edit = nullptr;
            Sleep(100);
        }
    }
    else
    {
        // Khoi phuc ITEAM
        if (PreLuaChon != -1 && PreLuaChon < listviewDS.size)
        {
            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
            setcolor(WHITE);
            setfillstyle(1, BLACK);
            setbkcolor(BLACK);
            bar(xDsLop[0] + 5, yDsLop[0] + 20 + PreLuaChon * 50 - 10, xDsLop[2] - 5, yDsLop[0] + 20 + PreLuaChon * 50 + 30);
            outtextxy(xDsLop[0] + 70, yDsLop[0] + 20 + PreLuaChon * 50, &DanhSachLop.arrLop[listviewDS.idItem[PreLuaChon]].MALOP[0]);
            outtextxy(xDsLop[1] + 70, yDsLop[0] + 20 + PreLuaChon * 50, &DanhSachLop.arrLop[listviewDS.idItem[PreLuaChon]].TENLOP[0]);
        }
        LuaChon = -1;
        PreLuaChon = -1;
        setlinestyle(0, 0, 2);
        setcolor(WHITE);
        line(350, 200, 350, 760);
    }
    return;
}

void DisplayLop(dslop &DanhSachLop)
{
    // Tim kiem theo nhap tu ban phim, xuat ra man hinh luon
    static int checkTimKiem = 0;
    if (drawList == true)
    {
        drawDSLop(DanhSachLop);
        drawList = false;
        if (checkTimKiem < 0)
        {
            checkTimKiem = 0;
        }
    }
    if (timKiemLop.content.size() > checkTimKiem)
    {
        checkTimKiem++;
        drawList = true;
    }
    else if (timKiemLop.content.size() == checkTimKiem)
    {
        drawList = false;
    }
    else if (timKiemLop.content.size() < checkTimKiem)
    {
        checkTimKiem -= 2;
        drawList = true;
    }

    // Bat su kien khi click ITEAM trong cai listView
    ClickItemLop(DanhSachLop);

    setfillstyle(1, LIGHTGRAY);
    btnQuaylai.ButtonEffect();
    btnLui.ButtonEffect();
    btnTien.ButtonEffect();
    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (btnQuaylai.isMouseHover())
        {
            curMenu = DISPLAY_GIAOVIEN;
            MenuThemLop = true;
            drawGV();
            Edit = nullptr;
            themMaLop.content = "";
            themTenLop.content = "";
            timKiemLop.content = "";
            soTrangLop = 1;
            drawList = true;
        }
        else if (timKiemLop.isMouseHover())
        {
            Edit = &timKiemLop;
        }
        else if (btnTien.isMouseHover())
        {
            drawList = true;
            btnTien.click = true;
            btnLui.click = false;
        }
        else if (btnLui.isMouseHover())
        {
            drawList = true;
            btnLui.click = true;
            btnTien.click = false;
        }
    }

    if (MenuThemLop)
    {
        btnThem.ButtonEffect();
        if (GetAsyncKeyState(VK_LBUTTON))
        {
            if (themMaLop.isMouseHover())
            {
                Edit = &themMaLop;
            }
            else if (themTenLop.isMouseHover())
            {
                Edit = &themTenLop;
            }

            else if (btnThem.isMouseHover())
            {

                if (themMaLop.content.size() == 0)
                {
                    AllocConsole();
                    MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Khong duoc de trong MA LOP!", "Thong bao", MB_ICONASTERISK | MB_OK);
                    Edit = &themMaLop;
                }
                else if (themTenLop.content.size() == 0)
                {
                    AllocConsole();
                    MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Khong duoc de trong TEN LOP!", "Thong bao", MB_ICONASTERISK | MB_OK);
                    Edit = &themTenLop;
                }
                else if (ThemDanhSachLop(DanhSachLop, themMaLop.ToString(), themTenLop.ToString()))
                {
                    ghiFileDSlop(DanhSachLop);
                    themTenLop.content = "";
                    themMaLop.content = "";
                    themMaLop.draw();
                    themTenLop.draw();
                    drawList = true;
                }
            }
        }
    }
}

//-------------------------------------------------- CHUC NANG SINH VIEN --------------------------------------------------

void ClickItemSinhVien(dslop DanhSachLop, listSV &danhSachSV, string maLop)
{
    int x = -1, y = -1;
    x = mousex();
    y = mousey();
    static int LuaChon = -1; // Thanh sang khi di chuot qua ITEAM
    static int PreLuaChon = -1;
    int soLuongSV = SizeListSV(danhSachSV);

    LuaChon = (y - yDsSV[0]) / 50;
    nodeSV *node = danhSachSV.First;
    nodeSV *PreNode = nullptr;

    if (x > xDsSV[0] && x < xDsSV[4] && y > yDsSV[0] && y < yDsSV[1])
    {
        // Khoi phuc ITEAM
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        if (PreLuaChon != -1 && PreLuaChon != LuaChon && PreLuaChon < listviewDS.size)
        {
            setcolor(WHITE);
            setfillstyle(1, BLACK);
            setbkcolor(BLACK);
            bar(0, yDsSV[0] + 20 + PreLuaChon * 50 - 10, xDsSV[0] - 5, yDsSV[0] + 20 + PreLuaChon * 50 + 30);
        }

        PreLuaChon = LuaChon;
        // Ve ITEAM hien tai
        if (PreLuaChon != -1 && LuaChon < listviewDS.size)
        {
            setcolor(LIGHTGREEN);
            setfillstyle(1, RED);
            setbkcolor(RED);
            readimagefile(troNgonTay, 0, yDsSV[0] + 20 + PreLuaChon * 50 - 10, xDsSV[0] - 5, yDsSV[0] + 20 + PreLuaChon * 50 + 30);
        }
        setlinestyle(0, 0, 2);
        setcolor(WHITE);
        line(250, 200, 250, 760);
        // Ve HO SV
        line(600, 200, 600, 760);
        // Ve TEN SV
        line(800, 200, 800, 760);
        // Bat su kien khi click vao ITEAM, khi click chuot trai hoac chuot phai
        if (GetAsyncKeyState(VK_RBUTTON) && LuaChon < listviewDS.size)
        {
            Sleep(20);
            node = danhSachSV.First;
            for (int i = 0; i < listviewDS.idItem[LuaChon]; i++)
            {
                if (node == nullptr)
                {
                    break;
                }
                PreNode = node;
                node = node->pNext;
            }

            edMSSV.content = node->info.mssv;
            edHoSV.content = node->info.Ho;
            edTenSV.content = node->info.Ten;
            if (node->info.gioiTinh == 0)
            {
                btnNam.click = true;
                btnNu.click = false;
            }
            else
            {
                btnNam.click = false;
                btnNu.click = true;
            }

            drawHieuChinhSV();
            while (node != nullptr)
            {
                KeyboardEvent();
                btnHieuChinh.ButtonEffect();
                btnXoaVinhVien.ButtonEffect();
                btnThoat.ButtonEffect();
                btnNam.ButtonEffect();
                btnNu.ButtonEffect();
                btnResetMK.ButtonEffect();
                GetAsyncKeyState(VK_RBUTTON); // Xoa bo nho dem chuot trai
                if (GetAsyncKeyState(VK_LBUTTON))
                {
                    if (btnXoaVinhVien.isMouseHover())
                    {
                        AllocConsole();
                        if (MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Ban chac chan muon xoa?", "Thong bao", MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
                        {
                            if (xoaSinhVien(danhSachSV, node))
                            {
                                setfillstyle(1, BLACK);
                                bar(1005, 0, 1600, 765);
                                drawList = true;
                                btnNam.click = false;
                                btnNu.click = false;
                                edMSSV.content = "";
                                edHoSV.content = "";
                                edTenSV.content = "";
                                drawThemSinhVien();
                                setfillstyle(1, BLACK);
                                bar(0, yDsSV[0], xDsSV[0] - 3, yDsSV[1]);
                                ghiFileDsSinhVien(danhSachSV, maLop);
                                break;
                            }
                        }
                    }
                    else if (btnHieuChinh.isMouseHover())
                    {
                        if (edMSSV.content.size() == 0)
                        {
                            AllocConsole();
                            MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Vui long nhap MSSV!", "Thong bao", MB_ICONEXCLAMATION | MB_OK);
                        }
                        else if (edHoSV.content.size() == 0)
                        {
                            AllocConsole();
                            MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Vui long nhap HO & TEN DEM!", "Thong bao", MB_ICONEXCLAMATION | MB_OK);
                        }
                        else if (edTenSV.content.size() == 0)
                        {
                            AllocConsole();
                            MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Vui long nhap TEN!", "Thong bao", MB_ICONEXCLAMATION | MB_OK);
                        }
                        else if (!btnNam.click && !btnNu.click)
                        {
                            AllocConsole();
                            MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Vui long lua chon GIOI TINH!", "Thong bao", MB_ICONEXCLAMATION | MB_OK);
                        }
                        else if (ChinhSuaSinhVien(DanhSachLop, danhSachSV, node, PreNode, edMSSV.ToString(), edHoSV.ToString(), edTenSV.ToString(), btnNam.click ? 0 : 1))
                        {
                            ghiFileDsSinhVien(danhSachSV, maLop);
                            AllocConsole();
                            MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Hieu chinh thanh cong", "Thong bao", MB_OK);
                            btnHieuChinh.click = true;
                            drawDsSinhVien(danhSachSV);
                            setfillstyle(1, BLACK);
                            bar(1005, 0, 1600, 765);
                            edMSSV.content = "";
                            edHoSV.content = "";
                            edTenSV.content = "";
                            btnNam.click = false;
                            btnNu.click = false;
                            Sleep(100);
                            drawThemSinhVien();
                            break;
                        }
                    }
                    else if (btnThoat.isMouseHover())
                    {
                        setfillstyle(1, BLACK);
                        bar(1005, 0, 1600, 765);
                        edMSSV.content = "";
                        edHoSV.content = "";
                        edTenSV.content = "";
                        btnNam.click = false;
                        btnNu.click = false;
                        Sleep(100);
                        drawThemSinhVien();
                        break;
                    }
                    else if (edMSSV.isMouseHover())
                    {
                        Edit = &edMSSV;
                    }
                    else if (edHoSV.isMouseHover())
                    {
                        Edit = &edHoSV;
                    }
                    else if (edTenSV.isMouseHover())
                    {
                        Edit = &edTenSV;
                    }
                    else if (btnNam.isMouseHover())
                    {
                        btnNam.click = true;
                        btnNu.click = false;
                        btnNam.draw();
                        btnNu.draw();
                    }
                    else if (btnNu.isMouseHover())
                    {
                        btnNam.click = false;
                        btnNu.click = true;
                        btnNam.draw();
                        btnNu.draw();
                    }
                    else if (btnResetMK.isMouseHover())
                    {
                        AllocConsole();
                        if (MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Chuc nang nay de cap lai MAT KHAU MAC DINH cho sinh vien. Ban muon tiep tuc?", "Thong bao", MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
                        {
                            thayDoiMK(node, "mk");
                            ghiFileDsSinhVien(danhSachSV, maLop);
                            MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Reset MAT KHAU thanh cong", "Thong bao", MB_OK);
                        }
                    }
                }
                Sleep(75);
            }
        }
    }
    else
    {
        // Khoi phuc ITEAM
        if (PreLuaChon != -1 && PreLuaChon < listviewDS.size)
        {
            settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
            setfillstyle(1, BLACK);
            setbkcolor(BLACK);
            setcolor(WHITE);
            setfillstyle(1, BLACK);
            setbkcolor(BLACK);
            bar(0, yDsDiemSV[0] + 20 + PreLuaChon * 50 - 10, xDsSV[0] - 5, yDsSV[0] + 20 + PreLuaChon * 50 + 30);
        }
        LuaChon = -1;
        PreLuaChon = -1;
        setlinestyle(0, 0, 2);
        setcolor(WHITE);
    }
}

void displaySinhVien(dslop DanhSachLop, listSV &danhSachSV, string maLop)
{
    static int checkTimKiem = 0;
    if (drawList == true)
    {
        drawDsSinhVien(danhSachSV);
        drawList = false;
        if (checkTimKiem < 0)
        {
            checkTimKiem = 0;
        }
    }
    if (edtimKiemSV.content.size() > checkTimKiem)
    {
        checkTimKiem++;
        drawList = true;
    }
    else if (edtimKiemSV.content.size() == checkTimKiem)
    {
        drawList = false;
    }
    else if (edtimKiemSV.content.size() < checkTimKiem)
    {
        checkTimKiem -= 2;
        drawList = true;
    }

    btnQuaylai.ButtonEffect();
    btnLui.ButtonEffect();
    btnTien.ButtonEffect();

    ClickItemSinhVien(DanhSachLop, danhSachSV, maLop);
    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (btnQuaylai.isMouseHover())
        {
            curMenu = DISPLAY_DSLOP;
            drawLop();
            Sleep(200);
            drawList = true;
            Edit = nullptr;
            edMSSV.content = "";
            edHoSV.content = "";
            edTenSV.content = "";
            edtimKiemSV.content = "";
            btnNam.click = false;
            btnNu.click = false;
            btnQuaylai.click = true;
            listviewDS.click = false;
        }
        else if (edtimKiemSV.isMouseHover())
        {
            Edit = &edtimKiemSV;
        }
        else if (btnTien.isMouseHover())
        {
            drawList = true;
            btnTien.click = true;
        }
        else if (btnLui.isMouseHover())
        {
            drawList = true;
            btnLui.click = true;
        }
    }

    btnNam.ButtonEffect();
    btnNu.ButtonEffect();
    btnThem.ButtonEffect();
    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (edMSSV.isMouseHover())
        {
            Edit = &edMSSV;
        }
        else if (edHoSV.isMouseHover())
        {
            Edit = &edHoSV;
        }
        else if (edTenSV.isMouseHover())
        {
            Edit = &edTenSV;
        }
        else if (btnNam.isMouseHover())
        {
            btnNam.click = true;
            btnNu.click = false;
            btnNam.draw();
            btnNu.draw();
        }
        else if (btnNu.isMouseHover())
        {
            btnNam.click = false;
            btnNu.click = true;
            btnNam.draw();
            btnNu.draw();
        }
        else if (btnThem.isMouseHover())
        {
            if (edMSSV.content.size() == 0)
            {
                AllocConsole();
                MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Vui long nhap MSSV!", "Thong bao", MB_ICONASTERISK | MB_OK);
            }
            else if (edHoSV.content.size() == 0)
            {
                AllocConsole();
                MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Vui long nhap HO & TEN DEM!", "Thong bao", MB_ICONASTERISK | MB_OK);
            }
            else if (edTenSV.content.size() == 0)
            {
                AllocConsole();
                MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Vui long nhap TEN!", "Thong bao", MB_ICONASTERISK | MB_OK);
            }
            else if (!btnNam.click && !btnNu.click)
            {
                AllocConsole();
                MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Vui long lua chon GIOI TINH!", "Thong bao", MB_ICONASTERISK | MB_OK);
            }
            else
            {
                sinhVien sv;
                sv.mssv = edMSSV.ToString();
                sv.Ho = edHoSV.ToString();
                sv.Ten = edTenSV.ToString();
                sv.gioiTinh = (btnNam.click ? 0 : 1);
                sv.Pass = "mk";
                sv.listDT.first = nullptr;
                if (InsertNodeSV(DanhSachLop, danhSachSV, sv))
                {
                    ghiFileDsSinhVien(danhSachSV, maLop);
                    edMSSV.content = "";
                    edHoSV.content = "";
                    edTenSV.content = "";
                    btnNam.click = false;
                    btnNu.click = false;
                    btnThem.click = true;
                    drawDsSinhVien(danhSachSV);
                    drawThemSinhVien();
                    Sleep(100);
                }
            }
        }
    }
}

//------------------------------------ CHON 1 MON HOAC 1 LOP KHI THUC HIEN CHUC NANG KHAC ------------------------------------

void displayLuaChonMon(ListMonHoc listMH)
{
    btnQuaylai.ButtonEffect();
    btnTien.ButtonEffect();
    btnLui.ButtonEffect();
    static int checkTimKiem = 0;
    if (drawList == true)
    {
        drawDSMonHoc(listMH);
        drawList = false;
        if (checkTimKiem < 0)
        {
            checkTimKiem = 0;
        }
    }
    if (timKiemMon.content.size() > checkTimKiem)
    {
        checkTimKiem++;
        drawList = true;
    }
    else if (timKiemMon.content.size() == checkTimKiem)
    {
        drawList = false;
    }
    else if (timKiemMon.content.size() < checkTimKiem)
    {
        checkTimKiem -= 2;
        drawList = true;
    }
    ClickItemMonHoc(nullptr, listMH);
    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (btnQuaylai.isMouseHover() && preMenu == CHUCNANG_CAUHOI)
        {
            Edit = nullptr;
            drawList = true;
            curMenu = CHUCNANG_CAUHOI;
            preMenu = -1;
            drawCauHoi();
            if (chucNangThemCauHoi)
            {
                drawThemCauHoi();
            }
            else
            {
                drawHieuChinhCauHoi(outtextTenMon);
            }
            soTrangMon = 1;
            Sleep(200);
        }
        else if (btnQuaylai.isMouseHover() && preMenu == DISPLAY_GIAOVIEN)
        {
            Edit = nullptr;
            drawList = true;
            curMenu = DISPLAY_GIAOVIEN;
            preMenu = -1;
            MenuThemMon = true;
            MenuThemLop = true;
            outtextTenMon = "";
            drawGV();
            soTrangMon = 1;
            timKiemMon.content = "";
        }
        else if (btnTien.isMouseHover())
        {
            drawList = true;
            btnTien.click = true;
        }
        else if (btnLui.isMouseHover())
        {
            drawList = true;
            btnLui.click = true;
        }
        else if (timKiemMon.isMouseHover())
        {
            Edit = &timKiemMon;
        }
    }
}

void displayLuaChonLop1(dslop &DanhSachLop, string maMon, string tenMon)
{
    // Tim kiem theo nhap tu ban phim, xuat ra man hinh luon
    static int checkTimKiem = 0;
    if (drawList == true)
    {
        drawDSLop(DanhSachLop);
        drawList = false;
        if (checkTimKiem < 0)
        {
            checkTimKiem = 0;
        }
    }
    if (timKiemLop.content.size() > checkTimKiem)
    {
        checkTimKiem++;
        drawList = true;
    }
    else if (timKiemLop.content.size() == checkTimKiem)
    {
        drawList = false;
    }
    else if (timKiemLop.content.size() < checkTimKiem)
    {
        checkTimKiem -= 2;
        drawList = true;
    }
    // Bat su kien khi click ITEAM trong cai listView
    ClickItemLop(DanhSachLop, maMon, tenMon);
    setfillstyle(1, LIGHTGRAY);
    btnQuaylai.ButtonEffect();
    btnLui.ButtonEffect();
    btnTien.ButtonEffect();
    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (btnQuaylai.isMouseHover())
        {
            curMenu = DISPLAY_DIEMMON;
            MenuThemLop = false;
            drawMonHoc();
            Edit = nullptr;

            timKiemLop.content = "";
            soTrangLop = 1;
            drawList = true;
            Sleep(200);
        }
        else if (timKiemLop.isMouseHover())
        {
            Edit = &timKiemLop;
        }
        else if (btnTien.isMouseHover())
        {
            drawList = true;
            btnTien.click = true;
            btnLui.click = false;
        }
        else if (btnLui.isMouseHover())
        {
            drawList = true;
            btnLui.click = true;
            btnTien.click = false;
        }
    }
}

void displayLuaChonLop2(dslop &DanhSachLop, ListMonHoc listMH)
{
    // Tim kiem theo nhap tu ban phim, xuat ra man hinh luon
    static int checkTimKiem = 0;
    if (drawList == true)
    {
        drawDSLop(DanhSachLop);
        drawList = false;
        if (checkTimKiem < 0)
        {
            checkTimKiem = 0;
        }
    }
    if (timKiemLop.content.size() > checkTimKiem)
    {
        checkTimKiem++;
        drawList = true;
    }
    else if (timKiemLop.content.size() == checkTimKiem)
    {
        drawList = false;
    }
    else if (timKiemLop.content.size() < checkTimKiem)
    {
        checkTimKiem -= 2;
        drawList = true;
    }
    // Bat su kien khi click ITEAM trong cai listView
    ClickItemChonLop(DanhSachLop, listMH);
    setfillstyle(1, LIGHTGRAY);
    btnQuaylai.ButtonEffect();
    btnLui.ButtonEffect();
    btnTien.ButtonEffect();
    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (btnQuaylai.isMouseHover())
        {
            curMenu = DISPLAY_GIAOVIEN;
            drawGV();
            Edit = nullptr;
            timKiemLop.content = "";
            soTrangLop = 1;
            drawList = true;
            Sleep(200);
        }
        else if (timKiemLop.isMouseHover())
        {
            Edit = &timKiemLop;
        }
        else if (btnTien.isMouseHover())
        {
            drawList = true;
            btnTien.click = true;
            btnLui.click = false;
        }
        else if (btnLui.isMouseHover())
        {
            drawList = true;
            btnLui.click = true;
            btnTien.click = false;
        }
    }
}

//------------------------------------------------ CHUC NANG XEM DIEM ------------------------------------------------

// Xem diem sinh vien ben chuc nang giang vien
void ClickItemDsDiemGV(listSV dsSinhVien, string maMon, string tenLop)
{
    int x = -1, y = -1;
    x = mousex();
    y = mousey();
    static int LuaChon = -1;
    static int PreLuaChon = -1;

    int soLuongSV = SizeListSV(dsSinhVien);
    LuaChon = (y - yDsDiem[0]) / 50;

    if (x > xDsDiem[0] && x < xDsDiem[4] && y > yDsDiem[0] && y < yDsDiem[1])
    {
        // Khoi phuc ITEAM
        if (PreLuaChon != -1 && PreLuaChon != LuaChon && PreLuaChon < listviewDS.size)
        {
            setfillstyle(1, BLACK);
            bar(220, yDsDiem[0] + 20 + PreLuaChon * 50 - 30, xDsDiem[0] - 5, yDsDiem[0] + 40 + PreLuaChon * 50 + 30);
        }

        PreLuaChon = LuaChon;
        // Ve ITEAM hien tai
        if (PreLuaChon != -1 && LuaChon < listviewDS.size)
        {
            setcolor(LIGHTGREEN);
            setbkcolor(RED);
            readimagefile(troNgonTay, 220, yDsDiem[0] + 20 + PreLuaChon * 50 - 30, xDsDiem[0] - 5, yDsDiem[0] + 40 + PreLuaChon * 50 + 30);
        }

        // Bat su kien khi o man hinh danh sach mon (Co the them & hieu chinh)
        if (GetAsyncKeyState(VK_LBUTTON) && LuaChon < listviewDS.size)
        {
            nodeSV *nodesv = dsSinhVien.First;
            Node_Diem_Thi *nodeDiem = nodesv->info.listDT.first;
            for (int i = 0; i < listviewDS.idItem[LuaChon]; i++)
            {
                if (nodesv == nullptr)
                {
                    break;
                }
                nodesv = nodesv->pNext;
                nodeDiem = nodesv->info.listDT.first;
            }

            if (nodesv != nullptr)
            {
                while (nodeDiem != nullptr)
                {

                    if (nodeDiem->info.MAMH == maMon)
                    {
                        break;
                    }
                    nodeDiem = nodeDiem->DTnext;
                }
            }

            if (nodeDiem == nullptr)
            {
                AllocConsole();
                MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Sinh vien chua thi mon hoc nay!", "Thong bao", MB_ICONEXCLAMATION | MB_OK);
            }
            else
            {
                cauHoiSo = 1;
                drawXemBaiThi(nodesv->info, nodeDiem->info, tenLop);
                drawXemLaiBaiLam(nodeDiem->info.baithi.arrCauHoi, nodeDiem->info.baithi.slcht);
            }

            while (nodeDiem != nullptr)
            {
                btnTien.ButtonEffect();
                btnLui.ButtonEffect();
                btnQuaylai.ButtonEffect();
                if (GetAsyncKeyState(VK_LBUTTON))
                {
                    if (btnTien.isMouseHover())
                    {
                        btnTien.click = true;
                        drawXemLaiBaiLam(nodeDiem->info.baithi.arrCauHoi, nodeDiem->info.baithi.slcht);
                    }
                    else if (btnLui.isMouseHover())
                    {
                        btnLui.click = true;
                        drawXemLaiBaiLam(nodeDiem->info.baithi.arrCauHoi, nodeDiem->info.baithi.slcht);
                    }
                    else if (btnQuaylai.isMouseHover())
                    {
                        btnQuaylai.click = true;
                        Sleep(100);
                        break;
                    }
                }
                Sleep(75);
            }
        }
    }
    else
    {
        if (PreLuaChon != -1 && PreLuaChon < listviewDS.size)
        {
            setcolor(WHITE);
            setfillstyle(1, BLACK);
            setbkcolor(BLACK);
            bar(220, yDsDiem[0] + 20 + PreLuaChon * 50 - 30, xDsDiem[0] - 5, yDsDiem[0] + 40 + PreLuaChon * 50 + 30);
        }
        LuaChon = -1;
        PreLuaChon = -1;
        setcolor(WHITE);
    }
}

void diplayDsDiem(string maMon, lop lh)
{
    btnQuaylai.ButtonEffect();
    btnTien_L1.ButtonEffect();
    btnLui_L.ButtonEffect();

    static int checkTimKiem = 0;
    if (drawList == true)
    {
        drawDsDiem(maMon, lh);
        drawList = false;
        if (checkTimKiem < 0)
        {
            checkTimKiem = 0;
        }
    }
    if (edtimKiemSV_R.content.size() > checkTimKiem)
    {
        checkTimKiem++;
        drawList = true;
    }
    else if (edtimKiemSV_R.content.size() == checkTimKiem)
    {
        drawList = false;
    }
    else if (edtimKiemSV_R.content.size() < checkTimKiem)
    {
        checkTimKiem -= 2;
        drawList = true;
    }

    ClickItemDsDiemGV(lh.dsSinhVien, maMon, lh.MALOP);
    if (btnQuaylai.click)
    {
        btnQuaylai.click = false;
        drawBangDiem(outtextTenMon, lh.TENLOP);
        drawDsDiem(maMon, lh);
    }

    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (btnQuaylai.isMouseHover())
        {
            curMenu = LUACHON_LOP;
            drawLop();
            drawList = true;
            soTrangSV = 1;
            edtimKiemSV_R.content = "";
            luaChonLop = -1;
            Edit = nullptr;
            Sleep(200);
        }
        else if (btnTien_L1.isMouseHover())
        {
            drawList = true;
            btnTien_L1.click = true;
        }
        else if (btnLui_L.isMouseHover())
        {
            drawList = true;
            btnLui_L.click = true;
        }
        else if (edtimKiemSV_R.isMouseHover())
        {
            Edit = &edtimKiemSV_R;
        }
    }
}

//------------------------------------------------- TUY CHINH CAU HOI THI -------------------------------------------------

bool kiemTraNhapCauHoi()
{
    if (!edCauHoi.content.size())
    {
        AllocConsole();
        MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "NOI DUNG khong duoc de trong!", "Thong bao", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    else if (!edDapAnA.content.size())
    {
        AllocConsole();
        MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "DAP AN A khong duoc de trong!", "Thong bao", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    else if (!edDapAnB.content.size())
    {
        AllocConsole();
        MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "DAP AN B khong duoc de trong!", "Thong bao", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    else if (!edDapAnC.content.size())
    {
        AllocConsole();
        MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "DAP AN C khong duoc de trong!", "Thong bao", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    else if (!edDapAnD.content.size())
    {
        AllocConsole();
        MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "DAP AN D khong duoc de trong!", "Thong bao", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    else if (!btnDapAnA.click && !btnDapAnB.click && !btnDapAnC.click && !btnDapAnD.click)
    {
        AllocConsole();
        MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Vui long chon 1 DAP AN DUNG!", "Thong bao", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    else if (!edChonMaMon.content.size())
    {
        AllocConsole();
        MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "MA MON khong duoc de trong!", "Thong bao", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    return true;
}

void batSKnhapCauHoi()
{
    if (edCauHoi.isMouseHover())
    {
        Edit = &edCauHoi;
    }
    else if (edDapAnA.isMouseHover())
    {
        Edit = &edDapAnA;
    }
    else if (edDapAnB.isMouseHover())
    {
        Edit = &edDapAnB;
    }
    else if (edDapAnC.isMouseHover())
    {
        Edit = &edDapAnC;
    }
    else if (edDapAnD.isMouseHover())
    {
        Edit = &edDapAnD;
    }
    else if (btnDapAnA.isMouseHover())
    {
        btnDapAnA.click = true;
        btnDapAnB.click = false;
        btnDapAnC.click = false;
        btnDapAnD.click = false;
        btnDapAnA.draw();
        btnDapAnB.draw();
        btnDapAnC.draw();
        btnDapAnD.draw();
    }
    else if (btnDapAnB.isMouseHover())
    {
        btnDapAnA.click = false;
        btnDapAnB.click = true;
        btnDapAnC.click = false;
        btnDapAnD.click = false;
        btnDapAnA.draw();
        btnDapAnB.draw();
        btnDapAnC.draw();
        btnDapAnD.draw();
    }
    else if (btnDapAnC.isMouseHover())
    {
        btnDapAnA.click = false;
        btnDapAnB.click = false;
        btnDapAnC.click = true;
        btnDapAnD.click = false;
        btnDapAnA.draw();
        btnDapAnB.draw();
        btnDapAnC.draw();
        btnDapAnD.draw();
    }
    else if (btnDapAnD.isMouseHover())
    {
        btnDapAnA.click = false;
        btnDapAnB.click = false;
        btnDapAnC.click = false;
        btnDapAnD.click = true;
        btnDapAnA.draw();
        btnDapAnB.draw();
        btnDapAnC.draw();
        btnDapAnD.draw();
    }
    else if (btnChonMaMon.isMouseHover())
    {
        Edit = nullptr;
        preMenu = curMenu;
        curMenu = LUACHON_MON;
        soTrangMon = 1;
        drawList = true;
        drawMonHoc();
    }
}

void ClickItemCauHoi(NodeCauHoi *&root, ListMonHoc listMH, IDRandom *&listID)
{
    int x = -1, y = -1;
    x = mousex();
    y = mousey();
    static int LuaChon = -1;
    static int PreLuaChon = -1;

    int soLuongCauHoi = countNodeCauHoi(root);
    LuaChon = (y - yDsCauHoi[0]) / 50;

    if (x > xDsCauHoi[0] && x < xDsCauHoi[3] && y > yDsCauHoi[0] && y < yDsCauHoi[1])
    {
        // Khoi phuc ITEAM
        if (PreLuaChon != -1 && PreLuaChon != LuaChon && PreLuaChon < listviewDS.size)
        {
            setfillstyle(1, BLACK);
            bar(0, yDsCauHoi[0] + 20 + PreLuaChon * 50 - 10, xDsCauHoi[0] - 5, yDsCauHoi[0] + 20 + PreLuaChon * 50 + 30);
        }

        PreLuaChon = LuaChon;
        // Ve ITEAM hien tai
        if (PreLuaChon != -1 && LuaChon < listviewDS.size)
        {
            setcolor(LIGHTGREEN);
            setbkcolor(RED);
            readimagefile(troNgonTay, 0, yDsCauHoi[0] + 20 + PreLuaChon * 50 - 10, xDsCauHoi[0] - 5, yDsCauHoi[0] + 20 + PreLuaChon * 50 + 30);
        }

        // Bat su kien khi o man hinh danh sach mon (Co the them & hieu chinh)
        if (GetAsyncKeyState(VK_RBUTTON) && LuaChon < listviewDS.size)
        {
            Sleep(20);
            NodeCauHoi *node = Tim_Kiem_Key(root, listviewDS.idItem[LuaChon]);
            chucNangThemCauHoi = false;

            if (node->info.DapAn == 'A')
            {
                btnDapAnA.click = true;
                btnDapAnB.click = false;
                btnDapAnC.click = false;
                btnDapAnD.click = false;
            }
            else if (node->info.DapAn == 'B')
            {
                btnDapAnA.click = false;
                btnDapAnB.click = true;
                btnDapAnC.click = false;
                btnDapAnD.click = false;
            }
            else if (node->info.DapAn == 'C')
            {
                btnDapAnA.click = false;
                btnDapAnB.click = false;
                btnDapAnC.click = true;
                btnDapAnD.click = false;
            }
            else if (node->info.DapAn == 'D')
            {
                btnDapAnA.click = false;
                btnDapAnB.click = false;
                btnDapAnC.click = false;
                btnDapAnD.click = true;
            }
            edCauHoi.content = node->info.NoiDung;
            edDapAnA.content = node->info.A;
            edDapAnB.content = node->info.B;
            edDapAnC.content = node->info.C;
            edDapAnD.content = node->info.D;
            edChonMaMon.content = node->info.maMonHoc;

            drawHieuChinhCauHoi(Truy_Xuat_Ten_Mon(listMH, node->info.maMonHoc));

            while (!chucNangThemCauHoi)
            {
                Sleep(100);
                if (curMenu == LUACHON_MON)
                {
                    displayLuaChonMon(listMH);
                }
                else
                {
                    if (drawList)
                    {
                        drawDsCauHoi(root);
                        drawList = false;
                    }
                    btnHieuChinhCauHoi.ButtonEffect();
                    btnXoaCauHoi.ButtonEffect();
                    btnThoatHieuChinhCH.ButtonEffect();
                    btnChonMaMon.ButtonEffect();
                    KeyboardEvent();
                    if (GetAsyncKeyState(VK_LBUTTON))
                    {
                        batSKnhapCauHoi();
                        if (btnHieuChinhCauHoi.isMouseHover() && kiemTraNhapCauHoi())
                        {
                            CauHoi cauHoiHieuChinh;
                            cauHoiHieuChinh.NoiDung = edCauHoi.ToString();
                            cauHoiHieuChinh.A = edDapAnA.ToString();
                            cauHoiHieuChinh.B = edDapAnB.ToString();
                            cauHoiHieuChinh.C = edDapAnC.ToString();
                            cauHoiHieuChinh.D = edDapAnD.ToString();
                            if (btnDapAnA.click)
                            {
                                cauHoiHieuChinh.DapAn = 'A';
                            }
                            else if (btnDapAnB.click)
                            {
                                cauHoiHieuChinh.DapAn = 'B';
                            }
                            else if (btnDapAnC.click)
                            {
                                cauHoiHieuChinh.DapAn = 'C';
                            }
                            else if (btnDapAnD.click)
                            {
                                cauHoiHieuChinh.DapAn = 'D';
                            }
                            cauHoiHieuChinh.maMonHoc = edChonMaMon.ToString();

                            if (Hieu_Chinh_Cau_Hoi(root, listviewDS.idItem[LuaChon], cauHoiHieuChinh))
                            {
                                Luu_File_Cau_Hoi(root);
                                drawList = true;
                                chucNangThemCauHoi = true;
                                btnDapAnA.click = false;
                                btnDapAnB.click = false;
                                btnDapAnC.click = false;
                                btnDapAnD.click = false;
                                edDapAnA.content = "";
                                edCauHoi.content = "";
                                edDapAnB.content = "";
                                edDapAnC.content = "";
                                edDapAnD.content = "";
                                edChonMaMon.content = "";
                                Edit = nullptr;
                                drawThemCauHoi();
                            }
                        }
                        else if (btnXoaCauHoi.isMouseHover())
                        {
                            AllocConsole();
                            if (MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Ban co chac chan muon xoa?", "Thong bao", MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
                            {
                                NodeCauHoi *xoaNode = Tim_Kiem_Key(root, listviewDS.idItem[LuaChon]);
                                if (xoaNode->info.used)
                                {
                                    AllocConsole();
                                    MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Cau hoi da duoc su dung thi. Khong the xoa!", "Thong bao", MB_ICONWARNING | MB_OK);
                                }
                                else
                                {

                                    root = Xoa_Cau_Hoi(root, listviewDS.idItem[LuaChon]);
                                    Xoa_ID(listID, listviewDS.idItem[LuaChon]);
                                    Luu_File_Cau_Hoi(root);
                                    AllocConsole();
                                    MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Xoa thanh cong", "Thong bao", MB_OK);
                                    setfillstyle(1, BLACK);
                                    bar(0, yDsCauHoi[0] + 20 + PreLuaChon * 50 - 10, xDsCauHoi[0] - 5, yDsCauHoi[0] + 20 + PreLuaChon * 50 + 30);
                                    drawList = true;
                                    chucNangThemCauHoi = true;
                                    btnDapAnA.click = false;
                                    btnDapAnB.click = false;
                                    btnDapAnC.click = false;
                                    btnDapAnD.click = false;
                                    edDapAnA.content = "";
                                    edCauHoi.content = "";
                                    edDapAnB.content = "";
                                    edDapAnC.content = "";
                                    edDapAnD.content = "";
                                    edChonMaMon.content = "";
                                    Edit = nullptr;
                                    drawThemCauHoi();
                                    break;
                                }
                            }
                        }
                        else if (btnThoatHieuChinhCH.isMouseHover())
                        {
                            setfillstyle(1, BLACK);
                            bar(850, 20, 1070, 70);
                            chucNangThemCauHoi = true;
                            btnDapAnA.click = false;
                            btnDapAnB.click = false;
                            btnDapAnC.click = false;
                            btnDapAnD.click = false;
                            edDapAnA.content = "";
                            edCauHoi.content = "";
                            edDapAnB.content = "";
                            edDapAnC.content = "";
                            edDapAnD.content = "";
                            edChonMaMon.content = "";
                            Edit = nullptr;
                            drawThemCauHoi();
                            break;
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (PreLuaChon != -1 && PreLuaChon < listviewDS.size)
        {
            setcolor(WHITE);
            setfillstyle(1, BLACK);
            setbkcolor(BLACK);
            bar(0, yDsCauHoi[0] + 20 + PreLuaChon * 50 - 10, xDsCauHoi[0] - 5, yDsCauHoi[0] + 20 + PreLuaChon * 50 + 30);
        }
        LuaChon = -1;
        PreLuaChon = -1;
        setcolor(WHITE);
    }
}

void displayChucNangCauHoi(NodeCauHoi *&rootCauHoi, IDRandom *&listID, ListMonHoc listMH)
{

    static int checkTimKiem = 0;
    if (drawList == true)
    {
        drawDsCauHoi(rootCauHoi);
        drawList = false;
        if (checkTimKiem < 0)
        {
            checkTimKiem = 0;
        }
    }
    if (timKiemCauHoi.content.size() > checkTimKiem)
    {
        checkTimKiem++;
        drawList = true;
    }
    else if (timKiemCauHoi.content.size() == checkTimKiem)
    {
        drawList = false;
    }
    else if (timKiemCauHoi.content.size() < checkTimKiem)
    {
        checkTimKiem -= 2;
        drawList = true;
    }

    btnQuaylai.ButtonEffect();
    btnTien_L.ButtonEffect();
    btnLui.ButtonEffect();
    btnDapAnA.ButtonEffect();
    btnDapAnB.ButtonEffect();
    btnDapAnC.ButtonEffect();
    btnDapAnD.ButtonEffect();
    btnChonMaMon.ButtonEffect();

    ClickItemCauHoi(rootCauHoi, listMH, listID);

    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (btnQuaylai.isMouseHover())
        {
            curMenu = DISPLAY_GIAOVIEN;
            drawList = true;
            btnDapAnA.click = false;
            btnDapAnB.click = false;
            btnDapAnC.click = false;
            btnDapAnD.click = false;
            timKiemCauHoi.content = "";
            edDapAnA.content = "";
            edCauHoi.content = "";
            edDapAnB.content = "";
            edDapAnC.content = "";
            edDapAnD.content = "";
            edChonMaMon.content = "";
            MenuThemMon = true;
            soTrangMon = 1;
            soTrangCauHoi = 1;
            outtextTenMon = "";
            drawGV();
            Sleep(100);
        }
        else if (timKiemCauHoi.isMouseHover())
        {
            Edit = &timKiemCauHoi;
        }
        else if (btnTien_L.isMouseHover())
        {
            drawList = true;
            btnTien.click = true;
            btnLui.click = false;
        }
        else if (btnLui.isMouseHover())
        {
            drawList = true;
            btnTien.click = false;
            btnLui.click = true;
        }
        batSKnhapCauHoi();
    }

    if (chucNangThemCauHoi == true)
    {
        btnThemCauHoi.ButtonEffect();
        if (GetAsyncKeyState(VK_LBUTTON) && btnThemCauHoi.isMouseHover() && kiemTraNhapCauHoi())
        {

            int id = Cap_ID(listID);
            CauHoi cauHoiMoi;
            cauHoiMoi.id = id;
            cauHoiMoi.NoiDung = edCauHoi.ToString();
            cauHoiMoi.A = edDapAnA.ToString();
            cauHoiMoi.B = edDapAnB.ToString();
            cauHoiMoi.C = edDapAnC.ToString();
            cauHoiMoi.D = edDapAnD.ToString();
            cauHoiMoi.maMonHoc = edChonMaMon.ToString();
            if (btnDapAnA.click == true)
            {
                cauHoiMoi.DapAn = 'A';
            }
            else if (btnDapAnB.click == true)
            {
                cauHoiMoi.DapAn = 'B';
            }
            else if (btnDapAnC.click == true)
            {
                cauHoiMoi.DapAn = 'C';
            }
            else if (btnDapAnD.click == true)
            {
                cauHoiMoi.DapAn = 'D';
            }

            if (!KiemTra_TrungDapAn(cauHoiMoi.A, cauHoiMoi.B, cauHoiMoi.C, cauHoiMoi.D) && !KiemTra_TrungNoiDung(rootCauHoi, id, cauHoiMoi.NoiDung) && id != 0)
            {
                rootCauHoi = Them_Cau_Hoi_Moi(rootCauHoi, id, cauHoiMoi);
                Luu_File_Cau_Hoi(rootCauHoi);
                AllocConsole();
                MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Them thanh cong", "Thong bao", MB_OK);
                btnDapAnA.click = false;
                btnDapAnB.click = false;
                btnDapAnC.click = false;
                btnDapAnD.click = false;
                outtextTenMon = "";
                edDapAnA.content = "";
                edCauHoi.content = "";
                edDapAnB.content = "";
                edDapAnC.content = "";
                edDapAnD.content = "";
                edCauHoi.content = "";
                edChonMaMon.content = "";
                drawThemCauHoi();
                drawList = true;
            }
            else if (id == 0)
            {
                AllocConsole();
                MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Khong the them cau hoi, ID da day!", "Thong bao", MB_ICONASTERISK | MB_OK);
            }
        }
    }
}

//--------------------------------------------------- CAI DAT CHUC NANG THI ---------------------------------------------------

void displayThietLapThiThu(ListMonHoc listMH, NodeCauHoi *rootCayCauHoi, mangCauHoi &arrCauHoi, Diem_Thi &gvThiThu)
{
    btnQuaylai.ButtonEffect();
    btnTien.ButtonEffect();
    btnLui.ButtonEffect();
    btnVaoThi.ButtonEffect();
    btnXemBaiThiThu.ButtonEffect();
    // Tim kiem theo nhap tu ban phim, xuat ra man hinh luon
    static int checkTimKiem = 0;
    if (drawList == true)
    {
        drawDSMonHoc(listMH);
        drawList = false;
        if (checkTimKiem < 0)
        {
            checkTimKiem = 0;
        }
    }
    if (timKiemMon.content.size() > checkTimKiem)
    {
        checkTimKiem++;
        drawList = true;
    }
    else if (timKiemMon.content.size() == checkTimKiem)
    {
        drawList = false;
    }
    else if (timKiemMon.content.size() < checkTimKiem)
    {
        checkTimKiem -= 2;
        drawList = true;
    }

    ClickItemMonHoc(rootCayCauHoi, listMH);
    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (btnQuaylai.isMouseHover())
        {
            curMenu = DISPLAY_GIAOVIEN;
            drawGV();
            drawList = true;
            Edit = nullptr;
            edChonMonThi.content = "";
            edTimeThi.content = "";
            edsoCau.content = "";
            timKiemMon.content = "";
            outtextTenMon = "";
            soTrangMon = 1;
            Sleep(100);
        }
        else if (timKiemMon.isMouseHover())
        {
            Edit = &timKiemMon;
        }
        else if (edTimeThi.isMouseHover())
        {
            Edit = &edTimeThi;
        }
        else if (edsoCau.isMouseHover())
        {
            Edit = &edsoCau;
        }
        else if (btnTien.isMouseHover())
        {
            drawList = true;
            btnTien.click = true;
        }
        else if (btnLui.isMouseHover())
        {
            drawList = true;
            btnLui.click = true;
        }
        else if (btnXemBaiThiThu.isMouseHover())
        {
            if (gvThiThu.MAMH.size())
            {
                drawXemBaiThiThu(gvThiThu, Truy_Xuat_Ten_Mon(listMH, gvThiThu.MAMH));
                drawXemLaiBaiLam(gvThiThu.baithi.arrCauHoi, gvThiThu.baithi.slcht);
                curMenu = XEMBAI_THUTHU;
            }
            else
            {
                AllocConsole();
                MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Khong co bai thi thu!", "Thong bao", MB_ICONEXCLAMATION | MB_OK);
            }
        }
        else if (btnVaoThi.isMouseHover())
        {
            int soLuongCauHoi = 0;
            if (edChonMonThi.content.size() && edTimeThi.content.size() && edsoCau.content.size())
            {
                demSoCauTheoMaMon(rootCayCauHoi, edChonMonThi.ToString(), soLuongCauHoi);
                arrCauHoi.arrCauHoiThi = new NodeCauHoi *[soLuongCauHoi];
                taoMangCauHoi(rootCayCauHoi, arrCauHoi, edChonMonThi.ToString());
            }

            if (edChonMonThi.content.size() == 0)
            {
                AllocConsole();
                MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Vui long chon 1 mon!", "Thong bao", MB_ICONINFORMATION | MB_OK);
            }
            else if (edTimeThi.content.size() == 0)
            {
                AllocConsole();
                MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Vui long thiet lap thoi gian thi!", "Thong bao", MB_ICONINFORMATION | MB_OK);
            }
            else if (edsoCau.content.size() == 0)
            {
                AllocConsole();
                MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Vui long thiet lap so cau thi!", "Thong bao", MB_ICONINFORMATION | MB_OK);
            }
            else if (taoBaiThiThu(gvThiThu, arrCauHoi, edsoCau.toInt()))
            {
                curMenu = VAO_THITHU;
                gvThiThu.MAMH = edChonMonThi.ToString();
                int giay = edTimeThi.toInt() * 60;
                drawThi();
                drawBaiLam(gvThiThu.baithi.arrCauHoi);
                Edit = nullptr;
                Sleep(100);
                timer = thread(drawThoiGian, giay);
            }
        }
    }
}

void displayThiThu(Diem_Thi &gvThiThu)
{
    rdChonA.RadioEffect();
    rdChonB.RadioEffect();
    rdChonC.RadioEffect();
    rdChonD.RadioEffect();
    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (rdChonA.isMouseHover())
        {
            gvThiThu.baithi.arrCauHoi[cauHoiSo - 1].luaChon = 'A';
            rdChonA.click = true;
            rdChonB.click = false;
            rdChonC.click = false;
            rdChonD.click = false;

            rdChonA.drawEffect();
            rdChonB.drawEffect();
            rdChonC.drawEffect();
            rdChonD.drawEffect();
        }
        else if (rdChonB.isMouseHover())
        {
            gvThiThu.baithi.arrCauHoi[cauHoiSo - 1].luaChon = 'B';
            rdChonA.click = false;
            rdChonB.click = true;
            rdChonC.click = false;
            rdChonD.click = false;

            rdChonA.drawEffect();
            rdChonB.drawEffect();
            rdChonC.drawEffect();
            rdChonD.drawEffect();
        }
        else if (rdChonC.isMouseHover())
        {
            gvThiThu.baithi.arrCauHoi[cauHoiSo - 1].luaChon = 'C';
            rdChonA.click = false;
            rdChonB.click = false;
            rdChonC.click = true;
            rdChonD.click = false;

            rdChonA.drawEffect();
            rdChonB.drawEffect();
            rdChonC.drawEffect();
            rdChonD.drawEffect();
        }
        else if (rdChonD.isMouseHover())
        {
            gvThiThu.baithi.arrCauHoi[cauHoiSo - 1].luaChon = 'D';
            rdChonA.click = false;
            rdChonB.click = false;
            rdChonC.click = false;
            rdChonD.click = true;

            rdChonA.drawEffect();
            rdChonB.drawEffect();
            rdChonC.drawEffect();
            rdChonD.drawEffect();
        }
        else if (btnTien.isMouseHover())
        {
            btnTien.click = true;
            drawBaiLam(gvThiThu.baithi.arrCauHoi);
        }
        else if (btnLui.isMouseHover())
        {
            btnLui.click = true;
            drawBaiLam(gvThiThu.baithi.arrCauHoi);
        }
        else if (btnNopBai.isMouseHover())
        {
            AllocConsole();
            if (MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Thoi gian van con! Ban co chac muon nop bai?", "Thong bao", MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
            {
                btnNopBai.click = true;
            }
        }
    }
}

void displayXemBaiThiThu(Diem_Thi gvThiThu)
{
    btnTien.ButtonEffect();
    btnLui.ButtonEffect();
    btnQuaylai.ButtonEffect();
    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (btnTien.isMouseHover())
        {
            btnTien.click = true;
            drawXemLaiBaiLam(gvThiThu.baithi.arrCauHoi, gvThiThu.baithi.slcht);
        }
        else if (btnLui.isMouseHover())
        {
            btnLui.click = true;
            drawXemLaiBaiLam(gvThiThu.baithi.arrCauHoi, gvThiThu.baithi.slcht);
        }
        else if (btnQuaylai.isMouseHover())
        {
            outtextTenMon = "";
            cauHoiSo = 1;
            drawList = true;
            curMenu = DISPLAY_GIAOVIEN;
            drawGV();
        }
    }
}