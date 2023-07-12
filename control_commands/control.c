/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:04:10 by crepou            #+#    #+#             */
/*   Updated: 2023/07/12 19:14:46 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/control.h"

void	clear_line(void)
{
	struct termios	terminal_args;

	tcgetattr(1, &terminal_args);
	terminal_args.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &terminal_args);
}

void	cntr_handler(int signum)
{
	slash_handler(signum);
	if (signum == SIGINT)
		write(1, "\n", 1);
	//rl_on_new_line();
	//rl_replace_line("", 0);
	//rl_redisplay();
}

void	slash_handler(int signum)
{
	struct sigaction	sig;

	(void)signum;
	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig, NULL);
}

void	signal_on_block(int signum)
{
	(void)signum;
	//rl_on_new_line();
}

void	block_signals(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_on_block;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
