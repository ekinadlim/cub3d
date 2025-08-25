/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi < apartowi@student.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:08:34 by apartowi          #+#    #+#             */
/*   Updated: 2025/08/25 19:45:18 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_ft_strlen(const char *s)
{
	size_t	i;

	if (s == 0)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	*gnl_ft_memcpy(void *dest, const void *src, size_t n)
{
	char			*dp;
	char			*sp;
	unsigned int	i;

	if (dest == 0 && src == 0)
		return (0);
	dp = dest;
	sp = (char *)src;
	i = 0;
	while (i < n)
	{
		dp[i] = sp[i];
		i++;
	}
	return (dest);
}

char	*gnl_ft_strjoin(char const *s1, char const *s2, size_t n)
{
	char	*ps1;
	char	*ps2;
	char	*new;
	int		ps1_len;
	int		ps2_len;

	ps1 = (char *)s1;
	ps2 = (char *)s2;
	ps1_len = gnl_ft_strlen(ps1);
	if (gnl_ft_strlen(ps2) <= n)
		ps2_len = gnl_ft_strlen(ps2);
	else
		ps2_len = n + 1;
	new = (char *)malloc(ps1_len + ps2_len + 1);
	if (new == 0)
	{
		ft_errno(true);
		return (0);
	}
	if (ps1 != 0)
		gnl_ft_memcpy(new, ps1, ps1_len);
	if (ps2 != 0)
		gnl_ft_memcpy(new + ps1_len, ps2, ps2_len);
	new[ps1_len + ps2_len] = '\0';
	return (new);
}

void	ft_free_remainder(char **remainder)
{
	if (*remainder)
	{
		free (*remainder);
		*remainder = 0;
	}
}

char	*ft_eof_or_error(int a_r, char *buffer, char **line, char **remainder)
{
	free (buffer);
	if (a_r < 0)
	{
		ft_free_remainder (remainder);
		ft_errno(true);
	}
	else
	{
		if ((*line)[0] != '\0')
			return (*line);
	}
	free (*line);
	return (0);
}
