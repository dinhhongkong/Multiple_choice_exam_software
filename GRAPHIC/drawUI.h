void drawThemLop();
// Ve giao dien LOGIN
void drawLogin()
{
    cleardevice();
    taiKhoan.content = "";
    matKhau.content = "";
    settextstyle(BOLD_FONT, 0, 7);
    setcolor(YELLOW);
    string nameApp = "PHAN MEM THI TRAC NGHIEM";
    outtextxy((w - textwidth(&nameApp[0])) / 2, 150, &nameApp[0]);
    taiKhoan.draw();
    matKhau.draw();
    dangnhap.draw();
    taiKhoan.setNext(&matKhau);
    matKhau.setPre(&taiKhoan);
    taiKhoan.setPre(&matKhau);
    matKhau.setNext(&taiKhoan);
}

// Ve giao dien chuc nang sinh vien
void drawHocSinh(string HO = "", string TEN = "", string MSSV = "", int GIOITINH = 0, string tenlop = "")
{
    cleardevice();
    btnThi.draw();
    btnXemDiemSV.draw();
    btnDoiMK.draw();
    btndangxuat.draw();
    setlinestyle(0, 0, 3);
    setcolor(YELLOW);
    rectangle(325, 200, 1275, 700);
    line(325, 325, 1275, 325);
    setfillstyle(WIDE_DOT_FILL, CYAN);
    bar(325, 200, 1275, 325);
    setcolor(YELLOW);
    settextstyle(0, 0, 5);
    outtextxy(430, 240, "THONG TIN SINH VIEN");

    static string hoTen;
    static string mssv;
    static string tenLop;
    string temp = (GIOITINH) ? ("NU") : ("NAM");
    static string gioiTinh;

    if (HO.size())
    {
        hoTen = "Ho va Ten: " + HO + " " + TEN;
        mssv = "MSSV: " + MSSV;
        gioiTinh = "Gioi tinh: " + temp;
    }
    if (tenlop.size())
    {
        tenLop = "Lop: " + tenlop;
    }
    settextstyle(10, 0, 4);
    setcolor(RED);
    setbkcolor(BLACK);
    outtextxy(430, 400, &hoTen[0]);
    outtextxy(430, 475, &mssv[0]);
    outtextxy(430, 550, &tenLop[0]);
    outtextxy(430, 625, &gioiTinh[0]);
}

int trangDiemSV = 1;
void drawDsDiemSV(Danh_Sach_Diem_Thi listDT, ListMonHoc listMH)
{
    setfillstyle(1, BLACK);
    int soLuong = 0;
    Node_Diem_Thi *nodeDiem = listDT.first;
    while (nodeDiem != nullptr)
    {
        soLuong++;
        nodeDiem = nodeDiem->DTnext;
    }
    listviewDS.size = 0;
    setbkcolor(BLACK);

    if (soLuong <= 10)
    {
        trangDiemSV = 1;
    }
    else if (btnTien_L1.click && soLuong > trangDiemSV * 10)
    {
        trangDiemSV++;
    }
    else if (btnLui_L.click && trangDiemSV > 1)
    {
        trangDiemSV--;
    }

    btnTien_L1.click = false;
    btnLui_L.click = false;

    string textTrang = to_string(trangDiemSV);

    textTrang += "/" + to_string((soLuong % 10 == 0) ? ((soLuong < 10) ? 1 : soLuong / 10) : (soLuong / 10 + 1));
    // thu nghiem xoa so trang:   setfillstyle(4, YELLOW);
    bar(760, 825, 850, 850);
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(w / 2 + textwidth(&textTrang[0]) - 20, 825, &textTrang[0]);
    nodeDiem = listDT.first;
    if (nodeDiem != nullptr)
    {
        nodeDiem = listDT.first;
        if (trangDiemSV > 1)
        {
            for (int i = 0; i < (trangDiemSV - 1) * 10; i++)
            {
                nodeDiem = nodeDiem->DTnext;
            }
        }

        bar(xDsDiemSV[0] + 1, yDsDiemSV[0] + 1, xDsDiemSV[1] - 1, 760 - 1);
        bar(xDsDiemSV[1] + 1, yDsDiemSV[0] + 1, xDsDiemSV[2] - 1, 760 - 1);
        bar(xDsDiemSV[2] + 1, yDsDiemSV[0] + 1, xDsDiemSV[3] - 1, 760 - 1);
        listviewDS.size = 0;

        for (int i = 0; i < 10; i++)
        {

            if (i + (trangDiemSV - 1) * 10 >= soLuong || nodeDiem == nullptr)
            {
                break;
            }
            listviewDS.size++;
            listviewDS.idItem[i] = i + (trangDiemSV - 1) * 10;
            string diem = "";
            string tenMon;

            outtextxy(xDsDiemSV[0] + 40, yDsDiemSV[0] + 20 + i * 50, &nodeDiem->info.MAMH[0]);
            tenMon = Truy_Xuat_Ten_Mon(listMH, nodeDiem->info.MAMH);
            outtextxy(xDsDiemSV[1] + 40, yDsDiemSV[0] + 20 + i * 50, &tenMon[0]);
            diem = to_string(nodeDiem->info.Diem);
            xoaSoThapPhan(diem);
            outtextxy(xDsDiemSV[2] + 60, yDsDiemSV[0] + 20 + i * 50, &diem[0]);
            nodeDiem = nodeDiem->DTnext;
        }
    }
}

void drawDiemSV()
{
    setbkcolor(BLACK);
    cleardevice();
    settextstyle(BOLD_FONT, 0, 8);
    setcolor(YELLOW);
    outtextxy(w / 2 - textwidth("DANH SACH DIEM CAC MON") / 2, 35, "DANH SACH DIEM CAC MON");
    settextstyle(BOLD_FONT, 0, 3);
    btnQuaylai.draw();
    btnLui_L.draw();
    btnTien_L1.draw();
    setcolor(LIGHTGREEN);
    rectangle(350, 200, 1250, 760);
    // Ve MA MON
    line(600, 200, 600, 760);
    // Ve TEN MON
    line(1100, 200, 1100, 760);
    // Ve gach ngang
    line(350, 250, 1250, 250);
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(xDsDiem[0] + 80, 215, "MA MON");
    outtextxy(xDsDiem[1] + 255, 215, "TEN MON");
    outtextxy(xDsDiem[3] + 50, 215, "DIEM");
}

void drawDoiMk()
{
    setbkcolor(BLACK);
    setfillstyle(1, BLACK);
    cleardevice();
    setfillstyle(WIDE_DOT_FILL, CYAN);
    bar(325, 100, 1275, 230);
    line(325, 230, 1275, 230);
    rectangle(325, 100, 1275, 700);
    setcolor(YELLOW);
    settextstyle(0, 0, 5);
    outtextxy(800 - textwidth("DOI MAT KHAU") / 2 + 20, 150, "DOI MAT KHAU");
    matKhauCu.draw();
    matKhauMoi.draw();
    nhapLaiMatKhau.draw();
    btnQuaylai.draw();
    btnDoiMKMoi.draw();

    matKhauCu.setNext(&matKhauMoi);
    matKhauMoi.setNext(&nhapLaiMatKhau);
    nhapLaiMatKhau.setNext(&matKhauCu);

    matKhauCu.setPre(&nhapLaiMatKhau);
    matKhauMoi.setPre(&matKhauCu);
    nhapLaiMatKhau.setPre(&matKhauMoi);
}

// Ve giao dien chuc nang giang vien
void drawGV()
{
    cleardevice();
    setcolor(YELLOW);
    settextstyle(BOLD_FONT, 0, 7);
    outtextxy((w - textwidth("QUAN TRI VIEN HE THONG THI")) / 2, 100, "QUAN TRI VIEN HE THONG THI");
    btnMonHoc.draw();
    btnDsLop.draw();
    btnDiemThi.draw();
    btnCauHoiThi.draw();
    btnThiThu.draw();
    btnDangXuat.draw();
    readimagefile(iconChuotTrai, 50, 820, 100, 870);
    outtextxy(120, 835, "CHON THAO TAC");
    readimagefile(iconChuotPhai, 100 + textwidth("CHON THAO TAC") + 50, 820, 100 + textwidth("CHON THAO TAC") + 100, 870);
    outtextxy(100 + textwidth("CHON THAO TAC") + 120, 835, "CHON CHUC NANG");
}

//---------------------------------------------------- CHUC NANG MON HOC ------------------------------------------------------
void DrawThemMonHoc()
{
    setfillstyle(1, BLACK);
    bar(1005, 0, 1600, 765);
    setfillstyle(WIDE_DOT_FILL, CYAN);
    bar(1050, 200, 1550, 300);
    setcolor(YELLOW);
    rectangle(1050, 200, 1550, 700);
    settextstyle(0, 0, 3);
    outtextxy(1170, 230, "THEM MON HOC");
    line(1050, 300, 1550, 300);

    line(1050, 600, 1550, 600);
    btnThem.draw();
    themMaMon.draw();
    themTenMon.draw();

    themMaMon.setNext(&themTenMon);
    themTenMon.setNext(&themMaMon);
    themMaMon.setPre(&themTenMon);
    themTenMon.setPre(&themMaMon);
}

void drawMonHoc()
{
    cleardevice();
    if (MenuThemMon == true)
    {
        DrawThemMonHoc();
    }
    settextstyle(BOLD_FONT, 0, 7);
    setcolor(YELLOW);
    if (curMenu == DISPLAY_DSMON)
    {
        outtextxy(200, 20, "DANH SACH MON HOC");
    }
    else
    {
        outtextxy(200, 20, "VUI LONG CHON 1 MON");
    }
    btnQuaylai.draw();
    timKiemMon.draw();
    btnLui.draw();
    btnTien.draw();
    line(1000, 0, 1000, 900);
    line(300, 200, 300, 760);
    rectangle(50, 200, 950, 760);
    // ve gach ngang
    line(50, 250, 950, 250);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(xDsMon[0] + 85, 210, "MA MON");
    outtextxy(550, 210, "TEN MON HOC");
}

int soTrangMon = 1;
void drawDSMonHoc(ListMonHoc listMH)
{
    setfillstyle(1, BLACK);
    bar(xDsMon[0] + 2, yDsMon[0] + 2, xDsMon[1] - 2, 760 - 2);
    bar(xDsMon[1] + 2, yDsMon[0] + 2, xDsMon[2] - 2, 760 - 2);
    if (listMH.slmh <= 10)
    {
        soTrangMon = 1;
    }
    else if (btnTien.click && listMH.slmh > soTrangMon * 10 && timKiemMon.content.size() == 0)
    {
        soTrangMon++;
        btnTien.click = false;
    }
    else if (btnLui.click && soTrangMon > 1 && timKiemMon.content.size() == 0)
    {
        soTrangMon--;
    }
    btnTien.click = false;
    btnLui.click = false;
    string textTrang = to_string(soTrangMon);
    textTrang += "/" + to_string((listMH.slmh % 10 == 0) ? ((listMH.slmh < 10) ? 1 : listMH.slmh / 10) : (listMH.slmh / 10 + 1));
    // thu nghiem xoa so trang:   setfillstyle(4, YELLOW);
    bar(425, 825, 500, 850);
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    listviewDS.size = 0;
    setcolor(WHITE);
    setbkcolor(BLACK);

    if (timKiemMon.content.size() == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            if (i + (soTrangMon - 1) * 10 >= listMH.slmh)
            {
                break;
            }
            listviewDS.size++;
            listviewDS.idItem[i] = i + (soTrangMon - 1) * 10;

            outtextxy(xDsMon[0] + 40, yDsMon[0] + 20 + i * 50, &listMH.monHoc[i + (soTrangMon - 1) * 10]->MAMH[0]);
            outtextxy(xDsMon[1] + 40, yDsMon[0] + 20 + i * 50, &listMH.monHoc[i + (soTrangMon - 1) * 10]->TENMH[0]);
        }
        outtextxy(450, 825, &textTrang[0]);
    }
    else
    {
        int j = 0;
        for (int i = 0; i < listMH.slmh; i++)
        {
            if (j >= 10)
            {
                break;
            }
            if (FIND(listMH.monHoc[i]->MAMH, timKiemMon.ToSearch()) || FIND(listMH.monHoc[i]->TENMH, timKiemMon.ToSearch()))
            {
                listviewDS.size++;
                listviewDS.idItem[j] = i;

                outtextxy(xDsMon[0] + 40, yDsMon[0] + 20 + j * 50, &listMH.monHoc[i]->MAMH[0]);
                outtextxy(xDsMon[1] + 40, yDsMon[0] + 20 + j * 50, &listMH.monHoc[i]->TENMH[0]);
                j++;
            }
        }
    }
}

void drawHieuChinhMonHoc()
{
    setfillstyle(1, BLACK);
    bar(1005, 0, 1600, 765); // 75 tai y neu thay menu
    setfillstyle(WIDE_DOT_FILL, CYAN);
    bar(1050, 200, 1550, 300);
    setcolor(YELLOW);
    rectangle(1050, 200, 1550, 700);
    settextstyle(0, 0, 3);
    outtextxy(1080, 230, "HIEU CHINH MON HOC");
    line(1050, 300, 1550, 300);
    line(1050, 600, 1550, 600);
    themMaMon.draw();
    themTenMon.draw();
    btnHieuChinh.draw();
    btnXoaVinhVien.draw();
    btnThoat.draw();
}

//---------------------------------------------------- CHUC NANG LOP HOC ------------------------------------------------------
void drawLop()
{
    setbkcolor(BLACK);
    cleardevice();
    if (MenuThemLop == true)
    {
        drawThemLop();
    }
    // THU NGHIEM SET MAU BACKGROUND
    settextstyle(BOLD_FONT, 0, 7);
    setcolor(YELLOW);
    if (curMenu == DISPLAY_DSLOP)
    {
        outtextxy(250, 20, "DANH SACH LOP HOC");
    }
    else
    {
        outtextxy(200, 20, "VUI LONG CHON 1 LOP");
    }
    btnQuaylai.draw();
    btnLui.draw();
    btnTien.draw();
    timKiemLop.draw();
    line(1000, 0, 1000, 900);

    rectangle(50, 200, 950, 760);
    // Ve MA LOP
    line(350, 200, 350, 760);
    // Ve gach ngang
    line(50, 250, 950, 250);
    outtextxy(xDsLop[0] + 110, 215, "MA LOP");
    outtextxy(xDsLop[1] + 235, 215, "TEN LOP");
}

void drawThemLop()
{
    MenuThemLop = true;
    setfillstyle(1, BLACK);
    bar(1005, 75, 1600, 765);
    setfillstyle(WIDE_DOT_FILL, CYAN);
    bar(1050, 200, 1550, 300);
    setcolor(YELLOW);
    rectangle(1050, 200, 1550, 700);
    settextstyle(0, 0, 3);

    outtextxy(1170, 230, "THEM LOP HOC");
    line(1050, 300, 1550, 300);
    line(1050, 600, 1550, 600);
    btnThem.draw();
    themMaLop.draw();
    themTenLop.draw();

    themMaLop.setNext(&themTenLop);
    themTenLop.setNext(&themMaLop);
    themMaLop.setPre(&themTenLop);
    themTenLop.setPre(&themMaLop);
}

int soTrangLop = 1;
void drawDSLop(dslop DanhSachLop)
{
    setfillstyle(1, BLACK);
    bar(xDsLop[0] + 1, yDsLop[0] + 1, xDsLop[1] - 1, 760 - 1);
    bar(xDsLop[1] + 1, yDsLop[0] + 1, 950 - 1, 760 - 1);

    if (DanhSachLop.solop <= 10)
    {
        soTrangLop = 1;
    }
    else if (btnTien.click && DanhSachLop.solop > soTrangLop * 10 && timKiemLop.content.size() == 0)
    {
        soTrangLop++;
        btnTien.click = false;
    }
    else if (btnLui.click && soTrangLop > 1 && timKiemLop.content.size() == 0)
    {
        soTrangLop--;
    }
    btnTien.click = false;
    btnLui.click = false;
    setbkcolor(BLACK);
    string textTrang = to_string(soTrangLop);
    textTrang += "/" + to_string((DanhSachLop.solop % 10 == 0) ? ((DanhSachLop.solop < 10) ? 1 : DanhSachLop.solop / 10) : (DanhSachLop.solop / 10 + 1));
    // thu nghiem xoa so trang:   setfillstyle(4, YELLOW);
    bar(425, 825, 500, 850);
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    listviewDS.size = 0;

    if (timKiemLop.content.size() == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            if (i + (soTrangLop - 1) * 10 >= DanhSachLop.solop)
            {
                break;
            }
            listviewDS.size++;
            listviewDS.idItem[i] = i + (soTrangLop - 1) * 10;

            outtextxy(xDsLop[0] + 70, yDsLop[0] + 20 + i * 50, &DanhSachLop.arrLop[i + (soTrangLop - 1) * 10].MALOP[0]);
            outtextxy(xDsLop[1] + 70, yDsLop[0] + 20 + i * 50, &DanhSachLop.arrLop[i + (soTrangLop - 1) * 10].TENLOP[0]);
        }
        outtextxy(450, 825, &textTrang[0]);
    }
    else
    {
        int j = 0;
        for (int i = 0; i < DanhSachLop.solop; i++)
        {
            if (j >= 10)
            {
                break;
            }
            if (FIND(DanhSachLop.arrLop[i].MALOP, timKiemLop.ToSearch()) || FIND(DanhSachLop.arrLop[i].TENLOP, timKiemLop.ToSearch()))
            {
                listviewDS.size++;
                listviewDS.idItem[j] = i;

                outtextxy(xDsLop[0] + 70, yDsLop[0] + 20 + j * 50, &DanhSachLop.arrLop[i].MALOP[0]);
                outtextxy(xDsLop[1] + 70, yDsLop[0] + 20 + j * 50, &DanhSachLop.arrLop[i].TENLOP[0]);
                j++;
            }
        }
    }
}

void drawHieuChinhLop()
{
    setfillstyle(1, BLACK);
    bar(1005, 0, 1600, 765);
    setfillstyle(WIDE_DOT_FILL, CYAN);
    bar(1050, 200, 1550, 300);
    setcolor(YELLOW);
    rectangle(1050, 200, 1550, 700);
    settextstyle(0, 0, 3);
    outtextxy(1080, 230, "HIEU CHINH LOP HOC");
    line(1050, 300, 1550, 300);
    line(1050, 600, 1550, 600);
    themMaLop.draw();
    themTenLop.draw();
    btnHieuChinh.draw();
    btnXoaVinhVien.draw();
    btnThoat.draw();
}

///--------------------------------------------------- CHUC NANG SINH VIEN ----------------------------------------------------
void drawSinhVien(string tenlop)
{
    setbkcolor(BLACK);
    cleardevice();
    settextstyle(BOLD_FONT, 0, 5);
    setcolor(YELLOW);
    outtextxy(250, 20, "DANH SACH SINH VIEN");
    settextstyle(BOLD_FONT, 0, 3);
    string TenDeMuc = "Lop: " + tenlop;
    outtextxy(250, 65, &TenDeMuc[0]);
    btnQuaylai.draw();
    edtimKiemSV.draw();
    // MenuThemSV = true;
    btnLui.draw();
    btnTien.draw();
    line(1000, 0, 1000, 900);
    rectangle(50, 200, 950, 760);
    // ve ma sv
    line(250, 200, 250, 760);
    // ve ho sv
    line(600, 200, 600, 760);
    // ve ten sv
    line(800, 200, 800, 760);
    // ve gach ngang
    line(50, 250, 950, 250);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(xDsSV[0] + 75, 215, "MSSV");
    outtextxy(xDsSV[1] + 165, 215, "HO");
    outtextxy(xDsSV[2] + 80, 215, "TEN");
    outtextxy(xDsSV[3] + 35, 215, "GIOI TINH");
}

void drawThemSinhVien()
{
    setfillstyle(1, BLACK);
    bar(1005, 75, 1600, 765);
    setfillstyle(WIDE_DOT_FILL, CYAN);
    bar(1050, 200, 1550, 300);
    setcolor(YELLOW);
    rectangle(1050, 200, 1550, 700);
    settextstyle(0, 0, 3);

    outtextxy(1140, 230, "THEM SINH VIEN");
    line(1050, 300, 1550, 300);
    line(1050, 600, 1550, 600);
    btnThem.draw();
    edMSSV.draw();
    edHoSV.draw();
    edTenSV.draw();
    setcolor(13);
    outtextxy(1075, 550, "Gioi tinh:");
    btnNam.draw();
    btnNu.draw();

    edMSSV.setNext(&edHoSV);
    edMSSV.setPre(&edTenSV);

    edHoSV.setNext(&edTenSV);
    edHoSV.setPre(&edMSSV);

    edTenSV.setNext(&edMSSV);
    edTenSV.setPre(&edHoSV);
}

int soTrangSV = 1;
void drawDsSinhVien(listSV danhSachSV)
{
    setfillstyle(1, BLACK);
    int soLuongSV = SizeListSV(danhSachSV);
    if (danhSachSV.First == nullptr)
    {
        bar(xDsSV[0] + 1, yDsSV[0] + 1, xDsSV[1] - 1, 760 - 1);
        bar(xDsSV[1] + 1, yDsSV[0] + 1, xDsSV[2] - 1, 760 - 1);
        bar(xDsSV[2] + 1, yDsSV[0] + 1, xDsSV[3] - 1, 760 - 1);
        bar(xDsSV[3] + 1, yDsSV[0] + 1, xDsSV[4] - 1, 760 - 1);
        listviewDS.size = 0;
        return;
    }

    nodeSV *node = nullptr;

    if (listviewDS.click || btnThem.click || btnHieuChinh.click || btnXoaVinhVien.click || edtimKiemSV.isChoose == false || (edtimKiemSV.isChoose == true && edtimKiemSV.content.size() == 0))
    {
        node = danhSachSV.First;
        listviewDS.click = false;
        listviewDS.size = 0;
        btnHieuChinh.click = false;
        btnXoaVinhVien.click = false;
        btnThem.click = false;
        soTrangSV = 1;
    }
    setbkcolor(BLACK);

    if (soLuongSV <= 10)
    {
        soTrangSV = 1;
    }
    else if (btnTien.click && soLuongSV > soTrangSV * 10 && edtimKiemSV.content.size() == 0 && node != nullptr)
    {
        soTrangSV++;
    }
    else if (btnLui.click && edtimKiemSV.content.size() == 0)
    {
        if (soTrangSV > 1)
        {
            soTrangSV--;
        }
    }

    btnTien.click = false;
    btnLui.click = false;

    string textTrang = to_string(soTrangSV);

    textTrang += "/" + to_string((soLuongSV % 10 == 0) ? ((soLuongSV < 10) ? 1 : soLuongSV / 10) : (soLuongSV / 10 + 1));
    // thu nghiem xoa so trang:   setfillstyle(4, YELLOW);
    bar(425, 825, 500, 850);
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);

    if (edtimKiemSV.content.size() == 0)
    {
        outtextxy(450, 825, &textTrang[0]);
    }

    if (edtimKiemSV.content.size() == 0 && node != nullptr)
    {
        node = danhSachSV.First;
        if (soTrangSV > 1)
        {
            for (int i = 0; i < (soTrangSV - 1) * 10; i++)
            {
                node = node->pNext;
            }
        }
        bar(xDsSV[0] + 1, yDsSV[0] + 1, xDsSV[1] - 1, 760 - 1);
        bar(xDsSV[1] + 1, yDsSV[0] + 1, xDsSV[2] - 1, 760 - 1);
        bar(xDsSV[2] + 1, yDsSV[0] + 1, xDsSV[3] - 1, 760 - 1);
        bar(xDsSV[3] + 1, yDsSV[0] + 1, xDsSV[4] - 1, 760 - 1);
        listviewDS.size = 0;
        for (int i = 0; i < 10; i++)
        {
            if (i + (soTrangSV - 1) * 10 >= soLuongSV || node == nullptr)
            {
                break;
            }

            listviewDS.size++;
            listviewDS.idItem[i] = i + (soTrangSV - 1) * 10;

            outtextxy(xDsSV[0] + 40, yDsSV[0] + 20 + i * 50, &node->info.mssv[0]);
            outtextxy(xDsSV[1] + 45, yDsSV[0] + 20 + i * 50, &node->info.Ho[0]);
            outtextxy(xDsSV[2] + 45, yDsSV[0] + 20 + i * 50, &node->info.Ten[0]);
            if (node->info.gioiTinh == 0)
            {
                outtextxy(xDsSV[3] + 40, yDsSV[0] + 20 + i * 50, "NAM");
            }
            else
            {
                outtextxy(xDsSV[3] + 40, yDsSV[0] + 20 + i * 50, "NU");
            }
            node = node->pNext;
        }
    }
    else if (edtimKiemSV.ToSearch().size())
    {
        listviewDS.size = 0;
        int j = 0, i = 0;
        node = danhSachSV.First;
        bar(xDsSV[0] + 1, yDsSV[0] + 1, xDsSV[1] - 1, 760 - 1);
        bar(xDsSV[1] + 1, yDsLop[0] + 1, xDsSV[2] - 1, 760 - 1);
        bar(xDsSV[2] + 1, yDsLop[0] + 1, xDsSV[3] - 1, 760 - 1);
        bar(xDsSV[3] + 1, yDsLop[0] + 1, xDsSV[4] - 1, 760 - 1);
        while (node != nullptr)
        {

            if (j >= 10)
            {
                break;
            }
            string HoTen = node->info.Ho + " " + node->info.Ten;
            if (FIND(node->info.mssv, edtimKiemSV.ToSearch()) || FIND(HoTen, edtimKiemSV.ToSearch()))
            {
                listviewDS.size++;
                listviewDS.idItem[j] = i;

                outtextxy(xDsSV[0] + 40, yDsSV[0] + 20 + j * 50, &node->info.mssv[0]);
                outtextxy(xDsSV[1] + 45, yDsSV[0] + 20 + j * 50, &node->info.Ho[0]);
                outtextxy(xDsSV[2] + 45, yDsSV[0] + 20 + j * 50, &node->info.Ten[0]);
                if (node->info.gioiTinh == 0)
                {
                    outtextxy(xDsSV[3] + 40, yDsSV[0] + 20 + j * 50, "NAM");
                }
                else
                {
                    outtextxy(xDsSV[3] + 40, yDsSV[0] + 20 + j * 50, "NU");
                }
                j++;
            }
            i++;
            node = node->pNext;
        }
    }
}

void drawHieuChinhSV()
{
    setfillstyle(1, BLACK);
    bar(1005, 0, 1600, 765);
    setfillstyle(WIDE_DOT_FILL, CYAN);
    bar(1050, 200, 1550, 300);
    setcolor(YELLOW);
    rectangle(1050, 200, 1550, 700);
    settextstyle(0, 0, 3);
    outtextxy(1060, 230, "HIEU CHINH SINH VIEN");
    line(1050, 300, 1550, 300);
    line(1050, 600, 1550, 600);
    edMSSV.draw();
    edHoSV.draw();
    edTenSV.draw();
    btnHieuChinh.draw();
    btnXoaVinhVien.draw();
    btnThoat.draw();
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setcolor(13);
    outtextxy(1075, 550, "Gioi tinh:");
    btnNam.draw();
    btnNu.draw();
    btnResetMK.draw();
}

//------------------------------------------------ GIAO DIEN IN BANG DIEM --------------------------------------------------

void drawChonXemDiem()
{
    HWND hWnd = FindWindowA(NULL, "Xem Diem");
    HMENU hMenu = GetSystemMenu(hWnd, false);
    DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    settextstyle(10, 0, 4);
    setcolor(YELLOW);
    setfillstyle(WIDE_DOT_FILL, CYAN);
    bar(50, 120, 550, 200);
    rectangle(50, 120, 550, 450);
    line(50, 200, 550, 200);
    outtextxy(300 - textwidth("CHON CHUC NANG XEM DIEM") / 2, 145, "CHON CHUC NANG XEM DIEM");
    btnDiemSV.draw();
    btnDiemLop.draw();
    btnQuaylai.draw();
}

// dung cho gv
void drawDsDiem(string maMon, lop lh)
{
    setfillstyle(1, BLACK);
    int soLuongSV = SizeListSV(lh.dsSinhVien);

    nodeSV *node = nullptr;

    if (listviewDS.click || edtimKiemSV_R.isChoose == false || (edtimKiemSV_R.isChoose == true && edtimKiemSV_R.content.size() == 0))
    {
        node = lh.dsSinhVien.First;
        listviewDS.size = 0;
        soTrangSV = 1;
    }
    setbkcolor(BLACK);

    if (soLuongSV <= 10)
    {
        soTrangSV = 1;
    }
    else if (btnTien_L1.click && soLuongSV > soTrangSV * 10 && edtimKiemSV_R.content.size() == 0 && node != nullptr)
    {
        soTrangSV++;
    }
    else if (btnLui_L.click && edtimKiemSV_R.content.size() == 0)
    {
        if (soTrangSV > 1)
        {
            soTrangSV--;
        }
    }

    btnTien_L1.click = false;
    btnLui_L.click = false;

    string textTrang = to_string(soTrangSV);

    textTrang += "/" + to_string((soLuongSV % 10 == 0) ? ((soLuongSV < 10) ? 1 : soLuongSV / 10) : (soLuongSV / 10 + 1));
    // thu nghiem xoa so trang:   setfillstyle(4, YELLOW);
    bar(725, 825, 800, 850);
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);

    if (edtimKiemSV_R.content.size() == 0)
    {
        outtextxy(750, 825, &textTrang[0]);
    }

    if (edtimKiemSV_R.content.size() == 0 && node != nullptr)
    {
        node = lh.dsSinhVien.First;
        if (soTrangSV > 1)
        {
            for (int i = 0; i < (soTrangSV - 1) * 10; i++)
            {
                node = node->pNext;
            }
        }
        bar(xDsDiem[0] + 1, yDsSV[0] + 1, xDsDiem[1] - 1, 760 - 1);
        bar(xDsDiem[1] + 1, yDsSV[0] + 1, xDsDiem[2] - 1, 760 - 1);
        bar(xDsDiem[2] + 1, yDsSV[0] + 1, xDsDiem[3] - 1, 760 - 1);
        bar(xDsDiem[3] + 1, yDsSV[0] + 1, xDsDiem[4] - 1, 760 - 1);
        listviewDS.size = 0;
        for (int i = 0; i < 10; i++)
        {
            if (i + (soTrangSV - 1) * 10 >= soLuongSV || node == nullptr)
            {
                break;
            }
            listviewDS.size++;
            listviewDS.idItem[i] = i + (soTrangSV - 1) * 10;

            outtextxy(xDsDiem[0] + 40, yDsSV[0] + 20 + i * 50, &node->info.mssv[0]);
            outtextxy(xDsDiem[1] + 45, yDsSV[0] + 20 + i * 50, &node->info.Ho[0]);
            outtextxy(xDsDiem[2] + 45, yDsSV[0] + 20 + i * 50, &node->info.Ten[0]);

            string diem = "";
            bool check = false;
            for (Node_Diem_Thi *p = node->info.listDT.first; p != nullptr; p = p->DTnext)
            {
                if (p->info.MAMH == maMon)
                {
                    diem = to_string(p->info.Diem);
                    xoaSoThapPhan(diem);
                    outtextxy(xDsDiem[3] + 30, yDsSV[0] + 20 + i * 50, &diem[0]);
                    check = true;
                    break;
                }
            }
            if (check == false)
            {
                outtextxy(xDsDiem[3] + 30, yDsSV[0] + 20 + i * 50, "CHUA THI");
            }
            node = node->pNext;
        }
    }
    else if (edtimKiemSV_R.ToSearch().size())
    {
        listviewDS.size = 0;
        int j = 0, i = 0;
        node = lh.dsSinhVien.First;
        bar(xDsDiem[0] + 1, yDsSV[0] + 1, xDsDiem[1] - 1, 760 - 1);
        bar(xDsDiem[1] + 1, yDsSV[0] + 1, xDsDiem[2] - 1, 760 - 1);
        bar(xDsDiem[2] + 1, yDsSV[0] + 1, xDsDiem[3] - 1, 760 - 1);
        bar(xDsDiem[3] + 1, yDsSV[0] + 1, xDsDiem[4] - 1, 760 - 1);
        while (node != nullptr)
        {

            if (j >= 10)
            {
                break;
            }
            string HoTen = node->info.Ho + " " + node->info.Ten;
            if (FIND(node->info.mssv, edtimKiemSV_R.ToSearch()) || FIND(HoTen, edtimKiemSV_R.ToSearch()))
            {
                listviewDS.size++;
                listviewDS.idItem[j] = i;

                outtextxy(xDsDiem[0] + 40, yDsSV[0] + 20 + j * 50, &node->info.mssv[0]);
                outtextxy(xDsDiem[1] + 45, yDsSV[0] + 20 + j * 50, &node->info.Ho[0]);
                outtextxy(xDsDiem[2] + 45, yDsSV[0] + 20 + j * 50, &node->info.Ten[0]);

                string diem = "";
                bool check = false;
                for (Node_Diem_Thi *p = node->info.listDT.first; p != nullptr; p = p->DTnext)
                {
                    check = false;
                    if (p->info.MAMH == maMon)
                    {
                        diem = to_string(p->info.Diem);
                        xoaSoThapPhan(diem);
                        outtextxy(xDsDiem[3] + 30, yDsSV[0] + 20 + j * 50, &diem[0]);
                        check = true;
                        break;
                    }
                }
                if (check == false)
                {
                    outtextxy(xDsDiem[3] + 30, yDsSV[0] + 20 + j * 50, "CHUA THI");
                }

                j++;
            }
            i++;
            node = node->pNext;
        }
    }
}

void drawBangDiem(string tenMon, string tenlop)
{
    setbkcolor(BLACK);
    cleardevice();
    settextstyle(BOLD_FONT, 0, 6);
    setcolor(YELLOW);
    outtextxy(450, 20, "DANH SACH DIEM SINH VIEN");
    settextstyle(BOLD_FONT, 0, 3);
    string TenDeMuc = "Lop: " + tenlop + "          Mon: " + tenMon;
    outtextxy(w / 2 - textwidth(&TenDeMuc[0]) / 2, 65, &TenDeMuc[0]);
    btnQuaylai.draw();
    edtimKiemSV_R.draw();
    btnLui_L.draw();
    btnTien_L1.draw();
    rectangle(350, 200, 1250, 760);
    // ve ma sv
    line(550, 200, 550, 760);
    // ve ho sv
    line(900, 200, 900, 760);
    // ve ten sv
    line(1100, 200, 1100, 760);
    // ve gach ngang
    line(350, 250, 1250, 250);

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(xDsDiem[0] + 75, 215, "MSSV");
    outtextxy(xDsDiem[1] + 165, 215, "HO");
    outtextxy(xDsDiem[2] + 80, 215, "TEN");
    outtextxy(xDsDiem[3] + 50, 215, "DIEM");
}

//---------------------------------------------- GIAO DIEN SUA & XOA CAU HOI ------------------------------------------------
void drawXemCauHoi()
{
    setfillstyle(1, BLACK);
    bar(849, 75, 1600, 761);
    setfillstyle(WIDE_DOT_FILL, CYAN);
    bar(850, 200, 1550, 300);
    rectangle(850, 200, 1550, 760);
    line(850, 300, 1550, 300);
    line(850, 650, 1550, 650);
    settextstyle(0, 0, 3);
    setcolor(YELLOW);
    outtextxy(1080, 230, "XEM CAU HOI");

    edCauHoi.draw();
    edDapAnA.draw();
    edDapAnB.draw();
    edDapAnC.draw();
    edDapAnD.draw();
    setcolor(TEXT_EDIITEXT_TITLE_COLOR);

    outtextxy(860, 600, "DAP AN DUNG: ");
    btnDapAnA.draw();
    btnDapAnB.draw();
    btnDapAnC.draw();
    btnDapAnD.draw();
}

int soTrangCauHoi = 1;
void outTextCauHoi(NodeCauHoi *rootCauHoi, int &i, int &j)
{
    if (rootCauHoi != nullptr)
    {
        if (j >= (soTrangCauHoi - 1) * 10 && j < (soTrangCauHoi)*10)
        {
            listviewDS.idItem[i] = rootCauHoi->key;
            listviewDS.size++;
            string Key = to_string(rootCauHoi->key);
            outtextxy(xDsCauHoi[0] + 15, yDsCauHoi[0] + 20 + i * 50, &Key[0]);
            if (rootCauHoi->info.maMonHoc.size() > 8)
            {
                string temp = rootCauHoi->info.maMonHoc.substr(0, 5) + "...";
                outtextxy(xDsCauHoi[1] + 25, yDsCauHoi[0] + 20 + i * 50, &temp[0]);
            }
            else
            {
                outtextxy(xDsCauHoi[1] + 25, yDsCauHoi[0] + 20 + i * 50, &rootCauHoi->info.maMonHoc[0]);
            }

            outtextxy(xDsCauHoi[2] + 10, yDsCauHoi[0] + 20 + i * 50, &rootCauHoi->info.NoiDung[0]);
            i++;
        }
        else if (j == (soTrangCauHoi)*10)
        {
            return;
        }
        j++;

        outTextCauHoi(rootCauHoi->left, i, j);
        outTextCauHoi(rootCauHoi->right, i, j);
    }
}

void outTextTimKiemCauHoi(NodeCauHoi *rootCauHoi, int &i)
{
    if (i == 10)
    {
        return;
    }

    // duyet LNR
    if (rootCauHoi != nullptr)
    {
        if (rootCauHoi->info.id == timKiemCauHoi.toInt() || FIND(rootCauHoi->info.NoiDung, timKiemCauHoi.ToSearch()))
        {
            listviewDS.idItem[i] = rootCauHoi->key;
            listviewDS.size++;
            string Key = to_string(rootCauHoi->key);
            outtextxy(xDsCauHoi[0] + 15, yDsCauHoi[0] + 20 + i * 50, &Key[0]);
            outtextxy(xDsCauHoi[1] + 25, yDsCauHoi[0] + 20 + i * 50, &rootCauHoi->info.maMonHoc[0]);
            outtextxy(xDsCauHoi[2] + 10, yDsCauHoi[0] + 20 + i * 50, &rootCauHoi->info.NoiDung[0]);
            i++;
        }

        outTextTimKiemCauHoi(rootCauHoi->left, i);
        outTextTimKiemCauHoi(rootCauHoi->right, i);
    }
}

void drawDsCauHoi(NodeCauHoi *rootCauHoi)
{
    setfillstyle(1, BLACK);
    bar(xDsCauHoi[0] + 1, yDsCauHoi[0] + 1, xDsCauHoi[1] - 1, 760 - 1);
    bar(xDsCauHoi[1] + 1, yDsCauHoi[0] + 1, xDsCauHoi[2] - 1, 760 - 1);
    bar(xDsCauHoi[2] + 1, yDsCauHoi[0] + 1, xDsCauHoi[3] - 1, 760 - 1);

    int soLuongCauHoi = countNodeCauHoi(rootCauHoi);

    if (soLuongCauHoi <= 10)
    {
        soTrangCauHoi = 1;
    }
    else if (btnTien.click && soLuongCauHoi > soTrangCauHoi * 10 && timKiemCauHoi.content.size() == 0)
    {
        soTrangCauHoi++;
        btnTien.click = false;
    }
    else if (btnLui.click && soTrangCauHoi > 1 && timKiemCauHoi.content.size() == 0)
    {
        soTrangCauHoi--;
    }
    btnTien.click = false;
    btnLui.click = false;
    setbkcolor(BLACK);
    string textTrang = to_string(soTrangCauHoi);
    textTrang += "/" + to_string((soLuongCauHoi % 10 == 0) ? ((soLuongCauHoi < 10) ? 1 : soLuongCauHoi / 10) : (soLuongCauHoi / 10 + 1));
    // thu nghiem xoa so trang:   setfillstyle(4, YELLOW);
    bar(425, 825, 500, 850);
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    listviewDS.size = 0;

    if (timKiemCauHoi.content.size() == 0)
    {
        int i = 0, j = 0;
        outTextCauHoi(rootCauHoi, i, j);
        outtextxy(400, 825, &textTrang[0]);
    }
    else if (timKiemCauHoi.content.size())
    {
        int i = 0;
        outTextTimKiemCauHoi(rootCauHoi, i);
    }
}

void drawThemCauHoi()
{
    setfillstyle(1, BLACK);
    bar(849, 0, 1600, 761);
    setfillstyle(WIDE_DOT_FILL, CYAN);
    bar(850, 200, 1550, 300);
    rectangle(850, 200, 1550, 760);
    line(850, 300, 1550, 300);
    line(850, 680, 1550, 680);
    settextstyle(0, 0, 3);
    setcolor(YELLOW);
    outtextxy(1200 - textwidth("THEM CAU HOI") / 2, 220, "THEM CAU HOI");
    settextstyle(0, 0, 2);
    outtextxy(1200 - textwidth(&outtextTenMon[0]) / 2, 260, &outtextTenMon[0]);

    edCauHoi.draw();
    edDapAnA.draw();
    edDapAnB.draw();
    edDapAnC.draw();
    edDapAnD.draw();
    edChonMaMon.draw();
    btnChonMaMon.draw();
    btnThemCauHoi.draw();
    setcolor(TEXT_EDIITEXT_TITLE_COLOR);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(860, 585, "DAP AN DUNG: ");
    btnDapAnA.draw();
    btnDapAnB.draw();
    btnDapAnC.draw();
    btnDapAnD.draw();
}

void drawHieuChinhCauHoi(string tenMon)
{
    setfillstyle(1, BLACK);
    bar(849, 75, 1600, 761);
    setfillstyle(WIDE_DOT_FILL, CYAN);
    bar(850, 200, 1550, 300);
    rectangle(850, 200, 1550, 760);
    line(850, 300, 1550, 300);
    line(850, 680, 1550, 680);
    outtextTenMon = "";
    settextstyle(0, 0, 3);
    setcolor(YELLOW);
    outtextxy(1200 - textwidth("HIEU CHINH CAU HOI") / 2, 220, "HIEU CHINH CAU HOI");
    settextstyle(0, 0, 2);

    edCauHoi.draw();
    edDapAnA.draw();
    edDapAnB.draw();
    edDapAnC.draw();
    edDapAnD.draw();
    edChonMaMon.draw();
    btnChonMaMon.draw();
    btnHieuChinhCauHoi.draw();
    btnXoaCauHoi.draw();
    btnThoatHieuChinhCH.draw();

    setcolor(TEXT_EDIITEXT_TITLE_COLOR);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(860, 585, "DAP AN DUNG: ");
    btnDapAnA.draw();
    btnDapAnB.draw();
    btnDapAnC.draw();
    btnDapAnD.draw();
}

void drawCauHoi()
{
    setbkcolor(BLACK);
    cleardevice();
    settextstyle(BOLD_FONT, 0, 5);
    setcolor(YELLOW);
    outtextxy(250, 20, "NGAN HANG CAU HOI");
    settextstyle(BOLD_FONT, 0, 3);
    btnQuaylai.draw();
    timKiemCauHoi.draw();
    btnLui.draw();
    btnTien_L.draw();
    rectangle(50, 200, 825, 760);
    line(50, 250, 825, 250);
    line(125, 200, 125, 760);
    line(250, 200, 250, 760);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(xDsCauHoi[0] + 30, 215, "ID");
    outtextxy(xDsCauHoi[1] + 25, 215, "MA MON");
    outtextxy(xDsCauHoi[2] + 230, 215, "CAU HOI");

    edCauHoi.setNext(&edDapAnA);
    edDapAnA.setNext(&edDapAnB);
    edDapAnB.setNext(&edDapAnC);
    edDapAnC.setNext(&edDapAnD);
    edDapAnD.setNext(&edCauHoi);

    edCauHoi.setPre(&edDapAnD);
    edDapAnA.setPre(&edCauHoi);
    edDapAnB.setPre(&edDapAnA);
    edDapAnC.setPre(&edDapAnB);
    edDapAnD.setPre(&edDapAnC);
}

//--------------------------------------------------- CHUC NANG THI THU -----------------------------------------------------
int cauHoiSo = 1;
void drawThoiGian(int giay)
{
    string Phut;
    string Giay;
    string thoiGian = Phut + "phut" + Giay;
    bool checkNopBai = false;
    while (giay > -1)
    {
        if (btnNopBai.click)
        {
            btnNopBai.click = false;
            checkNopBai = true;
            break;
        }
        setfillstyle(1, BLACK);
        bar(1102, 552, 1598, 898);
        Phut = to_string(giay / 60);
        Giay = to_string(giay - giay / 60 * 60);
        if (Giay.size() == 1)
        {
            Giay = "0" + Giay;
        }
        thoiGian = Phut + " PHUT : " + Giay + " GIAY";
        setcolor(YELLOW);
        settextstyle(10, 0, 3);

        outtextxy(1350 - textwidth(&thoiGian[0]) / 2, 680, &thoiGian[0]);
        Sleep(1000);
        giay--;
        thoiGian = to_string(giay);
        setcolor(WHITE);
    }
    if (!checkNopBai)
    {
        AllocConsole();
        MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Het gio lam bai!", "Thong bao", MB_OK);
    }
    drawList = true;
    if (curMenu == VAO_THITHU)
    {
        preMenu = VAO_THITHU;
        curMenu = DISPLAY_GIAOVIEN;
    }
    else if (curMenu == DISPLAY_HSTHI)
    {
        preMenu = DISPLAY_HSTHI;
        curMenu = DISPLAY_HOCSINH;
    }
    edChonMonThi.content = "";
    edsoCau.content = "";
    edTimeThi.content = "";
    cauHoiSo = 1;
    return;
}

void drawThi(string ho = "", string ten = "", string mssv = "", string Lop = "", string mon = "")
{
    setbkcolor(BLACK);
    cleardevice();
    btnTien.draw();
    btnLui.draw();
    rdChonA.draw();
    rdChonB.draw();
    rdChonC.draw();
    rdChonD.draw();
    btnNopBai.draw();

    setcolor(RED);
    rectangle(1100, 1, 1600, 900);
    line(1100, 450, 1600, 450);
    line(1100, 550, 1600, 550);
    line(1100, 70, 1600, 70);

    setbkcolor(GREEN);
    setfillstyle(WIDE_DOT_FILL, RED);
    bar(1100, 0, 1600, 70);
    bar(1100, 450, 1600, 550);

    setcolor(YELLOW);
    rectangle(50, 100, 1000, 760);
    settextstyle(10, 0, 3);
    line(50, 200, 1000, 200);

    settextstyle(0, 0, 4);
    outtextxy(1200, 485, "THOI GIAN:");

    outtextxy(1150, 20, "THONG TIN SV");
    settextstyle(10, 0, 3);
    setbkcolor(BLACK);
    setcolor(YELLOW);

    ho = "Ho va Ten: " + ho + " " + ten;
    mssv = "MSSV: " + mssv;
    Lop = "Lop: " + Lop;
    mon = "Mon: " + outtextTenMon;
    int temp = edsoCau.toInt();
    string SoCau = "So cau: " + to_string(temp);
    setcolor(WHITE);
    outtextxy(1130, 100, &ho[0]);
    outtextxy(1130, 160, &mssv[0]);
    outtextxy(1130, 220, &Lop[0]);
    outtextxy(1130, 280, &mon[0]);
    outtextxy(1130, 340, &SoCau[0]);
}

void drawXemBaiThi(sinhVien SV, Diem_Thi diem, string Lop = "")
{
    setbkcolor(BLACK);
    cleardevice();
    btnTien.draw();
    btnLui.draw();
    rdChonA.draw();
    rdChonB.draw();
    rdChonC.draw();
    rdChonD.draw();
    btnQuaylai.draw();

    setcolor(RED);
    rectangle(1100, 1, 1600, 900);
    line(1100, 450, 1600, 450);
    line(1100, 550, 1600, 550);
    line(1100, 70, 1600, 70);

    setbkcolor(GREEN);
    setfillstyle(WIDE_DOT_FILL, RED);
    bar(1100, 0, 1600, 70);
    bar(1100, 450, 1600, 550);

    setcolor(YELLOW);
    rectangle(50, 100, 1000, 760);
    settextstyle(10, 0, 3);
    line(50, 200, 1000, 200);

    settextstyle(0, 0, 4);
    outtextxy(1350 - textwidth("DIEM") / 2, 485, "DIEM");

    outtextxy(1150, 20, "THONG TIN SV");
    settextstyle(10, 0, 3);
    setbkcolor(BLACK);
    setcolor(YELLOW);

    string ho = "Ho va Ten: " + SV.Ho + " " + SV.Ten;
    string mssv = "MSSV: " + SV.mssv;
    Lop = "Lop: " + Lop;
    string mon = "Mon: " + outtextTenMon;
    string SoCau = "So cau hoi: " + to_string(diem.baithi.slcht);
    setcolor(WHITE);
    outtextxy(1130, 100, &ho[0]);
    outtextxy(1130, 160, &mssv[0]);
    outtextxy(1130, 220, &Lop[0]);
    outtextxy(1130, 280, &mon[0]);
    outtextxy(1130, 340, &SoCau[0]);

    setbkcolor(BLACK);
    settextstyle(0, 0, 10);
    string Textdiem = to_string(diem.Diem);
    for (int i = Textdiem.size() - 1; i >= 0; i--)
    {
        if (Textdiem[i] == '0')
        {
            Textdiem.pop_back();
        }
        else if (Textdiem[i] == '.')
        {
            Textdiem.pop_back();
            break;
        }
        else
        {
            break;
        }
    }
    setcolor(YELLOW);
    outtextxy(1350 - textwidth(&Textdiem[0]) / 2, 680, &Textdiem[0]);
    settextstyle(10, 0, 3);
    setcolor(WHITE);
}

void drawXemBaiThiThu(Diem_Thi diem, string TenMon)
{
    setbkcolor(BLACK);
    cleardevice();
    btnTien.draw();
    btnLui.draw();
    rdChonA.draw();
    rdChonB.draw();
    rdChonC.draw();
    rdChonD.draw();
    btnQuaylai.draw();

    setcolor(RED);
    rectangle(1100, 1, 1600, 900);
    line(1100, 450, 1600, 450);
    line(1100, 550, 1600, 550);
    line(1100, 70, 1600, 70);

    setbkcolor(GREEN);
    setfillstyle(WIDE_DOT_FILL, RED);
    bar(1100, 0, 1600, 70);
    bar(1100, 450, 1600, 550);

    setcolor(YELLOW);
    rectangle(50, 100, 1000, 760);
    settextstyle(10, 0, 3);
    line(50, 200, 1000, 200);

    settextstyle(0, 0, 4);
    outtextxy(1350 - textwidth("DIEM") / 2, 485, "DIEM");

    outtextxy(1150, 20, "THONG TIN SV");
    settextstyle(10, 0, 3);
    setbkcolor(BLACK);
    setcolor(YELLOW);

    string ho = "Ho va Ten: ";
    string mssv = "MSSV: ";
    string Lop = "Lop: ";
    TenMon = "Mon: " + TenMon;
    string SoCau = "So cau hoi: " + to_string(diem.baithi.slcht);
    setcolor(WHITE);
    outtextxy(1130, 100, &ho[0]);
    outtextxy(1130, 160, &mssv[0]);
    outtextxy(1130, 220, &Lop[0]);
    outtextxy(1130, 280, &TenMon[0]);
    outtextxy(1130, 340, &SoCau[0]);

    setbkcolor(BLACK);
    settextstyle(0, 0, 10);
    string Textdiem = to_string(diem.Diem);
    for (int i = Textdiem.size() - 1; i >= 0; i--)
    {
        if (Textdiem[i] == '0')
        {
            Textdiem.pop_back();
        }
        else if (Textdiem[i] == '.')
        {
            Textdiem.pop_back();
            break;
        }
        else
        {
            break;
        }
    }
    setcolor(YELLOW);
    outtextxy(1350 - textwidth(&Textdiem[0]) / 2, 680, &Textdiem[0]);
    settextstyle(10, 0, 3);
    setcolor(WHITE);
}

void drawBaiLam(cauHoiThi arrCauHoi[])
{
    if (btnTien.click && edsoCau.toInt() > cauHoiSo)
    {
        btnTien.click = false;
        cauHoiSo++;
    }
    else if (btnLui.click && cauHoiSo > 1)
    {
        btnLui.click = false;
        cauHoiSo--;
    }
    else if (btnTien.click || btnLui.click)
    {
        btnTien.click = false;
        btnLui.click = false;
        return;
    }

    setbkcolor(BLACK);
    setfillstyle(1, BLACK);
    bar(53, 105, 998, 198);
    bar(178, 205, 998, 758);

    setcolor(YELLOW);
    settextstyle(10, 0, 3);
    string cauSo = "CAU " + to_string(cauHoiSo) + ":";
    outtextxy(70, 140, &cauSo[0]);
    settextstyle(10, 0, 3);
    setcolor(WHITE);
    outtextxy(180, 140, &arrCauHoi[cauHoiSo - 1].cauHoiThi.NoiDung[0]);
    outtextxy(180, 240, &arrCauHoi[cauHoiSo - 1].cauHoiThi.A[0]);
    outtextxy(180, 390, &arrCauHoi[cauHoiSo - 1].cauHoiThi.B[0]);
    outtextxy(180, 540, &arrCauHoi[cauHoiSo - 1].cauHoiThi.C[0]);
    outtextxy(180, 690, &arrCauHoi[cauHoiSo - 1].cauHoiThi.D[0]);
    if (arrCauHoi[cauHoiSo - 1].luaChon == 'A')
    {
        rdChonA.click = true;
        rdChonB.click = false;
        rdChonC.click = false;
        rdChonD.click = false;
    }
    else if (arrCauHoi[cauHoiSo - 1].luaChon == 'B')
    {
        rdChonA.click = false;
        rdChonB.click = true;
        rdChonC.click = false;
        rdChonD.click = false;
    }
    else if (arrCauHoi[cauHoiSo - 1].luaChon == 'C')
    {
        rdChonA.click = false;
        rdChonB.click = false;
        rdChonC.click = true;
        rdChonD.click = false;
    }
    else if (arrCauHoi[cauHoiSo - 1].luaChon == 'D')
    {
        rdChonA.click = false;
        rdChonB.click = false;
        rdChonC.click = false;
        rdChonD.click = true;
    }
    else
    {
        rdChonA.click = false;
        rdChonB.click = false;
        rdChonC.click = false;
        rdChonD.click = false;
    }
    rdChonA.drawEffect();
    rdChonB.drawEffect();
    rdChonC.drawEffect();
    rdChonD.drawEffect();
}

void drawXemLaiBaiLam(cauHoiThi arrCauHoi[], int soCau)
{
    if (btnTien.click && soCau > cauHoiSo)
    {
        btnTien.click = false;
        cauHoiSo++;
    }
    else if (btnLui.click && cauHoiSo > 1)
    {
        btnLui.click = false;
        cauHoiSo--;
    }
    else if (btnTien.click || btnLui.click)
    {
        btnTien.click = false;
        btnLui.click = false;
        return;
    }

    setbkcolor(BLACK);
    setfillstyle(1, BLACK);
    bar(53, 105, 998, 198);
    bar(178, 205, 998, 758);

    setcolor(YELLOW);
    settextstyle(10, 0, 3);
    string cauSo = "CAU " + to_string(cauHoiSo) + ":";
    outtextxy(70, 140, &cauSo[0]);
    settextstyle(10, 0, 3);
    setcolor(WHITE);
    outtextxy(180, 140, &arrCauHoi[cauHoiSo - 1].cauHoiThi.NoiDung[0]);
    outtextxy(180, 240, &arrCauHoi[cauHoiSo - 1].cauHoiThi.A[0]);
    outtextxy(180, 390, &arrCauHoi[cauHoiSo - 1].cauHoiThi.B[0]);
    outtextxy(180, 540, &arrCauHoi[cauHoiSo - 1].cauHoiThi.C[0]);
    outtextxy(180, 690, &arrCauHoi[cauHoiSo - 1].cauHoiThi.D[0]);
    if (arrCauHoi[cauHoiSo - 1].luaChon == 'A')
    {
        rdChonA.click = true;
        rdChonB.click = false;
        rdChonC.click = false;
        rdChonD.click = false;
    }
    else if (arrCauHoi[cauHoiSo - 1].luaChon == 'B')
    {
        rdChonA.click = false;
        rdChonB.click = true;
        rdChonC.click = false;
        rdChonD.click = false;
    }
    else if (arrCauHoi[cauHoiSo - 1].luaChon == 'C')
    {
        rdChonA.click = false;
        rdChonB.click = false;
        rdChonC.click = true;
        rdChonD.click = false;
    }
    else if (arrCauHoi[cauHoiSo - 1].luaChon == 'D')
    {
        rdChonA.click = false;
        rdChonB.click = false;
        rdChonC.click = false;
        rdChonD.click = true;
    }
    else
    {
        rdChonA.click = false;
        rdChonB.click = false;
        rdChonC.click = false;
        rdChonD.click = false;
    }
    if (arrCauHoi[cauHoiSo - 1].cauHoiThi.DapAn == 'A')
    {
        outtextxy(515 - textwidth("DAP AN DUNG: A") / 2, 825, "DAP AN DUNG: A");
    }
    else if (arrCauHoi[cauHoiSo - 1].cauHoiThi.DapAn == 'B')
    {
        outtextxy(515 - textwidth("DAP AN DUNG: B") / 2, 825, "DAP AN DUNG: B");
    }
    else if (arrCauHoi[cauHoiSo - 1].cauHoiThi.DapAn == 'C')
    {
        outtextxy(515 - textwidth("DAP AN DUNG: C") / 2, 825, "DAP AN DUNG: C");
    }
    else if (arrCauHoi[cauHoiSo - 1].cauHoiThi.DapAn == 'D')
    {
        outtextxy(515 - textwidth("DAP AN DUNG: D") / 2, 825, "DAP AN DUNG: D");
    }

    rdChonA.drawEffect();
    rdChonB.drawEffect();
    rdChonC.drawEffect();
    rdChonD.drawEffect();
}

void drawDiemVuaThi(float diem)
{
    HWND hWnd = FindWindowA(NULL, "Diem so");
    HMENU hMenu = GetSystemMenu(hWnd, false);
    DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    settextstyle(10, 0, 4);
    setcolor(YELLOW);
    setfillstyle(WIDE_DOT_FILL, CYAN);
    bar(50, 120, 550, 200);
    rectangle(50, 120, 550, 450);
    line(50, 200, 550, 200);
    outtextxy(300 - textwidth("So diem cua ban la:") / 2, 145, "So diem cua ban la:");
    settextstyle(10, 0, 10);
    setcolor(WHITE);
    string diemSo = to_string(diem);
    xoaSoThapPhan(diemSo);
    outtextxy(300 - textwidth(&diemSo[0]) / 2, 250, &diemSo[0]);
    btnQuaylai.draw();
}
// Ve chuc nang chon THOI GIAN, SO CAU HOI THI
void drawThietLapThi()
{
    setfillstyle(1, BLACK);
    outtextTenMon = "";
    bar(1005, 0, 1600, 765);
    setfillstyle(WIDE_DOT_FILL, CYAN);
    bar(1050, 200, 1550, 300);
    setcolor(YELLOW);
    settextstyle(0, 0, 3);
    outtextxy(1300 - textwidth("MON THI") / 2, 220, "MON THI");

    rectangle(1050, 200, 1550, 700);
    line(1050, 300, 1550, 300);

    line(1050, 600, 1550, 600);
    edChonMonThi.draw();
    edTimeThi.draw();
    edsoCau.draw();
    btnVaoThi.draw();
    if (curMenu == DISPLAY_THITHU)
    {
        btnXemBaiThiThu.draw();
    }

    edTimeThi.setNext(&edsoCau);
    edsoCau.setNext(&edTimeThi);

    edTimeThi.setPre(&edsoCau);
    edsoCau.setPre(&edTimeThi);
}