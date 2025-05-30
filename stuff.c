/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:38:04 by nkrasimi          #+#    #+#             */
/*   Updated: 2025/05/30 17:32:03 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "cub3.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/* Estas 3 funciones son para parsear el map */
int	is_valid_line(char *map_line)
{
	int	i;

	i = 0;
	if (map_line[i] != '1')
		return (0);
	while (map_line[i])
	{
		if (map_line[i] != '1' && map_line[i] != '0' && map_line[i] != 'N')
			return (0);
		i++;
	}
	i -= 1;
	if (map_line[i] != '1')
		return (0);
	return (1);
}

void	remove_spaces(char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	if (len == 0)
		mess(2, "Error. Empty line\n");
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

// Con esta funcion sabremos si realmente se esta leyendo y guardando bien el mapa
void	print_matrix(char **matrix)
{
	int i;
	int ii; 

	i = 0;
	while (matrix[i])
	{   
		ii = 0;
		while (matrix[i][ii])
		{
			 write(1, &matrix[i][ii], 1);
			ii++;
		}
		i++;
	}
}   

void	ft_memdel(void *ptr)
{
	if (ptr != 0)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	freeme(char **memory)
{
	int	i;

	i = 0;
	while (memory[i])
	{
		ft_memdel(memory[i]);
		i++;
	}
	ft_memdel(memory);
}

/* int ismap(char *str) */
/* { */
/* 	int	i; */
/* 	char	*check; */

/* 	i = 0; */
/* 	while (str[i]) */
/* 		i++; */
/* 	if (i < 5) */
/* 		mess(2, "Tiene que tener algo delante de la extension .cub\n"), exit(1); */
/* 	i -= 5; */
/* 	check = &str[i]; */
/* 	if (!ft_isprint(check[0])) */
/* 		mess(2, "El caracter que va delante de la extension .cub tiene que ser imprimible\n"), exit(1); */
/* 	if (check[1] == '.' && check[2] == 'c' && check[3] == 'u' && */
/* 	check[4] == 'b' && check[5] == '\0') */
/* 		return (1); */
/* 	else */
/* 		return (0); */
/* } */


void	init_values(t_map *mapa)
{
	mapa->ndirections = 4;
	mapa->ncolors = 2;
}

void	freeall(t_map *map)
{
	ft_memdel(map->path);
	freeme(map->toflood_map);
	freeme(map->final_map);
	ft_memdel(map->northtexture);
	ft_memdel(map->easttexture);
	ft_memdel(map->westtexture);
	ft_memdel(map->southtexture);
	ft_memdel(map->floorcolor);
	ft_memdel(map->ceilingcolor);
}

int main (int ac, char **av)
{
	/* size_t	i; */
	t_map	mapa;

	if (ac != 2)
		return (mess(1, ARGERROR), 1);
	if (av[1][0] == '\0')
		return (mess(1, ARGERROR2), 1);

	init_values(&mapa);
	/* i = 0; */
	/* Vamos a ver Ibon aqui tenemos que hacer el parseo de los argumentos por terminal */

	/* Leer el mapa y comprobar que todo esta bien con el floodfill */
	if (ismap(av[1]) == 1)
    {
		mapa.path = ft_strdup(av[1]);
		if (check3atributtes(&mapa) == 0)
			return (mess(2, "Saliendo...\n"), 1);
	}
	else
		return (mess(1, ARGERROR3), 1);
	/* Raycasting */
	/* Por ahora vamos a dejar el resto para luego */
	
	return (freeall(&mapa), 0);
}
