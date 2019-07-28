#ifndef BASE_H
#define BASE_H

#include <vector>		/* We use vectors.		*/

class base 				/* Our base class.		*/
{
public:
	base();																		/* Default constructor of base class.		*/
	void setDataType(const std::string data){ dataType = data; }				/* Sets the data type.						*/
	const std::string getDataType()const { return dataType; }					/* Gets the data type.						*/
	const std::string getCommandLine(const int index)const { return CommandLine[index]; }	/* Gets command line string.	*/
	const std::vector<std::string> getCommandVector()const { return CommandLine; }			/* Gets command vector.			*/

	void DataTextReader();			/* Reads data type.		*/
	void CommandsTextReader();		/* Reads all commands.	*/
private:
	std::string dataType;					/* Our data type.		*/
	std::vector<std::string> CommandLine;	/* Our command vector.	*/
};

int check_errors(std::ifstream *f);						/* It checks if file openned or not.					*/

#endif