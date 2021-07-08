#include "microshell.h"

int ft_strlen(char *a)
{
      int i;
 
      i = 0;
      while (a[i])
          i++;
      return (i);
}

int ft_strlen2(char **a)
{
      int i;
 
      i = 0;
      while (a[i])
          i++;
      return (i);
}

char *ft_strdup(char *a)
{
	char *cpy;
	int i;

	i = 0;
	if (a == 0)
		return (0);
	if ((cpy = malloc(sizeof(char) * ft_strlen(a) + 1)) == 0)
		return (0);
	while (a[i] != 0)
	{
		cpy[i] = a[i];
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}

/*
char *ft_strjoin(char *a, char *b)
{
	int i;
	int n;
	char *ret;

	i = 0;
	n = 0;
	ret = malloc(ft_strlen(a) + ft_strlen(b) + 1);
	while(a[i])
	{
		ret[i] = a[i];
		i++;
	}
	while(b[n])
	{
		ret[i] = b[n];
	  	i++;
		n++;
	}
	ret[i] = 0;
	return (ret);
}*/
