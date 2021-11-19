// Подпрограммы инициализации ФУ
#include "stdafx.h"
#include "FUini.h"
#include "Consts.h"
#include "Bus.h"
#include "Console.h"
#include "StrGen.h"
#include "Lex.h"
#include "Find.h"
#include "List.h"
#include "GraphTransf.h"
#include "AluGeneral.h"
#include "InOut.h"
#include "Neuro.h"
#include "NetModeling.h"
#include "SchedulerEventser.h"
#include "MeanShift.h"
#include "Gauss.h"
#include "Bag.h"
#include "Gauss.h"

using namespace std;

FU *ConsIni(FU *Bus, FU *TEmpl)
{
 	return (FU*)new Console(Bus, TEmpl);
}

FU *BusIni(FU *BusContext, FU *TEmpl)
{
	return (FU*)new BusFU(BusContext, TEmpl);
}

FU *LexIni(FU *BusContext, FU *TEmpl)
{
	return (FU*)new Lex(BusContext, TEmpl);
}
FU *StrGenIni(FU *BusContext, FU *TEmpl)
{
	return (FU*)new StrGenContext(BusContext, TEmpl);
}

FU *FindIni(FU *BusContext, FU *TEmpl)
{
	return (FU*)new Find(BusContext, TEmpl);
}

FU *ListIni(FU *BusContext, FU *TEmpl)
{
	return (FU*)new List(BusContext, TEmpl);
}

FU* GraphTrasfIni(FU* BusContext, FU* TEmpl)
{
	return (FU*) new GraphTransf(BusContext, TEmpl);
}

FU* AluGeneralIni(FU* BusContext, FU* TEmpl)
{
	return (FU*) new ALUGeneral(BusContext, TEmpl);
}

FU* InOutIni(FU* BusContext, FU* TEmpl)
{
	return (FU*) new InOut(BusContext, TEmpl);
}

FU* AutomatManagerIni(FU* BusContext, FU* TEmpl)
{
	return (FU*) new AutomatManager(BusContext, TEmpl);
}

FU* NeuroIni(FU* BusContext, FU* TEmpl)
{
	return (FU*) new Neuro(BusContext, TEmpl);
}

FU* NetManagerIni(FU* BusContext, FU* TEmpl)
{
	return (FU*) new NetManager(BusContext, TEmpl);
//	return nullptr;
}

FU* SchedulerIni(FU* BusContext, FU* TEmpl)
{
	return (FU*) new Scheduler(BusContext, TEmpl);
}

FU* EventserIni(FU* BusContext, FU* TEmpl)
{
	return (FU*) new Eventser(BusContext, TEmpl);
}

FU* MeanShiftIni(FU* BusContext, FU* TEmpl)
{
	return (FU*) new MeanShift(BusContext, TEmpl);
}

FU* BagIni(FU* BusContext, FU* TEmpl)
{
	return (FU*) new Bag(BusContext, TEmpl);
}

FU* GaussIni(FU* BusContext, FU* TEmpl)
{
	return (FU*) new Gauss(BusContext, TEmpl);
}
