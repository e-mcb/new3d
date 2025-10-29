/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:39:57 by mzutter           #+#    #+#             */
/*   Updated: 2025/10/29 20:52:40 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_sep(char c, const char *seps)
{
	size_t	i;

	i = 0;
	while (seps[i])
	{
		if (c == seps[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_only_digits(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

char	**duplicate_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_valid_identifier(const char *ptr)
{
	if (!ptr)
		return (false);
	if ((ptr[0] == 'F' || ptr[0] == 'C') && (ptr[1] == ' ' || ptr[1] == '\t'))
		return (true);
	if ((ft_strncmp(ptr, "NO", 2) == 0
			|| ft_strncmp(ptr, "SO", 2) == 0
			|| ft_strncmp(ptr, "EA", 2) == 0
			|| ft_strncmp(ptr, "WE", 2) == 0)
		&& (ptr[2] && (ptr[2] == ' ' || ptr[2] == '\t')))
		return (true);
	return (false);
}
