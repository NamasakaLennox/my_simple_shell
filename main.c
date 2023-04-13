#include "main.h"

void child_exec(char *argv[])
{
        pid_t child;
        int status;

        child = fork();

        if (child == 0)
	{
                execve(argv[0], argv, NULL);
        }
        else
        {
                wait(&status);
                return;
        }
}

int main(void)
{
        char *line;
        char *argv[3];
	size_t max = 1024;
	char *temp;
	int count = 0;

        argv[1] = NULL;
        while (1)
        {
                printf("$ ");
                if (getline(&line, &max, stdin))
                {
	                while (line[count] != '\n')
                                count++;
                        temp = malloc(count + 1);
			if (!temp)
			{
				printf("Error: allocation failed\n");
				return (1);
			}
			count = 0;
			while (line[count] != '\n')
			{
                         	temp[count] = line[count];
				count++;
			}
                        temp[count] = '\0';
			argv[0] = temp;

			child_exec(argv);
			free(temp);
		}
                else
		{
                 	printf("Error: \n");
			exit(98);
		}
        }
	return (0);
}