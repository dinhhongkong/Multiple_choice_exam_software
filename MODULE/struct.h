#pragma once
#include <iostream>
using namespace std;

//----------------------------------------------- MON HOC -----------------------------------------------
struct Mon_Hoc
{
	string MAMH;
	string TENMH;
};

struct Danh_Sach_Mon_Hoc
{
	Mon_Hoc *monHoc[MAXMONHOC];
	int slmh = 0;
};
typedef Danh_Sach_Mon_Hoc ListMonHoc;

//----------------------------------------------- CAU HOI -----------------------------------------------
struct CauHoi
{
	int id;
	string maMonHoc;
	string NoiDung;
	string A, B, C, D;
	char DapAn;		   // Dap an: A, B, C or D
	bool used = false; // false: The question haven't been used & true: The question have been used
};

struct NodeCauHoi
{
	int key;
	CauHoi info;
	int height;
	NodeCauHoi *left, *right;
};

struct mangCauHoi
{
	NodeCauHoi **arrCauHoiThi;
	int tongSoCau = 0;
};

//---------------------------------------- CAU HOI THI & BAI THI ----------------------------------------
struct cauHoiThi
{
	CauHoi cauHoiThi;
	char luaChon = '0';
};

struct Bai_Thi
{
	cauHoiThi *arrCauHoi;
	int slcht = 0;
};

//----------------------------------------------- DIEM THI -----------------------------------------------
struct Diem_Thi
{
	string MAMH;
	float Diem;
	Bai_Thi baithi;
};

struct Node_Diem_Thi
{
	Diem_Thi info;
	Node_Diem_Thi *DTnext;
};

struct Danh_Sach_Diem_Thi
{
	Node_Diem_Thi *first = nullptr;
};

//---------------------------------------------- SINH VIEN -----------------------------------------------
struct sinhVien
{
	string mssv;
	string Pass;
	string Ho;
	string Ten;
	int gioiTinh;
	Danh_Sach_Diem_Thi listDT;
};

struct nodeSV
{
	sinhVien info;
	nodeSV *pNext;
};

struct listSV
{
	nodeSV *First = nullptr;
	nodeSV *Last = nullptr;
};

//----------------------------------------------- LOP HOC -----------------------------------------------
struct lop
{
	string MALOP;
	string TENLOP;
	listSV dsSinhVien;
};

struct dslop
{
	lop arrLop[MAXLOP];
	int solop = 0;
};

//---------------------------------------------- RANDOM ID -----------------------------------------------
struct IDRandom
{
	int ID;
	IDRandom *next;
};