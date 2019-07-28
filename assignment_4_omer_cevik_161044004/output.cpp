#include <string>					/* We use strings.					*/
using namespace std;
#include "gates.h"					/* We use base class.				*/
#include "output.h"					/* We use output class.				*/

output::output():gates()			/* We create OUTPUT gate' names in constructor.		*/
{
	int outputCounter = 0, k = 0, t = 0; 

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'O' && getGate(i)[1] == 'U' )
		{
			for (int j = 6; j < getGate(i).length(); ++j)
			{
				if ( getGate(i)[j] == ' ' )
				{
					++outputSize;
				}
			}
		}
	}
	
	outputName = new char*[outputSize];
	OutputResult = new int[outputSize];

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'O' && getGate(i)[1] == 'U' )
		{
			for (int j = 7; j < getGate(i).length(); ++j)
			{
				if ( getGate(i)[j] != ' ' )
				{
					++outputCounter;
				}
				else
				{
					outputName[k++] = new char[outputCounter];
					outputCounter = 0;
				}
			}
			outputName[k] = new char[outputCounter];
		}
	}

	k = 0;

	for (int i = 0; i < getGateSize(); ++i)
	{
		if ( getGate(i)[0] == 'O' && getGate(i)[1] == 'U' )
		{
			for (int j = 7; j < getGate(i).length(); ++j)
			{
				if ( getGate(i)[j] != ' ' )
				{
					setOutputName(k,t++,getGate(i)[j]);
				}
				else
				{
					setOutputName(k++,t,'\0');
					t = 0;
				}
			}
			setOutputName(k,t,'\0');
		}
	}
}

output::~output()					/* We delete OUTPUT gate' names in destructor.		*/
{
	for (int i = 0; i < outputSize; ++i)
	{
		delete[] outputName[i];
	}
	delete outputName;
}

void output::evaluate(int inp1, int inp2){}		/* We don't have evaluate operation.		*/