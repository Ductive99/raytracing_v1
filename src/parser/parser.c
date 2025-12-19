/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 02:21:20 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 22:52:24 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <sys/stat.h>

static t_parse_status	parse_line(char *line, t_scene *scene);
static t_parse_status	parse_object_wrapper(char *line,
							t_parse_status (*parser_func)(char **, t_scene *),
							t_scene *scene);

/**
 * parse_scene - reads and parses scene file
 *
 * @filename: name of the file to parse
 *
 * Return: 1 on success, 0 on failure
 */
int	parse_scene(char *filename, t_scene *scene)
{
	int			fd;
	char		*line;
	struct stat	g_st;

	if (stat(filename, &g_st) == 0 && S_ISDIR(g_st.st_mode))
		return (print_err("Cannot open directory"), PARSE_ERROR);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Failed to open file"), PARSE_ERROR);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (parse_line(line, scene) == PARSE_ERROR)
			return (free(line), get_next_line(-1), close(fd), PARSE_ERROR);
		free(line);
	}
	get_next_line(-1);
	close(fd);
	if (!scene->has_camera)
		return (print_err("Missing camera (C) in scene"), PARSE_ERROR);
	if (!scene->has_ambient)
		return (print_err("Missing ambient light (A) in scene"), PARSE_ERROR);
	return (PARSE_SUCCESS);
}

static t_parse_status	parse_line(char *line, t_scene *scene)
{
	static const t_object_parser	parsers[] = {{"A", 1, parse_ambient}, {"C",
		1, parse_camera}, {"L", 1, parse_light}, {"sp", 2, parse_sphere},
	{"pl", 2, parse_plane}, {"cy", 2, parse_cylinder}, {"co", 2,
		parse_cone}, {NULL, 0, NULL}};
	int								i;

	if (!line[0] || line[0] == '\n')
		return (PARSE_SUCCESS);
	i = 0;
	while (parsers[i].id)
	{
		if (ft_strncmp(line, parsers[i].id, parsers[i].id_len) == 0)
			return (parse_object_wrapper(line, parsers[i].parser_func, scene));
		i++;
	}
	print_err("Line format");
	return (PARSE_ERROR);
}

static t_parse_status	parse_object_wrapper(char *line,
		t_parse_status (*parser_func)(char **, t_scene *), t_scene *scene)
{
	char			**split;
	t_parse_status	status;

	split = ft_split(line, " \t\n");
	if (!split)
		return (PARSE_ERROR);
	status = parser_func(split, scene);
	free_split(split);
	return (status);
}
