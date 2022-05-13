// �� ������
#include "stdafx.h"
#include "List.h"

using namespace std;

void List::ProgFU(int MK, LoadPoint Load)
{
	ProgExec(PrefixProg); // ��������������� ���������, ���������� ��� ������� ����� ��
	switch (MK)
	{
	case 0: // Reset
		Searcher.Clear();
		Stack.clear();// ������� ����� ������� ������
		Stack.push_back({});
		break;
	case 1:	// Set
		Stack.back().ListHead = (IC_type)Load.Point;
		break;
	case 2:// Out ������ ������ �� ������
		if (Load.Type >> 1 == Cvoid)
			*(void**)Load.Point = Stack.back().ListHead;
		break;
	case 3:// OutMk ������ �� �� ������� �� ������
		MkExec(Load, { TIC,(void*)Stack.back().ListHead });
		break;
	case 5:	// MultiLineModeSet 
		MultiLineMode = Load.ToInt(1);
		break;
	case 6: // MultyListModeSet ���������� ����� ��������������� ������ ��� ������ (true �� ���������)
		MultyListMode = Load.ToBool(true);
		break;
	case 7: // MkModeSet ����� ���������� ���� �� � ��-������� (��-�� ��������� ����� �������, ������ �������� ������ 0) ��� ������ �������� ����� ���������������
		Searcher.MkMode = Load.ToBool(true);
		break;
	case 8:// EmptyProgExec ��������� ���������, ���� ������ ����
	case 9:// FullExec ��������� ���������, ���� ������ �� ����
	case 14: // OneLineExec ��������� ���������, ���� � ������ ������ ���� ������
	case 13: // MoreOneLineExec ��������� ���������, ���� � ������ ������ ����� ������
		if (MK==8 && (Stack.back().ListHead == nullptr || Stack.back().ListHead->size() == 0)||\
			Stack.back().ListHead != nullptr && Stack.back().ListHead->size() != 0 &&\
			(MK==9 || MK == 14 && Stack.back().ListHead->size() == 1 ||\
				MK == 13 && Stack.back().ListHead->size() >1 ) )
			if (Load.Point != nullptr && Load.Type >> 1 == DIC)
				ProgExec(Load);
			else
				ProgExec(Prog);
		else if(Load.Point == nullptr)
			ProgExec(ElseProg);
		break;
	case 10: // SuccessLineProgSet ���������� ��������� �� ���������, ����������� ��� ������� ������ � ����� ������
		Searcher.SuccessProg = (IC_type)Load.Point;
		break;
	case 11: // SuccessAfterLineProgSet ���������� ��������� �� ���������, ����������� ��� ������� ������ � ����� ������ ����� ���������� �������� �����
		Searcher.SuccessAfterProg = (IC_type)Load.Point;
		break;
	case 12: // Su��essProgSet ���������� ��������� �� ���������, ����������� � ������ �������� ������ �� ����  ������
		Su��essProg = Load.Point;
		break;
	case 15: // FailLineProgSet ���������� ��������� �� ���������, ����������� � ������ ���������� ������ � ����� ������
		Searcher.FailProg = (IC_type)Load.Point;
		break;
	case 16: // FailAfterLineProgSet ���������� ��������� �� ���������, ����������� � ������ ���������� ������ � ����� ������ ����� ���������� �������� �����
		Searcher.FailAfterProg = (IC_type)Load.Point;
		break;
	case 17: // FailProgSet ���������� ��������� �� ���������, ����������� � ������ ���������� ������ �� ����  ������
		FailProg = Load.Point;
		break;
	case 18: //  ���������� ��������� �� ���������, ����������� � ������ �������� ������ � ������� �����
		Su��essLineProg = Load.Point;
		break;
	case 20: // ProgAtrSet ���������� ������� ����� ������ �� ���������
		if (Load.Point != nullptr && Load.Type >> 1 == Dint)
			Searcher.Prog_atr = Load.ToInt();
		break;
	case 21: //LineAtrDef ���������� ������� ����� ������ �� ���������
		LineAtr = Load.ToInt();
		break;
	case 22: //SubAtrDef ���������� ������� ��������� �� ���������
		SubAtr = Load.ToInt();
		break;
	case 25: // BackOut ������ ������� ������ ��� ������
		if (Load.Type == TPPoint)
			(*(LoadPoint*)Load.Point) = Searcher.Obj;
		break;
	case 30: // BackOutMk ������� �� �� ������� �������� ��� ������
		MkExec(Load, Searcher.Obj.Clone());
		break;
	case 31: // CopyBackOutMk ������� �� �� ������� �������� ��� ������
		MkExec(Load, Searcher.Obj.Clone());
		break;

	case 35: // LoadBackOut ������ �������� �������� ������� ��� ������
		if (Searcher.Obj.Type >> 1 == DIC)
			Load.Point = ((IC_type)(Searcher.Obj.Point))->begin()->Load.Point;
		else if (Searcher.Obj.Type >> 1 == DIP)
			Load.Point = ((ip*)(Searcher.Obj.Point))->Load.Point;
		break;
	case 36: // LoadBackOutMk ������ �� � ��������� �������� ������� ��� ������
		if (Load.Type >> 1 == Dint)
			if(Searcher.Obj.Type>>1==DIC)
				MkExec(*((int*)Load.Point), ((IC_type)(Searcher.Obj.Point))->begin()->Load);
			else if(Searcher.Obj.Type >> 1 == DIP)
				MkExec(*((int*)Load.Point), ((ip*)(Searcher.Obj.Point))->Load);
		break;

	case 100: // RezOut ������ ���������� ���������
		if (Load.Type == Tbool)
			Load.Write(Searcher.Rez);
		break;
	case 101: // RezOutMk ������ �� � ����������� ���������
		MkExec(*(int*)(Load.Point), { Cbool , &Searcher.Rez });
		break;
	case 105: // MkAtrAdd �������� ��
		if (Load.Type >> 1 == Dint)
			Searcher.MkAtrAdd(*(int*)Load.Point);
		break;
	case 106: // MkAtrClear �������� ������ ��
		Searcher.MkAtrClear();
		break;

	case 120: // MarkAtrSet ���������� ������� ������� ������
		if (Stack.back().LineUk != nullptr)
			Stack.back().LineUk->atr = Load.ToInt();
		break;
	case 121: // LastMarkAtrSet ���������� ������� ��������� ������
		if (Stack.back().ListHead != nullptr)
			(Stack.back().ListHead->end() - 1)->atr = Load.ToInt();
		break;
	case 122: //MarkAtrOut ������ ������ ������� ������
		if (Stack.back().LineUk != nullptr)
			Load.Write(Stack.back().LineUk->atr);
		break;
	case 123: //MarkAtrOutMk ������ �� � �������� ������� ������
		if (Stack.back().LineUk != nullptr)
			MkExec(Load, { Cint, &Stack.back().LineUk->atr });
		break;
	case 124: //LastMarkAtrOut ������ ������ ��������� ������
		if(Stack.back().ListHead!=nullptr && !Stack.back().ListHead->size())
			Load.Write((Stack.back().ListHead->end()-1)->atr);
		break;
	case 129: //LastMarkAtrOutMk ������ �� � �������� ��������� ������
		if (Stack.back().ListHead != nullptr && !Stack.back().ListHead->size())
			MkExec(Load, { Cint, &(Stack.back().ListHead->end() - 1)->atr });
		break;
	case 125: //  MarkAtrInc ��������� �������� ������� ������
		if (Stack.back().LineUk != nullptr)
			Stack.back().LineUk->atr++;
		break;
	case 126: // LastMarkAtrInc ��������� �������� ��������� ������
		if (Stack.back().ListHead != nullptr)
			(Stack.back().ListHead->end() - 1)->atr++;
		break;
	case 127: //  MarkAtrDec ��������� �������� ������� ������
		if (Stack.back().LineUk != nullptr)
			Stack.back().LineUk->atr--;
		break;
	case 128: // LastMarkAtrDec ��������� �������� ��������� ������
		if (Stack.back().ListHead != nullptr)
			(Stack.back().ListHead->end() - 1)->atr--;
		break;
	case 130: // MarkAtrEQExec ������ ��������� ��� ����/��������� �������� ������� ������ ��� �������� c ��������� ��
		if (Stack.back().ListHead == nullptr || Stack.back().ListHead->size() == 0 || Stack.back().LineUk == nullptr) break;
		if (Load.Type >> 1 == DIC) {
			if (!Stack.back().LineUk->atr)
				ProgExec(Load);
		}
		else if(Stack.back().LineUk->atr == Load.ToInt())
			ProgExec(Prog);
		else
			ProgExec(ElseProg);
		break;
	case 131: // LastMarkEQExec ������ ��������� ��� ����/��������� �������� ��������� ������ ��� �������� c ��������� ��
		if (Stack.back().ListHead == nullptr || Stack.back().ListHead->size() == 0) break;
		if (Load.Type >> 1 == DIC) {
			if (!(Stack.back().ListHead->end() - 1)->atr )
				ProgExec(Load);
		}
		else if ((Stack.back().ListHead->end() - 1)->atr == Load.ToInt())
			ProgExec(Prog);
		else
			ProgExec(ElseProg);
		break;
	case 133: // MarkAtrNEQExec ������ ��������� ��� �� ����/����������� �������� ������� ������
		if (Stack.back().ListHead == nullptr || Stack.back().ListHead->size() == 0 || Stack.back().LineUk==nullptr) break;
		if (Load.Type >> 1 == DIC) {
			if (Stack.back().LineUk->atr)
				ProgExec(Load);
		}
		else if (Stack.back().LineUk->atr != Load.ToInt())
			ProgExec(Prog);
		else
			ProgExec(ElseProg);
		break;
	case 134: // LastMarkAtrNEQExec ������ ��������� ��� �� ����/����������� �������� ��������� ������
		if (Stack.back().ListHead == nullptr || Stack.back().ListHead->size() == 0) break;
		if (Load.Type >> 1 == DIC) {
			if ((Stack.back().ListHead->end() - 1)->atr)
				ProgExec(Load);
		}
		else if ((Stack.back().ListHead->end() - 1)->atr != Load.ToInt())
			ProgExec(Prog);
		else
			ProgExec(ElseProg);
		break;
	case 135: // MarkAtrBiggerExec ������ ��������� ��� �������� ������� ������ ������ (������ 0)
		if (Stack.back().ListHead == nullptr || Stack.back().ListHead->size() == 0 || Stack.back().LineUk == nullptr) break;
		if (Load.Type >> 1 == DIC) {
			if (Stack.back().LineUk->atr>0)
				ProgExec(Load);
		}
		else if (Stack.back().LineUk->atr > Load.ToInt())
			ProgExec(Prog);
		else
			ProgExec(ElseProg);
		break;
	case 136: // LastMarkAtrBiggerExec ������ ��������� ��� �������� ��������� ������ ������ (������ 0)
		if (Stack.back().ListHead == nullptr || Stack.back().ListHead->size() == 0) break;
		if (Load.Type >> 1 == DIC) {
			if (!(Stack.back().ListHead->end() - 1)->atr>0)
				ProgExec(Load);
		}
		else if ((Stack.back().ListHead->end() - 1)->atr > Load.ToInt())
			ProgExec(Prog);
		else
			ProgExec(ElseProg);
		break;
	case 137: // MarkAtrBiggerEQExec ������ ��������� ��� �������� ������� ������ ������ ��� ������ 0
		if (Stack.back().ListHead == nullptr || Stack.back().ListHead->size() == 0 || Stack.back().LineUk == nullptr) break;
		if (Load.Type >> 1 == DIC) {
			if (Stack.back().LineUk->atr>=0)
				ProgExec(Load);
		}
		else if (Stack.back().LineUk->atr >= Load.ToInt())
			ProgExec(Prog);
		else
			ProgExec(ElseProg);
		break;
	case 138: // LastMarkAtrBiggerEQExec ������ ��������� ��� �������� ��������� ������ ������ ��� ������ 0
		if (Stack.back().ListHead == nullptr || Stack.back().ListHead->size() == 0) break;
		if (Load.Type >> 1 == DIC) {
			if ((Stack.back().ListHead->end() - 1)->atr>=0)
				ProgExec(Load);
		}
		else if ((Stack.back().ListHead->end() - 1)->atr >= Load.ToInt())
			ProgExec(Prog);
		else
			ProgExec(ElseProg);
		break;
	case 139: // MarkAtrLessExec ������ ��������� ��� �������� ������� ������ ������ 0
		if (Stack.back().ListHead == nullptr || Stack.back().ListHead->size() == 0 || Stack.back().LineUk == nullptr) break;
		if (Load.Type >> 1 == DIC) {
			if (Stack.back().LineUk->atr<0)
				ProgExec(Load);
		}
		else if (Stack.back().LineUk->atr < Load.ToInt()) 
			ProgExec(Prog);
		else
			ProgExec(ElseProg);
		break;
	case 140: // LastMarkAtrLessExec ������ ��������� ��� �������� ��������� ������ ������ 0
		if (Stack.back().ListHead == nullptr || Stack.back().ListHead->size() == 0) break;
		if (Load.Type >> 1 == DIC) {
			if ((Stack.back().ListHead->end() - 1)->atr <0)
				ProgExec(Load);
		}
		else if ((Stack.back().ListHead->end() - 1)->atr < Load.ToInt()) 
			ProgExec(Prog);
		else
			ProgExec(ElseProg);
		break;
	case 141: // MarkAtrLessEQExec ������ ��������� ��� �������� ������� ������ ������ ��� ������ 0
		if (Stack.back().ListHead == nullptr || Stack.back().ListHead->size() == 0 || Stack.back().LineUk == nullptr) break;
		if (Load.Type >> 1 == DIC) {
			if (Stack.back().LineUk->atr <= 0)
				ProgExec(Load);
		}
		else if (Stack.back().LineUk->atr <= Load.ToInt()) 
			ProgExec(Prog);
		else
			ProgExec(ElseProg);
		break;
	case 142: // LastMarkAtrLessEQExec ������ ��������� ��� �������� ��������� ������ ������ ��� ������ 0
		if (Stack.back().ListHead == nullptr || Stack.back().ListHead->size() == 0) break;
		if (Load.Type >> 1 == DIC) {
			if ((Stack.back().ListHead->end() - 1)->atr<=0)
				ProgExec(Load);
		}
		else if ((Stack.back().ListHead->end() - 1)->atr <= Load.ToInt()) 
			ProgExec(Prog);
		else
			ProgExec(ElseProg);
		break;

	case 150: //LastOut ������ ������ �� ��������� ����� ������
	case 151: //LastPop ������ ������ �� ��������� ����� ������ � ������� �� ������
	case 152: //LastDel ������ ������ �� ��������� ����� ������ � ������� �� ��
		if (Load.Type == Tvoid)
			*(void**)Load.Point = (void*)Stack.back().ListHead->back().Load.Point;
		if (MK == 152) ICDel((void*)Stack.back().ListHead->back().Load.Point);
		if (MK == 151 || MK == 152) 
			Stack.back().ListHead->pop_back();
		break;
	case 153: //LastIpOutMk ������ ������ �� ��������� �� ��������� �����
		MkExec(Load, { CIP,(void*)&((IC_type)Stack.back().ListHead->back().Load.Point)->back() });
		break;
	case 154: // LastIpCopyOutMk ������ �� �� ������� �� ��������� �� ��������� �����
		MkExec(Load, { CIC,((IC_type)Stack.back().ListHead->back().Load.Point)->back().�lone() });
		break;
	case 155: //LastOutMK ������ ������ �� ��������� ����� ������
	case 156: //LastPopMK ������ ������ �� ��������� ����� ������ � ������� �� ������
	case 157: //LastDelMk ������ ������ �� ��������� ����� ������ � ������� �� ��
		if (Stack.back().ListHead == nullptr || !Stack.back().ListHead->size()) break;
		MkExec(Load, Stack.back().ListHead->back().Load);
		if (MK == 157) ICDel((void*)Stack.back().ListHead->back().Load.Point);
		if (MK == 156 || MK == 157) 
			Stack.back().ListHead->pop_back();
		break;
	case 158: // LastLoadOut ������ �������� ��������� �� ��������� �����
		Load.Write(((IC_type)(Stack.back().ListHead->back().Load.Point))->back().Load);
//		*(LoadPoint*)Load.Point = ((IC_type)(Stack.back().ListHead->back().Load.Point))->back().Load;
		break;
	case 169: // LastLoadOutMk ������ �� � ��������� ��������� �� ��������� �����
		MkExec(Load, ((IC_type)(Stack.back().ListHead->back().Load.Point))->back().Load);
		break;
	case 145: //LineIpOutMk ������ ������ �� ��������� �� ������� �����
		if (Stack.back().ListHead == nullptr || !Stack.back().ListHead->size() || Stack.back().LineUk==nullptr) break;
		MkExec(Load, { CIP,&((IC_type)Stack.back().LineUk->Load.Point)->back() });
		break;
	case 146: // LineIcCopyOutMk ������ �� �� ������� �� ��������� �� ������� �����
//		MkExec(Load, { CIC,((IC_type)Stack.back().ListHead->back().Load.Point)->back().�loneToIC() });
		break;
	case 147: // LastIpOutMk ������ ������ �� ��������� �� ������� �����
		MkExec(Load, { CIP,&((IC_type)Stack.back().ListHead->back().Load.Point)->back() });
		break;
	case 163: // LastCopyAddPrevLoadSet
	case 159: // LastCopyAddPrevLoadSetLoadMov �������� ����� ����� ��������� �������� � �� ����� ������ � �������� � �������� ���������� ������ ������ �� ����� ������ 
	{
		LoadPoint t = { 0, nullptr };
		if (Stack.back().ListHead != nullptr && Stack.back().ListHead->size() && Stack.back().ListHead->back().Load.Type>>1==DIC)\
			t = ((IC_type)Stack.back().ListHead->back().Load.Point)->back().Load;
		if (Stack.back().ListHead == nullptr) Stack.back().ListHead = new vector<ip>;
		if (Load.Point == nullptr)
			Stack.back().ListHead->push_back({ LineAtr, TIC, new vector<ip> });
		else
			Stack.back().ListHead->push_back({ LineAtr, TIC, ICCopy(Load) });
		if (Stack.back().ListHead->size() > 1 && Stack.back().ListHead->back().Load.Point!=nullptr && Stack.back().ListHead->back().Load.Type>>1==DIC)
			((IC_type)Stack.back().ListHead->at(Stack.back().ListHead->size() - 2).Load.Point)->back().Load = Stack.back().ListHead->back().Load;
		if (MK == 159)
			((IC_type)Stack.back().ListHead->back().Load.Point)->back().Load = t;
		break;
	}
	case 160: // LineAdd �������� ����� ������ �������
		if (Stack.back().ListHead == nullptr) Stack.back().ListHead = new vector<ip>;
		if (Stack.back().ListHead == nullptr)
			Stack.back().ListHead = new vector<ip>;
		if(Load.Point!=nullptr)
			Stack.back().ListHead->push_back({ LineAtr, Load });
		break;
	case 161: // LineCopyAdd �������� ����� ������
		if (Stack.back().ListHead == nullptr) Stack.back().ListHead = new vector<ip>;
		if (Load.Point != nullptr)
			Stack.back().ListHead->push_back({ LineAtr, TIC, ICCopy(Load) });
		break;
//	case 163: //  LineCopyAddPrevLoadSet �������� ����� � ������ � ��������� ������ �� ��� � �������� ��������� �� ��������� ������
//	 	if (Stack.back().ListHead == nullptr) Stack.back().ListHead = new vector<ip>;
//		if(Load.Point==nullptr)
//			Stack.back().ListHead->push_back({ LineAtr, TIC, new vector<ip> });
//		else
//			Stack.back().ListHead->push_back({ LineAtr, TIC, ICCopy(Load) });
//		if (Stack.back().ListHead->size() > 1)
//			((IC_type)Stack.back().ListHead->at(Stack.back().ListHead->size() - 2).Load.Point)->back().Load = Stack.back().ListHead->back().Load;
//		break;
	case 162: // LineCopyTreeAdd �������� ����� ��-�����
		if (Stack.back().ListHead == nullptr) Stack.back().ListHead = new vector<ip>;
		// ....
		break;
	case 164: // LineLoadOutMk ������ �� � ��������� ��������� �� ������� �����
		MkExec(Load, ((IC_type)(Stack.back().LineUk->Load.Point))->back().Load);
		break;
	case 165: // LinePopMk ��������� ����� ������
		if (Stack.back().ListHead == nullptr || Stack.back().ListHead->size() == 0) break;
		MkExec(Load, { TIC , (void*)Stack.back().ListHead->back().Load.Point });
		Stack.back().ListHead->pop_back();
		break;
	case 166: // LineDelMk ������ �� �� ������� �� �� � ������� ��
	{
		if (Stack.back().ListHead == nullptr || Stack.back().ListHead->size() == 0) break;
		LoadPoint t = Stack.back().ListHead->back().Load;
		Stack.back().ListHead->pop_back();
		MkExec(Load, t);
		ICDel(Stack.back().ListHead->back().Load.Point);
		break;
	}
	case 167: // LineIpCut ������� ��������� �� �� ������� ����� (� �������� ���������� ��������� ��, �� ��������� 1)
	case 168: // LineVarIpCut" Hint = "������� ��������� �� c ����������� �� ������� ����� (� �������� ���������� ��������� ��, �� ��������� 1)" }
		if (Stack.back().LineUk != nullptr && Stack.back().LineUk->Load.Type>>1==DIC && Stack.back().LineUk->Load.Point!=nullptr)
		{
			int n;
			if (Load.Point == nullptr || Load.Type >> 1 != Dint)
				n = 1;
			else
				n = *(int*)Load.Point;
			while (n-- && ((IC_type)Stack.back().LineUk->Load.Point)->size() != 0)
			{
				((IC_type)Stack.back().LineUk->Load.Point)->resize(((IC_type)Stack.back().LineUk->Load.Point)->size() - 1);
			}
		}
		break;
	case 170: // LastAttach ������������ �� � ��������� ����� ������
	case 171: // LastCopyAttach ������������ ����� �� � ��������� ����� ������
	case 172: // LastCopyAttachLoadMove �������� �� � ���������� ��������� ��������
	{
		if (Stack.back().ListHead == nullptr)
		{
			Stack.back().ListHead = new vector<ip>;
			Stack.back().ListHead->push_back({ LineAtr,{ CIC,new vector<ip>} });
		}
		if (Stack.back().ListHead != nullptr && Load.Point != nullptr)
			if (Load.Type >> 1 == DIP || Load.Type >> 1 == DIC)
			{
				if (Load.Type >> 1 == DIP)
				{
					((IC_type)Stack.back().ListHead->back().Load.Point)->push_back(*(ip*)Load.Point);
					if (MK == 170 && Load.Type == CIP) { delete (ip*)Load.Point; Load.Point = nullptr; Load.Type = 0; }
				}
				else if (Load.Type >> 1 == DIC)
				{
					for (auto i : *(IC_type)Load.Point)
						((IC_type)Stack.back().ListHead->back().Load.Point)->push_back(i);
					if (MK == 170 && Load.Type == CIP) { delete (ip*)Load.Point; Load.Point = nullptr; Load.Type = 0; }
				}
			}
			else
			{
				if (Load.Type >> 1 == DIC)
				{
					copy(((IC_type)Load.Point)->begin(), ((IC_type)Load.Point)->end(), inserter(*((IC_type)Stack.back().ListHead->back().Load.Point), ((IC_type)Stack.back().ListHead->back().Load.Point)->end()));
					if (MK == 170 && Load.Type == CIP) { ICDel(Load.Point); Load.Point = nullptr; Load.Type = 0; };
				}
			}
		break;
	}
	case 173: // LastCopyGrahpAttach
		// ....
		break;
	case 175: // LineAttach ������������ �� � ������� ����� ������
	case 176: // LineCopyAttach ������������ ����� �� � ������� ����� ������
		if (Stack.back().LineUk != nullptr && Load.Point != nullptr)
			if (Load.Type >> 1 == DIP)
			{
				((IC_type)Stack.back().LineUk->Load.Point)->push_back(*(ip*)Load.Point);
				if (MK == 175 && Load.Type == CIP) { delete (ip*)Load.Point; Load.Point = nullptr; Load.Type = 0; }
			}
			else
			{
				if (Load.Type >> 1 == DIC)
				{
					copy(((IC_type)Load.Point)->begin(), ((IC_type)Load.Point)->end(), inserter(*((IC_type)Stack.back().LineUk->Load.Point), ((IC_type)Stack.back().LineUk->Load.Point)->end()));
					if (MK == 175 && Load.Type == CIP) { ICDel(Load.Point); Load.Point = nullptr; Load.Type = 0; };
				}
			}
		break;
	case 178: // LineCopyAttach ������������ ����� �� � ������� ����� ������
		if (Stack.back().LineUk != nullptr && Load.Point != nullptr)
			if (Load.Type >> 1 == DIP)
			{
				((IC_type)Stack.back().LineUk->Load.Point)->push_back(*(ip*)Load.Point);
				if (MK == 175 && Load.Type == CIP) { delete (ip*)Load.Point; Load.Point = nullptr; Load.Type = 0; }
			}
			else
			{
				if (Load.Type >> 1 == DIC)
				{
					copy(((IC_type)Load.Point)->begin(), ((IC_type)Load.Point)->end(), inserter(*((IC_type)Stack.back().LineUk->Load.Point), ((IC_type)Stack.back().LineUk->Load.Point)->end()));
					if (MK == 175 && Load.Type == CIP) { ICDel(Load.Point); Load.Point = nullptr; Load.Type = 0; };
				}
			}
		break;
	case 179: // LineCopyGrahpAttach
			  // ....
		break;
	case 185: // LastLoadSet �������� ����� � �������� ��������� �� ��������� ������
	case 195: // LineLoadSet �������� ����� � �������� ��������� �� ��������� ������
	case 186: // LastLoadCopySet �������� ����� � �������� ��������� �� ��������� ������
	case 196: // LineLoadCopySet �������� ����� � �������� ��������� �� ��������� ������
	case 187: // LastPointLoadCopyGraphSet
	case 197: // LinePointLoadCopyGraphSet
	case 189: // LastAtrSet ���������� ������� � ��������� �� ��������� ����� 
	case 199: // LineAtrSet ���������� ������� � ��������� �� ��������� ����� 
	{	IC_type t;
		if (Stack.back().ListHead == nullptr || Stack.back().ListHead->back().Load.Point == nullptr || Stack.back().ListHead->back().Load.Type >> 1 != DIC) break;
		if (((IC_type)Stack.back().ListHead->back().Load.Point)->size() == 0) break;
		if (MK < 190)
			t = ((IC_type)Stack.back().ListHead->back().Load.Point);
		else if (Stack.back().LineUk != nullptr && Stack.back().LineUk->Load.Point != nullptr && Stack.back().LineUk->Load.Type >> 1 != DIC)
			break;
		else
			t = (IC_type)Stack.back().LineUk->Load.Point;
		switch (MK)
			{
			case 185:
			case 195:
				t->back().Load = Load;	break;
			case 186:
			case 196:
				if (Load.Type >> 1 != DIC)
					t->back().Load.Copy(Load);
				else
				{
					t->back().Load.Type = Load.Type;
					t->back().Load.Point = ICCopy(Load);
				}
				break;
			case 189:
			case 199:
				if (Load.Type >> 1 == Dint)
					t->back().atr = *(int*)Load.Point;
				break;
				//	case 177: // LastPointLoadCopyGraphSet
						// ...
						//break;
				}

		break;
	}
	case 180: // LineVarTypeSet // ���������� ��� '����������' � ��������� �� ������� �����
		if (Stack.back().ListHead == nullptr || !Stack.back().ListHead->size() || \
			Stack.back().LineUk == nullptr || Stack.back().LineUk->Load.Point == nullptr || \
			Stack.back().LineUk->Load.Type>>1!=DIC || !((IC_type)Stack.back().LineUk->Load.Point)->size())
			break;
		((IC_type)Stack.back().LineUk->Load.Point)->back().Load.VarTypeSet(Load.ToBool(true));
		break;
	case 182: // LastVarTypeSet // ���������� ��� '����������' � ��������� �� ��������� �����
		if (Stack.back().ListHead == nullptr || !Stack.back().ListHead->size() || \
			Stack.back().ListHead->back().Load.Type >> 1 != DIC || !((IC_type)Stack.back().ListHead->back().Load.Point)->size())
			break;
		((IC_type)Stack.back().ListHead->back().Load.Point)->back().Load.VarTypeSet(Load.ToBool(true));
		break;
	case 200: // LineToLast ���������� ������� ������ �� ��������� ������
		if(Stack.back().ListHead!=nullptr && Stack.back().ListHead->size()>0 && Stack.back().ListHead->back().Load.Point!=nullptr && Stack.back().ListHead->back().Load.Type>>1==DIC)
			Stack.back().LineUk = &Stack.back().ListHead->back();
		break;
	case 205: // LinePush �������� ������� ����� � ����
		if (Stack.back().LineNum >= 0 && Stack.back().LineNum < Stack.back().ListHead->size() > 0) 
			LineStack.push_back(Stack.back().LineNum);
		break;
	case 206: // LineLastPush �������� ��������� ����� � ����
		if (Stack.back().ListHead->size() > 0) LineStack.push_back(Stack.back().ListHead->size()-1);
		break;
	case 207: // LinePop ����� ������� ����� �� �����
		if (LineStack.size() && Stack.back().ListHead->size()> LineStack.back() && LineStack.back()>=0)
		{
			Stack.back().LineNum = LineStack.back();
			LineStack.pop_back();
			Stack.back().LineUk = Stack.back().ListHead->begin()._Ptr+ Stack.back().LineNum;
		}
		break;
	case 220: // FindOr ����� ���
	case 221: // FindOrLastLine ����� ��� � ��������� ������
	case 226: // FindAnd ����� �                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             227: // FindAndLastLine ����� � � ��������� ������
	case 230: // FindXor ����� XOR
	case 231: // FindXorLastLine ����� XOR � ��������� ������
	case 236: // FindAndSource ����� � � ���������
	case 237: // FindAndSourceLastLine ����� � � ��������� � ��������� ������
	{
		Stack.back().LineCount = 0; // ������� ����������
		Stack.back().LineNumOld = Stack.back().LineNum;
		Stack.back().LineNum = 0; // ����� ������ ����������� �����
		Stack.back().LineUk = nullptr; // ������ �� ��������� ������
		int LineNumFirst = -1;

		if (Stack.back().ListHead == nullptr)
		{
			Searcher.Template = { 0,nullptr };
			Searcher.FindOr({ 0,nullptr });
			ProgExec(FailProg);
			break;
		}
		auto i = Stack.back().ListHead->begin();
		if (MK % 2 != 0)
			i = Stack.back().ListHead->end() - 1;
		for (; i != Stack.back().ListHead->end(); i++)
		{
			if (i->atr != LineAtr) 
				continue;
			if (MultyListMode && AtrSearch(i->Load.Point,LineAtr)) // ������� �������� �� ������ ������� ������
				{
					Stack.push_back(Stack.back()); // �������� �������� � ���� ����������
					Stack.back().ListHead = (IC_type)i->Load.Point;
					ProgFU(MK, Load); // ����� �� ��������� ������
					IC_type t = (Stack.end() - 1)->ListHead;
					*(Stack.end() - 1) = Stack.back();
					Stack.pop_back(); // ������ �� ����� ����������
					Stack.back().ListHead = t;
					if (Stack.back().LineCount && !MultiLineMode) // ���� ����� �� ������� ����������, �� �����
						break;
				}

			//Stack.back().LineUk = i._Ptr;
			Searcher.Template = i->Load;
			switch (MK)
			{
			case 220: // FindOr		
				Searcher.FindOr(Load);
				break;
			case 226: // FindAnd 
				Searcher.FindAnd(Load);
				break;
			case 230: // FindXor
				Searcher.FindXor(Load);
				break;
			case 235: // FindAndSource
				Searcher.FindAndSource(Load);
				break;
			}
			if (Searcher.Rez)
			{
				Stack.back().LineCount++;
				if (Stack.back().LineCount==1)
				{
					if (MK % 2 == 1)
						LineNumFirst = Stack.back().ListHead->size() - 1;
					else
						LineNumFirst = Stack.back().LineNum;

				}
				if (MultiLineMode == 0) break;
			}
			Stack.back().LineNum++;
		}
		if (Stack.back().LineCount)
		{
			Stack.back().LineUk = &Stack.back().ListHead->at(LineNumFirst);
			Stack.back().LineNum = LineNumFirst;
			ProgExec(Su��essProg);
		}
		else
		{
			Stack.back().LineNum == -1;
			Stack.back().LineUk = nullptr;
			ProgExec(FailProg);
		}
	}
	if (Stack.back().LineNum > Stack.back().LineNumOld)  ProgExec(BibberProg);
	if (Stack.back().LineNum < Stack.back().LineNumOld)  ProgExec(LessProg);
	if (Stack.back().LineNum >= Stack.back().LineNumOld) ProgExec(BibberEQProg);
	if (Stack.back().LineNum < Stack.back().LineNumOld)  ProgExec(LessEQProg);
	if (Stack.back().LineNum == Stack.back().LineNumOld) ProgExec(EQProg);
	///Stack.back().LineUk == nullptr;
	break;

	// �������� � �����������
	case 238: // ToRoot ������� � ��������� ������ ������
		while (Stack.size() > 1)
			Stack.pop_back(); // ������� � ��������� ������
		break;
	case 239: // SubCopyAdd
		Stack.back().ListHead->push_back({ Load.ToInt(ListLine), TIC, new ICVect });
		Stack.push_back({ (vector<ip>*)Stack.back().ListHead->back().Load.Point, nullptr, -1, -1, 0 });
		Stack.back().ListHead->push_back({ LineAtr, Load.Copy()});
		break;
	case 240: // SubAdd �������� ����� ������� � ������ � ���������� �� ���� (� �������� ������� ���������, ���� nil ������� �� ���������)
		Stack.back().ListHead->push_back({ Load.ToInt(LineAtr), TIC, new ICVect });
		Stack.push_back({ (vector<ip>*) Stack.back().ListHead->back().Load.Point,nullptr,-1,-1,0 });
		break;
	case 241: // SubRootAdd �������� ����� ������� � �������� ������ � ���������� �� ���� �������� � ����� ������� ������ �� ���������� ��  (� �������� ������� ���������, ���� nil ������� �� ���������)
	case 242: // SubRootCopyAdd
		Stack.back().StopSearch = true;
		while (Stack.size() > 1)
			Stack.pop_back(); // ������� � ��������� ������

		if (Stack.back().ListHead == nullptr)
			Stack.back().ListHead = new vector<ip>;
		Stack.back().ListHead->push_back({LineAtr,TIC, new vector<ip>});
		Stack.push_back({ (vector<ip>*) Stack.back().ListHead->back().Load.Point, nullptr, -1, -1, 0 });
		if(Load.isIC())
			if(MK==241)
				Stack.back().ListHead->push_back({ LineAtr, Load.Type, Load.Point });
			else
				Stack.back().ListHead->push_back({ LineAtr, Load.Copy()});
		break;
	
	case 250: // SubUp ������� �� ������� ����
		Stack.pop_back();
		break;
	case 251: // SubUpDel ������� �� ������� ���� � ���������� ������� �������
		ICDel(Stack.back().ListHead->back().Load.Point);
		Stack.pop_back();
		break;
	case 252: // SubUpDelGraph ������� �� ������� ���� � ���������� ������� ������� � �����������
		//GraphDel(Stack.back().ListHead->back().Load.Point);
		Stack.pop_back();
		break;
	case 253: // SubDeepOut ������ ����� �������� ������
		Load.Write(Stack.size());
		break;
	case 254: // SubDeepOutMk ������ �� � ������� �������� ������
	{
		int t = Stack.size();
		MkExec(MK, {Cint,&t});
		break;
	}
	case 255: // SubDown ������� �� ������� ���� (�� ��������� ������� �������������� �� ������� ��������� ������
		if (Load.Point == nullptr)
			Stack.push_back({ (IC_type)Stack.back().LineUk->Load.Point,nullptr,-1,-1,0,false});
		else if(Load.isIC())
			Stack.push_back({ (IC_type)Load.Point,nullptr,-1,-1,0,false });
		break;

	case 400: // LineOutMk ������ �� � ��������� ������
			MkExec(Load, Stack.back().LineUk->Load);
		break;
	case 401: // LineOut ������ ��������� ������
			Load.Write(Stack.back().LineUk->Load.Point);
		break;

		// ��������� �� ������������ ��������� ������� �����
	case 450: // EqProgExec
		if(Load.Point==nullptr)
			if (Stack.back().LineNumOld == Stack.back().LineNum) ProgExec(Load.Point);
		break;
	case 451: // BiggerExec
		if (Stack.back().LineNumOld < Stack.back().LineNum)
			if (Load.Point != 0)
				ProgExec(Load);
			else
				ProgExec(Prog);
		break;
	case 452: // SmallerExec
		if (Stack.back().LineNumOld > Stack.back().LineNum)
			if (Load.Point != 0)
				ProgExec(Load);
			else
				ProgExec(Prog);
			break;
	case 453: // BigerEqExec
		if (Stack.back().LineNumOld <= Stack.back().LineNum)
			if (Load.Point != 0)
				ProgExec(Load);
			else
				ProgExec(Prog);
		break;
	case 454: // SmallerEqExec
		if (Stack.back().LineNumOld >= Stack.back().LineNum)
			if (Load.Point != 0)
				ProgExec(Load);
			else
				ProgExec(Prog);
		break;
	case 455: // DifferenceOut ������ �������� ������ ��������� ����� � �����
		Load.Write(Stack.back().LineNum - Stack.back().LineNumOld);
		break;
	case 456: // DifferenceOutMk ������ �� � ��������� ������ ��������� ����� � �����
	{
		int temp = Stack.back().LineNum - Stack.back().LineNumOld;
		MkExec(Load, { Cint,&temp });
		break; }
	case 459: // Stack.back().LineNumSet ���������� ����� ��������� ������ (����� ��� ����������� �������� ���������)
		Stack.back().LineNum = Load.ToInt();
		break;
	case 460: //Stack.back().LineCountOut ������ ���������� ��������� �����
		Load.Write(Stack.back().LineCount);
		break;
	case 461: //Stack.back().LineCountOutMk ������ �� � ����������� ��������� �����
		MkExec(Load, { Cint, &Stack.back().LineCount });
		break;

	case 470: // LessProgSet
		LessProg = Load.Point;
		break;
	case 471: // BiggerProgSet
		BibberProg = Load.Point;
		break;
	case 472: // EQProgSet
		EQProg = Load.Point;
		break;
	case 473: // LessEQProgSet
		LessEQProg = Load.Point;
		break;
	case 474: // BiggerEQProgSet
		BibberEQProg = Load.Point;
		break;
	// ��������� �� ������� �����
	case 500: // LineEmptyExec ��������� ������������, ���� ������� ������ ������
		if (Stack.back().ListHead != nullptr && Stack.back().LineUk != nullptr && ((IC_type)Stack.back().LineUk->Load.Point)->size()==0)
			ProgExec(Load);
		break;
	case 501: //LineFullExec  ��������� ������������, ���� ������� ������ �� ������
		if (Stack.back().ListHead != nullptr && Stack.back().LineUk != nullptr && ((IC_type)Stack.back().LineUk->Load.Point)->size() != 0)
			ProgExec(Load);
		break;
	case 505: // LastEmptyExec  ��������� ������������, ���� ��������� ������ ������
		if (Stack.back().ListHead != nullptr && Stack.back().ListHead->size() != 0 && ((IC_type)Stack.back().ListHead->back().Load.Point)->size() == 0)
			ProgExec(Load);
		break;
	case 506: //LastFullExec ��������� ������������, ���� ��������� ������ �� ������
		if (Stack.back().ListHead != nullptr && Stack.back().ListHead->size() != 0 && ((IC_type)Stack.back().ListHead->back().Load.Point)->size() != 0)
			ProgExec(Load);
		break;
	default:
		CommonMk(MK, Load);
		break;
	}
	if (Stack.size() == 1)
		ProgExec(PostfixProg); // ��������� ��������� ���������
}
