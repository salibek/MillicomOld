#include "stdafx.h"
#include "InOut.h"
#include <algorithm>

using namespace std;

void InOut::ProgFU(int MK, LoadPoint Load)
{
	switch (MK)
	{
	case 0: // Reset
		Channels.clear();
		Ind = -1; // ����� �������� ������
		AutoInc = 0;
		CurrentCh = -1;
		break;
	case 1: //IndSet � ���������� ������� ������
		if (Load.Type >> 1 == Dint)
			Ind = *(int*)Load.Point;
		break;
	case 2: // AutoIncSet � ���������� �������������� ��������� (�� ��������� 0)
		if (Load.Type >> 1 == Dint)
			AutoInc = *(int*)Load.Point;
		break;
	case 3: //IndOut � ������ �������� �������� �������
		if (Load.Point != nullptr)
			if (Load.Type == Tint)
				*(int*)Load.Point = Ind;
		break;
	case 4: //IndOutMk � ������ �� �� ��������� �������� �������
		if (Load.Point != nullptr)
			if (Load.Type >> 1 == Dint)
				MkExec(*(int*)Load.Point, { Cint,&Ind });
		break;
	case 5: //NameOut � ������ ��������(���?) �������� �������   ???????????????
		if (Load.Type == Tstring)
			*(string*)Load.Point = Channels[Ind]->Name;
		Ind += AutoInc;
		break;
	case 6: //NameOutMk � ������ �� �� ���������(������) �������� ������� ???
		if (Load.Point != nullptr)
			if (Load.Type >> 1 == Dint)
				MkExec(*(int*)Load.Point, { Cstring,&Channels[Ind]->Name });
		Ind += AutoInc;
		break;
	case 7: // NameSet - ���������� ��� �������� ������
		if (Load.Point != nullptr)
			if (Load.Type >> 1 == Dstring)
				if (Ind >= 0 && Ind < Channels.size())
					Channels[Ind]->Name = *(string*)Load.Point;
		Ind += AutoInc;
		break;
	case 8: // NameIndSet � ���������� ������ �� ����� ������
		Ind = -1;
		if (Load.Type >> 1 == Dstring)
			for (auto& i : Channels)
				if (i->Name == *(string*)Load.Point) {
					Ind = i->Ind;
					break;
				}
		break;
	case 10: // CannelCreate �� ����� ���������� ����������� �������
	{
		int Count; // ���������� ����������� �������
		Count = 1;
		if (Load.Point != nullptr)
			if (Load.Type >> 1 == Dint)
				Count = *(int*)Load.Point;
		for (; Count; Count--) {
			Channels.push_back(new Channel((FU) this));
			Channels.back()->CurrentCh = &CurrentCh;
		}
		Nch = Channels.size(); // ��������� ���������� ��������� �������
		if (Load.Point != nullptr)
			if (Load.Type >> 1 == Dstring)
				Channels.back()->Name = *(string*)Load.Point;
		break;
	}
	case 15: // NChannelsOut ������ ���������� �������
		if (Load.Point != nullptr)
			if (Load.Type == Tint)
				*(int *)Load.Point = Nch;
		break;
	case 16: // NChannelsOutMK ������ �� � ����������� �������
		if (Load.Point != nullptr)
			if (Load.Type >> 1 == Dint)
				MkExec(*(int*)Load.Point, { Cint,&Nch });
		break;
	case 17: //ChannelClear
		Channels.clear();
		break;
	case 18: //ChannelNameSet
		if (Load.Type >> 1 == Dstring)
			if (Ind >= 0 && Ind < Channels.size())
				Channels[Ind]->Name = Load.Point != nullptr? *(string*)Load.Point: "";
		Ind += AutoInc;
	    break;
	case 19: //ChannelNameOut
		if (Load.Type == Tstring)
			if (Ind >= 0 && Ind < Channels.size())
				*(string*)Load.Point = Channels[Ind]->Name;
		Ind += AutoInc;
		break;
	case 20: //ChannelNameOutMk
		if (Load.Point != nullptr)
			if (Load.Type >> 1 == Dint)
				MkExec(*(int*)Load.Point, { Cstring, &Channels[Ind]->Name });
		break;
	case 24: // IndSet ���������� ������� ������
		Ind = 0;
		if (Load.Point != nullptr)
			if (Load.Type >> 1 == Dint)
				Ind = *(int*)Load.Point;
		break;
	case 25: //ChModeOut
		if (Load.Point != nullptr)
			if (Load.Type == Tint)
				*(int*)Load.Point = Channels[Ind]->Mode;
		break;
	case 26: //ChModeOutMk
		if (Load.Point != nullptr)
			if (Load.Type >> 1 == Dint)
				MkExec(*(int*)Load.Point, { Cint, &Channels[Ind]->Mode });
		break;
	case 27: // ChModeSet
		if (Ind >= 0 && Ind < Channels.size())
		{
			Channels[Ind]->Mode = 0;
			if (Load.Type >> 1 == Dint)
				Channels[Ind]->Mode = *(int*)Load.Point;
			Ind += AutoInc;
		}
		break;
	case 28: //ChannelActiveSet ���������� ����������/������������ �������� ������     
		if (Load.Type >> 1 == Dbool)
			if (Ind >= 0 && Ind < Channels.size())
				Channels[Ind]->Active = *(bool*)Load.Point;
		break;
	case 29: //SignalSet ���������� ������� �������� �������
		if (Ind >= 0 && Ind < Channels.size())
			if (Load.Type >> 1 == Ddouble)
				Channels[Ind]->Signal = *(double*)Load.Point;
		else if (Load.Type >> 1 == Dfloat)
			Channels[Ind]->Signal = *(float*)Load.Point;
		else if(Load.Type >> 1 == Dint)
				Channels[Ind]->Signal = *(int*)Load.Point;
		Ind += AutoInc;
		break;
	case 30: //SignalOutMk ������ ������� ������ 
		if (Load.Point != nullptr)
			if (Load.Type >> 1 == Dint)
				MkExec(*(int*)Load.Point, { Cdouble, &Channels[Ind]->Signal });
		break;
	case 31: //SignalPrevOutMk ������ ���������� ������
		if (Load.Point != nullptr)
			if (Load.Type >> 1 == Dint)
				MkExec(*(int*)Load.Point, { Cdouble, &Channels[Ind]->PrevSignal });
		break;
	
		//��������� �������
	case 34: //PeriodSet ���������� ������
		if (Load.Type >> 1 == Ddouble)
			if (Ind >= 0 && Ind < Channels.size())
				Channels[Ind]->Tact = *(double*)Load.Point;
		
		Ind += AutoInc;
		break;
	case 35: //PeriodOutMk
		if (Load.Point != nullptr)
			if (Load.Type >> 1 == Ddouble)
				MkExec(*(int*)Load.Point, { Cdouble, &Channels[Ind]->Tact });
		break;
	case 36: //SensitSet ���������� ����������������
		if (Ind >= 0 && Ind < Channels.size())
			if (Load.Point == nullptr)
				Channels[Ind]->Sensit = 0;
			else
				if (Load.Type >> 1 == Ddouble)
					Channels[Ind]->Sensit = *(double*)Load.Point;
				else if (Load.Type >> 1 == Dint)
					Channels[Ind]->Sensit = *(int*)Load.Point;

		Ind += AutoInc;
		break;
	case 37: //SensitOutMk
		if (Load.Point != nullptr)
			if (Load.Type >> 1 == Dint)
				MkExec(*(int*)Load.Point, { Cdouble, &Channels[Ind]->Sensit });
		break;
	case 38: //SignalMkSet
		if (Load.Type >> 1 == Dint)
			if (Ind >= 0 && Ind < Channels.size())
				Channels[Ind]->Mk = *(int*)Load.Point;
		break;
	case 39: //SignalAtrSet
		if (Load.Type >> 1 == Dint)
			if (Ind >= 0 && Ind < Channels.size())
				Channels[Ind]->Atr = *(int*)Load.Point;
		break;
		//��������� ������ �������
	case 40: //BorderSet
		if (Load.Type >> 1 == Ddouble || Load.Type >> 1 == Dint)
			if (Ind >= 0 && Ind < Channels.size())
				Channels[Ind]->Border.borders.push_back(*(double*)Load.Point);
		break;
	case 41: //BorderUpProgSet
		if (Ind >= 0 && Ind < Channels.size())
			Channels[Ind]->Border.UpProg.push_back(Load.Point);
	case 42: //BorderDownProgSet
		if (Ind >= 0 && Ind < Channels.size())
			Channels[Ind]->Border.DownProg.push_back(Load.Point);
		//������� �������������� �������
	case 43: //FactorSet
	case 44: //MaxSet
	case 45: //MinSet

	case 99: // ������ �������� ������� SignaCurrentlOut[0]
		if (Load.Point != nullptr)
			if (Load.Type == Ddouble)
				*(double*)Load.Point = Channels[CurrentCh]->Signal;
		break;
		//������� ������ �������� SignalOut[0 - 15]
	case 100: // ������� ������ ������� SignalOut[0]
	case 101: // ������� ������ ������� SignalOut[1]
	case 102: // ������� ������ ������� SignalOut[2]
	case 103: // ������� ������ ������� SignalOut[3]
	case 104: // ������� ������ ������� SignalOut[4]
	case 105: // ������� ������ ������� SignalOut[5]
	case 106: // ������� ������ ������� SignalOut[6]
	case 107: // ������� ������ ������� SignalOut[7]
	case 108: // ������� ������ ������� SignalOut[8]
	case 109: // ������� ������ ������� SignalOut[9]
	case 110: // ������� ������ ������� SignalOut[10]
	case 111: // ������� ������ ������� SignalOut[11]
	case 112: // ������� ������ ������� SignalOut[12]
	case 113: // ������� ������ ������� SignalOut[13]
	case 114: // ������� ������ ������� SignalOut[14]
	case 115: // ������� ������ ������� SignalOut[15]
		if (Load.Point != nullptr)
			if (Load.Type == Ddouble)
				*(double*)Load.Point = Channels[MK-100]->Signal;
		break;
			// ������� ������ �� �� ��������� ������� [0-15]
	
	case 145: //CurrentLoadOut ������ ��� �����������
		MkExec(MK, Load);
		break;
	case 149: //SignalCurrentOutMk  ������ �� � ������� ��������
		if (Load.Point != nullptr)
			if (Load.Type >> 1 == Dint)
				MkExec(*(int*)Load.Point, { Cdouble, &Channels[CurrentCh]->Signal });
	case 150: //SignalOutMk [0]
	case 152: //SignalOutMk [1]
	case 153: //SignalOutMk [2]
	case 154: //SignalOutMk [3]
	case 155: //SignalOutMk [4]
	case 156: //SignalOutMk [5]
	case 157: //SignalOutMk [6]
	case 158: //SignalOutMk [7]
	case 159: //SignalOutMk [8]
	case 160: //SignalOutMk [9]
	case 161: //SignalOutMk [10]
	case 162: //SignalOutMk [11]
	case 163: //SignalOutMk [12]
	case 164: //SignalOutMk [13]
	case 165: //SignalOutMk [14]
	case 166: //SignalOutMk [15]
		if (Load.Point != nullptr)
			if (Load.Type >> 1 == Dint)
				MkExec(*(int*)Load.Point, { Cdouble, &Channels[MK - 150]->Signal });
		break;
	case 200: //SignalAtrSet [1]
	case 201: //SignalAtrSet [1]
	case 202: //SignalAtrSet [2]
	case 203: //SignalAtrSet [3]
	case 204: //SignalAtrSet [4]
	case 205: //SignalAtrSet [5]
	case 206: //SignalAtrSet [6]
	case 207: //SignalAtrSet [7]
	case 208: //SignalAtrSet [8]
	case 209: //SignalAtrSet [9] 
	case 210: //SignalAtrSet [10]
	case 211: //SignalAtrSet [11]
	case 212: //SignalAtrSet [12]
	case 213: //SignalAtrSet [13]
	case 214: //SignalAtrSet [14]
	case 215: //SignalAtrSet [15]
		if (Load.Type >> 1 == Dint)
				Channels[MK - 200]->Atr = *(int*)Load.Point;
		break;

	case 250: // SignalSet_0 
	case 251: // SignalSet 
	case 252: // SignalSet
	case 253: // SignalSet
	case 254: // SignalSet
	case 255: // SignalSet
	case 256: // SignalSet
	case 257: // SignalSet
	case 258: // SignalSet
	case 259: // SignalSet
	case 260: // SignalSet
	case 261: // SignalSet
	case 262: // SignalSet
	case 263: // SignalSet
	case 264: // SignalSet
	case 265: // SignalSet_15
		
	{
		if (Channels[MK - 250]->Active)
		{
			if (Load.Point == nullptr)
				Channels[MK - 250]->Signal = 0;
			else
				Channels[MK - 250]->PrevSignal = Channels[MK - 250]->Signal;
			if (Load.Type >> 1 == Dint)
				Channels[MK - 250]->Signal = *(int*)Load.Point;
			else if (Load.Type >> 1 == Ddouble)
				Channels[MK - 250]->Signal = *(double*)Load.Point;
			else if (Load.Type >> 1 == Dfloat)
				Channels[MK - 250]->Signal = *(float*)Load.Point;

			if (Channels[MK - 250]->Mk >= 0 && abs(Channels[MK - 250]->Signal - Channels[MK - 250]->PrevSignal) >= Channels[MK - 250]->Sensit)
				if (Channels[MK - 250]->Atr >= 0)
					MkExec(Channels[MK - 250]->Mk, { Cdouble, &Channels[MK - 250]->Signal });
				else
				{
					Channels[MK - 250]->OutIP = { Channels[MK - 250]->Atr ,{Cdouble, &Channels[MK - 250]->Signal} };
					MkExec(Channels[MK - 250]->Mk, { CIP, &Channels[MK - 250]->OutIP });
   			    }
		}
		break;
	}
	default:
		CommonMk(MK, Load);
	}
}


void AutomatManager::ProgFU(int MK, LoadPoint Load)
{
	switch (MK)
	{
	case 0: // Reset
		ReceiverMk = -1;
		Template = nullptr; // ���������� �������� ��� ��������� ��
		Var = nullptr;
		IPout = { 0, {0,new double()} };
		IPoutPrev = { 0, {0,new double()} };
		StageInProg.clear();
		StageOutProg.clear();
		StageProgMk = -1;
		break;
	case 3: // RecieverMKSet
		if (Load.Point == nullptr || Load.Type >> 1 != Dint)
			ReceiverMk = -1;
		else
		{
			if (StageOutProg.find(ReceiverMk) != StageOutProg.end() && ReceiverMk>=0)
				ProgExec(StageOutProg[ReceiverMk]);

			ReceiverMk = *(int*)Load.Point;
			// ������ ��������� ��� ��������� ��������
			if (StageInProg.find(ReceiverMk) != StageInProg.end())
				ProgExec(StageInProg[ReceiverMk]);
		}
		if (TemplAutoClear) ((IC_type)Template)->clear();
		break;
	case 4: // TemplAutoClearSet ���������� ���� ��������������� ������ ������� ������ ��� ��������� �� ��� ���������� ������ �������
		TemplAutoClear = Load.ToBool();
		break;
	case 5: // StageProgInAdd �������� ������ ��������� ��� ���������
	case 6: // StageProgOutAdd �������� �������� ��������� ��� ���������
		if (StageProgMk < 0){
			if (Load.Type >> 1 == Dint)
				StageProgMk = *(int*)Load.Point;
			}
		else
			{
			if (Load.Type >>= DIC)
				if(MK==5)
					StageInProg[StageProgMk] = (void*)Load.Point;
				else
					StageOutProg[StageProgMk] = (void*)Load.Point;
			StageProgMk = -1;
			}
		break;
	case 7: // StageProgInClear �������� ������ ������� �������� ���������
		StageInProg.clear();
		break;
	case 8: // StageProgOutClear �������� ������ �������� �������� ���������
		StageOutProg.clear();
		break;
	case 10: // TemplSet
		if (Load.Point == nullptr || Load.Type >> 1 != DIC)
			Template = nullptr;
		else
			Template = Load.Point;
		break;
	case 11: // TemplClear �������� �� �������
		(*(IC_type)Template).clear();
		break;
	case 15: // TemplOut
		if (Load.Point != nullptr)
			if (Load.Type == DIC)
				Load.Point = (void*)Template;
		break;
	case 16: // TemplOutMK
		if (Load.Point != nullptr || Load.Type >> 1 == DIC)
			MkExec(*(int*)Load.Point, { DIC,&Template });
		break;
	case 17: // TemplClear
		Template = nullptr;
		break;
	case 20: // VarSet
		if (Load.Point == nullptr || Load.Type >> 1 != DIC)
			Var = nullptr;
		else
			Var = Load.Point;
		break;
	case 21: // VarOut
		if (Load.Point != nullptr)
			if (Load.Type == DIC)
				Load.Point = (void*)Var;
		break;
	case 22: // VarOutMK
		if (Load.Point != nullptr || Load.Type >> 1 == DIC)
			MkExec(*(int*)Load.Point, { DIC,&Var });
		break;
	case 30: // SignalOut
		if (Load.Point != nullptr)
			if (Load.Type == CIP)
				Load.Point = (void*)&IPout; //??
		break;
	case 31: // SignalOutMK
		if (Load.Point != nullptr || Load.Type >> 1 == Dint)
			MkExec(*(int*)Load.Point, { CIP,&IPout });
		break;
	case 33: // SignalAtrOut
		if (Load.Point != nullptr)
			if (Load.Type == Dint)
				*(int*)Load.Point = IPout.atr;
		break;
	case 34: // SignalAtrOutMK
		if (Load.Point != nullptr || Load.Type >> 1 == Dint)
			MkExec(*(int*)Load.Point, { Cint,&IPout.atr });
		break;
	case 35: // SignalLoadOut
		if (Load.Point != nullptr)
			if (Load.Type == Dint)
				*(LoadPoint*)Load.Point = IPout.Load;

		break;
	case 36: // SignalLoadOutMK
		if (Load.Point != nullptr || Load.Type >> 1 == Dint)
			MkExec(*(int*)Load.Point, IPout.Load);
		break;
	case 37: // SignalAtrSet
		if (Load.Point != nullptr || Load.Type >> 1 == Dint)
			IPout.atr = *(int*)Load.Point;
		break;
	case 38: // SignalLoadSet
		if (Load.Point != nullptr)
			IPout.Load = Load;
		break;
	case 50: // SignalSet
	case 51: // Send
	{
		if (Load.Point != nullptr)
			if (Load.Type >> 1 == DIC && (*((IC_type)Load.Point)).size() > 0)
				IPout = (*((IC_type)Load.Point))[0];
		if (Load.Type >> 1 == DIP)
			IPout = *((ip*)Load.Point);
		// ���������, ���� �� ������� � �� ����������
		auto ukVar = AtrFind(Var, IPout.atr);
		if (!ukVar)
			;// ������
		else
		{
			// �������� � �� �������
			auto ukTempl = AtrFind(Template, IPout.atr);
			if (!ukTempl)
				(*(IC_type)Template).push_back(IPout);
			else
				ukTempl->Load = IPout.Load;
		}
		if (MK == 51) // ��������� ������ �� ��-���������
			if (ReceiverMk >= 0)
				MkExec(ReceiverMk, { CIC,Template });
		break;
	}
	default:
		CommonMk(MK, Load);
	}
}

void border::Run(LoadPoint Load) {
	if (!borders.size())return; // ���� ��� ������
	double val = Load.ToDouble();
	if (!borders.size()) return;
	if (Start) // ���� ������ ������
	{
		OldVal = val;
		Start = false;
		return;
	}
	auto uk = borders.begin();
	for (; uk != borders.end() && *uk<=val, val; uk++);
	if (uk == borders.end())
	{
		if(OldVal<=borders.back())
			Parent.ProgExec(UpProg.back());
	}
	else
	if(OldVal>=*(uk+1))
			Parent.ProgExec(DownProg[distance(borders.begin(),uk)+1]);
		else
			if (uk!=borders.begin() && OldVal <= *(uk-1))
				Parent.ProgExec(UpProg[distance(borders.begin(), uk)-1]);
	OldVal = val;

};