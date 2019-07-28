#include <fstream>
#include <iostream>
using namespace std;
#include "reader.h"
#include <sstream>

reader::reader()		/* Constructor reads text files.		*/
{
	ReadCommands("commands.txt");	/* Reads commands.		*/
	ReadFiles("files.txt");			/* Reads files.			*/
}

void reader::ReadCommands(const string fname)		/* It reads commands into 2D string array.	*/
{
	ifstream inputFile;
	string line;
	int i = 0, j = 0;

	inputFile.open(fname);

	while(1)
	{
		if ( inputFile.is_open() )
		{
			getline(inputFile,line);

			if ( check_errors(&inputFile) )
			{
				inputFile.close();
				inputFile.open(fname);
				break;
			}
			setCommandLineSize(getCommandLineSize()+1);
		}
	}
	
	CommandLine = new string*[getCommandLineSize()];
	CommandSize = new int[getCommandLineSize()];

	while(1)
	{
		if ( inputFile.is_open() )
		{
			getline(inputFile,line);

			if ( check_errors(&inputFile) )
			{
				inputFile.close();
				inputFile.open(fname);
				break;
			}
			
			for (int i = 0; i < line.length(); ++i)
			{
				if ( line[i] == ' ')
				{
					++j;
				}
			}
			CommandLine[i++] = new string[j+1];
		}
	}

	i = 0;

	while( i < getCommandLineSize() )
	{
		if ( inputFile.is_open() )
		{
			getline(inputFile,line);

			if ( check_errors(&inputFile) )
			{
				break;
			}

			string token;

			int j = 0;

			std::istringstream iss(line);

			while( getline(iss,token,' ') )
			{
				setCommandLine(i,j++,token);
			}
			setCommandSize(i++,j);
		}
	}

	inputFile.close();
}

void reader::ReadFiles(const string fname)		/* It reads files into 2D string array.		*/
{
	ifstream inputFile;
	string line;
	int i = 0, j = 0;

	inputFile.open(fname);

	while(1)
	{
		if ( inputFile.is_open() )
		{
			getline(inputFile,line);

			if ( check_errors(&inputFile) )
			{
				inputFile.close();
				inputFile.open(fname);
				break;
			}
			setFileLineSize(getFileLineSize()+1);
		}
	}
	
	FileLine = new string*[getFileLineSize()];
	FileNameSize = new int[getFileLineSize()];

	while(1)
	{
		if ( inputFile.is_open() )
		{
			getline(inputFile,line);

			if ( check_errors(&inputFile) )
			{
				inputFile.close();
				inputFile.open(fname);
				break;
			}
			
			for (int i = 0; i < line.length(); ++i)
			{
				if ( line[i] == '/')
				{
					++j;
				}
			}
			FileLine[i++] = new string[j+1];
		}
	}

	i = 0;

	while( i < getFileLineSize() )
	{
		if ( inputFile.is_open() )
		{
			getline(inputFile,line);

			if ( check_errors(&inputFile) )
			{
				break;
			}

			string token;

			int j = 0;

			std::istringstream iss(line);

			while( getline(iss,token,'/') )
			{
				setFileLine(i,j++,token);
			}
			setFileNameSize(i++,j);
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

reader::~reader()		/* Our destructor. 			*/
{
	for (int i = 0; i < getCommandLineSize(); ++i)
	{
		delete[] CommandLine[i]; 
	}
	delete[] CommandLine;

	for (int i = 0; i < getFileLineSize(); ++i)
	{
		delete[] FileLine[i];
	}
	delete[] FileLine;
}