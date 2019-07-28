#ifndef DECODER_H
#define DECODER_H

class decoder : public gates 			/* We create DECODER gates.			*/
{
public:
	decoder();
	const char* getDecName(int indGate, int ind1) const { return DecName[indGate][ind1]; }
	const char getDecName(int indGate, int ind1, int ind2) const { return DecName[indGate][ind1][ind2]; }
	const char setDecName(int indGate, int ind1, int ind2, char data) { DecName[indGate][ind1][ind2] = data; return DecName[indGate][ind1][ind2]; }
	const int getDecGateSize() const { return DecGateSize; }
	~decoder();
	virtual void evaluate(int inp1, int inp2) override;

private:
	char*** DecName = NULL;
	int DecGateSize = 0;
};

#endif