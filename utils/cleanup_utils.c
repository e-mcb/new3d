/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:39:36 by mzutter           #+#    #+#             */
/*   Updated: 2025/10/29 20:52:59 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_parse(t_parse *parse)
{
	int	i;

	i = 0;
	if (!parse)
		return ;
	free(parse->texture_north);
	free(parse->texture_south);
	free(parse->texture_west);
	free(parse->texture_east);
	if (parse->map)
	{
		i = 0;
		while (parse->map[i] != NULL)
		{
			free(parse->map[i]);
			i++;
		}
		free(parse->map);
		parse->map = NULL;
	}
}
