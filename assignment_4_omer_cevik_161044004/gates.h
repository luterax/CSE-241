#ifndef GATES_H
#define GATES_H

class gates 	/* Our base class.			*/
{
public:
	const int getDec1()const { return dec1; }
	const int getDec2()const { return dec2; }
	const int getDec3()const { return dec3; }
	const int getDec4()const { return dec4; }
	const void setDec1(const int data) { dec1 = data; }
	const void setDec2(const int data) { dec2 = data; }
	const void setDec3(const int data) { dec3 = data; }
	const void setDec4(const int data) { dec4 = data; }
	const int getInp1()const { return inp1; }
	const int getInp2()const { return inp2; }
	void setInp1(const int data){ inp1 = data; }
	void setInp2(const int data){ inp2 = data; }
	void setOutput(const int data){output = data;}
	const int getOutput()const { return output; }
	const int setInput(int ind1, int ind2, const int data){ input[ind1][ind2] = data; return input[ind1][ind2]; }
	const int getInput(int ind1, int ind2)const { return input[ind1][ind2]; }
	const string getGate(int ind)const { return Gate[ind]; }
	const string setGate(int ind, const string data){ Gate[ind] = data; return Gate[ind]; }
	const int getInputSize()const { return inputSize; }
	const int getInputColumnSize()const { return inputCol; }
	const int getGateSize()const { return GateSize; }
	void ReadCircuit(const string filename);
	void ReadInput(const string filename);
	gates();
	~gates();

	virtual void evaluate(int inp1, int inp2) = 0;

private:
	int dec1 = 0;
	int dec2 = 0;
	int dec3 = 0;
	int dec4 = 0;
	int **input = NULL;
	int output = 0;
	int inp1 = 0;
	int inp2 = 0;
	int inputGateSize = 0;
	int inputSize = 0;
	int inputCol = 0;
	int GateSize = 0;
	string *Gate = NULL;
};

int check_errors(ifstream *f);	/* It checks if file openned or not.		*/

#endif