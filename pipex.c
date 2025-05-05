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

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(void)
{
	char	*values[] = {"ping", "-c 3","google.com", NULL};
	char	*env[] = {NULL};

	execve("/bin/ping", values, env);
	printf("Success\n");
	return (0);
}
