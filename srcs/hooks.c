/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:01:31 by lsun              #+#    #+#             */
/*   Updated: 2023/07/04 17:40:56 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	key_hook(int key, t_fdf *fdf)
{
	if (key == 53)
		exit(0);
	else if (key == 69)
		fdf->input->zoom_z++;
	else if (key == 78)
		fdf->input->zoom_z--;
	refresh_image(fdf);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 5)
		fdf->input->zoom++;
	else if (button == 4)
		fdf->input->zoom--;
	refresh_image(fdf);
	return (0);
}

int	close_widow(t_fdf *fdf)
{
	fdf = NULL;
	exit(0);
	return (0);
}

void	register_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->win_ptr, 17, 0, close_widow, fdf);
	mlx_key_hook(fdf->win_ptr, key_hook, fdf);
	mlx_mouse_hook(fdf->win_ptr, mouse_hook, fdf);
}
