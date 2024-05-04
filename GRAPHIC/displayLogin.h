void displayLogin(ListMonHoc listMH, dslop &DanhSachLop, IDRandom *&listID, NodeCauHoi *root, mangCauHoi arrCauHoi)
{
    dangnhap.ButtonEffect();
    if (GetAsyncKeyState(VK_LBUTTON))
    {

        if (dangnhap.isMouseHover())
        {
            if (taiKhoan.ToString() == "GV" && matKhau.content == "GV")
            {
                curMenu = DISPLAY_GIAOVIEN;
                drawGV();
                Edit = nullptr;
                // De nguoi dung nha chuot ra
                Sleep(500);
            }
            else if (taiKhoan.content.size() && matKhau.content.size())
            {
                nodeSV *node = nullptr;
                bool checkThoat = true;
                for (int i = 0; i < DanhSachLop.solop; i++)
                {
                    node = DanhSachLop.arrLop[i].dsSinhVien.First;
                    while (node != nullptr)
                    {
                        if (taiKhoan.ToString() == node->info.mssv && matKhau.content == node->info.Pass)
                        {
                            curMenu = DISPLAY_HOCSINH;
                            drawHocSinh(node->info.Ho, node->info.Ten, node->info.mssv, node->info.gioiTinh, DanhSachLop.arrLop[i].TENLOP);
                            Edit = nullptr;
                            while (true)
                            {
                                KeyboardEvent();
                                if (curMenu == DISPLAY_HOCSINH)
                                {
                                    displayHocSinh(listMH, DanhSachLop.arrLop[i].dsSinhVien, node->info, DanhSachLop.arrLop[i].MALOP);
                                }
                                else if (curMenu == DISPLAY_DOIMK)
                                {
                                    displayDoiMK(DanhSachLop.arrLop[i].dsSinhVien, node->info.Pass, DanhSachLop.arrLop[i].MALOP);
                                    if (btnQuaylai.click)
                                    {
                                        btnQuaylai.click = false;
                                        drawHocSinh();
                                    }
                                }
                                else if (curMenu == LUACHON_THI_HS)
                                {
                                    displayLuaChonMonThi(listMH, node->info, DanhSachLop.arrLop[i].MALOP, root, arrCauHoi);
                                }
                                else if (curMenu == DISPLAY_HSTHI)
                                {
                                    dipslayHocSinhThi(node->info.listDT.first->info.baithi);
                                }
                                else if (curMenu == DISPLAY_DIEMSV)
                                {
                                    displayDiemSV(node->info, listMH, DanhSachLop.arrLop[i].MALOP);
                                    if (btnQuaylai.click)
                                    {
                                        btnQuaylai.click = false;
                                        drawHocSinh();
                                    }
                                }

                                if (btndangxuat.click == true)
                                {
                                    btndangxuat.click = false;
                                    return;
                                }
                                if (preMenu == DISPLAY_HSTHI)
                                {
                                    timer.join();
                                    drawHocSinh();
                                    chamBai(node->info.listDT.first->info);
                                    luuBaiThi(node->info.mssv, node->info.listDT);
                                    Luu_File_Cau_Hoi(root);
                                    windowDiemSo = initwindow(600, 500, "DIEM SO", GetSystemMetrics(SM_CXSCREEN) / 2 - 300, 200);
                                    drawDiemVuaThi(node->info.listDT.first->info.Diem);
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
                        else if (taiKhoan.ToString() == node->info.mssv && matKhau.content != node->info.Pass)
                        {
                            AllocConsole();
                            MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "TAI KHOAN hoac MAT KHAU khong chinh xac!", "Thong bao", MB_ICONWARNING | MB_OK);
                            checkThoat = false;
                            return;
                        }
                        // Neu tim thay TAI KHOAN nhung MAT KHAU sai thi THOAT
                        if (checkThoat == false)
                        {
                            break;
                        }
                        node = node->pNext;
                    }
                }
                AllocConsole();
                MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "TAI KHOAN hoac MAT KHAU khong chinh xac!", "Thong bao", MB_ICONWARNING | MB_OK);
                Sleep(500);
            }
            else
            {
                AllocConsole();
                MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "TAI KHOAN hoac MAT KHAU khong chinh xac!", "Thong bao", MB_ICONWARNING | MB_OK);
            }
        }
        else if (taiKhoan.isMouseHover())
        {
            Edit = &taiKhoan;
        }
        else if (matKhau.isMouseHover())
        {
            Edit = &matKhau;
        }
    }
}