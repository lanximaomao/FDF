/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_handeling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:56:52 by lsun              #+#    #+#             */
/*   Updated: 2023/01/17 18:31:22 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/ft_printf.h"
#include "libft/get_next_line.h"
#include "libft/libft.h"

/*
** put pixel into image using function mlx_get_data_addr
** why mars map is not showing? should I remove the zoom/offset?
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


int bresenham_line (int x0, int y0, int x1, int y1, t_fdf fdf, int color_code)
{
  int dx =  ft_abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -ft_abs (y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy, e2; /* error value e_xy */

  for (;;){  /* loop */
    mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, x0, y0, color_code);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
  return (1);
}

//int	bresenham_line(t_positions pos1, t_positions pos2, t_fdf fdf, int color_code)
//{
//	int x;
//	int y;
//	int dx;
//	int dy;
//	int p;

//	x = pos1.new_x;
//	y = pos1.new_y;
//	dx = ft_abs(pos2.new_x - pos1.new_x);
//	dy = ft_abs(pos2.new_y - pos1.new_y);
//	if (dx > dy)
//	{
//		p = 2 * dy - dx;
//		while (x <= pos2.new_x)
//		{
//			mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, x, y, color_code);
//			x++;
//			if (p < 0)
//				p = p + 2 * dy;
//			else
//			{
//				p = p + 2 * dy - 2 * dx;
//				y++;
//			}
//		}
//	}
//	else
//	{
//		p = 2 * dx - dy;
//		while (y <= pos2.new_y)
//		{
//			mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, x, y, color_code);
//			y++;
//			if (p < 0)
//				p = p + 2 * dx;
//			else
//			{
//				p = p + 2 * dx - 2 * dy;
//				x++;
//			}
//		}
//	}
//	return (0);
//}

//void drawline(int x0, int y0, int x1, int y1)
//{
//    int dx, dy, p, x, y;
//    dx=x1-x0;
//    dy=y1-y0;
//    x=x0;
//    y=y0;
//    p=2*dy-dx;
//    while(x<x1)
//    {
//        if(p>=0)
//        {
//            mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, x, y, color_code);
//            y=y+1;
//            p=p+2*dy-2*dx;
//        }
//        else
//        {
//            putpixel(x,y,7);
//            p=p+2*dy;}
//            x=x+1;
//        }
//}

t_positions isometric(t_positions pos)
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
	input.offset_x = 0.87 * input.size_y*input.zoom + (WIN_SIZE_X - 0.87 * (input.size_x - input.size_y ) * input.zoom)/2;
	input.offset_y = (WIN_SIZE_Y - 0.5 * (input.size_x + input.size_y) * input.zoom)/2;
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
	if (input.size_x > input.size_y)
		input.zoom = WIN_SIZE_X / (0.87* (input.size_x + input.size_x));
	input.zoom_z = input.zoom/3; // arbitary values
	return(input);
}

int which_color(t_positions pos1, t_positions pos2)
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
		color_code = 0xFFFF00; // yellow
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
				//printf("Pos1: X: %d Y: %d Z: %d\n",pos1.new_x, pos1.new_y, pos1.new_z);
				pos1 = isometric(pos1);
				//printf("Pos1: X: %d Y: %d Z: %d\n",pos1.new_x, pos1.new_y, pos1.new_z);
			if (i != input.size_y - 1)
			{
				pos2.new_x = j * input.zoom + input.offset_x;
				pos2.new_y = (i + 1) * input.zoom + input.offset_y;
				pos2.new_z = input.map_int[i+1][j]*input.zoom_z;

				 //decide which color
				color_code = which_color(pos1, pos2);
				 //add the isometric conversion here
				pos2 = isometric(pos2);
				bresenham_line(pos1.new_x, pos1.new_y, pos2.new_x, pos2.new_y, fdf, color_code);//white line along y axis
				//bresenham_line(pos1, pos2, fdf, color_code);
			}
			if (j != input.size_x - 1)
			{
				pos2.new_x = (j + 1) * input.zoom + input.offset_x;
				pos2.new_y = i * input.zoom + input.offset_y;
				pos2.new_z = input.map_int[i][j+1]*input.zoom_z;
				color_code = which_color(pos1, pos2);
				pos2 = isometric(pos2);
				bresenham_line(pos1.new_x, pos1.new_y, pos2.new_x, pos2.new_y, fdf, color_code);//red line along x axis
				//bresenham_line(pos1, pos2, fdf, color_code);
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
