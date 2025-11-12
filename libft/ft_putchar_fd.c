/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apartowi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:41:44 by apartowi          #+#    #+#             */
/*   Updated: 2024/09/17 14:42:31 by apartowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*#include <fcntl.h>

int main() 
{
    int fd;

//O_WRONLY: Open the file for write-only access.
//You won't be able to read from the file, only write to it.

//O_CREAT: Create the file if it doesn't exist.
//If the file already exists, this flag has no effect on the file's existence.

//O_TRUNC: Truncate the file to zero length if it already exists.
//This means that if the file already contains data, it will be erased,
//and the file will start as an empty file.
    // Open a file (create it if it doesn't exist, truncate if it does)
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	//printf("%d", fd);
    if (fd < 0) {
        // Handle error
        return (1);
    }

    // Write a character to the file descriptor
    ft_putchar_fd('B', fd);

    // Close the file descriptor
    close(fd);

    return (0);
}*/
