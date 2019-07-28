#ifndef OR_H
#define OR_H

class Or : public gates 				/* We create OR gates.		*/
{
public:
	Or();
	const char* getOrName(int indGate, int ind1) const { return OrName[indGate][ind1]; }
	const char getOrName(int indGate, int ind1, int ind2) const { return OrName[indGate][ind1][ind2]; }
	const char setOrName(int indGate, int ind1, int ind2, char data) { OrName[indGate][ind1][ind2] = data; return OrName[indGate][ind1][ind2]; }
	const int getOrGateSize() const { return OrGateSize; }
	~Or();
	virtual void evaluate(int inp1, int inp2) override;

private:
	char*** OrName = NULL;
	int OrGateSize = 0;
};

#endif