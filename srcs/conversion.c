/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:13:42 by lsun              #+#    #+#             */
/*   Updated: 2023/07/04 17:31:39 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	zoom_init(t_fdf *fdf)
{
	int	len;
	int	num;
	int	min;

	if (WIN_SIZE_X > WIN_SIZE_Y)
		min = WIN_SIZE_Y;
	else
		min = WIN_SIZE_X;
	num = 1;
	len = 0.87 * (fdf->input->size_x + fdf->input->size_y);
	if (num * len > min)
	{
		while (num * len > min)
			num = num / 2;
	}
	else if (num * len < min)
	{
		while (num * len < min)
			num++;
	}
	fdf->input->zoom = num;
}

t_pos	apply_zoom(t_pos pos, t_fdf *fdf)
{
	pos.x *= fdf->input->zoom;
	pos.y *= fdf->input->zoom;
	pos.z *= fdf->input->zoom_z;
	return (pos);
}

t_pos	conversion(t_pos pos, t_fdf *fdf)
{
	pos.x -= fdf->input->size_x / 2;
	pos.y -= fdf->input->size_y / 2;
	pos = apply_zoom(pos, fdf);
	pos = isometric(pos);
	pos.x += WIN_SIZE_X / 2;
	pos.y += WIN_SIZE_Y / 2;
	return (pos);
}
