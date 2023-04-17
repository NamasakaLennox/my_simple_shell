#include "main.h"

int _strcmp(char *s1, char *s2)
{
	int diff, i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		diff = s1[i] - s2[i];
		if (diff)
		{
			return (diff);
		}
		i++;
	}

	return (0);
}

int _strlen(char *str)
{
	int count = 0;

	while (str[count])
		count++;

	return (count);
}
