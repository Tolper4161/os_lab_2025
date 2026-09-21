#include "swap.h"

void Swap(char *left, char *right)
{
	char variable = *left;
	*left = *right;
	*right = variable;
}
