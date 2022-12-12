/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:56:52 by lsun              #+#    #+#             */
/*   Updated: 2022/12/12 12:06:55 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

// color code and color percentage

int deal_key(int key, void *param)
{
	//ESC 27
	//zoom in  and zoom out

}

int main()
{
	void	*mlx_ptr;
	void	*mlx_window;
	void	*mlx_image;

	mlx_ptr = mlx_init();
	mlx_window = mlx_new_window(mlx_ptr, 1000, 1000, "where is my line?");
	mlx_pixel_put(mlx_ptr, mlx_window, 500, 500, 0xFFFFFF);
	mlx_pixel_put(mlx_ptr, mlx_window, 501, 500, 0xFFFFFF);
	mlx_pixel_put(mlx_ptr, mlx_window, 502, 500, 0xFFFFFF);
	mlx_key_hook(mlx_window, deal_key, (void*)0); // why key is not used as an input here?
	mlx_loop(mlx_ptr);
	return (0);
}
