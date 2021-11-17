// Описание основных констант и информационных конструкций
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <string>

using namespace std; 

// Типы переменных
const int Tvoid = 0, Tint = 2, Tfloat = 4, Tdouble = 6, Tchar = 8, Tstring = 10, TIP = 12, Tbool = 14, TIC = 16;
const int TPPoint = 18, TGraph=20, TFU=22, TLoad=24;
const int TcharArray = 1002, TintArray = 1004, TfloatArray = 1006, TdoubleArray = 1008, TstringArray = 1010, TIPArray = 1012;
const int TboolArray = 1014, TICArray = 1016, TPPointArray = 1018, TGrapgArray = 1020, TFUArray = 1022, TLoadArray = 1024;
const int TcharArray2 = 2002, TintArray2 = 2004, TfloatArray2 = 2006, TdoubleArray2 = 2008, TstringArray2 = 2010, TIPArray2 = 2012;
const int TboolArray2 = 2014, TICArray2 = 2016, TPPointArray2 = 2018, TGrapgArray2 = 2020, TFUArray2 = 2022, TLoadArray2 = 2024;
// Типы констант
const int Cvoid = 1, Cint = 3, Cfloat = 5, Cdouble = 7, Cchar = 9, Cstring = 11, CIP = 13, Cbool = 15, CIC = 17;
const int CPPoint = 19, CGraph = 21, CFU = 23, CLoad = 25;
const int CcharArray = 1001, CintArray = 1003, CfloatArray = 1005, CdoubleArray = 1007, CstringArray = 1009, CIPArray = 1011;
const int CboolArray = 1013, CICArray = 1015, CPPointArray = 1017, CGrapgArray = 1019, CFUArray = 1021, CLoadArray = 1023;
const int CcharArray2 = 2001, CintArray2 = 2003, CfloatArray2 = 2005, CdoubleArray2 = 2007, CstringArray2 = 2009, CIPArray2 = 2011;
const int CboolArray2 = 2013, CICArray2 = 2015, CPPointArray2 = 2017, CGrapgArray2 = 2019, CFUArray2 = 2021, CLoadArray2 = 2023;
// Общие типы данных (остаток от целочисленного деления на 2 типа переменной или константы)
const int Dvoid=0, Dint = 1, Dfloat = 2, Ddouble = 3, Dchar = 4, Dstring = 5, DIP = 6, Dbool = 7, DIC = 8;
const int DPPoint = 9, DGraph = 10, DFU = 11, DLoad = 12;
const int DcharArray = 501, DintArray = 502, DfloatArray = 503, DdoubleArray = 504, DstringArray = 505, DIPArray = 506;
const int DboolArray = 507, DICArray = 508, DPPointArray = 509, DGrapgArray = 510, DFUArray = 511, DLoadArray = 512;
const int DcharArray2 = 1001, DintArray2 = 1002, DfloatArray2 = 1003, DdoubleArray2 = 1004, DstringArray2 = 1005, DIPArray2 = 1006;
const int DboolArray2 = 1007, DICArray2 = 1008, DPPointArray2 = 1009, DGrapgArray2 = 1010, DFUArray2 = 1011, DLoadArray2 = 1012;

// Типы ФУ
const int FUBus = 0, FUCons = 1, FUStrGen = 2, FULex = 3, FUList = 4, FUFind = 5;

// Веса типов
const vector<int> w_type = { 10, 30, 40, 50, 60, 70, 20 };

// Общие атрибуты
const int ProgAtr = -100, Atr=-60, SubMk=900, RepeatMk=901;

bool isIPinIC(void* iP, void* iC); //проверка, что ИК входит в ИП

class LoadPoint
{
	void VectorPrint(unsigned int Type, void* P, void* AtrMnemo, string offset, string Sep, string End, string ArrayBracketStart, string ArrayBracketFin); // Печать вектора
	void MatrixPrint(unsigned int Type, void* P, void* AtrMnemo, string offset, string Sep, string End, string ArrayBracketStart, string ArrayBracketFin); // Пачать матрицы
public:
	unsigned int Type = 0; // Неизвестный тип
	void *Point;
	bool isDigit() { return Type >> 1 == Dint || Type >> 1 == Dchar || Type >> 1 == Dfloat || Type >> 1 == Ddouble; }; // 
	bool isDigitBool() { return Type >> 1 == Dint || Type >> 1 == Dchar || Type >> 1 == Dfloat || Type >> 1 == Ddouble; Type >> 1 == Dbool; }; // Число или булеан?
	bool IpTest() { return (Type >> 1 == DIP || Type >> 1 == DIC); } // Является ли нагрузка ИП?
	bool IsConvert(unsigned int T) {}; // Тест на возможность конвертации значения из Point в определенный тип
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
	void WriteVar(LoadPoint x) { Point = x.Point; Type = x.Type; Type |= 1; Type--; }; //Записать ссылку и сделать ее переменной
	void WriteConst(LoadPoint x) {Point = x.Point; Type = x.Type; Type |= 1;}; // Записать ссылку и сделать ее константой

	string ToStr(string define=""); // Первод в string
	bool ToBool(bool define = false); // Перевод в bool
	int ToInt(int define=0); // Перевод в integer
	double ToDouble(double define=0); // Перевод в double
	float ToFloat(float define=0);// Перевод во float
	char ToChar() { return Point == nullptr ? 0 : *(char*)Point; }; // Перевод в integer
	void Copy(LoadPoint *LP);
	void Clear(); // Сброс нагрузки ИП
	void VarClear(); // Сброс нагрузки ИП в том числе и с переменной (переменная стирается)
	void* VarClone(); // Копирование значения нагрузки
	void VarDel();// Удаление нагрузки ИП
	void print(void* AtrMnemo=nullptr, string offset="", string Sep = "", string End = "\n", string ArrayBracketStart = "[", string ArrayBracketFin = "]"); // Параметр - указатель на табл. мнемоник атрибутов
	LoadPoint Clone(); // Дублировать нагрузку
	void ConstTypeSet(bool F = true) { if (F)Type |= 1; else VarTypeSet(); }; // Установить тип 'константа'
    // Установить тип 'переменная'
	void VarTypeSet(bool F = true) {
		if (!F) { ConstTypeSet(); return; } Type |= 1; Type -= 1;}
	LoadPoint IpOut() // Возвращается указатель на ИП или на первую ИП из ИК, иначе null
	{
		if (Type >> 1 == DIP) return *this;
//		if (Type >> 1 == DIC) return { DIP,((IC_type)Point)->begin()._Ptr};
//		return { 0,nullptr };
	};

};

// struct TAtrMnemo

class ip // Информационная пара
{
public:
	int atr = 0;
	LoadPoint Load = {0, nullptr }; // Указатель на нагрузку с типом даннных
	~ip() { }//Load.Clear(); };
	void copy(ip *IP)// Копирование ИП
	{
		atr = IP->atr;
		Load.Point = IP->Load.Point;
		Load.Type = IP->Load.Type;
	};
	void copy(void *IP) { copy(*(ip*)IP); }// Копирование ИП
	void copy(ip &IP)// Копирование ИП
	{
		atr = IP.atr;
		Load.Copy(&IP.Load);
	};
	void copy(LoadPoint &LP)// Копирование ИП
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
	ip* Сlone()
	{
		ip* ip_new = new ip;
		ip_new->copy(*this);
		return ip_new;
	};

	vector<ip>* СloneToIC()
	{
		vector<ip>* t = new vector<ip>;
		t->push_back(*this);
		return t;
	};

};

typedef  vector<vector<ip>*> ICVect;
typedef  vector<ip>* IC_type;

struct deletedIC //удаленная ИП
{
	vector<ip*>* IC; // информационная капсула, содержащая удаленную ИП
	void* programm; // указатель на милипрограмму (ИК, содержащую набор милликоманд)
};

class FUModeling
{
public:
	bool SchedulerFlag = false; // Флаг запуска МК планироващиком
	vector<ip> qmk; // Очередь МК для моделирования
	bool ManualMode = false; // Режим ручного управления (для моделирования)
	map<int, double> MkTime; // Время выполнения операций (для моделирования)
//	int CoreFreeMK; // МК освобождения ядра для планировщика вычислений
	void* scheduler = nullptr; // Указатель на контекст планировщика вычислений
//	double Dtime = 0; // Время выполнения текущей команды
};

class FU {  // Ядро функционального устройства
public:
	virtual void ProgFU(int MK, LoadPoint Load) {}; // Реализация логики работы ФУ
//	virtual void ProgFU(LoadPoint MK, LoadPoint Load)
//	{ if ((MK.Type >> 1) == Dint) ProgFU(Load.ToInt(), Load); }; // Реализация логики работы ФУ
	void Scheduling(); // Запуск МК после разрешенрия планировщика
	int FUtype = 0; // Тип ФУ
	string FUName; //  Имя ФУ
//	int MkStage = 0; // Стадия выполнения милликоманды (когда МК выполняется за несколько стадий)
	bool Active = true;

	FUModeling *Modeling=nullptr; // Моделирование

	FU() { Bus = nullptr; };
	FU(FU *BusContext) { Bus = BusContext; };

	void MkExec(int MK, LoadPoint Load, FU* BusContext = nullptr); // Выполнить одну милликоманду 
	void MkExec(LoadPoint MK, LoadPoint Load, FU* BusContext = nullptr); // Выдача МК с нагрузкой
	void ProgExec(void* Uk, FU* Bus = nullptr, vector<ip>::iterator* Start = nullptr); // Исполнение программы из ИК
	void ProgExec(LoadPoint Uk, FU* Bus = nullptr, vector<ip>::iterator* Start = nullptr); // Исполнение программы из ИК
	int SubAtr=SubMk; // Атрибут входа в подпрограмму

	FU *Bus; // Ссылка на контекст Шины
	int FUMkRange = 1000; // Диапазон МК для каждого ФУ
	int ProgStop = 0; // Флаг остановки программы, выполняемой ProgExec
	bool ProgStopAll = false; // Флаг остановки всех запущенных на выполнение миллипрограммы для данного ФУ
//	bool RepeatFlag = false; // Флаг повторения программы
	void CommonMk(int Mk, LoadPoint Uk); // Выполнение общих МК для ФУ
	IC_type PrefixProg = nullptr, PostfixProg = nullptr, Prog = nullptr, ElseProg = nullptr; // Программы презапуска и послезапуска во время прихода МК, просто программа, альтернативная программа
private:
//	int ProgSetFaze = 0; // Фаза для установки программы ProgSet, ElseProgSet
};

void ICDel(void* Uk);// Удаление ИК

void* ICCopy(LoadPoint uk);// Копирование ИК

//void ProgExec(void *Uk, FU* Bus, vector<ip>::iterator *Start=nullptr); // Исполнение программы из ИК

bool LoadCmp(LoadPoint x, LoadPoint y); // Сравнение двух нагрузок ИП
bool IPCmp(ip* x, ip* y); // Сравнение двух  ИП
void AtrProgExec(vector<ip>* Prog, int Atr, FU* Bus=nullptr, bool AfterContinue = false); // Найти в ИК ИП с атрибутом Atr и выполнить программу либо по адр. в нагрузке, либо после найденной ИП
//void AddOrReplIPAtr(vector<ip>* UK, ip* IP); // 
ip* AtrFind(void* IC, int Atr); // Поиск в ИК ИП с заданным атрибутом. На выходе указатель на ИП или NULLL
