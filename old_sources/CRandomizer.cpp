#include "CRandomizer.h"
#include "math.h"

int CRandomizer::pieces[28];
int CRandomizer::last;

void CRandomizer::swap(int index1, int index2)
{
	int k = pieces[index1];
	pieces[index1] = pieces[index2];
	pieces[index2] = k;
}

void CRandomizer::newRandom()
{
	for (int i = 0; i < 7; i++)
	{
		pieces[i] = pieces[i + 7] = pieces[i + 14] = pieces[i + 21] = i;
	}
	for (int i = 0; i < 50; i++)
	{
		swap(rand() % 28, rand() % 28);
	}
}

int CRandomizer::getNewRand()
{
	if (last < 27)
	{
		int tmp = pieces[last];
		last++;
		return tmp;
	}
	else
	{
		int tmp = pieces[27];
		newRandom();
		last = 0;
		return tmp;
	}
}