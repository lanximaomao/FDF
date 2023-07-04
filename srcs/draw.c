/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:11:39 by lsun              #+#    #+#             */
/*   Updated: 2023/07/04 17:40:45 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_pos	pos_init(int x, int y, int z, t_pos pos)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
	return (pos);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color_code)
{
	int	dst;

	dst = y * (data->line_length / 4) + x;
	if ((x >= 0 && x < WIN_SIZE_X) && (y >= 0 && y < WIN_SIZE_Y))
		data->addr[dst] = color_code;
}

int	draw(t_fdf *fdf)
{
	t_pos	pos1;
	t_pos	pos2;

	while (++fdf->i < fdf->input->size_y)
	{
		fdf->j = -1;
		while (++fdf->j < fdf->input->size_x)
		{
			pos1 = pos_init(fdf->j, fdf->i, fdf->input->map_int[fdf->i][fdf->j],
					pos1);
			pos1 = conversion(pos1, fdf);
			pos2 = pos1;
			if (fdf->i != fdf->input->size_y - 1)
			{
				pos2 = pos_init(fdf->j, fdf->i + 1, fdf->input->map_int[fdf->i
						+ 1][fdf->j], pos2);
				pos2 = conversion(pos2, fdf);
				bresenham_line(pos1, pos2, fdf);
			}
			if (fdf->j != fdf->input->size_x - 1)
			{
				pos2 = pos_init(fdf->j + 1, fdf->i,
						fdf->input->map_int[fdf->i][fdf->j + 1], pos2);
				pos2 = conversion(pos2, fdf);
				bresenham_line(pos1, pos2, fdf);
			}
		}
	}
	return (0);
}
