/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:05:17 by lsun              #+#    #+#             */
/*   Updated: 2023/01/31 15:25:06 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/ft_printf.h"
# include "libft/get_next_line.h"
# include "libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# ifndef WIN_SIZE_X
#  define WIN_SIZE_X 1920
# endif

# ifndef WIN_SIZE_Y
#  define WIN_SIZE_Y 1080
# endif

typedef struct s_map
{
	int		fd;
	int		size_x;
	int		size_y;
	char	*line;
	char	**point;
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
	int		x;
	int		y;
	int		z;
}			t_pos;

typedef struct s_line
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
}			t_line;

typedef struct s_img
{
	void	*img_ptr;
	int		*addr;
	int		line_length;
	int		bits_per_pixel;
	int		endian;
}			t_img;

typedef struct s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	*input;
	t_img	*img;
	int		i;
	int		j;
	int		k;
}			t_fdf;

int			ft_create_2d_int(t_fdf *fdf);
int			ft_how_many(char *str, char c);
void		ft_map_init(t_fdf *fdf);
int			ft_read_map(char **argv, t_fdf *fdf);
int			ft_print_2D_int(t_map *input);
int			map_handling(int argc, char **argv, t_fdf *fdf);

void		zoom_init(t_fdf *fdf);

void		register_hooks(t_fdf *fdf);
int			key_hook(int key, t_fdf *fdf);
int			mouse_hook(int button, int x, int y, t_fdf *fdf);
int			close_widow(t_fdf *fdf);

int			image_handeling(t_fdf *fdf);
int			refresh_image(t_fdf *fdf);

void		clean(t_fdf *fdf);
void		free_int(int **input, int height);
void		free_char(char **input);

int			which_color(t_pos pos1, t_pos pos2);
t_pos		isometric(t_pos pos);
int			draw(t_fdf *fdf);
void		my_mlx_pixel_put(t_img *data, int x, int y, int color_code);

int			ft_abs(int a);
t_line		line_init(t_pos pos0, t_pos pos1);
int			bresenham_line(t_pos pos0, t_pos pos1, t_fdf *fdf, int color_code);
t_pos		pos_init(int x, int y, int z, t_pos pos);

t_pos		apply_zoom(t_pos pos, t_fdf *fdf);
t_pos		conversion(t_pos pos, t_fdf *fdf);

#endif
