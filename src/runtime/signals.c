/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:17:28 by kgebski           #+#    #+#             */
/*   Updated: 2023/06/16 15:24:15 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//! In interactive mode it works but inside a program it has to give back
// one prompt insted of two and it should print the signal ;/

static void	pc_sigint_handler(int signal)
{
	if (signal)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	pc_sigquit_handler(int signal)
{
	if (signal)
	{
		exit(EXIT_FAILURE);
	}
}

void	pc_signals_interactive(void)
{
	signal(SIGINT, pc_sigint_handler);
	signal(SIGTSTP, pc_sigquit_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	pc_proc_signal_handler(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
