/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourlogin <youremail@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:57:27 by yourlogin         #+#    #+#             */
/*   Updated: 2025/11/28 13:57:27 by yourlogin        ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
