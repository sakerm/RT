/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:15:26 by rmenegau          #+#    #+#             */
/*   Updated: 2017/05/01 09:30:08 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

double	dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	get_point(t_ray ray, double t)
{
	t_vec	p;

	p.x = ray.o.x + ray.d.x * t;
	p.y = ray.o.y + ray.d.y * t;
	p.z = ray.o.z + ray.d.z * t;
	return (p);
}

t_vec	bisector(t_vec v, t_vec l)
{
	t_vec	b;
	t_vec	sum;

	sum.x = v.x + l.x;
	sum.y = v.y + l.y;
	sum.z = v.z + l.z;
	b.x = sum.x / abs(sum.x);
	b.y = sum.y / abs(sum.y);
	b.z = sum.z / abs(sum.z);
	return (b);
}

t_vec	create_vec(double x, double y, double z)
{
	t_vec ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

void	normalize(t_vec *v)
{
	double len = v->x * v->x + v->y * v->y + v->z * v->z;
	len = sqrt(len);
	v->x /= len;
	v->y /= len;
	v->z /= len;
}
