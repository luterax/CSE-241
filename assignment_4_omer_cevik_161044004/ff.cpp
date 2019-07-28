#include <string>			/* We use strings.					*/
using namespace std;
#include "gates.h"			/* We use base class.				*/
#include "ff.h"				/* We use flipflop class.			*/

ff::ff():gates()			/* We create FLIPFLOP gate' names in constructor.		*/
{
	int FfCounter = 0, k = 0, t = 0, l = 0; 

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'F' )
		{
			++FfGateSize;
		}
	}

	FfName = new char**[FfGateSize];

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'F' )
		{
			FfName[k++] = new char*[2];
		}
	}

	k = 0;

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'F' )
		{
			for (int j = 9; j < getGate(i).length(); ++j)
			{
				if ( getGate(i)[j] != ' ' )
				{
					++FfCounter;
				}
				else
				{
					FfName[t][k++] = new char[FfCounter];
					FfCounter = 0;
				}
			}
			FfName[t++][k] = new char[FfCounter];
			k = 0;
			FfCounter = 0;
		}
	}

	k = 0;
	t = 0;

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'F' )
		{	
			for (int j = 9; j < getGate(i).length(); ++j)
			{
				if ( getGate(i)[j] != ' ' )
				{
					setFfName(l,k,t++,getGate(i)[j]);
				}
				else
				{
					setFfName(l,k++,t,'\0');
					t = 0;
				}
			}
			setFfName(l++,k,t,'\0');
			k = 0;
			t = 0;
		}
	}
}

ff::~ff()					/* We delete FLIPFLOP gate' names in destructor.		*/
{	
	for (int i = 0; i < FfGateSize; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			delete[] FfName[i][j];
		}
		delete[] FfName[i];
	}
	delete FfName;
}

void ff::evaluate(int inp1, int inp2)		/* We evaluate FLIPFLOP operation.		*/
{
	setOutput(( (!inp1) && getFormerOut() ) || (inp1) && (!getFormerOut()));
	setFormerOut(getOutput());
}