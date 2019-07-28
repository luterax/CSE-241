#ifndef INPUT_H
#define INPUT_H

class input : public gates 				/* We create INPUT gate.		*/
{
public:
	input();
	const char* getInputName(int ind1) const { return inputName[ind1]; }
	const char getInputName(int ind1, int ind2) const { return inputName[ind1][ind2]; }
	const char setInputName(int ind1, int ind2, char data) { inputName[ind1][ind2] = data; return inputName[ind1][ind2]; }
	~input();
	virtual void evaluate(int inp1, int inp2) override;
private:
	char **inputName;
};

#endif