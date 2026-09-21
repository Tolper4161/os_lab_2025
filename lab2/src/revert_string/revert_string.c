#include "revert_string.h"
#include <string.h>

void RevertString(char *str)
{
	size_t n = strlen(str);

	char *left = str;
	char *right = str + n - 1;

	while (left < right) {
		char symb = *left;
		*left = *right;
        *right = symb;
        left++;
        right--;
	}
}

