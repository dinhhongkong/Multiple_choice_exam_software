//--------------------------------- NGUYEN MAU HAM ---------------------------------
bool KiemTra_TrungDapAn(string A, string B, string C, string D);
bool KiemTra_TrungNoiDung(NodeCauHoi *root, int key, string NoiDung);
int Max(int a, int b);
int ChiSo_ChieuSau(NodeCauHoi *ptr);
int ChiSo_CanBang(NodeCauHoi *ptr);
NodeCauHoi *Tao_Node_Cau_Hoi(int key, CauHoi cauHoiMoi, int height = 1);
NodeCauHoi *Xoay_Trai(NodeCauHoi *&root);
NodeCauHoi *Xoay_Phai(NodeCauHoi *&root);
NodeCauHoi *Node_Cuc_Trai(NodeCauHoi *root);
NodeCauHoi *Them_Cau_Hoi_Moi(NodeCauHoi *&root, int key, CauHoi cauHoiMoi);
NodeCauHoi *Xoa_Cau_Hoi(NodeCauHoi *&root, int key);
bool Hieu_Chinh_Cau_Hoi(NodeCauHoi *&root, int key, CauHoi cauHoiHieuChinh);
void Them_Cau_Hoi_File(NodeCauHoi *&root, NodeCauHoi *cauHoiFile);
void Doc_File_Cau_Hoi(NodeCauHoi *&root, IDRandom *&first);
void Duyet_Luu_Cau_Hoi(NodeCauHoi *p, ofstream &fileout);
void Luu_File_Cau_Hoi(NodeCauHoi *root);
int countNodeCauHoi(NodeCauHoi *root);
void demSoCauTheoMaMon(NodeCauHoi *rootCauHoi, string maMon, int &dem);
void taoMangCauHoi(NodeCauHoi *rootCauHoi, mangCauHoi &dsCauHoi, string maMon);

//--------------------------------- DINH NGHIA HAM ---------------------------------
bool KiemTra_TrungDapAn(string A, string B, string C, string D)
{
	if (A == B || A == C || A == D || B == C || B == D || C == D)
	{
		AllocConsole();
		MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Khong the ton tai cac dap an giong nhau!", "Thong bao", MB_ICONWARNING | MB_OK);
		return true;
	}
	return false;
}

bool KiemTra_TrungNoiDung(NodeCauHoi *root, int key, string NoiDung)
{
	if (root != nullptr)
	{
		if (root->key != key && root->info.NoiDung == NoiDung)
		{
			AllocConsole();
			MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Noi dung cau hoi da ton tai!", "Thong bao", MB_ICONWARNING | MB_OK);
			return true;
		}
		if (KiemTra_TrungNoiDung(root->left, key, NoiDung) || KiemTra_TrungNoiDung(root->right, key, NoiDung))
		{
			return true;
		}
	}
	return false;
}

NodeCauHoi *Tao_Node_Cau_Hoi(int key, CauHoi cauHoiMoi, int height)
{
	NodeCauHoi *ptr = new NodeCauHoi;
	ptr->key = key;
	ptr->left = nullptr;
	ptr->right = nullptr;
	ptr->height = height;
	ptr->info = cauHoiMoi;
	return ptr;
}

int Max(int a, int b)
{
	return (a > b) ? a : b;
}

int ChiSo_ChieuSau(NodeCauHoi *ptr)
{
	if (ptr == nullptr)
		return 0;
	return ptr->height;
}

int ChiSo_CanBang(NodeCauHoi *ptr)
{
	if (ptr == nullptr)
		return 0;
	return ChiSo_ChieuSau(ptr->left) - ChiSo_ChieuSau(ptr->right);
}

NodeCauHoi *Node_Cuc_Trai(NodeCauHoi *root)
{
	while (root->left != nullptr)
		root = root->left;
	return root;
}

NodeCauHoi *Xoay_Trai(NodeCauHoi *&root)
{
	NodeCauHoi *ptr = root;
	if (root != nullptr && root->right != nullptr)
	{
		ptr = root->right;
		root->right = ptr->left;
		ptr->left = root;

		root->height = Max(ChiSo_ChieuSau(root->left), ChiSo_ChieuSau(root->right)) + 1;
		ptr->height = Max(ChiSo_ChieuSau(ptr->left), ChiSo_ChieuSau(ptr->right)) + 1;
	}
	return ptr;
}

NodeCauHoi *Xoay_Phai(NodeCauHoi *&root)
{
	NodeCauHoi *ptr = root;
	if (root != nullptr && root->left != nullptr)
	{
		ptr = root->left;
		root->left = ptr->right;
		ptr->right = root;

		root->height = Max(ChiSo_ChieuSau(root->left), ChiSo_ChieuSau(root->right)) + 1;
		ptr->height = Max(ChiSo_ChieuSau(ptr->left), ChiSo_ChieuSau(ptr->right)) + 1;
	}
	return ptr;
}

NodeCauHoi *Them_Cau_Hoi_Moi(NodeCauHoi *&root, int key, CauHoi cauHoiMoi)
{
	if (root == nullptr)
		return Tao_Node_Cau_Hoi(key, cauHoiMoi);
	if (key < root->key)
	{
		root->left = Them_Cau_Hoi_Moi(root->left, key, cauHoiMoi);
	}
	else
	{
		root->right = Them_Cau_Hoi_Moi(root->right, key, cauHoiMoi);
	}

	root->height = Max(ChiSo_ChieuSau(root->left), ChiSo_ChieuSau(root->right)) + 1;

	int bf = ChiSo_CanBang(root);
	// Left Left case
	if (bf > 1 && key < root->left->key)
	{
		return Xoay_Phai(root);
	}
	// Right Right case
	if (bf < -1 && key > root->right->key)
	{
		return Xoay_Trai(root);
	}
	// Left Right case
	if (bf > 1 && key > root->left->key)
	{
		root->left = Xoay_Trai(root->left);
		return Xoay_Phai(root);
	}
	// Right Left case
	if (bf < -1 && key < root->right->key)
	{
		root->right = Xoay_Phai(root->right);
		return Xoay_Trai(root);
	}
	// Balance case
	return root;
}

NodeCauHoi *Tim_Kiem_Key(NodeCauHoi *root, int key)
{
	while (root != nullptr && root->key != key)
	{
		if (key < root->key)
		{
			root = root->left;
		}
		else
		{
			root = root->right;
		}
	}
	return root;
}

NodeCauHoi *Xoa_Cau_Hoi(NodeCauHoi *&root, int key)
{
	if (root == nullptr)
		return root;
	if (key < root->key)
	{
		root->left = Xoa_Cau_Hoi(root->left, key);
	}
	else if (key > root->key)
	{
		root->right = Xoa_Cau_Hoi(root->right, key);
	}
	else
	{
		if (root->left == nullptr || root->right == nullptr)
		{
			NodeCauHoi *tmp = (root->left == nullptr) ? root->right : root->left;
			// No child case
			if (tmp == nullptr)
			{
				tmp = root;
				root = nullptr;
			}
			else
			{ // One child case
				*root = *tmp;
			}
			delete tmp;
		}
		else
		{ // Two children case
			NodeCauHoi *tmp = Node_Cuc_Trai(root->right);
			root->key = tmp->key;
			root->info = tmp->info;
			root->right = Xoa_Cau_Hoi(root->right, tmp->key);
		}
	}
	// One node case
	if (root == nullptr)
		return root;

	root->height = Max(ChiSo_ChieuSau(root->left), ChiSo_ChieuSau(root->right)) + 1;

	int bf = ChiSo_CanBang(root);
	// Left Left case
	if (bf > 1 && ChiSo_CanBang(root->left) >= 0)
	{
		return Xoay_Phai(root);
	}
	// Left Right case
	if (bf > 1 && ChiSo_CanBang(root->left) < 0)
	{
		root->left = Xoay_Trai(root->left);
		return Xoay_Phai(root);
	}
	// Right Right case
	if (bf < -1 && ChiSo_CanBang(root->right) <= 0)
	{
		return Xoay_Trai(root);
	}
	// Right Left case
	if (bf < -1 && ChiSo_CanBang(root->right) > 0)
	{
		root->right = Xoay_Phai(root->right);
		return Xoay_Trai(root);
	}
	// Balance case
	return root;
}

bool Hieu_Chinh_Cau_Hoi(NodeCauHoi *&root, int key, CauHoi cauHoiHieuChinh)
{
	NodeCauHoi *ptr = Tim_Kiem_Key(root, key);
	if (cauHoiHieuChinh.maMonHoc == ptr->info.maMonHoc && cauHoiHieuChinh.NoiDung == ptr->info.NoiDung && cauHoiHieuChinh.A == ptr->info.A && cauHoiHieuChinh.B == ptr->info.B && cauHoiHieuChinh.C == ptr->info.C && cauHoiHieuChinh.D == ptr->info.D && cauHoiHieuChinh.DapAn == ptr->info.DapAn)
	{
		AllocConsole();
		MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Vui long thay doi thong tin cau hoi khi thuc hien hieu chinh!", "Thong bao", MB_ICONASTERISK | MB_OK);
		return false;
	}
	else if (ptr->info.used == true && ptr->info.maMonHoc != cauHoiHieuChinh.maMonHoc)
	{
		AllocConsole();
		MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Cau hoi da duoc su dung thi. Khong the hieu chinh MA MON!", "Thong bao", MB_ICONWARNING | MB_OK);
		return false;
	}
	else if (!KiemTra_TrungNoiDung(root, key, cauHoiHieuChinh.NoiDung) && !KiemTra_TrungDapAn(cauHoiHieuChinh.A, cauHoiHieuChinh.B, cauHoiHieuChinh.C, cauHoiHieuChinh.D))
	{
		ptr->info.maMonHoc = cauHoiHieuChinh.maMonHoc;
		ptr->info.NoiDung = cauHoiHieuChinh.NoiDung;
		ptr->info.A = cauHoiHieuChinh.A;
		ptr->info.B = cauHoiHieuChinh.B;
		ptr->info.C = cauHoiHieuChinh.C;
		ptr->info.D = cauHoiHieuChinh.D;
		ptr->info.DapAn = cauHoiHieuChinh.DapAn;
		AllocConsole();
		MessageBox(FindWindowA(nullptr, "THI TRAC NGHIEM"), "Hieu chinh thanh cong", "Thong bao", MB_OK);
		return true;
	}
	return false;
}

void Them_Cau_Hoi_File(NodeCauHoi *&ptr, NodeCauHoi *cauHoiFile)
{
	if (ptr == nullptr)
	{
		ptr = cauHoiFile;
	}
	else if (cauHoiFile->key < ptr->key)
	{
		Them_Cau_Hoi_File(ptr->left, cauHoiFile);
	}
	else
	{
		Them_Cau_Hoi_File(ptr->right, cauHoiFile);
	}
}

void Doc_File_Cau_Hoi(NodeCauHoi *&root, IDRandom *&first)
{
	ifstream filein;
	filein.open("DATA\\FileDSCauHoi.txt", ios_base::in);
	if (!filein.is_open())
		return;
	string id, height, used;
	while (getline(filein, id, ','))
	{
		CauHoi cauHoiFile;
		cauHoiFile.id = stoi(id);
		Them_ID(first, cauHoiFile.id);
		getline(filein, cauHoiFile.maMonHoc, ',');
		getline(filein, height, ',');
		getline(filein, used, ',');
		cauHoiFile.used = stoi(used);
		getline(filein, cauHoiFile.NoiDung);
		getline(filein, cauHoiFile.A);
		getline(filein, cauHoiFile.B);
		getline(filein, cauHoiFile.C);
		getline(filein, cauHoiFile.D);
		filein >> cauHoiFile.DapAn;
		filein.ignore();
		Them_Cau_Hoi_File(root, Tao_Node_Cau_Hoi(cauHoiFile.id, cauHoiFile, stoi(height)));
	}
	filein.close();
}

void Duyet_Luu_Cau_Hoi(NodeCauHoi *p, ofstream &fileout)
{
	if (p != nullptr)
	{
		fileout << p->info.id << "," << p->info.maMonHoc << "," << p->height << "," << p->info.used << "," << p->info.NoiDung << endl;
		fileout << p->info.A << endl
				<< p->info.B << endl
				<< p->info.C << endl
				<< p->info.D << endl;
		fileout << p->info.DapAn << endl;
		Duyet_Luu_Cau_Hoi(p->left, fileout);
		Duyet_Luu_Cau_Hoi(p->right, fileout);
	}
}

void Luu_File_Cau_Hoi(NodeCauHoi *root)
{
	ofstream fileout;
	fileout.open("DATA\\FileDSCauHoi.txt", ios_base::out);
	Duyet_Luu_Cau_Hoi(root, fileout);
	fileout.close();
}

int countNodeCauHoi(NodeCauHoi *root)
{
	if (root == nullptr)
	{
		return 0;
	}
	else
	{
		return 1 + countNodeCauHoi(root->left) + countNodeCauHoi(root->right);
	}
}

void demSoCauTheoMaMon(NodeCauHoi *rootCauHoi, string maMon, int &dem)
{
	// Duyet NLR
	if (rootCauHoi != nullptr)
	{
		if (rootCauHoi->info.maMonHoc == maMon)
		{
			dem++;
		}
		demSoCauTheoMaMon(rootCauHoi->left, maMon, dem);
		demSoCauTheoMaMon(rootCauHoi->right, maMon, dem);
	}
}

void taoMangCauHoi(NodeCauHoi *rootCauHoi, mangCauHoi &dsCauHoi, string maMon)
{
	// Duyet NLR
	if (rootCauHoi != nullptr)
	{
		if (rootCauHoi->info.maMonHoc == maMon)
		{
			dsCauHoi.arrCauHoiThi[dsCauHoi.tongSoCau] = rootCauHoi;
			dsCauHoi.tongSoCau++;
		}
		taoMangCauHoi(rootCauHoi->left, dsCauHoi, maMon);
		taoMangCauHoi(rootCauHoi->right, dsCauHoi, maMon);
	}
}