#include <string>					/* We use strings.					*/
using namespace std;
#include "gates.h"					/* We use base class.				*/
#include "decoder.h"				/* We use decoder class.			*/

decoder::decoder():gates()			/* We create DECODER gate' names in constructor.		*/
{
	int DecCounter = 0, k = 0, t = 0, l = 0; 

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'D' )
		{
			++DecGateSize;
		}
	}

	DecName = new char**[DecGateSize];

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'D' )
		{
			DecName[k++] = new char*[6];
		}
	}

	k = 0;

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'D' )
		{
			for (int j = 8; j < getGate(i).length(); ++j)
			{
				if ( getGate(i)[j] != ' ' )
				{
					++DecCounter;
				}
				else
				{
					DecName[t][k++] = new char[DecCounter];
					DecCounter = 0;
				}
			}
			DecName[t++][k] = new char[DecCounter];
			k = 0;
			DecCounter = 0;
		}
	}

	k = 0;
	t = 0;

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'D' )
		{	
			for (int j = 8; j < getGate(i).length(); ++j)
			{
				if ( getGate(i)[j] != ' ' )
				{
					setDecName(l,k,t++,getGate(i)[j]);
				}
				else
				{
					setDecName(l,k++,t,'\0');
					t = 0;
				}
			}
			setDecName(l++,k,t,'\0');
			k = 0;
			t = 0;
		}
	}
}

decoder::~decoder()					/* We delete DECODER gate' names in destructor.			*/
{	
	for (int i = 0; i < DecGateSize; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			delete[] DecName[i][j];
		}
		delete[] DecName[i];
	}
	delete DecName;
}

void decoder::evaluate(int inp1, int inp2)	/* We evaluate DECODER operation.				*/
{
	if ( inp1 == 0 && inp2 == 0 )
	{
		setDec1(1);
		setDec2(0);
		setDec3(0);
		setDec4(0);
	}
	else if ( inp1 == 0 && inp2 == 1 )
	{
		setDec1(0);
		setDec2(1);
		setDec3(0);
		setDec4(0);
	}
	else if ( inp1 == 0 && inp2 == 1 )
	{
		setDec1(0);
		setDec2(0);
		setDec3(1);
		setDec4(0);
	}
	else
	{
		setDec1(0);
		setDec2(0);
		setDec3(0);
		setDec4(1);
	}
}