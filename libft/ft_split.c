#include "libft.h"

/*
**	@brief	searches next occurence a substr in the string
**	
**	@param	s		pointer to string
**	@param	c		delimiter character
**	@param	first		1 if it's first search
**	@return	char*	pointer to found substr or NULL
*/

static char	*ft_next_s(char const *s, char c, int first)
{
	size_t	i;

	if (*s && *s != c && first)
		return ((char *)s);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!s[i])
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	if (s[i])
		return ((char *)&s[i]);
	return (NULL);
}

/*
**	@brief	counts the number of substrings in a string
**	
**	@param	s		pointer to string
**	@param	c		delimiter character
**	@return	size_t	counts substrings
*/

static size_t	ft_count_substr(char const *s, char c)
{
	size_t	total;
	char	*substr;

	total = 0;
	substr = ft_next_s(s, c, 1);
	while (substr)
	{
		total++;
		substr = ft_next_s(substr, c, 0);
	}
	return (total);
}

/*
**	@brief	allocates memory and copies string. 
**			Copies to the end of string or first occurence delimiter 'c'
**	
**	@param	s		pointer to string
**	@param	c		delimiter character
**	@return	char*	pointer to new string or NULL
*/

static char	*ft_strcdup(const char *s, char c)
{
	char	*new_str;
	int		len_s;
	int		i;

	len_s = 0;
	while (s[len_s] && s[len_s] != c)
		len_s++;
	new_str = (char *)malloc(sizeof(*new_str) * (len_s + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len_s)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}

/*
**	@brief	creates array of strings obtained by splitting ’s’ 
**			using the character ’c’ as a delimiter.
**	
**	@param	s		pointer to string
**	@param	c		delimiter character
**	@return	char**	pointer to new array of strings, terminated by a NULL
*/

char	**ft_split(char const *s, char c)
{
	int		i;
	char	*substr;
	char	**array;

	array = (char **)malloc((ft_count_substr(s, c) + 1) * sizeof(*array));
	if (!array)
		return (NULL);
	i = 0;
	substr = ft_next_s(s, c, 1);
	while (substr)
	{
		array[i] = ft_strcdup(substr, c);
		if (!array[i])
		{
			while (i--)
				free(array[i]);
			free(array);
			return (NULL);
		}
		i++;
		substr = ft_next_s(substr, c, 0);
	}
	array[i] = NULL;
	return (array);
}
