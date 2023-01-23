/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:05:17 by lsun              #+#    #+#             */
/*   Updated: 2023/01/24 00:09:26 by linlinsun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

#ifndef WIN_SIZE_X
# define WIN_SIZE_X 1920
#endif

#ifndef WIN_SIZE_Y
# define WIN_SIZE_Y 1080
#endif

typedef struct s_map
{
	int		fd;
	int		size_x;
	int		size_y;
	char	*line;
	char** point;
	char	**line_split;
	char	*map_1d;
	char	**map_2d;
	int		**map_int;
	int		offset_x;
	int		offset_y;
	int		zoom_z;
	int		zoom;
}			t_map;

typedef struct s_pos
{
	int	x;
	int	y;
	int z;
}			t_pos;

typedef struct s_line
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;
}	t_line;
typedef struct s_img
{
	void		*img_ptr;
	int			*addr;
	int			line_length;
	int			bits_per_pixel;
	int			endian;
}				t_img;

typedef struct s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	*input;
	t_img	*data;
}			t_fdf;

t_map	ft_create_2d_int(t_map input);
int	ft_how_many(char *str, char c);
t_map	ft_map_init(char **argv, t_map input);
t_map	ft_read_map(char **argv, t_map input);
void ft_print_2D_int(t_map input);
t_map	map_handling(int argc, char **argv, t_map input);

#endif
