#pragma once
#include "Consts.h"
#include <vector>
#include <map>
#include <set>
#include <fstream>

class MeanShiftPoint : public FU {
public:
	void ProgFU(int MK, LoadPoint Load) override;
	int ID = 0; // Идентификатор ФУ-исполнителя
	int NDim = 2; // Количество изменений в фазовом пространстве
	MeanShiftPoint(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; };
	MeanShiftPoint() : FU() { Bus = nullptr; };
	vector<double> Coodinate; // координата точки в фазовом прострастве
	int NV; // Количество точек в множестве близлажищих точек?
	void* Manager = nullptr; // Указатель на менеджера
	vector<int> eps; // Изначальная ширина коридора для выбора точек во множество близлежащих точек
					 // В программе значение делится на 2, т.е. устанавливается диаметр, чтобы было удобнее работать в программе
	vector<int> eps_t; // Текущая ширина коридора для выбора точек во множество близлежащих точек
					 // В программе значение делится на 2, т.е. устанавливается диаметр, чтобы было удобнее работать в программе
	vector<MeanShiftPoint**>refXY; // Указатели на описание ссылки на ФУ в векторах упрорядоченных ссылок по осям
	set<MeanShiftPoint*> N; // Множество близлежащих точек
	vector<int> IdXY; // Индексы ФУ-исполнителя по всем осям координат
	double  dist(vector<double>& a, vector<double>& b); // Вычисление расстояния между двумя точками
private:
//	vector < vector<MeanShiftPoint*>>* VXY; // Указатели на точки, упорядоченные по координате X и Y
//											// Каждое изменение - это отдельная линия в векторе
//	vector<vector<MeanShiftPoint*>::iterator> vxy;  //указатели на описание ФУ в векторах VX, VY  
//													// Каждое изменение - это отдельная линия в векторе
	multimap <double,MeanShiftPoint*> Nd; // Множество близлежащих точек (атрибут - расстояние до точки)
	multimap <double, MeanShiftPoint*> N_Alph; // Близлежащие точки в сетке, упорядоченные по углу от текущей точки
	int Nneighbourhood = 14; // Величина окрестности (т.е. число точек, скоторыми данная точка связана)
	double Lmax = -1;
};

class MeanShifRegion : public FU { // Область для поиска максимума концентрации
public:
	void ProgFU(int MK, LoadPoint Load) override;
	void Migration(); // Поиск концентрации точек
	void* Manager = nullptr; // Указатель на менеджера
	vector<double> Center; // Координата центра кластера
	int ID = 0; // Идентификатор ФУ-региона
	int NDim = 2; // Количество изменений в фазовом пространстве
	int CenterPhase = 0; // Фаза записи стартовой точки для региона
	MeanShiftPoint* CenterFU = nullptr; // ФУ наиболее близкое к центру
	double R = 1; // Радиус региона
	void MoveToPoint(MeanShiftPoint* CenterStart); // Метод установки региона в стартовую позицию
	int MassCenter(vector<double>& CenterNew, MeanShiftPoint* Point, set<MeanShiftPoint*>& Pass); // Вычисление центра масс области (Возвращается количество точек)
	// на входе ссылка на ФУ для вычисления и вектор пройденных вершин
	vector<vector<double>> MigrationHistory; // История перемещения центра области (в историю попадают центры области на каждом шаге)
	double Eps = 0.0001; // Погрешность в вычислениях при миграции
};

class MeanShift : public FU {
public:
	vector <vector<MeanShiftPoint*>> VXY; // Указатели на точки, упорядоченные по координате X и Y и т.д.
											// Каждое изменение - это отдельная линия в векторе
	void ProgFU(int MK, LoadPoint Load) override;
	MeanShift(FU* BusContext, FU* Templ) : FU(BusContext) { ProbMaxMin = { {0,1},{0,1} }; eps = { 15,15 }; eps.resize(2);  Bus = BusContext; };
	MeanShift() : FU() { ProbMaxMin = { {0,1},{0,1} }; eps = { 16,16 }; Bus = nullptr; };
private:
	int NDim = 2; // Количество изменений в фазовом пространстве
	int NV=15; // Требуемое количество близлежащих точек для начала построения окрестной сетки вокруг узла
	vector<int> eps; // Количество анализируемых точек по осям
	vector<vector<double>> ProbMaxMin; // Максимальные и минимальные координаты по осям просотранства для генерации вычислительной сетки
	int NProb = 10; // Количество генерируемых случайных точек
	int ProbPhase = 0, EpsFaze=0; // Фаза считывания параметров для генерации множества случайных точек и фаза считывания необходимого количество точек по осей для построения вычислительной сетки

	void* NVPointErrProg = nullptr;  // Подпрограмма выдачи сообщения об ошибке при превышении количества точек 
								 //в системе над количеством требуемых точек для построения сетки 
	vector<MeanShifRegion> Regions; // Список регионов для поиска
	int RegionPhase = 0; // Фаза записи информации о региона (координаты и радиус)
	int RegionNetPhaze = 0; // Фаза записи информации о регионе
	vector<double> RegionNetParameters; // Параметры сетки регионов
	int RegionID = 0; // Индекс текущего региона
	double ClasterEps = 0.0001; // Погрешность в вычислениях при миграции
	void  NetGen(); // Генерация сетки
	void FileRead(LoadPoint Load); // Считывание точек пространства из файла
	void PointsGen(); // Генеация случайных точек пространства
	void Start(); // Запуск кластеризации
};