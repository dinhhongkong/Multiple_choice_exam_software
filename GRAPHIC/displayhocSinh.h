void displayHocSinh(ListMonHoc listMH, listSV &dsSinhVien, sinhVien &sv, string maLop)
{
    btnThi.ButtonEffect();
    btnXemDiemSV.ButtonEffect();
    btnDoiMK.ButtonEffect();
    btndangxuat.ButtonEffect();

    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (btndangxuat.isMouseHover())
        {
            drawLogin();
            curMenu = DISPLAY_LOGIN;
            btndangxuat.click = true;
        }
        else if (btnDoiMK.isMouseHover())
        {
            curMenu = DISPLAY_DOIMK;
            drawDoiMk();
        }
        else if (btnThi.isMouseHover())
        {
            curMenu = LUACHON_THI_HS;
            drawMonHoc();
            drawThietLapThi();
            MenuThemMon = false;
        }
        else if (btnXemDiemSV.isMouseHover())
        {
            curMenu = DISPLAY_DIEMSV;
            drawDiemSV();
            listviewDS.size = 0;
            drawDsDiemSV(sv.listDT, listMH);
        }
    }
}

void displayDoiMK(listSV &dsSinhVien, string &mk, string maLop)
{
    btnQuaylai.ButtonEffect();
    btnDoiMKMoi.ButtonEffect();

    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (matKhauCu.isMouseHover())
        {
            Edit = &matKhauCu;
        }
        else if (matKhauMoi.isMouseHover())
        {
            Edit = &matKhauMoi;
        }
        else if (nhapLaiMatKhau.isMouseHover())
        {
            Edit = &nhapLaiMatKhau;
        }
        else if (btnDoiMKMoi.isMouseHover())
        {
            if (matKhauCu.content == "")
            {
                AllocConsole();
                MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Mat khau khong the trong!", "Thong bao", MB_ICONINFORMATION | MB_OK);
            }
            else if (matKhauMoi.content == "")
            {
                AllocConsole();
                MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Vui long nhap mat khau moi!", "Thong bao", MB_ICONINFORMATION | MB_OK);
            }
            else if (nhapLaiMatKhau.content == "")
            {
                AllocConsole();
                MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Vui long nhap lai mat khau moi!", "Thong bao", MB_ICONINFORMATION | MB_OK);
            }
            else
            {
                if (mk != matKhauCu.content)
                {
                    AllocConsole();
                    MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Mat khau cu khong chinh xac!", "Thong bao", MB_ICONWARNING | MB_OK);
                }
                else if (matKhauMoi.content != nhapLaiMatKhau.content)
                {
                    AllocConsole();
                    MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Mat khau nhap lai khong giong mat khau moi!", "Thong bao", MB_ICONWARNING | MB_OK);
                }
                else if (mk == matKhauMoi.content)
                {
                    AllocConsole();
                    MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Mat khau moi trung voi mat khau cu!", "Thong bao", MB_ICONWARNING | MB_OK);
                }
                else
                {
                    mk = matKhauMoi.content;
                    ghiFileDsSinhVien(dsSinhVien, maLop);
                    AllocConsole();
                    MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Doi mat khau thanh cong", "Thong bao", MB_OK);
                    matKhauCu.content = "";
                    matKhauMoi.content = "";
                    nhapLaiMatKhau.content = "";
                    btnQuaylai.click = true;
                    curMenu = DISPLAY_HOCSINH;
                }
            }
        }
        else if (btnQuaylai.isMouseHover())
        {
            matKhauCu.content = "";
            matKhauMoi.content = "";
            nhapLaiMatKhau.content = "";
            btnQuaylai.click = true;
            curMenu = DISPLAY_HOCSINH;
            Edit = nullptr;
        }
    }
}

void ClickItemMonThi(NodeCauHoi *root, ListMonHoc &listMH)
{
    int x = -1, y = -1;
    x = mousex();
    y = mousey();
    static int LuaChon = -1; // Thanh sang khi chuot di qua ITEAM
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

        // Bat su kien o giao dien danh sach mon thi
        if (GetAsyncKeyState(VK_LBUTTON) && LuaChon < listviewDS.size && curMenu == LUACHON_THI_HS)
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

void displayLuaChonMonThi(ListMonHoc listMH, sinhVien &sv, string tenLOP, NodeCauHoi *root, mangCauHoi &arrCauHoi)
{
    btnQuaylai.ButtonEffect();
    btnTien.ButtonEffect();
    btnLui.ButtonEffect();
    btnVaoThi.ButtonEffect();
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
    ClickItemMonThi(root, listMH);
    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (btnQuaylai.isMouseHover())
        {
            Edit = nullptr;
            drawList = true;
            curMenu = DISPLAY_HOCSINH;
            preMenu = -1;
            MenuThemMon = true;
            MenuThemLop = true;
            edChonMonThi.content = "";
            edTimeThi.content = "";
            edsoCau.content = "";
            timKiemMon.content = "";
            outtextTenMon = "";
            drawHocSinh();
            soTrangMon = 1;
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
        else if (edTimeThi.isMouseHover())
        {
            Edit = &edTimeThi;
        }
        else if (edsoCau.isMouseHover())
        {
            Edit = &edsoCau;
        }
        else if (btnVaoThi.isMouseHover())
        {

            int soLuongCauHoi = 0;
            if (edChonMonThi.content.size() && edTimeThi.content.size() && edsoCau.content.size())
            {
                demSoCauTheoMaMon(root, edChonMonThi.ToString(), soLuongCauHoi);
                arrCauHoi.arrCauHoiThi = new NodeCauHoi *[soLuongCauHoi];
                taoMangCauHoi(root, arrCauHoi, edChonMonThi.ToString());
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
            else if (kiemTraDaThi(sv.listDT, edChonMonThi.ToString()))
            {
                Diem_Thi diemThiSV;
                diemThiSV.MAMH = edChonMonThi.ToString();
                Node_Diem_Thi *nodeDiemSV = new Node_Diem_Thi;
                nodeDiemSV->info = diemThiSV;
                nodeDiemSV->DTnext = nullptr;
                if (taoBaiThi(nodeDiemSV->info.baithi, arrCauHoi, edsoCau.toInt()))
                {
                    Luu_File_Cau_Hoi(root);
                    Them_Diem_Vao_Dau(sv.listDT, nodeDiemSV);
                    curMenu = DISPLAY_HSTHI;
                    int giay = edTimeThi.toInt() * 60;
                    drawThi(sv.Ho, sv.Ten, sv.mssv, tenLOP, "");
                    drawBaiLam(nodeDiemSV->info.baithi.arrCauHoi);
                    Edit = nullptr;
                    Sleep(100);
                    timer = thread(drawThoiGian, giay);
                    timKiemMon.content = "";
                }
                else
                {
                    delete nodeDiemSV;
                }
            }
            else
            {
                giaiPhongArrCauHoi(arrCauHoi);
            }
        }
    }
}

void ClickItemXemBai(sinhVien SV, ListMonHoc listMH, string Lop)
{
    int x = -1, y = -1;
    x = mousex();
    y = mousey();
    static int LuaChon = -1;
    static int PreLuaChon = -1;

    int soLuong = 0;
    Node_Diem_Thi *nodeDiem = SV.listDT.first;
    while (nodeDiem != nullptr)
    {
        soLuong++;
        nodeDiem = nodeDiem->DTnext;
    }
    LuaChon = (y - yDsDiemSV[0]) / 50;

    if (x > xDsDiemSV[0] && x < xDsDiemSV[3] && y > yDsDiemSV[0] && y < yDsDiemSV[1])
    {
        // Khoi phuc ITEAM
        if (PreLuaChon != -1 && PreLuaChon != LuaChon && PreLuaChon < listviewDS.size)
        {
            setfillstyle(1, BLACK);
            bar(xDsDiemSV[0] - 100, yDsDiemSV[0] + 20 + PreLuaChon * 50 - 30, xDsDiemSV[0] - 5, yDsDiemSV[0] + 40 + PreLuaChon * 50 + 30);
        }

        PreLuaChon = LuaChon;
        // Ve ITEAM hien tai
        if (PreLuaChon != -1 && LuaChon < listviewDS.size)
        {
            setcolor(LIGHTGREEN);
            setbkcolor(RED);
            readimagefile(troNgonTay, xDsDiemSV[0] - 100, yDsDiemSV[0] + 20 + PreLuaChon * 50 - 30, xDsDiemSV[0] - 5, yDsDiemSV[0] + 40 + PreLuaChon * 50 + 30);
        }

        if (GetAsyncKeyState(VK_LBUTTON) && LuaChon < listviewDS.size)
        {
            nodeDiem = SV.listDT.first;
            for (int i = 0; i < listviewDS.idItem[LuaChon]; i++)
            {
                nodeDiem = nodeDiem->DTnext;
            }
            cauHoiSo = 1;
            outtextTenMon = Truy_Xuat_Ten_Mon(listMH, nodeDiem->info.MAMH);
            drawXemBaiThi(SV, nodeDiem->info, Lop);
            drawXemLaiBaiLam(nodeDiem->info.baithi.arrCauHoi, nodeDiem->info.baithi.slcht);

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
                        outtextTenMon = "";
                        cauHoiSo = 1;
                        Sleep(100);
                        break;
                    }
                }
                Sleep(100);
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
            bar(xDsDiemSV[0] - 100, yDsDiemSV[0] + 20 + PreLuaChon * 50 - 30, xDsDiemSV[0] - 5, yDsDiemSV[0] + 40 + PreLuaChon * 50 + 30);
        }
        LuaChon = -1;
        PreLuaChon = -1;
        setcolor(WHITE);
    }
}

void displayDiemSV(sinhVien SV, ListMonHoc listMH, string Lop)
{
    btnQuaylai.ButtonEffect();
    btnTien_L1.ButtonEffect();
    btnLui_L.ButtonEffect();
    if (drawList)
    {
        drawList = false;
        drawDsDiemSV(SV.listDT, listMH);
    }
    ClickItemXemBai(SV, listMH, Lop);
    if (btnQuaylai.click)
    {
        btnQuaylai.click = false;
        drawDiemSV();
        drawDsDiemSV(SV.listDT, listMH);
    }

    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (btnQuaylai.isMouseHover() && curMenu == DISPLAY_DIEMSV)
        {
            curMenu = DISPLAY_HOCSINH;
            btnQuaylai.click = true;

            drawList = true;
            trangDiemSV = 1;
            edtimKiemSV_R.content = "";
            luaChonLop = -1;
            Edit = nullptr;
        }

        if (btnQuaylai.isMouseHover() && curMenu == DISLPAY_DIEM_THEO_SV)
        {
            btnQuaylai.click = true;
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
    }
}

void dipslayHocSinhThi(Bai_Thi &baiThisv)
{
    rdChonA.RadioEffect();
    rdChonB.RadioEffect();
    rdChonC.RadioEffect();
    rdChonD.RadioEffect();
    if (GetAsyncKeyState(VK_LBUTTON))
    {

        if (rdChonA.isMouseHover())
        {
            baiThisv.arrCauHoi[cauHoiSo - 1].luaChon = 'A';
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
            baiThisv.arrCauHoi[cauHoiSo - 1].luaChon = 'B';
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
            baiThisv.arrCauHoi[cauHoiSo - 1].luaChon = 'C';
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
            baiThisv.arrCauHoi[cauHoiSo - 1].luaChon = 'D';
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
            drawBaiLam(baiThisv.arrCauHoi);
        }
        else if (btnLui.isMouseHover())
        {
            btnLui.click = true;
            drawBaiLam(baiThisv.arrCauHoi);
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

void displayDiemVuaThi()
{
    btnQuaylai.ButtonEffect();
    if (GetAsyncKeyState(VK_LBUTTON) && btnQuaylai.isMouseHover())
    {
        btnQuaylai.click = true;
        closegraph(CURRENT_WINDOW);
        setcurrentwindow(mainWindow);
    }
}