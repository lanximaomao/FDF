/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_handeling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:56:52 by lsun              #+#    #+#             */
/*   Updated: 2023/01/20 12:34:52 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"
#include "libft/ft_printf.h"
#include "libft/get_next_line.h"
#include "libft/libft.h"

/*
** put pixel into image using function mlx_get_data_addr
** why mars map is not showing? should I remove the zoom/offset?
** add new functionalities, translation, zoom in and out, rotation
** norminette
*/

int	deal_key(int key, t_fdf *fdf)
{
	if (key == 53)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		exit(1);
	}
	ft_printf("%d ", key);
	return (0);
}

int	close_window(void *fdf)
{
	fdf = NULL;
	exit(1);
}

int ft_abs(int a)
{
	if (a < 0)
		return(-a);
	return(a);
}


int bresenham_line (t_pos pos0, t_pos pos1, t_fdf fdf, int color_code)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;

	dx =  ft_abs (pos1.new_x - pos0.new_x);
	if (pos0.new_x < pos1.new_x)
		sx = 1;
	else
		sx = -1;
	dy = -ft_abs (pos1.new_y - pos0.new_y);
	if (pos0.new_y < pos1.new_y)
		sy = 1;
	else
		sy = -1;
	err = dx + dy;
	e2 = 2 *err;

  while (1)
  {
    mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, pos0.new_x, pos0.new_y, color_code);
    if (pos0.new_x == pos1.new_x && pos0.new_y == pos1.new_y)
		break;
    e2 = 2 * err;
    if (e2 >= dy)
	{
		 err += dy;
		 pos0.new_x += sx;
	}
    if (e2 <= dx)
	{
		err += dx;
		pos0.new_y += sy;
	}
  }
  return (1);
}


t_pos isometric(t_pos pos)
{
	int temp;

	temp =pos.new_x;

	pos.new_x = (pos.new_x - pos.new_y) * 0.87; // cos30
	pos.new_y = -pos.new_z + (temp + pos.new_y) * 0.50; // sin30
	return(pos);
}

//t_map	offset(t_map input)
//{
//	input.offset_x = (WIN_SIZE_X - input.size_x * input.zoom)/2 ;
//	input.offset_y = (WIN_SIZE_Y - input.size_y*input.zoom)/2;
//	return(input);
//}

t_map	offset(t_map input)
{
	input.offset_x = 0.87 * input.size_y*input.zoom + (WIN_SIZE_X - 0.87 * (input.size_x - input.size_y ) * input.zoom)/2 ;
	input.offset_y = (WIN_SIZE_Y - 0.5 * (input.size_x + input.size_y) * input.zoom)/2 ;
	//input.offset_x = 0;
	//input.offset_y = 0;
	return(input);
}

// x-axis is defined by top right (input.size_x-1, 0) and left down (0, input.size_y-1)
// after projection it become
// y-axis is defined by top left (0,0) and right down (input.size_x-1, input.size_y-1)
// (x+y)*0.5 - (0 + 0 )* 0.5

//t_map	zoom(t_map input)
//{
//	if (input.size_x > input.size_y)
//		input.zoom = WIN_SIZE_X / input.size_x / 3;
//	else
//		input.zoom = WIN_SIZE_X / input.size_y / 3;
//	input.zoom_z = input.zoom/3; // arbitary values
//	return(input);
//}

t_map	zoom(t_map input)
{
	input.zoom = WIN_SIZE_X / (0.87* (input.size_x + input.size_y));
	input.zoom_z = input.zoom/3;
	return(input);
}

int which_color(t_pos pos1, t_pos pos2)
{
	int color_code;

	if (pos1.new_z == 0 && pos2.new_z == 0)
		color_code = 0xFFFFFF; // white
	else if (pos1.new_z > 0 && pos2.new_z > 0)
		color_code = 0xff0000; // red
	else if (pos1.new_z < 0 && pos2.new_z < 0)
		color_code = 0x00ffff;//cyan
	else if ((pos1.new_z ==  0 && pos2.new_z < 0) || (pos1.new_z < 0 && pos2.new_z == 0))
		color_code = (0x00ffff + 0xFFFFFF)/2; // grey
	else if ((pos1.new_z ==  0 && pos2.new_z > 0) || (pos1.new_z > 0 && pos2.new_z == 0))
		color_code = 0xffcccb; // light red
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
	t_pos	pos1;
	t_pos pos2;

	i = 0;
	input = offset(zoom(input));
	while (i < input.size_y)
	{
		j = 0;
		while (j < input.size_x)
		{
				pos1.new_x = j * input.zoom + input.offset_x;
				pos1.new_y = i * input.zoom + input.offset_y;
				pos1.new_z = input.map_int[i][j]* input.zoom_z;
				pos1 = isometric(pos1);
			if (i != input.size_y - 1)
			{
				pos2.new_x = j * input.zoom + input.offset_x;
				pos2.new_y = (i + 1) * input.zoom + input.offset_y;
				pos2.new_z = input.map_int[i+1][j]*input.zoom_z;
				color_code = which_color(pos1, pos2);
				pos2 = isometric(pos2);
				//ft_printf("pos1 x and y %d, %d\npos2 x and y %d, %d\n", pos1.new_x, pos1.new_y, pos2.new_x, pos2.new_y);
				//ft_printf("i and j %d %d\n", i , j);
				//ft_printf("zoom is %d\n", input.zoom);
				bresenham_line(pos1, pos2, fdf, color_code);
			}
			if (j != input.size_x - 1)
			{
				pos2.new_x = (j + 1) * input.zoom + input.offset_x;
				pos2.new_y = i * input.zoom + input.offset_y;
				pos2.new_z = input.map_int[i][j+1]*input.zoom_z;
				color_code = which_color(pos1, pos2);
				pos2 = isometric(pos2);
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
	fdf.img_ptr = mlx_new_image(fdf.mlx_ptr, 1000, 1000);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, fdf.img_ptr, 0, 0);
	draw(*input, fdf);
	mlx_hook(fdf.win_ptr, 2, 0, deal_key, &fdf);      //key press
	mlx_hook(fdf.win_ptr, 17, 0, close_window, &fdf); //mouse click
	mlx_loop(fdf.mlx_ptr);
	return (0);
}

/*
** https://stackoverflow.com/questions/14087274/difference-between-and-in-c
*/
