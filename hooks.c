/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:01:31 by lsun              #+#    #+#             */
/*   Updated: 2023/01/31 14:55:39 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/ft_printf.h"
#include "libft/get_next_line.h"
#include "libft/libft.h"

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
	exit(1);
	return (0);
}
