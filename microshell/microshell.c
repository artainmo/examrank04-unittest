#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void launch_cmd(char ***cmds, int i, char **env);


void ft_fatal_error()
{
          write(2, "error: fatal\n", 13);
          exit(EXIT_FAILURE); //Only EXIT_FAILURE is the standard value for returning unsuccessful termination, but 1 is used for the same in many implementations.
 }

int ft_strlen2(char **a)
{
	int i;

	i = 0;
	while(a[i])
		i++;
	return (i);
}

int ft_strlen(char *a)
{
	int i;

	i = 0;
	while(a[i])
		i++;
	return (i);
}

void ft_cd(char **cmd)
{
	if (ft_strlen2(cmd) != 2)
		write(2, "error: cd: bad arguments\n", 25);
	else
	{
		if (chdir(cmd[1]) == -1)
		{
			write(2, "error: cd: cannot change directory to ", 38);
			write(2, cmd[1], ft_strlen(cmd[1]));
			write(2, "\n", 1);
		}
	}
}

void ft_exec(char **cmd, char **env)
{
	pid_t pid;

	if ((pid = fork()) == -1)
			ft_fatal_error();
	if (!pid)
	{
		if (execve(cmd[0], cmd, env) == -1)
		{
			write(2, "error: cannot execute ", 22);
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, "\n", 1);
		}
		exit(0);
	}
	if (waitpid(pid, 0, 0) == -1)
		ft_fatal_error();
}

void ft_pipe(char ***cmd, int i, char **env)
{
	pid_t pid;
	int fd[2];
	int fd1;
	int fd0;

	if (pipe(fd) == -1)
		ft_fatal_error();
	if ((pid = fork()) == -1)
		ft_fatal_error();
	if (!pid)
	{
		if ((fd1 = dup(1)) == -1)
			ft_fatal_error();
		if (close(fd[0]) == -1)
			ft_fatal_error();
		if (dup2(fd[1], 1) == -1)
			ft_fatal_error();
		ft_exec(cmd[i], env);
		if (dup2(1, fd1) == -1)
			ft_fatal_error();
		if (close(fd1) == -1)
			ft_fatal_error();
		if (close(fd[1]) == -1)
			ft_fatal_error();
		exit(0);
	}
	else
	{
		if (waitpid(pid, 0, 0) == -1)
			ft_fatal_error();
		if ((fd0 = dup(0)) == -1)
			ft_fatal_error();
		if (close(fd[1]) == -1)
			ft_fatal_error();
		if (dup2(fd[0], 0) == -1)
			ft_fatal_error();
		launch_cmd(cmd, i + 2, env);
		if (dup2(0, fd0) == -1)
			ft_fatal_error();
		if (close(fd0) == -1)
			ft_fatal_error();
		if (close(fd[0]) == -1)
			ft_fatal_error();
	}
}

void launch_cmd(char ***cmds, int i, char **env)
{
	//printf("{%s %s}\n", cmds[i][0], cmds[i][1]);
	if (cmds[i + 1] != 0 && strcmp(cmds[i + 1][0], "|") == 0)
		ft_pipe(cmds, i,  env);
	else if (strcmp(cmds[i][0], "cd") == 0)
		ft_cd(cmds[i]);
	else
		ft_exec(cmds[i], env);
}

void launch_cmds(char ***cmds, char **env)
{
	int i;

	i = 0;
	while (cmds[i])
	{
		if (strcmp(cmds[i][0], "|") == 0)
		{
			while(cmds[i] && strcmp(cmds[i][0], "|") == 0)
				i += 2;
			if (!cmds[i])
				break ;
		}
		launch_cmd(cmds, i, env);
		i++;
	}
}

void parsing(int argc, char **argv, char ***cmds)
{
	int i;
	int l;
	int m;

	i = 1;
	l = 0;
	m = 0;
	if ((cmds[0] = malloc(sizeof(char *) * argc)) == 0)
		ft_fatal_error();
	while (i < argc)
	{	
		if (i == argc - 1 && (strcmp(argv[i], "|") == 0 || strcmp(argv[i], ";") == 0))
			break ;
		else if (m == 0 && (strcmp(argv[i], "|") == 0 || strcmp(argv[i], ";") == 0))
			(void)0;
		else if (strcmp(argv[i], ";") == 0)
		{
			cmds[l][m] = 0;
			l++;
			m = 0;
			if ((cmds[l] = malloc(sizeof(char *) * argc)) == 0)
				ft_fatal_error();
		}
		else if (strcmp(argv[i], "|") == 0)
		{
			cmds[l][m] = 0;
			l++;
			if ((cmds[l] = malloc(sizeof(char *) + 1)) == 0)
				ft_fatal_error();
			cmds[l][0] = argv[i];
			cmds[l][1] = 0;
			l++;
			m = 0;
			if ((cmds[l] = malloc(sizeof(char *) * argc)) == 0)
				ft_fatal_error();
		}
		else
		{	
			cmds[l][m] = argv[i];
			//printf("|%s|\n", cmds[l][m]);
			m++;
		}
		i++;
	}
	if (m == 0)
		cmds[l] = 0;
	else
	{
		cmds[l][m] = 0;
		cmds[l + 1] = 0;
	}	
}

int main(int argc, char **argv, char **env)
{
	char ***cmds; //First split with | and ; //Second with words for each command

	if (argc == 1)
		return (0);
	if ((cmds = malloc(sizeof(char *) * argc + 1)) == 0) //allocate max memory potentially necessary each time
		ft_fatal_error();
	parsing(argc, argv, cmds);
	launch_cmds(cmds, env);
	exit(0); //No leaks
}
