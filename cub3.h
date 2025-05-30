/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:33:46 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/05/30 17:19:41 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3_H
# define CUB3_H

# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <math.h>

# define RED 0xFF0000
# define GREEN 0xFF00
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define YELLOW 0xFFFF00
# define ARGERROR "Debes introducir dos argumentos por terminal\n"
# define ARGERROR2 "Argumento vacio, especifica un mapa\n"
# define ARGERROR3 "El mapa tiene que acabar en .cub\n"
# define MAPERROR "Something went wrong copying the map\n"
# define MAPERROR2 "El mapa no se ha podido abrir\n"
# define MAPERROR3 "Error: Empty map\n"
# define MAPERROR4 "North word is wrong\n"
# define MAPERROR5 "South word is wrong\n"
# define MAPERROR6 "West word is wrong\n"
# define MAPERROR7 "East word is wrong\n"
# define IMG "The image of one of the directions was not found in the system\n"
# define FORMAT "Lo que van delante de .cub tiene que ser imprimible\n"
# define FORMAT2 "Tiene que tener algo delante de la extension .cub\n"
# define FORMAT3 "There is some non digit character\n"
# define SPOTERROR "Characters positions is initialized in more than one spot\n"
# define MEMERROR "Memory allocation failed\n"
# define RGBERROR "There aren't three arguments after spliting\n"
# define RGBERROR2 "Some introduced number is not valid for rgb standard\n"
# define FLOOR "Floor character wrong\n"
# define CEILING "Ceiling character wrong\n"
# define NOPATH "No path to file to open\n"
# define WIDTH 600
# define HEIGHT 600

typedef struct s_complex
{
	double	x;
	double	y;
}				t_complex;

typedef struct s_img
{
	void	*img_ptr;
	void	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_cube
{
	char	*name;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	double	zoom;
	double	escape_value;
	int		iterations;
	int		color;
	double	changed_x;
	double	changed_y;
	double	julia_x;
	double	julia_y;
}	t_cube;

typedef struct s_map
{
	char	directions[4][200];
	int		ndirections;
	char	*northtexture;
	char	*southtexture;
	char	*westtexture;
	char	*easttexture;
	char	colors[2][200];
	int		ncolors;
	char	*floorcolor;
	char	*ceilingcolor;
	char	map[2000][2000];
	int		nmap;
	char	*path;
	char	**final_map;
	char	**toflood_map;
	char	**spaceless_map;
	int		x;
	int		y;
	void	*mlx;
	void	*mlx_win;
}		t_map;

t_complex	square_complex(t_complex z);
t_complex	sum_complex(t_complex z1, t_complex z2);
double		atod(char *s);

double		escale(double element, double new_min,
				double new_max, double old_max);
void		fractal_init(t_cube *fractal);
void		fractal_render(t_cube *fractal);
void		handle_pixel(int x, int y, t_cube *fractal);

int			closewindow(t_cube *fractal);
int			handle_key(int keysym, t_cube *fractal);
int			handle_mouse(int button, int x, int y, t_cube *fractal);
int			track_julia(int x, int y, t_cube *fractal);

void		data_init(t_cube *fractal);
void		fractal_init(t_cube *fractal);
int			ft_strcmp(char *s1, char *s2);
//freemem
void		ft_memdel(void *ptr);
void		freeme(char **memory);

//utils.c
int			ismap(char *str);
void		directions_bridge(t_map *map, int *i, int fd);
int			check3atributtes(t_map *map);
void		checkdirections(t_map *map, int i);
void		fill_directions(t_map *map, int i, char *noendline);

//utils2.c
char		*noendl_dup(const char *s1);
void		floornceiling(t_map *map, int *i, int fd);
void		mapcpy(t_map *map, int *i, int fd);
void		getfinalmap(t_map *map);
void		flood_staff(t_map *map);

//utils3.c
void		map4flood(t_map *map);
int			checkns(t_map *map);
void		add_values(t_map *map, int i, int ii);
void		mess(int fd, char *str);

//utils4.c
void		checkcolors(t_map *map, int i);
void		isvalidnum(char **arr2);
void		isrgbable(char **arr2);

#endif