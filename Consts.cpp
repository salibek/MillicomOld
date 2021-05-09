#include "stdafx.h"
#include "Consts.h"
#include <iostream>
#include <string>
#include "LocationTable.h"

using namespace std;

string LoadPoint::ToStr() // ������� � bool
{
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

bool LoadPoint::ToBool() // ������� � bool
{
	if (Point == nullptr)
		return false;
	switch (Type >> 1)
	{
	case Ddouble: return *(double*)Point; break;
	case Dfloat: return *(float*)Point; break;
	case Dint: return *(int*)Point; break;
	case Dbool: return *(bool*)Point; break;
	case Dstring: return ((*(string*)Point)=="")?false:true;
	default:
		return false;
		break;
	}
}

int LoadPoint::ToInt() { // ������� � integer
	if (Point == nullptr)
		return 0;
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
double LoadPoint::ToDouble() {// ������� � integer
		if (Point == nullptr)
			return 0;
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

float LoadPoint::ToFloat() {// ������� � integer
		switch (Type >> 1)
		{
		if (Point == nullptr)
			return 0;
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


void LoadPoint::Write(int x)
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
	}
}

void LoadPoint::Write(double x)
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
	}
}

void LoadPoint::Write(float x)
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
	}
}

void LoadPoint::Write(bool x)
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
	}
}

void LoadPoint::Write(char x)
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
	}
}

void LoadPoint::Write(string x)
{
	switch (Type)
	{
	case Tstring:
		*((string*)Point) = x;
		break;
	}
}

void LoadPoint::Write(void* x)
{
	switch (Type)
	{
//	case TIP:
//		*((void*)Load.Point) = x;
//		break;
	}
}


void ICDel(void* Uk) // �������� ��
{
	for (auto &&i : *(IC_type)Uk)
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
		j->Load.Copy(&i->Load);
	}
	return CapsNew;
}

void* GraphCopy(void* Uk, LocatTable* Table=nullptr) // ����������� ��-�����
{
	return nullptr;
}

void GraphDel(void* Uk, LocatTable* Table = nullptr) // �������� ��-�����
{
	return;
}

LoadPoint LoadPoint::Clone()
{
	switch (Type)
	{
	case Cstring: return { Type, new string(*(string*)Point) };
	case Cint: return { Type, new int(*(int*)Point) };
	case Cfloat: return { Type, new float(*(float*)Point)};
	case Cdouble: return { Type,new double(*(double*)Point)};
	case Cchar: return { Type,new char(*(char*)Point) };
	case Cbool: return { Type,new bool(*(bool*)Point) };
	case CPPoint: return { Type,new (void*)(*(void**)Point) };
	case CIP: return { Type, (*(ip*)Point).�lone()};
	case CIC: return { Type, Point = ICCopy(*this) };
	default: return *this;
	}
}

void* LoadPoint::VarCopy()
{
	switch (Type<<1)
	{
	case Dstring: return new string(*(string*)Point);
	case Dint: return new int(*(int*)Point);
	case Dfloat: return new float(*(float*)Point);
	case Ddouble: return new double(*(double*)Point);
	case Dchar: return new char(*(char*)Point);
	case Dbool: return new bool(*(bool*)Point);
	case DPPoint: return new (void*)(*(void**)Point);
//	case DIP: return (*(ip*)Point).�lone();
//	case DIC: return Point = ICCopy(*this);
	}
}

void LoadPoint::VarDel() // �������� �������� ��
{
	switch (Type << 1)
	{
	case Dstring: delete (string*)Point;
	case Dint: delete (int*)Point;
	case Dfloat: delete (float*)Point;
	case Ddouble: delete (double*)Point;
	case Dchar: delete (char*)Point;
	case Dbool: delete (bool*)Point;
	case DPPoint: delete (void**)Point;
		//	case DIP: return (*(ip*)Point).�lone();
		//	case DIC: return Point = ICCopy(*this);
	}
	Point = nullptr; Type = 0;
}

void LoadPoint::Copy(LoadPoint *LP)
{
	Type = LP->Type;
	if (LP->Type % 2 == 0)
	{
		Point = LP->Point;
		return;
	}
	switch (Type)
	{
	case Cstring: Point = new string(*(string*)LP->Point); break;
	case Cint: Point = new int(*(int*)LP->Point); break;
	case Cfloat: Point = new float(*(float*)LP->Point); break;
	case Cdouble: Point = new double(*(double*)LP->Point); break;
	case Cchar: Point = new char(*(char*)LP->Point); break;
	case Cbool: Point = new bool(*(bool*)LP->Point); break;
	case CPPoint: Point = new (void*)(*(void**)LP->Point); break;
	case CIP: // ???
		break;
	case CIC:
		Point = ICCopy(*LP);
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

void LoadPoint::VarClear() // ����� �������� �� � ��� ����� � � ���������� (���������� ���������)
{
	Type -= Type % 2;
	Type += 1;
	Clear();
}

void LoadPoint::print(void* AtrMnemo, string offset)
{
	if (Point == nullptr)
	{
		cout << "null\n";
		return;
	}
	switch (Type)
	{
	case Tstring:
	case Cstring: cout << *(string*)Point; break;
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
		if(((ip*)Point)->Load.Type >> 1 == DIP || ((ip*)Point)->Load.Type >> 1 == DIC)
			cout << ((ip*)Point)->atr << " ->\n";
		else
			cout << ((ip*)Point)->atr << " # ";
			((ip*)Point)->Load.print();
			break;
	case TIC:
	case CIC:
	{int _i = 0;
	for (auto i : *(vector<ip>*)Point)
	{
		if (i.Load.Type >> 1 == DIP || i.Load.Type >> 1 == DIC) {
			cout << offset << i.atr << " ->\n";
		}
		else
			cout << offset << i.atr << " # ";
		i.Load.print(nullptr, offset + "  ");
		cout << endl;
	}
	break;
	}
	default:
		cout << "unknown load\n";
	}
}



void FU::CommonMk(int Mk, LoadPoint Load)
{
	switch (Mk)
	{
	case SubMk: // 900 Sub ����� ������������
		ProgExec(Load.Point);
		break;
	case 989: // ProgStop ��������� ��������� (����� �������� nil, �� ������������� true)
		ProgStop = (Load.Point == nullptr)? true: Load.ToBool();
		break;
	case 916:// ManualModeSet ���������� ����� ������� ����������
			if (Modeling == nullptr) Modeling = new FUModeling();
			Modeling->ManualMode = Load.ToBool();
			break;
		case 918: // SchedulerSet ���������� �������� ������������ ����������
			if (Modeling == nullptr) Modeling = new FUModeling();
			Modeling->scheduler = (FU*)Load.Point;
			Modeling->ManualMode = true;
			break\
				;
		case 924: // Pr�fixProgSet
			PrefixProg =(IC_type) Load.Point;
			break;
		case 926: // PostfixProgSet
			PostfixProg = (IC_type)Load.Point;
			break;
		case 990: // ProgExec ��������� ��������� (���� � �������� null, �� ��������� �� �������� Prog
			if(Load.Point==nullptr)
				ProgExec(((vector<ip>*)Prog), Bus, nullptr);
			else
				ProgExec(((vector<ip>*)Load.Point), Bus, nullptr);
			break;
		case 991: // ProgSet // ���������� ��������� �� ���������
			Prog = (IC_type)Load.Point;
			break;
		case 995: //ContextOut ������ ��������� �� �������� ��
			if (Load.Type >> 1 == Dvoid || Load.Type >> 1 == DPPoint || Load.Type >> 1 == DFU)
				Load.Point = this;
			break;
		case 998: //FUNameSet
			FUName = Load.ToStr();
			break;
		case 996: // FUNameOut
			Load.Write(FUName);
			break;
		case 997: // FUNameOutMk
			if(Load.Point!=nullptr)
			MkExec(Load.ToInt(), { Cstring,&FUName });
			break;
		case 999: //ContextOutMK ������ ������������ � ���������� �� �������� ��
			if (Load.Type >> 1 == Dint)
				Bus->ProgFU(*(int*)Load.Point, { TFU, this });
			break;
	}
}

// ������ ���������
void FU::ProgExec(void* UK, FU* ProgBus, vector<ip>::iterator* Start) // ���������� ��������� �� ��
{
	if (!UK)return;
	vector<ip>* Uk = (IC_type)UK;
	if (ProgBus == nullptr) ProgBus = Bus;
	for (auto i = Start==nullptr? Uk->begin(): *Start; i != Uk->end(); i++)
		{
			if (ProgStop) { ProgStop = false; return; } // ������������ ����� �� ������������
			if (i->atr < FUMkRange)
				ProgFU(i->atr, i->Load);
			else
				ProgBus->ProgFU(i->atr, i->Load);
		}
	ProgStop = false;
}
// ������ ��������� �� ��������� �� ������� ��
void FU::ProgExec(LoadPoint Uk, FU* Bus, vector<ip>::iterator* Start) // ���������� ��������� �� ��
{
	if(Uk.Type>>1==DIC)
		ProgExec(Uk.Point, Bus, Start);
}

void FU::MkExec(int MK, LoadPoint Load, FU* BusContext) // ������ �� � ���������
{
	if(MK<FUMkRange) // ���� �� ���������� ������ ��
		ProgFU(MK, Load);
	else
		if (BusContext != nullptr)
			BusContext->ProgFU(MK, Load);
		else
			Bus->ProgFU(MK, Load);
}

void FU::MkExec(LoadPoint Mk, LoadPoint Load, FU* BusContext) // ������ �� � ���������
{
	if (Mk.Type >> 1 == Dint && Mk.Point!=nullptr)
	{
		int MK = *(int*)Mk.Point;
		if (MK < FUMkRange) // ���� �� ���������� ������ ��
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
	if (Modeling->qmk.size()!=0)
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
	if( (xt== Dint || xt == Dfloat || xt== Ddouble || xt== Dchar)&&(yt == Dint || yt == Dfloat || yt == Ddouble || yt == Dchar) )
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

// ����� � �� �� � ��������� Atr � ��������� ��������� ���� �� ���. � ��������, ���� ����� ��������� ��
void AtrProgExec(vector<ip>* Prog, int Atr, FU* Bus, bool AfterContinue)
{
	auto i = Prog->begin();
	for (; i != Prog->end() && i->atr != Atr; i++);
	if (i != Prog->end())
	{
		if (i->Load.Point != nullptr)
			Bus->ProgExec((vector<ip> *)i->Load.Point, Bus);
		if((++i)!=Prog->end() && AfterContinue)
			Bus->ProgExec(Prog, nullptr,&i);
	}
}

ip* AtrFind(void* IC, int Atr) // ����� � �� �� � �������� ����
{
	if (IC == nullptr) return nullptr;
	auto uk = (*(IC_type)IC).begin();
	for (; uk != ((IC_type)IC)->end(); uk++)
		if (uk ==( (IC_type)IC)->end())
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