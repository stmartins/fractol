/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 13:33:34 by stmartin          #+#    #+#             */
/*   Updated: 2016/04/21 16:40:33 by stmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractinc.h"
#include <stdio.h>
unsigned long	colorrgb(int r, int g, int b)
{
	return ((r & 0xff) << 8) + ((g & 0xff) << 4) + ((b & 0xff) << 2);
}

void			image_put_pixel(t_image *i, int x, int y, int color)
{
	if (x <= 0 || y <= 0 || x >= WIN_X || y >= WIN_Y)
		return ;
	if ((x * i->bpp / 8) + (y * i->szline) < 0 || (x * i->bpp / 8) +
			(y * i->szline) > (i->szline * WIN_Y) - 1)
		return ;
	if (i->endian)
	{
		i->data[(x * i->bpp / 8) + (y * i->szline)] = color / 65536 % 256;
		i->data[(x * i->bpp / 8) + 1 + (y * i->szline)] = color / 256 % 256;
		i->data[(x * i->bpp / 8) + 2 + (y * i->szline)] = color % 256;
	}
	else
	{
		i->data[(x * i->bpp / 8) + 2 + (y * i->szline)] = color / 65536 % 256;
		i->data[(x * i->bpp / 8) + 1 + (y * i->szline)] = color / 256 % 256;
		i->data[(x * i->bpp / 8) + (y * i->szline)] = color % 256;
	}
}
