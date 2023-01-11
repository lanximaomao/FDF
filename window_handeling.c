/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_handeling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:56:52 by lsun              #+#    #+#             */
/*   Updated: 2023/01/11 13:15:16 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/ft_printf.h"
#include "libft/get_next_line.h"
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

int zoom(t_map input)
{
	if (input.size_x > input.size_y)
		return (1000/input.size_x);
	else
		return(1000/input.size_y);
}

int draw(t_map input, t_fdf fdf, int color_code)
{
	int i;
	int j;
	int scale;

	i = 0;
	scale = zoom(input);
	while (i < input.size_y)
	{
		j = 0;
		while (j < input.size_x)
		{
			if (input.map_int[i][j] != 0)
				mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, j*scale, i*scale, color_code);
			j++;
		}
		i++;
	}
	return(0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	t_map	*input;

	input = ft_calloc(1, sizeof(t_map));
	if (!input)
		return(0);
	*input = map_handling(argc, argv, *input);
	//
	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, 1000, 1000,
			"where is my line?");
	fdf.image_ptr = mlx_new_image(fdf.mlx_ptr, 1000, 1000);//how to use this?
	//line1 = line_init(500,500,700,700);
	//bresenham_line(line1, fdf, 0xFFFFFF);
	draw(*input, fdf, 0xFFFFFF);
	mlx_hook(fdf.win_ptr, 2, 0, deal_key, &fdf); //key press
	mlx_hook(fdf.win_ptr, 17, 0, close_window, &fdf); //mouse click
	mlx_loop(fdf.mlx_ptr);
	return (0);
}



/*
** https://stackoverflow.com/questions/14087274/difference-between-and-in-c
*/
