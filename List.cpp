// ФУ Список
#include "stdafx.h"
#include "List.h"

using namespace std;

void List::ProgFU(int MK, LoadPoint Load)
{
	ProgExec(PrefixProg); // Предварительная программа, вызываемая при приходе любой МК
	switch (MK)
	{
	case 0: // Reset
		Searcher.Clear();
		break;
	case 1:	// Set
		ListHead = (IC_type)Load.Point;
//		LineCounter = ListHead->size();
		break;
	case 2:// Out Выдать ссылку на список
		if (Load.Type >> 1 == Cvoid)
			*(void**)Load.Point = ListHead;
		break;
	case 3:// OutMk Выдать МК со ссылкой на список
		if (Load.Type >> 1 == Dint)
			MkExec(*(int*)Load.Point, { TIC,(void*)ListHead });
		break;
	case 5:	// MultiLineModeSet
		if(Load.Type>>1==Dint)
			MultiLineMode = *(int *)Load.Point;
		break;
	case 7: // MkModeSet Режим выполнения всех МК в ИК-шаблоне (МК-ой считается любой атрибут, индекс которого больше 0) При пустой нагрузке режим устанавливается
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
	case 8:// EmptyProgExec Выполнить программу, если список пуст
//		if (ListHead == nullptr || ListHead->size() == 0)
//			if(Load.Type>>1==DIC)
//				ProgExec(Load.Point, Bus, nullptr);
//		break;
	case 9:// FullExec Выполнить программу, если список не пуст
		break;
	case 14: // OneLineExec Выполнить программу, если в списке только одна строка
		break;
	case 13: // MoreOneLineExec Выполнить программу, если в списке больше одной строка
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
	case 10: // SuccessLineProgSet Установить указатель на программу, выполняемую при удачном поиска в линии списка
		Searcher.SuccessProg = (IC_type)Load.Point;
		break;
	case 11: // SuccessAfterLineProgSet Установить указатель на программу, выполняемую при удачном поиска в линии списка после обоработки программ линии
		Searcher.SuccessAfterProg = (IC_type)Load.Point;
		break;
	case 12: // SuссessProgSet Установить указатель на программу, выполняемую в случае удачного поиска во всем  списке
		SuссessProg = Load.Point;
		break;
	case 15: // FailLineProgSet Установить указатель на программу, выполняемую в случае неудачного поиска в линии списка
		Searcher.FailProg = (IC_type)Load.Point;
		break;
	case 16: // FailAfterLineProgSet Установить указатель на программу, выполняемую в случае неудачного поиска в линии списка после обоработки программ линии
		Searcher.FailAfterProg = (IC_type)Load.Point;
		break;
	case 17: // FailProgSet Установить указатель на программу, выполняемую в случае неудачного поиска во всем  списке
		FailProg = Load.Point;
		break;
	case 18: // SuссessLineProgSet Установить указатель на программу, выполняемую в случае удачного поиска во всем  списке
		SuссessLineProg = Load.Point;
		break;

	case 20: // ProgAtrSet Установить атрибут программы
		if (Load.Point != nullptr && Load.Type >> 1 == Dint)
			Searcher.Prog_atr = *(int *)Load.Point;
		break;
	case 21: //MarcAtrDef Установить атрибут марки списка по умолчанию
		LineAtr = Load.ToInt();
		break;
	case 25: // BackOut Вылать входной объект для поиска
		if (Load.Type == TPPoint)
			(*(LoadPoint*)Load.Point) = Searcher.Obj;
		break;
	case 30: // BackOutMk Вылаить МК со входным объектом для поиска
		if (Load.Type >> 1 == Dint)
			MkExec(*(int*)Load.Point, Searcher.Obj.Clone());
		break;
	case 31: // CopyBackOutMk Вылаить МК со входным объектом для поиска
		if (Load.Type >> 1 == Dint)
			MkExec(*(int*)Load.Point, Searcher.Obj.Clone());
		break;

	case 35: // LoadBackOut Выдать нагрузку входного объекта для поиска
		if (Searcher.Obj.Type >> 1 == DIC)
			Load.Point = ((IC_type)(Searcher.Obj.Point))->begin()->Load.Point;
		else if (Searcher.Obj.Type >> 1 == DIP)
			Load.Point = ((ip*)(Searcher.Obj.Point))->Load.Point;
		break;
	case 36: // LoadBackOutMk Выдать МК с нагрузкой входного объекта для поиска
		if (Load.Type >> 1 == Dint)
			if(Searcher.Obj.Type>>1==DIC)
				MkExec(*((int*)Load.Point), ((IC_type)(Searcher.Obj.Point))->begin()->Load);
			else if(Searcher.Obj.Type >> 1 == DIP)
				MkExec(*((int*)Load.Point), ((ip*)(Searcher.Obj.Point))->Load);
		break;

	case 100: // RezOut Выдача результата сравнения
		if (Load.Type == Tbool)
			*(bool*)Load.Point = Searcher.Rez;
		break;
	case 101: // RezOutMk Выдача МК с результатом сравнения
		MkExec(*(int*)(Load.Point), { Cbool , &Searcher.Rez });
		break;
	case 105: // MkAtrAdd Добавить МК
		if (Load.Type >> 1 == Dint)
			Searcher.MkAtrAdd(*(int*)Load.Point);
		break;
	case 106: // MkAtrClear Очистить список МК
		Searcher.MkAtrClear();
		break;

	case 120: // MarkAtrSet Установить атрибут текущей строки
		if (LineUk != nullptr)
			LineUk->atr = Load.ToInt();
		break;
	case 121: // LastMarkAtrSet Установить атрибут последней строки
		if (ListHead != nullptr)
			(ListHead->end() - 1)->atr = Load.ToInt();
		break;
	case 122: //MarkAtrOut Выдать маркер текущей строки
		if (LineUk != nullptr)
			Load.Write(LineUk->atr);
		break;
	case 123: //MarkAtrOutMk Выдать МК с маркером текущей строки
		if (LineUk != nullptr)
			MkExec(Load, { Cint, &LineUk->atr });
		break;
	case 124: //LastMarkAtrOut Выдать маркер последней строки
		if(ListHead!=nullptr && !ListHead->size())
			Load.Write((ListHead->end()-1)->atr);
		break;
	case 129: //LastMarkAtrOutMk Выдать МК с маркером последней строки
		if (ListHead != nullptr && !ListHead->size())
			MkExec(Load, { Cint, &(ListHead->end() - 1)->atr });
		break;
	case 125: //  MarkAtrInc Инкремент атрибута текущей строки
		if (LineUk != nullptr)
			LineUk->atr++;
		break;
	case 126: // LastMarkAtrInc Инкремент атрибута последней строки
		if (ListHead != nullptr)
			(ListHead->end() - 1)->atr++;
		break;
	case 127: //  MarkAtrDec Декримент атрибута текущей строки
		if (LineUk != nullptr)
			LineUk->atr--;
		break;
	case 128: // LastMarkAtrDec Декримент атрибута последней строки
		if (ListHead != nullptr)
			(ListHead->end() - 1)->atr--;
		break;
	case 130: // MarkAtrZeroExec Запуск программы при нуле атрибута текущей строки или равестве c нагрузкой МК
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
	case 131: // LastMarkAtrZeroExec Запуск программы при нуле атрибута последней строки или равестве c нагрузкой МК
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
	case 133: // MarkAtrNZeroExec Запуск программы при не нуле атрибута текущей строки
		if (LineUk->atr) ProgExec(Load);
		break;
	case 134: // LastMarkAtrNZeroExec Запуск программы при не нуле атрибута последней строки
		if ((ListHead->end() - 1)->atr) ProgExec(Load);
		break;
	case 135: // MarkAtrBiggerExec Запуск программы при атрибуте текущей строки больше 0
		if (LineUk->atr > 0) ProgExec(Load);
		break;
	case 136: // LastMarkAtrBiggerExec Запуск программы при атрибуте последней строки больше 0
		if ((ListHead->end() - 1)->atr > 0) ProgExec(Load);
		break;
	case 137: // MarkAtrBiggerZeroExec Запуск программы при атрибуте текущей строки больше или райным 0
		if (LineUk->atr >= 0) ProgExec(Load);
		break;
	case 138: // LastMarkAtrBiggerZeroExec Запуск программы при атрибуте последней строки больше или равным 0
		if ((ListHead->end() - 1)->atr >= 0) ProgExec(Load);
		break;
	case 139: // MarkAtrLessExec Запуск программы при атрибуте текущей строки меньше 0
		if (LineUk->atr < 0) ProgExec(Load);
		break;
	case 140: // LastMarkAtrLessExec Запуск программы при атрибуте последней строки меньше 0
		if ((ListHead->end() - 1)->atr < 0) ProgExec(Load);
		break;
	case 141: // MarkAtrLessZeroExec Запуск программы при атрибуте текущей строки меньше или равным 0
		if (LineUk->atr <= 0) ProgExec(Load);
		break;
	case 142: // LastMarkAtrLessZeroExec Запуск программы при атрибуте последней строки меньше или равным 0
		if ((ListHead->end() - 1)->atr <= 0) ProgExec(Load);
		break;

	case 150: //LastOut Выдать ссылку на последнюю линию списка
	case 151: //LastPop Выдать ссылку на последнюю линию списка и удалить из списка
	case 152: //LastDel Выдать ссылку на последнюю линию списка и удалить из ИК
		if (Load.Type == Tvoid)
			*(void**)Load.Point = (void*)ListHead->back().Load.Point;
		if (MK == 152) ICDel((void*)ListHead->back().Load.Point);
		if (MK == 151 || MK == 152) 
			ListHead->pop_back();
		break;
	case 153: //LastIpOutMk Выдать ссылку на последнюю ИП последней линии
		MkExec(Load, { CIP,(void*)&((IC_type)ListHead->back().Load.Point)->back() });
		break;
	case 154: // LastIpCopyOutMk Выдать МК со ссылкой на последнюю ИП последней линии
		MkExec(Load, { CIC,((IC_type)ListHead->back().Load.Point)->back().Сlone() });
		break;
	case 155: //LastOutMK Выдать ссылку на последнюю линию списка
	case 156: //LastPopMK Выдать ссылку на последнюю линию списка и удалить из списка
	case 157: //LastDelMk Выдать ссылку на последнюю линию списка и удалить из ИК
		if (ListHead == nullptr) break;
		if(Load.Point!=nullptr)
			MkExec(*(int*)Load.Point, ListHead->back().Load);
		if (MK == 157) ICDel((void*)ListHead->back().Load.Point);
		if (MK == 156 || MK == 157) 
			ListHead->pop_back();
		break;
	case 158: // LastLoadOutMK Выдать МК с нагрузкой последней ИП последней линии
		MkExec(Load, ((IC_type)(ListHead->back().Load.Point))->back().Load);
		break;
	case 145: //LineIcOutMk Выдать ссылку на последнюю ИП текущей линии
		MkExec(Load, { CIP,&((IC_type)ListHead->back().Load.Point)->back() });
		break;
	case 146: // LineIcCopyOutMk Выдать МК со ссылкой на последнюю ИП текущей линии
//		MkExec(Load, { CIC,((IC_type)ListHead->back().Load.Point)->back().СloneToIC() });
		break;

	case 160: // LineAdd Добавить новую строку всписок
		if (ListHead == nullptr) ListHead = new vector<ip>;
		if (ListHead == nullptr)
			ListHead = new vector<ip>;
		if(Load.Point!=nullptr)
			ListHead->push_back({ LineAtr, Load });
		break;
	case 161: // LineCopyAdd Добавить копию строки
		if (ListHead == nullptr) ListHead = new vector<ip>;
		if (Load.Point != nullptr)
			ListHead->push_back({ LineAtr, TIC, ICCopy(Load) });
		break;
	case 163: //  LineCopyAddPrevLoadSet Добавить линию в список и поместить ссылку на нее в нагрузку последней ИП последней строки
	 	if (ListHead == nullptr) ListHead = new vector<ip>;
		if(Load.Point==nullptr)
			ListHead->push_back({ LineAtr, TIC, new vector<ip> });
		else
			ListHead->push_back({ LineAtr, TIC, ICCopy(Load) });
		if (ListHead->size() > 1)
			((IC_type)ListHead->at(ListHead->size() - 2).Load.Point)->back().Load = ListHead->back().Load;
		break;
	case 162: // LineCopyTreeAdd Добавить копию ОА-графа
		if (ListHead == nullptr) ListHead = new vector<ip>;
		// ....
		break;
	case 164: // LineLoadOutMk Выдать МК с нагрузкой последней ИП текущей линии
		MkExec(Load, ((IC_type)(LineUk->Load.Point))->back().Load);
		break;
	case 165: // LineExcludeMk Исключить линию списка
		if (ListHead == nullptr || ListHead->size() == 0) break;
		if(Load.Point!=nullptr && Load.Type>>1==Dint) MkExec(*(int*)Load.Point, { TIC , (void*)ListHead->back().Load.Point });
		ListHead->pop_back();
		break;
	case 166: // LineDelMk Выдать МК со ссылкой на ИК и удалить ИК
		if (ListHead == nullptr || ListHead->size() == 0) break;
		MkExec(*(int*)Load.Point, { TIC , (void*)ListHead->back().Load.Point });
		ICDel(ListHead->back().Load.Point);
		ListHead->pop_back();
		break;
	case 167: // LineIpCut Удалить последние ИП из текущей линии (в нагрузке количество удаляемых ИП, по умолчанию 1)
	case 168: // LineVarIpCut" Hint = "Удалить последние ИП c пемеменными из текущей линии (в нагрузке количество удаляемых ИП, по умолчанию 1)" }
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
	case 170: // LastAttach Конкатенация ИК к последней линии списка
	case 171: // LastCopyAttach Конкатенация копии ИК к последней линии списка
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
	case 175: // LineAttach Конкатенация ИК к текущей линии списка
	case 176: // LineCopyAttach Конкатенация копии ИК к текущей линии списка
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
	case 185: // LastLoadSet Записать адрес в нагрузку последней ИП последней строки
	case 195: // LineLoadSet Записать адрес в нагрузку последней ИП последней строки
	case 186: // LastLoadCopySet Записать адрес в нагрузку последней ИП последней строки
	case 196: // LineLoadCopySet Записать адрес в нагрузку последней ИП последней строки
	case 187: // LastPointLoadCopyGraphSet
	case 197: // LinePointLoadCopyGraphSet
	case 189: // LastAtrSet Установить атрибут у последней ИК последней линии 
	case 199: // LineAtrSet Установить атрибут у последней ИК последней линии 
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
	case 180: // LineVarTypeSet // Установить тип 'переменная' в последней ИП текущей линии
		if (ListHead == nullptr || !ListHead->size() || \
			LineUk == nullptr || LineUk->Load.Point == nullptr || \
			LineUk->Load.Type>>1!=DIC || !((IC_type)LineUk->Load.Point)->size())
			break;
		((IC_type)LineUk->Load.Point)->back().Load.VarTypeSet(Load.ToBool(true));
		break;
	case 182: // LastVarTypeSet // Установить тип 'переменная' в последней ИП последней линии
		if (ListHead == nullptr || !ListHead->size() || \
			ListHead->back().Load.Type >> 1 != DIC || !((IC_type)ListHead->back().Load.Point)->size())
			break;
		((IC_type)ListHead->back().Load.Point)->back().Load.VarTypeSet(Load.ToBool(true));
		break;
//	case 181: // LastPointConstTypeSet // Установить тип 'константа' в последней ИП последней линии
//	case 183: // LinePointConstTypeSet // Установить тип 'константа' в последней ИП текущей линии
	case 200: // LineToLast Установить текущую строку на последнюю строку
		if(ListHead!=nullptr && ListHead->size()>0 && ListHead->back().Load.Point!=nullptr && ListHead->back().Load.Type>>1==DIC)
			LineUk = &ListHead->back();
		break;
	case 205: // LinePush Положить текущую линию в стек
		if (LineNum >= 0 && LineNum < ListHead->size() > 0) 
			LineStack.push_back(LineNum);
		break;
	case 206: // LineLastPush Положить последнюю линию в стек
		if (ListHead->size() > 0) LineStack.push_back(ListHead->size()-1);
		break;
	case 207: // LinePop Взять текущую линию из стека
		if (LineStack.size() && ListHead->size()> LineStack.back() && LineStack.back()>=0)
		{
			LineNum = LineStack.back();
			LineStack.pop_back();
			LineUk = ListHead->begin()._Ptr+ LineNum;
		}
		break;
	case 220: // FindOr Поиск ИЛИ
	case 221: // FindOrLastLine Поиск ИЛИ в последней строке
	case 226: // FindAnd Поиск И                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             227: // FindAndLastLine Поиск И в последней строке
	case 230: // FindXor Поиск XOR
	case 231: // FindXorLastLine Поиск XOR в последней строке
	case 236: // FindAndSource Поиск И в источнике
	case 237: // FindAndSourceLastLine Поиск И в источнике в последней строке
	{
		LineCount = 0; // счетчик совпадений
		LineNumOld = LineNum;
		LineNum = 0; // Номер первой совпадающей линии
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

	case 400: // LineOutMk Выдать МК с найденной линией
			MkExec(Load, LineUk->Load);
		break;
	case 401: // LineOut Выдать найденную линиию
			Load.Write(LineUk->Load.Point);
		break;

		// Программы по срезультатам сравнения номеров строк
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
	case 455: // DifferenceOut Выдать различие старой найденной линии и новой
		Load.Write(LineNum - LineNumOld);
		break;
	case 456: // DifferenceOutMk Выдать МК с различием старой найденной линии и новой
	{
		int temp = LineNum - LineNumOld;
		MkExec(Load, { Cint,&temp });
		break; }
	case 459: // LineNumSet Установить номер найденной строки (нужно для организации операций сравнения)
		LineNum = Load.ToInt();
		break;
	case 460: //LineCountOut Выдать количество найденных строк
		Load.Write(LineCount);
		break;
	case 461: //LineCountOutMk Выдать МК с количеством найденных строк
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
	// Программы по анализу строк
	case 500: // LineEmptyExec Выполнить подпрограмму, если текущая строка пустая
		if (ListHead != nullptr && LineUk != nullptr && ((IC_type)LineUk->Load.Point)->size()==0)
			ProgExec(Load);
		break;
	case 501: //LineFullExec  Выполнить подпрограмму, если текущая строка не пустая
		if (ListHead != nullptr && LineUk != nullptr && ((IC_type)LineUk->Load.Point)->size() != 0)
			ProgExec(Load);
		break;
	case 505: // LastEmptyExec  Выполнить подпрограмму, если последняя строка пустая
		if (ListHead != nullptr && ListHead->size() != 0 && ((IC_type)ListHead->back().Load.Point)->size() == 0)
			ProgExec(Load);
		break;
	case 506: //LastFullExec Выполнить подпрограмму, если последняя строка не пустая
		if (ListHead != nullptr && ListHead->size() != 0 && ((IC_type)ListHead->back().Load.Point)->size() != 0)
			ProgExec(Load);
		break;
	default:
		CommonMk(MK, Load);
		break;
	}
}
