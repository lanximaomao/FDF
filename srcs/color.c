/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:09:04 by lsun              #+#    #+#             */
/*   Updated: 2023/07/04 17:31:35 by lsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	which_color(t_pos pos1, t_pos pos2)
{
	int	color_code;

	if (pos1.z == 0 && pos2.z == 0)
		color_code = 0xffffff;
	else if (pos1.z > 0 && pos2.z > 0 && pos1.z == pos2.z)
		color_code = 0x020f0;
	else if (pos1.z > 0 && pos2.z > 0 && pos1.z != pos2.z)
		color_code = 0x8b0000;
	else if (pos1.z < 0 && pos2.z < 0 && pos1.z == pos2.z)
		color_code = 0x00ffff;
	else if (pos1.z < 0 && pos2.z < 0 && pos1.z != pos2.z)
		color_code = 0x1616ff;
	else if ((pos1.z == 0 && pos2.z < 0) || (pos1.z < 0 && pos2.z == 0))
		color_code = (0x00ffff + 0xffffff) / 2;
	else if ((pos1.z == 0 && pos2.z > 0) || (pos1.z > 0 && pos2.z == 0))
		color_code = 0x013220;
	else if ((pos1.z > 0 && pos2.z < 0) || (pos1.z < 0 && pos2.z > 0))
		color_code = (0x00ffff + 0xffffff) / 2;
	else
		color_code = 0x0000FF;
	return (color_code);
}
