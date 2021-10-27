#define _USE_MATH_DEFINES
#include "stdafx.h"
#include "MeanShift.h"
#include <string>
#include <fstream>
#include <set>
#include <algorithm>
#include <cmath>

double  MeanShiftPoint::dist(vector<double> &a, vector<double> &b) // Вычисление расстояния между двумя точками
{
	if (a.size() != b.size()) return -1; // Не совпадают размерности пространств для точек
	double D = 0;
	for (vector<double>::iterator ua = a.begin(), ub = b.begin(); ua != a.end(); ua++, ub++)
		D += (*ua - *ub) * (*ua - *ub);
}

void MeanShiftPoint::ProgFU(int MK, LoadPoint Load) // Поведение точки фазового пространства
{
	switch (MK)
	{
	case 100: // Gen
		// Подбор точек, находящихся в области вокруг данной точки
		vector<int>eps_t(eps); // Текущая ширина коридора для выбора точек во множество близлежащих точек
		N.clear();
		for (;;) // Пока не набирается нужное количество близлежащих точек
		{
			MeanShift* MANAGER = (MeanShift*)Manager;
		//	for (vector<MeanShiftPoint>::iterator uFU = (eps_t[0] < IdXY[0] ? (&Manager->VXY[IdXY[0]] - eps_t[0])) : &Manager->VXY[IdXY[0]];
			for (auto uFU = MANAGER->VXY[0].begin() + ((eps_t[0] > Coodinate[0]) ? 0 : Coodinate[0] - eps_t[0]);
				uFU != MANAGER->VXY[0].end() && distance(MANAGER->VXY[0].begin(), uFU) <= Coodinate[0] + eps_t[0]; uFU++)
			{
				if ((*uFU)->ID==ID) continue; // Пропускаем данное ФУ
				int i_dim;
				for (i_dim = 0; i_dim < NDim && \
						(*uFU)->IdXY[i_dim]<=IdXY[i_dim]+eps_t[i_dim] &&\
						(*uFU)->IdXY[i_dim] >= IdXY[i_dim] - eps_t[i_dim]; i_dim++);
				if (i_dim == NDim) // Если добрались до конца вектора
					N.push_back(*uFU); // Формирование множества близлежащих точек N
			}

			if (N.size() >= NV)
				break;
			// Еще одна итерация с расширенными в 2 раза границами
			for (auto& i : eps_t)
					i += i;
			N.clear();
			//break; // Заглушка!!!!
		}
		// Генерация окрестной сетки
		multimap<double, MeanShiftPoint*> Distance; // Список близлежащих вершин, упорядоченных по расстоянию от точки
		multimap<double, MeanShiftPoint*> Angle; // Новый список близлежащих вершин, упорядоченных по углу
		for (auto i : N)
			Distance.insert({ dist(this->Coodinate,i->Coodinate),i });// Список ФУ по расстояниям
//		cout << this->Coodinate[0] << " " << this->Coodinate[1] << endl;
//		for (auto i : Distance)
//			cout << i.first << " " << i.second->Coodinate[0]<<" "<< i.second->Coodinate[1] << endl;
//		cout << "-----\n";

		for (auto &k:Distance)
		{		
			Angle.insert(pair<double, MeanShiftPoint*>
				(atan2(k.second->Coodinate[0] - Coodinate[0],
				k.second->Coodinate[1] - Coodinate[1]),k.second)); // Дабавление элементов
			if (Angle.size() < 3)continue;
			auto i = Angle.begin();
			auto st = Angle.begin();
			auto fin = Angle.begin();
			for (; i->second != k.second; i++);
			if (i == Angle.begin()) //Если точка в начале списка по углам
			{
				fin = (--Angle.end());
				st = i; st++;
			}
			else if (i == --Angle.end()) // Если точка в конце списка по углам
			{
				fin = Angle.begin();
				st = i; st--;
			}
			else
			{
				st = fin = i;
				st--;
				fin++;
			}
			double dSt = (abs(i->first - st->first)) <= M_PI ? abs(i->first - st->first):abs(i->first + st->first);
			double dFin = (abs(i->first - fin->first)) <= M_PI ? abs(i->first - fin->first) : abs(i->first + fin->first);
			double dStFin = (abs(st->first - fin->first)) <= M_PI ? abs(st->first - fin->first) : abs(st->first + fin->first);
			
			if (dSt + dFin == dStFin && // Если точка находится в остром угле между двумя соседними точками
				k.first > dist(st->second->Coodinate, fin->second->Coodinate))// Расстояние между соседними точками меньше расстояния от данной точки до текущей точки
				Angle.erase(i); // Удалить текущую точку из списка близлежащих точек, т.к. она не образует близлажщую сетку
		}
		// Запись в контекст ФУ-исполнителя списка на близлежащие вершины списка
		N.clear();
		for (auto i : Angle)
			N.push_back(i.second);
	}
}

void MeanShift::ProgFU(int MK, LoadPoint Load) // Поведение ФУ MeanShift
{
	switch (MK)
	{
	case 0: // Reset
		break;
	case 3: // NDimSet Установить количество измерений фазового пространства
		NDim = Load.ToInt();
		EpsFaze = 0; // Сброс фазы считывания eps
		eps.resize(NDim);
		ProbMaxMin.resize(NDim);
		for (auto& i : ProbMaxMin)
			i.resize(2);
		break;
	case 5: // Start
		//...
		if ((Load.Type >> 1) == Dstring)
			FileRead(Load);
		NetGen();
		break;
	case 8: // NVSet Установить требуемое количество близлежащих точек для начала построения окрестной сетки вокруг узла
		NV = Load.ToInt();
		break;
	case 15: // PointsGen Генерация случайных точек (праметр: макс и мин координаты по осям и количество генерируемых точек)
	case 16: // PointsGenStart Генерация случайных точек (праметры: верхний левый угол поля, правый нижний угол поля, количество точек)
		if (ProbFaze < NDim + NDim)
			ProbMaxMin[ProbFaze / 2][ProbFaze % 2] = Load.ToDouble();
		else
		{
			NProb = Load.ToInt();
			PointsGen(); // Генерация точек поля
			NetGen(); // Генерация сетки
			if (MK == 16)
				Start(); // Запуск кластеризации
			ProbFaze = -1; // Сброс фазы МК в нуль через строку ProbFaze++
		}
		ProbFaze++;
		break;
	case 20: // PointsOutMk Выдать точки фазового пространства
	{
		
		for (auto& i : VXY[0])
		{
			MkExec(Load, { CdoubleArray,&i->Coodinate });
		}
		break;
	}
	case 30: //ArcsOutMk Выдать список дуг
	{
		set<pair< MeanShiftPoint*, MeanShiftPoint*> >ArksOut;// Список координат
		for (auto& i : VXY[0])
		{
			pair<MeanShiftPoint*, MeanShiftPoint*> p;
			for (auto j : i->N) {
				if (i->ID < j->ID)
				{
					p.first = i; p.second = j;
				}
				else
				{
					p.first = j; p.second = i;
				}
				ArksOut.insert(p);
			}
		}
		
		for (auto &i : ArksOut)
		{
			MkExec(Load, { CdoubleArray, &i.first->Coodinate });
			MkExec(Load, { CdoubleArray, &i.second->Coodinate });
		}
		break;
	}
	case 40: // NVPointErrProgSet Установить программу реакции на событие превышения количества требуемых для окрестности точек над количеством точек в системе
		NVPointErrProg = Load.Point;
		break;
	case 51: // epsSet Установить количество анализируемых точек по оси (по умолчанию 20)
		eps[EpsFaze] = Load.ToInt(20)/2;
		EpsFaze = (EpsFaze + 1) % NDim;
		break;
	case 52: // epsAllSet Установить одинаковое количество анализируемых точек для всех осей (по умолчанию 20)
	{	int t = Load.ToInt(20) / 2;
		for (auto& i : eps)
			i = t;
		break;
	}
	default:
		CommonMk(MK, Load);
		break;
	}
}

void MeanShift::Start() // Запуск кластеризации
{
}

void MeanShift::PointsGen()
{
	for (auto& i : VXY) // Очистка предыдувщего поля
	{
		for (auto& j : i)
			delete j;
	}
	VXY.clear();
	VXY.resize(NDim);
	for (int i = 0; i < NProb; i++)
	{
		MeanShiftPoint* t = new MeanShiftPoint;
		t->Coodinate.resize(NDim);
		t->Manager = this;
		t->eps = eps;
		t->NV = NV;
		t->ID = i; // Установить индетификатор ФУ-исполнителя
		for (auto& l : t->Coodinate) // Генерация точек
			l = (double) rand() / RAND_MAX * (ProbMaxMin[l][1] - ProbMaxMin[l][0]) + ProbMaxMin[l][0];
		for (auto& k : VXY)
			k.push_back(t); // Запись указателей на исполнительные ФУ в вектора всех изменений
	}
	// Упорядочивание точек по каждой из координат
	int i = 0;
	for (auto& k : VXY)
	{
		sort(k.begin(), k.end(), [i](MeanShiftPoint* a, MeanShiftPoint* b) {return a->Coodinate[i] < b->Coodinate[i]; });
		i++;
	}
	// Расстановка ссылок в точках на их описание в VX,VY
	for (auto& k : VXY) {// Перебор всех точек
		for (auto& uFU : k)
		{
			int i = 0;
			uFU->refXY.push_back(&uFU);
			uFU->IdXY.push_back(i); // Запись индекса ФУ по каждому измерению
			i++;
		}
	}

}

void MeanShift::FileRead(LoadPoint Load)
{
/*	ifstream f; // файл для считывания исходных данных
	string FName;
	ifstream fin;
	f.open(Load.ToStr());
	if (!f) return;
	vector<pair<double, MeanShiftPoint*>> VXt, VYt;
	while (!f.eof())
	{
		double x, y;
		f >> x >> y;
		MeanShiftPoint* MP = new MeanShiftPoint();
		VXt.push_back({ x, MP });
		VYt.push_back({ y, MP });
		MP->epsX = epsX;
		MP->epsY = epsY;
		MP->NV = NV;
		MP->Manager = this;
		MP->Coodinate.push_back(x);
		MP->Coodinate.push_back(y);
		MP->VX = &VX; // Ссылка на список упорядоченных вершин по координате X
		MP->VY = &VY; // Ссылка на список упорядоченных вершин по координате Y
	}
	// Упорядочивание векторов VXt, VYt
	sort(VXt.begin(), VXt.end());
	sort(VYt.begin(), VYt.end());
	// Формирование векторов VX, VY
	for (auto uk = VXt.begin(); uk != VXt.end(); uk++)
		VX.push_back(uk->second);
	for (auto uk = VYt.begin(); uk != VYt.end(); uk++)
		VY.push_back(uk->second);
*/
}

void  MeanShift::NetGen() // Генерация сетки
{
	// Непосредственно генерация сетки
	// Определение множества близлежащих точек для построения сетки (множество N)
	if (NV > VXY[0].size()) // Если количество точек в системе меньше,
	{						// чем требуемое для окрестности, то построение сетки прерывается
		ProgExec(NVPointErrProg); // Вызов подрограммы сообщения об ошибке
		return;
	}
	for (auto FUuk : VXY[0])
	{
		FUuk->ProgFU(100, {0,nullptr});// Милликоманда генерации близлежащей сетки
	}

}
