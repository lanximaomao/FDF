/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_handeling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:03:50 by lsun              #+#    #+#             */
/*   Updated: 2023/01/31 15:05:02 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	image_handeling(t_fdf *fdf)
{
	fdf->img = (t_img *)ft_calloc(sizeof(t_img), 1);
	if (!fdf->img)
		return (0);
	fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y);
	if (!fdf->img->img_ptr)
		return (1);
	fdf->img->addr = (int *)mlx_get_data_addr(fdf->img->img_ptr,
			&fdf->img->bits_per_pixel, &fdf->img->line_length,
			&fdf->img->endian);
	fdf->i = -1;
	fdf->j = -1;
	draw(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, 0,
		0);
	return (1);
}

int	refresh_image(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
	free(fdf->img);
	image_handeling(fdf);
	return (1);
}
