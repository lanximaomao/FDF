/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:56:52 by lsun              #+#    #+#             */
/*   Updated: 2022/12/19 20:13:35 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

// make the hook work
// include libft and printf

int	deal_key(int key, t_fdf fdf)
{
	if (key == 53)
	{
		mlx_destroy_window(fdf.mlx_ptr, fdf.mlx_window);
		exit(1);
	}
	return (0);
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
		mlx_pixel_put(fdf.mlx_ptr, fdf.mlx_window, x, y, color_code);
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

//void close_window(t_fdf fdf)
//{
//	exit (1);
//}

//int read_map()
//{

//}

int	main(void)
{
	t_fdf	fdf;
	t_line	line1;

	fdf.mlx_ptr = mlx_init();
	fdf.mlx_window = mlx_new_window(fdf.mlx_ptr, 1000, 1000,
			"where is my line?");
	fdf.mlx_image = mlx_new_image(fdf.mlx_ptr, 1000, 1000);
	//mlx_pixel_put(fdf.mlx_ptr, fdf.mlx_window, 500, 500, 0xFFFFFF);
	//mlx_pixel_put(fdf.mlx_ptr, fdf.mlx_window, 600, 600, 0xFFFFFF);
	//mlx_pixel_put(fdf.mlx_ptr, fdf.mlx_window, 700, 700, 0xFFFFFF);
	line1 = line_init(500,500,700,700);
	bresenham_line(line1, fdf, 0xFFFFFF);
	//mlx_hook(fdf.mlx_window, 2, 0, deal_key, (void *)0);
	//mlx_hook(fdf.mlx_window, 1, 0, close_window, (void *)0);
	mlx_key_hook(fdf.mlx_window, deal_key, (void *)0);
	// why key is not used as an input here?
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
