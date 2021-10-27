// ФУ Консоль
#pragma once
#include "Consts.h"
#include <fstream>
class Console : public FU
{
private:
	string prefix;
	string filename = "";
	ofstream fout;
	FILE* streamOut, *streamIn;
	string Sep = " ", End = "\n"; // Строка-разделитель и строка в конце вывода
	string ArrayBracketStart = "[", ArrayBracketFin = "]"; // Начальная и конечная скобки для вывода вектора
public:
	void ProgFU(int MK, LoadPoint Load) override;
	Console(FU *BusContext, FU *Templ) : FU(BusContext) { Bus = BusContext; };
	Console() : FU() { Bus = nullptr; };
private:
};
