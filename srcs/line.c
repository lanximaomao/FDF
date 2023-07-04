/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:56:52 by lsun              #+#    #+#             */
/*   Updated: 2023/07/04 17:31:56 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
** 1) 17 is the mouse event code means for close button;
** 2) https://stackoverflow.com/questions/14087274/difference-between-and-in-c
*/

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

t_line	line_init(t_pos pos0, t_pos pos1)
{
	t_line	line;

	line.dx = ft_abs(pos1.x - pos0.x);
	if (pos0.x < pos1.x)
		line.sx = 1;
	else
		line.sx = -1;
	line.dy = -ft_abs(pos1.y - pos0.y);
	if (pos0.y < pos1.y)
		line.sy = 1;
	else
		line.sy = -1;
	line.err = line.dx + line.dy;
	line.e2 = 2 * line.err;
	return (line);
}

int	bresenham_line(t_pos pos0, t_pos pos1, t_fdf *fdf)
{
	t_line	line;
	int		color_code;

	line = line_init(pos0, pos1);
	color_code = which_color(pos0, pos1);
	while (1)
	{
		my_mlx_pixel_put(fdf->img, pos0.x, pos0.y, color_code);
		if (pos0.x == pos1.x && pos0.y == pos1.y)
			break ;
		line.e2 = 2 * line.err;
		if (line.e2 >= line.dy)
		{
			line.err += line.dy;
			pos0.x += line.sx;
		}
		if (line.e2 <= line.dx)
		{
			line.err += line.dx;
			pos0.y += line.sy;
		}
	}
	return (1);
}
