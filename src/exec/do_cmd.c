/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:53:01 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/09 12:06:08 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

void	child(t_data *data, t_cmd_node *cmd, int pos, int *pipe_fd)
{
	char	*path;
	int		fd_out;
	int		fd_in;

	close(pipe_fd[0]);
	if (cmd->output)
	{
		if (cmd->append_mode == 1)
			fd_out = open(cmd->output, O_WRONLY | O_CREAT, O_APPEND, 0777);
		else
			fd_out = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd_out < 0)
			return ;
		dup2(fd_out, 1);
		close(fd_out);
	}
	else if (pos != 2 && pos != -1)
		dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	if (cmd->input)
	{
		fd_in = open(cmd->input, O_RDONLY);
		if (fd_in < 0)
			return ;
		dup2(fd_in, 0);
		close(fd_in);
	}
	else if (pos > 0)
	{
		dup2(data->prev_pipe_fd0, 0);
		close(data->prev_pipe_fd0);
	}
	if (check_builtin(cmd->cmd_name[0]))
		builtin(data, cmd);
	else
	{
		path = NULL;
		init_path(data, cmd->cmd_name[0], &path);
		if (!path)
			return ;
		signal(SIGQUIT, SIG_DFL);
		execve(path, cmd->cmd_name, data->env);
		free(path);
	}
}

void	parent(t_data *data, int *pipe_fd, int pos)
{
	close(pipe_fd[1]);
	if (pos == 2 || pos == -1)
		close(pipe_fd[0]);
	wait(NULL);
	if (pos != 2)
		data->prev_pipe_fd0 = pipe_fd[0];
}

bool	do_cmd(t_data *data, t_cmd_node *cmd, int pos)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (false);
	signal_pid = fork();
	if (signal_pid == -1)
		return (false);
	else if (signal_pid == 0)
		child(data, cmd, pos, pipe_fd);
	else
		parent(data, pipe_fd, pos);
	//wait(NULL);
	return (true);
}

