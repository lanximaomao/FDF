/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:06:10 by lsun              #+#    #+#             */
/*   Updated: 2023/07/04 17:32:18 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	fdf = ft_calloc(1, sizeof(t_fdf));
	if (!fdf)
		clean(fdf);
	fdf->input = ft_calloc(1, sizeof(t_map));
	if (!fdf->input)
		clean(fdf);
	if (map_handling(argc, argv, fdf) == 0)
		clean(fdf);
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		clean(fdf);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_SIZE_X, WIN_SIZE_Y, "FDF");
	if (!fdf->win_ptr)
		clean(fdf);
	if (image_handeling(fdf) == 0)
		clean(fdf);
	register_hooks(fdf);
	mlx_loop(fdf->mlx_ptr);
	clean(fdf);
	return (0);
}
