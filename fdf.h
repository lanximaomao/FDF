/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:05:17 by lsun              #+#    #+#             */
/*   Updated: 2023/01/13 13:40:31 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	struct s_map *input;
}			t_fdf;

typedef struct s_line
{
	int		x1;
	int		y1;
	int 	z1;
	int		x2;
	int		y2;
	int		z2;
}			t_line;

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
}			t_map;

t_map	ft_create_2d_int(t_map input);
int	ft_how_many(char *str, char c);
t_map	ft_map_init(char **argv, t_map input);
t_map	ft_read_map(char **argv, t_map input);
void ft_print_2D_int(t_map input);
t_map	map_handling(int argc, char **argv, t_map input);

#endif
