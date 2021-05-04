#include "stdafx.h"
#include "gauss.h"

const int Key = 1, KeyToRight = 3, DownARight = 5, DownA = 7, Cof=9, Zero = 11, SumToLeft = 13, SumToLeftUp=15, Up=17;

void GaussPoint::ProgFU(int MK, LoadPoint Load)
{
	switch (MK)
	{
	case 1: // Key
		if (Neighbours[3] == nullptr)
			Neighbours[0]->ProgFU(SumToLeftUp, { Cdouble, new double(0)});
		else
		{
			if (Neighbours[0] != nullptr)
				Neighbours[0]->ProgFU(DownARight, { 0, nullptr });
			Neighbours[3]->ProgFU(Zero, { Cint,&a });
			Neighbours[3]->ProgFU(KeyToRight, { 0, nullptr });
		}
		break;
	case 3://	KeyToRight
		Neighbours[0]->ProgFU(Key, { 0, nullptr });
		break;
	case 5:	//	DownARight
		if(Neighbours[3]!=nullptr)
			Neighbours[3]->ProgFU(DownA, { Cint,&a });
		if (Neighbours[0] != nullptr)
			Neighbours[0]->ProgFU(DownARight, { 0, nullptr });
		break;
	case 7: // DownA
		UpBuf = Load.ToDouble();
		if (Neighbours[3] != nullptr)
			Neighbours[3]->ProgFU(DownA, Load);
		break;
	case 9: //Cof
		a = a + UpBuf * Load.ToDouble();
		if (Neighbours[0] != nullptr)
			Neighbours[0]->ProgFU(Cof, Load);
		break;
	case 11: // Zero
	{
		if (Neighbours[3] != nullptr)
			Neighbours[3]->ProgFU(Zero, Load);
		double t = -a / UpBuf;
		if (Neighbours[0] != nullptr)
			Neighbours[0]->ProgFU(Cof, { Cdouble, &t });
		break;
	}
	case 13: // SumToLeft
	{
		if (KeyF)
		{
			a = -Load.ToDouble() / a; // Вычисление корня
			;// Отсылка результата Менеджеру
			cout << a << endl;
			if (Neighbours[1] != nullptr)
				Neighbours[1]->ProgFU(Up, { Cdouble, &a });
		}
		else
		{
			double t = -a + Load.ToDouble();
			if (Neighbours[2] != nullptr)
				Neighbours[2]->ProgFU(SumToLeft, { Cdouble, &t });
		}
		break;
	}
	case 15: // 9.	SumToLeftUp
		if (Neighbours[2] != nullptr)
			Neighbours[2]->ProgFU(SumToLeft, { Cdouble, &a });
		if (Neighbours[1] != nullptr)
			Neighbours[1]->ProgFU(SumToLeftUp, { 0, nullptr });
		break;
	default:
		CommonMk(MK, Load);
		break;
	}
}

void Gauss::ProgFU(int MK, LoadPoint Load)
{
	switch (MK)
	{
	case 0: // Reset
		break;
	case 1: // ReadAndStart
	{
		ifstream f_in(Load.ToStr());
		int N;
		f_in >> N;
		Field.resize(N);
		for (auto &iu : Field)
		{
			iu.resize(N + 1);
			//iu[N].FreeF = true;
		}
		for (int i = 0; i < N; i++)
			for (int j = 0; j <= N; j++)
				f_in>>Field[i][j].a;
		// Прописать ссылки на соседей
		for (int i = 0; i < N; i++)
			for (int j = 0; j <= N; j++)
			{
				Field[i][j].Neighbours[0] = (j == N) ? nullptr : &Field[i][j + 1];
				Field[i][j].Neighbours[1] = (i == 0) ? nullptr : &Field[i-1][j];
				Field[i][j].Neighbours[2] = (j == 0) ? nullptr : &Field[i][j - 1];
				Field[i][j].Neighbours[3] = (i==N-1) ? nullptr : &Field[i+1][j];
				if (i == j)Field[i][j].KeyF = true;
			}
		Field[0][0].ProgFU(Key, {0 ,nullptr });
		break;
	}
	default:
		CommonMk(MK, Load);
		break;
	}
}

