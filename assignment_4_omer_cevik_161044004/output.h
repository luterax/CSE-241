#ifndef OUTPUT_H
#define OUTPUT_H

class output : public gates 				/* We create OUTPUT gate.		*/
{
public:
	output();
	const int setOutputResult(int index,const int data) { OutputResult[index] = data; return OutputResult[index]; }
	const int getOutputResult(int index)const { return OutputResult[index]; }
	const int getOutputSize()const { return outputSize; }
	const char* getOutputName(int ind1) const { return outputName[ind1]; }
	const char getOutputName(int ind1, int ind2) const { return outputName[ind1][ind2]; }
	const char setOutputName(int ind1, int ind2,const char data) { outputName[ind1][ind2] = data; return outputName[ind1][ind2]; }
	~output();
	virtual void evaluate(int inp1, int inp2) override;

private:
	char **outputName = NULL;
	int outputSize = 0;
	int *OutputResult = NULL;
};

#endif