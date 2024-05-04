//--------------------------------- NGUYEN MAU HAM ---------------------------------
nodeSV *CreateNodeSV(sinhVien sv);
void AddLast(listSV &l, nodeSV *sv);
void AddFirst(listSV &l, nodeSV *sv);
bool InsertNodeSV(dslop DanhSachLop, listSV &l, sinhVien sv);
bool ChinhSuaSinhVien(dslop DanhSachLop, listSV &DsSinhVien, nodeSV *&nodeHieuChinh, nodeSV *&PreNodeHieuChinh, string Mssv, string Ho, string Ten, int GioiTinh);
bool xoaSinhVien(listSV &DsSinhVien, nodeSV *&sv);
void thayDoiMK(nodeSV *&sv, string matKhauMoi);
int SizeListSV(listSV l);
void DocDsSinhVien(listSV &dsSinhVien, string maLop);
void ghiFileDsSinhVien(listSV &dsSinhVien, string maLop);

//--------------------------------- DINH NGHIA HAM ---------------------------------
nodeSV *CreateNodeSV(sinhVien sv)
{
	nodeSV *a = new nodeSV;
	a->info = sv;
	a->pNext = nullptr;
	return a;
}

void AddLast(listSV &l, nodeSV *sv)
{
	if (l.First == nullptr)
	{
		l.First = sv;
		l.Last = sv;
	}
	else
	{
		l.Last->pNext = sv;
		l.Last = sv;
	}
}

void AddFirst(listSV &l, nodeSV *sv)
{
	if (l.First == nullptr)
	{
		l.First = sv;
		l.Last = sv;
	}
	else
	{
		sv->pNext = l.First;
		l.First = sv;
	}
}

bool InsertNodeSV(dslop DanhSachLop, listSV &l, sinhVien sv)
{
	nodeSV *node = nullptr;
	for (int i = 0; i < DanhSachLop.solop; i++)
	{
		node = DanhSachLop.arrLop[i].dsSinhVien.First;

		while (node != nullptr)
		{
			if (node->info.mssv == sv.mssv)
			{
				AllocConsole();
				MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "MA SO SINH VIEN da ton tai!", "Thong bao", MB_ICONWARNING | MB_OK);
				return false;
			}
			node = node->pNext;
		}
	}

	if (l.First == nullptr)
	{
		AddFirst(l, CreateNodeSV(sv));
		AllocConsole();
		MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Them thanh cong", "Thong bao", MB_OK);
		return true;
	}

	if (l.First->info.mssv > sv.mssv)
	{
		nodeSV *p = new nodeSV;
		p->info = sv;
		p->pNext = l.First;
		l.First = p;
		AllocConsole();
		MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Them thanh cong", "Thong bao", MB_OK);
		return true;
	}

	if (l.Last->info.mssv < sv.mssv)
	{
		AddLast(l, CreateNodeSV(sv));
		AllocConsole();
		MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Them thanh cong", "Thong bao", MB_OK);
		return true;
	}

	nodeSV *temp = l.First;
	while (temp != nullptr)
	{
		if (temp->pNext->info.mssv > sv.mssv)
		{
			nodeSV *chenSV = CreateNodeSV(sv);

			chenSV->pNext = temp->pNext;
			temp->pNext = chenSV;
			AllocConsole();
			MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Them thanh cong", "Thong bao", MB_OK);
			return true;
		}
		temp = temp->pNext;
	}
	return false;
}

bool ChinhSuaSinhVien(dslop DanhSachLop, listSV &DsSinhVien, nodeSV *&nodeHieuChinh, nodeSV *&PreNodeHieuChinh, string Mssv, string Ho, string Ten, int GioiTinh)
{

	if (nodeHieuChinh->info.mssv == Mssv && nodeHieuChinh->info.Ho == Ho && nodeHieuChinh->info.Ten == Ten && nodeHieuChinh->info.gioiTinh == GioiTinh)
	{
		AllocConsole();
		MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Vui long thay doi thong tin sinh vien khi thuc hien hieu chinh!", "Thong bao", MB_ICONASTERISK | MB_OK);
		return false;
	}

	nodeSV *node = DsSinhVien.First;
	for (int i = 0; i < DanhSachLop.solop; i++)
	{
		node = DanhSachLop.arrLop[i].dsSinhVien.First;
		if (Mssv != nodeHieuChinh->info.mssv)
		{
			while (node != nullptr)
			{
				if (node == nodeHieuChinh)
				{

					node = nodeHieuChinh->pNext;
					continue;
				}

				if (node->info.mssv == Mssv)
				{
					AllocConsole();
					MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "MA SO SINH VIEN da ton tai!", "Thong bao", MB_ICONWARNING | MB_OK);
					return false;
				}
				node = node->pNext;
			}
		}
	}
	string oldname = "DATA\\bai thi\\" + nodeHieuChinh->info.mssv + ".txt";

	nodeHieuChinh->info.mssv = Mssv;
	nodeHieuChinh->info.Ho = Ho;
	nodeHieuChinh->info.Ten = Ten;
	nodeHieuChinh->info.gioiTinh = GioiTinh;
	if (DsSinhVien.First == DsSinhVien.Last)
	{
		return true;
	}

	if (PreNodeHieuChinh == nullptr)
	{
		if (nodeHieuChinh->pNext == nullptr)
		{
			DsSinhVien.First = nullptr;
			DsSinhVien.Last = nullptr;
		}
		else
		{
			DsSinhVien.First = nodeHieuChinh->pNext;
		}
	}
	else if (PreNodeHieuChinh != nullptr)
	{

		PreNodeHieuChinh->pNext = nodeHieuChinh->pNext;

		if (nodeHieuChinh == DsSinhVien.Last)
		{
			DsSinhVien.Last = PreNodeHieuChinh;
		}
	}
	nodeHieuChinh->pNext = nullptr;

	if (DsSinhVien.First->info.mssv > nodeHieuChinh->info.mssv)
	{
		nodeHieuChinh->pNext = DsSinhVien.First;
		DsSinhVien.First = nodeHieuChinh;
		return true;
	}

	if (DsSinhVien.Last->info.mssv < nodeHieuChinh->info.mssv)
	{
		DsSinhVien.Last->pNext = nodeHieuChinh;
		DsSinhVien.Last = nodeHieuChinh;
		return true;
	}

	nodeSV *temp = DsSinhVien.First;
	while (temp != nullptr)
	{
		if (temp->pNext->info.mssv > nodeHieuChinh->info.mssv)
		{
			nodeHieuChinh->pNext = temp->pNext;
			temp->pNext = nodeHieuChinh;
			return true;
		}
		temp = temp->pNext;
	}
	string newname = "DATA\\bai thi\\" + nodeHieuChinh->info.mssv + ".txt";
	rename(&oldname[0], &newname[0]);
	return true;
}

bool xoaSinhVien(listSV &DsSinhVien, nodeSV *&sv)
{
	if (sv->info.listDT.first != nullptr)
	{
		AllocConsole();
		MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Sinh vien da thuc hien thi. Khong the xoa!", "Thong bao", MB_ICONWARNING | MB_OK);
		return false;
	}

	if (DsSinhVien.First == DsSinhVien.Last)
	{
		DsSinhVien.First = nullptr;
		DsSinhVien.Last = nullptr;
		delete sv;
		sv = nullptr;
	}
	else if (sv == DsSinhVien.First)
	{
		DsSinhVien.First = sv->pNext;
		sv->pNext = nullptr;
		delete sv;
		sv = nullptr;
	}
	else if (sv != DsSinhVien.Last)
	{
		nodeSV *node = DsSinhVien.First;
		while (node->pNext != sv)
		{
			node = node->pNext;
		}
		node->pNext = sv->pNext;
		sv->pNext = nullptr;
		delete sv;
		sv = nullptr;
	}
	else if (sv == DsSinhVien.Last)
	{
		nodeSV *node = DsSinhVien.First;
		while (node->pNext != sv)
		{
			node = node->pNext;
		}
		DsSinhVien.Last = node;
		DsSinhVien.Last->pNext = nullptr;
		sv->pNext = nullptr;
		delete sv;
		sv = nullptr;
	}
	AllocConsole();
	MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Xoa thanh cong", "Thong bao", MB_OK);

	return true;
}

void thayDoiMK(nodeSV *&sv, string matKhauMoi)
{
	sv->info.Pass = matKhauMoi;
}

// Dem so luong SV trong danh sach
int SizeListSV(listSV l)
{
	int count = 0;
	nodeSV *node = l.First;
	while (node != NULL)
	{
		count++;
		node = node->pNext;
	}
	return count;
}

void DocDsSinhVien(listSV &dsSinhVien, string maLop)
{
	ifstream fileIn;
	string nameFILE = "DATA\\FileDSSinhVien\\" + maLop + ".txt";
	fileIn.open(nameFILE, ios_base::in);
	if (!fileIn.is_open())
	{
		return;
	}

	sinhVien sv;
	while (getline(fileIn, sv.mssv, ','))
	{
		getline(fileIn, sv.Ho, ',');
		getline(fileIn, sv.Ten, ',');
		fileIn >> sv.gioiTinh;
		fileIn.ignore();
		getline(fileIn, sv.Pass, '\n');
		docBaiThi(sv.mssv, sv.listDT);
		AddLast(dsSinhVien, CreateNodeSV(sv));
	}
	fileIn.close();
}

void ghiFileDsSinhVien(listSV &dsSinhVien, string maLop)
{
	ofstream fileOut;
	string nameFILE = "DATA\\FileDSSinhVien\\" + maLop + ".txt";
	fileOut.open(nameFILE, ios_base::out);
	nodeSV *temp = dsSinhVien.First;
	while (temp != nullptr)
	{
		fileOut << temp->info.mssv << ',' << temp->info.Ho << ','
				<< temp->info.Ten << ',' << temp->info.gioiTinh << ',' << temp->info.Pass << '\n';

		temp = temp->pNext;
	}
	fileOut.close();
}