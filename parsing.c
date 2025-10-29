#include "cub3d.h"

void	fill_color_int_array(char **splitted, t_parse **parse)
{
	if (splitted[0][0] == 'C' && is_only_digits(splitted[1])
		&& is_only_digits(splitted[2]) && is_only_digits(splitted[3]))
	{
		(*parse)->ceiling_color[0] = ft_atoi(splitted[1]);
		(*parse)->ceiling_color[1] = ft_atoi(splitted[2]);
		(*parse)->ceiling_color[2] = ft_atoi(splitted[3]);
	}
	if (splitted[0][0] == 'F' && is_only_digits(splitted[1])
		&& is_only_digits(splitted[2])  && is_only_digits(splitted[3]) )
	{
		(*parse)->floor_color[0] = ft_atoi(splitted[1]);
		(*parse)->floor_color[1] = ft_atoi(splitted[2]);
		(*parse)->floor_color[2] = ft_atoi(splitted[3]);
	}
	return ;
}

static int	fill_texture_fields(char **splitted, t_parse **parse)
{
	if (ft_strncmp(splitted[0], "NO", 3) == 0)
	{
		(*parse)->texture_north = ft_strdup(splitted[1]);
		if (!(*parse)->texture_north)
			return (ft_putstr_fd("Err:malloc failed texture_north\n", 2), 1);
	}
	else if (ft_strncmp(splitted[0], "SO", 3) == 0)
	{
		(*parse)->texture_south = ft_strdup(splitted[1]);
		if (!(*parse)->texture_south)
			return (ft_putstr_fd("Err:malloc failed texture_south\n", 2), 1);
	}
	else if (ft_strncmp(splitted[0], "WE", 3) == 0)
	{
		(*parse)->texture_west = ft_strdup(splitted[1]);
		if (!(*parse)->texture_west)
			return (ft_putstr_fd("Err:malloc failed texture_west\n", 2), 1);
	}
	else if (ft_strncmp(splitted[0], "EA", 3) == 0)
	{
		(*parse)->texture_east = ft_strdup(splitted[1]);
		if (!(*parse)->texture_east)
			return (ft_putstr_fd("Err:malloc failed texture_east\n", 2), 1);
	}
	return (0);
}


int	fill_parse_struct(char **splitted, t_parse **parse)
{
	int	size;
	int	err;

	if (!splitted || !splitted[0])
		return (ft_putstr_fd("fill_parse_struct:failed to init arr\n", 2), 1);
	size = array_size(splitted);
	err = 0;
	if (size == 2)
		err = fill_texture_fields(splitted, parse);
	else if ((splitted[0][0] == 'F' || splitted[0][0] == 'C') && size == 4)
		fill_color_int_array(splitted, parse);
	ft_free_str_array(splitted);
	return (err);
}

static int	process_line(char *line, t_parse **parse, t_list **map_lines, bool *map_started)
{
	int		error_code;
	int		i;
	char	**splitted;


	error_code = 0;
	i = 0;
	printf("debug:content of line is: %s\n", line);
	while (line[i] && is_whitespace(line[i]))
		i++;
	if (line[i] == 0 && *map_started == false)
		return(0);
	if ((line[i] == '1' || line[i] == '0') && *map_started == false)
		*map_started = true;
	if (*map_started == true)
	{
		if (line[i] == 0)
			return(2);
		return (ft_lstadd_back(map_lines, ft_lstnew(ft_strdup(line))), 0);
	}
	if (!is_valid_identifier(&line[i]))
		return (ft_putstr_fd("process_line:invalid id\n", 2), 1);
	splitted = ft_new_split(line, " \t\n,");
	if (!splitted)
		return(ft_putstr_fd("process_line:malloc error\n", 2), 1);
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
			break;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	map_lst_to_char_array(t_list **map_lines, t_parse **parse)
{
	int	size;
	int	i;
	t_list	*tmp;

	i = 0;
	size = ft_lstsize(*map_lines);
	(*parse)->map = (char **)malloc(sizeof(char *) * (size + 1));
	tmp = *map_lines;
	while (tmp)
	{
		if (tmp->content == NULL || ((char *)tmp->content)[0] == 0)
			return(ft_putstr_fd("map_to_array: empty line in the map", 2), 1);
		(*parse)->map[i] = ft_strdup(tmp->content);
		if ((*parse)->map[i] == NULL)
			return (ft_putstr_fd("map_to_array: malloc error", 2), 1);
		i++;
		tmp = tmp->next;
	}
	ft_lstclear(map_lines, free);
	(*parse)->map[i] = NULL;
	return(0);
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
		return(ft_putstr_fd("read_map:fd < 0", 2), 1);
	if (read_map_lines(fd, parse, &map_lines))
	{
		ft_putstr_fd("read_map: read_map_lines returned an error\n", 2);
		close(fd);
		return (1);
	}
	close (fd);
	map_lst_to_char_array(&map_lines, &parse);
	// if (finalize_map(parse, map_lines))
	// 	return(ft_putstr_fd("read_map:finalizemap returned an error\n", 2), 1);
	return (0);
}
