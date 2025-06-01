/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:27:07 by smoore            #+#    #+#             */
/*   Updated: 2025/06/01 16:41:28 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	init_wall_data(t_wall *w, t_intersect *inter, int i, t_tex *tx, t_image *buf)
{
	w->i = i;
	w->addr = buf->addr;
	w->tex = get_wall_texture(tx, inter->side);
	w->wall_h = wall_height(inter);
	if (inter->side == EAST || inter->side == WEST)
		w->tex_x = (int)inter->y % TILE_SIZE;
	else
		w->tex_x = (int)inter->x % TILE_SIZE;
	w->tex_x = w->tex_x * w->tex->width / TILE_SIZE;
	w->step = (double)w->tex->height / w->wall_h;
	w->tex_pos = 0.0;
}

static void	clamp_wall_drawing(t_wall *w)
{
	w->draw_start = HEIGHT / 2 - w->wall_h / 2;
	w->draw_end = HEIGHT / 2 + w->wall_h / 2;
	if (w->draw_start < 0)
	{
		w->tex_pos = -w->draw_start * w->step;
		w->draw_start = 0;
	}
	if (w->draw_end > HEIGHT)
		w->draw_end = HEIGHT;
}

static void draw_wall_column(t_wall *w, t_image *buf)
{
	int	tex_offset;
	int	screen_offset;
	int	k;

	w->j = w->draw_start;
	while (w->j < w->draw_end)
	{
		w->tex_y = (int)w->tex_pos;
		w->tex_pos += w->step;
		tex_offset = w->tex_y * w->tex->line_len + w->tex_x * (w->tex->bpp / 8);
		screen_offset = w->j * buf->line_len + w->i * (buf->bpp / 8);
		k = 0;
		while (k < 4)
		{
			w->addr[screen_offset + k] = w->tex->addr[tex_offset + k];
			k++;
		}
		w->j++;
	}
}

void	paint_walls(t_image *buf, t_tex *tx, t_intersect *inter, int i)
{
	t_wall w;

	init_wall_data(&w, inter, i, tx, buf);
	if (!w.tex || !w.tex->addr)
		return ;
	clamp_wall_drawing(&w);
	draw_wall_column(&w, buf);
}
