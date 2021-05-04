// ФУ Список
#pragma once
#include "Consts.h"
#include "Search.h"

class List : public FU
{
public:
	void ProgFU(int MK, LoadPoint Load) override;
	vector<ip>* ListHead = nullptr; // Указатель на начало списка
	ip* LineUk=nullptr; // Указатель на найленную строку списка
	int LineNum = -1, LineNumOld = -1; // Номер первой совпадающей линии, номер предыдущей совпадающей линии
	int MultiLineMode = 0; // 0 - поиск только первого совпадения, 1 - поиск всех совпадений
	int ReceiverMk = 0; // Мк для выдаваемой лексемы
	int *ReceiverMkUk = &ReceiverMk; // Указатель на Мк для выдаваемой лексемы
	vector<int> LineStack; // Стек номеров линий
	Search Searcher;
	IC_type FailAllProg = nullptr;
//	vector<ip> *LineProg = nullptr;
	vector<ip> *DefProg = nullptr;
	List(FU *BusContext, FU *Templ) : FU(BusContext) { ProgFU(0, { 0, nullptr }); Bus = BusContext; Searcher.MainFU = this; };
	List() : FU() { List(nullptr, nullptr); };
private:
};