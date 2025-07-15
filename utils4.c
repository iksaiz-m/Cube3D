/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:53:31 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/07/15 21:18:11 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3.h"

void	isrgbable(char **arr2)
{
	int	i;

	i = 0;
	while (arr2[i])
	{
		if (ft_atoi(arr2[i]) < 0 || ft_atoi(arr2[i]) > 255)
			return (msg(2, RGBERROR2), exit(1));
		i++;
	}
	msg(1, "\nTodo esta funcionando muy bien por lo visto :)\n");
}

void	isvalidnum(char **arr2)
{
	int	i;
	int	ii;

	i = 0;
	/* Primero mirare el numero de argumentos para asegurarme de que son tres numeros */
	while (arr2[i])
		i++;
	if (i != 3)
		return (msg(2, RGBERROR), exit(1));
	/* Ahora tendre que comprobar que todos los caracteres son numeros */
	i = 0;
	while (arr2[i])
	{
		ii = 0;
		while (arr2[i][ii])
		{
			if (!ft_isdigit(arr2[i][ii]))
				return (msg(2, FORMAT3), exit(1));
			ii++;
		}
		i++;
	}
	/* Aqui mirare que los numeros estan entre el 0 y el 255 ambos incluidos con el atoi*/
	isrgbable(arr2);
}

void	checkcolors(t_map *map, int i)
{
	char	**arr;
	char	**arr2;
	char	*noendline;

	arr = ft_split(map->colors[i], ' ');
	if (i == 0 && ft_strcmp(arr[0], "F"))
		return (msg(2, FLOOR), freeme(arr), freetextures(map), exit(1));
	if (i == 1 && ft_strcmp(arr[0], "C"))
		return (msg(2, CEILING), freeme(arr), freetextures(map), exit(1));
	noendline = noendl_dup(arr[1]);
	freeme(arr);
	if (i == 0)
	{
		map->floorcolor = ft_strdup(noendline);
		msg(1, map->floorcolor);
	}
	if (i == 1)
	{
		map->ceilingcolor = ft_strdup(noendline);
		msg(1, map->ceilingcolor);
	}
	arr2 = ft_split(noendline, ',');
	ft_memdel(noendline);
	isvalidnum(arr2);
	freeme(arr2);
}

int	ft_is_nswe(char	c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '1'
		|| c == '0' || c == ' ' || c == '	' || c == '\n')
		return (1);
	return (0);
}

void	flood_fill(t_map *mapa, char **map, int x, int y)
{
	if (map[x][y] == ' ' || map[x][y] == '\n'|| map[x][y] == '	')
		return (msg(2, MAPERROR4), freeall(mapa), exit(1));
	if (map[x][y] && map[x][y] != '1')
	{
		if (map[x][y] != 1)
			map[x][y] = '1';
		flood_fill(mapa, map, x + 1, y);
		flood_fill(mapa, map, x - 1, y);
		flood_fill(mapa, map, x, y + 1);
		flood_fill(mapa, map, x, y - 1);
	}
}

// void	error(void)
// {
// 	ft_printf("Error\n");
// 	exit(1);
// }
