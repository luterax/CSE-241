#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "base.h"
#include "movie.h"
using namespace std;

movie::movie() : base()		/* Our movie constructor. We do everything in here. 	*/
{
	CreatePartialEntries();		/* Creates data.txt parts.		*/
	ErrorPrinter();				/* Prints errors.				*/
	ApplyCommands();			/* Applies commands.			*/
}

void movie::ErrorPrinter()			/* It checks and prints errors. */
{
	int uniqueCounter = 0, maximumSize = 0, starringCount = 0, yearCount = 0, titleCount = 0, directorCount = 0, genreCount = 0;
	ofstream outFile;
	outFile.open("output.txt", ios::out );

	if ( !outFile.is_open() )
	{
		throw "output.txt file is not openned.";
	}

	outFile << "Catalog Read: movie" << endl;

	maximumSize = max({ title.size(),director.size(),year.size(),genre.size(),starring.size() });

	if ( title.size() < maximumSize )
	{
		title.push_back("");
		++titleCount;
	}
	if ( director.size() < maximumSize )
	{
		director.push_back("");
		++directorCount;
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
	if ( starring.size() < maximumSize )
	{
		starring.push_back("");
		++starringCount;
	}

	bool f1,f2,f3,f4,f5;
	f1 = f2 = f3 = f4 = f5 = true;

	for (int i = 0; i < maximumSize; ++i)
	{
		if ( ( title[i] == "" || director[i] == "" || year[i] == "" || genre[i] == "" || starring[i] == "" ) )
		{
			if ( title[i] == "" && titleCount == 0 && f1 )
			{
				outFile << "Exception: duplicate entry" << endl;
				outFile << "\"" << title[i] << "\" \"" <<  director[i] << "\" \"" << year[i] << "\" \"" << genre[i] << "\" \"" << starring[i] << "\"" << endl;
				f1 = false;
				++uniqueCounter;
			}
			else if ( director[i] == "" && directorCount == 0 && f2 )
			{
				outFile << "Exception: duplicate entry" << endl;
				outFile << "\"" << title[i] << "\" \"" <<  director[i] << "\" \"" << year[i] << "\" \"" << genre[i] << "\" \"" << starring[i] << "\"" << endl;
				f2 = false;
				++uniqueCounter;
			}
			else if ( year[i] == "" && yearCount == 0 && f3 )
			{
				outFile << "Exception: duplicate entry" << endl;
				outFile << "\"" << title[i] << "\" \"" <<  director[i] << "\" \"" << year[i] << "\" \"" << genre[i] << "\" \"" << starring[i] << "\"" << endl;
				f3 = false;
				++uniqueCounter;
			}
			else if ( genre[i] == "" && genreCount == 0 && f4 )
			{
				outFile << "Exception: duplicate entry" << endl;
				outFile << "\"" << title[i] << "\" \"" <<  director[i] << "\" \"" << year[i] << "\" \"" << genre[i] << "\" \"" << starring[i] << "\"" << endl;
				f4 = false;
				++uniqueCounter;
			}
			else if ( starring[i] == "" && starringCount == 0 && f5 )
			{
				outFile << "Exception: duplicate entry" << endl;
				outFile << "\"" << title[i] << "\" \"" <<  director[i] << "\" \"" << year[i] << "\" \"" << genre[i] << "\" \"" << starring[i] << "\"" << endl;
				f5 = false;
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
				outFile << "\"" <<  director[i] << "\" \"" << year[i] << "\" \"" << genre[i] << "\" \"" << starring[i] << "\"" << endl;
			}
		}
	}
	else if ( directorCount == 1 )
	{
		++uniqueCounter;
		outFile << "Exception: missing field" << endl;
		for (int i = 0; i < director.size(); ++i)
		{
			if ( director[i] == "" )
			{
				outFile << "\"" << title[i] << "\" \"" << year[i] << "\" \"" << genre[i] << "\" \"" << starring[i] << "\"" << endl;
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
				outFile << "\"" << title[i] << "\" \"" <<  director[i] << "\" \"" << genre[i] << "\" \"" << starring[i] << "\"" << endl;
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
				outFile << "\"" << title[i] << "\" \"" <<  director[i] << "\" \"" << year[i] << "\" \"" << starring[i] << "\"" << endl;
			}
		}
	}
	else if ( starringCount == 1 )
	{
		++uniqueCounter;
		outFile << "Exception: missing field" << endl;
		for (int i = 0; i < starring.size(); ++i)
		{
			if ( starring[i] == "" )
			{
				outFile << "\"" << title[i] << "\" \"" <<  director[i] << "\" \"" << year[i] << "\" \"" << genre[i]  << "\"" << endl;
			}
		}
	}

	outFile << uniqueCounter << " unique entries" << endl;

	outFile.close();
}

void movie::ApplyCommands()			/* It applies commands. If command is sort then it sorts, if command is search then searches and prints to output.txt.	*/
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
				if ( year.size() == title.size() && year.size() == director.size() && year.size() == genre.size() && year.size() == starring.size() )
				{
					int min,StringToInt1,StringToInt2;
					string temp,temp1,temp2,temp3,temp4;

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
						temp2 = director[min];
						temp3 = genre[min];
						temp4 = starring[min];
						year[min] = year[i];
						title[min] = title[i];
						director[min] = director[i];
						genre[min] = genre[i];
						starring[min] = starring[i];
						year[i] = temp;
						title[i] = temp1;
						director[i] = temp2;
						genre[i] = temp3;
						starring[i] = temp4;
					}

					for (int i = 0; i < year.size(); ++i)
					{
						if ( year[i] != "" && title[i] != "" && director[i] != "" && genre[i] != "" && starring[i] != "" )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << director[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << genre[i] << "\" ";
							outFile << "\"" << starring[i] << "\"" << endl;
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
				if ( year.size() == title.size() && year.size() == director.size() && year.size() == genre.size() && year.size() == starring.size() )
				{
					int min;
					string temp,temp1,temp2,temp3,temp4;

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
						temp2 = director[min];
						temp3 = genre[min];
						temp4 = starring[min];
						year[min] = year[i];
						title[min] = title[i];
						director[min] = director[i];
						genre[min] = genre[i];
						starring[min] = starring[i];
						year[i] = temp;
						title[i] = temp1;
						director[i] = temp2;
						genre[i] = temp3;
						starring[i] = temp4;
					}

					for (int i = 0; i < title.size(); ++i)
					{
						if ( year[i] != "" && title[i] != "" && director[i] != "" && genre[i] != "" && starring[i] != "" )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << director[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << genre[i] << "\" ";
							outFile << "\"" << starring[i] << "\"" << endl;
						}
					}
				}
				else
				{
					outFile << "Exception: missing field" << endl;
				}
			}
			else if ( Entry == "director" )
			{
				if ( year.size() == title.size() && year.size() == director.size() && year.size() == genre.size() && year.size() == starring.size() )
				{
					int min;
					string temp,temp1,temp2,temp3,temp4;

					for (int i = 0; i < director.size(); i++)
					{
						min = i;
						for (int j = i+1; j < director.size(); ++j)
						{
							if ( director[j] < director[min] )
							{
								min = j;
							}
						}

						temp = year[min];
						temp1 = title[min];
						temp2 = director[min];
						temp3 = genre[min];
						temp4 = starring[min];
						year[min] = year[i];
						title[min] = title[i];
						director[min] = director[i];
						genre[min] = genre[i];
						starring[min] = starring[i];
						year[i] = temp;
						title[i] = temp1;
						director[i] = temp2;
						genre[i] = temp3;
						starring[i] = temp4;
					}

					for (int i = 0; i < director.size(); ++i)
					{
						if ( year[i] != "" && title[i] != "" && director[i] != "" && genre[i] != "" && starring[i] != "" )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << director[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << genre[i] << "\" ";
							outFile << "\"" << starring[i] << "\"" << endl;
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
				if ( year.size() == title.size() && year.size() == director.size() && year.size() == genre.size() && year.size() == starring.size() )
				{
					int min;
					string temp,temp1,temp2,temp3,temp4;

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
						temp2 = director[min];
						temp3 = genre[min];
						temp4 = starring[min];
						year[min] = year[i];
						title[min] = title[i];
						director[min] = director[i];
						genre[min] = genre[i];
						starring[min] = starring[i];
						year[i] = temp;
						title[i] = temp1;
						director[i] = temp2;
						genre[i] = temp3;
						starring[i] = temp4;
					}

					for (int i = 0; i < genre.size(); ++i)
					{
						if ( year[i] != "" && title[i] != "" && director[i] != "" && genre[i] != "" && starring[i] != "" )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << director[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << genre[i] << "\" ";
							outFile << "\"" << starring[i] << "\"" << endl;
						}
					}
				}
				else
				{
					outFile << "Exception: missing field" << endl;
				}
			}
			else if ( Entry == "starring" )
			{
				if ( year.size() == title.size() && year.size() == director.size() && year.size() == genre.size() && year.size() == starring.size() )
				{
					int min;
					string temp,temp1,temp2,temp3,temp4;

					for (int i = 0; i < starring.size(); i++)
					{
						min = i;
						for (int j = i+1; j < starring.size(); ++j)
						{
							if ( starring[j] < starring[min] )
							{
								min = j;
							}
						}

						temp = year[min];
						temp1 = title[min];
						temp2 = director[min];
						temp3 = genre[min];
						temp4 = starring[min];
						year[min] = year[i];
						title[min] = title[i];
						director[min] = director[i];
						genre[min] = genre[i];
						starring[min] = starring[i];
						year[i] = temp;
						title[i] = temp1;
						director[i] = temp2;
						genre[i] = temp3;
						starring[i] = temp4;
					}

					for (int i = 0; i < starring.size(); ++i)
					{
						if ( year[i] != "" && title[i] != "" && director[i] != "" && genre[i] != "" && starring[i] != "" )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << director[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << genre[i] << "\" ";
							outFile << "\"" << starring[i] << "\"" << endl;
						}
					}
				}
				else
				{
					outFile << "Exception: missing field" << endl;
				}
			}
			else
			{
				outFile << "Exception: Command is wrong." << endl;
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
						outFile << "\"" << director[i] << "\" ";
						outFile << "\"" << year[i] << "\" ";
						outFile << "\"" << genre[i] << "\" ";
						outFile << "\"" << starring[i] << "\"" << endl;
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
							outFile << "\"" << director[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << genre[i] << "\" ";
							outFile << "\"" << starring[i] << "\"" << endl;
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
						outFile << "\"" << director[i] << "\" ";
						outFile << "\"" << year[i] << "\" ";
						outFile << "\"" << genre[i] << "\" ";
						outFile << "\"" << starring[i] << "\"" << endl;
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
							outFile << "\"" << director[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << genre[i] << "\" ";
							outFile << "\"" << starring[i] << "\"" << endl;
							flag = false;
						}
					}
				}

				if ( flag == true )
				{
					outFile << "Exception: Command is wrong" << endl;
				}
			}
			else if ( inMember == "director" )
			{
				token = "";
				bool flag = true;

				for (int i = 0; i < director.size(); ++i)
				{
					if ( Entry == director[i] )
					{
						outFile << "\"" << title[i] << "\" ";
						outFile << "\"" << director[i] << "\" ";
						outFile << "\"" << year[i] << "\" ";
						outFile << "\"" << genre[i] << "\" ";
						outFile << "\"" << starring[i] << "\"" << endl;
						flag = false;
					}
				}

				for (int i = 0; i < director.size() && flag; ++i)
				{
					istringstream iss4(director[i]);
					while( getline(iss4,token,' ') )
					{
						if ( token == Entry )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << director[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << genre[i] << "\" ";
							outFile << "\"" << starring[i] << "\"" << endl;
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
						outFile << "\"" << director[i] << "\" ";
						outFile << "\"" << year[i] << "\" ";
						outFile << "\"" << genre[i] << "\" ";
						outFile << "\"" << starring[i] << "\"" << endl;
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
							outFile << "\"" << director[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << genre[i] << "\" ";
							outFile << "\"" << starring[i] << "\"" << endl;
							flag = false;
						}
					}
				}

				if ( flag == true )
				{
					outFile << "Exception: Command is wrong" << endl;
				}
			}
			else if ( inMember == "starring" )
			{
				token = "";
				bool flag = true;

				for (int i = 0; i < starring.size(); ++i)
				{
					if ( Entry == starring[i] )
					{
						outFile << "\"" << title[i] << "\" ";
						outFile << "\"" << director[i] << "\" ";
						outFile << "\"" << year[i] << "\" ";
						outFile << "\"" << genre[i] << "\" ";
						outFile << "\"" << starring[i] << "\"" << endl;
						flag = false;
					}
				}

				for (int i = 0; i < starring.size() && flag; ++i)
				{
					istringstream iss4(starring[i]);
					while( getline(iss4,token,' ') )
					{
						if ( token == Entry )
						{
							outFile << "\"" << title[i] << "\" ";
							outFile << "\"" << director[i] << "\" ";
							outFile << "\"" << year[i] << "\" ";
							outFile << "\"" << genre[i] << "\" ";
							outFile << "\"" << starring[i] << "\"" << endl;
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

void movie::CreatePartialEntries()		/* It reads data.txt file and creates parts of movie's.		*/
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
						director.push_back(Word);
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
						++MemberCounter;
						Word = "";
					}
					else if ( MemberCounter == 4 )
					{
						starring.push_back(Word);
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