/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klabaune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 23:15:49 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/15 23:15:52 by klabaune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

int	open_outfile_bin(t_cmd_node *cmd, int pos, int *pipe_fd)
{
	int	fd_out;

	if (cmd->output)
	{
		if (cmd->append_mode == 1)
			fd_out = open(cmd->output, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			fd_out = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd_out < 0)
		{
			printf("open: can't open output file: %s\n", cmd->output);
			return (1);
		}
		dup2(fd_out, 1);
		close(fd_out);
	}
	else if (pos != 2 && pos != -1)
		dup2(pipe_fd[1], 1);
	return (0);
}

int	open_infile_bin(t_cmd_node *cmd, int pos, t_data *data)
{
	int	fd_in;

	if (cmd->input)
	{
		fd_in = open(cmd->input, O_RDONLY);
		if (fd_in < 0)
		{
			printf("open: can't open input file: %s\n", cmd->input);
			return (1);
		}
		dup2(fd_in, 0);
		close(fd_in);
	}
	else if (pos > 0)
	{
		if (data->prev_pipe_fd0 == -1)
			return (1);
		dup2(data->prev_pipe_fd0, 0);
		close(data->prev_pipe_fd0);
	}
	return (0);
}

void	wait_all(t_data *data)
{
	int	nbr_cmd;
	int	i;
	int	pid;
	int	exit_s;

	nbr_cmd = count_cmd(data->head);
	i = 0;
	while (i != nbr_cmd)
	{
		pid = waitpid(0, &exit_s, 0);
		if (pid == g_signal_pid)
			data->exit_status = WEXITSTATUS(exit_s);
		i++;
	}
}

void	open_outfile(t_cmd_node *cmd, int pos, int *pipe_fd, int save_fd1)
{
	int	fd_out;

	if (cmd->output)
	{
		if (cmd->append_mode == 1)
			fd_out = open(cmd->output, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			fd_out = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd_out < 0)
		{
			dup2(save_fd1, 1);
			printf("open: can't open output file: %s\n", cmd->output);
			exit(errno);
		}
		dup2(fd_out, 1);
		close(fd_out);
	}
	else if (pos != 2 && pos != -1)
		dup2(pipe_fd[1], 1);
}

void	open_infile(t_cmd_node *cmd, int pos, int save_fd1, t_data *data)
{
	int	fd_in;

	if (cmd->input)
	{
		fd_in = open(cmd->input, O_RDONLY);
		if (fd_in < 0)
		{
			dup2(save_fd1, 1);
			printf("open: can't open input file: %s\n", cmd->input);
			exit(errno);
		}
		dup2(fd_in, 0);
		close(fd_in);
	}
	else if (pos > 0)
	{
		if (data->prev_pipe_fd0 == -1)
			exit(1);
		dup2(data->prev_pipe_fd0, 0);
		close(data->prev_pipe_fd0);
	}
}
