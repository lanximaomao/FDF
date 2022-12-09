/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:56:52 by lsun              #+#    #+#             */
/*   Updated: 2022/12/09 17:09:22 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

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
	mlx_loop(mlx_ptr);
	return (0);
}
