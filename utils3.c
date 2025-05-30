/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:30:31 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/05/30 17:22:14 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	map4flood(t_map *map)
{
	int	i;

	i = 0;
	mess(2, "Let's start the map to flood it\n");
	map->toflood_map = ft_calloc((map->nmap) + 1, sizeof(char *));
	if (!map->toflood_map)
		return (mess(2, MEMERROR), exit(1));
	while (i < map->nmap)
	{
		map->toflood_map[i] = ft_strdup(map->map[i]);
		i++;
	}
	i = 0;
	while (map->toflood_map[i])
	{
		mess(1, map->toflood_map[i]);
		i++;
	}
}

int	checkns(t_map *map)
{
	int	i;
	int	ii;
	int	count;

	i = 0;
	count = 0;
	while (map->toflood_map[i])
	{
		ii = 0;
		while (map->toflood_map[i][ii])
		{
			if (map->toflood_map[i][ii] == 'N' || map->toflood_map[i][ii] == 'S'
				|| map->toflood_map[i][ii] == 'E' || map->toflood_map[i][ii] == 'W')
			{
				if (count == 0)
					add_values(map, i, ii);
				count++;
			}
			ii++;
		}
		i++;
	}
	return (count);
}

void	add_values(t_map *map, int i, int ii)
{
	map->x = i;
	map->y = ii;
}

void	mess(int fd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}
