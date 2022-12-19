/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:56:52 by lsun              #+#    #+#             */
/*   Updated: 2022/12/19 16:26:22 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_fdf
{
	void	*mlx_ptr;
	void	*mlx_window;
	void	*mlx_image;
}			t_fdf;

typedef struct s_line
{
	int		x1;
	int		y1;
	int		x2;
	int		y2;
}			t_line;

int	deal_key(int key, t_fdf fdf)
{
	if (key == 53)
	{
		mlx_destroy_window(fdf.mlx_ptr, fdf.mlx_window);
		exit(0);
	}
	return (1);
}

int	bresenham_line(t_line line1, t_fdf fdf, int color_code)
{
	int	x;
	int	y;
	int dx;
	int dy;
	int p;

	x = line1.x1;
	y = line1.y1;
	dx = line1.x2 - line1.x1;
	dy = line1.y2 - line1.y1;
	p = 2 * dy - dx;
	while (x <= line1.x2)
	{
		mlx_pixel_put(fdf.mlx_ptr, fdf.mlx_window, x, y, 0xFFFFFF);
		x++;
		if (p < 0)
			p = p + 2 * dy;
		else
		{
			p = p + 2 * dy - 2*dx;
			y++;
		}
	}
	return (0);
}

t_line line_init(int x1, int y1, int x2, int y2)
{
	t_line	line1;

	line1.x1 = x1;
	line1.y1 = y1;
	line1.x2 = x2;
	line1.y2 = y2;
	return (line1);
}

int	main(void)
{
	t_fdf	fdf;
	t_line	line1;

	fdf.mlx_ptr = mlx_init();
	fdf.mlx_window = mlx_new_window(fdf.mlx_ptr, 1000, 1000,
			"where is my line?");
	//mlx_pixel_put(fdf.mlx_ptr, fdf.mlx_window, 500, 500, 0xFFFFFF);
	//mlx_pixel_put(fdf.mlx_ptr, fdf.mlx_window, 600, 600, 0xFFFFFF);
	//mlx_pixel_put(fdf.mlx_ptr, fdf.mlx_window, 700, 700, 0xFFFFFF);
	line1 = line_init(500,500,700,700);
	bresenham_line(line1, fdf, 0xFFFFFF);
	mlx_key_hook(fdf.mlx_window, deal_key, (void *)0);
	// why key is not used as an input here?
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
