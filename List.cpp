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
		break;
	case 1:	// Set
		ListHead = (IC_type)Load.Point;
//		LineCounter = ListHead->size();
		break;
	case 2:// Out ������ ������ �� ������
		if (Load.Type >> 1 == Cvoid)
			*(void**)Load.Point = ListHead;
		break;
	case 3:// OutMk ������ �� �� ������� �� ������
		if (Load.Type >> 1 == Dint)
			MkExec(*(int*)Load.Point, { TIC,(void*)ListHead });
		break;
	case 5:	// MultiLineModeSet
		if(Load.Type>>1==Dint)
			MultiLineMode = *(int *)Load.Point;
		break;
	case 7: // MkModeSet ����� ���������� ���� �� � ��-������� (��-�� ��������� ����� �������, ������ �������� ������ 0) ��� ������ �������� ����� ���������������
		if (Load.Point == nullptr)
			Searcher.MkMode = true;
		else
			switch (Load.Type >> 1)
			{
			case Dbool:
				Searcher.MkMode = *(bool*)Load.Point;
			case Dint:
				Searcher.MkMode = *(int*)Load.Point;
			}
		break;
	case 8:// EmptyProgExec ��������� ���������, ���� ������ ����
//		if (ListHead == nullptr || ListHead->size() == 0)
//			if(Load.Type>>1==DIC)
//				ProgExec(Load.Point, Bus, nullptr);
//		break;
	case 9:// FullExec ��������� ���������, ���� ������ �� ����
		break;
	case 14: // OneLineExec ��������� ���������, ���� � ������ ������ ���� ������
		break;
	case 13: // MoreOneLineExec ��������� ���������, ���� � ������ ������ ����� ������
		if (MK==8 && (ListHead == nullptr || ListHead->size() == 0)||\
			ListHead != nullptr && ListHead->size() != 0 &&\
			(MK==9 || MK==10 && ListHead->size() != 0 || MK == 14 && ListHead->size() == 1 ||\
				MK == 13 && ListHead->size() >1 ) )
//			ProgExec(Load);
			if (Load.Point != nullptr && Load.Type >> 1 == DIC)
				ProgExec(Load);
			else
				ProgExec(Prog);
		else if(Load.Point == nullptr)
			ProgExec(ElseProg);
		break;
//		if (ListHead != nullptr && ListHead->size() >1)
//			if (ListHead != nullptr && ListHead->size() == 1)
//				if (Load.Point != nullptr && Load.Type >> 1 == DIC)
//					ProgExec(Load);
//				else
//					ProgExec(Prog);
//			else if (Load.Point == nullptr)
//				ProgExec(ElseProg);
//		break;
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
	case 18: // Su��essLineProgSet ���������� ��������� �� ���������, ����������� � ������ �������� ������ �� ����  ������
		Su��essLineProg = Load.Point;
		break;

	case 20: // ProgAtrSet ���������� ������� ���������
		if (Load.Point != nullptr && Load.Type >> 1 == Dint)
			Searcher.Prog_atr = *(int *)Load.Point;
		break;
	case 21: //MarcAtrDef ���������� ������� ����� ������ �� ���������
		LineAtr = Load.ToInt();
		break;
	case 25: // BackOut ������ ������� ������ ��� ������
		if (Load.Type == TPPoint)
			(*(LoadPoint*)Load.Point) = Searcher.Obj;
		break;
	case 30: // BackOutMk ������� �� �� ������� �������� ��� ������
		if (Load.Type >> 1 == Dint)
			MkExec(*(int*)Load.Point, Searcher.Obj.Clone());
		break;
	case 31: // CopyBackOutMk ������� �� �� ������� �������� ��� ������
		if (Load.Type >> 1 == Dint)
			MkExec(*(int*)Load.Point, Searcher.Obj.Clone());
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
			*(bool*)Load.Point = Searcher.Rez;
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
		if (LineUk != nullptr)
			LineUk->atr = Load.ToInt();
		break;
	case 121: // LastMarkAtrSet ���������� ������� ��������� ������
		if (ListHead != nullptr)
			(ListHead->end() - 1)->atr = Load.ToInt();
		break;
	case 122: //MarkAtrOut ������ ������ ������� ������
		if (LineUk != nullptr)
			Load.Write(LineUk->atr);
		break;
	case 123: //MarkAtrOutMk ������ �� � �������� ������� ������
		if (LineUk != nullptr)
			MkExec(Load, { Cint, &LineUk->atr });
		break;
	case 124: //LastMarkAtrOut ������ ������ ��������� ������
		if(ListHead!=nullptr && !ListHead->size())
			Load.Write((ListHead->end()-1)->atr);
		break;
	case 129: //LastMarkAtrOutMk ������ �� � �������� ��������� ������
		if (ListHead != nullptr && !ListHead->size())
			MkExec(Load, { Cint, &(ListHead->end() - 1)->atr });
		break;
	case 125: //  MarkAtrInc ��������� �������� ������� ������
		if (LineUk != nullptr)
			LineUk->atr++;
		break;
	case 126: // LastMarkAtrInc ��������� �������� ��������� ������
		if (ListHead != nullptr)
			(ListHead->end() - 1)->atr++;
		break;
	case 127: //  MarkAtrDec ��������� �������� ������� ������
		if (LineUk != nullptr)
			LineUk->atr--;
		break;
	case 128: // LastMarkAtrDec ��������� �������� ��������� ������
		if (ListHead != nullptr)
			(ListHead->end() - 1)->atr--;
		break;
	case 130: // MarkAtrZeroExec ������ ��������� ��� ���� �������� ������� ������ ��� �������� c ��������� ��
		if (LineUk == nullptr) break;
		if (Load.Type >> 1 == DIC) {
			if (LineUk->atr)
				ProgExec(Load);
		}
		else if(LineUk->atr == Load.ToInt())
			ProgExec(Prog);
		else
			ProgExec(ElseProg);
		break;
	case 131: // LastMarkAtrZeroExec ������ ��������� ��� ���� �������� ��������� ������ ��� �������� c ��������� ��
		if (ListHead == nullptr || ListHead->size() == 0) break;
		if (Load.Type >> 1 == DIC) {
			if (!(ListHead->end() - 1)->atr)
				ProgExec(Load);
		}
		else if (Load.Point==nullptr && (ListHead->end() - 1)->atr ==0 || (ListHead->end() - 1)->atr == Load.ToInt())
			ProgExec(Prog);
		else
			ProgExec(ElseProg);
		break;
	case 133: // MarkAtrNZeroExec ������ ��������� ��� �� ���� �������� ������� ������
		if (LineUk->atr) ProgExec(Load);
		break;
	case 134: // LastMarkAtrNZeroExec ������ ��������� ��� �� ���� �������� ��������� ������
		if ((ListHead->end() - 1)->atr) ProgExec(Load);
		break;
	case 135: // MarkAtrBiggerExec ������ ��������� ��� �������� ������� ������ ������ 0
		if (LineUk->atr > 0) ProgExec(Load);
		break;
	case 136: // LastMarkAtrBiggerExec ������ ��������� ��� �������� ��������� ������ ������ 0
		if ((ListHead->end() - 1)->atr > 0) ProgExec(Load);
		break;
	case 137: // MarkAtrBiggerZeroExec ������ ��������� ��� �������� ������� ������ ������ ��� ������ 0
		if (LineUk->atr >= 0) ProgExec(Load);
		break;
	case 138: // LastMarkAtrBiggerZeroExec ������ ��������� ��� �������� ��������� ������ ������ ��� ������ 0
		if ((ListHead->end() - 1)->atr >= 0) ProgExec(Load);
		break;
	case 139: // MarkAtrLessExec ������ ��������� ��� �������� ������� ������ ������ 0
		if (LineUk->atr < 0) ProgExec(Load);
		break;
	case 140: // LastMarkAtrLessExec ������ ��������� ��� �������� ��������� ������ ������ 0
		if ((ListHead->end() - 1)->atr < 0) ProgExec(Load);
		break;
	case 141: // MarkAtrLessZeroExec ������ ��������� ��� �������� ������� ������ ������ ��� ������ 0
		if (LineUk->atr <= 0) ProgExec(Load);
		break;
	case 142: // LastMarkAtrLessZeroExec ������ ��������� ��� �������� ��������� ������ ������ ��� ������ 0
		if ((ListHead->end() - 1)->atr <= 0) ProgExec(Load);
		break;

	case 150: //LastOut ������ ������ �� ��������� ����� ������
	case 151: //LastPop ������ ������ �� ��������� ����� ������ � ������� �� ������
	case 152: //LastDel ������ ������ �� ��������� ����� ������ � ������� �� ��
		if (Load.Type == Tvoid)
			*(void**)Load.Point = (void*)ListHead->back().Load.Point;
		if (MK == 152) ICDel((void*)ListHead->back().Load.Point);
		if (MK == 151 || MK == 152) 
			ListHead->pop_back();
		break;
	case 153: //LastIpOutMk ������ ������ �� ��������� �� ��������� �����
		MkExec(Load, { CIP,(void*)&((IC_type)ListHead->back().Load.Point)->back() });
		break;
	case 154: // LastIpCopyOutMk ������ �� �� ������� �� ��������� �� ��������� �����
		MkExec(Load, { CIC,((IC_type)ListHead->back().Load.Point)->back().�lone() });
		break;
	case 155: //LastOutMK ������ ������ �� ��������� ����� ������
	case 156: //LastPopMK ������ ������ �� ��������� ����� ������ � ������� �� ������
	case 157: //LastDelMk ������ ������ �� ��������� ����� ������ � ������� �� ��
		if (ListHead == nullptr) break;
		if(Load.Point!=nullptr)
			MkExec(*(int*)Load.Point, ListHead->back().Load);
		if (MK == 157) ICDel((void*)ListHead->back().Load.Point);
		if (MK == 156 || MK == 157) 
			ListHead->pop_back();
		break;
	case 158: // LastLoadOutMK ������ �� � ��������� ��������� �� ��������� �����
		MkExec(Load, ((IC_type)(ListHead->back().Load.Point))->back().Load);
		break;
	case 145: //LineIcOutMk ������ ������ �� ��������� �� ������� �����
		MkExec(Load, { CIP,&((IC_type)ListHead->back().Load.Point)->back() });
		break;
	case 146: // LineIcCopyOutMk ������ �� �� ������� �� ��������� �� ������� �����
//		MkExec(Load, { CIC,((IC_type)ListHead->back().Load.Point)->back().�loneToIC() });
		break;

	case 160: // LineAdd �������� ����� ������ �������
		if (ListHead == nullptr) ListHead = new vector<ip>;
		if (ListHead == nullptr)
			ListHead = new vector<ip>;
		if(Load.Point!=nullptr)
			ListHead->push_back({ LineAtr, Load });
		break;
	case 161: // LineCopyAdd �������� ����� ������
		if (ListHead == nullptr) ListHead = new vector<ip>;
		if (Load.Point != nullptr)
			ListHead->push_back({ LineAtr, TIC, ICCopy(Load) });
		break;
	case 163: //  LineCopyAddPrevLoadSet �������� ����� � ������ � ��������� ������ �� ��� � �������� ��������� �� ��������� ������
	 	if (ListHead == nullptr) ListHead = new vector<ip>;
		if(Load.Point==nullptr)
			ListHead->push_back({ LineAtr, TIC, new vector<ip> });
		else
			ListHead->push_back({ LineAtr, TIC, ICCopy(Load) });
		if (ListHead->size() > 1)
			((IC_type)ListHead->at(ListHead->size() - 2).Load.Point)->back().Load = ListHead->back().Load;
		break;
	case 162: // LineCopyTreeAdd �������� ����� ��-�����
		if (ListHead == nullptr) ListHead = new vector<ip>;
		// ....
		break;
	case 164: // LineLoadOutMk ������ �� � ��������� ��������� �� ������� �����
		MkExec(Load, ((IC_type)(LineUk->Load.Point))->back().Load);
		break;
	case 165: // LineExcludeMk ��������� ����� ������
		if (ListHead == nullptr || ListHead->size() == 0) break;
		if(Load.Point!=nullptr && Load.Type>>1==Dint) MkExec(*(int*)Load.Point, { TIC , (void*)ListHead->back().Load.Point });
		ListHead->pop_back();
		break;
	case 166: // LineDelMk ������ �� �� ������� �� �� � ������� ��
		if (ListHead == nullptr || ListHead->size() == 0) break;
		MkExec(*(int*)Load.Point, { TIC , (void*)ListHead->back().Load.Point });
		ICDel(ListHead->back().Load.Point);
		ListHead->pop_back();
		break;
	case 167: // LineIpCut ������� ��������� �� �� ������� ����� (� �������� ���������� ��������� ��, �� ��������� 1)
	case 168: // LineVarIpCut" Hint = "������� ��������� �� c ����������� �� ������� ����� (� �������� ���������� ��������� ��, �� ��������� 1)" }
		if (LineUk != nullptr && LineUk->Load.Type>>1==DIC && LineUk->Load.Point!=nullptr)
		{
			int n;
			if (Load.Point == nullptr || Load.Type >> 1 != Dint)
				n = 1;
			else
				n = *(int*)Load.Point;
			while (n-- && ((IC_type)LineUk->Load.Point)->size() != 0)
			{
				((IC_type)LineUk->Load.Point)->resize(((IC_type)LineUk->Load.Point)->size() - 1);
			}
		}
		break;
	case 170: // LastAttach ������������ �� � ��������� ����� ������
	case 171: // LastCopyAttach ������������ ����� �� � ��������� ����� ������
		if (ListHead == nullptr)
		{
			ListHead = new vector<ip>;
			ListHead->push_back({ LineAtr,{ CIC,new vector<ip>} });
		}
		if (ListHead != nullptr && Load.Point != nullptr)
			if (Load.Type >> 1 == DIP || Load.Type >> 1 == DIC)
			{
//				ListHead->push_back({});
				if (Load.Type >> 1 == DIP)
				{
					((IC_type)ListHead->back().Load.Point)->push_back(*(ip*)Load.Point);
					if (MK == 170 && Load.Type == CIP) { delete (ip*)Load.Point; Load.Point = nullptr; Load.Type = 0; }
				}
				else if (Load.Type >> 1 == DIC)
				{
					for (auto i : *(IC_type)Load.Point)
						((IC_type)ListHead->back().Load.Point)->push_back(i);
					if (MK == 170 && Load.Type == CIP) { delete (ip*)Load.Point; Load.Point = nullptr; Load.Type = 0; }
				}
			}
		else
			{
			if (Load.Type >> 1 == DIC)
			{
				copy(((IC_type)Load.Point)->begin(), ((IC_type)Load.Point)->end(), inserter(*((IC_type)ListHead->back().Load.Point), ((IC_type)ListHead->back().Load.Point)->end()));
				if (MK == 170 && Load.Type==CIP) { ICDel(Load.Point); Load.Point = nullptr; Load.Type = 0; };
			}
		}
		break; 
	case 172: // LastCopyGrahpAttach
		// ....
		break;
	case 175: // LineAttach ������������ �� � ������� ����� ������
	case 176: // LineCopyAttach ������������ ����� �� � ������� ����� ������
		if (LineUk != nullptr && Load.Point != nullptr)
			if (Load.Type >> 1 == DIP)
			{
				((IC_type)LineUk->Load.Point)->push_back(*(ip*)Load.Point);
				if (MK == 175 && Load.Type == CIP) { delete (ip*)Load.Point; Load.Point = nullptr; Load.Type = 0; }
			}
			else
			{
				if (Load.Type >> 1 == DIC)
				{
					copy(((IC_type)Load.Point)->begin(), ((IC_type)Load.Point)->end(), inserter(*((IC_type)LineUk->Load.Point), ((IC_type)LineUk->Load.Point)->end()));
					if (MK == 175 && Load.Type == CIP) { ICDel(Load.Point); Load.Point = nullptr; Load.Type = 0; };
				}
			}
		break;
	case 177: // LineCopyGrahpAttach
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
		if (ListHead == nullptr || ListHead->back().Load.Point == nullptr || ListHead->back().Load.Type >> 1 != DIC) break;
		if (((IC_type)ListHead->back().Load.Point)->size() == 0) break;
		if (MK < 190)
			t = ((IC_type)ListHead->back().Load.Point);
		else if (LineUk != nullptr && LineUk->Load.Point != nullptr && LineUk->Load.Type >> 1 != DIC)
			break;
		else
			t = (IC_type)LineUk->Load.Point;
		switch (MK)
			{
			case 185:
			case 195:
				t->back().Load = Load;	break;
			case 186:
			case 196:
				if (Load.Type >> 1 != DIC)
					t->back().Load.Copy(&Load);
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
		if (ListHead == nullptr || !ListHead->size() || \
			LineUk == nullptr || LineUk->Load.Point == nullptr || \
			LineUk->Load.Type>>1!=DIC || !((IC_type)LineUk->Load.Point)->size())
			break;
		((IC_type)LineUk->Load.Point)->back().Load.VarTypeSet(Load.ToBool(true));
		break;
	case 182: // LastVarTypeSet // ���������� ��� '����������' � ��������� �� ��������� �����
		if (ListHead == nullptr || !ListHead->size() || \
			ListHead->back().Load.Type >> 1 != DIC || !((IC_type)ListHead->back().Load.Point)->size())
			break;
		((IC_type)ListHead->back().Load.Point)->back().Load.VarTypeSet(Load.ToBool(true));
		break;
//	case 181: // LastPointConstTypeSet // ���������� ��� '���������' � ��������� �� ��������� �����
//	case 183: // LinePointConstTypeSet // ���������� ��� '���������' � ��������� �� ������� �����
	case 200: // LineToLast ���������� ������� ������ �� ��������� ������
		if(ListHead!=nullptr && ListHead->size()>0 && ListHead->back().Load.Point!=nullptr && ListHead->back().Load.Type>>1==DIC)
			LineUk = &ListHead->back();
		break;
	case 205: // LinePush �������� ������� ����� � ����
		if (LineNum >= 0 && LineNum < ListHead->size() > 0) 
			LineStack.push_back(LineNum);
		break;
	case 206: // LineLastPush �������� ��������� ����� � ����
		if (ListHead->size() > 0) LineStack.push_back(ListHead->size()-1);
		break;
	case 207: // LinePop ����� ������� ����� �� �����
		if (LineStack.size() && ListHead->size()> LineStack.back() && LineStack.back()>=0)
		{
			LineNum = LineStack.back();
			LineStack.pop_back();
			LineUk = ListHead->begin()._Ptr+ LineNum;
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
		LineCount = 0; // ������� ����������
		LineNumOld = LineNum;
		LineNum = 0; // ����� ������ ����������� �����
		int LineNumFirst = -1;
		if (ListHead == nullptr)
		{
			Searcher.Template = { 0,nullptr };
			Searcher.FindOr({ 0,nullptr });
			ProgExec(FailProg, Bus, nullptr);
			break;
		}
		auto i = ListHead->begin();
		if (MK % 2 != 0)
			i = ListHead->end() - 1;
		for (; i != ListHead->end(); i++)
		{
			LineUk = i._Ptr;
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
				LineCount++;
				if (LineCount==1)
				{
					if (MK % 2 == 1)
						LineNumFirst = ListHead->size() - 1;
					else
						LineNumFirst = LineNum;

				}
				if (MultiLineMode == 0) break;
			}
			LineNum++;
		}
		if (LineCount)
		{
			LineUk = &ListHead->at(LineNumFirst);
			LineNum = LineNumFirst;
		}
		else
		{
			LineNum == -1;
			LineUk = nullptr;
			ProgExec(FailProg, Bus, nullptr);
		}
	}
	if (LineNum > LineNumOld)  ProgExec(BibberProg);
	if (LineNum < LineNumOld)  ProgExec(LessProg);
	if (LineNum >= LineNumOld) ProgExec(BibberEQProg);
	if (LineNum < LineNumOld)  ProgExec(LessEQProg);
	if (LineNum == LineNumOld) ProgExec(EQProg);
	break;

	case 400: // LineOutMk ������ �� � ��������� ������
			MkExec(Load, LineUk->Load);
		break;
	case 401: // LineOut ������ ��������� ������
			Load.Write(LineUk->Load.Point);
		break;

		// ��������� �� ������������ ��������� ������� �����
	case 450: // EqProgExec
		if(Load.Point==nullptr)
			if (LineNumOld == LineNum) ProgExec(Load.Point);
		break;
	case 451: // BiggerProgExec
		if (LineNumOld < LineNum) ProgExec(Load.Point);
		break;
	case 452: // SmallerProgExec
		if (LineNumOld > LineNum) ProgExec(Load.Point);
		break;
	case 453: // BigerEqProgExec
		if (LineNumOld <= LineNum) ProgExec(Load.Point);
		break;
	case 454: // SmallerEqProgExec
		if (LineNumOld >= LineNum) ProgExec(Load.Point);
		break;
	case 455: // DifferenceOut ������ �������� ������ ��������� ����� � �����
		Load.Write(LineNum - LineNumOld);
		break;
	case 456: // DifferenceOutMk ������ �� � ��������� ������ ��������� ����� � �����
	{
		int temp = LineNum - LineNumOld;
		MkExec(Load, { Cint,&temp });
		break; }
	case 459: // LineNumSet ���������� ����� ��������� ������ (����� ��� ����������� �������� ���������)
		LineNum = Load.ToInt();
		break;
	case 460: //LineCountOut ������ ���������� ��������� �����
		Load.Write(LineCount);
		break;
	case 461: //LineCountOutMk ������ �� � ����������� ��������� �����
		MkExec(Load, { Cint, &LineCount });
		break;

	case 470: // LessProgSet
		LessProg = Load.Point;
		break;
	case 471: // LessProgSet
		BibberProg = Load.Point;
		break;
	case 472: // LessProgSet
		EQProg = Load.Point;
		break;
	case 473: // LessProgSet
		LessEQProg = Load.Point;
		break;
	case 474: // LessProgSet
		BibberEQProg = Load.Point;
		break;
	// ��������� �� ������� �����
	case 500: // LineEmptyExec ��������� ������������, ���� ������� ������ ������
		if (ListHead != nullptr && LineUk != nullptr && ((IC_type)LineUk->Load.Point)->size()==0)
			ProgExec(Load);
		break;
	case 501: //LineFullExec  ��������� ������������, ���� ������� ������ �� ������
		if (ListHead != nullptr && LineUk != nullptr && ((IC_type)LineUk->Load.Point)->size() != 0)
			ProgExec(Load);
		break;
	case 505: // LastEmptyExec  ��������� ������������, ���� ��������� ������ ������
		if (ListHead != nullptr && ListHead->size() != 0 && ((IC_type)ListHead->back().Load.Point)->size() == 0)
			ProgExec(Load);
		break;
	case 506: //LastFullExec ��������� ������������, ���� ��������� ������ �� ������
		if (ListHead != nullptr && ListHead->size() != 0 && ((IC_type)ListHead->back().Load.Point)->size() != 0)
			ProgExec(Load);
		break;
	default:
		CommonMk(MK, Load);
		break;
	}
}
