	#include "stdafx.h"
	#include "Lex.h"
	#include <string.h>

	using namespace std;

	void Lex::LexOut(bool Copy,int MK) // ������ ������� �����������
	{
		auto uk = UnicAtr.find(LexBuf[ib].atr);
		if (MK < 0)MK = ReceiverMK;
		if (uk!= UnicAtr.end())
		{
			if (uk->second.Fu != nullptr && uk->second.Mk!= 0)
				if(Copy)
					uk->second.Fu->ProgFU(uk->second.Mk, { TIP, &LexBuf[ib] });
				else
					uk->second.Fu->ProgFU(uk->second.Mk, { TIP, LexBuf[ib].�lone() });
		}
		else
			if (Receiver != nullptr) 
				if (Copy)
					Receiver->ProgFU(MK, { TIP, LexBuf[ib].�lone() });
				else
					Receiver->ProgFU(MK, { TIP, &LexBuf[ib] });
	}

	void Lex::ProgFU(int MK, LoadPoint Load)
	{
		// �������� ����� �� � ���������
		switch (MK)
 		{
		case 0: // Reset
			S = 0; // ����� ��������� ������������� ��������
				   //		FigureBuf = "";
			UnicAtr.clear();
			ReceiverMK = 0;
			ErrProg = nullptr;
			break;
		case 5: //ReceiverMKSet
			if (Load.Type >> 1 == Dint) ReceiverMK = *(int*)Load.Point; break;
		case 10: //ErrProgSet
			ErrProg = (vector<ip> *)Load.Point;
			break;
		case 12: // StartProgSet ���������� ���������, ����������� ����� ������� ���������� 
			StartProg = (IC_type)Load.Point;
			break;
		case 13: // StopProgSet ���������� ���������, ����������� ��� ��������� ���������� ������������� ������� �� �� Stop 
			StopProg = (IC_type)Load.Point;
			break;
		case 14: // FinProgSet  ���������� ���������, ����������� ����� ��������� ������� ������
			FinProg = (IC_type)Load.Point;
			break;
		case 15:// UnicAtrSet ���������� ���������� �������
			UnicAtr[*(int*)Load.Point] = { 0,Bus };
			break;
		case 16:// UnicMkSet ���������� �� ��� ����������� ��������
			if(UnicAtr.size())
				(--UnicAtr.end())->second.Mk= *(int*)Load.Point;
			break;
		case 17:// UnicFuSet ���������� �������� ��� ����������� ��������
			if (UnicAtr.size())
				(--UnicAtr.end())->second.Fu = (FU*)Load.Point;
			break;
		case 18:// UnicReset �������� ������ ���������� ���������
			UnicAtr.clear();
			break;
		case 20: // LexBufSizeSet ���������� ������ ������ ������
			if (Load.Type >> 1 != Dint) break;
			for (int i = 0; i < SizeBuf; LexBuf[i++].Load.Clear());
			delete[] LexBuf;
			SizeBuf = *(int*)Load.Point;
			LexBuf = new ip[SizeBuf];
			for (int i = 0; i < SizeBuf; LexBuf[i++].Load = { 0,nullptr });
			break;
		case 26: // NoUnucToReseiver ������ �������, �� �������� ���������� ��������� (��� ������� �������� �������� ������� �������)
			if (Load.Point == nullptr)
				MkExec(ReceiverMK, LexBuf[ib].Load, Receiver);
			else
			{
				ib = (ib + 1) % SizeBuf;
				LexBuf[ib].Load.Clear(); // ������� �������� ��
				LexBuf[ib].copy(Load);
				MkExec(Load, LexBuf[ib].Load, Receiver);
			}
			break;
		case 27: //Replace �������� ������� ������� � ������
		case 28: //ReplaceToReceiver ������ ������� �� �������� �� ����������, ������� ������� ������� � ������
		case 29: //ReplaceCopyToReceiver ������ ����� ������� �� �������� �� ����������, ������� ������� ������� � ������
		case 30: //ToReceiver ������ ������� �� �������� �� ���������� (���� �������� nil, �� �������� ������� �������)
		case 31: //CopyToReceiver ������ ����� ������� �� �������� �� ����������
			if(MK==30 && Load.Point==nullptr)	{
				LexOut(false);
				break;
			}
			if(MK==30 || MK==31) ib = (ib + 1) % SizeBuf;
			LexBuf[ib].Load.Clear(); // ������� �������� ��
			LexBuf[ib].copy(Load);
			if(MK!=27)LexOut(MK==31);
			break;
//		case 32: //LastLexemaToReceiver ������ ��������� ������� ����������
//		case 33: //LastLexemaCopyToReceiver ������ ��������� ������� ����������
//			if (Receiver != nullptr)
//				if (MK==33)
//					Receiver->ProgFU(ReceiverMK, { TIP, LexBuf[ib].�lone() });
//				else
//					Receiver->ProgFU(ReceiverMK, { TIP, &LexBuf[ib] });
//	//		LexOut(MK==33);
//			break;
		case 35: //OutMk ������ MK c ��������� �������� (���� nil � ��������, �� �������� �� Receiver)
			if (Load.Point == nullptr)
			{
				//LexOut(false);
				Receiver->ProgFU(ReceiverMK, { TIP, &LexBuf[ib] });
			}
			else

//			if (Load.Type >> 1 == Dint)
//				LexOut(false,Load.ToInt())
				Receiver->ProgFU(Load, { TIP, &LexBuf[ib] });
		//	else if(Load.Point==0)

			break;
		case 36: // CopyOutMk ������ �� � ������ ��������� ������� (���� nil � ��������, �� �������� �� Receiver)
			if (Load.Point!=nullptr) 
				Receiver->ProgFU(Load, { TIP, LexBuf[ib].�lone() });
			else
				Receiver->ProgFU(ReceiverMK, { TIP, LexBuf[ib].�lone() });
			break;
		
//		case 40: //PrevToReseiver ������ ���������� ������� ����������
//			if (Receiver != nullptr && Load.Type >> 1 == Dint) 
//				Receiver->ProgFU(*(int*)Load.Point, { TIP, &LexBuf[(ib-1+ SizeBuf)% SizeBuf] });
//			break;
//		case 41: //PrevCopyToReseiver ������ ����� ���������� ������� ����������
//			if (Receiver != nullptr && Load.Type >> 1 == Dint) 
//				Receiver->ProgFU(*(int*)Load.Point, { TIP, LexBuf[(ib - 1 + SizeBuf) % SizeBuf].�lone() });
//			break;
		case 45: //PrevOutMk ������ �� � ���������� �������� (���� �������� nil, �� �������� �� Receiver)
			if (Load.Point==nullptr)
				Receiver->ProgFU(ReceiverMK, { TIP, &LexBuf[(ib - 1 + SizeBuf) % SizeBuf] });
			else
				Receiver->ProgFU(Load, { TIP, &LexBuf[(ib - 1 + SizeBuf) % SizeBuf] });
			break;
		case 46: //PrevCopyOutMk ������ �� � ������ ���������� ������� (���� �������� nil, �� �������� �� Receiver)
			if (Load.Point == nullptr)
				Receiver->ProgFU(ReceiverMK, { TIP, LexBuf[(ib - 1 + SizeBuf) % SizeBuf].�lone() });
			else	
				Receiver->ProgFU(Load, { TIP, LexBuf[(ib - 1 + SizeBuf) % SizeBuf].�lone() });
			break;
		case 50: // AtrSet ���������� ������� ��������� �������
			LexBuf[ib].atr=Load.ToInt();
			break;
		case 51: // PrevAtrSet ���������� ������� ���������� �������
			LexBuf[(ib - 1 + SizeBuf) % SizeBuf].atr = Load.ToInt();
			break;
		case 55: // LoadSet ���������� ��������� � ��������� �������
			LexBuf[ib].Load = Load;
			break;
		case 56: // PrevLoadSet ���������� ��������� � ���������� �������
			LexBuf[(ib - 1 + SizeBuf) % SizeBuf].Load = Load;
			break;
		case 57: // LoadCopySet ���������� ����� ��������� � ��������� �������
			LexBuf[ib].Load.Copy(&Load);
			break;
		case 58: // PrevLoadCopySet ���������� ����� ��������� � ���������� �������
			LexBuf[(ib - 1 + SizeBuf) % SizeBuf].Load.Copy(&Load);
			break;
		case 65: // VarSet ���������� ��� ���������� ��� �������� ��������� �������
			LexBuf[ib].Load.Type |= 1;
			LexBuf[ib].Load.Type --;
			break;
		case 66: // PrevVarSet ���������� ��� ���������� ��� �������� ���������� �������
			LexBuf[(ib - 1 + SizeBuf) % SizeBuf].Load.Type |= 1;
			LexBuf[(ib - 1 + SizeBuf) % SizeBuf].Load.Type--;
			break;

		case 99: // Stop ���������� ����������� ������
			Work = false;
			ProgExec((IC_type)StopProg,Bus,nullptr); // ��������� ��������� �� �������� ������������ �������
			break;
		case 100: // Lexing
		{
//			ProgExec((IC_type)StartProg,Bus);
			if (Load.Type >> 1 == Dstring && *((string*)Load.Point) == "")
			{
				ib = (ib + 1) % SizeBuf;
				LexBuf[ib].Load.Clear(); // ������� �������� ��
				LexBuf[ib] = { StrAtr,Tstring , new string("") };
				LexOut();
			}
			(*(string*)Load.Point) += " "; // ���������� ������� ��������� ��������
			Work = true;
			string FigureBuf;
			for (auto i = (*(string*)Load.Point).begin(); i != (*(string*)Load.Point).end() && Work; i++)
				switch (S)
				{
				case 0: // ��������� ���������
					if (*i == ' ') break;
					if (*i == '"')
					{
						FigureBuf = "";
						S = 4;
						break;
					}
					if (Seps.count(*i))
					{
						ib = (ib + 1) % SizeBuf;
						LexBuf[ib].Load.Clear();
						string  *tstr = new string;
						
						*tstr = *i;
						if (i + 1 != (*(string*)Load.Point).end())
						{
							*tstr += *(i + 1);
							if (i + 2 != (*(string*)Load.Point).end())
								*tstr += *(i + 2);
						}
						if (i + 1 != (*(string*)Load.Point).end() && i + 2 != (*(string*)Load.Point).end() && Seps.count(*(i + 1)) && Seps.count(*(i + 2)) && SepsComlex3.count(*tstr) )
						{
							LexBuf[ib] = { SeperatAtr,Tstring , tstr };
							i += 2;
							LexOut();
							break;
						}

						*tstr = *i;
						if (i + 1 != (*(string*)Load.Point).end()) *tstr += *(i + 1);
						if (i + 1 != (*(string*)Load.Point).end() && Seps.count(*(i + 1)) && SepsComlex2.count(*tstr))
						{
							LexBuf[ib] = { SeperatAtr,Tstring , tstr };
							i++;
							LexOut();
							break;
						}
						*tstr = *i;
						LexBuf[ib] = { SeperatAtr,Tstring , tstr };
						LexOut();
						break;
					}
					if (*i >= '0' && *i <= '9')
					{
						FigureBuf = *i;
						S = 1;
						ib = (ib + 1) % SizeBuf; // ������ ������ ������
						break;
					}
					if (ABC.count(*i))
					{
						S = 3;
						FigureBuf = *i;
						break;
					}
					Work = false;
					if (ErrProg != nullptr) ProgExec(ErrProg, Bus,nullptr);
					break;
				case 1: // ����������� �����
					if (*i >= '0' && *i <= '9')
					{
						FigureBuf += *i;
						break;
					}
					if (*i == '.')
					{
						FigureBuf = FigureBuf + (*i);
						S = 2;
						break;
					}
					if (Seps.count(*i) || *i == ' ')
					{
						int  *tint = new int;
						*tint = atoi(FigureBuf.c_str());
						ib = (ib + 1) % SizeBuf;
						LexBuf[ib].Load.Clear(); // ������� �������� ��
						LexBuf[ib] = { IntAtr,Tint , tint };
						LexOut();

						S = 0;
						i--; // ��� ��������� ����������
						break;
					}
					Work = false;
					ProgExec(ErrProg, Bus, nullptr);
					break;
				case 2: // ����� ���������� �����
					if (*i >= '0' && *i <= '9')
					{
						FigureBuf = FigureBuf + (*i);
						break;
					}
					if (Seps.count(*i) || *i == ' ')
					{
						double *ft = new double;
						*ft = atof(FigureBuf.c_str());
						ib = (ib + 1) % SizeBuf;
						LexBuf[ib].Load.Clear();
						LexBuf[ib] = { DoubleAtr, Tdouble, ft };
						LexOut();
						S = 0;
						i--;
					}
					Work = false;
					ProgExec(ErrProg, Bus, nullptr);
					break;
				case 3: // ���������
					if (Seps.count(*i) || *i == ' ')
					{
						S = 0;
						i--;
						string *st = new string;
						*st = FigureBuf;
						ib = (ib + 1) % SizeBuf;
						LexBuf[ib].Load.Clear();
						LexBuf[ib] = { MnemoAtr, Tstring, st };
						LexOut();
						break;
					}
					if (ABC.count(*i) || *i >= '0' && *i <= '9')
					{
						FigureBuf += *i;
						break;
					}
					Work = false;
					ProgExec(ErrProg, Bus, nullptr);
					break;
				case 4:
					if (*i != '"'){
						FigureBuf += *i; break;
					}
					else
					{
						S = 0;
						string *st = new string;
						*st = FigureBuf;
						ib = (ib + 1) % SizeBuf;
						LexBuf[ib].Load.Clear();
						LexBuf[ib] = { StrAtr, Cstring, st };
						LexOut();
					}
					Work = false;
					ProgExec(ErrProg, Bus, nullptr);
					break;
				case 5:
					break;
				default:
					break;
				}
		}
		ProgExec(FinProg); // ��������� 
		break;
		default:
			CommonMk(MK, Load);
		}
	}

	Lex::Lex(FU *BusContext, FU *Templ) 
	{
		Bus = BusContext;
		Receiver = BusContext;
		copy(ABC_templ.begin(), ABC_templ.end(), inserter(ABC, ABC.end()));
		copy(Seps_templ.begin(), Seps_templ.end(), inserter(Seps, Seps.end()));
		LexBuf = new ip[SizeBuf];
		for (int i = 0; i < SizeBuf; LexBuf[i++].Load = { 0,nullptr });
		ProgFU(0, {0,nullptr});
	}

	Lex::Lex() : FU() 
	{
		Lex(nullptr, nullptr); 
	}
