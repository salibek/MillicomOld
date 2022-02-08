#include "ConfineSimple.h"


void ConfineSimple::ProgFU(int MK, LoadPoint Load)
{
	switch (MK)
	{
	case 0: // Reset
		break;
	case 1: // iniSet
		ini = Load;
		break;
	case 20: //FpostSet
		Fpost = Load.ToBool();
		break;
		// è ò.ä.
	default:
		CommonMk(MK, Load);
		break;
	}
}