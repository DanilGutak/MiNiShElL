/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:53:04 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/04 13:14:03 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal = 0;

void handler(int status)
{
	(void)status;
	g_signal = CNTRL_C;
	write(STDERR_FILENO, "\n", 1);
	// rl_replace_line("", 0);
	rl_on_new_line();
}

void setup_signals(t_data *data)
{
	if (data->mode == INTERACTIVE) // heredoc, prompt
	{
		signal(SIGINT, &handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (data->mode == NON_INTERACTIVE) // child
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
