/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:53:01 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/19 12:08:40 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

void	child(t_data *data, t_cmd_node *cmd, int pos, int *pipe_fd)
{
	char	*path;
	int		save_fd1;

	if (cmd->del_cmd)
		exit(data->exit_status);
	save_fd1 = dup(1);
	close(pipe_fd[0]);
	open_outfile(cmd, pos, pipe_fd, save_fd1);
	close(pipe_fd[1]);
	open_infile(cmd, pos, save_fd1, data);
	path = NULL;
	init_path(data, cmd->cmd_name[0], &path);
	if (!path)
		exit(data->exit_status);
	execve(path, cmd->cmd_name, data->env);
	free(path);
}

void	parent(t_data *data, int *pipe_fd, int pos)
{
	close(pipe_fd[1]);
	if (pos == 2 || pos == -1)
		close(pipe_fd[0]);
	if (pos != 2)
		data->prev_pipe_fd0 = pipe_fd[0];
}

bool	the_fork(t_data *data, t_cmd_node *cmd, int pos, int *pipe_fd)
{
	if (!ft_strncmp(cmd->cmd_name[0], "./minishell", 11))
		signal(SIGINT, SIG_IGN);
	else
		signal(SIGQUIT, &signal_handler_sigquit);
	g_signal_pid = fork();
	if (g_signal_pid == -1)
	{
		printf("ERROR: fork not opened...\n");
		data->exit_status = 1;
		return (false);
	}
	else if (g_signal_pid == 0)
		child(data, cmd, pos, pipe_fd);
	else
		parent(data, pipe_fd, pos);
	return (true);
}

void	no_path(t_cmd_node *cmd, t_data *data, char *path)
{
	if (cmd->del_cmd == 1)
		data->exit_status = 1;
	if (!path)
	{
		if (cmd->del_cmd == 0)
			data->exit_status = 127;
		cmd->del_cmd = 1;
	}
}

bool	do_cmd(t_data *data, t_cmd_node *cmd, int pos)
{
	int		pipe_fd[2];
	char	*path;

	path = NULL;
	if (pipe(pipe_fd) == -1)
	{
		write(2, "ERROR: pipe not opened...\n", 26);
		data->exit_status = 1;
		return (false);
	}
	if (check_builtin(cmd->cmd_name[0]))
	{
		do_builtin(data, cmd, pipe_fd, pos);
		return (false);
	}
	init_path(data, cmd->cmd_name[0], &path);
	if (path || count_cmd(data->head) > 1)
	{
		no_path(cmd, data, path);
		free(path);
		return (the_fork(data, cmd, pos, pipe_fd));
	}
	return (false);
}
