// ������ ���������� ����� ������� �������
#include "stdafx.h"
#include "IndFileConvertOld.h"
#include "consts.h"
#include <map>
#include <vector>
#include <array>
#include <string>
#include <string.h>
#include <fstream>
#include <algorithm>

using namespace std;

int i;

vector<vector<void*>> BackRec; // ������ ������� ��� �������� ������ ������
vector<int> BackRecInd; // ������ �������� ��� �������� ������ ������

void ConvIndStrOld(string str, ip &IP, vector<ip*> IpUk, map<int, vector<ip>*> &CapsId, int Count) // ���������� ����� ��������� ��
{
	IP.atr = atoi(str.substr(0, str.find(' ')).c_str());
	str = str.substr(str.find(' ') + 1, string::npos);
	char DataType = str[0];
	str = str.substr(2, string::npos);

	if (DataType != 'S' && DataType != 'C')
	{
		int DInd = atoi(str.substr(str.find(' ') + 1, str.find(' ', str.find(' ') + 1)).c_str());// ������ ��� ���������
		if (DInd != (Count << 2) + 2)
		{
			switch (DInd % 4)
			{
			case 0:// ��������� �� ��
				if (CapsId.count(DInd >> 2) == 0)
				{
					IP.Load.Point = IpUk[DInd >> 2];
					IP.Load.Type = TIP;
				}
				else
				{
					IP.Load.Point = CapsId[DInd >> 2];
					IP.Load.Type = TIC;
				}
				break;
			case 1:// ��������� �� �������
				IP.Load.Point = &(IpUk[DInd >> 2]->atr);
				IP.Load.Type = Tint;
				break;
			case 2:// ��������� �� ������
				IP.Load.Point = IpUk[DInd >> 2]->Load.Point;
				IP.Load.Type = IpUk[DInd >> 2]->Load.Type;
				break;
			case 3:// ��������� �� ��������� �� ��
				IP.Load.Point = &(IpUk[DInd >> 2]->Load.Point);
				IP.Load.Type = Tvoid;
				break;
			}
			return;
		}
	}
	string *Strdat;
	int *intVar;
	double *doubleVar;
	float *floatVar;
	char *charVar;
	bool *boolVar;
	switch (DataType)
	{
	case 'S':
	case 'C':
		Strdat = new string(str.substr(0, str.rfind('"')));
		str = str.substr(str.rfind('"') + 1, string::npos);
		IP.Load.Point = Strdat;
		IP.Load.Type = Cstring;
		break;
	case 'I':
		intVar = new int;
		*intVar = atoi(str.substr(0, str.find(' ')).c_str());
		IP.Load.Point = intVar;
		IP.Load.Type = Cint;
		break;
		//		case 'C':
		//			charVar = new char;
		//			*charVar = str[2];
		//			IP.Load.Point = charVar;
		//			IP.Load.Type = Cchar;
		//			break;
	case 'B':
		boolVar = new bool;
		*boolVar = str[2] ? true : false;
		IP.Load.Point = boolVar;
		IP.Load.Type = Cbool;
		break;
	case 'F':
	case 'D':
	{
		doubleVar = new double;
		string buf = str.substr(0, str.find(' '));
		if (buf.find(',') < buf.length())
			buf[buf.find(',')] = '.';
		*doubleVar = atof(buf.c_str());
		IP.Load.Point = doubleVar;
		IP.Load.Type = Cdouble;
		break;
	}
//	case 'F':
//		floatVar = new float;
//		*floatVar = atof(str.substr(0, str.find(' ')).c_str());
//		IP.Load.Point = floatVar;
//		IP.Load.Type = Cfloat;
//		break;
	}
}

ICVect* ConvIndOld(string FileName)
{
	ICVect *ipVect = new ICVect;
	ifstream in(FileName);
	map<int, vector<ip>* > CapsId; // ������ ��, � ������� ���������� ��
	if (!in) return ipVect;
	int N;
	in >> N;
	vector<ip*> IpUk; // ��������� �� ��
	vector<ip*>::iterator IpUkIterat;
	IpUk.resize(N);
	string str;// ������� �������� ������ �� �����

			   // ������������ ������� ��-����� (��������� ������ ��� ��)
	int Count = 0; // ������� ���������� �� � �������
	vector<int> LIC; // ����� ������ �� ��-�����
	vector<int> NIC; // ������� ������ ������ �� ��-�����
	int LIC_Current = 0; // �������� ����� ���� ������ ��-�����
	map <int, int> LIC_Ind; // ������, � �������� ������������ ������� ��-�����
	LIC.push_back(0);
	NIC.push_back(0);
	LIC_Ind[N + 3] = 0;
	getline(in, str);
	for (int i = 0; i < N; i++)
	{
		getline(in, str);
		str = str.substr(0, str.rfind(' '));

		LIC[LIC_Current]++;
		if (str.substr(str.rfind(' ') + 1, string::npos) == "-1") // ����� ��?
			if (LIC_Ind.begin()->first == i + 1)
			{ // ����� ������� ��
				LIC_Current = LIC_Ind.begin()->second;
				LIC_Ind.erase(LIC_Ind.begin()->first);
			}
			else
			{
				//				if (i < N - 1)
				{// ����� ��
					LIC_Current = LIC.size();
					LIC.push_back(0);
					NIC.push_back(i + 1);
				}
			}
		else if (atoi(str.substr(str.rfind(' ') + 1, string::npos).c_str()) >> 2 != i + 1) // ������ ��?
			if (LIC_Ind.begin()->first == i + 1)
			{ // ����� ������� ��
				int t = LIC_Current;
				LIC_Current = LIC_Ind.begin()->second;
				LIC_Ind.erase(LIC_Ind.begin()->first);
				LIC_Ind[atoi(str.substr(str.rfind(' ') + 1, string::npos).c_str()) >> 2] = t;
			}
			else
			{
				LIC_Ind[atoi(str.substr(str.rfind(' ') + 1, string::npos).c_str()) >> 2] = LIC_Current; // ������, � �������� ������������ ������� ��-�����
				LIC_Current = LIC.size();
				LIC.push_back(0);
				NIC.push_back(i + 1);
			}
	}
	LIC.pop_back();
	NIC.pop_back();
	ipVect->resize(LIC.size());

	for (int i = 0; i < NIC.size(); i++)// ������������ ������� ���������������� ��
										// � ������ ��
	{
		(*ipVect)[i] = new vector<ip>();
		(*ipVect)[i]->resize(LIC[i]);
		CapsId[NIC[i]] = (ipVect->at(i));
	}
	// ������������ ������ ������� �� ��
	LIC_Current = 0;
	LIC.clear();  LIC.push_back(0);
	//	NIC.clear();  NIC.push_back(0);
	LIC_Ind.clear();
	LIC_Ind[N + 3] = 0;

	in.seekg(0, ios::beg); // ������� � ������ �����
	getline(in, str);
	int ICNUM = 0, IPNUM = 0; // ������� ����� ��
	int IC_Count = 0;
	auto _IpUk = IpUk.begin();
	for (int i = 0; i < N; i++)
	{
		getline(in, str);
		str = str.substr(0, str.rfind(' '));
		*_IpUk = &(*ipVect->at(LIC_Current))[LIC[LIC_Current]];
		LIC[LIC_Current]++;
		if (str.substr(str.rfind(' ') + 1, string::npos) == "-1") // ����� ��?
			if (LIC_Ind.begin()->first == i + 1)
			{ // ����� ������� ��
				LIC_Current = LIC_Ind.begin()->second;
				LIC_Ind.erase(LIC_Ind.begin()->first);
			}
			else
			{
				//				if (i < N - 1)
				{// ����� ��
					LIC_Current = LIC.size();
					LIC.push_back(0);
					//					NIC.push_back(i + 1);
				}
			}
		else if (atoi(str.substr(str.rfind(' ') + 1, string::npos).c_str()) >> 2 != i + 1) // ������ ��?
			if (LIC_Ind.begin()->first == i + 1)
			{ // ����� ������� ��
				int t = LIC_Current;
				LIC_Current = LIC_Ind.begin()->second;
				LIC_Ind.erase(LIC_Ind.begin()->first);
				LIC_Ind[atoi(str.substr(str.rfind(' ') + 1, string::npos).c_str()) >> 2] = t;
			}
			else
			{
				LIC_Ind[atoi(str.substr(str.rfind(' ') + 1, string::npos).c_str()) >> 2] = LIC_Current; // ������, � �������� ������������ ������� ��-�����
				LIC_Current = LIC.size();
				LIC.push_back(0);
				//				NIC.push_back(i + 1);
			}
		_IpUk++;
	}
	LIC.pop_back();
	//	NIC.pop_back();
	ipVect->resize(LIC.size());

	in.seekg(0, ios::beg); // ������� � ������ �����
	getline(in, str);
	int t = 0;
	for (auto &i : IpUk)
	{
		getline(in, str);
		ConvIndStrOld(str, *i, IpUk, CapsId, t++);
	}

	IpUk.clear();
	NIC.clear();
	LIC.clear();

	in.close();
	return ipVect;
}