/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:39:54 by mzutter           #+#    #+#             */
/*   Updated: 2025/10/29 22:54:17 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	process_line(char *line, t_parse **parse, t_list **map_lines,
						bool *map_started)
{
	int		error_code;
	int		i;
	char	**splitted;

	error_code = 0;
	i = 0;
	while (line[i] && is_whitespace(line[i]))
		i++;
	if (line[i] == 0 && *map_started == false)
		return (0);
	if ((line[i] == '1' || line[i] == '0') && *map_started == false)
		*map_started = true;
	if (*map_started == true)
	{
		if (line[i] == 0)
			return (2);
		return (ft_lstadd_back(map_lines, ft_lstnew(ft_strdup(line))), 0);
	}
	if (!is_valid_identifier(&line[i]))
		return (ft_putstr_fd("process_line:invalid id\n", 2), 1);
	splitted = ft_new_split(line, " \t\n,");
	if (!splitted)
		return (ft_putstr_fd("process_line:malloc error\n", 2), 1);
	return (fill_parse_struct(splitted, parse));
}

static int	read_map_lines(int fd, t_parse *parse, t_list **map_lines)
{
	char	*line;
	bool	map_started;
	int		error_code;

	map_started = false;
	line = get_next_line(fd);
	while (line)
	{
		error_code = process_line(line, &parse, map_lines, &map_started);
		if (error_code == 1)
			return (free(line), ft_putstr_fd("rdmaplines:malloc err\n", 2), 1);
		if (error_code == 2)
		{
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	map_lst_to_char_array(t_list **map_lines, t_parse **parse)
{
	int		size;
	int		i;
	size_t	len;
	t_list	*tmp;

	i = 0;
	size = ft_lstsize(*map_lines);
	(*parse)->map = (char **)malloc(sizeof(char *) * (size + 1));
	tmp = *map_lines;
	len = ft_strlen((*map_lines)->content);
	while (tmp)
	{
		if (tmp->content == NULL || ((char *)tmp->content)[0] == 0)
			return (ft_putstr_fd("map_to_array: empty line in the map", 2), 1);
		if (ft_strlen(tmp->content) > len)
			len = ft_strlen(tmp->content);
		(*parse)->map[i] = ft_strdup(tmp->content);
		if ((*parse)->map[i] == NULL)
			return (ft_putstr_fd("map_to_array: malloc error", 2), 1);
		i++;
		tmp = tmp->next;
	}
	(*parse)->map[i] = NULL;
	(*parse)->map_width = len;
	return (ft_lstclear(map_lines, free), 0);
}

int	replace_spaces_and_find_start(t_parse *parse)
{
	int		y;
	int		x;
	int		start_count;
	char	c;

	start_count = 0;
	y = -1;
	while (parse->map[++y])
	{
		x = -1;
		while (parse->map[y][++x])
		{
			c = parse->map[y][x];
			if (c == ' ')
				parse->map[y][x] = '0';
			else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				start_count++;
		}
	}
	if (start_count != 1)
		return (ft_putstr_fd("findstart:invalid number of start pos\n", 2), 1);
	return (0);
}

int	read_map(char *filename, t_parse *parse)
{
	t_list	*map_lines;
	int		fd;

	map_lines = NULL;
	if (!filename || !parse)
		return (ft_putstr_fd("read_map:nullptr dereferenced\n", 2), 1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("read_map:fd < 0", 2), 1);
	if (read_map_lines(fd, parse, &map_lines))
	{
		ft_putstr_fd("read_map: read_map_lines returned an error\n", 2);
		close(fd);
		return (1);
	}
	close (fd);
	if (map_lst_to_char_array(&map_lines, &parse))
		return (1);
	if (replace_spaces_and_find_start(parse))
		return (1);
	return (0);
}
