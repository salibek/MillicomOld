// �������� �������� �������� � �������������� �����������
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <string>

using namespace std; 

// ���� ����������
const int Tvoid = 0, Tint = 2, Tfloat = 4, Tdouble = 6, Tchar = 8, Tstring = 10, TIP = 12, Tbool = 14, TIC = 16;
const int TPPoint = 18, TGraph=20, TFU=22, TLoad=24;
const int TcharArray = 1002, TintArray = 1004, TfloatArray = 1006, TdoubleArray = 1008, TstringArray = 1010, TIPArray = 1012;
const int TboolArray = 1014, TICArray = 1016, TPPointArray = 1018, TGrapgArray = 1020, TFUArray = 1022, TLoadArray = 1024;
const int TcharArray2 = 2002, TintArray2 = 2004, TfloatArray2 = 2006, TdoubleArray2 = 2008, TstringArray2 = 2010, TIPArray2 = 2012;
const int TboolArray2 = 2014, TICArray2 = 2016, TPPointArray2 = 2018, TGrapgArray2 = 2020, TFUArray2 = 2022, TLoadArray2 = 2024;
// ���� ��������
const int Cvoid = 1, Cint = 3, Cfloat = 5, Cdouble = 7, Cchar = 9, Cstring = 11, CIP = 13, Cbool = 15, CIC = 17;
const int CPPoint = 19, CGraph = 21, CFU = 23, CLoad = 25;
const int CcharArray = 1001, CintArray = 1003, CfloatArray = 1005, CdoubleArray = 1007, CstringArray = 1009, CIPArray = 1011;
const int CboolArray = 1013, CICArray = 1015, CPPointArray = 1017, CGrapgArray = 1019, CFUArray = 1021, CLoadArray = 1023;
const int CcharArray2 = 2001, CintArray2 = 2003, CfloatArray2 = 2005, CdoubleArray2 = 2007, CstringArray2 = 2009, CIPArray2 = 2011;
const int CboolArray2 = 2013, CICArray2 = 2015, CPPointArray2 = 2017, CGrapgArray2 = 2019, CFUArray2 = 2021, CLoadArray2 = 2023;
// ����� ���� ������ (������� �� �������������� ������� �� 2 ���� ���������� ��� ���������)
const int Dvoid=0, Dint = 1, Dfloat = 2, Ddouble = 3, Dchar = 4, Dstring = 5, DIP = 6, Dbool = 7, DIC = 8;
const int DPPoint = 9, DGraph = 10, DFU = 11, DLoad = 12;
const int DcharArray = 501, DintArray = 502, DfloatArray = 503, DdoubleArray = 504, DstringArray = 505, DIPArray = 506;
const int DboolArray = 507, DICArray = 508, DPPointArray = 509, DGrapgArray = 510, DFUArray = 511, DLoadArray = 512;
const int DcharArray2 = 1001, DintArray2 = 1002, DfloatArray2 = 1003, DdoubleArray2 = 1004, DstringArray2 = 1005, DIPArray2 = 1006;
const int DboolArray2 = 1007, DICArray2 = 1008, DPPointArray2 = 1009, DGrapgArray2 = 1010, DFUArray2 = 1011, DLoadArray2 = 1012;

// ���� ��
const int FUBus = 0, FUCons = 1, FUStrGen = 2, FULex = 3, FUList = 4, FUFind = 5;

// ���� �����
const vector<int> w_type = { 10, 30, 40, 50, 60, 70, 20 };

// ����� ��������
const int ProgAtr = -100, Atr=-60, SubMk=900, RepeatMk=901;

bool isIPinIC(void* iP, void* iC); //��������, ��� �� ������ � ��

class LoadPoint
{
	void VectorPrint(unsigned int Type, void* P, void* AtrMnemo, string offset, string Sep, string End, string ArrayBracketStart, string ArrayBracketFin); // ������ �������
	void MatrixPrint(unsigned int Type, void* P, void* AtrMnemo, string offset, string Sep, string End, string ArrayBracketStart, string ArrayBracketFin); // ������ �������
public:
	unsigned int Type = 0; // ����������� ���
	void *Point;
	bool isDigit() { return Type >> 1 == Dint || Type >> 1 == Dchar || Type >> 1 == Dfloat || Type >> 1 == Ddouble; }; // 
	bool isDigitBool() { return Type >> 1 == Dint || Type >> 1 == Dchar || Type >> 1 == Dfloat || Type >> 1 == Ddouble; Type >> 1 == Dbool; }; // ����� ��� ������?
	bool IpTest() { return (Type >> 1 == DIP || Type >> 1 == DIC); } // �������� �� �������� ��?
	bool IsConvert(unsigned int T) {}; // ���� �� ����������� ����������� �������� �� Point � ������������ ���
	void Write(int x);
	void Write(size_t x);
	void Write(double x);
	void Write(float x);
	void Write(bool x);
	void Write(char x);
	void Write(string x);
	void Write(LoadPoint x);
	void Write(vector<double> x);
	void Write(vector<float> x);
	void Write(vector<bool> x);
	void Write(vector<char> x);
	void Write(vector<int> x);

	void Write(void* x) { Point = x; };
	void WriteVar(LoadPoint x) { Point = x.Point; Type = x.Type; Type |= 1; Type--; }; //�������� ������ � ������� �� ����������
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
	void ProgExec(void* Uk, FU* Bus = nullptr, vector<ip>::iterator* Start = nullptr); // ���������� ��������� �� ��
	void ProgExec(LoadPoint Uk, FU* Bus = nullptr, vector<ip>::iterator* Start = nullptr); // ���������� ��������� �� ��
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

void ICDel(void* Uk);// �������� ��

void* ICCopy(LoadPoint uk);// ����������� ��

//void ProgExec(void *Uk, FU* Bus, vector<ip>::iterator *Start=nullptr); // ���������� ��������� �� ��

bool LoadCmp(LoadPoint x, LoadPoint y); // ��������� ���� �������� ��
bool IPCmp(ip* x, ip* y); // ��������� ����  ��
void AtrProgExec(vector<ip>* Prog, int Atr, FU* Bus=nullptr, bool AfterContinue = false); // ����� � �� �� � ��������� Atr � ��������� ��������� ���� �� ���. � ��������, ���� ����� ��������� ��
//void AddOrReplIPAtr(vector<ip>* UK, ip* IP); // 
ip* AtrFind(void* IC, int Atr); // ����� � �� �� � �������� ���������. �� ������ ��������� �� �� ��� NULLL
