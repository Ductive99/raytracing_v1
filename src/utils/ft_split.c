/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 03:06:36 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 21:42:33 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_in_charset(char c, const char *charset)
{
	while (*charset)
		if (*charset++ == c)
			return (1);
	return (0);
}

static int	count_words(char const *s, const char *charset)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && is_in_charset(*s, charset))
			s++;
		if (*s && ++count)
			while (*s && !is_in_charset(*s, charset))
				s++;
	}
	return (count);
}

static char	**fill_arr(char **arr, const char *s, const char *charset)
{
	int		j;
	int		start;
	int		i;
	char	*word;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && is_in_charset(s[i], charset))
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] && !is_in_charset(s[i], charset))
			i++;
		word = malloc(i - start + 1);
		if (!word)
			return (arr[j] = NULL, free_split(arr), NULL);
		ft_memcpy(word, &s[start], i - start);
		word[i - start] = '\0';
		arr[j++] = word;
	}
	return (arr);
}

char	**ft_split(char const *s, const char *charset)
{
	char	**words;
	int		word_count;

	if (!s || !charset)
		return (NULL);
	word_count = count_words(s, charset);
	words = malloc((word_count + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	words[word_count] = NULL;
	if (word_count == 0)
		return (words);
	return (fill_arr(words, s, charset));
}

// int	main(int argc, char **argv)
// {
//     char	**result;
//     char	*charset;
//     int		i;

//     if (argc < 2)
//     {
//         printf("Usage: %s <string> [charset]\n", argv[0]);
//         printf("Example: %s \"hello world test\"\n", argv[0]);
//         printf("Example: %s \"hello,world;test\" \",;\"\n", argv[0]);
//         return (1);
//     }
//     if (argc == 2)
//         charset = " \t\n";
//     else
//         charset = argv[2];
//     result = ft_split(argv[1], charset);
//     if (!result)
//     {
//         printf("Error: ft_split failed\n");
//         return (1);
//     }
//     i = 0;
//     while (result[i])
//     {
//         printf("[%d]: \"%s\"\n", i, result[i]);
//         i++;
//     }
//     printf("\nTotal words: %d\n", i);
//     free_split(result, i);
//     return (0);
// }