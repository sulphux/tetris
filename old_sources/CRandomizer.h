#include <stdlib.h>
#include <time.h>

class CRandomizer
{
public:
	static CRandomizer& getInstance()
	{
		static CRandomizer instance;
		return instance;
	}

	static int getNewRand();

private:
	CRandomizer(){ srand(time(NULL)); newRandom(); last = 0; };
	CRandomizer(const CRandomizer &);
	CRandomizer& operator=(const CRandomizer&);

	static int last;
	static int pieces[28];
	static void newRandom();
	static void swap(int index1, int index2);

};

