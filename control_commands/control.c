/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:04:10 by crepou            #+#    #+#             */
/*   Updated: 2023/06/19 18:05:06 by apaghera         ###   ########.fr       */
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
	// rl_on_new_line();
	// // rl_replace_line("", 0);
	// rl_redisplay();
}

void	slash_handler(int signum)
{
	struct sigaction	sig;

	(void)signum;
	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig, NULL);
}

void	signal_reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	// rl_on_new_line();
	// // rl_replace_line("", 0);
	// rl_redisplay();
}

/* set_signals_interactive:
*	Sets the behavior in response to SIGINT (ctrl-c) and SIGQUIT (ctrl-\).
*	SIGINT resets the user input prompt to a new blank line.
*	SIGQUIT is ignored.
*	Used when minishell is in interactive mode, meaning it is awaiting
*	user input.
*/
void	set_signals_interactive(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

/* signal_print_newline:
*	Prints a newline for noninteractive signal handling.
*/
void	signal_print_newline(int signal)
{
	(void)signal;
	// rl_on_new_line();
}
void	set_signals_noninteractive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

/* ignore_sigquit:
*	Replaces SIGQUIT signals (ctrl-\) with SIG_IGN to ignore
*	the signal.
*/
void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}
