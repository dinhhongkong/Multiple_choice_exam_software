//--------------------------------- NGUYEN MAU HAM ---------------------------------
bool Them_Mon_Hoc(ListMonHoc &listMH, Mon_Hoc mh);
void Xoa_Mon_Hoc(ListMonHoc &listMH, string maMH);
void Hieu_Chinh_Mon_Hoc(ListMonHoc &listMH, string maMH);
void Doc_File_Mon_Hoc(ListMonHoc &listMH);
void Luu_File_Mon_Hoc(ListMonHoc listMH);
string Truy_Xuat_Ten_Mon(ListMonHoc listMH, string maMonHoc);
bool KiemTra_MH_TonTai_CH(NodeCauHoi *root, string maMonHoc);

//--------------------------------- DINH NGHIA HAM ---------------------------------
void Doc_File_Mon_Hoc(ListMonHoc &listMH)
{
	ifstream filein;
	filein.open("DATA\\FileDSMon.txt", ios_base::in);
	if (!filein.is_open())
		return;

	filein >> listMH.slmh;
	filein.ignore();
	for (int i = 0; i < listMH.slmh; i++)
	{
		Mon_Hoc mh;
		getline(filein, mh.MAMH, ',');
		getline(filein, mh.TENMH);
		listMH.monHoc[i] = new Mon_Hoc;
		*listMH.monHoc[i] = mh;
	}
	filein.close();
}

void Luu_File_Mon_Hoc(ListMonHoc listMH)
{
	ofstream fileout;
	fileout.open("DATA\\FileDSMon.txt", ios_base::out);
	fileout << listMH.slmh << endl;
	for (int i = 0; i < listMH.slmh; i++)
	{
		fileout << listMH.monHoc[i]->MAMH << "," << listMH.monHoc[i]->TENMH << endl;
	}
	fileout.close();
}

bool Them_Mon_Hoc(ListMonHoc &listMH, Mon_Hoc mh)
{
	for (int i = 0; i < listMH.slmh; i++)
	{
		if (mh.MAMH == listMH.monHoc[i]->MAMH || mh.TENMH == listMH.monHoc[i]->TENMH)
		{
			AllocConsole();
			MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "MA MON hoac TEN MON da ton tai!", "Thong bao", MB_ICONWARNING | MB_OK);
			return false;
		}
	}

	int N = listMH.slmh;
	if (N == MAXMONHOC)
	{
		AllocConsole();
		MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Danh sach mon hoc da day!", "Thong bao", MB_ICONWARNING | MB_OK);
	}
	else
	{
		listMH.monHoc[N] = new Mon_Hoc();
		listMH.slmh++;
		if (N == 0)
		{
			*listMH.monHoc[0] = mh;
		}
		else
		{
			if (mh.MAMH > listMH.monHoc[N - 1]->MAMH)
			{
				*listMH.monHoc[N] = mh;
			}
			else
			{
				for (int i = 0; i < N; i++)
				{
					if (mh.MAMH < listMH.monHoc[i]->MAMH)
					{
						for (int j = N; j > i; j--)
						{
							*listMH.monHoc[j] = *listMH.monHoc[j - 1];
						}
						*listMH.monHoc[i] = mh;
						break;
					}
				}
			}
		}
	}
	AllocConsole();
	MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Them thanh cong", "Thong bao", MB_OK);
	return true;
}

bool KiemTra_MH_TonTai_CH(NodeCauHoi *root, string maMonHoc)
{
	if (root != nullptr)
	{
		if (root->info.maMonHoc == maMonHoc)
			return true;
		if (KiemTra_MH_TonTai_CH(root->left, maMonHoc) || KiemTra_MH_TonTai_CH(root->right, maMonHoc))
			return true;
	}
	return false;
}

bool Hieu_Chinh_Mon_Hoc(NodeCauHoi *r, ListMonHoc &listMH, int index, string maMon, string tenMon)
{
	if (maMon == listMH.monHoc[index]->MAMH && tenMon == listMH.monHoc[index]->TENMH)
	{
		AllocConsole();
		MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Vui long thay doi thong tin mon hoc khi thuc hien hieu chinh!", "Thong bao", MB_ICONASTERISK | MB_OK);
		return false;
	}

	if (KiemTra_MH_TonTai_CH(r, listMH.monHoc[index]->MAMH) && maMon != listMH.monHoc[index]->MAMH)
	{
		AllocConsole();
		MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Mon hoc ton tai cau hoi thi. Khong the thay doi thong tin MA MON!", "Thong bao", MB_ICONWARNING | MB_OK);
		return false;
	}
	Mon_Hoc mh;
	mh.MAMH = maMon;
	mh.TENMH = tenMon;
	for (int i = 0; i < listMH.slmh; i++)
	{
		if (i == index)
		{
			continue;
		}
		if (mh.MAMH == listMH.monHoc[i]->MAMH || mh.TENMH == listMH.monHoc[i]->TENMH)
		{
			AllocConsole();
			MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "MA MON hoac TEN MON da ton tai!", "Thong bao", MB_ICONWARNING | MB_OK);
			return false;
		}
	}
	*listMH.monHoc[index] = mh;
	if (listMH.slmh == 1)
		return true;

	if (index > 0 && mh.MAMH < listMH.monHoc[index - 1]->MAMH)
	{
		for (int i = index - 1; i >= 0; i--)
		{
			if (mh.MAMH > listMH.monHoc[i]->MAMH)
				break;
			swap(*listMH.monHoc[index], *listMH.monHoc[i]);
			index = i;
		}
	}
	else if (index < listMH.slmh - 1 && mh.MAMH > listMH.monHoc[index + 1]->MAMH)
	{
		for (int i = index + 1; i < listMH.slmh; i++)
		{
			if (mh.MAMH < listMH.monHoc[i]->MAMH)
				break;
			swap(*listMH.monHoc[index], *listMH.monHoc[i]);
			index = i;
		}
	}
	AllocConsole();
	MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Hieu chinh thanh cong", "Thong bao", MB_OK);
	return true;
}

bool Xoa_Mon_Hoc(NodeCauHoi *r, ListMonHoc &listMH, int index)
{
	if (KiemTra_MH_TonTai_CH(r, listMH.monHoc[index]->MAMH))
	{
		AllocConsole();
		MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Mon hoc ton tai cau hoi thi. Khong the xoa!", "Thong bao", MB_ICONWARNING | MB_OK);
		return false;
	}
	delete listMH.monHoc[index];
	for (int i = index + 1; i < listMH.slmh; i++)
	{
		listMH.monHoc[i - 1] = listMH.monHoc[i];
	}
	listMH.slmh--;
	AllocConsole();
	MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Xoa thanh cong", "Thong bao", MB_OK);
	return true;
}

string Truy_Xuat_Ten_Mon(ListMonHoc listMH, string maMonHoc)
{
	int left = 0, right = listMH.slmh - 1;
	int middle;
	while (left <= right)
	{
		middle = (left + right) / 2;
		if (listMH.monHoc[middle]->MAMH == maMonHoc)
		{
			return listMH.monHoc[middle]->TENMH;
		}
		if (maMonHoc < listMH.monHoc[middle]->MAMH)
		{
			right = middle - 1;
		}
		else
		{
			left = middle + 1;
		}
	}
	return "";
}