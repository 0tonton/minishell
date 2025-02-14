/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:52:26 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/14 17:32:33 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

bool	check_builtin(char *cmd)
{
	if (ft_strncmp("cd", cmd, INT_MAX) == 0 || ft_strncmp("echo", cmd, INT_MAX) == 0 \
	|| ft_strncmp("env", cmd, INT_MAX) == 0 || ft_strncmp("exit", cmd, INT_MAX) == 0 \
	|| ft_strncmp("export", cmd, INT_MAX) == 0 || ft_strncmp("pwd", cmd, INT_MAX) == 0 \
	|| ft_strncmp("unset", cmd, INT_MAX) == 0)
		return (true);
	return (false);
}

void	builtin(t_data *data, t_cmd_node *cmd)
{
	if (ft_strncmp("cd", cmd->cmd_name[0], INT_MAX) == 0)
		data->exit_status = ft_cd(data, cmd->cmd_name);
	else if (ft_strncmp("echo", cmd->cmd_name[0], INT_MAX) == 0)
		data->exit_status = ft_echo(cmd->cmd_name);
	else if (ft_strncmp("env", cmd->cmd_name[0], INT_MAX) == 0)
		data->exit_status = ft_env(data->env);
	else if (ft_strncmp("pwd", cmd->cmd_name[0], INT_MAX) == 0)
		data->exit_status = ft_pwd();
	else if (ft_strncmp("exit", cmd->cmd_name[0], INT_MAX) == 0)
		ft_exit(data, cmd->cmd_name);
	else if (ft_strncmp("export", cmd->cmd_name[0], INT_MAX) == 0)
		data->exit_status = ft_export(data, cmd->cmd_name, data->env);
	else if (ft_strncmp("unset", cmd->cmd_name[0], INT_MAX) == 0)
		data->exit_status = ft_unset(data, cmd->cmd_name, data->env);
}

void	do_builtin(t_data *data, t_cmd_node *cmd, int *pipe_fd, int pos)
{
	int	save_fd1;
	int	save_fd0;
	int	fd_in;
	int	fd_out;

	save_fd1 = dup(1);
	save_fd0 = dup(0);
	if (pos == 2 || pos == -1)
		close(pipe_fd[0]);
	if (cmd->output)
	{
		if (cmd->append_mode == 1)
			fd_out = open(cmd->output, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			fd_out = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd_out < 0)
		{
			printf("open: can't open output file: %s\n", cmd ->output);
			return ;
		}
		dup2(fd_out, 1);
		close(fd_out);
	}
	else if (pos != 2 && pos != -1)
		dup2(pipe_fd[1], 1);
	if (cmd->input)
	{
		fd_in = open(cmd->input, O_RDONLY);
		if (fd_in < 0)
		{
			printf("open: can't open input file: %s\n", cmd->input);
			return ;
		}
		dup2(fd_in, 0);
		close(fd_in);
	}
	else if (pos > 0)
	{
		dup2(data->prev_pipe_fd0, 0);
		close(data->prev_pipe_fd0);
	}
	if (pos != 2)
		data->prev_pipe_fd0 = pipe_fd[0];
	builtin(data, cmd);
	dup2(save_fd0, 0);
	dup2(save_fd1, 1);
	close(pipe_fd[1]);
}


int	exec(t_data *data, t_node *node)
{
	int	i;
	int	nbr_cmd;
	t_pipe_node	*pipe;
	int	exit_s;
	int	pid;

	if (node->type == 0)
	{
		if (!do_cmd(data, (t_cmd_node *)node, -1))
			return (0);
		waitpid(0, &exit_s, 0);
		data->exit_status = WEXITSTATUS(exit_s);
		return (1);
	}
	pipe = (t_pipe_node *)node;
	if (pipe->left->type == 1)
		exec(data, pipe->left);
	else
		do_cmd(data, (t_cmd_node *)pipe->left, 0);
	if (node != data->head)
		do_cmd(data, (t_cmd_node *)pipe->right, 1);
	else
	{
		do_cmd(data, (t_cmd_node *)pipe->right, 2);
		nbr_cmd = count_cmd(data->head);
		i = 0;
		while (i != nbr_cmd)
		{
			pid = waitpid(0, &exit_s, 0);
			if (pid == signal_pid)
				data->exit_status = WEXITSTATUS(exit_s);
			i++;
		}
	}
	return (1);
}

