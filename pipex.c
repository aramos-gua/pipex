/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:03:18 by aramos            #+#    #+#             */
/*   Updated: 2025/05/03 19:11:49 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(void)
{
	int	id;
	int	n;
	int	i;

	id = fork();
	if (id == 0)
		n = 1;
	else
	{
		n = 6;
		wait(0);
	}
	i = n;
	while (i < n + 5)
	{
		printf("%d", i);
		i++;
	}
	return (0);
}
