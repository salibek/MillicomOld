// Описание основных констант и информационных конструкций
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>

using namespace std; 

// Типы переменных
const int Tvoid = 0, Tint = 2, Tfloat = 4, Tdouble = 6, Tchar = 8, Tstring = 10, TIP = 12, Tbool = 14, TIC = 16;
const int TPPoint = 18, TGraph=20, TFU=22;
// Типы констант
const int Cvoid = 1, Cint = 3, Cfloat = 5, Cdouble = 7, Cchar = 9, Cstring = 11, CIP = 13, Cbool = 15, CIC = 17;
const int CPPoint = 19, CGraph = 21, CFU = 23;
// Общие типы данных (остаток от целочисленного деления на 2 типа переменной или константы)
const int Dvoid=0, Dint = 1, Dfloat = 2, Ddouble = 3, Dchar = 4, Dstring = 5, DIP = 6, Dbool = 7, DIC = 8;
const int DPPoint = 9, DGraph = 10, DFU = 11;

// Типы ФУ
const int FUBus = 0, FUCons = 1, FUStrGen = 2, FULex = 3, FUList = 4, FUFind = 5;

// Весы типов
const vector<int> w_type = { 10, 30, 40, 50, 60, 70, 20 };

// Общие атрибуты
const int ProgAtr = -100, Atr=-60;

bool isIPinIC(void* iP, void* iC); //проверка, что ИК входит в ИП

class LoadPoint
{
public:
	unsigned int Type = 0; // Неизвестный тип
	void *Point;
	bool IsConvert(unsigned int T) {}; // Тест на возможность конвертации значения из Point в определенный тип
	int ToInt() {return Point==nullptr? 0 :  *(int*)Point; }; // Перевод в integer
	double ToDouble() {
		switch (Type>>1)
		{
		case Ddouble: return *(double*)Point; break;
		case Dfloat: return *(float*)Point; break;
		case Dint: return *(int*)Point; break;
		case Dbool: return *(bool*)Point; break;
		default:
			return 0;
			break;
		}
	}; // Перевод в integer
	bool ToBool() { return Point == nullptr ? 0 : *(bool*)Point; }; // Перевод в integer
	char ToChar() { return Point == nullptr ? 0 : *(char*)Point; }; // Перевод в integer
	string ToStr() { return Point == nullptr ? "" : *(string*)Point; }; // Перевод в integer
	void Copy(LoadPoint *LP);
	void Clear(); // Сброс нагрузки ИП
	void VarClear(); // Сброс нагрузки ИП в том числе и с переменной (переменная стирается)
	void print(void* AtrMnemo=nullptr, string offset=""); // Параметр - указатель на табл. мнемоник атрибутов
	LoadPoint Clone(); // Дублировать нагрузку
	void ConstTypeSet(bool F = true) { if (F)Type |= 1; else VarTypeSet(); }; // Установить тип 'константа'
    // Установить тип 'переменная'
	void VarTypeSet(bool F = true) {
		if (!F) { ConstTypeSet(); return; } Type |= 1; if (Type >= 0)Type -= 1; else Type += 1;}
	LoadPoint IpOut() // Возвращается указатель на ИП или на первую ИП из ИК, иначе null
	{
		if (Type >> 1 == DIP) return *this;
//		if (Type >> 1 == DIC) return { DIP,((IC_type)Point)->begin()._Ptr};
//		return { 0,nullptr };
	};
	bool IpTest() { return (Type >> 1 == DIP || Type >> 1 == DIC); } // Является ли нагрузка ИП?

};

// struct TAtrMnrmo

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
	ip* сlone()
	{
		ip* ip_new = new ip;
		ip_new->copy(*this);
		return ip_new;
	}

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
	bool Active = true;

	FUModeling Modeling; // Моделирование

	FU() { Bus = nullptr; };
	FU(FU *BusContext) { Bus = BusContext; };
//	FU* Scheduler = nullptr; // Контекст планировщика вычислений

	void MkExec(int MK, LoadPoint Load, FU* BusContext = nullptr); // Выполнить одну милликоманду 
	void MkExec(LoadPoint MK, LoadPoint Load, FU* BusContext); // Выдача МК с нагрузкой
    void ProgExec(void *Uk, FU* Bus=nullptr, vector<ip>::iterator *Start=nullptr); // Исполнение программы из ИК

	FU *Bus; // Ссылка на контекст Шины
	int FUMkRange = 1000; // Диапазон МК для каждого ФУ
	bool ProgStop = false; // Флаг остановки программы, выполняемой ProgExec

	void CommonMk(int Mk, LoadPoint Uk); // Выполнение общих МК для ФУ
	IC_type PrefixProg = nullptr, PostfixProg = nullptr, Prog=nullptr; // Программы презапуска и послезапуска во время прихода МК, просто программа
};

void ICDel(void* Uk);// Удаление ИК

void* ICCopy(LoadPoint uk);// Копирование ИК

//void ProgExec(void *Uk, FU* Bus, vector<ip>::iterator *Start=nullptr); // Исполнение программы из ИК

bool LoadCmp(LoadPoint x, LoadPoint y); // Сравнение двух нагрузок ИП
bool IPCmp(ip* x, ip* y); // Сравнение двух  ИП
void AtrProgExec(vector<ip>* Prog, int Atr, FU* Bus=nullptr, bool AfterContinue = false); // Найти в ИК ИП с атрибутом Atr и выполнить программу либо по адр. в нагрузке, либо после найденной ИП
//void AddOrReplIPAtr(vector<ip>* UK, ip* IP); // 
ip* AtrFind(void* IC, int Atr); // Поиск в ИК ИП с заданным атрибутом. На выходе указатель на ИП или NULLL
