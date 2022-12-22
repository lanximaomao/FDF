/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:56:52 by lsun              #+#    #+#             */
/*   Updated: 2022/12/22 11:33:29 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"


int	deal_key(int key, t_fdf *fdf)
{
	if (key == 53)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		exit(1);
	}
	printf("%d ", key);
	return (0);
}

int	bresenham_line(t_line line1, t_fdf fdf, int color_code) // how to optimize it?
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
		mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, x, y, color_code);
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

int close_window(void *fdf)
{
	fdf = NULL;
	exit(1);
}


int	main(void)
{
	t_fdf	fdf;
	t_line	line1;

	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, 1000, 1000,
			"where is my line?");
	//fdf.image_ptr = mlx_new_image(fdf.mlx_ptr, 1000, 1000);
	//mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, 500, 500, 0xFFFFFF);
	//mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, 600, 600, 0xFFFFFF);
	//mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, 700, 700, 0xFFFFFF);
	line1 = line_init(500,500,700,700);
	bresenham_line(line1, fdf, 0xFFFFFF);
	mlx_hook(fdf.win_ptr, 2, 0, deal_key, &fdf); //key press
	mlx_hook(fdf.win_ptr, 17, 0, close_window, &fdf); //mouse click
	//mlx_key_hook(fdf.win_ptr, deal_key, &fdf); // a key is pressed
	//mlx_mouse_hook(fdf.win_ptr, close_window, &fdf);
	// why key is not used as an input here?
	mlx_loop(fdf.mlx_ptr);
	return (0);
}



/*
** https://stackoverflow.com/questions/14087274/difference-between-and-in-c
*/
