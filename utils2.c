/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:25:13 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/07/08 19:32:08 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

char	*noendl_dup(const char *s1)
{
	size_t		i;
	char		*memory;

	memory = ft_calloc((ft_strlen(s1)), sizeof(char));
	i = 0;
	if (!memory)
		return (0);
	while (i < (ft_strlen(s1) - 1))
	{
		memory[i] = s1[i];
		i++;
	}
	return (memory);
}

void	floornceiling(t_map *map, int *i, int fd)
{
	int	ii;
	char	*line;

	while (*i < map->ncolors)
	{
		line = get_next_line(fd);
		if (line && ft_strcmp(line, "\n"))
		{
			/* Aqui quiero incluir la linea valida dentro del array de strings de la estructura */
			ii = 0;
			while (line[ii])
			{
				map->colors[*i][ii] = line[ii];
				ii++;
			}
			map->colors[*i][ii] = '\0';
			msg(1, map->colors[*i]);
			checkcolors(map, *i);
			(*i)++;
		}
		ft_memdel(line);
	}	
}

void	mapcpy(t_map *map, int *i, int fd)
{
	int	ii;
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strcmp(line, "\n"))
		{
			ii = 0;
			while (line[ii])
			{
				map->map[*i][ii] = line[ii];
				ii++;
			}
			map->map[*i][ii] = '\0';
			(*i)++;
		}
		ft_memdel(line);
	}
	map->row = *i;
}

void	getfinalmap(t_map *map)
{
	int	i;

	i = 0;
	map->final_map = ft_calloc(map->row + 1, sizeof(char *));
	if (!map->final_map)
		return (msg(2, MEMERROR), exit(1));
	while (i < map->row)
	{
		map->final_map[i] = ft_strdup(map->map[i]);
		i++;
	}
	i = 0;
	while (map->final_map[i])
	{
		msg(1, map->final_map[i]);
		i++;
	}

}

// validate_top_bottom(char *map_line)
// {
// 	int	i;

// 	i = -1;
// 	while (map_line[++i])
// 	{
// 		if (map_line[i] != ' ' && map_line[i] != '1')
// 			return (0);
// 	}
// }

// validate_map(t_map *map)
// {
// 	int	i;

// 	i = -1;
// 	while (map->toflood_map[++i])
// 	{
// 		if ((i == 0 || i == map->row - 1)
// 			&& validate_top_bottom(map->toflood_map[i]))
// 			return (1);
// 	}
// }

void	flood_staff(t_map *map)
{
	int	i;

	i = 0;
	map4flood(map);
	if (map->toflood_map == NULL)
		return (msg(2, "Error\n"), freeall(map), exit(1));
	if (checkns(map, 0, 0, 0) != 1)
		return (msg(2, SPOTERROR), freeall(map), exit(1));
	/* Aqui me falta el floodfill y ya en principio acabo el parseo */
	
	// ft_freeme(map->toflood_map);
	// validate_map(map);
	printf("floodmap\n");
	printf("que es x %d\n", map->x);
	printf("que es y %d\n", map->y);

	flood_fill(map, map->toflood_map, map->x, map->y);
	// if (!flood_fill(map->toflood_map, map->x, map->y))
		// return msg(2, MAPERROR4), exit(1);
	while (map->toflood_map[i])
	{
		msg(1, map->toflood_map[i]);
		i++;
	}
}
