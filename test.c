/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:15:44 by hfiqar            #+#    #+#             */
/*   Updated: 2024/06/12 10:08:10 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    const char* path = getenv("PATH");
    printf("PATH: %s\n", path);

    char* path_copy = strdup(path);
    char* dir = strtok(path_copy, ":");

    printf("%s/ls\n", dir);
    while (dir!= NULL) {
        char cmd_path[1024];
        snprintf(cmd_path, sizeof(cmd_path), "%s/ls", dir);
        if (access(cmd_path, X_OK) == 0) {
            printf("Path to ls: %s\n", cmd_path);
            break;
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return 0;
}
