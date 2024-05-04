int curMenu = 0;
int preMenu = -1;
bool drawList = true;
int luaChonLop = -1;
int luaChonMon = -1;
int mainWindow;
int window1;
int windowDiemSo;
const char *troNgonTay = "IMAGE\\icon_finger.jpg";
const char *iconChuotTrai = "IMAGE\\icon_leftMouse.jpg";
const char *iconChuotPhai = "IMAGE\\icon_rightMouse.jpg";
thread timer;

editText *Edit = nullptr;

class listview
{
public:
    int size = 0;
    int idItem[10];
    bool click = false;
};

//GIAO DIEN DANG NHAP
editText taiKhoan(500, 300, 600, 50, "TAI KHOAN: ", "Nhap ma so sinh vien", 100);
editText matKhau(500, 400, 600, 50, "MAT KHAU: ", "Nhan chu, so va ki tu dac biet (Luu y: CapsLock)", 20, 1);
button dangnhap(700, 500, 200, 70, "DANG NHAP");

//GIAO DIEN THAY DOI MAT KHAU TAI GIAO DIEN SINH VIEN
editText matKhauCu(500, 300, 600, 50, "Mat khau cu: ", "Nhan chu, so va ki tu dac biet (Luu y: CapsLock)", 20, 1);
editText matKhauMoi(500, 400, 600, 50, "Mat khau moi: ", "Nhan chu, so va ki tu dac biet (Luu y: CapsLock)", 20, 1);
editText nhapLaiMatKhau(500, 500, 600, 50, "Nhap lai MK: ", "Nhan chu, so va ki tu dac biet (Luu y: CapsLock)", 20, 1);
button btnDoiMKMoi(700, 600, 200, 50, "DOI MAT KHAU");

int xDsDiemSV[4] = {350, 600, 1100, 1250};
int yDsDiemSV[2] = {250, 750};

//GIAO DIEN GIANG VIEN
button btnMonHoc(700, 200, 250, 50, "QUAN LY MON HOC");
button btnDsLop(700, 300, 250, 50, "QUAN LY LOP HOC");
button btnDiemThi(700, 400, 250, 50, "DIEM THI");
button btnCauHoiThi(700, 500, 250, 50, "CAU HOI THI");
button btnThiThu(700, 600, 250, 50, "THI THU");
button btnDangXuat(750, 700, 150, 50, "DANG XUAT");

listview listviewDS;
button btnLui(70, 820, 100, 50, "PRE");
button btnTien(800, 820, 100, 50, "NEXT");
button btnTien_L(640, 820, 100, 50, "NEXT");
button btnThem(1250, 625, 100, 50, "THEM");
button btnHieuChinh(1075, 625, 200, 50, "HIEU CHINH");
button btnXoaVinhVien(1325, 625, 200, 50, "XOA VINH VIEN");
button btnThoat(1050, 20, 220, 50, "< THOAT CHUC NANG");

//NUT CHUC NANG QUAN LY MON HOC TAI GIAO DIEN GIANG VIEN
int xDsMon[3] = {50, 300, 950};
int yDsMon[2] = {250, 750};
button btnQuaylai(20, 20, 100, 50, "< BACK");
editText timKiemMon(100, 100, 600, 50, "TIM KIEM: ", "Nhap MA hoac TEN MON muon tim", 100);
bool MenuThemMon = true;
editText themMaMon(1075, 350, 450, 50, "MA MON:", "Toi da 15 ki tu", 15);
editText themTenMon(1075, 475, 450, 50, "TEN MON:", "Toi da 35 ki tu", 35);

//GIAO DIEN SINH VIEN
button btnThi(325, 50, 200, 50, "THI");
button btnXemDiemSV(575, 50, 200, 50, "XEM DIEM");
button btnDoiMK(825, 50, 200, 50, "DOI MAT KHAU");
button btndangxuat(1075, 50, 200, 50, "DANG XUAT");

//NUT CHUC NANG QUAN LY LOP
int xDsLop[3] = {50, 350, 950};
int yDsLop[2] = {250, 750};
bool MenuThemLop = true;
editText themMaLop(1075, 350, 450, 50, "MA LOP HOC:", "Toi da 15 ki tu", 15);
editText themTenLop(1075, 475, 450, 50, "TEN LOP HOC:", "Toi da 40 ki tu", 40);
editText timKiemLop(100, 100, 600, 50, "TIM KIEM: ", "Nhap MA hoac TEN LOP muon tim", 100);

//DANH SACH SINH VIEN TRONG 1 LOP
int xDsSV[6] = {50, 250, 600, 800, 950};
int yDsSV[2] = {250, 750};
editText edtimKiemSV(100, 100, 600, 50, "TIM KIEM: ", "Nhap MA hoac TEN SINH VIEN muon tim", 100);
editText edMSSV(1075, 325, 450, 50, "MSSV:", "Toi da 10 ki tu", 10);
editText edHoSV(1075, 400, 450, 50, "Ho va ten dem:", "Toi da 25 ki tu", 25);
editText edTenSV(1075, 475, 450, 50, "Ten:", "Toi da 10 ki tu", 10);
button btnNam(1225, 540, 100, 40, "NAM");
button btnNu(1350, 540, 100, 40, "NU");
button btnResetMK(1150, 710, 300, 50, "RESET MAT KHAU MAC DINH");

//CHUC NANG XEM DIEM TAI GIAO DIEN GIANG VIEN
int xDsDiem[5] = {350, 550, 900, 1100, 1250};
int yDsDiem[2] = {250, 750};
button btnDiemSV(100,250,400,50,"XEM DIEM THEO SINH VIEN");
button btnDiemLop(100,350,400,50,"XEM DIEM THEO MON HOC");
editText edtimKiemSV_R(500, 100, 600, 50, "TIM KIEM: ", "Nhap MA hoac TEN SINH VIEN muon tim", 100);
button btnLui_L(370, 820, 100, 50, "PRE");
button btnTien_L1(1120, 820, 100, 50, "NEXT");

//CAU HOI
int xDsCauHoi[4] = {50, 125, 250, 825};
int yDsCauHoi[2] = {250, 750};
bool chucNangThemCauHoi = true;
editText edCauHoi(860, 325, 670, 40, "NOI DUNG:", "Toi da 50 ki tu", 50);
editText edDapAnA(860, 375, 670, 40, "DAP AN A:", "Toi da 40 ki tu", 40);
editText edDapAnB(860, 425, 670, 40, "DAP AN B:", "Toi da 40 ki tu", 40);
editText edDapAnC(860, 475, 670, 40, "DAP AN C:", "Toi da 40 ki tu", 40);
editText edDapAnD(860, 525, 670, 40, "DAP AN D:", "Toi da 40 ki tu", 40);
editText edChonMaMon(860, 630, 670, 40, "", "Click vao MA MON de chon", 50);
button btnChonMaMon(860, 630, 140, 40, "MA MON:");
button btnDapAnA(1040, 575, 100, 40, "A");
button btnDapAnB(1165, 575, 100, 40, "B");
button btnDapAnC(1290, 575, 100, 40, "C");
button btnDapAnD(1415, 575, 100, 40, "D");
button btnThemCauHoi(1100, 695, 200, 50, "THEM CAU HOI");
button btnHieuChinhCauHoi(950, 695, 200, 50, "HIEU CHINH");
button btnThoatHieuChinhCH(850, 20, 220, 50, "< THOAT HIEU CHINH");
button btnXoaCauHoi(1250, 695, 200, 50, "XOA");
editText timKiemCauHoi(100, 100, 600, 50, "TIM KIEM: ", "Nhap ID hoac TU KHOA muon tim", 100);

//CHUC NANG TUY CHON TRUOC KHI THI
string outtextTenMon;
editText edChonMonThi(1075, 350, 450, 50, "MA MON THI:", "Chon mon thi trong danh sach", 10);
editText edTimeThi(1075, 420, 450, 50, "T/G LAM BAI:", "Tinh theo phut", 3);
editText edsoCau(1075, 490, 450, 50, "SO CAU:", "So cau trong bai thi", 3);
button btnVaoThi(1250, 625, 100, 50, "VAO THI");
button btnXemBaiThiThu(1180, 100, 240, 50, "XEM LAI BAI THI THU");

//THI
button btnNopBai(1250, 390, 200, 50, "NOP BAI");
radioButton rdChonA(105, 250, 30, "A.");
radioButton rdChonB(105, 400, 30, "B.");
radioButton rdChonC(105, 550, 30, "C.");
radioButton rdChonD(105, 700, 30, "D.");

void ClearStream();

void KeyboardEvent()
{
    if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT))
    {
        ClearStream();
        return;
    }
    static editText *PreEdit = nullptr;
    if (Edit != nullptr)
    {
        if (Edit != PreEdit && PreEdit != nullptr)
        {
            PreEdit->isChoose = false;
            PreEdit->draw();
        }
        PreEdit = Edit;
        Edit->isChoose = true;
        Edit->draw();
        if (curMenu == DISPLAY_LOGIN)
        {

            if (Edit == &taiKhoan)
            {
                Scan(Edit, Edit->textSize, TEXT_NUMBER);
            }

            else if (Edit == &matKhau)
            {
                Scan(Edit, Edit->textSize, SCAN_PASS);
            }
        }
        else if (curMenu == DISPLAY_DSMON)
        {
            if (Edit == &themMaMon)
            {
                Scan(Edit, Edit->textSize, TEXT_NUMBER_NO_SPACE);
            }
            else if (Edit == &themTenMon)
            {
                Scan(Edit, Edit->textSize, TEXT_NUMBER);
            }
            else if (Edit == &timKiemMon)
            {
                Scan(Edit, Edit->textSize, TEXT_NUMBER);
            }
        }
        else if (curMenu == DISPLAY_DSLOP)
        {
            if (Edit == &themMaLop)
            {
                Scan(Edit, Edit->textSize, SCAN_MALOP);
            }
            else if (Edit == &themTenLop)
            {
                Scan(Edit, Edit->textSize, TEXT_NUMBER);
            }
            else if (Edit == &timKiemLop)
            {
                Scan(Edit, Edit->textSize, TEXT_NUMBER);
            }
        }
        else if (curMenu == DISPLAY_DSSV)
        {
            if (Edit == &edMSSV)
            {
                Scan(Edit, Edit->textSize, TEXT_NUMBER_NO_SPACE);
            }
            else if (Edit == &edHoSV)
            {
                Scan(Edit, Edit->textSize, SPACE_TEXT);
            }
            else if (Edit == &edTenSV)
            {
                Scan(Edit, Edit->textSize, SPACE_TEXT);
            }
            else if (Edit == &edtimKiemSV)
            {
                Scan(Edit, Edit->textSize, TEXT_NUMBER);
            }
        }
        else if (curMenu == LUACHON_MON)
        {
            if (Edit == &timKiemMon)
            {
                Scan(Edit, Edit->textSize, TEXT_NUMBER);
            }
        }
        else if (curMenu == LUACHON_LOP)
        {
            if (Edit == &timKiemLop)
            {
                Scan(Edit, Edit->textSize, TEXT_NUMBER);
            }
        }
        else if (curMenu == DISPLAY_DSDIEMGV)
        {
            if (Edit == &edtimKiemSV_R)
            {
                Scan(Edit, Edit->textSize, TEXT_NUMBER);
            }
        }
        else if ( curMenu == DISLPAY_DIEM_THEO_SV) {
            if (Edit == &timKiemLop || Edit == &edtimKiemSV)
            {
                Scan(Edit, Edit->textSize, TEXT_NUMBER);
            }
        }
        else if ( curMenu == DISPLAY_DIEMMON) {
            if (Edit == &timKiemMon)
            {
                Scan(Edit, Edit->textSize, TEXT_NUMBER);
            }
        }
        else if (curMenu == CHUCNANG_CAUHOI)
        {
            if (Edit == &timKiemCauHoi || Edit == &edCauHoi || Edit == &edDapAnA || Edit == &edDapAnB || Edit == &edDapAnC || Edit == &edDapAnD)
            {
                Scan(Edit, Edit->textSize, SCAN_ALL);
            }
        }
        else if (curMenu == DISPLAY_THITHU || curMenu == LUACHON_THI_HS)
        {
            if (Edit == &timKiemMon)
            {
                Scan(Edit, Edit->textSize, TEXT_NUMBER);
            }
            else if (Edit == &edTimeThi || Edit == &edsoCau)
            {
                Scan(Edit, Edit->textSize, ONLY_NUMBER);
            }
        }
        //Giao dien sinh vien
        else if (curMenu == DISPLAY_DOIMK)
        {
            if (Edit == &matKhauCu || Edit == &matKhauMoi || Edit == &nhapLaiMatKhau)
            {
                Scan(Edit, Edit->textSize, SCAN_PASS);
            }
        }
    }
    else
    {
        if (PreEdit != nullptr)
        {
            PreEdit->isChoose = false;
            PreEdit = nullptr;
        }
        ClearStream();
    }
}

void ClearStream()
{
    while (kbhit())
    {
        char c = getch();
    }
}

//Xoa so thap phan du thua. VD: 10.0000000 -> 10
void xoaSoThapPhan(string &s)
{
    for (int i = s.size() - 1; i >= 0; i--)
    {
        if (s[i] == '0')
        {
            s.pop_back();
        }
        else if (s[i] == '.')
        {
            s.pop_back();
            break;
        }
        else
        {
            break;
        }
    }
}

bool FIND(string ChuoiCanTim, string timkiem)
{
    if (timkiem.size() > ChuoiCanTim.size())
    {
        return false;
    }

    for (int i = 0; i < ChuoiCanTim.size(); i++)
    {
        int j = 0;
        if (ChuoiCanTim[i] == timkiem[j])
        {
            int k = i;
            while (ChuoiCanTim[i] == timkiem[j] && j < timkiem.size())
            {
                j++;
                i++;
            }
            if (j == timkiem.size()) {
                return true;
            }
            else {
                i = k;
            }
        }
    }
    return false;
}