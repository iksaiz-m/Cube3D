/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:47:48 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/07/20 21:04:31 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

int	ismap(char *str, t_map *map)
{
	int		i;
	int		ii;
	char	*check;

	i = ft_strlen(str);
	ii = checkmap_name_folders(str);
	if (ii > 0)
	ii++;
	if (i - ii < 5)
		return (msg(2, FORMAT), exit(1), 0);
	check = &str[i - 4];
	check_printable_map_name(str, i, ii);
	if (check[0] == '.' && check[1] == 'c' && check[2] == 'u'
		&& check[3] == 'b' && check[4] == '\0')
		{
			map->name = ft_substr(str, ii, i -4 - ii);
			return (1);
		}
		return (0);
}

void	fill_directions(t_map *map, int i, char *noendline)
{
	if (i == 0)
	{
		map->northtexture = ft_strdup(noendline);
		// msg(1, map->northtexture);
		// printf("\nnorth texture: %s\n", map->northtexture);
	}
	if (i == 1)
	{
		map->southtexture = ft_strdup(noendline);
		// msg(1, map->southtexture);
	}
	if (i == 2)
	{
		map->westtexture = ft_strdup(noendline);
		// msg(1, map->westtexture);
	}
	if (i == 3)
	{
		map->easttexture = ft_strdup(noendline);
		// msg(1, map->easttexture);
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
		return (msg(2, MAPERROR5), freeme(arr), freeall(map), exit(1));
	if (i == 1 && ft_strcmp(arr[0], "SO"))
		return (msg(2, MAPERROR6), freeme(arr), freeall(map), exit(1));
	if (i == 2 && ft_strcmp(arr[0], "WE"))
		return (msg(2, MAPERROR7), freeme(arr), freeall(map), exit(1));
	if (i == 3 && ft_strcmp(arr[0], "EA"))
		return (msg(2, MAPERROR8), freeme(arr), freeall(map), exit(1));
	/* Me falta ver si la ruta existe  */
	if (arr[1])
		noendline = noendl_dup(arr[1]);
	else
		return (msg(2, NOPATH), exit(1));
	freeme(arr);
	fill_directions(map, i, noendline);
	fd = open(noendline, O_RDONLY);
	ft_memdel(noendline);
	if (fd > 0)
		close(fd);
	else
		return (msg(2, IMG), freetextures(map), exit(1));
}
// ft_memdel(map->path), ft_memdel(map->name),
// 			ft_memdel(map->northtexture), ft_memdel(map->easttexture), ft_memdel(map->southtexture), ft_memdel(map->westtexture)

			
// void	directions_bridge(t_map *map, int *i, int fd)
// {
// 	int		ii;
// 	char	*line;

// 	ii = 0;
// 	while (*i < map->ndirections)
// 	{
// 		line = get_next_line(fd);
// 		if (*i == 0 && line == NULL)
// 			return (msg(2, MAPERROR3), exit(1));
// 		if (line && ft_strcmp(line, "\n"))
// 		{
// 			/* Aqui quiero incluir la linea valida dentro del array de strings de la estructura RECUERDA borrar el salto de linea del final del string cuando le pases la informacion definitiva a Ibon*/
// 			ii = 0;
// 			while (line[ii])
// 			{
// 				map->directions[*i][ii] = line[ii];
// 				ii++;
// 			}
// 			map->directions[*i][ii] = '\0';
// 			msg(1, map->directions[*i]);
// 			ft_memdel(line);
// 			checkdirections(map, *i);
// 			(*i)++;
// 		}
// 	}
// }

void	directions_bridge(t_map *map, int i, int fd)
{
	int		ii;
	char	*line;

	ii = 0;
	while (i < map->ndirections)
	{
		line = get_next_line(fd);
		if (i == 0 && line == NULL)
			return (msg(2, MAPERROR3), freetextures(map), exit(1));
		if (line && ft_strcmp(line, "\n"))
		{
			/* Aqui quiero incluir la linea valida dentro del array de strings de la estructura RECUERDA borrar el salto de linea del final del string cuando le pases la informacion definitiva a Ibon*/
			ii = 0;
			while (line[ii])
			{
				map->directions[i][ii] = line[ii];
				ii++;
			}
			map->directions[i][ii] = '\0';
			msg(1, map->directions[i]);
			ft_memdel(line);
			checkdirections(map, i);
			(i)++;
		}
		else
			ft_memdel(line);
	}
}
int	fill_atributes2(t_map *map, char *noendline, char *arr0)
{
	if (!ft_strcmp(arr0, "F") && !map->floorcolor)
	{
		msg(1, "floor\n");
		return (map->floorcolor = ft_strdup(noendline), 0);
	}
	if (!ft_strcmp(arr0, "C") && !map->ceilingcolor)
	{
		msg(1, "ceiling\n");
		return (map->ceilingcolor = ft_strdup(noendline), 0);
	}
	return (msg(2, MAP_ARG_DUP), 1);
}

int	fill_atributes(t_map *map, char *noendline, char *arr0)
{
	if (!ft_strcmp(arr0, "NO") && !map->northtexture)
	{
		msg(1, "north\n");
		return (map->northtexture = ft_strdup(noendline), 0);
	}
	if (!ft_strcmp(arr0, "SO") && !map->southtexture)
	{
		msg(1, "south\n");
		return	(map->southtexture = ft_strdup(noendline), 0);
	}
	if (!ft_strcmp(arr0, "WE") && !map->westtexture)
	{
		msg(1, "west\n");
			return (map->westtexture = ft_strdup(noendline),0 );
	}
	if (!ft_strcmp(arr0, "EA") && !map->easttexture)
	{		
		msg(1, "east\n");
		return (map->easttexture = ft_strdup(noendline), 0);
	}
	return (msg(2, MAP_ARG_DUP), 1);
}

int	asign_directions(t_map *map, char **arr)
{
	char	*noendline;
	int		fd;

	if (arr[1])
		noendline = noendl_dup(arr[1]);
	else
		return (msg(2, NOPATH), 1);
	if (noendline)
		if (fill_atributes(map, noendline, arr[0]))
			return (ft_memdel(noendline), 1);
	fd = open(noendline, O_RDONLY);
	ft_memdel(noendline);
	if (fd > 0)
		close(fd);
	else
		return (msg(2, IMG), 1);
	return (0);
}

int	asign_atributes(t_map *map, char **arr)
{
	char	*noendline;
	char	**arr2;

	if (arr[1])
		noendline = noendl_dup(arr[1]);
	else
		return (msg(2, NOPATH), 1);
	if (noendline)
		if (fill_atributes2(map, noendline, arr[0]))
			return (ft_memdel(noendline), 1);
	arr2 = ft_split(noendline, ',');
	if (!arr2)
		return (ft_memdel(noendline), 1);
	ft_memdel(noendline);
	if (isvalidnum(arr2))
		return (freeme(arr2), 1);
	freeme(arr2);
	return (0);
}


// fd = open(noendline, O_RDONLY);
// ft_memdel(noendline);
// if (fd > 0)
// 	close(fd);
// else
// 	return (msg(2, IMG), freetextures(map), exit(1));

int	check_array_for_atributes(t_map * map, char **arr)
{
	if (ft_strcmp(arr[0], "NO") && ft_strcmp(arr[0], "SO") &&
		ft_strcmp(arr[0], "WE") && ft_strcmp(arr[0], "EA") &&
		ft_strcmp(arr[0], "F") && ft_strcmp(arr[0], "C"))
		return (msg(2, MAPERROR10), 1);
	if (!ft_strcmp(arr[0], "F") || !ft_strcmp(arr[0], "C"))
	{
		if (asign_atributes(map, arr))
			return (1);
	}
	else
	{
		if (asign_directions(map, arr))
			return (1);
	}
		// return (msg(2, MAPERROR5), freeme(arr), freeall(map), exit(1));
	// if (ft_strcmp(arr[0], "SO"))
	// 	return (msg(2, MAPERROR6), freeme(arr), freeall(map), exit(1));
	// if (ft_strcmp(arr[0], "WE"))
	// 	return (msg(2, MAPERROR7), freeme(arr), freeall(map), exit(1));
	// if (ft_strcmp(arr[0], "EA"))
	// 	return (msg(2, MAPERROR8), freeme(arr), freeall(map), exit(1));
	return (0);
}

void	checkatributes(t_map *map, char *line)
{
	char	**arr;

	arr = ft_split(line, ' ');
	if (!arr)
		return (msg(2, MAPERROR9), ft_memdel(line), freeall(map), exit(1));
	if (check_array_for_atributes(map, arr))
		return (freeme(arr), ft_memdel(line), freeall(map), exit(1));

	freeme(arr);
	// if (ft_strcmp(arr[0], "NO"))
	// 	return (msg(2, MAPERROR5), freeme(arr), freeall(map), exit(1));
	// if (ft_strcmp(arr[0], "SO"))
	// 	return (msg(2, MAPERROR6), freeme(arr), freeall(map), exit(1));
	// if (ft_strcmp(arr[0], "WE"))
	// 	return (msg(2, MAPERROR7), freeme(arr), freeall(map), exit(1));
	// if (ft_strcmp(arr[0], "EA"))
	// 	return (msg(2, MAPERROR8), freeme(arr), freeall(map), exit(1));
}

int	all_atributes_asigned(t_map *map)
{
	if (map->northtexture && map->southtexture && map->easttexture
		&& map->westtexture && map->floorcolor && map->ceilingcolor)
		return (1);
	else
		return (0);
}
void	parsefloorceilingdirections(t_map *map, int i, int fd)
{
	char	*line;
	char 	*null;

	null = "\n";
	ft_printf("null string---> %s\n", null);
	while (i)
	{
		line = get_next_line(fd);
		if (i == 1 && line == NULL)
			return (msg(2, MAPERROR3), freetextures(map), exit(1));
		printf("line---> %s", line);
		if (all_atributes_asigned(map))
		{
			return (ft_memdel(line));
		}
		if (line && ft_strcmp(line, "\n"))
			checkatributes(map, line);
		if (line == NULL)
			break ;
		ft_memdel(line);
		i++;
	}
}

int	check3atributtes(t_map *map)
{
	int	fd;
	int	i;

	fd = open(map->path, O_RDONLY);
	// Tenemos que importar el GNL para poder parsear esto correctamente bueno y la libft tambien
	if (fd > 0)
	{
		msg(1, "Todo el parseo funciona correctamente\n");
		/* Primero checkeo las 4 direcciones y las meto en un doble punter de la estructura */
		i = 1;
		parsefloorceilingdirections(map, i, fd);
		// directions_bridge(map, i, fd);
		/* Despues lo mismo con los colores del suelo y del cielo */
		i = 0;
		// floornceiling(map, i, fd);
		/* Para terminar meto las lineas de mapa y me aseguro de quitar espacios y ver que los caracteres son correctos REMINDER:El mapa que le tengo que pasar a Ibon es la version con espacios*/
		i = 0;
		mapcpy(map, &i, fd);
		printf("El numero de lineas del mapa es: %d\n", map->row);
		getfinalmap(map);
		if (map->final_map == NULL)
			return (msg(2, MAPERROR), freeme(map->final_map), 0);
		/* Floodfill para asegurarme que el mapa esta correctamente cerrado */
		flood_staff(map);
	}
	else
		return (msg(2, MAPERROR2), 0);
	return (close(fd), 1);
}
