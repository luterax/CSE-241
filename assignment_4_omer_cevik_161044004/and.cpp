#include <string>			/* We use strings.					*/
using namespace std;
#include "gates.h"			/* We use base class.				*/
#include "and.h"			/* We use and class.				*/

And::And():gates()			/* We create AND gate' names in constructor.		*/
{
	int AndCounter = 0, k = 0, t = 0, l = 0; 

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'A' )
		{
			++AndGateSize;
		}
	}

	AndName = new char**[AndGateSize];

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'A' )
		{
			AndName[k++] = new char*[3];
		}
	}

	k = 0;

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'A' )
		{
			for (int j = 4; j < getGate(i).length(); ++j)
			{
				if ( getGate(i)[j] != ' ' )
				{
					++AndCounter;
				}
				else
				{
					AndName[t][k++] = new char[AndCounter];
					AndCounter = 0;
				}
			}
			AndName[t++][k] = new char[AndCounter];
			k = 0;
			AndCounter = 0;
		}
	}

	k = 0;
	t = 0;

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'A' )
		{	
			for (int j = 4; j < getGate(i).length(); ++j)
			{
				if ( getGate(i)[j] != ' ' )
				{
					setAndName(l,k,t++,getGate(i)[j]);
				}
				else
				{
					setAndName(l,k++,t,'\0');
					t = 0;
				}
			}
			setAndName(l++,k,t,'\0');
			k = 0;
			t = 0;
		}
	}
}

And::~And()					/* We delete AND gate' names in destructor.			*/
{	
	for (int i = 0; i < AndGateSize; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			delete[] AndName[i][j];
		}
		delete[] AndName[i];
	}
	delete AndName;
}

void And::evaluate(int inp1, int inp2)		/* We evaluate AND gate.		*/
{
	setOutput(inp1 && inp2);
}