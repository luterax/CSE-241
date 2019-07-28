#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;
#include "base.h"
#include "music.h"

music::music() : base()		/* Our music constructor. We do everything in here. 	*/
{
	CreatePartialEntries();		/* Creates data.txt parts.		*/
	ErrorPrinter();				/* Prints errors.				*/
	ApplyCommands();			/* Applies commands.			*/
}

void music::ErrorPrinter()			/* It checks and prints errors. */
{
	int uniqueCounter = 0, maximumSize = 0, yearCount = 0, titleCount = 0, artistsCount = 0, genreCount = 0;
	ofstream outFile;
	outFile.open("output.txt", ios::out );

	if ( !outFile.is_open() )
	{
		throw "output.txt file is not openned.";
	}

	outFile << "Catalog Read: music" << endl;

	maximumSize = max({ title.size(),artists.size(),year.size(),genre.size() });

	if ( title.size() < maximumSize )
	{
		title.push_back("");
		++titleCount;
	}
	if ( artists.size() < maximumSize )
	{
		artists.push_back("");
		++artistsCount;
	}
	if ( year.size() < maximumSize )
	{
		year.push_back("");
		++yearCount;
	}
	if ( genre.size() < maximumSize )
	{
		genre.push_back("");
		++genreCount;
	}

	bool f1,f2,f3,f4;
	f1 = f2 = f3 = f4 = true;

	for (int i = 0; i < maximumSize; ++i)
	{
		if ( ( title[i] == "" || artists[i] == "" || year[i] == "" || genre[i] == "" ) )
		{
			if ( title[i] == "" && titleCount == 0 && f1 )
			{
				outFile << "Exception: duplicate entry" << endl;
				outFile << "\"" << title[i] << "\" \"" <<  artists[i] << "\" \"" << year[i] << "\" \"" << genre[i] << "\"" << endl;
				f1 = false;
				++uniqueCounter;
			}
			else if ( artists[i] == "" && artistsCount == 0 && f2 )
			{
				outFile << "Exception: duplicate entry" << endl;
				outFile << "\"" << title[i] << "\" \"" <<  artists[i] << "\" \"" << year[i] << "\" \"" << genre[i] << "\"" << endl;
				f2 = false;
				++uniqueCounter;
			}
			else if ( year[i] == "" && yearCount == 0 && f3 )
			{
				outFile << "Exception: duplicate entry" << endl;
				outFile << "\"" << title[i] << "\" \"" <<  artists[i] << "\" \"" << year[i] << "\" \"" << genre[i] << "\"" << endl;
				f3 = false;
				++uniqueCounter;
			}
			else if ( genre[i] == "" && genreCount == 0 && f4 )
			{
				outFile << "Exception: duplicate entry" << endl;
				outFile << "\"" << title[i] << "\" \"" <<  artists[i] << "\" \"" << year[i] << "\" \"" << genre[i] << "\"" << endl;
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
				outFile << "\"" <<  artists[i] << "\" \"" << year[i] << "\" \"" << genre[i] << "\"" << endl;
			}
		}
	}
	else if ( artistsCount == 1 )
	{
		++uniqueCounter;
		outFile << "Exception: missing field" << endl;
		for (int i = 0; i < artists.size(); ++i)
		{
			if ( artists[i] == "" )
			{
				outFile << "\"" << title[i] << "\" \"" << year[i] << "\" \"" << genre[i] << "\"" << endl;
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
				outFile << "\"" << title[i] << "\" \"" <<  artists[i] << "\" \"" << genre[i] << "\"" << endl;
			}
		}
	}
	else if ( genreCount == 1 )
	{
		++uniqueCounter;
		outFile << "Exception: missing field" << endl;
		for (int i = 0; i < genre.size(); ++i)
		{
			if (  genre[i] == "" )
			{
				outFile << "\"" << title[i] << "\" \"" <<  artists[i] << "\" \"" << year[i] << "\"" << endl;
			}
		}
	}

	outFile << uniqueCounter << " unique entries" << endl;

	outFile.close();
}

void music::ApplyCommands()			/* It applies commands. If command is sort then it sorts, if command is search then searches and prints to output.txt.	*/
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
				if ( year.size() == title.size() && year.size() == artists.size() && year.size() == genre.size() )
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
						temp2 = artists[min];
						temp3 = genre[min];
						year[min] = year[i];
						title[min] = title[i];
						artists[min] = artists[i];
						genre[min] = genre[i];
						year[i] = temp;
						title[i] = temp1;
						artists[i] = temp2;
						genre[i] = temp3;
					}

					for (int i = 0; i < year.size(); ++i)
					{
						if ( year[i] != "" && title[i] != "" && artists[i] != "" && genre[i] != "" )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << artists[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << genre[i] << "\"" << endl;
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
				if ( year.size() == title.size() && year.size() == artists.size() && year.size() == genre.size() )
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
						temp2 = artists[min];
						temp3 = genre[min];
						year[min] = year[i];
						title[min] = title[i];
						artists[min] = artists[i];
						genre[min] = genre[i];
						year[i] = temp;
						title[i] = temp1;
						artists[i] = temp2;
						genre[i] = temp3;
					}

					for (int i = 0; i < title.size(); ++i)
					{
						if ( year[i] != "" && title[i] != "" && artists[i] != "" && genre[i] != "" )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << artists[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << genre[i] << "\"" << endl;
						}
					}
				}
				else
				{
					outFile << "Exception: missing field" << endl;
				}
			}
			else if ( Entry == "artists" )
			{
				if ( year.size() == title.size() && year.size() == artists.size() && year.size() == genre.size() )
				{
					int min;
					string temp,temp1,temp2,temp3;

					for (int i = 0; i < artists.size(); i++)
					{
						min = i;
						for (int j = i+1; j < artists.size(); ++j)
						{
							if ( artists[j] < artists[min] )
							{
								min = j;
							}
						}

						temp = year[min];
						temp1 = title[min];
						temp2 = artists[min];
						temp3 = genre[min];
						year[min] = year[i];
						title[min] = title[i];
						artists[min] = artists[i];
						genre[min] = genre[i];
						year[i] = temp;
						title[i] = temp1;
						artists[i] = temp2;
						genre[i] = temp3;
					}

					for (int i = 0; i < artists.size(); ++i)
					{
						if ( year[i] != "" && title[i] != "" && artists[i] != "" && genre[i] != "" )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << artists[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << genre[i] << "\"" << endl;
						}
					}
				}
				else
				{
					outFile << "Exception: missing field" << endl;
				}
			}
			else if ( Entry == "genre" )
			{
				if ( year.size() == title.size() && year.size() == artists.size() && year.size() == genre.size() )
				{
					int min;
					string temp,temp1,temp2,temp3;

					for (int i = 0; i < genre.size(); i++)
					{
						min = i;
						for (int j = i+1; j < genre.size(); ++j)
						{
							if ( genre[j] < genre[min] )
							{
								min = j;
							}
						}

						temp = year[min];
						temp1 = title[min];
						temp2 = artists[min];
						temp3 = genre[min];
						year[min] = year[i];
						title[min] = title[i];
						artists[min] = artists[i];
						genre[min] = genre[i];
						year[i] = temp;
						title[i] = temp1;
						artists[i] = temp2;
						genre[i] = temp3;
					}

					for (int i = 0; i < genre.size(); ++i)
					{
						if ( year[i] != "" && title[i] != "" && artists[i] != "" && genre[i] != "" )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << artists[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << genre[i] << "\"" << endl;
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
						outFile << "\"" << artists[i] << "\" ";
						outFile << "\"" << year[i] << "\" ";
						outFile << "\"" << genre[i] << "\"" << endl;
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
							outFile << "\"" << artists[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << genre[i] << "\"" << endl;
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
						outFile << "\"" << artists[i] << "\" ";
						outFile << "\"" << year[i] << "\" ";
						outFile << "\"" << genre[i] << "\"" << endl;
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
							outFile << "\"" << artists[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << genre[i] << "\"" << endl;
							flag = false;
						}
					}
				}

				if ( flag == true )
				{
					outFile << "Exception: Command is wrong" << endl;
				}
			}
			else if ( inMember == "artists" )
			{
				token = "";
				bool flag = true;

				for (int i = 0; i < artists.size(); ++i)
				{
					if ( Entry == artists[i] )
					{
						outFile << "\"" << title[i] << "\" ";
						outFile << "\"" << artists[i] << "\" ";
						outFile << "\"" << year[i] << "\" ";
						outFile << "\"" << genre[i] << "\"" << endl;
						flag = false;
					}
				}

				for (int i = 0; i < artists.size() && flag; ++i)
				{
					istringstream iss4(artists[i]);
					while( getline(iss4,token,' ') )
					{
						if ( token == Entry )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << artists[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << genre[i] << "\"" << endl;
							flag = false;
						}
					}
				}

				if ( flag == true )
				{
					outFile << "Exception: Command is wrong" << endl;
				}
			}
			else if ( inMember == "genre" )
			{
				token = "";
				bool flag = true;

				for (int i = 0; i < genre.size(); ++i)
				{
					if ( Entry == genre[i] )
					{
						outFile << "\"" << title[i] << "\" ";
						outFile << "\"" << artists[i] << "\" ";
						outFile << "\"" << year[i] << "\" ";
						outFile << "\"" << genre[i] << "\"" << endl;
						flag = false;
					}
				}

				for (int i = 0; i < genre.size() && flag; ++i)
				{
					istringstream iss4(genre[i]);
					while( getline(iss4,token,' ') )
					{
						if ( token == Entry )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << artists[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << genre[i] << "\"" << endl;
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

void music::CreatePartialEntries()		/* It reads data.txt file and creates parts of music's.		*/
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
						artists.push_back(Word);
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
						genre.push_back(Word);
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