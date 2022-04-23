#include "header.h"

int Truncate(float realNumber)
{
	int res = realNumber;
	if (res <= realNumber)
	{
		return res;
	}
	else
	{
		return (res + 1);
	}
}

