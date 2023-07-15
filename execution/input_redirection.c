/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:36:41 by crepou            #+#    #+#             */
/*   Updated: 2023/07/15 19:32:09 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/control.h"

void	input_redirection(t_cmds **red, char **envp)
{
	int	pid;
	int	fd;

	fd = open((*red)->data.input, O_RDONLY);
	if (fd == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		if ((*red)->data.fd_out != -1)
			dup2((*red)->data.fd_out, STDOUT_FILENO);
		if (execve((char const *)(*red)->data.env, (*red)->cmds, envp) == -1)
			exit(-1);
	}
	waitpid(pid, NULL, 0);
	(*red)->data.fd_in = fd;
}
