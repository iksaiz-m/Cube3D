/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:47:48 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/06/04 20:55:42 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

int	ismap(char *str)
{
	int		i;
	int		ii;
	char	*check;

	i = 0;
	while (str[i])
		i++;
	ii = i;
	if (i < 5)
		return (mess(2, FORMAT), exit(1), 0);
	i -= 4;
	check = &str[i];
	i = 0;
	while (i <= ii - 4)
	{
		if (!ft_isprint(str[i]))
			return (mess(2, FORMAT2), exit(1), 0);
		i++;
	}
	if (check[0] == '.' && check[1] == 'c' && check[2] == 'u'
		&& check[3] == 'b' && check[4] == '\0')
		return (1);
	else
		return (0);
}

void	fill_directions(t_map *map, int i, char *noendline)
{
	if (i == 0)
	{
		map->northtexture = ft_strdup(noendline);
		mess(1, map->northtexture);
	}
	if (i == 1)
	{
		map->southtexture = ft_strdup(noendline);
		mess(1, map->southtexture);
	}
	if (i == 2)
	{
		map->westtexture = ft_strdup(noendline);
		mess(1, map->westtexture);
	}
	if (i == 3)
	{
		map->easttexture = ft_strdup(noendline);
		mess(1, map->easttexture);
	}
}

void	checkdirections(t_map *map, int i)
{
	/* Aqui voy a meter un split para cada una de las partes y negare un ft_strcmp para ver si es el str que deberia en la primera parte y en la segunda ver si la ruta existe*/
	char	**arr;
	char	*noendline;
	int		fd;

	arr = ft_split(map->directions[i], ' ');
	if (i == 0 && ft_strcmp(arr[0], "NO"))
		return (mess(2, MAPERROR5), exit(1));
	if (i == 1 && ft_strcmp(arr[0], "SO"))
		return (mess(2, MAPERROR6), exit(1));
	if (i == 2 && ft_strcmp(arr[0], "WE"))
		return (mess(2, MAPERROR7), exit(1));
	if (i == 3 && ft_strcmp(arr[0], "EA"))
		return (mess(2, MAPERROR8), exit(1));
	/* Me falta ver si la ruta existe  */
	if (arr[1])
		noendline = noendl_dup(arr[1]);
	else
		return (mess(2, NOPATH), exit(1));
	freeme(arr);
	fill_directions(map, i, noendline);
	/* mess(1, noendline); */
	fd = open(noendline, O_RDONLY);
	ft_memdel(noendline);
	if (fd > 0)
		close(fd);
	else
		return (mess(2, IMG), exit(1));
}

void	directions_bridge(t_map *map, int *i, int fd)
{
	int		ii;
	char	*line;

	ii = 0;
	while (*i < map->ndirections)
	{
		line = get_next_line(fd);
		if (*i == 0 && line == NULL)
			return (mess(2, MAPERROR3), exit(1));
		if (line && ft_strcmp(line, "\n"))
		{
			/* Aqui quiero incluir la linea valida dentro del array de strings de la estructura RECUERDA borrar el salto de linea del final del string cuando le pases la informacion definitiva a Ibon*/
			ii = 0;
			while (line[ii])
			{
				map->directions[*i][ii] = line[ii];
				ii++;
			}
			map->directions[*i][ii] = '\0';
			mess(1, map->directions[*i]);
			/* mess(1, "\n"); */
			checkdirections(map, *i);
			(*i)++;
			ft_memdel(line);
		}
	}
}

// int	checkclosemap(t_map *map, int i, int ii)
// {
// 	int x;

// 	while (map->final_map[i])
// 	{
// 		ii = 0;
// 		while(map->final_map[i][ii])
// 		{
// 			printf("ii: %c\n", map->final_map[i][ii]);
// 			if (map->final_map[i][ii + 1] == '\n' || map->final_map[i][ii + 1] == '\0')
// 				if (map->final_map[i][ii] != '1')
// 				{
// 					printf("\n\n\n\n");
// 					printf("valor ii: %d\n", ii);
// 					return (0);
// 				}
// 			ii++;
// 		}
// 		x = ii;
// 		i++;
// 		printf("valor i: %d\n", i);
// 	}
// 	return (1);
// }

int	check3atributtes(t_map *map)
{
	int	fd;
	int	i;

	fd = open(map->path, O_RDONLY);
	// Tenemos que importar el GNL para poder parsear esto correctamente bueno y la libft tambien
	if (fd > 0)
	{
		mess(1, "Todo el parseo fuciona correctamente\n");
		/* Primero checkeo las 4 direcciones y las meto en un doble punter de la estructura */
		i = 0;
		directions_bridge(map, &i, fd);
		/* Despues lo mismo con los colores del suelo y del cielo */
		i = 0;
		floornceiling(map, &i, fd);
		/* Para terminar meto las lineas de mapa y me aseguro de quitar espacios y ver que los caracteres son correctos REMINDER:El mapa que le tengo que pasar a Ibon es la version con espacios*/
		i = 0;
		mapcpy(map, &i, fd);
		printf("El numero de lineas del mapa es: %d\n", map->row);
		getfinalmap(map);
		if (map->final_map == NULL)
			return (mess(2, MAPERROR), freeme(map->final_map), 0);
		// if (!checkclosemap(map, 0, 0))
		// 	return ((mess(2, MAPERROR4), 0));
		/* Floodfill para asegurarme que el mapa esta correctamente cerrado */
		flood_staff(map);
	}
	else
		return (mess(2, MAPERROR2), 0);
	return (close(fd), 1);
}
