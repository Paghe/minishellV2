/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:36:41 by crepou            #+#    #+#             */
/*   Updated: 2023/06/15 20:19:23 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "../include/control.h"

void	output_redirection_renew(t_cmds **red, char **envp)
{
	int	pid;
	int	fd;

	fd = open((*red)->data.output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, STDOUT_FILENO);
		if ((*red)->data.fd_in != -1)
		{
			dup2((*red)->data.fd_in, STDIN_FILENO);
			close((*red)->data.fd_in);
		}
		execve((char const *)(*red)->data.env, (*red)->cmds, envp);
	}
	waitpid(pid, NULL, 0);
	(*red)->data.fd_out = fd;
}

/*void do_io()
{
	if  (out_put	input)
		waitpid
	return ;
}*/
//void	output_redirection_append(t_redirection *red)
//{
//	int	fd;

//	while (1)
//	{
//		if (fork() != 0)
//			wait(NULL);
//		else
//		{
//			fd = open(red->filename, O_WRONLY | O_APPEND | O_CREAT);
//			dup2(fd, 1);
//			execve(red->envp[0], red->args, red->envp);
//			perror("error in child");
//		}
//		break ;
//	}
//	close(fd);
//}
