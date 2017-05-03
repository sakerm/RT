/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:07:58 by rmenegau          #+#    #+#             */
/*   Updated: 2017/05/03 10:58:49 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_color	create_color(double r, double g, double b)
{
	t_color	ret;

	ret.r = r;
	ret.g = g;
	ret.b = b;
	return (ret);
}
