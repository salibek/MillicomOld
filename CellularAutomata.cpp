#include "CellularAutomat.h"

// ���������� ��������� ������� (���������� ��� ���������� �������� �������)
void CellularAutomat::ProgFU(int MK, LoadPoint Load)
{
	// �������� ����� �� � ���������
	if (ReceiveProg != nullptr && Mode == 0) // ������ ��������� ����������� ������, �.�. ������ ������� �������������� ������������ ���������� ��
	{
		int t = Mode; 
		Mode = 0; // ������� ����� ������ �� �������
		ProgExec(ReceiveProg);
		if(!Mode)
			Mode = t; // ������������ ������� ����� ������ ��
	}
	switch (MK)
	{
	case 0: // Reset
		PlyInd = 0;
		if (AccumCreating)
		{
			delete Alu;
			Alu = nullptr;
			AccumCreating = false;
		}
		Neighbours.resize(0);
		NeighboursMk.resize(0);
		RezReady.resize(0);
		InCounter.resize(0);
		Rez.resize(0);
		Plys.resize(0);
		InComplectF.resize(0);
		PlyCurrent = 0; ParameterInd = -1;
		CalcProg = nullptr; ReceiveProg = nullptr; IndFuOffcet = 0; FUInd = 0;
		break;
	case 700: // N_NeighbourSet ���������� ���������� �������
		Neighbours.resize(Load.ToInt());
		NeighboursMk.resize(Load.ToInt());
		if (!Plys.size())
		{
			for (auto& i : Plys)
				i.resize(Load.ToInt());
		}
		break;
	case 701: // N_PlySet ���������� ���������� ����� ��� �������
		Plys.resize(Load.ToInt());
		Rez.resize(Load.ToInt());
		if (!Neighbours.size())
			for (auto& i : Plys)
				i.resize(Neighbours.size());
		break;
	case 705: //RezSet  ���������� ��������� ���������� (���� PlyInd<0, �������� �������� ��������� ������� �������� ����)
		Rez[PlyInd < 0 ? Rez.size() - 1 : PlyInd] = Load.ToDouble();
		break;
	case 706: //RezOut ������ ��������� ���������� (���� PlyInd<0, �������� �������� ��������� ������� �������� ����)
		Load.Write(Rez[PlyInd < 0 ? Rez.size() - 1 : PlyInd]);
		break;
	case 707: //RezOutMk ������ �� � ����������� ���������� (���� PlyInd<0, �������� �������� ��������� ������� �������� ����)
	{
		double t = Rez[PlyInd < 0 ? Rez.size() - 1 : PlyInd];
		MkExec(Load, {Cdouble, &t });
		break;
	}
	case 708: // PlyIndSet ���������� ������ ���� ��� �������
		PlyInd = Load.ToInt(-1);
		break;
	case 710: //�	IndFuOffcetSet �������� ������� �� (������ ����������� �� ��� �������� � � ���� ������������ ������ ����)
		IndFuOffcet = Load.ToInt();
		break;
	case 711: // �	ModeSet ����� ������ �������� (0 - ���������, 1 - ������� �����)
		Mode = Load.ToInt();
	case 715: //CollectorSet 
		CollectorFU = Load.Point;
		break;
	case 720: // �CalcProgSet ���������� ������ �� ��������� ���������� ���������� ��� ���������� ������ ������
		CalcProg = Load.Point;
		break;
	case 721: // �CalcProgOut ���������� ������ �� ��������� ���������� ���������� ��� ���������� ������ ������
		Load.Write(CalcProg);
		break;
	case 722: // �CalcProgOutMk ���������� ������ �� ��������� ���������� ���������� ��� ���������� ������ ������
		MkExec(Load, {CIC, CalcProg });
		break;
	case 725: // ReceiveProgSet ���������� ���������, ����������� ��� ������ ������
		ReceiveProg = Load.Point;
		break;
	case 726: // ReceiveProgOut ���������� ������ �� ��������� ���������� ���������� ��� ���������� ������ ������
		Load.Write(ReceiveProg);
		break;
	case 727: // �ReceiveProgOutMk ���������� ������ �� ��������� ���������� ���������� ��� ���������� ������ ������
		MkExec(Load, { CIC, ReceiveProg });
		break;
	case 730: // �AutoSendSet ���������� ���� �������������� ��������� ����������� ����������
		AutoSend = Load.ToBool();
		break;
	case 735: // �	RezReadyOut 
		Load.Write(RezReady);
		break;
	case 736: // �	RezReady OutMk
		MkExec(Load,{Cbool, &RezReady});
		break;
	case 740: // VarAdd �������� ��������� ����������
		Vars.push_back(Load.ToDouble());
		break;
	case 741: // VarClear �������� ������ ��������� ����������
		Vars.clear();
		break;
	case 742: // VarIndexSet ���������� ������ ��������� (���� -1, �� ���������� ��������� ����������� ��������)
	case 743: // VarOut ������ ��������� ����������
		if (VarInd < 0)
			Load.Write(Vars.back());
		else
			Load.Write(Vars[VarInd]);
		break;
	case 744: // VarOutMk ������ �� � ��������� ����������
		if (VarInd < 0)
			MkExec(Load, { Cdouble,&Vars.back() });
		else
			MkExec(Load, { Cdouble,&Vars[VarInd] });
		break;
	case 748: // VarSet ���������� �������� � ������ ���������� (���� VarInd=-1, �� ������������� ��������� ��������)
		if (VarInd < 0)
			Vars[Vars.size() - 1] = Load.ToDouble();
		else
			Vars[VarInd] = Load.ToDouble();
		break;
	case 745: // �ParameterIndSet ������ �������� ��������� (��� -1 �������� ��������� ��������)
		ParameterInd = Load.ToInt();
		break;
	case 746: // �ParameterClear �������� ������ ����������
		ParameterInd = -1;
		parameters.clear();
		break;
	case 750: // ParameterSet ���������� �������� (��� -1 ����������� ����� ��������)
		if (ParameterInd < 0)
			parameters.push_back(Load);
		else
			if(ParameterInd< parameters.size())
				parameters[ParameterInd]=Load;
		break;
	case 751: // ParametrOut
		if (ParameterInd < 0)
			Load.WriteFromLoad(parameters.back());
		else
			if(ParameterInd< parameters.size())
				parameters.back().WriteFromLoad(Load);
		break;
	case 752: // ParametrOutMk
		if (ParameterInd < 0)
			MkExec(Load, parameters.back());
		else
			if (ParameterInd < parameters.size())
				MkExec(Load, parameters[ParameterInd]);
		break;
	case 753: // ParameterAdd �������� ����� ��������
		parameters.push_back(Load.Clone());
		break;
	case 755: // �InComplectFSet
		Load.Write(InComplectF[PlyCurrent]);
		break;
	case 756: // �InComplectFOut
		Load.Write(InComplectF[PlyCurrent]);
		break;
	case 757: // �InComplectFOutMk
		MkExec(Load, { Cbool,&InComplectF });
		break;
	case 760: //ParametersCountOut
		Load.Write(parameters.size());
		break;
	case 761: //ParametersCountOutMk
	{
		int t = parameters.size();
		MkExec(Load, { Cint,&t });
		break;
	}
	case 763: // FUIndSet ���������� ������ ��-��������
		FUInd = Load.ToInt();
		break;
	case 765: // �	ManagerSet ���������� ������ �� ��������� ��������
		Manager = Load.Point;
		break;
	case 770: // ���������/������� �����
		Mode = Load.ToInt();
		break;
	case 780: // RezSend ������ ��������� ���������� �������
		for (int i = 0; i < Neighbours.size(); i++)
			MkExec(NeighboursMk[i], {Cdouble,&Rez[PlyCurrent]});
		break;
	case 785: // CalcPrigSet ���������� ��������� ���������� �����������
		CalcProg = Load.Point;
		break;
	case 790: // InCounterSet ���������� ������� ������� ������ (���� PlyInd<0, �� ��������������� ��� �������� ������)
		if(PlyInd<0)
			InCounter[PlyCurrent] = Load.ToInt();
		else
			InCounter[PlyInd] = Load.ToInt();
		break;
	case 791: // InCounterOut ������ ������� �������� ������� ������
		Load.Write(InCounter);
		break;
	case 792: // InCounterOutMk ������ �� �� ��������� �������� ������� ������
		MkExec(Load, { Cint,&InCounter });
		break;
	case 795: // RezOut ������ ��������� ���������� (���� PlyInd<0, �� �������� ��������� �������� ����)
		if(PlyInd>=0)
			Load.Write(Rez[PlyInd]);
		else
			Load.Write(Rez[PlyCurrent]);
		break;
	case 796: // RezOutMk
		if (PlyInd >= 0)
			MkExec(Load, {Cdouble, &Rez[PlyInd] });
		else
			MkExec(Load, { Cdouble, &Rez[PlyCurrent] });
		break;
	case 797: //  PlyCurrentOut ������ ������ �������� ���� �������
		Load.Write(PlyCurrent);
		break;
	case 798: //  PlyCurrentOutMk ������ �� � �������� �������� ���� �������
		MkExec(Load, { Cint, &PlyCurrent });
		break;
	case 800: // FUIndSet ���������� ������ ��������
		FUInd = Load.ToInt();
		break;
	case 801: // FUIndSet ������ ������ ��������
		Load.Write(FUInd);
		break; 
	case 802: // FUIndSet ������ �� � �������� ��������
		MkExec(Load, {Cint,&FUInd});
		break;


	case 885: // SendToManager ��������� �� ��� ��������� �� ���������
		if(Load.Type>>1==DIC)
			for(auto i: *(IC_type)Load.Point)
				MkExec(i.atr,i.Load,(FU*)Manager);
		else if(Load.Type >> 1 == DIP)
			MkExec(((ip*)Load.Point)->atr, ((ip*)Load.Point)->Load, (FU*)Manager);
		break;
	case 886: // SendToCollector ��������� �� ��� ��������� �� ����������
		if (Load.Type >> 1 == DIC)
			for (auto i : *(IC_type)Load.Point)
				MkExec(i.atr, i.Load, (FU*)CollectorFU);
		else if (Load.Type >> 1 == DIP)
			MkExec(((ip*)Load.Point)->atr, ((ip*)Load.Point)->Load, (FU*)CollectorFU);
		break;

	case 890: //Synk ������������� ���������� (�� ����� ������� �� ������ ��������� ���������� �������, ���� �� ���������� AutoSend)
		if (RezReady[PlyCurrent])
		{
			for (int i=0;i< Neighbours.size(); i++)
				MkExec(NeighboursMk[i]+IndFuOffcet, {Cdouble,&Rez[PlyCurrent]}, Neighbours[i]);
			PlyCurrent = (PlyCurrent + 1) % Neighbours.size();
		}
		break;
	case 1:   //In_1_Set ������� �������� �� 1-�� ������
	case 101: //In_1_Out ������ ��������, ���������� �� 1-�� ������
	case 201: //In_1_OutMk ������ �� ��� ���������, ���������� �� 1-�� ������
	case 301: //NeighbourMk_1_Set ���������� �� ��� 1-�� ������
	case 401: //Parametr_1_Set ���������� 1-� ��������
	case 501: //Parametr_1_Out ������ 1-� ��������
	case 601: //Parametr_1_OutMk ������  �� � 1-� ����������
	case 2:   //In_2_Set ������� �������� �� 2-�� ������
	case 102: //In_2_Out ������ ��������, ���������� �� 2-�� ������
	case 202: //In_2_OutMk ������ �� ��� ���������, ���������� �� 2-�� ������
	case 302: //NeighbourMk_2_Set ���������� �� ��� 2-�� ������
	case 402: //Parametr_2_Set ���������� 2-� ��������
	case 502: //Parametr_2_Out ������ 2-� ����������
	case 602: //Parametr_2_OutMk ������  �� � 1-� ��������
	case 3:   //In3_Set ������� �������� �� 3-�� ������
	case 103: //In3_Out ������ ��������, ���������� �� 3-�� ������
	case 203: //In3_OutMk ������ �� ��� ���������, ���������� �� 3-�� ������
	case 303: //NeighbourMk_3_Set ���������� �� ��� 3-�� ������
	case 403: //Parametr_2_Set ���������� 3-� ��������
	case 503: //Parametr_2_Out ������ 3-� ��������
	case 603: //Parametr_2_OutMk ������ �� � 3-� ����������
	case 4:   //In4_Set ������� �������� �� 4-�� ������
	case 104: //In4_Out ������ ��������, ���������� �� 4-�� ������
	case 204: //In4_OutMk ������ �� ��� ���������, ���������� �� 4-�� ������
	case 304: //NeighbourMk_4_Set ���������� �� ��� 4-�� ������
	case 404: //Parametr_3_Set ���������� 4-� ��������
	case 504: //Parametr_3_Out ������ 4-� ��������
	case 604: //Parametr_3_OutMk ������  �� � 4-� ����������
	case 5:   //In5_Set ������� �������� �� 5-�� ������
	case 105: //In5_Out ������ ��������, ���������� �� 5-�� ������
	case 205: //In5_OutMk ������ �� ��� ���������, ���������� �� 5-�� ������
	case 305: //NeighbourMk_5_Set ���������� �� ��� 5-�� ������
	case 405: //Parametr_4_Set ���������� 5-� ��������
	case 505: //Parametr_4_Out ������ 5-� ��������
	case 605: //Parametr_4_OutMk ������  �� � 5-� ��������
	case 6:   //In6_Set ������� �������� �� 6-�� ������
	case 106: //In6_Out ������ ��������, ���������� �� 6-�� ������
	case 206: //In6_OutMk ������ �� ��� ���������, ���������� �� 6-�� ������
	case 306: //NeighbourMk_6_Set ���������� �� ��� 6-�� ������
	case 406: //Parametr_5_Set ���������� 6-� ��������
	case 506: //Parametr_5_Out ������ 6-� ��������
	case 606: //Parametr_5_OutMk ������  �� � 6-� ��������
	case 7:   //In7_Set ������� �������� �� 7-�� ������
	case 107: //In7_Out ������ ��������, ���������� �� 7-�� ������
	case 207: //In7_OutMk ������ �� ��� ���������, ���������� �� 7-�� ������
	case 307: //NeighbourMk_7_Set ���������� �� ��� 7-�� ������
	case 407: //Parametr_6_Set ���������� 7-� ��������
	case 507: //Parametr_6_Out ������ 7-� ��������
	case 607: //Parametr_6_OutMk ������  �� � 7-� ��������
	case 8:   //In8_Set ������� �������� �� 8-�� ������
	case 108: //In8_Out ������ ��������, ���������� �� 8-�� ������
	case 208: //In8_OutMk ������ �� ��� ���������, ���������� �� 8-�� ������
	case 308: //NeighbourMk_8_Set ���������� �� ��� 8-�� ������
	case 408: //Parametr_7_Set ���������� 8-� ��������
	case 508: //Parametr_7_Out ������ 8-� ��������
	case 608: //Parametr_7_OutMk ������  �� � 8-� ��������
	case 9:   //In9_Set ������� �������� �� 9-�� ������
	case 109: //In9_Out ������ ��������, ���������� �� 9-�� ������
	case 209: //In9_OutMk ������ �� ��� ���������, ���������� �� 9-�� ������
	case 309: //NeighbourMk_9_Set ���������� �� ��� 9-�� ������
	case 409: //Parametr_8_Set ���������� 9-� ��������
	case 509: //Parametr_8_Out ������ 9-� ��������
	case 609: //Parametr_8_OutMk ������  �� � 9-� ��������
	case 10:  //In10_Set ������� �������� �� 10-�� ������
	case 110: //In10_Out ������ ��������, ���������� �� 10-�� ������
	case 210: //In10_OutMk ������ �� ��� ���������, ���������� �� 10-�� ������
	case 310: //NeighbourMk_10_Set ���������� �� ��� 10-�� ������
	case 410: //Parametr_9_Set ���������� 10-� ��������
	case 510: //Parametr_9_Out ������ 10-� ��������
	case 610: //Parametr_9_OutMk ������   �� � 10-� ��������
	case 11:  //In11_Set ������� �������� �� 11-�� ������
	case 111: //In11_Out ������ ��������, ���������� �� 11-�� ������
	case 211: //In11_OutMk ������ �� ��� ���������, ���������� �� 11-�� ������
	case 311: //NeighbourMk_11_Set ���������� �� ��� 11-�� ������
	case 411: //Parametr_10_Set ���������� 11-� ��������
	case 511: //Parametr_10_Out ������ 11-� ��������
	case 611: //Parametr_10_OutMk ������  �� 11-� ��������
	case 12:  //In12_Set ������� �������� �� 12-�� ������
	case 112: //In12_Out ������ ��������, ���������� �� 12-�� ������
	case 212: //In12_OutMk ������ �� ��� ���������, ���������� �� 12-�� ������
	case 312: //NeighbourMk_12_Set ���������� �� ��� 12-�� ������
	case 412: //Parametr_11_Set ���������� 12-� ��������
	case 512: //Parametr_11_Out ������ 12-� ��������
	case 612: //Parametr_11_OutMk ������  �� 12-� ��������
	case 13:  //In13_Set ������� �������� �� 13-�� ������
	case 113: //In13_Out ������ ��������, ���������� �� 13-�� ������
	case 213: //In13_OutMk ������ �� ��� ���������, ���������� �� 13-�� ������
	case 313: //NeighbourMk_13_Set ���������� �� ��� 13-�� ������
	case 413: //Parametr_12_Set ���������� 13-� ��������
	case 513: //Parametr_12_Out ������ 13-� ��������
	case 613: //Parametr_12_OutMk ������  �� 13-� ��������
	case 14:  //In14_Set ������� �������� �� 14-�� ������
	case 114: //In14_Out ������ ��������, ���������� �� 14-�� ������
	case 214: //In14_OutMk ������ �� ��� ���������, ���������� �� 14-�� ������
	case 314: //NeighbourMk_14_Set ���������� �� ��� 14-�� ������
	case 414: //Parametr_13_Set ���������� 14-� ��������
	case 514: //Parametr_13_Out ������ 14-� ��������
	case 614: //Parametr_13_OutMk ������ �� 14-� ��������
	case 15:  //In15_Set ������� �������� �� 15-�� ������
	case 115: //In15_Out ������ ��������, ���������� �� 15-�� ������
	case 215: //In15_OutMk ������ �� ��� ���������, ���������� �� 15-�� ������
	case 315: //NeighbourMk_15_Set ���������� �� ��� 15-�� ������
	case 415: //Parametr_14_Set ���������� 15-� ��������
	case 515: //Parametr_14_Out ������ 15-� ��������
	case 615: //Parametr_14_OutMk ������ �� 15-� ��������
	case 16:  //In16_Set ������� �������� �� 16-�� ������
	case 116: //In16_Out ������ ��������, 16-�� ������
	case 216: //In16_OutMk ������ �� ��� ���������, ���������� �� 16-�� ������
	case 316: //NeighbourMk_16_Set ���������� �� ��� 16-�� ������
	case 416: //Parametr_15_Set ���������� 16-� ��������
	case 516: //Parametr_15_Out ������ 16-� ��������
	case 616: //Parametr_15_OutMk ������ �� 16-� ��������
		if (MK / 100 == 1) // ������ �������� ������
			Load.Write(Plys[PlyInd][MK % 100]);
		else if (MK / 100 == 2) // ������ ������ �� �� ���������
			MkExec(Load, Plys[PlyInd][MK % 100]); 
		else if (MK / 100 == 3) // ���������� ������ �� ������
			Neighbours[MK % 100] = (CellularAutomat*)Load.Point;
		else if (MK / 100 == 4) // ���������� �� ��� ������
			NeighboursMk[MK % 100] = Load.ToInt(); // ���������� �� ��� ������
		else if (MK / 100 == 4) // ���������� ��������
			parameters[MK % 100].WriteFromLoad(Load);
		else if (MK / 100 == 6) // ������ �� � ����������
			MkExec(Load, parameters[MK % 100]);
		else if (MK / 100 == 0)// ������ �������� �� ������
		{
			if(Plys[PlyCurrent][MK%100].Point==nullptr)
				InCounter[PlyCurrent]++;
			Plys[PlyCurrent][MK % 100] = Load.Clone();
			if (InCounter[PlyCurrent] == Neighbours.size()) // �������� ������ ��������
			{
				InComplectF[PlyCurrent][MK % 100] = true;
				RezReady[MK % 100] = true;
				ProgExec(CalcProg);
				RezReady[PlyCurrent] = true;
				if(AutoSend) ProgFU(890, { 0, nullptr });
				PlyCurrent++;
				InCounter[PlyCurrent] = 0;
				RezReady[PlyCurrent] = false;
				for(int i=0;i<Neighbours.size();i++)
					InComplectF[PlyCurrent][i]= false;
			}
		}
		break;
	default:
		CommonMk(MK, Load);
		break;
	}
}

void CellularAutomatManager::ProgFU(int MK, LoadPoint Load)
{
	// �������� ����� �� � ���������
	switch (MK)
	{
	case 0: // Reset
		NetType = 0;
		break;
	case 1:// NetTypeSet ���������� ��� �����
		NetType = Load.ToInt();
		break;
	case 3: // DimAdd �������� ���������
		Dim.push_back(Load.ToInt());
	case 5: // DimClear �������� ������� ������������
		Dim.clear();
	case 10: // IniAutmataProgSet ���������� ��������� ������������� ��������
		iniAutmataProg = Load.Point;
	default:
		CommonMk(MK, Load);
		break;
	}
}