#pragma once
#include "Consts.h"
#include <vector>
#include <map>
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
	vector<MeanShiftPoint*> N; // Множество близлежащих точек
	vector<int> IdXY; // Индексы ФУ-исполнителя по всем осям координат
private:
//	vector < vector<MeanShiftPoint*>>* VXY; // Указатели на точки, упорядоченные по координате X и Y
//											// Каждое изменение - это отдельная линия в векторе
//	vector<vector<MeanShiftPoint*>::iterator> vxy;  //указатели на описание ФУ в векторах VX, VY  
//													// Каждое изменение - это отдельная линия в векторе
	multimap <double,MeanShiftPoint*> Nd; // Множество близлежащих точек (атрибут - расстояние до точки)
	multimap <double, MeanShiftPoint*> N_Alph; // Близлежащие точки в сетке, упорядоченные по углу от текущей точки
	double Lmax = -1;
	double  dist(vector<double>& a, vector<double>& b); // Вычисление расстояния между двумя точками
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
	int ProbFaze = 0, EpsFaze=0; // Фаза считывания параметров для генерации множества случайных точек и фаза считывания необходимого количество точек по осей для построения вычислительной сетки

//	vector<vector<MeanShiftPoint*>::iterator> vxy;  //указатели на описание ФУ в векторах VX, VY
													// Каждое изменение - это отдельная линия в векторе

	void* NVPointErrProg = nullptr;  // Подпрограмма выдачи сообщения об ошибке при превышении количества точек 
								 //в системе над количеством требуемых точек для построения сетки 
	void  NetGen(); // Генерация сетки
	void FileRead(LoadPoint Load); // Считывание точек пространства из файла
	void PointsGen(); // Генеация случайных точек пространства
	void Start(); // Запуск кластеризации
};