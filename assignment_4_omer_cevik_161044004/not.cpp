#include <string>			/* We use strings.					*/
using namespace std;
#include "gates.h"			/* We use base class.				*/
#include "not.h"			/* We use not class.				*/

Not::Not():gates()			/* We create NOT gate' names in constructor.		*/
{
	int NotCounter = 0, k = 0, t = 0, l = 0; 

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'N' )
		{
			++NotGateSize;
		}
	}

	NotName = new char**[NotGateSize];

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'N' )
		{
			NotName[k++] = new char*[2];
		}
	}

	k = 0;

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'N' )
		{
			for (int j = 4; j < getGate(i).length(); ++j)
			{
				if ( getGate(i)[j] != ' ' )
				{
					++NotCounter;
				}
				else
				{
					NotName[t][k++] = new char[NotCounter];
					NotCounter = 0;
				}
			}
			NotName[t++][k] = new char[NotCounter];
			k = 0;
			NotCounter = 0;
		}
	}

	k = 0;
	t = 0;

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'N' )
		{	
			for (int j = 4; j < getGate(i).length(); ++j)
			{
				if ( getGate(i)[j] != ' ' )
				{
					setNotName(l,k,t++,getGate(i)[j]);
				}
				else
				{
					setNotName(l,k++,t,'\0');
					t = 0;
				}
			}
			setNotName(l++,k,t,'\0');
			k = 0;
			t = 0;
		}
	}
}

Not::~Not()					/* We delete NOT gate' names in destructor.			*/
{	
	for (int i = 0; i < NotGateSize; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			delete[] NotName[i][j];
		}
		delete[] NotName[i];
	}
	delete NotName;
}

void Not::evaluate(int inp1, int inp2)		/* We evaluate NOT operation.	*/
{
	setOutput(!inp1);
}