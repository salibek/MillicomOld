// �������� �������� �������� � �������������� �����������
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <string>
//#include "LocationTable.h"

using namespace std;

// ���� ����������
const int Tvoid = 0, Tbool = 2, Tchar = 4, Tint = 6, Tfloat = 8, Tdouble = 10,  Tstring = 12, TIP = 14, TIC = 16;
const int TPPoint = 18, TGraph=20, TFU=22, TLoad=24;
const int TvoidArray = 1000, TboolArray = 1002, TCharArray=1004, TintArray = 1006, TfloatArray = 1008, TdoubleArray = 1010, TstringArray = 1012;
const int TIPArray = 1014, TICArray = 1016, TPPointArray = 1018, TGrapgArray = 1020, TFUArray = 1022, TLoadArray = 1024;
const int TboolArray2 = 2002, TcharArray2 = 2004, TintArray2 = 2006, TfloatArray2 = 2008, TdoubleArray2 = 2010, TstringArray2 = 2012;
const int TIPArray2 = 2014, TICArray2 = 2016, TPPointArray2 = 2018, TGrapgArray2 = 2020, TFUArray2 = 2022, TLoadArray2 = 2024;
// ���� ��������
const int Cvoid = 1, Cbool = 3, Cchar = 5, Cint = 7, Cfloat = 9, Cdouble = 11, Cstring = 13, CIP = 15, CIC = 17;
const int CPPoint = 19, CGraph = 21, CFU = 23, CLoad = 25;
const int CvoidArray = 1001, CboolArray=1003, CcharArray = 1005, CintArray = 1007, CfloatArray = 1009, CdoubleArray = 1011, CstringArray = 1013;
const int CIPArray = 1015, CICArray = 1017, CPPointArray = 1019, CGrapgArray = 1021, CFUArray = 1023, CLoadArray = 1025;
const int CvoidArray2 = 2001, CboolArray2 = 2003, CcharArray2 = 2005, CintArray2 = 2007, CfloatArray2 = 2009, CdoubleArray2 = 2011, CstringArray2 = 2013;
const int CIPArray2 = 2015, CICArray2 = 2017, CPPointArray2 = 2019, CGrapgArray2 = 2021, CFUArray2 = 2023, CLoadArray2 = 2025;
// ����� ���� ������ (������� �� �������������� ������� �� 2 ���� ���������� ��� ���������)
const int Dvoid=0, Dbool = 1, Dchar = 2, Dint = 3, Dfloat = 4, Ddouble = 5, Dstring = 6, DIP = 7,  DIC = 8;
const int DPPoint = 9, DGraph = 10, DFU = 11, DLoad = 12;
const int DVoidArray = 500, DboolArray = 501, DcharArray = 502, DintArray = 503, DfloatArray = 504, DdoubleArray = 505, DstringArray = 506;
const int DIPArray = 507, DICArray = 508, DPPointArray = 509, DGrapgArray = 510, DFUArray = 511, DLoadArray = 512;
const int DvoidArray2 = 1000, DboolArray2 = 1001, DcharArray2 = 1002, DintArray2 = 1003, DfloatArray2 = 1004, DdoubleArray2 = 1005, DstringArray2 = 1006;
const int DIPArray2 = 1007, DICArray2 = 1008, DPPointArray2 = 1009, DGrapgArray2 = 1010, DFUArray2 = 1011, DLoadArray2 = 1012;

// ���� ��
const int FUBus = 0, FUCons = 1, FUStrGen = 2, FULex = 3, FUList = 4, FUFind = 5;

// ���� �����
const vector<int> w_type = { 10, 30, 40, 50, 60, 70, 20 };

// ����� ��������
const int ProgAtr = -100, Atr=-60, SubMk=900, RepeatMk=901;
const int ListLine = -80, ListSub = -90; // �������� ����� ������ � ���������

bool isIPinIC(void* iP, void* iC); //��������, ��� �� ������ � ��

class LoadPoint
{
	void VectorPrint(unsigned int Type, void* P, void* AtrMnemo, string offset, string Sep, string End, string ArrayBracketStart, string ArrayBracketFin); // ������ �������
	void MatrixPrint(unsigned int Type, void* P, void* AtrMnemo, string offset, string Sep, string End, string ArrayBracketStart, string ArrayBracketFin); // ������ �������
public:
	unsigned int Type = 0; // ����������� ���
	void *Point;
	bool isDigit(int type = -1) { int t = type < 0 ? Type : type;  return t >> 1 == Dint || t >> 1 == Dchar || t >> 1 == Dfloat || t >> 1 == Ddouble; }; // 
	bool isDigitBool(int type=-1) { int t = type < 0 ? Type : type; return t >> 1 == Dint || t >> 1 == Dchar || t >> 1 == Dfloat || t >> 1 == Ddouble; t >> 1 == Dbool; }; // ����� ��� ������?
	bool IpTest() { return (Type >> 1 == DIP || Type >> 1 == DIC); } // �������� �� �������� ��?
	bool IsConvert(unsigned int T) {}; // ���� �� ����������� ����������� �������� �� Point � ������������ ���
	int Write(int x); // return 0 - ���������� ������, 1 - ������������� �����
	int Write(size_t x);
	int Write(double x);
	int Write(float x);
	int Write(bool x);
	int Write(char x);
	int Write(string x);
	int Write(LoadPoint x);
	int WriteByLoad(LoadPoint x); // �������� �������� �� ��������
	void Write(vector<double> x);
	void Write(vector<float> x);
	void Write(vector<bool> x);
	void Write(vector<char> x);
	void Write(vector<int> x);

	void Write(void* x) { Point = x; };
	void WriteVar(LoadPoint x);// { Point = x.Point; Type = x.Type; Type |= 1; Type--; }; //�������� ������ � ������� �� ����������
	void WriteConst(LoadPoint x) {Point = x.Point; Type = x.Type; Type |= 1;}; // �������� ������ � ������� �� ����������

	string ToStr(string define=""); // ������ � string
	bool ToBool(bool define = false); // ������� � bool
	int ToInt(int define=0); // ������� � integer
	double ToDouble(double define=0); // ������� � double
	float ToFloat(float define=0);// ������� �� float
	char ToChar() { return Point == nullptr ? 0 : *(char*)Point; }; // ������� � integer
	void Copy(LoadPoint *LP);
	void Clear(); // ����� �������� ��
	void VarClear(); // ����� �������� �� � ��� ����� � � ���������� (���������� ���������)
	void* VarClone(); // ����������� �������� ��������
	void VarDel();// �������� �������� ��
	void print(void* AtrMnemo=nullptr, string offset="", string Sep = "", string End = "\n", string ArrayBracketStart = "[", string ArrayBracketFin = "]"); // �������� - ��������� �� ����. �������� ���������
	LoadPoint Clone(); // ����������� ��������
	void ConstTypeSet(bool F = true) { if (F)Type |= 1; else VarTypeSet(); }; // ���������� ��� '���������'
    // ���������� ��� '����������'
	void VarTypeSet(bool F = true) {
		if (!F) { ConstTypeSet(); return; } Type |= 1; Type -= 1;}
	LoadPoint IpOut() // ������������ ��������� �� �� ��� �� ������ �� �� ��, ����� null
	{
		if (Type >> 1 == DIP) return *this;
//		if (Type >> 1 == DIC) return { DIP,((IC_type)Point)->begin()._Ptr};
//		return { 0,nullptr };
	};

};

// struct TAtrMnemo

class ip // �������������� ����
{
public:
	int atr = 0;
	LoadPoint Load = {0, nullptr }; // ��������� �� �������� � ����� �������
	~ip() { }//Load.Clear(); };
	void copy(ip *IP)// ����������� ��
	{
		atr = IP->atr;
		Load.Point = IP->Load.Point;
		Load.Type = IP->Load.Type;
	};
	void copy(void *IP) { copy(*(ip*)IP); }// ����������� ��
	void copy(ip &IP)// ����������� ��
	{
		atr = IP.atr;
		Load.Copy(&IP.Load);
	};
	void copy(LoadPoint &LP)// ����������� ��
	{
		switch (LP.Type >> 1)
		{
		case DIP:
			atr = ((ip*)LP.Point)->atr;
			Load.Copy(&((ip*)LP.Point)->Load);
			break;
		case DIC:
			atr = ((vector<ip>*)LP.Point)->begin()->atr;
			Load.Copy(&((vector<ip>*)LP.Point)->begin()->Load);
		}
	};
	ip* �lone()
	{
		ip* ip_new = new ip;
		ip_new->copy(*this);
		return ip_new;
	};

	vector<ip>* �loneToIC()
	{
		vector<ip>* t = new vector<ip>;
		t->push_back(*this);
		return t;
	};

};

typedef  vector<vector<ip>*> ICVect;
typedef  vector<ip>* IC_type;

struct deletedIC //��������� ��
{
	vector<ip*>* IC; // �������������� �������, ���������� ��������� ��
	void* programm; // ��������� �� ������������� (��, ���������� ����� �����������)
};

class FUModeling
{
public:
	bool SchedulerFlag = false; // ���� ������� �� ��������������
	vector<ip> qmk; // ������� �� ��� �������������
	bool ManualMode = false; // ����� ������� ���������� (��� �������������)
	map<int, double> MkTime; // ����� ���������� �������� (��� �������������)
//	int CoreFreeMK; // �� ������������ ���� ��� ������������ ����������
	void* scheduler = nullptr; // ��������� �� �������� ������������ ����������
//	double Dtime = 0; // ����� ���������� ������� �������
};

class Tread { // �������������� ����
	double accum = 0; // �����������
	double* P_accum = &accum; // ������ �� �����������
	
};

class FU {  // ���� ��������������� ����������
public:
	virtual void ProgFU(int MK, LoadPoint Load) {}; // ���������� ������ ������ ��
//	virtual void ProgFU(LoadPoint MK, LoadPoint Load)
//	{ if ((MK.Type >> 1) == Dint) ProgFU(Load.ToInt(), Load); }; // ���������� ������ ������ ��
	void Scheduling(); // ������ �� ����� ����������� ������������
	int FUtype = 0; // ��� ��
	string FUName; //  ��� ��
//	int MkStage = 0; // ������ ���������� ������������ (����� �� ����������� �� ��������� ������)
	bool Active = true;

	FUModeling *Modeling=nullptr; // �������������

	FU() { Bus = nullptr; };
	FU(FU *BusContext) { Bus = BusContext; };

	void MkExec(int MK, LoadPoint Load, FU* BusContext = nullptr); // ��������� ���� ������������ 
	void MkExec(LoadPoint MK, LoadPoint Load, FU* BusContext = nullptr); // ������ �� � ���������
	void ProgExec(LoadPoint UK, FU* Bus = nullptr, vector<ip>::iterator* Start = nullptr); // ���������� ��������� �� ��
	int SubAtr=SubMk; // ������� ����� � ������������

	FU *Bus; // ������ �� �������� ����
	int FUMkRange = 1000; // �������� �� ��� ������� ��
	int ProgStop = 0; // ���� ��������� ���������, ����������� ProgExec
	bool ProgStopAll = false; // ���� ��������� ���� ���������� �� ���������� �������������� ��� ������� ��
//	bool RepeatFlag = false; // ���� ���������� ���������
	void CommonMk(int Mk, LoadPoint Uk); // ���������� ����� �� ��� ��
	IC_type PrefixProg = nullptr, PostfixProg = nullptr, Prog = nullptr, ElseProg = nullptr; // ��������� ���������� � ������������ �� ����� ������� ��, ������ ���������, �������������� ���������
private:
//	int ProgSetFaze = 0; // ���� ��� ��������� ��������� ProgSet, ElseProgSet
};

//void GraphDel(void* Uk, LocatTable* Table = nullptr); // �������� ��-�����
void ICDel(void* Uk);// �������� ��

void* ICCopy(LoadPoint uk);// ����������� ��

//void ProgExec(void *Uk, FU* Bus, vector<ip>::iterator *Start=nullptr); // ���������� ��������� �� ��

bool LoadCmp(LoadPoint x, LoadPoint y); // ��������� ���� �������� ��
bool IPCmp(ip* x, ip* y); // ��������� ����  ��
void AtrProgExec(vector<ip>* Prog, int Atr, FU* Bus=nullptr, bool AfterContinue = false); // ����� � �� �� � ��������� Atr � ��������� ��������� ���� �� ���. � ��������, ���� ����� ��������� ��
//void AddOrReplIPAtr(vector<ip>* UK, ip* IP); // 
ip* AtrFind(void* IC, int Atr); // ����� � �� �� � �������� ���������. �� ������ ��������� �� �� ��� NULLL
