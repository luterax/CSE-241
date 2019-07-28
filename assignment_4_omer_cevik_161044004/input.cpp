#include <string>			/* We use strings.					*/
using namespace std;
#include "gates.h"			/* We use base class.				*/
#include "input.h"			/* We use input class.				*/

input::input():gates()		/* We create INPUT gate' names in constructor.		*/
{
	int inputCounter = 0, k = 0, t = 0; 
	inputName = new char*[getInputSize()];

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'I' )
		{
			for (int j = 6; j < getGate(i).length(); ++j)
			{
				if ( getGate(i)[j] != ' ' )
				{
					++inputCounter;
				}
				else
				{
					inputName[k++] = new char[inputCounter];
					inputCounter = 0;
				}
			}
			inputName[k] = new char[inputCounter];
		}
	}

	k = 0;

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'I' )
		{
			for (int j = 6; j < getGate(i).length(); ++j)
			{
				if ( getGate(i)[j] != ' ' )
				{
					setInputName(k,t++,getGate(i)[j]);
				}
				else
				{
					setInputName(k++,t,'\0');
					t = 0;
				}
			}
			setInputName(k,t,'\0');
		}
	}
}

input::~input()				/* We delete INPUT gate' names in destructor.			*/
{
	for (int i = 0; i < getInputSize(); ++i)
	{
		delete[] inputName[i];
	}
	delete inputName;
}

void input::evaluate(int inp1, int inp2){}	/* We don't evaluate anything.		*/