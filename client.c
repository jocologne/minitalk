/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:07:21 by jcologne          #+#    #+#             */
/*   Updated: 2025/02/12 10:08:37 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int	g_char_received = 0;

void	ack_handler(int signal)
{
	g_char_received = 1;
}

static int	validate(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static int	ft_atoi(const char *n)
{
	int		sign;
	long	num;
	int		i;

	i = 0;
	sign = 1;
	num = 0;
	if (n[i] == '\0')
		return (0);
	while ((n[i] >= 9 && n[i] <= 13) || n[i] == 32)
		i++;
	if (n[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (n[i] == '+')
		i++;
	while (n[i] >= '0' && n[i] <= '9')
	{
		num = (num * 10) + (n[i]) - 48;
		i++;
	}
	return (num * sign);
}

void	send_signal(char c, pid_t server)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		g_char_received = 0;
		if (c & (1 << i))
			kill(server, SIGUSR2);
		else
			kill(server, SIGUSR1);
		while (!g_char_received)
			pause();
		i--;
	}
}

int	main(int ac, char **av)
{
	pid_t	server;
	char	*message;

	if (ac != 3 || !validate(av[1]))
	{
		ft_printf("Argument error");
		return (1);
	}
	server = ft_atoi(av[1]);
	message = av[2];
	signal(SIGUSR1, ack_handler);
	while (*message)
	{
		send_signal(*message, server);
		message++;
	}
	send_signal('\0', server);
	send_signal('\n', server);
	return (0);
}
