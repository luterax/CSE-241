#ifndef FF_H
#define FF_H

class ff : public gates
{
public:
	ff();
	void setFormerOut(const int data){ former_out = data; }
	const int getFormerOut()const { return former_out; }
	const char* getFfName(int indGate, int ind1) const { return FfName[indGate][ind1]; }
	const char getFfName(int indGate, int ind1, int ind2) const { return FfName[indGate][ind1][ind2]; }
	const char setFfName(int indGate, int ind1, int ind2, char data) { FfName[indGate][ind1][ind2] = data; return FfName[indGate][ind1][ind2]; }
	const int getFfGateSize() const { return FfGateSize; }
	~ff();
	virtual void evaluate(int inp1, int inp2) override;

private:
	char*** FfName = NULL;
	int FfGateSize = 0;
	int former_out = 0;
};

#endif