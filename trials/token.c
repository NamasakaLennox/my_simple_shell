#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *_strchr(const char *s, int c)
{
	while (*s != (char)c)
		if (!*s++)
			return (0);
	return ((char *)s);
}

size_t _strcspn(const char *s1, const char *s2)
{
	size_t ret = 0;

	while (*s1)
	{
		if (_strchr(s2, *s1))
			return (ret);
		s1++, ret++;
	}
	return (ret);
}

size_t _strspn(const char *s1, const char *s2)
{
	size_t ret = 0;

	while (*s1 && _strchr(s2, *s1++))
		ret++;
	return (ret);
}

char *_strtok(char *str, const char *delim)
{
	static char *p;

	if (str)
		p = str;
	else if (!p)
		return (0);
	str = p + _strspn(p, delim);
	p = str + _strcspn(str, delim);
	if (p == str)
		return (p = 0);
	p = *p ? *p = 0, p + 1 : 0;
	return (str);
}

int main(void)
{
	char *token;
	char *string = "This is\tmy\rhouse";
	char *delim = " \t\r";

	token = _strtok(string, delim);

	while (token != NULL)
	{
		printf("%s\n", token);
		token = _strtok(NULL, delim);
	}
	return (0);
}
