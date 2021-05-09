#include "stdafx.h"
#include "Bag.h"
#include <fstream>

void BagPoint::ProgFU(int MK, LoadPoint Load)
{
	switch(MK)
	{
	case 1: // Calc ��������� ��������
		if (p_Diag < 0)
			p = p_Up; // ������ ������
		else
			p = max(p_Up, p_Diag + Load.ToDouble());
		if (Down) Down->ProgFU(2, { Cdouble,&p }); // �������� ����
		if (Diagonal) Diagonal->ProgFU(3, { Cdouble,&p }); // �������� �� ���������
		if (Next) Next->ProgFU(1, Load); // �������� ������
		break;
	case 2: // Up ������� �������� ������
		p_Up = Load.ToDouble();
		break;
	case 3: // Diag ������� �������� �� ���������
		p_Diag = Load.ToDouble();
		break;
	}
}

void Bag::ProgFU(int MK, LoadPoint Load)
{
	switch (MK)
	{
	case 0: // Reset
		for (auto& i : Field)
			i.resize(0);
		Field.resize(0);
		break;
	case 1: // Start
	{
		ifstream in(Load.ToStr());
		in>>WMax;
		Field.push_back({ {} });
		for(int i=0;i<=WMax;i++)
			Field.back().push_back({});
		W.push_back(0); // ������ �������
		P.push_back(0); // ������ �������
		while (!in.eof()) // 
		{
			int w;
			double p;
			in >> w >> p;
			W.push_back(w); P.push_back(p);
			Field.push_back({}); // ��������� �������������� �����
			for (int i = 0; i < WMax; i++)
				Field.back().push_back({});
		}
		in.close();
		// ������
		for(int i=1;i<Field.size();i++)
			for (int j = 0; j < Field[0].size()-1; j++)
			{
				Field[i][j].Next = &Field[i][j + 1];
				if (i < Field[0].size() - 1)
				{
					Field[i][j + 1].Down = &Field[i + 1][j + 1];
					if(j+1+W[i]<= WMax)
						Field[i][j+1].Diagonal = & Field[i + 1][j + 1+W[i]];
				}
			}
		// ������ ����������
		for (int i = 0; i < P.size(); i++)
			Field[i][1].ProgFU(1,{Cdouble, & P[i]}); // ������ ���������� �� ������ �����
		break;
	}
	case 10: // RezOut ������ ���������
		if (Field.size() && Field[0].size())
			Load.Write(Field[Field.size() - 1][Field[0].size() - 1].p);
		break;
	case 11: // RezOutMk ������ �� � �����������
		if (Field.size() && Field[0].size())
			MkExec(Load, { Cdouble,&Field[Field.size() - 1][Field[0].size() - 1].p });
		break;
	default:
		CommonMk(MK, Load);
		break;
	}
}