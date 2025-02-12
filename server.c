/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:07:41 by jcologne          #+#    #+#             */
/*   Updated: 2025/02/12 10:47:06 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	read_signal(int signal, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				bit_index;
	pid_t					client_pid;

	client_pid = info->si_pid;
	if (signal == SIGUSR2)
		c = c + (1 << (7 - bit_index));
	bit_index++;
	if (bit_index == 8)
	{
		write(1, &c, 1);
		c = 0;
		bit_index = 0;
	}
	kill(client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("%d\n", getpid());
	sa.sa_sigaction = read_signal;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
