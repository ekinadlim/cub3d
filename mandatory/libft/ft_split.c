/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:13:46 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/12 14:53:31 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_alloc_s(char **s_array, int i, int j, int char_count)
{
	s_array[i] = (char *)malloc(char_count - j + 1);
	if (s_array[i] == 0)
	{
		j = 0;
		while (j < i)
		{
			free (s_array[j]);
			j++;
		}
		free (s_array);
		return (0);
	}
	return (s_array[i]);
}

static int	ft_create_string(char *string, char *s, int j, char c)
{
	int	l;

	if (string == 0)
		return (0);
	l = 0;
	while (s[j] && s[j] != c)
	{
		string[l] = s[j];
		j++;
		l++;
	}
	string[l] = '\0';
	return (j);
}

static int	ft_real_split(char **string_array, char *s, char c, int word_count)
{
	int	i;
	int	j;
	int	char_count;

	i = 0;
	j = 0;
	while (i < word_count)
	{
		while (s[j] && s[j] == c)
			j++;
		if (s[j] && s[j] != c)
		{
			char_count = j;
			while (s[char_count] && s[char_count] != c)
				char_count++;
			if (ft_alloc_s(string_array, i, j, char_count) == 0)
				return (0);
			j = ft_create_string(string_array[i], s, j, c);
		}
		i++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**string_array;
	int		word_count;

	word_count = ft_count_words((char *)s, c);
	string_array = (char **)malloc((word_count + 1) * sizeof(char *));
	if (string_array == 0)
	{
		free (string_array);
		return (0);
	}
	string_array[word_count] = 0;
	if (ft_real_split(string_array, (char *)s, c, word_count) == 0)
		return (0);
	return (string_array);
}

/*int main()
{
	int i = 0;
	//int words = ft_count_words("lorem ipsum dolor sit amet", ' ');
	int words = ft_count_words("Hello World", ' ');
	printf("%d\n", words);
	//char **string = ft_split("lorem ipsum dolor sit amet", ' ');
	char **string = ft_split("Hello World", ' ');
	//printf("\n", sizeof(string)); 
	while (i < words)
	{
		printf("%s\n", string[i]);
		i++;
	}
	char **tabstr;
	if (!(tabstr = ft_split("Hello World :D", ' ')))
        	printf("NULL");
	else
		if (!tabstr[0])
		printf("ok\n");

}*/
