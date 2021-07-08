#include "microshell.h"

void ft_fatal_error()
{
          write(2, "error: fatal\n", 13);
          exit(EXIT_FAILURE); //Only EXIT_FAILURE is the standard value for returning unsuccessful termination, but 1 is used for the same in many implementations.
 }

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
		ft_fatal_error();
	while (a[i] != 0)
	{
		cpy[i] = a[i];
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}
