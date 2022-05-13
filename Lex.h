#pragma once
#include "Consts.h"
#include <set>
#include <map>
#include <vector>

struct MkFu
{
	int Mk;
	FU* Fu;
};

class Lex : public FU {
private:
	void LexOut(bool Copy=false, int MK = -1);
	string ABC_templ = "_QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm"; // ������� ��������
	string Digit_templ = "0123456789"; // --- ������� �����
	string Digit_seps_templ = "."; // --- ������� ������������ �����
	set<string> Seps_templ = { "//=", "!!=", "&&=", "||=", "&&=", "^^=",\
	"^=", "*=", "%=", "/=", "//", "++", "--", "-=","+=","<>", ">=", "<=", "!!", "!=", "||", "|=", "&&", "&=", "^^", "^=",\
	"<", ">", "~", "`", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "+", "=", "-", "{", "}", "[", "]", "?", ";", ":", ",", ".", "\\", "/", "|", "\""};// ������� ������������
	set<char> ABC, Digit, DigitSeps; // --- DigitSeps - ���������, �������� ����������� ����� � ������� ����� �����
	set<string> Seps;
	IC_type StartProg = nullptr, StopProg = nullptr, FinProg = nullptr; // ���������, ����������� ��� ������� �������� ������������ �������
	string EOL = "\n"; // ������� ��������� ������
	vector<string> TrueConst = { "true","Ture" }; // ��������� true
	vector<string> FalseConst = { "false","False" }; // ��������� false
	int ProgLevel = 0; // ������� ��������� �����������
	char ProgBracket = '{', ProgFinBracket = '}'; // ������� ����������� �������
	void* TabErrProg = nullptr; // ��������� ��������� ������ ���������
public:
	void ProgFU(int MK, LoadPoint Load);
	Lex(FU *BusContext=nullptr, FU *Templ=nullptr);
	Lex() ;
	FU *Receiver = nullptr;
	int ReceiverMK = 0;
	int S = 0; // ����� ��������� ������������� ��������
	bool Work = true; // ���� �������� ������ �������
	int MnemoAtr = -2, SeperatAtr=-4, IntAtr=-10, DoubleAtr=-3, BoolAtr=-5, StrAtr=-6, ConstAtr=-13;
	int ib = 0, SizeBuf = 5; // ������� ������� �������� �� �������� ������� � ������ ������
	ip *LexBuf; // ����� �������� ������
	void *ErrProg=nullptr; // ���������, ����������� ��� ������
	map<int,MkFu> UnicAtr; // ������ ������������� ���������, �� ������� ���� ��������� ������� ��
	// ����� �������� ������ {"dsfsdf",-3,"dfsdfs",""}
//	void Debug(char i, int S, string FigureBuf); // --- ��� �������, ����� �������
};