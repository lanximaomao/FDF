/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_handeling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:56:52 by lsun              #+#    #+#             */
/*   Updated: 2023/01/16 16:11:04 by lsun             ###   ########.fr       */
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

int	bresenham_line(t_positions pos1, t_positions pos2, t_fdf fdf, int color_code)
	// how to optimize it?
{
	int x;
	int y;
	int dx;
	int dy;
	int p;

	x = pos1.new_x;
	y = pos1.new_y;
	dx = pos2.new_x - pos1.new_x;
	dy = pos2.new_y - pos1.new_y;

	if (dx > dy)
	{
		p = 2 * dy - dx;
		while (x <= pos2.new_x)
		{
			mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, x, y, color_code);
			x++;
			if (p < 0)
				p = p + 2 * dy;
			else
			{
				p = p + 2 * dy - 2 * dx;
				y++;
			}
		}
	}
	else
	{
		p = 2 * dx - dy;
		while (y <= pos2.new_y)
		{
			mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, x, y, color_code);
			y++;
			if (p < 0)
				p = p + 2 * dx;
			else
			{
				p = p + 2 * dx - 2 * dy;
				x++;
			}
		}
	}
	return (0);
}

//int	bresenham_line(t_positions pos1, t_positions pos2, t_fdf fdf, int color_code)
//	// how to optimize it?
//{
//	int dx;
//	int dy;
//	int p;

//	dx = pos2.new_x - pos1.new_x;
//	dy = pos2.new_y - pos2.new_y;

//	if (dx > dy)
//	{
//		p = 2 * dy - dx;
//		while (pos1.new_x <= pos2.new_x)
//		{
//			mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, pos1.new_x, pos1.new_y, color_code);
//			pos1.new_x++;
//			if (p < 0)
//				p = p + 2 * dy;
//			else
//			{
//				p = p + 2 * dy - 2 * dx;
//				pos1.new_x++;
//			}
//		}
//	}
//	else
//	{
//		p = 2 * dx - dy;
//		while (pos1.new_y <= pos2.new_x)
//		{
//			mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, pos1.new_x, pos1.new_y, color_code);
//			pos1.new_y++;
//			if (p < 0)
//				p = p + 2 * dx;
//			else
//			{
//				p = p + 2 * dx - 2 * dy;
//				pos1.new_y++;
//			}
//		}
//	}
//	return (0);
//}

//int	isometric(t_pos *pos)
//{
//	t_pos	old;

//	old = *pos;
//	pos->x = (old.x - old.y) * 0.87;
//	pos->y = -old.z + (old.x + old.y) * 0.523599;
//	return (1);
//}


t_positions isometric(t_positions pos)
{
	int temp;

	temp =pos.new_x;

	pos.new_x = (pos.new_x - pos.new_y) * 0.87;
	pos.new_y = -pos.new_z + (temp + pos.new_y) * 0.523599;
	return(pos);
}

int	close_window(void *fdf)
{
	fdf = NULL;
	exit(1);
}

t_map	zoom(t_map input)
{
	if (input.size_x > input.size_y)
		input.zoom = WIN_SIZE_X / input.size_x / 2;
	else
		input.zoom = WIN_SIZE_X / input.size_y / 2;
	input.offset_x = (WIN_SIZE_X - input.size_x * input.zoom)/2 ;
	input.offset_y = (WIN_SIZE_Y - input.size_y*input.zoom)/2;
	input.zoom_z = input.zoom/3; // arbitary values
	return(input);
}

int which_color(t_positions pos1, t_positions pos2)
{
	int color_code;

	ft_printf("my z is %d && %d\n", pos1.new_z, pos2.new_z);
	if (pos1.new_z == 0 && pos2.new_z == 0)
		color_code = 0xFFFFFF; // white
	else if (pos1.new_z > 0 && pos2.new_z > 0)
		color_code = 0xff0000; // red
	else if (pos1.new_z < 0 && pos2.new_z < 0)
		color_code = 0x00ffff;//cyan
	else if ((pos1.new_z ==  0 && pos2.new_z < 0) || (pos1.new_z < 0 && pos2.new_z == 0))
		color_code = (0x00ffff + 0xFFFFFF)/2; // grey
	else if ((pos1.new_z ==  0 && pos2.new_z > 0) || (pos1.new_z > 0 && pos2.new_z == 0))
		color_code = 0xFFFF00; // grey
	else if ((pos1.new_z >  0 && pos2.new_z < 0) || (pos1.new_z < 0 && pos2.new_z > 0))
		color_code = (0x00ffff + 0xFFFFFF)/2; // grey
	else
		color_code = 0x0000FF;
	return(color_code);
}

int	draw(t_map input, t_fdf fdf)
{
	int		i;
	int		j;
	int		color_code;
	t_positions	pos1;
	t_positions pos2;
	t_map	map;

	i = 0;
	map = zoom(input);
	ft_printf(" here my map size is %d && %d\n", map.size_x, map.size_y);
	ft_printf(" here my zoom %d && zoom z %d\n", map.zoom, map.zoom_z);
	ft_printf(" here my map offset is %d && %d\n", map.offset_x, map.offset_y);
	while (i < map.size_y)
	{
		j = 0;
		while (j < map.size_x)
		{
			if (i != map.size_y - 1)
			{
				pos1.new_x = j * map.zoom + map.offset_x;
				pos1.new_y = i * map.zoom + map.offset_y;
				pos1.new_z = map.map_int[i][j]* map.zoom_z;
				pos2.new_x = j * map.zoom + map.offset_x;
				pos2.new_y = (i + 1) * map.zoom + map.offset_y;
				pos2.new_z = map.map_int[i+1][j]*map.zoom_z;

				 //decide which color
				color_code = which_color(pos1, pos2);
				 //add the isometric conversion here
				//pos1 = isometric(pos1);
				//pos2 = isometric(pos2);
				bresenham_line(pos1, pos2, fdf, color_code);
			}
			if (j != map.size_x - 1)
			{
				pos1.new_x = j * map.zoom + map.offset_x;
				pos1.new_y = i * map.zoom + map.offset_y;
				pos1.new_z = map.map_int[i][j]* map.zoom_z;
				pos2.new_x = (j + 1) * map.zoom + map.offset_x;
				pos2.new_y = i * map.zoom + map.offset_y;
				pos2.new_z = map.map_int[i][j+1]*map.zoom_z;

				// decide which color
				color_code = which_color(pos1, pos2);
				// add the isometric conversion here
				//pos1 = isometric(pos1);
				//pos2 = isometric(pos2);
				bresenham_line(pos1, pos2, fdf, color_code);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	t_map	*input;

	input = ft_calloc(1, sizeof(t_map));
	if (!input)
		return (0);
	*input = map_handling(argc, argv, *input);
	//
	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, 1000, 1000, "where is my line?");
	fdf.img_ptr = mlx_new_image(fdf.mlx_ptr, 1000, 1000); //how to use this?
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, fdf.img_ptr, 0, 0);
	//line1 = line_init(500,500,700,700);
	//bresenham_line(line1, fdf, 0xFFFFFF);
	draw(*input, fdf);
	mlx_hook(fdf.win_ptr, 2, 0, deal_key, &fdf);      //key press
	mlx_hook(fdf.win_ptr, 17, 0, close_window, &fdf); //mouse click
	mlx_loop(fdf.mlx_ptr);
	return (0);
}

/*
** https://stackoverflow.com/questions/14087274/difference-between-and-in-c
*/
