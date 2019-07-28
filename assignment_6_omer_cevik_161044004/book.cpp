#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;
#include "base.h"
#include "book.h"

book::book() : base()		/* Our book constructor. We do everything in here. 	*/
{
	CreatePartialEntries();		/* Creates data.txt parts.		*/
	ErrorPrinter();				/* Prints errors.				*/
	ApplyCommands();			/* Applies commands.			*/
}

void book::ErrorPrinter()			/* It checks and prints errors. */
{
	int uniqueCounter = 0, maximumSize = 0, yearCount = 0, titleCount = 0, authorsCount = 0, tagsCount = 0;
	ofstream outFile;
	outFile.open("output.txt", ios::out );

	if ( !outFile.is_open() )
	{
		throw "output.txt file is not openned.";
	}

	outFile << "Catalog Read: book" << endl;

	maximumSize = max({ title.size(),authors.size(),year.size(),tags.size() });

	if ( title.size() < maximumSize )
	{
		title.push_back("");
		++titleCount;
	}
	if ( authors.size() < maximumSize )
	{
		authors.push_back("");
		++authorsCount;
	}
	if ( year.size() < maximumSize )
	{
		year.push_back("");
		++yearCount;
	}
	if ( tags.size() < maximumSize )
	{
		tags.push_back("");
		++tagsCount;
	}

	bool f1,f2,f3,f4;
	f1 = f2 = f3 = f4 = true;

	for (int i = 0; i < maximumSize; ++i)
	{
		if ( ( title[i] == "" || authors[i] == "" || year[i] == "" || tags[i] == "" ) )
		{
			if ( title[i] == "" && titleCount == 0 && f1 )
			{
				outFile << "Exception: duplicate entry" << endl;
				outFile << "\"" << title[i] << "\" \"" <<  authors[i] << "\" \"" << year[i] << "\" \"" << tags[i] << "\"" << endl;
				f1 = false;
				++uniqueCounter;
			}
			else if ( authors[i] == "" && authorsCount == 0 && f2 )
			{
				outFile << "Exception: duplicate entry" << endl;
				outFile << "\"" << title[i] << "\" \"" <<  authors[i] << "\" \"" << year[i] << "\" \"" << tags[i] << "\"" << endl;
				f2 = false;
				++uniqueCounter;
			}
			else if ( year[i] == "" && yearCount == 0 && f3 )
			{
				outFile << "Exception: duplicate entry" << endl;
				outFile << "\"" << title[i] << "\" \"" <<  authors[i] << "\" \"" << year[i] << "\" \"" << tags[i] << "\"" << endl;
				f3 = false;
				++uniqueCounter;
			}
			else if ( tags[i] == "" && tagsCount == 0 && f4 )
			{
				outFile << "Exception: duplicate entry" << endl;
				outFile << "\"" << title[i] << "\" \"" <<  authors[i] << "\" \"" << year[i] << "\" \"" << tags[i] << "\"" << endl;
				f4 = false;
				++uniqueCounter;
			}
		}
	}

	if ( titleCount == 1 )
	{
		++uniqueCounter;
		outFile << "Exception: missing field" << endl;
		for (int i = 0; i < title.size(); ++i)
		{
			if ( title[i] == "" )
			{
				outFile << "\"" <<  authors[i] << "\" \"" << year[i] << "\" \"" << tags[i] << "\"" << endl;
			}
		}
	}
	else if ( authorsCount == 1 )
	{
		++uniqueCounter;
		outFile << "Exception: missing field" << endl;
		for (int i = 0; i < authors.size(); ++i)
		{
			if ( authors[i] == "" )
			{
				outFile << "\"" << title[i] << "\" \"" << year[i] << "\" \"" << tags[i] << "\"" << endl;
			}
		}
	}
	else if ( yearCount == 1 )
	{
		++uniqueCounter;
		outFile << "Exception: missing field" << endl;
		for (int i = 0; i < year.size(); ++i)
		{
			if ( year[i] == "" )
			{
				outFile << "\"" << title[i] << "\" \"" <<  authors[i] << "\" \"" << tags[i] << "\"" << endl;
			}
		}
	}
	else if ( tagsCount == 1 )
	{
		++uniqueCounter;
		outFile << "Exception: missing field" << endl;
		for (int i = 0; i < tags.size(); ++i)
		{
			if (  tags[i] == "" )
			{
				outFile << "\"" << title[i] << "\" \"" <<  authors[i] << "\" \"" << year[i] << "\"" << endl;
			}
		}
	}

	outFile << uniqueCounter << " unique entries" << endl;

	outFile.close();
}

void book::ApplyCommands()			/* It applies commands. If command is sort then it sorts, if command is search then searches and prints to output.txt.	*/
{
	ofstream outFile;

	outFile.open("output.txt", ios_base::app );

	if ( !outFile.is_open() )
	{
		throw "output.txt file is not openned."; 
	}

	for (int K = 0; K < getCommandVector().size(); ++K)
	{
		outFile << getCommandLine(K) << endl;
		istringstream iss(getCommandLine(K));
		string token;
		getline(iss,token,' ');

		if ( token == "sort" )				/* It sorts. 		*/
		{
			getline(iss,token,' ');
			
			istringstream iss2(token);
			string Entry;
			getline(iss2,Entry,'"');
			getline(iss2,Entry,'"');

			if ( Entry == "year" )
			{
				if ( year.size() == title.size() && year.size() == authors.size() && year.size() == tags.size() )
				{
					int min,StringToInt1,StringToInt2;
					string temp,temp1,temp2,temp3;

					for (int i = 0; i < year.size(); i++)
					{
						min = i;
						for (int j = i+1; j < year.size(); ++j)
						{
							sscanf(year[j].c_str(),"%d",&StringToInt1);
							sscanf(year[min].c_str(),"%d",&StringToInt2);
							if ( StringToInt1 < StringToInt2 )
							{
								min = j;
							}
						}

						temp = year[min];
						temp1 = title[min];
						temp2 = authors[min];
						temp3 = tags[min];
						year[min] = year[i];
						title[min] = title[i];
						authors[min] = authors[i];
						tags[min] = tags[i];
						year[i] = temp;
						title[i] = temp1;
						authors[i] = temp2;
						tags[i] = temp3;
					}

					for (int i = 0; i < year.size(); ++i)
					{
						if ( year[i] != "" && title[i] != "" && authors[i] != "" && tags[i] != "" )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << authors[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << tags[i] << "\"" << endl;
						}
					}
				}
				else
				{
					outFile << "Exception: missing field" << endl;
				}
			}
			else if ( Entry == "title" )
			{
				if ( year.size() == title.size() && year.size() == authors.size() && year.size() == tags.size() )
				{
					int min;
					string temp,temp1,temp2,temp3;

					for (int i = 0; i < title.size(); i++)
					{
						min = i;
						for (int j = i+1; j < title.size(); ++j)
						{
							if ( title[j] < title[min] )
							{
								min = j;
							}
						}

						temp = year[min];
						temp1 = title[min];
						temp2 = authors[min];
						temp3 = tags[min];
						year[min] = year[i];
						title[min] = title[i];
						authors[min] = authors[i];
						tags[min] = tags[i];
						year[i] = temp;
						title[i] = temp1;
						authors[i] = temp2;
						tags[i] = temp3;
					}

					for (int i = 0; i < title.size(); ++i)
					{
						if ( year[i] != "" && title[i] != "" && authors[i] != "" && tags[i] != "" )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << authors[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << tags[i] << "\"" << endl;
						}
					}
				}
				else
				{
					outFile << "Exception: missing field" << endl;
				}
			}
			else if ( Entry == "authors" )
			{
				if ( year.size() == title.size() && year.size() == authors.size() && year.size() == tags.size() )
				{
					int min;
					string temp,temp1,temp2,temp3;

					for (int i = 0; i < authors.size(); i++)
					{
						min = i;
						for (int j = i+1; j < authors.size(); ++j)
						{
							if ( authors[j] < authors[min] )
							{
								min = j;
							}
						}

						temp = year[min];
						temp1 = title[min];
						temp2 = authors[min];
						temp3 = tags[min];
						year[min] = year[i];
						title[min] = title[i];
						authors[min] = authors[i];
						tags[min] = tags[i];
						year[i] = temp;
						title[i] = temp1;
						authors[i] = temp2;
						tags[i] = temp3;
					}

					for (int i = 0; i < authors.size(); ++i)
					{
						if ( year[i] != "" && title[i] != "" && authors[i] != "" && tags[i] != "" )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << authors[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << tags[i] << "\"" << endl;
						}
					}
				}
				else
				{
					outFile << "Exception: missing field" << endl;
				}
			}
			else if ( Entry == "tags" )
			{
				if ( year.size() == title.size() && year.size() == authors.size() && year.size() == tags.size() )
				{
					int min;
					string temp,temp1,temp2,temp3;

					for (int i = 0; i < tags.size(); i++)
					{
						min = i;
						for (int j = i+1; j < tags.size(); ++j)
						{
							if ( tags[j] < tags[min] )
							{
								min = j;
							}
						}

						temp = year[min];
						temp1 = title[min];
						temp2 = authors[min];
						temp3 = tags[min];
						year[min] = year[i];
						title[min] = title[i];
						authors[min] = authors[i];
						tags[min] = tags[i];
						year[i] = temp;
						title[i] = temp1;
						authors[i] = temp2;
						tags[i] = temp3;
					}

					for (int i = 0; i < tags.size(); ++i)
					{
						if ( year[i] != "" && title[i] != "" && authors[i] != "" && tags[i] != "" )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << authors[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << tags[i] << "\"" << endl;
						}
					}
				}
				else
				{
					outFile << "Exception: missing field" << endl;
				}
			}
		}
		else if ( token == "search" )				/* It searches.				*/
		{
			getline(iss,token,' ');
			istringstream iss2(token);
			string Entry;
			getline(iss2,Entry,'"'); getline(iss2,Entry,'"');
			getline(iss,token,' ');  getline(iss,token,' ');
			istringstream iss3(token);
			string inMember;
			getline(iss3,inMember,'"'); getline(iss3,inMember,'"');

			if ( inMember == "year" )
			{
				token = "";
				bool flag = true;

				for (int i = 0; i < year.size(); ++i)
				{
					if ( Entry == year[i] )
					{
						outFile << "\"" << title[i] << "\" ";
						outFile << "\"" << authors[i] << "\" ";
						outFile << "\"" << year[i] << "\" ";
						outFile << "\"" << tags[i] << "\"" << endl;
						flag = false;
					}
				}

				for (int i = 0; i < year.size() && flag; ++i)
				{
					istringstream iss4(year[i]);
					while( getline(iss4,token,' ') )
					{
						if ( token == Entry )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << authors[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << tags[i] << "\"" << endl;
							flag = false;
						}
					}
				}

				if ( flag == true )
				{
					outFile << "Exception: Command is wrong" << endl;
				}
			
			}
			else if ( inMember == "title" )
			{
				token = "";
				bool flag = true;

				for (int i = 0; i < title.size(); ++i)
				{
					if ( Entry == title[i] )
					{
						outFile << "\"" << title[i] << "\" ";
						outFile << "\"" << authors[i] << "\" ";
						outFile << "\"" << year[i] << "\" ";
						outFile << "\"" << tags[i] << "\"" << endl;
						flag = false;
					}
				}

				for (int i = 0; i < title.size() && flag; ++i)
				{
					istringstream iss4(title[i]);
					while( getline(iss4,token,' ') )
					{
						if ( token == Entry )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << authors[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << tags[i] << "\"" << endl;
							flag = false;
						}
					}
				}

				if ( flag == true )
				{
					outFile << "Exception: Command is wrong" << endl;
				}
			}
			else if ( inMember == "authors" )
			{
				token = "";
				bool flag = true;

				for (int i = 0; i < authors.size(); ++i)
				{
					if ( Entry == authors[i] )
					{
						outFile << "\"" << title[i] << "\" ";
						outFile << "\"" << authors[i] << "\" ";
						outFile << "\"" << year[i] << "\" ";
						outFile << "\"" << tags[i] << "\"" << endl;
						flag = false;
					}
				}

				for (int i = 0; i < authors.size() && flag; ++i)
				{
					istringstream iss4(authors[i]);
					while( getline(iss4,token,' ') )
					{
						if ( token == Entry )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << authors[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << tags[i] << "\"" << endl;
							flag = false;
						}
					}
				}

				if ( flag == true )
				{
					outFile << "Exception: Command is wrong" << endl;
				}
			}
			else if ( inMember == "tags" )
			{
				token = "";
				bool flag = true;

				for (int i = 0; i < tags.size(); ++i)
				{
					if ( Entry == tags[i] )
					{
						outFile << "\"" << title[i] << "\" ";
						outFile << "\"" << authors[i] << "\" ";
						outFile << "\"" << year[i] << "\" ";
						outFile << "\"" << tags[i] << "\"" << endl;
						flag = false;
					}
				}

				for (int i = 0; i < tags.size() && flag; ++i)
				{
					istringstream iss4(tags[i]);
					while( getline(iss4,token,' ') )
					{
						if ( token == Entry )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << authors[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << tags[i] << "\"" << endl;
							flag = false;
						}
					}
				}

				if ( flag == true )
				{
					outFile << "Exception: Command is wrong" << endl;
				}
			}
		}
	}
	outFile.close();
}

void book::CreatePartialEntries()		/* It reads data.txt file and creates parts of book's.		*/
{
	ifstream inputFile;

	inputFile.open("data.txt");

	if ( !inputFile.is_open() )
	{
		throw "data.txt file is not openned.";
	}
	else if ( check_errors(&inputFile) )
	{
		throw -1;
	}
	else
	{
		string line;
		string Word;
		char c;
		int QuotesCounter = 0, MemberCounter = 0;
		getline(inputFile,line);
		setDataType(line);

		while( inputFile.get(c) )
		{
			if ( c != '"' )
			{
				if ( c == '\n' )
				{
					c = ' ';
				}
				if ( QuotesCounter == 0 && c == ' ' )
				{
					continue;
				}
				Word += c;
			}
			else
			{
				++QuotesCounter;

				if ( QuotesCounter == 2 )
				{
					if ( MemberCounter == 0 )
					{
						title.push_back(Word);
						++MemberCounter;
						QuotesCounter = 0;
						Word = "";
					}
					else if ( MemberCounter == 1 )
					{
						authors.push_back(Word);
						++MemberCounter;
						Word = "";
					}
					else if ( MemberCounter == 2 )
					{
						year.push_back(Word);
						++MemberCounter;
						Word = "";
					}
					else if ( MemberCounter == 3 )
					{
						tags.push_back(Word);
						MemberCounter = 0;
						Word = "";
					}
					QuotesCounter = 0;
				}
			}
		}
	}

	inputFile.close();
}