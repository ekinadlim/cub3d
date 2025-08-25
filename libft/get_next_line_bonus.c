/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:22:30 by apartowi          #+#    #+#             */
/*   Updated: 2024/10/22 19:36:09 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_new_line_found(char *s1, char **line, char **remainder, int i)
{
	char	*temp;

	temp = *line;
	*line = gnl_ft_strjoin(*line, s1, i);
	free (temp);
	if (*line == 0)
		return (-1);
	if (s1[i + 1] != '\0')
	{
		temp = *remainder;
		*remainder = gnl_ft_strjoin(0, s1 + i + 1, gnl_ft_strlen(s1 + i +1));
		free (temp);
		if (*remainder == 0)
			return (-1);
	}
	else if (*remainder)
	{
		free (*remainder);
		*remainder = 0;
	}
	return (1);
}

static int	ft_check_remainder(char **line, char **remainder)
{
	int		i;
	char	*temp;
	int		check_return;

	i = 0;
	while ((*remainder)[i] && (*remainder)[i] != '\n')
		i++;
	if ((*remainder)[i] == '\n')
	{
		check_return = ft_new_line_found(*remainder, line, remainder, i);
		if (check_return == 1)
			return (1);
		else if (check_return == -1)
			return (-1);
	}
	temp = *line;
	*line = gnl_ft_strjoin(0, *remainder, gnl_ft_strlen(*remainder));
	free (temp);
	if (*line == 0)
		return (-1);
	free (*remainder);
	*remainder = 0;
	return (0);
}

static int	ft_find_new_line(char *buffer, char **line, char **remainder)
{
	int		i;
	char	*temp;
	int		check_return;

	if (*remainder)
	{
		i = ft_check_remainder(line, remainder);
		if (i == 1 || i == -1)
			return (i);
	}
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		check_return = ft_new_line_found(buffer, line, remainder, i);
		if (check_return == 1 || check_return == -1)
			return (check_return);
	}
	temp = *line;
	*line = gnl_ft_strjoin(*line, buffer, i - 1);
	free (temp);
	if (*line == 0)
		return (-1);
	return (0);
}

static char	*ft_real_gnl(int fd, char *buffer, char **line, char **remainder)
{
	int	amount_read;

	amount_read = 0;
	while (1)
	{
		if (*remainder == 0)
			amount_read = read(fd, buffer, BUFFER_SIZE);
		if ((amount_read == 0 && *remainder == 0) || amount_read < 0)
			return (ft_eof_or_error(amount_read, buffer, line, remainder));
		buffer[amount_read] = '\0';
		amount_read = ft_find_new_line(buffer, line, remainder);
		if (amount_read == 1 || amount_read == -1)
		{
			free (buffer);
			if (amount_read == -1)
			{
				ft_free_remainder (remainder);
				free (*line);
				return (0);
			}
			return (*line);
		}
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*remainder[1024];

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	line = gnl_ft_strjoin(0, "", 1);
	if (line == 0)
	{
		ft_free_remainder (&remainder[fd]);
		return (0);
	}
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (buffer == 0)
	{
		ft_free_remainder (&remainder[fd]);
		free (line);
		errno = 99;
		return (0);
	}
	return (ft_real_gnl(fd, buffer, &line, &remainder[fd]));
}

/*int main()
{
	//char *line = ft_strjoin(0, "", 1);
	//int fd = 0;
	printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);
	char *s;
	int fd1 = open("test.txt", O_RDONLY);
	s = get_next_line(fd1);
	printf("%s", s);
	free (s);
	int fd2 = open("1char.txt", O_RDONLY);
	s = get_next_line(fd2);
	printf("%s", s);
	free (s);
	s = get_next_line(fd1);
	printf("%s", s);
	free (s);
	s = get_next_line(fd2);
	printf("%s", s);
	free (s);
	//while (s != 0)
	//{
	//	s = get_next_line(fd);
	//	printf("%s", s);
	//	free (s);
	//}
	//printf("%s", s);
	//	free (s);
	//s = get_next_line(fd);
	//free (s);
}*/
