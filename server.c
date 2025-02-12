/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:07:41 by jcologne          #+#    #+#             */
/*   Updated: 2025/02/12 08:20:12 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	read_signal(int signal)
{
	static unsigned char	c;
	static int				bit_index;

	if (signal == SIGUSR1)
		c &= ~(1 << (7 - bit_index));
	else if (signal == SIGUSR2)
		c |= (1 << (7 - bit_index));
	bit_index++;
	if (bit_index == 8)
	{
		write(1, &c, 1);
		c = 0;
		bit_index = 0;
	}
}

int	main(void)
{
	ft_printf("%d\n", getpid());
	signal(SIGUSR1, read_signal);
	signal(SIGUSR2, read_signal);
	while (1)
		pause();
	return (0);
}
