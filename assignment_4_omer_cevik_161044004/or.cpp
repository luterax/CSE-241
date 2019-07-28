#include <string>			/* We use strings.					*/
using namespace std;
#include "gates.h"			/* We use base class.				*/
#include "or.h"				/* We use or class.					*/

Or::Or():gates()			/* We create OR gate' names in constructor.		*/
{
	int OrCounter = 0, k = 0, t = 0, l = 0; 

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'O' && getGate(i)[1] == 'R' )
		{
			++OrGateSize;
		}
	}

	OrName = new char**[OrGateSize];

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'O' && getGate(i)[1] == 'R' )
		{
			OrName[k++] = new char*[3];
		}
	}

	k = 0;

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'O' && getGate(i)[1] == 'R' )
		{
			for (int j = 3; j < getGate(i).length(); ++j)
			{
				if ( getGate(i)[j] != ' ' )
				{
					++OrCounter;
				}
				else
				{
					OrName[t][k++] = new char[OrCounter];
					OrCounter = 0;
				}
			}
			OrName[t++][k] = new char[OrCounter];
			k = 0;
			OrCounter = 0;
		}
	}

	k = 0;
	t = 0;

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'O' && getGate(i)[1] == 'R' )
		{	
			for (int j = 3; j < getGate(i).length(); ++j)
			{
				if ( getGate(i)[j] != ' ' )
				{
					setOrName(l,k,t++,getGate(i)[j]);
				}
				else
				{
					setOrName(l,k++,t,'\0');
					t = 0;
				}
			}
			setOrName(l++,k,t,'\0');
			k = 0;
			t = 0;
		}
	}
}

Or::~Or()					/* We delete OR gate' names in destructor.			*/
{	
	for (int i = 0; i < OrGateSize; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			delete[] OrName[i][j];
		}
		delete[] OrName[i];
	}
	delete OrName;
}

void Or::evaluate(int inp1, int inp2)	/* We evaluate OR operation.		*/
{
	setOutput((inp1 || inp2));
}