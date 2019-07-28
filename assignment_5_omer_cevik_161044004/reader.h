#ifndef READER_H
#define READER_H

class reader
{
public:
	reader();
	const int getFileNameSize(const int index)const { return FileNameSize[index]; }
	void setFileNameSize(const int index, const int data){ FileNameSize[index] = data; }

	const string getCommandLine(const int index1, const int index2)const { return CommandLine[index1][index2]; }
	void setCommandLine(const int index1, const int index2, const string data){ CommandLine[index1][index2] = data; }

	const string getFileLine(const int index1, const int index2)const { return FileLine[index1][index2]; }
	void setFileLine(const int index1, const int index2, const string data){ FileLine[index1][index2] = data; }

	const int getFileLineSize()const { return FileLineSize; }
	void setFileLineSize(int data) { FileLineSize = data; }

	const int getCommandSize(const int index)const { return CommandSize[index]; }
	void setCommandSize(const int index, const int data) { CommandSize[index] = data; }

	const int getCommandLineSize()const { return CommandLineSize; }
	void setCommandLineSize(const int data) { CommandLineSize = data; }

	void ReadCommands(const string fname);
	void ReadFiles(const string fname);
	~reader();

private:
	string** CommandLine = NULL;
	string** FileLine = NULL;
	int* FileNameSize = NULL;
	int* CommandSize = NULL;
	int CommandLineSize = 0;
	int FileLineSize = 0;
};

int check_errors(ifstream *f);	/* It checks if file openned or not.		*/

#endif