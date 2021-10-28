#include "stdafx.h"
#include "Consts.h"
#include <iostream>
#include <string>
#include "LocationTable.h"

using namespace std;

string LoadPoint::ToStr(string define) // Перевод в bool
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

bool LoadPoint::ToBool(bool define) // Перевод в bool (по умолчания false)
{
	if (Point == nullptr)
		return define;
	switch (Type >> 1)
	{
	case Ddouble: return *(double*)Point; break;
	case Dfloat: return *(float*)Point; break;
	case Dint: return *(int*)Point; break;
	case Dbool: return *(bool*)Point; break;
	case Dstring: return ((*(string*)Point) == "") ? false : true;
	default:
		return false;
		break;
	}
}

int LoadPoint::ToInt(int define) { // Перевод в integer
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
double LoadPoint::ToDouble(double define) {// Перевод в integer
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

float LoadPoint::ToFloat(float define) {// Перевод в integer
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
// Копирование векторов
void LoadPoint::Write(vector<double> x) // Копирование вектора
{
	if (Type == CdoubleArray)
		*(vector<double>*)Point = x;
}
void LoadPoint::Write(vector<float> x) // Копирование вектора
{
	if (Type == CdoubleArray)
		*(vector<float>*)Point = x;
}
void LoadPoint::Write(vector<bool> x) // Копирование вектора
{
	if (Type == CdoubleArray)
		*(vector<bool>*)Point = x;
}
void LoadPoint::Write(vector<char> x) // Копирование вектора
{
	if (Type == CdoubleArray)
		*(vector<char>*)Point = x;
}
void LoadPoint::Write(vector<int> x) // Копирование вектора
{
	if (Type == CdoubleArray)
		*(vector<int>*)Point = x;
}
// -----

void LoadPoint::Write(size_t x)
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
void LoadPoint::Write(LoadPoint x)
{
	switch (Type)
	{
	case TLoad:
		*(LoadPoint*)Point = x;
		break;
	}
}

void ICDel(void* Uk) // Удаление ИК
{
	for (auto&& i : *(IC_type)Uk)
		i.Load.Clear();
	delete (IC_type)Uk;
}

void* ICCopy(LoadPoint uk) // Копирование ИК
{
	IC_type CapsNew = new vector<ip>;
	if (uk.Type >> 1 == DIP) // Если передается ИП
	{
		CapsNew->push_back(*(*(ip*)uk.Point).Сlone());
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

void* GraphCopy(void* Uk, LocatTable* Table = nullptr) // Копирование ОА-графа
{
	return nullptr;
}

void GraphDel(void* Uk, LocatTable* Table = nullptr) // Удаление ОА-графа
{
	return;
}

LoadPoint LoadPoint::Clone() // Вернуть клонированную нагрузку
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
	case DIP: //return { Type, (*(ip*)Point).Сlone() };
	{
		vector<ip>* t = new vector<ip>;
		t->push_back(*((ip*)Point));
		//		((ip*)Point)->Load.Clone();
		return { Type, t };
	}
	default: return *this;
	}
}

void* LoadPoint::VarClone() // Вернуть ссылку на клонированное значение из нагрузки
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

void LoadPoint::VarDel() // Удаление нагрузки ИП
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
		//	case DIP: return (*(ip*)Point).сlone();
		//	case DIC: return Point = ICCopy(*this);
	}
	Point = nullptr; Type = 0;
}

void LoadPoint::Copy(LoadPoint* LP)
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

void LoadPoint::Clear() // Сбросить нагрузку
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

void LoadPoint::VarClear() // Сброс нагрузки ИП в том числе и с переменной (переменная стирается)
{
	Type -= Type % 2;
	Type += 1;
	Clear();
}

void LoadPoint::print(void* AtrMnemo, string offset, string Sep, string End, string ArrayBracketStart, string ArrayBracketFin)
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
		if (((ip*)Point)->Load.Type >> 1 == DIP || ((ip*)Point)->Load.Type >> 1 == DIC)
			cout << ((ip*)Point)->atr << " ->\n";
		else
			cout << ((ip*)Point)->atr << ((((ip*)Point)->Load.Type%2)? " # ": "=");
		((ip*)Point)->Load.print();
		break;
	case TIC:
	case CIC:
	{
		for (auto i = ((IC_type)Point)->begin(); i != ((IC_type)Point)->end(); i++)
		{
			if (i->Load.Type >> 1 == DIP || i->Load.Type >> 1 == DIC) {
				cout << offset << i->atr << " ->\n";
			}
			else
				cout << offset << i->atr <<  ((i->Load.Type % 2) ? " # " : " = ");
			i->Load.print(nullptr, offset + "  ");
			if (i != ((IC_type)Point)->end() - 1) cout << endl;
		}
		break;
	}
	default:
		if (Type >= 1000) // Печать вектора
		{
			switch ((Type % 1000) >> 1)
			{
			case Dstring: {
				cout << ArrayBracketStart;
				for (auto t = (*((vector<string> *)Point)).begin(); t != (*(vector<string> *)Point).end(); t++)
					cout << *t << (t == (*((vector<string> *)Point)).begin() - 1 ? Sep : "");
				cout << ArrayBracketFin;
				break; }
			case Dint: {
				cout << ArrayBracketStart;
				for (auto t = (*((vector<int> *)Point)).begin(); t != (*(vector<int> *)Point).end(); t++)
					cout << *t << (t == (*((vector<int> *)Point)).begin() - 1 ? Sep : "");
				cout << ArrayBracketFin;
			}break;
			case Dfloat: {
				cout << ArrayBracketStart;
				for (auto t = (*((vector<float> *)Point)).begin(); t != (*(vector<float> *)Point).end(); t++)
					cout << *t << (t == (*((vector<float> *)Point)).begin() - 1 ? Sep : "");
				cout << ArrayBracketFin;
			}break;
			case Ddouble: {
				cout << ArrayBracketStart;
				for (auto t = (*((vector<double>*)Point)).begin(); t != (*(vector<double>*)Point).end(); t++)
				{
					cout << *t << ((t != (*((vector<double>*)Point)).end() - 1) ? Sep : "");
//					cout << *t;
//					if(t != (*((vector<double>*)Point)).end() - 1)
//						cout<<Sep;
				}
				cout << ArrayBracketFin;
			}break;
			case Dchar: {
				cout << ArrayBracketStart;
				for (auto t = (*((vector<char> *)Point)).begin(); t != (*(vector<char> *)Point).end(); t++)
					cout << *t << (t == (*((vector<char> *)Point)).begin() - 1 ? Sep : "");
				cout << ArrayBracketFin;
			}break;
			case Dbool: {
				cout << ArrayBracketStart;
				for (auto t = (*((vector<bool> *)Point)).begin(); t != (*(vector<bool> *)Point).end(); t++)
					cout << *t << (t == (*((vector<bool> *)Point)).begin() - 1 ? Sep : "");
				cout << ArrayBracketFin;
			}break;
			case DIP: {
				cout << ArrayBracketStart;
				for (auto t = (*((vector<ip> *)Point)).begin(); t != (*(vector<ip> *)Point).end(); t++)
					t->Load.print(AtrMnemo, offset, Sep, End);
				cout << ArrayBracketFin;
			}break;
			case DIC: {
				cout << ArrayBracketStart;
				for (auto t = (*((vector<ip> *)Point)).begin(); t != (*(vector<ip> *)Point).end(); t++)
					t->Load.print(AtrMnemo, offset, Sep, End);				
				cout << ArrayBracketFin;
			}break;
			}
//			cout << End;
			return;
		}
		cout << "unknown load\n";
	}
}


void FU::CommonMk(int Mk, LoadPoint Load)
{
	switch (Mk)
	{
	case SubMk: // 900 Sub Вызов подпрограммыd
		ProgExec(Load.Point);
		break;
	case 901: //RepeatProg
		break;
	case 989: // ProgStop Остановка программы (несли нагрузка nil, то присваивается true)
		ProgStop = Load.ToInt(1);
		break;
	case 988: // ProgStopAll Остановка всех запущенных на выполнение миллипрограммы для данного ФУ
		ProgStopAll = Load.ToBool(true);
		break;
	case 916:// ManualModeSet Установить режим ручного управления
		if (Modeling == nullptr) Modeling = new FUModeling();
		Modeling->ManualMode = Load.ToBool();
		break;
	case 918: // SchedulerSet Установить контекст планировщика вычислений
		if (Modeling == nullptr) Modeling = new FUModeling();
		Modeling->scheduler = (FU*)Load.Point;
		Modeling->ManualMode = true;
		break;
	case 924: // PrеfixProgSet
		PrefixProg = (IC_type)Load.Point;
		break;
	case 926: // PostfixProgSet
		PostfixProg = (IC_type)Load.Point;
		break;
	case 990: // ProgExec Выполнить программу (если в нагрузке null, То выполнить из регистра Prog
		if (Load.Point == nullptr)
			ProgExec(((vector<ip>*)Prog), Bus, nullptr);
		else
			ProgExec(((vector<ip>*)Load.Point), Bus, nullptr);
		break;
	case 991: // ProgSet // Установить указатель на программу
		Prog = (IC_type)Load.Point;
		break;
	case 953: // ElseProgSet
		ElseProg = (IC_type)Load.Point;
		break;
	case 954: // ProgSetExec Установить указатель на программу и выполнить ее
		Prog = (IC_type)Load.Point;
		ProgExec(((vector<ip>*)Prog), Bus, nullptr);
		break;
	case 995: //ContextOut Выдать указатель на контекст ФУ
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
		if (Load.Point != nullptr)
			MkExec(Load.ToInt(), { Cstring,&FUName });
		break;
	case 999: //ContextOutMK Выдать милликоманду с указателем на контекст ФУ
		if (Load.Type >> 1 == Dint)
			Bus->ProgFU(*(int*)Load.Point, { TFU, this });
		break;
	}
}

// Запуск программы
void FU::ProgExec(void* UK, FU* ProgBus, vector<ip>::iterator* Start) // Исполнение программы из ИК
{
	if (UK==nullptr)return;
	vector<ip>* Uk = (IC_type)UK;
	if (ProgBus == nullptr) ProgBus = Bus;
	bool RepeatF = false;
	do
	{
		ProgStop = 0;
		RepeatF = false;
		ProgStopAll = false;
		for (auto i = Start == nullptr ? Uk->begin() : *Start; i != Uk->end(); i++)
		{
			if (i->atr < FUMkRange)
			{
				if (i->atr != RepeatMk)
					ProgFU(i->atr, i->Load);
				else
				{
					RepeatF = true; break;
				}
			}
			else
				ProgBus->ProgFU(i->atr, i->Load);
			if (ProgStop > 1) { ProgStop--; return; }
			if (ProgStopAll) { ProgStop = 0; return; } // Внеочередной выход из подпрограммы
		}
	} while (RepeatF);
}
// Запуск программы по указателю из нарузки ИП
void FU::ProgExec(LoadPoint Uk, FU* Bus, vector<ip>::iterator* Start) // Исполнение программы из ИК
{
	if (Uk.Type >> 1 == DIC)
		ProgExec(Uk.Point, Bus, Start);
}

void FU::MkExec(int MK, LoadPoint Load, FU* BusContext) // Выдача МК с нагрузкой
{
	if (MK < FUMkRange) // Если МК адресована сомому ФУ
		ProgFU(MK, Load);
	else
		if (BusContext != nullptr)
			BusContext->ProgFU(MK, Load);
		else
			Bus->ProgFU(MK, Load);
}

void FU::MkExec(LoadPoint Mk, LoadPoint Load, FU* BusContext) // Выдача МК с нагрузкой
{
	if (Mk.Type >> 1 == Dint && Mk.Point != nullptr)
	{
		int MK = *(int*)Mk.Point;
		if (MK < FUMkRange) // Если МК адресована сомому ФУ
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

bool LoadCmp(LoadPoint x, LoadPoint y) // Сравнение двух нагрузок ИП
{
	// Доработать с указателями на ИК и ИП
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

bool IPCmp(ip* x, ip* y) // Сравнение двух  ИП
{
	if (!LoadCmp(x->Load, y->Load))
		return false;
	else
		if (x->atr == y->atr || x->atr == 0 || y->atr == 0)
			return true;
		else
			return false;
}

// Найти в ИК ИП с атрибутом Atr и выполнить программу либо по адр. в нагрузке, либо после найденной ИП
void AtrProgExec(vector<ip>* Prog, int Atr, FU* Bus, bool AfterContinue)
{
	auto i = Prog->begin();
	for (; i != Prog->end() && i->atr != Atr; i++);
	if (i != Prog->end())
	{
		if (i->Load.Point != nullptr)
			Bus->ProgExec((vector<ip> *)i->Load.Point, Bus);
		if ((++i) != Prog->end() && AfterContinue)
			Bus->ProgExec(Prog, nullptr, &i);
	}
}

ip* AtrFind(void* IC, int Atr) // Поиск в ИК ИП с заданным атру
{
	if (IC == nullptr) return nullptr;
	auto uk = (*(IC_type)IC).begin();
	for (; uk != ((IC_type)IC)->end(); uk++)
		if (uk == ((IC_type)IC)->end())
			return nullptr;
		else
			return uk._Ptr;
	return nullptr;
}

bool isIPinIC(void* iP, void* iC) //проверка, что ИК входит в ИП
{
	for (auto i = ((IC_type)iC)->begin()._Ptr; i != ((IC_type)iC)->end()._Ptr; i++) {
		if (IPCmp(i, ((ip*)iP)))
			return true;
	}
	return false;
}