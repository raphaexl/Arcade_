/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 12:36:08 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/02 12:40:59 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RAYTRACE_H
# define RAYTRACE_H

typedef struct	s_ray
{
	t_vector	pos;
	t_vector	dir;
}		t_ray;

typedef	struct	s_light
{
	t_vector pos;
	int	 intensity;
}		t_light;

typedef struct	s_sphere
{
	t_vector	pos;
	double		radius;
}		t_sphere;

int		ft_sphere_intersect(t_sphere *s, t_ray *r, t_vector *p, t_vector *n);
#endif
