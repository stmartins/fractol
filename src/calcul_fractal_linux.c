#include "fractinc.h"

int				mouse_hook(int button, int x, int y, t_env *e)
{
	double	lax;
	double	lay;

	if (button == 5)
	{
		lax = (x / e->v.zoom) + e->v.x1;
		lay = (y / e->v.zoom) + e->v.y1;
		e->v.zoom *= 1.1;
		e->v.x1 = lax - (x / e->v.zoom);
		e->v.y1 = lay - (y / e->v.zoom);
	}
	if (button == 4 && e->v.zoom > 50)
	{
		lax = (x / e->v.zoom) + e->v.x1;
		lay = (y / e->v.zoom) + e->v.y1;
		e->v.zoom /= 1.1;
		e->v.x1 = lax - (x / e->v.zoom);
		e->v.y1 = lay - (y / e->v.zoom);
	}
	expose_hook(e);
	return (0);
}

void			move_map(int keycode, t_env *e)
{
	if (keycode == 65362)
		e->my -= 100 / e->v.zoom;
	if (keycode == 65364)
		e->my += 100 / e->v.zoom;
	if (keycode == 65363)
		e->mx += 100 / e->v.zoom;
	if (keycode == 65361)
		e->mx -= 100 / e->v.zoom;
}

void			wich_fractal(t_env *e)
{
	if (e->ret == 1 || e->ret == 2)
		e->ret == 2 ? mandelbrot(e) : julia(e);
	else
		myfractal(e);
}

void			fractal(t_env *e, int i)
{
	double	tmp;

	e->v.y = 0;
	while (e->v.y < WIN_Y)
	{
		e->v.x = 0;
		while(e->v.x < WIN_X)
		{
			e->v.z_r = e->v.x / e->v.zoom + e->v.x1 + e->mx;
			e->v.z_i = e->v.y / e->v.zoom + e->v.y1 + e->my;
			i = 0;
			while (e->v.z_r * e->v.z_r + e->v.z_i * e->v.z_i < 4 && i < e->v.it_max)
			{
				wich_fractal(e);
								tmp = e->v.z_r;
				e->v.z_r = e->v.z_r * e->v.z_r  - e->v.z_i * e->v.z_i + e->v.c_r;
				e->v.z_i = 2 * e->v.z_i * tmp + e->v.c_i;
				i++;
			}
			if (i == e->v.it_max)
				image_put_pixel(&(e->img), e->v.x, e->v.y, 0);
			else
				image_put_pixel(&(e->img), e->v.x, e->v.y, colrgb(e->col, i *
			255 / e->v.it_max, i * 255 / e->v.it_max, i * 255 / e->v.it_max));
			e->v.x++;
		}
		e->v.y++;
	}
}