#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, char **argv)
{
	int frame_count;
	char slash[2];

	if (argc < 4 || argc > 4)
		return (printf("Error\narg 1: starting number\narg 2: ending number\narg 3: directory\n"),
			1);

	frame_count = atoi(argv[2]);
	memset(slash, 0, 2);

	if (argv[3][strlen(argv[3])] != '/')
		slash[0] = '/';

	for (int i = atoi(argv[1]); i <= frame_count; i++)
		printf("%s%s%i.xpm ", argv[3], slash, i);

	return (0);
}