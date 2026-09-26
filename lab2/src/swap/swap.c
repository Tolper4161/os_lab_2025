#include "swap.h"

void Swap(char *left, char *right)
{
	char symb = *left;
	*left = *right;
	*right = symb;
}
