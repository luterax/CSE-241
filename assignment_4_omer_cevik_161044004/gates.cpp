#include <fstream>			/* We use ifstream.			 */
using namespace std;		/* We use ifstream etc.		 */			
#include "gates.h"			/* We use base class.		 */

gates::gates()					/* Our constructor.			*/
{
	ReadCircuit("circuit.txt");	/* We read the circuit txt file.	*/
	ReadInput("input.txt");		/* We read the input txt file.		*/
}

void gates::ReadInput(const string filename)		/* It reads inputs into 2D int array.					*/
{
	ifstream inputFile;
	string line;
	int i = 0, j = 0, k = 0;

	inputFile.open(filename);

	while(1)
	{
		if ( inputFile.is_open() )
		{
			getline(inputFile,line);

			if ( check_errors(&inputFile) )
			{
				inputFile.close();
				inputFile.open(filename);
				break;
			}
			++inputCol;
		}
	}

	input = new int*[inputCol];

	for (int i = 0; i < inputCol; ++i)
	{
		input[i] = new int[inputSize];
	}

	while(j < inputCol)
	{
		if ( inputFile.is_open() )
		{
			getline(inputFile,line);

			if ( check_errors(&inputFile) )
			{
				break;
			}
			
			for (int i = 0; i < line.length(); ++i)
			{
				if ( line[i] != ' ' )
				{
					setInput(j,k++,line[i]-'0');
				}
			}
			k = 0;
			++j;
		}
	}
	
	inputFile.close();
}

void gates::ReadCircuit(const string filename)		/* It reads lines of circuit txt into string pointer.	*/
{
	ifstream inputFile;
	string line;
	int i = 0, j = 0, k = 0;

	inputFile.open(filename);

	while(1)
	{
		if ( inputFile.is_open() )
		{
			getline(inputFile,line);

			if ( check_errors(&inputFile) )
			{
				inputFile.close();
				inputFile.open(filename);
				i = 0;
				break;
			}
		
			if ( line[0] == 'I' )
			{
				i = 5;

				while( i < line.length() )
				{
					if ( line[i] == ' ' )
					{
						++inputGateSize;
					}
					++i;
				}

				inputSize = inputGateSize;
			}
			++GateSize;
		}
	}

	Gate = new string[GateSize];

	while( i < GateSize )
	{
		if ( inputFile.is_open() )
		{
			getline(inputFile,line);

			if ( check_errors(&inputFile) )
			{
				break;
			}

			setGate(i++,line);
		}
	}

	inputFile.close();
}

int check_errors(ifstream *f)						/* It checks if file openned or not.					*/
{
	int stop = 0;		/* It's our flag.							*/

	if( f->eof() )		/* It checks if it's in end of file.		*/
	{
		stop = 0;		/* Then we make it zero.					*/
	}
	if( f->fail() )		/* It checks if it failed.					*/
	{
		stop = 1;		/* Then we make it one.						*/
	}
	if( f->bad() )		/* It checks if it's bad.					*/
	{
		stop = 1;		/* Then we make it one.						*/
	}

	return stop;		/* We return our result.					*/
}

gates::~gates()				/* Our destructor.				*/
{
	delete[] Gate;							/* Deleting our Gate.		*/

	for (int i = 0; i < inputCol; ++i)		/* Making loop to delete inputs.		*/
	{
		delete[] input[i];					/* Delete the 2D inputs.				*/ 
	}
	
	delete[] input;							/* Delete the input pointer.			*/
}