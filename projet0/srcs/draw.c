/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 22:21:00 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/02 12:45:09 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/prototypes.h"

void	ft_draw(Uint32 *pixels)
{
	int	x;
	t_point	p1;
	t_point	p2;
	int	y;
	y = -1;
	while (++y < SCR_HEIGHT / 2)
	{
		x = -1;
		while (++x < SCR_WIDTH)
		{
		 float middlepoint = 0.5f;
		 float roadwidth = 0.6f;
		 float clipwidth = roadwidth * 0.15f;

		 roadwidth *= 0.5f;

		 int leftgrass = (middlepoint - roadwidth - clipwidth) * SCR_WIDTH;
		 int	leftclip = (middlepoint - roadwidth) * SCR_WIDTH;
		 int rightgrass = (middlepoint + roadwidth + clipwidth) * SCR_WIDTH;
		 int  rightclip = (middlepoint + roadwidth) * SCR_WIDTH;

		 p1.x = x;
		 p2.x = x;
		 p1.y = SCR_HEIGHT / 2 + y;
		 p2.y = SCR_HEIGHT / 2 + y;
		 if (x >= 0 && x <leftgrass)
		 ft_sdl_draw_line(pixels, p1, p2, 0x00FF00);
		 if (x >= leftgrass && x < leftclip)
		 ft_sdl_draw_line(pixels, p1, p2, 0xFF0000);
		 if (x >= leftclip && x <rightclip)
		 ft_sdl_draw_line(pixels, p1, p2, 0xDDDDDD);
		 if (x >= rightclip && x < rightgrass)
		 ft_sdl_draw_line(pixels, p1, p2, 0xFF0000);
		 if (x >= rightgrass && x <SCR_WIDTH)
		 ft_sdl_draw_line(pixels, p1, p2, 0x00FF00);
		}
	}
}	
