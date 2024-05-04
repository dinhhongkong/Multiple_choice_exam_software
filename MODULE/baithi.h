//--------------------------------- NGUYEN MAU HAM ---------------------------------
void giaiPhongArrCauHoi(mangCauHoi &dsCauHoi);
bool taoBaiThi(Bai_Thi &baiThi, mangCauHoi &arr, int soCau);
bool taoBaiThiThu(Diem_Thi &gvThiThu, mangCauHoi &arr, int soCau);
bool kiemTraDaThi(Danh_Sach_Diem_Thi listDT, string maMon);
void chamBai(Diem_Thi &chamThi);
void luuBaiThi(string mssv, Danh_Sach_Diem_Thi dsDiem);
void docBaiThi(string mssv, Danh_Sach_Diem_Thi &dsDiem);

//--------------------------------- DINH NGHIA HAM ---------------------------------
void giaiPhongArrCauHoi(mangCauHoi &dsCauHoi) {
	for ( int i = 0 ; i < dsCauHoi.tongSoCau; i++) {
        dsCauHoi.arrCauHoiThi[i] = nullptr;
    }
	dsCauHoi.tongSoCau = 0;
    delete []dsCauHoi.arrCauHoiThi;
}

bool taoBaiThi(Bai_Thi &baiThi, mangCauHoi &arr, int soCau)
{
    int maxSoCau = arr.tongSoCau;
    if (soCau > maxSoCau)
    {
        giaiPhongArrCauHoi(arr);
        AllocConsole();
        MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "So luong cau hoi khong du!", "Thong bao", MB_ICONINFORMATION | MB_OK);
        return false;
    }
    baiThi.slcht = soCau;
    baiThi.arrCauHoi = new cauHoiThi[soCau];
    for (int i = 0; i < maxSoCau; i++)
    {
        int vitri = Random(0, maxSoCau - 1);
        swap(arr.arrCauHoiThi[i], arr.arrCauHoiThi[vitri]);
    }
    
    for (int i = 0; i < soCau; i++)
    {
        baiThi.arrCauHoi[i].cauHoiThi = arr.arrCauHoiThi[i]->info;
        arr.arrCauHoiThi[i]->info.used = true;
    }
    giaiPhongArrCauHoi(arr);
    return true;
}

bool taoBaiThiThu(Diem_Thi &gvThiThu, mangCauHoi &arr, int soCau)
{
    int maxSoCau = arr.tongSoCau;
    if (soCau > maxSoCau)
    {
        giaiPhongArrCauHoi(arr);
        AllocConsole();
        MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "So luong cau hoi khong du!", "Thong bao", MB_ICONINFORMATION | MB_OK);
        return false;
    }
    if (gvThiThu.MAMH.size()) {
        delete []gvThiThu.baithi.arrCauHoi;
    }
    gvThiThu.baithi.slcht = soCau;
    gvThiThu.baithi.arrCauHoi = new cauHoiThi[soCau];
    for (int i = 0; i < maxSoCau; i++)
    {
        int vitri = Random(0, maxSoCau -1);
        swap(arr.arrCauHoiThi[i], arr.arrCauHoiThi[vitri]);
    }
    for (int i = 0; i < soCau; i++)
    {
        gvThiThu.baithi.arrCauHoi[i].cauHoiThi = arr.arrCauHoiThi[i]->info;
    }
    giaiPhongArrCauHoi(arr);
    return true;
}

bool kiemTraDaThi(Danh_Sach_Diem_Thi listDT, string maMon)
{
    Node_Diem_Thi *node = listDT.first;

    while (node != nullptr)
    {
        if (node->info.MAMH == maMon)
        {
            AllocConsole();
            MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Ban da thi mon nay!", "Thong bao", MB_ICONEXCLAMATION | MB_OK);
            return false;
        }
        node = node->DTnext;
    }
    return true;
}

void chamBai(Diem_Thi &chamThi)
{
    float tongDiem = 0;
    for (int i = 0; i < chamThi.baithi.slcht; i++)
    {
        if (chamThi.baithi.arrCauHoi[i].cauHoiThi.DapAn == chamThi.baithi.arrCauHoi[i].luaChon)
        {
            tongDiem++;
        }
    }
    chamThi.Diem = ceilf(((tongDiem * 10) /chamThi.baithi.slcht) * 100) / 100;
}

void luuBaiThi(string mssv, Danh_Sach_Diem_Thi dsDiem)
{
    ofstream fileOut;
    string fileName = "DATA\\FileDSDiem\\" + mssv + ".txt";
    fileOut.open(fileName, ios_base::out);

    Node_Diem_Thi *nodeDiemThi = dsDiem.first;
    while (nodeDiemThi != nullptr)
    {
        fileOut << nodeDiemThi->info.MAMH << ',';
        fileOut << nodeDiemThi->info.Diem << endl;
        fileOut << nodeDiemThi->info.baithi.slcht << endl;
        for (int i = 0; i < nodeDiemThi->info.baithi.slcht; i++)
        {
            fileOut << nodeDiemThi->info.baithi.arrCauHoi[i].cauHoiThi.id << endl;
            fileOut << nodeDiemThi->info.baithi.arrCauHoi[i].cauHoiThi.NoiDung << endl;
            fileOut << nodeDiemThi->info.baithi.arrCauHoi[i].cauHoiThi.A << endl;
            fileOut << nodeDiemThi->info.baithi.arrCauHoi[i].cauHoiThi.B << endl;
            fileOut << nodeDiemThi->info.baithi.arrCauHoi[i].cauHoiThi.C << endl;
            fileOut << nodeDiemThi->info.baithi.arrCauHoi[i].cauHoiThi.D << endl;
            fileOut << nodeDiemThi->info.baithi.arrCauHoi[i].cauHoiThi.DapAn << endl;
            fileOut << nodeDiemThi->info.baithi.arrCauHoi[i].luaChon << endl;
        }
        nodeDiemThi = nodeDiemThi->DTnext;
    }
    fileOut.close();
}

void docBaiThi(string mssv, Danh_Sach_Diem_Thi &dsDiem)
{
    ifstream fileIn;
    string fileName = "DATA\\FileDSDiem\\" + mssv + ".txt";
    fileIn.open(fileName, ios_base::in);
    dsDiem.first = nullptr;
    if (!fileIn.is_open())
    {
        return;
    }

    Diem_Thi diemthi;
    while (getline(fileIn, diemthi.MAMH, ','))
    {
        fileIn >> diemthi.Diem;
        fileIn >> diemthi.baithi.slcht;
        diemthi.baithi.arrCauHoi = new cauHoiThi[diemthi.baithi.slcht];

        for (int i = 0; i < diemthi.baithi.slcht; i++)
        {
            fileIn >> diemthi.baithi.arrCauHoi[i].cauHoiThi.id;
            fileIn.ignore();
            getline(fileIn, diemthi.baithi.arrCauHoi[i].cauHoiThi.NoiDung, '\n');
            getline(fileIn, diemthi.baithi.arrCauHoi[i].cauHoiThi.A, '\n');
            getline(fileIn, diemthi.baithi.arrCauHoi[i].cauHoiThi.B, '\n');
            getline(fileIn, diemthi.baithi.arrCauHoi[i].cauHoiThi.C, '\n');
            getline(fileIn, diemthi.baithi.arrCauHoi[i].cauHoiThi.D, '\n');
            fileIn >> diemthi.baithi.arrCauHoi[i].cauHoiThi.DapAn;
            fileIn >> diemthi.baithi.arrCauHoi[i].luaChon;
            fileIn.ignore();
        }
        Node_Diem_Thi *nodeDiemSV = new Node_Diem_Thi;
        nodeDiemSV->info = diemthi;
        nodeDiemSV->DTnext = nullptr;
        Them_Diem_Vao_Cuoi(dsDiem, nodeDiemSV);
    }
    fileIn.close();
}