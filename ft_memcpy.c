/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jualissa <jualissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:28:21 by jualissa          #+#    #+#             */
/*   Updated: 2025/10/02 23:06:30 by jualissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "poulet.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*real_dest;
	unsigned char	*real_src;

	real_dest = (unsigned char *)dest;
	real_src = (unsigned char *)src;
	i = 0;
	if ((!real_dest && !real_src))
		return (NULL);
	while (n > 0)
	{
		real_dest[i] = real_src [i];
		i++;
		n--;
	}
	return (real_dest);
}
