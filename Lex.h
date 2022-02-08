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
	set<string> Seps_templ = { "//=", "!!=", "&&=", "||=", "&&=", "^^=",\
	"^=", "*=", "%=", "/=", "//", "++", "--", "-=","+=","<>", ">=", "<=", "!!", "!=", "||", "|=", "&&", "&=", "^^", "^=",\
	"<", ">", "~", "`", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "+", "=", "-", "{", "}", "[", "]", "?", ";", ":", ",", ".", "\\", "/", "|", "\""};// ������� ������������
	set<char> ABC, Digit;
	set<string> Seps;
	IC_type StartProg = nullptr, StopProg = nullptr, FinProg = nullptr; // ���������, ����������� ��� ������� �������� ������������ �������
public:
	void ProgFU(int MK, LoadPoint Load);
	Lex(FU *BusContext, FU *Templ);
	Lex();
	FU *Receiver = nullptr;
	int ReceiverMK = 0;
	int S = 0; // ����� ��������� ������������� ��������
	bool Work = true; // ���� �������� ������ �������
	int MnemoAtr = -2, SeperatAtr=-4, IntAtr=-10, DoubleAtr=-3, BoolAtr=-5, StrAtr=-6, CharAtr=-11;
	int ib = 0, SizeBuf = 5; // ������� ������� �������� �� �������� ������� � ������ ������
	ip *LexBuf; // ����� �������� ������
	vector<ip> *ErrProg=nullptr; // ���������, ����������� ��� ������
	map<int,MkFu> UnicAtr; // ������ ������������� ���������, �� ������� ���� ��������� ������� ��
	// ����� �������� ������ {"dsfsdf",-3,"dfsdfs",""}
};