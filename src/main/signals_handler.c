/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:33:19 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/16 15:29:14 by oloncle          ###   ########.fr       */
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

void	set_up_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &signal_handler);
}
