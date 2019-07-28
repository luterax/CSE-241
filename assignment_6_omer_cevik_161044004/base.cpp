#include <iostream>
#include <fstream>
#include "base.h"
using namespace std;

base::base()		/* Base constructor.		*/
{
	DataTextReader();				/* Reads dataType.		*/
	CommandsTextReader();			/* Reads all commands.	*/
}

void base::CommandsTextReader()				/* It just reads commands.txt file into a vector.	*/ 
{
	ifstream inputFile;

	inputFile.open("commands.txt");

	if ( !inputFile.is_open() )
	{
		throw "commands.txt file is not openned.";
	}
	else
	{
		string line;

		while( !inputFile.eof() )
		{
			getline(inputFile,line);

			if ( check_errors(&inputFile) )
			{
				inputFile.close();
				break;
			}
			CommandLine.push_back(line);
		}
	}
}

void base::DataTextReader()					/* It just reads data.txt file for dataType.		*/
{
	ifstream inputFile;

	inputFile.open("data.txt");

	if ( !inputFile.is_open() )
	{
		throw "data.txt file is not openned.";
	}
	else
	{
		string line;
		getline(inputFile,line);
		setDataType(line);
	}

	inputFile.close();
}

int check_errors(ifstream *f)				/* It checks if file openned or not.					*/
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