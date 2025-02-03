/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:25:16 by oloncle           #+#    #+#             */
/*   Updated: 2025/01/31 11:21:05 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ms.h"
#include "../inc/parsing.h"
#include "../inc/lexing.h"
#include <stdio.h>

void	print_lexer_lst(t_lexer **first_node)
{
	t_lexer	*current;
	int	i;

	current = *first_node;
	i = 0;
	while (current != NULL)
	{
		printf("Node n°%d: str:%s. tok type: %d\n", i, current->str, current->tok_type);
		current = current->next;
		i++;
	}
}

void	print_cmd_name(char **cmd_name, char *in, char *out)
{
	char	*mot;
	int	i;

	i = 0;
	mot = cmd_name[0];
	while (mot)
	{
		printf("[%s] ", mot);
		i++;
		mot = cmd_name[i];
	}
	printf("\ninput name: %s\noutput name: %s\n", in, out);
}

void	print_children(t_pipe_node *parent)
{
	if (parent->left && parent->right)
	{
		printf("\t-- Left child -- Right child --\ntype:\t\t%d      --     %d\n", parent->left->type, parent->right->type);
		if (parent->left->type == CMD)
		{
			printf("Left cmd: ");
			print_cmd_name(((t_cmd_node *)parent->left)->cmd_name, ((t_cmd_node *)parent->left)->input, ((t_cmd_node *)parent->left)->output);
			printf("\n");
		}
		if (parent->right->type == CMD)
		{
			printf("Right cmd: ");
			print_cmd_name(((t_cmd_node *)(parent->right))->cmd_name, ((t_cmd_node *)(parent->right))->input, ((t_cmd_node *)(parent->right))->output);
			printf("\n\n");
		}
	}
}

void	print_ast(t_node *top_node)
{
	t_node	*current_parent;

	current_parent = top_node;
	if (current_parent->type == CMD)
	{
		printf("Sole node CMD: ");
		print_cmd_name(((t_cmd_node *)current_parent)->cmd_name, ((t_cmd_node *)current_parent)->input, ((t_cmd_node *)current_parent)->output);
		printf("\n");
	}
	while (current_parent && current_parent->type == PIPE)
	{
		print_children((t_pipe_node *)current_parent);
		current_parent = ((t_pipe_node *)current_parent)->left;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_lexer	**lex_lst;
	t_node	*top_node;

	(void)(argc);
	(void)(argv);
	(void)(env);
	while (1)
	{
		lex_lst = NULL;
		top_node = NULL;
		printf("\033[0;31m");
		printf("minishell> ");
		printf("\033[0m");
		line = readline(" ");
		if (line == NULL || line[0] == 0)
		{
			printf("ERROR LINE\n");	
		}
		else
		{
			lex_lst = lexer_line(line);
			if (lex_lst)
			{
				//print_lexer_lst(lex_lst);
				top_node = creating_tree(lex_lst);
				print_ast(top_node);
			}
			printf("EOL\n");
		}
		if (lex_lst)
			free_lexer(lex_lst);
		if (top_node)
			free_ast(top_node);
		if (line && line[0] != 0)
			free(line);
	}
}
