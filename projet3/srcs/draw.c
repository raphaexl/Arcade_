/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 22:21:00 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/02 12:58:56 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/prototypes.h"

int	time1 = 0;
int	time2 = 0;


float elapsed_time = 0.f;

void	ft_draw(Uint32 *pixels, t_player *p, t_track *track)
{
	int	x;
	t_point	p1;
	t_point	p2;
	t_point	car_pos;
	float fcar_pos = 0.0;
	int	y;
	float offset = 0;
	float fcurvature = 0.0f;
	int	track_section = 0;

	time1 = time2;
	time2 = SDL_GetTicks(); 
	elapsed_time = (float)(time2 - time1) / 100.f;
	while (track_section < 9 && offset <= p->fdistance)
	{
		offset += track[track_section].distance;
		track_section ++;
	}
	float	curvature = track[track_section - 1].curvature;
	float	dif_curvature = (curvature - fcurvature) * (elapsed_time) * p->speed;
	fcurvature += dif_curvature;
	//p->tcurvature += fcurvature * elapsed_time * p->speed;
	y = -1;
	while (++y < SCR_HEIGHT / 2)
	{
		x = -1;
		while (++x < SCR_WIDTH)
		pixels[y * SCR_WIDTH + x] = (y < SCR_HEIGHT / 4) ? 0x000055 : 0x0000FF;
	}
	x = -1;
	while (++x < SCR_WIDTH)
	{
		int h = fabs(sinf(x * 0.01f + p->tcurvature) * 50.0f);
		y = SCR_HEIGHT / 2 - h;
		while (++y < SCR_HEIGHT)
		pixels[y * SCR_WIDTH + x] = (y < SCR_HEIGHT / 4) ? 0x555500 : 0xFFFF;
	}
	y = -1;
	while (++y < SCR_HEIGHT / 2)
	{
		x = -1;
		while (++x < SCR_WIDTH)
		{
			float perspective = (float)y / (SCR_HEIGHT / 2.0f);
			//float middlepoint = 0.5f;
			//float middlepoint = 0.5f + fcurvature;
			float middlepoint = 0.5f + fcurvature * powf(1.0f - perspective, 3);
			// float roadwidth = 0.6f;
			// float roadwidth = perspective;
			float roadwidth = 0.1f + perspective * 0.8;
			float clipwidth = roadwidth * 0.15f;
			roadwidth *= 0.5f;

			int leftgrass = (middlepoint - roadwidth - clipwidth) * SCR_WIDTH;
			int	leftclip = (middlepoint - roadwidth) * SCR_WIDTH;
			int rightgrass = (middlepoint + roadwidth + clipwidth) * SCR_WIDTH;
			int  rightclip = (middlepoint + roadwidth) * SCR_WIDTH;

			int	grass_color = sinf(20.0f * powf(1.0f - perspective, 3) + p->fdistance * 0.1f) > 0.0f ? 0x00FF00 : 0x00AA00;
			int	clip_color = sinf(80.0f * powf(1.0f - perspective, 2) + p->fdistance ) > 0.0f ? 0xFF0000:0xFFFFFF;
			p1.x = x;
			p2.x = x;
			p1.y = SCR_HEIGHT / 2 + y;
			p2.y = SCR_HEIGHT / 2 + y;
			if (x >= 0 && x <leftgrass)
				ft_sdl_draw_line(pixels, p1, p2, grass_color);
			if (x >= leftgrass && x < leftclip)
				ft_sdl_draw_line(pixels, p1, p2, clip_color);
			if (x >= leftclip && x <rightclip)
				ft_sdl_draw_line(pixels, p1, p2, 0xDDDDDD);
			if (x >= rightclip && x < rightgrass)
				ft_sdl_draw_line(pixels, p1, p2, clip_color);
			if (x >= rightgrass && x <SCR_WIDTH)
				ft_sdl_draw_line(pixels, p1, p2, grass_color);
		}
	}
	fcar_pos = (p->curvature - p->tcurvature)/10.0f;
	car_pos.x = SCR_WIDTH / 2 + (int) (SCR_WIDTH * fcar_pos) / 2;
	car_pos.y = SCR_HEIGHT - 80;
	ft_sdl_draw_disc(pixels, car_pos, 50, 0x0000FF);
}

void	ft_handle_input(t_input *in, t_player *p)
{
	if (in->keys[SDL_SCANCODE_UP])
		p->speed += elapsed_time * 2.0f;
	else
		p->speed -= 1.0 * elapsed_time;
	/*if (in->keys[SDL_SCANCODE_LEFT])
	p->curvature -= 0.4f * elapsed_time * (1.0f - p->speed / 2.0f);
	if (in->keys[SDL_SCANCODE_RIGHT])
	p->curvature += 0.4f * elapsed_time * (1.0f - p->speed / 2.0f);
	if (fabs(p->curvature - p->tcurvature) > 0.8f)
	p->speed -= 5.0f * elapsed_time;*/
	if (p->speed < 0.0f)
		p->speed = 0.0f;
	if(p->speed > 1.0f)
		p->speed = 1.0f;

	p->fdistance += (10.0f * p->speed) * elapsed_time;
}

void	ft_track_init(t_track *trak)
{
	trak[0].curvature = 0.0f;
	trak[0].distance = 10.0f;
	trak[1].curvature = 0.0f;
	trak[1].distance = 200.0f;
	trak[2].curvature = -1.0f;
	trak[2].distance = 100.0f;
	trak[3].curvature = 0.0f;
	trak[3].distance = 200.0f;
	trak[4].curvature = -1.0f;
	trak[4].distance = 200.0f;
	trak[5].curvature = 1.0f;
	trak[5].distance = 200.0f;
	trak[6].curvature = 0.0f;
	trak[6].distance = 200.0f;	
	trak[7].curvature = 0.2f;
	trak[7].distance = 500.0f;
	trak[8].curvature = 0.0f;
	trak[8].distance = 200.0f;	
}
