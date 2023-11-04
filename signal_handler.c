/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:53:04 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/04 23:10:57 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

void	handler(int status)
{
	if (status == SIGINT)
	{
		g_signal = CNTRL_C;
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signals(t_data *data)
{
	if (data->mode == INTERACTIVE)
	{
		signal(SIGINT, &handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (data->mode == NON_INTERACTIVE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (data->mode == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	mode(t_data *data, t_mode mode)
{
	data->mode = mode;
	setup_signals(data);
}
