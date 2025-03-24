/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:35:46 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/23 11:35:46 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Entry point of the pipex program.
**
** Expects exactly 4 arguments (excluding program name):
**     ./pipex <infile> <cmd1> <cmd2> <outfile>
**
** If the number of arguments is correct, it calls the core pipex logic.
** Otherwise, it prints a formatted usage error message.
*/
int	main(int ac, char **av, char **envp)
{
	if (ac == 5)
		pipex(av, envp);
	else
	{
		ft_putstr_fd("\033[31mError: Bad arguments\033[0m\n", 2);
		return (1);
	}
	return (0);
}
