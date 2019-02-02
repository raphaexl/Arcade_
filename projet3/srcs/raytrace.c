#include "../includes/prototypes.h"

int		ft_sphere_intersect(t_sphere *s, t_ray *r, t_vector *p, t_vector *n)
{
 	//a * t^2 + b*t + c
	double a = 1;
	t_vector k = ft_vector_sub(&r->pos, &s->pos);
	double b = 2 * ft_vector_dot(&r->dir, &k);
	double	c = ft_vector_norm(&k) - s->radius * s->radius;
	double	delta = b * b - 4 * a * c;
	if (delta < 0)
	return 0;
	double t1 = (-b - sqrt(delta) / (2.0 * a));
	double t2 = (-b + sqrt(delta) / (2.0 * a));
	if (t2 < 0)
	return (0);
	double	t;
	if (t1 > 0)
	t = t1;
	else
	t = t2;
	k = ft_vector_kmult(t, &r->dir);
	*p = ft_vector_sum(&r->pos, &k);
	k = ft_vector_sub(p, &s->pos);
	*n = ft_vector_normalized(&k);
	return (1);
}
