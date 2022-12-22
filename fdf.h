/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:05:17 by lsun              #+#    #+#             */
/*   Updated: 2022/12/22 17:41:25 by lsun             ###   ########.fr       */
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
	void	*image_ptr;
}			t_fdf;

typedef struct s_line
{
	int		x1;
	int		y1;
	int		x2;
	int		y2;
}			t_line;

typedef struct s_map
{
	int		fd;
	int		size_x;
	int		size_y;
	char	*line;
	char	**line_split;
	char	*map_1d;
	char	**map_2d;
	int		**map_int;
}			t_map;

#endif
