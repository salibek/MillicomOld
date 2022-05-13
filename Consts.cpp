#include "stdafx.h"
#include "Consts.h"
#include <iostream>
#include <string>
#include "LocationTable.h"
#include "ALU.h"

using namespace std;

bool LoadPoint::isIC() 
{
	set<unsigned int> IC_Types = {DIC}; // ���������� ����� �� � ��-������
	return IC_Types.count(Type>>1);
}

string LoadPoint::ToStr(string define) // ������� � bool
{
	if (Point == nullptr)
		return define;
	switch (Type >> 1)
	{
	case Dstring: return *((string*)Point);
	case Ddouble: return to_string(*(double*)Point); break;
	case Dfloat: return to_string(*(float*)Point); break;
	case Dint: return to_string(*(int*)Point); break;
	case Dbool: return to_string(*(bool*)Point); break;
	default:
		return "";
		break;
	}
}

bool LoadPoint::ToBool(bool define) // ������� � bool (�� ��������� false)
{
	if (Point == nullptr)
		return define;
	switch (Type >> 1)
	{
	case Ddouble: return *(double*)Point;
	case Dfloat: return *(float*)Point;
	case Dint: return *(int*)Point;
	case Dbool: return *(bool*)Point;
	case Dstring: return !((*(string*)Point) == "");
	default:
		return false;
	}
}

int LoadPoint::ToInt(int define) { // ������� � integer
	if (Point == nullptr)
		return define;
	switch (Type >> 1)
	{
	case Ddouble: return (int)*(double*)Point; break;
	case Dfloat: return (int)*(float*)Point; break;
	case Dint: return *(int*)Point; break;
	case Dbool: return *(bool*)Point; break;
	case Dstring: return atoi((*(string*)Point).c_str());
	default:
		return 0;
		break;
	}
}
double LoadPoint::ToDouble(double define) {// ������� � integer
	if (Point == nullptr) return define;
	switch (Type >> 1)
	{
	case Ddouble: return *(double*)Point; break;
	case Dfloat: return *(float*)Point; break;
	case Dint: return *(int*)Point; break;
	case Dbool: return *(bool*)Point; break;
	case Dstring: return atof((*(string*)Point).c_str());
	default:
		return 0;
		break;
	}
}

float LoadPoint::ToFloat(float define) {// ������� � integer
	if (Point == nullptr)
		return define;
	switch (Type >> 1)
	{
	case Ddouble: return *(double*)Point; break;
	case Dfloat: return *(float*)Point; break;
	case Dint: return *(int*)Point; break;
	case Dbool: return *(bool*)Point; break;
	case Dstring: return atof((*(string*)Point).c_str());
	default:
		return 0;
		break;
	}
};
// ������ � �������� ��
void LoadPoint::Write(vector<double> x) // ����������� �������
{
	if (Type == CdoubleArray)
		*(vector<double>*)Point = x;
}
void LoadPoint::Write(vector<float> x) // ����������� �������
{
	if (Type == CdoubleArray)
		*(vector<float>*)Point = x;
}
void LoadPoint::Write(vector<bool> x) // ����������� �������
{
	if (Type == CdoubleArray)
		*(vector<bool>*)Point = x;
}
void LoadPoint::Write(vector<char> x) // ����������� �������
{
	if (Type == CdoubleArray)
		*(vector<char>*)Point = x;
}
void LoadPoint::Write(vector<int> x) // ����������� �������
{
	if (Type == CdoubleArray)
		*(vector<int>*)Point = x;
}
// -----

int LoadPoint::WriteFromLoad(LoadPoint Load) // �������� �������� �� ��������
{
	switch (Type)
	{
	case Tdouble:
		*((double*)Point) = Load.ToDouble();
		break;
	case Tfloat:
		*((float*)Point) = Load.ToFloat();
		break;
	case Tint:
		*((int*)Point) = Load.ToInt();
		break;
	case Tbool:
		*((bool*)Point) = Load.ToBool();
		break;
	case Tchar:
		*((char*)Point) = Load.ToChar();
		break;
	default: // ���������� ���������
		if (Type % 2 != 0) // ���� ��� ����������
			return 2; // ������: ������� ������ � ���������
		else
			if (Type >> 1 != Load.Type >> 1)
				return 1; // ������: ������������� �����
			else
				Point = Load.Point;
	}
	return 0;
}

int LoadPoint::Write(size_t x)
{
	switch (Type)
	{
	case Tdouble:
		*((double*)Point) = x;
		break;
	case Tfloat:
		*((float*)Point) = x;
		break;
	case Tint:
		*((int*)Point) = x;
		break;
	case Tbool:
		*((bool*)Point) = x;
		break;
	case Tchar:
		*((char*)Point) = x;
		break;
	default:
		return 2; // �������������� �����
	}
	return 0;
}

int LoadPoint::Write(int x)
{
	switch (Type)
	{
	case Tdouble:
		*((double*)Point) = x;
		break;
	case Tfloat:
		*((float*)Point) = x;
		break;
	case Tint:
		*((int*)Point) = x;
		break;
	case Tbool:
		*((bool*)Point) = x;
		break;
	case Tchar:
		if (x >= 0 && x < 256)
			*((char*)Point) = x;
		else
			return 1; // �������������� �����
		break;
	defoult:
		return 1; // �������������� �����
	}
	return 0;
}

int LoadPoint::Write(double x)
{
	switch (Type)
	{
	case Tdouble:
		*((double*)Point) = x;
		break;
	case Tfloat:
		*((float*)Point) = x;
		break;
	case Tint:
		*((int*)Point) = x;
		break;
	case Tbool:
		*((bool*)Point) = x;
		break;
	case Tchar:
		*((char*)Point) = x;
		break;
	defoult:
		return 1; // �������������� �����
	}
	return 0;
}

int LoadPoint::Write(float x)
{
	switch (Type)
	{
	case Tdouble:
		*((double*)Point) = x;
		break;
	case Tfloat:
		*((float*)Point) = x;
		break;
	case Tint:
		*((int*)Point) = x;
		break;
	case Tbool:
		*((bool*)Point) = x;
		break;
	case Tchar:
		*((char*)Point) = x;
		break;
	defoult:
		return 1; // �������������� �����
	}
	return 0;
}

int LoadPoint::Write(bool x)
{
	switch (Type)
	{
	case Tdouble:
		*((double*)Point) = x;
		break;
	case Tfloat:
		*((float*)Point) = x;
		break;
	case Tint:
		*((int*)Point) = x;
		break;
	case Tbool:
		*((bool*)Point) = x;
		break;
	case Tchar:
		*((char*)Point) = x;
		break;
	defoult:
		return 1; // �������������� �����
	}
	return 0;
}

int LoadPoint::Write(char x)
{
	switch (Type)
	{
	case Tdouble:
		*((double*)Point) = x;
		break;
	case Tfloat:
		*((float*)Point) = x;
		break;
	case Tint:
		*((int*)Point) = x;
		break;
	case Tbool:
		*((bool*)Point) = x;
		break;
	case Tchar:
		*((char*)Point) = x;
		break;
	defoult:
		return 1; // �������������� �����
	}
	return 0;
}

int LoadPoint::Write(string x)
{
	switch (Type)
	{
	case Tstring:
		*((string*)Point) = x;
		break;
	defoult:
		return 1; // �������������� �����
	}
	return 0;
}

int LoadPoint::Write(LoadPoint x) // �������� �������� �� ��������
{
	switch (Type)
	{
	case TLoad:
		if (x.Type >> 1 != DLoad)
			return 1;
		*(LoadPoint*)Point = *(LoadPoint*)x.Point;
		break;
	case Tstring:
		if (x.Type >> 1 != Dstring)
			return 1;
		*(string*)Point = *(string*)x.Point;	
	case Tdouble:
		if (!x.isDigitBool())
			return 1;
		*((double*)Point) = x.ToDouble();
		break;
	case Tfloat:
		if (!x.isDigitBool())
			return 1;
		*((float*)Point) = x.ToFloat();
		break;
	case Tint:
		if(x.Type>>1==Dint || x.Type >> 1 == Dbool || x.Type >> 1 == Dchar)
			*((int*)Point) = x.ToInt();
		else return 1;
		break;
	case Tbool:
		if (!x.isDigitBool() || x.Type >> 1 == Dstring)
			*((bool*)Point) = x.ToBool();
		else return 1;
		break;
	case Tchar:
		if(x.Type >> 1 == Dchar || x.Type >> 1 == Dbool ||
			x.Type >> 1 == Dint && *(int*)x.Point>=0 && *(int*)x.Point <256)
		*((char*)Point) = x.ToChar();
		break;

	defoult:
		WriteFromLoad(x); // ������� �������� �� ��������
	}
	return 0;
}

LoadPoint LoadPoint::Clone() // ������� ������������� ��������
{
	switch (Type >> 1)
	{
	case Dstring: return { Type, new string(*(string*)Point) };
	case Dint: return { Type, new int(*(int*)Point) };
	case Dfloat: return { Type, new float(*(float*)Point) };
	case Ddouble: return { Type,new double(*(double*)Point) };
	case Dchar: return { Type,new char(*(char*)Point) };
	case Dbool: return { Type,new bool(*(bool*)Point) };
	case DPPoint: return { Type,new (void*)(*(void**)Point) };
	case DIC: return { Type, ICCopy(*this) };
	case DIP: //return { Type, (*(ip*)Point).�lone() };
	{
		vector<ip>* t = new vector<ip>;
		t->push_back(*((ip*)Point));
		//		((ip*)Point)->Load.Clone();
		return { Type, t };
	}
	default: return *this;
	}
}

void* LoadPoint::VarClone() // ������� ������ �� ������������� �������� �� ��������
{
	switch (Type >> 1)
	{
	case Dstring: return new string(*(string*)Point);
	case Dint: return new int(*(int*)Point);
	case Dfloat: return new float(*(float*)Point);
	case Ddouble: return new double(*(double*)Point);
	case Dchar: return new char(*(char*)Point);
	case Dbool: return new bool(*(bool*)Point);
	case DPPoint: return new (void*)(*(void**)Point);
	case DIP: {IC_type t = new vector<ip>; t->push_back(*(ip*)Point); return t; }
	case DIC: return ICCopy(*this);
	}
}

void LoadPoint::VarDel() // �������� �������� ��
{
	if (Point == nullptr)
		return;
	switch (Type >> 1)
	{
	case Dstring: delete (string*)Point; break;
//	case Dint: delete (int*)Point; break;
	case Dfloat: delete (float*)Point; break;
//	case Ddouble: delete (double*)Point; break;
	case Dchar: delete (char*)Point; break;
	case Dbool: delete (bool*)Point; break;
	case DPPoint: delete (void**)Point; break;
		//	case DIP: return (*(ip*)Point).�lone();
		//	case DIC: return Point = ICCopy(*this);
	}
	Point = nullptr; Type = 0;
}

LoadPoint LoadPoint::Copy()
{
	if (!this->isIC())
		return { 0,nullptr };
	IC_type t=new vector<ip>;
	
	LoadPoint LP;
	LP.Copy(*this);
	return LP;
}

void LoadPoint::Copy(LoadPoint LP)
{
	Type = LP.Type;
	if (LP.Type % 2 == 0)
	{
		Point = LP.Point;
		return;
	}
	switch (Type)
	{
	case Cstring: Point = new string(*(string*)LP.Point); break;
	case Cint: Point = new int(*(int*)LP.Point); break;
	case Cfloat: Point = new float(*(float*)LP.Point); break;
	case Cdouble: Point = new double(*(double*)LP.Point); break;
	case Cchar: Point = new char(*(char*)LP.Point); break;
	case Cbool: Point = new bool(*(bool*)LP.Point); break;
	case CPPoint: Point = new (void*)(*(void**)LP.Point); break;
	case CIP: // ???
		break;
	case CIC:
		Point = ICCopy(LP);
		break;
	}
}

void LoadPoint::Clear() // �������� ��������
{
	if (Type % 2 == 0) return;
	switch (Type)
	{
	case Cstring: delete (string*)Point; break;
	case Cint: delete (int*)Point; break;
	case Cfloat: delete (float*)Point; break;
	case Cdouble: delete (double*)Point; break;
	case Cchar: delete (char*)Point; break;
	case Cbool: delete (bool*)Point; break;
	case CPPoint: delete (void**)Point; break;
	case CIP: // ???
		break;
	case CIC:
		ICDel(Point);
		break;
	}
	Type = 0; Point = nullptr;
}
// ������ �������
void LoadPoint::LoadPoint::VarClear() // ����� �������� �� � ��� ����� � � ���������� (���������� ���������)
{
	Type -= Type % 2;
	Type += 1;
	Clear();
}

void LoadPoint::VectorPrint(unsigned int Type, void* P, map<int, string > AtrMnemo, string offset, string Sep, string End, string ArrayBracketStart, string ArrayBracketFin)
{
	switch ((Type % 1000) >> 1)
	{
	case Dstring: {
		cout << ArrayBracketStart;
		for (auto t = (*((vector<string>*)P)).begin(); t != (*(vector<string>*)P).end(); t++)
			cout << *t << (t == (*((vector<string>*)P)).begin() - 1 ? Sep : "");
		cout << ArrayBracketFin;
		break; }
	case Dint: {
		cout << ArrayBracketStart;
		for (auto t = (*((vector<int>*)P)).begin(); t != (*(vector<int>*)P).end(); t++)
			cout << *t << (t == (*((vector<int>*)P)).begin() - 1 ? Sep : "");
		cout << ArrayBracketFin;
	}break;
	case Dfloat: {
		cout << ArrayBracketStart;
		for (auto t = (*((vector<float>*)P)).begin(); t != (*(vector<float>*)P).end(); t++)
			cout << *t << (t == (*((vector<float>*)P)).begin() - 1 ? Sep : "");
		cout << ArrayBracketFin;
	}break;
	case Ddouble: {
		cout << ArrayBracketStart;
		for (auto t = (*((vector<double>*)P)).begin(); t != (*(vector<double>*)P).end(); t++)
		{
			cout << *t << ((t != (*((vector<double>*)P)).end() - 1) ? Sep : "");
		}
		cout << ArrayBracketFin;
	}break;
	case Dchar: {
		cout << ArrayBracketStart;
		for (auto t = (*((vector<char>*)P)).begin(); t != (*(vector<char>*)P).end(); t++)
			cout << *t << (t == (*((vector<char>*)P)).begin() - 1 ? Sep : "");
		cout << ArrayBracketFin;
	}break;
	case Dbool: {
		cout << ArrayBracketStart;
		for (auto t = (*((vector<bool>*)P)).begin(); t != (*(vector<bool>*)P).end(); t++)
			cout << *t << (t == (*((vector<bool>*)P)).begin() - 1 ? Sep : "");
		cout << ArrayBracketFin;
	}break;
	case DIP: {
		cout << ArrayBracketStart;
		for (auto t = (*((vector<ip>*)P)).begin(); t != (*(vector<ip>*)P).end(); t++)
			t->Load.print(AtrMnemo, offset, Sep, End);
		cout << ArrayBracketFin;
	}break;
	case DIC: {
		cout << ArrayBracketStart;
		for (auto t = (*((vector<ip>*)P)).begin(); t != (*(vector<ip>*)P).end(); t++)
			t->Load.print(AtrMnemo, offset, Sep, End);
		cout << ArrayBracketFin;
	}break;
	default:
		cout << "unknown load\n";
	}
}
// ������ �������
void LoadPoint::MatrixPrint(unsigned int Type, void* P, map<int, string > AtrMnemo, string offset, string Sep, string End, string ArrayBracketStart, string ArrayBracketFin)
{
	switch ((Type % 1000) >> 1)
	{
	case Dstring: {
		cout << ArrayBracketStart;
		for (auto t = (*((vector< vector<string>>*)P)).begin(); t != (*(vector < vector<string>>*)P).end(); t++)
			VectorPrint(Type-1000, (void*)&(*t), AtrMnemo, offset, Sep, End, ArrayBracketStart, ArrayBracketFin);
		cout << ArrayBracketFin;
		break; }
	case Dint: {
		cout << ArrayBracketStart;
		for (auto t = (*((vector < vector<int>>*)P)).begin(); t != (*(vector < vector<int>>*)P).end(); t++)
			VectorPrint(Type - 1000, (void*)&(*t), AtrMnemo, offset, Sep, End, ArrayBracketStart, ArrayBracketFin);
		cout << ArrayBracketFin;
	}break;
	case Dfloat: {
		cout << ArrayBracketStart;
		for (auto t = (*((vector < vector<float>>*)P)).begin(); t != (*(vector < vector<float>>*)P).end(); t++)
			VectorPrint(Type - 1000, (void*)&(*t), AtrMnemo, offset, Sep, End, ArrayBracketStart, ArrayBracketFin);
		cout << ArrayBracketFin ;
	}break;
	case Ddouble: {
		cout << ArrayBracketStart;
		for (auto t = (*((vector < vector<double>>*)P)).begin(); t != (*(vector < vector<double>>*)P).end(); t++)
		{
			VectorPrint(Type - 1000, (void*)&(*t), AtrMnemo, offset, Sep, End, ArrayBracketStart, ArrayBracketFin);
			cout << End;
		}
		cout << ArrayBracketFin;
	}break;
	case Dchar: {
		cout << ArrayBracketStart;
		for (auto t = (*((vector < vector<char>>*)P)).begin(); t != (*(vector < vector<char>>*)P).end(); t++)
			VectorPrint(Type - 1000, (void*)&(*t), AtrMnemo, offset, Sep, End, ArrayBracketStart, ArrayBracketFin);
		cout << ArrayBracketFin;
	}break;
	case Dbool: {
		cout << ArrayBracketStart;
		for (auto t = (*((vector < vector<bool>>*)P)).begin(); t != (*(vector < vector<bool>>*)P).end(); t++)
			VectorPrint(Type - 1000, (void*)&(*t), AtrMnemo, offset, Sep, End, ArrayBracketStart, ArrayBracketFin);
		cout << ArrayBracketFin;
	}break;
	case DIP: {
		cout << ArrayBracketStart;
		for (auto t = (*((vector < vector<ip>>*)P)).begin(); t != (*(vector < vector<ip>>*)P).end(); t++)
			VectorPrint(Type - 1000, (void*)&(*t), AtrMnemo, offset, Sep, End, ArrayBracketStart, ArrayBracketFin);
		cout << ArrayBracketFin;
	}break;
	case DIC: {
		cout << ArrayBracketStart;
		for (auto t = (*((vector < vector<ip>>*)P)).begin(); t != (*(vector < vector<ip>>*)P).end(); t++)
			VectorPrint(Type - 1000, (void*)&(*t), AtrMnemo, offset, Sep, End, ArrayBracketStart, ArrayBracketFin);
		cout << ArrayBracketFin;
	}break;
	default:
		cout << "unknown load\n";
	}
}

void LoadPoint::print(map<int, string > AtrMnemo, string offset, string Sep, string End, string ArrayBracketStart, string ArrayBracketFin, map<void*, int> *AdrMap)
{
	if (Point == nullptr)
	{
		cout << "null\n";
		return;
	}
	switch (Type)
	{
	case Tstring:
	case Cstring: cout << "\"" << * (string*)Point << "\""; break;
	case Tint:
	case Cint:	  cout << *(int*)Point; break;
	case Tfloat:
	case Cfloat:  cout << *(float*)Point; break;
	case Tdouble:
	case Cdouble: cout << *(double*)Point; break;
	case Tchar:
	case Cchar:   cout << *(char*)Point; break;
	case Tbool:
	case Cbool:   cout << *(bool*)Point; break;
	case TIP:
	case CIP:
		if (((ip*)Point)->Load.Type >> 1 == DIP || isIC())
			if(AtrMnemo.count(((ip*)Point)->atr))
				cout << AtrMnemo[((ip*)Point)->atr] << " ->\n";
			else
				cout << ((ip*)Point)->atr << " ->\n";
		else
			if (AtrMnemo.count(((ip*)Point)->atr))
				cout << AtrMnemo[((ip*)Point)->atr] << ((((ip*)Point)->Load.Type % 2) ? " # " : "=");
			else
				cout << ((ip*)Point)->atr << ((((ip*)Point)->Load.Type%2)? " # ": "=");
		((ip*)Point)->Load.print();
		break;
	case TIC:
	case CIC:
	{
		bool FMap = false; // ���� �������� ������ ���������� ������� ��-�����
		if (AdrMap == nullptr)
		{
			AdrMap = new map<void*, int>;
			FMap = true;
		}
		if (AdrMap->count(Point)) // ����������� ������������ ��-�����
		{
			cout << offset << "IC id: " << (*AdrMap)[Point] << endl;
			break;
		}
		(*AdrMap)[Point] = AdrMap->size(); // ��������� ���������� �� ��� ��������� ������������

		for (auto i = ((IC_type)Point)->begin(); i != ((IC_type)Point)->end(); i++)
		{
			if (i->Load.Type >> 1 == DIP || i->Load.isIC())
				if (AtrMnemo.count(i->atr))
					cout << offset << AtrMnemo[i->atr] << " ->\n";
				else
					cout << offset << i->atr << " ->\n";
			else
				if (AtrMnemo.count(i->atr))
					cout << offset << AtrMnemo[i->atr] <<  ((i->Load.Type % 2) ? " # " : " = ");
				else
					cout << offset << i->atr << ((i->Load.Type % 2) ? " # " : " = ");
			i->Load.print(AtrMnemo, offset + "  ", Sep, End, ArrayBracketStart, ArrayBracketFin, AdrMap);
			if (i != ((IC_type)Point)->end() - 1)
				cout << endl;
		}
		if (FMap)  // ������� ������� ���������� �������
		{
			AdrMap->clear();
			delete AdrMap;
		}
		break;
	}
	case TLoadArray:
	case CLoadArray: // ������ ��������
	{
		cout << ArrayBracketStart;
		int c = 1;
		for (auto i : *(vector<LoadPoint>*) Point)
		{
			i.print(AtrMnemo, offset, Sep, End, ArrayBracketStart, ArrayBracketFin);
			if(c<((vector<LoadPoint>*) Point)->size()) cout << Sep;
			c++;
		}
		cout << ArrayBracketFin << endl;
		break;
	}
	default:
		if (Type >= 2000) // ������ ������� � �������
		{
			MatrixPrint(Type, Point, AtrMnemo, offset, Sep, End, ArrayBracketStart, ArrayBracketFin);
		}
		else if(Type >= 1000)
			VectorPrint(Type, Point, AtrMnemo, offset, Sep, End, ArrayBracketStart, ArrayBracketFin);
	}
}

// ������ � ��
void FU::CommonMk(int Mk, LoadPoint Load)
{
	switch (Mk)
	{
	case ProgMk: // 958 Prog ����� ������������
	case ProgCycleMk: //959 CycleProg ����� �����
	case ProgPostCycleMk: //960 PostCycleProg ����� ���� �����
		if (Alu != nullptr)
			((ALU*)Alu)->Stack.push_back({}); //������������ �������� �����
		if (Load.Point == nullptr)
			ProgExec(Prog, Mk - ProgMk);
		else
			ProgExec(Load, Mk - ProgMk);
		if (Alu != nullptr)
			((ALU*)Alu)->Stack.pop_back(); // ������ ����������� �������� �����
		break;
	case YesMk: //961 YesProg ����� ������������ �� ��
	case YesCycleMk: //962 YesCycleProg ����� ����� �� ��
	case YesPostCycleMk: //963 YesPostCycleProg ����� ���� ����� �� ��
		if (Accum.ToBool())
		{
			if (Alu != nullptr)
				((ALU*)Alu)->Stack.push_back({}); //������������ �������� �����
			if (Load.Point == nullptr)
				ProgExec(Prog, Mk - YesMk);
			else
				ProgExec(Load.Point, Mk - YesMk);
			if (Alu != nullptr)
				((ALU*)Alu)->Stack.pop_back(); // ������ ����������� �������� �����
		}
		break;
	case NoMk: //964 NoProg ����� ������������ �� ���
	case NoCycleMk: //965 NoCycleProg ����� ����� �� ���
	case NoPostCycleMk: //966 NoPostCycleProg ����� ���� ����� �� ���
		if (Accum.ToBool())
		{
			if (Alu != nullptr)
				((ALU*)Alu)->Stack.push_back({}); //������������ �������� �����
			if (Load.Point == nullptr)
				ProgExec(Prog, Mk - NoMk);
			else
				ProgExec(Load.Point, Mk - NoMk);
			if (Alu != nullptr)
				((ALU*)Alu)->Stack.pop_back(); // ������ ����������� �������� �����
		}
		break;
	case 919: // AccumPointerSet ���������� ������ �� �����������
		if (Load.Type >> 1 == Ddouble)
			Accum = Load;
		break;
	case 920: // AccumPointerOut ������ ������ �� �����������
		Load.Write(Accum);
		break;
	case 921: // AccumPointerOutMk ������ �� �� ������� �� �����������
		MkExec(Load,Accum);
		break;
	case 922: // AccumSet ���������� �������� ������������
		if (Accum.Point = nullptr)
		{
			Accum = { Cdouble,new double };
			AccumCreating = true; // ������������� ���� ���������������� �������� ������������ ��-��
		}
		Accum.Write(Load.ToDouble());
		AccumCreating = false;
		break;
	case 923: // AccumOut ������ �������� ������������
		Load.WriteFromLoad(Accum);
		break;
	case 925: // AccumOutMk ������ �� �� ��������� ������������
		MkExec(Load,Accum);
		break;
	case CalcMk: // 927 Calc ��������� ���
		if (Alu == nullptr)
		{
			Alu = new ALU(this->Bus);
			Accum = { Cdouble, &((ALU*)Alu)->accum };
			AccumCreating = false;
			ALUCreating = true;
		}
		((FU*)Alu)->ProgFU(ProgExecMk,Load);
		break;
	case 989: // ProgStop ��������� ��������� (����� �������� nil, �� ������������� true)
		ProgStop = Load.ToInt(1);
		break;
	case 988: // ProgStopAll ��������� ���� ���������� �� ���������� �������������� ��� ������� ��
		ProgStopAll = Load.ToBool(true);
		break;
	case 987: //Next ������� � ��������� �������� �����
		CycleStop = Load.ToInt();
		break;
	case 916:// ManualModeSet ���������� ����� ������� ����������
		if (Modeling == nullptr) Modeling = new FUModeling();
		Modeling->ManualMode = Load.ToBool();
		break;
	case 918: // SchedulerSet ���������� �������� ������������ ����������
		if (Modeling == nullptr) Modeling = new FUModeling();
		Modeling->scheduler = (FU*)Load.Point;
		Modeling->ManualMode = true;
		break;
	case 924: // Pr�fixProgSet
		PrefixProg = (IC_type)Load.Point;
		break;
	case 926: // PostfixProgSet
		PostfixProg = (IC_type)Load.Point;
		break;
	case ProgExecMk: // ProgExec ��������� ��������� (���� � �������� null, �� ��������� �� �������� Prog
		if (Load.Point == nullptr)
			ProgExec((vector<ip>*)Prog);
		else
			ProgExec((vector<ip>*)Load.Point);
		break;
	case 991: // ProgSet // ���������� ��������� �� ���������
		Prog = (IC_type)Load.Point;
		break;
	case 953: // ElseProgSet
		ElseProg = (IC_type)Load.Point;
		break;
	case 954: // ProgSetExec ���������� ��������� �� ��������� � ��������� ��
		Prog = (IC_type)Load.Point;
		ProgExec((vector<ip>*)Prog);
		break;
	case 995: //ContextOut ������ ��������� �� �������� ��
		if (Load.Type >> 1 == Dvoid || Load.Type >> 1 == DPPoint || Load.Type >> 1 == DFU)
			Load.Point = this;
		break;
	case 928: // ALUSet ���������� ������ �� ���
		if (ALUCreating)
			delete Alu;
		Alu = Load.Point;
		ALUCreating = false;
		break;
	case 998: //FUNameSet
		FUName = Load.ToStr();
		break;
	case 996: // FUNameOut
		Load.Write(FUName);
		break;
	case 997: // FUNameOutMk
		if (Load.Point != nullptr)
			MkExec(Load.ToInt(), { Cstring,&FUName });
		break;
	case 999: //ContextOutMK ������ ������������ � ���������� �� �������� ��
		if (Load.Type >> 1 == Dint)
			Bus->ProgFU(*(int*)Load.Point, { TFU, this });
		break;
	}
}

// ������ ���������
//void FU::ProgExec(void* UK, FU* ProgBus, vector<ip>::iterator* Start) // ���������� ��������� �� ��{
// CycleType ��� �����: 0 - ��� �����, 1 - ����, 2 - ���� � ������������
void FU::ProgExec(void* UK, unsigned int CycleMode, FU* ProgBus, vector<ip>::iterator* Start) // ���������� ��������� �� ��
{
	if (UK==nullptr)return;
	vector<ip>* Uk = (IC_type)UK;
	if (ProgBus == nullptr) ProgBus = Bus;
	bool RepeatF = false; // ���� ������������ ���������� ��������� � ��
	do
	{
		ProgStop = 0; // ������� ��������� (�������� ���������� �������, �� ������� ���������� �����
		RepeatF = false; // ���� ������������� �������� �� ����� ���� ������� �� � ��
		ProgStopAll = false; // ���� ��������� ���� ���������
		CycleStop = 0; // ������� ������� �� ������ (���� ������������� ��������, �� ����������� �����)
		for (auto i = Start == nullptr ? Uk->begin() : *Start; i != Uk->end(); i++)
		{
			if (i->atr >= FUMkRange)
				ProgBus->ProgFU(i->atr, i->Load); // ���� �������� �� �� ����������� �� (������ �� Bus)
			else // �� ��� ������� ��
			{
				if (i->atr == BreakAtr) { ProgStop = i->Load.ToInt()-1; return; } // �������� ���������
				if (i->atr == NextAtr)
					if (!i->Load.ToInt())
					{
						i = Uk->begin();  // ����������� �������� �����
						continue;
					}
					else
					{
						CycleStop = i->Load.ToInt(); 
						return;
					} // ������� � ��������� ��������� ������
				// ����� �� ����� �� �������
				if (i->atr == YesContinueAtr || i->atr == NoContinueAtr) 
				{
					if (CycleMode == 2) // �������� ����� � ������������ (���������� ������ ��������)
					{
						CycleMode = 1;
						continue;
					}
					if (i->Load.IsProg() && Alu != nullptr) // ������ ���������� ���
//						((FU*)Alu)->ProgExec(i->Load.Point);
//
					// ������� � ��������� �������� ����� continue
					if (i->Load.IsProg())
					{
						if (Alu == nullptr)
						{
							Alu = new ALU(this);
							((FU*)Alu)->Bus = Bus;
							ALUCreating = true;
							AccumCreating = false;
							if (Accum.Point != nullptr && AccumCreating)
								Accum.Clear();
							AccumCreating = false;
							Accum = { Cdouble,&((ALU*)Alu)->accum };
						}
						((FU*)Alu)->ProgExec(i->Load);
					}
					if (i->atr == YesContinueAtr && !Accum.ToBool() || i->atr == NoContinueAtr && Accum.ToBool())
					{
						CycleMode = 0; // ����� �� �����
						break;
					} // ����� �� �����
					continue;
				}
				if (i->atr == RepeatAtr) { // ��������� ��������� ������
					RepeatF = true; break;
				}

				if (i->atr == ProgMkAtr || // ������� � �����������
					i->atr == YesAtr && Accum.ToBool() ||
					i->atr == NoAtr && !Accum.ToBool()) {
					((ALU*)Alu)->Stack.push_back(((ALU*)Alu)->Stack.back());
					ProgExec(i->Load, 0, ProgBus);
					((ALU*)Alu)->Stack.pop_back();
					((ALU*)Alu)->accum = ((ALU*)Alu)->Stack.back().accum;
					continue;
				}
				if (i->atr == YesCycleAtr && Accum.ToBool() || // ������� � ����� � ������������
					i->atr == NoCycleAtr && !Accum.ToBool() ||
					i->atr == ProgCycleAtr) {
					((ALU*)Alu)->Stack.push_back(((ALU*)Alu)->Stack.back());
					ProgExec(i->Load, 1, ProgBus);
					((ALU*)Alu)->Stack.pop_back();
					((ALU*)Alu)->accum = ((ALU*)Alu)->Stack.back().accum;
					continue;
				}
				if (i->atr == YesPostCycleAtr && Accum.ToBool() || // ������� � �����
					i->atr == NoPostCycleAtr && !Accum.ToBool() ||
					i->atr == ProgPostCycleAtr) {
					((ALU*)Alu)->Stack.push_back(((ALU*)Alu)->Stack.back());
					ProgExec(i->Load, 2, ProgBus);
					((ALU*)Alu)->Stack.pop_back();
					((ALU*)Alu)->accum = ((ALU*)Alu)->Stack.back().accum;
					continue;
				}

				ProgFU(i->atr, i->Load); // ���������� �������
			}

			if (CycleStop != 0) // ��������� ������
				if (!CycleMode) // ���� �� � ������ �����, �� ������ ������� �� ������
					return;
				else
					if (CycleStop > 0)
						CycleStop--; // ���������� �������� ������� �� �����
					else
					{
						CycleStop++;
						if (!CycleStop) // ���������� �������� ������� �� �����
							i = Uk->begin(); // ����������� �����
						return;
					}
			if (ProgStop > 0) { ProgStop--; return; }
			if (ProgStopAll) { return; } // ������������ ����� �� ������������
		}
	} while (RepeatF || CycleMode>0);
}

// ������ ��������� �� ��������� �� ������� ��
void FU::ProgExec(LoadPoint Uk, unsigned int CycleMode, FU* Bus, vector<ip>::iterator* Start) // ���������� ��������� �� ��
{
	if (Uk.Type >> 1 == DIC)
		ProgExec(Uk.Point, CycleMode, Bus, Start);
}

void FU::MkExec(int MK, LoadPoint Load, FU* BusContext, bool Ext) // ������ �� � ���������
{
	if (MK < FUMkRange && !Ext) // ���� �� ���������� ������ ��
		ProgFU(MK, Load);
	else
		if (BusContext != nullptr)
			BusContext->ProgFU(MK, Load);
		else
			Bus->ProgFU(MK, Load);
}

void FU::MkExec(LoadPoint Mk, LoadPoint Load, FU* BusContext, bool Ext) // ������ �� � ���������
{
	if (Mk.Type >> 1 == Dint && Mk.Point != nullptr)
	{
		int MK = *(int*)Mk.Point;
		if (MK < FUMkRange && !Ext) // ���� �� ���������� ������ ��
			ProgFU(MK, Load);
		else
			if (BusContext != nullptr)
				BusContext->ProgFU(MK, Load);
			else
				Bus->ProgFU(MK, Load);
	}
}

void FU::Scheduling()
{
	if (Modeling == nullptr) return;
	if (Modeling->qmk.size() != 0)
	{
		Modeling->SchedulerFlag = true;
		if (Modeling->qmk.size() == 0)
			cout << "Modeling error\n";
		else
		{
			ip t = Modeling->qmk.back();
			Modeling->qmk.pop_back();
			ProgFU(t.atr, t.Load);
			if (t.Load.Type % 2 == 1 && t.Load.Point != nullptr)
				t.Load.VarDel();
		}
	}
}

bool LoadCmp(LoadPoint x, LoadPoint y) // ��������� ���� �������� ��
{
	// ���������� � ����������� �� �� � ��
	if (x.Point == nullptr || y.Point == nullptr)
		return true;
	int xt = x.Type >> 1, yt = y.Type >> 1;
	if ((xt == Dint || xt == Dfloat || xt == Ddouble || xt == Dchar) && (yt == Dint || yt == Dfloat || yt == Ddouble || yt == Dchar))
		switch (xt)
		{
		case Dint:
			switch (yt)
			{
			case Dint: return *(int*)x.Point == *(int*)y.Point;
			case Dfloat: return *(int*)x.Point == *(float*)y.Point;
			case Ddouble: return *(int*)x.Point == *(double*)y.Point;
			case Dchar: return *(int*)x.Point == *(char*)y.Point;
			}
		case Dfloat:
			switch (yt)
			{
			case Dint: return *(float*)x.Point == *(int*)y.Point;
			case Dfloat: return *(float*)x.Point == *(float*)y.Point;
			case Ddouble: return *(float*)x.Point == *(double*)y.Point;
			case Dchar: return *(float*)x.Point == *(char*)y.Point;
			}
		case Ddouble:
			switch (yt)
			{
			case Dint: return *(double*)x.Point == *(int*)y.Point;
			case Dfloat: return *(double*)x.Point == *(float*)y.Point;
			case Ddouble: return *(double*)x.Point == *(double*)y.Point;
			case Dchar: return *(double*)x.Point == *(char*)y.Point;
			}
		case Dchar:
			switch (yt)
			{
			case Dint: return *(char*)x.Point == *(int*)y.Point;
			case Dfloat: return *(char*)x.Point == *(float*)y.Point;
			case Ddouble: return *(char*)x.Point == *(double*)y.Point;
			case Dchar: return *(char*)x.Point == *(char*)y.Point;
			}
		}
	if (xt == Dbool && yt == Dbool)
		return *(bool*)x.Point == *(bool*)y.Point;
	if (xt == Dstring && yt == Dstring)
		return *(string*)x.Point == *(string*)y.Point;

	return false;
}

bool IPCmp(ip* x, ip* y) // ��������� ����  ��
{
	if (!LoadCmp(x->Load, y->Load))
		return false;
	else
		if (x->atr == y->atr || x->atr == 0 || y->atr == 0)
			return true;
		else
			return false;
}

// ������ � ��
bool AtrSearch(void* uk, int Atr) // ����� ��������� � ��
{
	for (auto& i : *(IC_type)uk)
		if (i.atr == Atr)
			return true;
	return false;
}

int AtrCounter(void* uk, int Atr) // ������� ���������� �� � ��������� ���������� � ��
{
	int c = 0;
	for (auto& i : *(IC_type)uk)
		if (i.atr == Atr)
			c++;
	return c;
}

void ICDel(void* Uk) // �������� ��
{
	for (auto&& i : *(IC_type)Uk)
		i.Load.Clear();
	delete (IC_type)Uk;
}

void* ICCopy(LoadPoint uk) // ����������� ��
{
	IC_type CapsNew = new vector<ip>;
	if (uk.Type >> 1 == DIP) // ���� ���������� ��
	{
		CapsNew->push_back(*(*(ip*)uk.Point).�lone());
		return CapsNew;
	}
	IC_type Uk = (IC_type)uk.Point;
	CapsNew->resize(((IC_type)Uk)->size());
	for (auto i = ((IC_type)Uk)->begin(), j = CapsNew->begin(); j != CapsNew->end(); i++, j++)
	{
		j->atr = i->atr;
		j->Load.Copy(i->Load);
	}
	return CapsNew;
}

void* GraphCopy(void* Uk, LocatTable* Table = nullptr) // ����������� ��-�����
{
	return nullptr;
}

void GraphDel(void* Uk, LocatTable* Table = nullptr) // �������� ��-�����
{
	return;
}
// ------------------------



// ����� � �� �� � ��������� Atr � ��������� ��������� ���� �� ���. � ��������, ���� ����� ��������� ��
void AtrProgExec(vector<ip>* Prog, int Atr, FU* Bus, bool AfterContinue)
{
	auto i = Prog->begin();
	for (; i != Prog->end() && i->atr != Atr; i++);
	if (i != Prog->end())
	{
		if (i->Load.Point != nullptr)
			Bus->ProgExec((vector<ip> *)i->Load.Point);
		if ((++i) != Prog->end() && AfterContinue)
			Bus->ProgExec(Prog, 0, nullptr, &i);
	}
}

ip* AtrFind(void* IC, int Atr) // ����� � �� �� � �������� �������
{
	if (IC == nullptr) return nullptr;
	auto uk = (*(IC_type)IC).begin();
	for (; uk != ((IC_type)IC)->end() && uk->atr != Atr; uk++);
	if (uk == ((IC_type)IC)->end())
		return nullptr;
	else
		return uk._Ptr;
	return nullptr;
}

bool isIPinIC(void* iP, void* iC) //��������, ��� �� ������ � ��
{
	for (auto i = ((IC_type)iC)->begin()._Ptr; i != ((IC_type)iC)->end()._Ptr; i++) {
		if (IPCmp(i, ((ip*)iP)))
			return true;
	}
	return false;
}
