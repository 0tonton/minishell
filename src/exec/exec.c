/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:52:26 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/09 12:11:40 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

bool	check_builtin(char *cmd)
{
	if (ft_strncmp("cd", cmd, 10) == 0 || ft_strncmp("echo", cmd, 10) == 0 \
	|| ft_strncmp("env", cmd, 10) == 0 || ft_strncmp("exit", cmd, 10) == 0 \
	|| ft_strncmp("export", cmd, 10) == 0 || ft_strncmp("pwd", cmd, 10) == 0 \
	|| ft_strncmp("unset", cmd, 10) == 0)
		return (true);
	return (false);
}

void	builtin(t_data *data, t_cmd_node *cmd)
{
	if (ft_strncmp("cd", cmd->cmd_name[0], 10) == 0)
		data->exit_status = ft_cd(data, cmd->cmd_name);
	else if (ft_strncmp("echo", cmd->cmd_name[0], 10) == 0)
		data->exit_status = ft_echo(cmd->cmd_name);
	else if (ft_strncmp("env", cmd->cmd_name[0], 10) == 0)
		data->exit_status = ft_env(data->env);
	else if (ft_strncmp("pwd", cmd->cmd_name[0], 10) == 0)
		data->exit_status = ft_pwd();
	else if (ft_strncmp("exit", cmd->cmd_name[0], 10) == 0)
		ft_exit(data, cmd->cmd_name);
	else if (ft_strncmp("export", cmd->cmd_name[0], 10) == 0)
		data->exit_status = ft_export(data, cmd->cmd_name, data->env);
	else if (ft_strncmp("unset", cmd->cmd_name[0], 10) == 0)
		data->exit_status = ft_unset(data, cmd->cmd_name, data->env);
}

int	only_cmd(t_data *data, t_cmd_node *cmd)
{
	int		fd_in;
	int		fd_out;
	char	*path;

	if (cmd->input)
	{
		fd_in = open(cmd->input, O_RDONLY);
		if (fd_in < 0)
			return (0);
		dup2(fd_in, 0);
	}
	if (cmd->output)
	{
		if (cmd->append_mode == 1)
			fd_out = open(cmd->output, O_WRONLY | O_CREAT, 0777);
		else
			fd_out = open(cmd->output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd_out < 0)
			return (0);
		dup2(fd_out, 1);
	}
	if (check_builtin(cmd->cmd_name[0]))
		builtin(data, cmd);
	else
	{
		path = NULL;
		init_path(data, cmd->cmd_name[0], &path);
		signal(SIGQUIT, SIG_DFL);
		execve(path, cmd->cmd_name, data->env);
		free(path);
	}
	return (0);
}

int	exec(t_data *data, t_node *node)
{
	t_pipe_node	*pipe;

	if (node->type == 0)
	{
		if (!do_cmd(data, (t_cmd_node *)node, -1))
			return (0);
		return (1);
	}
	pipe = (t_pipe_node *)node;
	if (pipe->left->type == 1)
	{
		if (!exec(data, pipe->left))
			return (0);
	}
	else
	{	
		if (!do_cmd(data, (t_cmd_node *)pipe->left, 0))
			return (0);
	}
	if (node != data->head)
	{
		if (!do_cmd(data, (t_cmd_node *)pipe->right, 1))
			return (0);
	}
	else
	{
		if (!do_cmd(data, (t_cmd_node *)pipe->right, 2))
			return (0);
	}
	return (1);
}

