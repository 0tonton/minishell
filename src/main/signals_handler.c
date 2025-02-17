/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:33:19 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/17 16:06:44 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

void	signal_handler(int signum)
{
	(void)(signum);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_signal_pid == 0)
		rl_redisplay();
}

void	signal_handler_segv(int signum)
{
	(void)(signum);
	write(2, "Segmentation fault\n", 19);
	exit(11);
}

void	set_up_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, &signal_handler_segv);
	signal(SIGINT, &signal_handler);
}
