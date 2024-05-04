//--------------------------------- NGUYEN MAU HAM ---------------------------------
void Them_Diem_Vao_Cuoi(Danh_Sach_Diem_Thi& dsDiem, Node_Diem_Thi* nodeDiemThi);
void Them_Diem_Vao_Dau(Danh_Sach_Diem_Thi& dsDiem, Node_Diem_Thi* nodeDiemThi);

//--------------------------------- DINH NGHIA HAM ---------------------------------
void Them_Diem_Vao_Cuoi(Danh_Sach_Diem_Thi& dsDiem, Node_Diem_Thi* nodeDiemThi) {
	if (dsDiem.first == nullptr) {
		dsDiem.first = nodeDiemThi;
	}
	else {
		Node_Diem_Thi* ptr = dsDiem.first;
		while (ptr->DTnext != nullptr) {
			ptr = ptr->DTnext;
		}
		ptr->DTnext = nodeDiemThi;
	}
}

void Them_Diem_Vao_Dau(Danh_Sach_Diem_Thi& dsDiem, Node_Diem_Thi* nodeDiemThi) {
	if (dsDiem.first == nullptr) {
		dsDiem.first = nodeDiemThi;
	}
	else {
		nodeDiemThi->DTnext = dsDiem.first;
		dsDiem.first = nodeDiemThi;
	}
}