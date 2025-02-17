/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:52:26 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/17 16:27:06 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

bool	check_builtin(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (access(cmd, F_OK) == 0)
	{
		if (ft_strnstr(cmd, "cd", INT_MAX) || ft_strnstr(cmd, "echo", INT_MAX) \
		|| ft_strnstr(cmd, "env", INT_MAX) || ft_strnstr(cmd, "exit", INT_MAX) \
		|| ft_strnstr(cmd, "export", INT_MAX) \
		|| ft_strnstr(cmd, "pwd", INT_MAX) || ft_strnstr(cmd, "unset", INT_MAX))
			return (true);
	}
	else
	{
		if (!ft_strncmp(cmd, "cd", len) || !ft_strncmp(cmd, "echo", len) \
		|| !ft_strncmp(cmd, "env", len) || !ft_strncmp(cmd, "exit", len) \
		|| !ft_strncmp(cmd, "export", len) || !ft_strncmp(cmd, "pwd", len) \
		|| !ft_strncmp(cmd, "unset", len))
			return (true);
	}
	return (false);
}

void	builtin(t_data *data, t_cmd_node *cmd)
{
	if (ft_strnstr(cmd->cmd_name[0], "cd", INT_MAX))
		data->exit_status = ft_cd(data, cmd->cmd_name);
	else if (ft_strnstr(cmd->cmd_name[0], "echo", INT_MAX))
		data->exit_status = ft_echo(cmd->cmd_name);
	else if (ft_strnstr(cmd->cmd_name[0], "env", INT_MAX))
		data->exit_status = ft_env(data->env);
	else if (ft_strnstr(cmd->cmd_name[0], "pwd", INT_MAX))
		data->exit_status = ft_pwd();
	else if (ft_strnstr(cmd->cmd_name[0], "exit", INT_MAX))
		ft_exit(data, cmd->cmd_name);
	else if (ft_strnstr(cmd->cmd_name[0], "export", INT_MAX))
		data->exit_status = ft_export(data, cmd->cmd_name, data->env);
	else if (ft_strnstr(cmd->cmd_name[0], "unset", INT_MAX))
		data->exit_status = ft_unset(data, cmd->cmd_name);
}

void	do_builtin(t_data *data, t_cmd_node *cmd, int *pipe_fd, int pos)
{
	int	save_fd1;
	int	save_fd0;

	save_fd1 = dup(1);
	save_fd0 = dup(0);
	if (pos == 2 || pos == -1)
		close(pipe_fd[0]);
	if (open_outfile_bin(cmd, pos, pipe_fd) == 1)
		return ;
	if (open_infile_bin(cmd, pos, data) == 1)
		return ;
	if (pos != 2)
		data->prev_pipe_fd0 = pipe_fd[0];
	builtin(data, cmd);
	dup2(save_fd0, 0);
	dup2(save_fd1, 1);
	close(pipe_fd[1]);
}

int	exec(t_data *data, t_node *node)
{
	t_pipe_node	*pipe;
	int			exit_s;

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
		wait_all(data);
	}
	return (1);
}
