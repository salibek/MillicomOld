// ФУ Список
#pragma once
#include "Consts.h"
#include "Search.h"

class ListContext
{
public:
	vector<ip>* ListHead = nullptr; // Указатель на начало списка
	ip* LineUk = nullptr; // Указатель на найленную строку списка
	int LineNum = -1, LineNumOld = -1; // Номер первой совпадающей линии, номер предыдущей совпадающей линии
	int LineCount = 0; // Количество найденных строк
	bool StopSearch = false; // Флаг прекращения поиска в текущей иерархии
};

class List : public FU
{
public:
	void ProgFU(int MK, LoadPoint Load) override;
	vector<ListContext> Stack;
	int MultiLineMode = 0; // 0 - поиск только первого совпадения, 1 - поиск всех совпадений
	int MultiLavelSearch = 0; // Режим поиска не нескольких уровнях списка
	// 0 - на текущем уровне, 1 - на всех уровнях, 2- только в текущей иерархии
	int ReceiverMk = 0; // Мк для выдаваемой лексемы
	int* ReceiverMkUk = &ReceiverMk; // Указатель на Мк для выдаваемой лексемы
	// Выделить в контекст
/*	vector<ip>* ListHead = nullptr; // Указатель на начало списка
	ip* LineUk=nullptr; // Указатель на найленную строку списка
	int LineNum = -1, LineNumOld = -1; // Номер первой совпадающей линии, номер предыдущей совпадающей линии
	int MultiLineMode = 0; // 0 - поиск только первого совпадения, 1 - поиск всех совпадений
	int ReceiverMk = 0; // Мк для выдаваемой лексемы
	int *ReceiverMkUk = &ReceiverMk; // Указатель на Мк для выдаваемой лексемы
	int LineCount = 0; // Количество найденных строк
*/	// -----
	int SearchMode = 0; // Режим поиска 0 - локальный поиск 1 - общий поиск (по всем подспискам), 2 - восходящий поиск (с текущего уровне и до корневого)
	int LineAtr = Atr; // Атрибут линии списка
	int SubLineAtr = Atr; // Атрибут подсписка
	void* LessProg = nullptr, * BibberProg = nullptr, *EQProg = nullptr, *LessEQProg = nullptr, *BibberEQProg = nullptr;
	vector<int> LineStack; // Стек номеров линий
	Search Searcher; // Устройство поиска
	void *FailLineProg = nullptr; // Программа, выполняемая в случае неудачного поиска в текущей линии списка
	void *FailProg = nullptr; // Программа, выполняемаЯ в случае неудачного поиска во всем  списке
	void* SuссessLineProg = nullptr, * SuссessProg = nullptr;
	vector<ip> *DefProg = nullptr;

	List(FU *BusContext, FU *Templ) : FU(BusContext) { ProgFU(0, { 0, nullptr }); Bus = BusContext; Searcher.MainFU = this; };
	List() : FU() { List(nullptr, nullptr); };
private:
};