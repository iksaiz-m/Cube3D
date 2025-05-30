/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:25:13 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/05/30 17:19:38 by iksaiz-m         ###   ########.fr       */
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
	// memory[i] = '\0';
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
			mess(1, map->colors[*i]);
			/* mess(1, "\n"); */
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
			/* mess(1, map->map[*i]); */
			(*i)++;
		}
		ft_memdel(line);
	}
	/* map->map[*i] = NULL; */
	map->nmap = *i;
}

void	getfinalmap(t_map *map)
{
	int	i;

	i = 0;
	map->final_map = ft_calloc(map->nmap + 1, sizeof(char *));
	// map->final_map = malloc((sizeof(char *) * map->nmap) + 1);
	if (!map->final_map)
		return (mess(2, MEMERROR), exit(1));
	while (i < map->nmap)
	{
		map->final_map[i] = ft_strdup(map->map[i]);
		i++;
	}
	// map->final_map[i] = NULL;
	i = 0;
	while (map->final_map[i])
	{
		mess(1, map->final_map[i]);
		i++;
	}
}

void	flood_staff(t_map *map)
{
	map4flood(map);
	if (map->toflood_map == NULL)
		return (mess(2, "Error\n"), freeme(map->toflood_map), exit(1));
	if (checkns(map) != 1)
		return (mess(2, SPOTERROR), exit(1));
	/* Aqui me falta el floodfill y ya en principio acabo el parseo */
	// ft_freeme(map->toflood_map);
}
