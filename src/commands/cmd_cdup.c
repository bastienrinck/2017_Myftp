/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <zconf.h>
#include "cmd.h"

void cmd_cdup(client_t *client)
{
	char *new_path;

	if (!client->logged) {
		dprintf(client->client_fd, GBL_NOT_LOGGED);
		return;
	}
	new_path = realpath("..", NULL);
	if (strstr(new_path, client->home)) {
		free(client->cwd);
		client->cwd = new_path;
		dprintf(client->client_fd,
			((chdir(client->cwd)) ? CDUP_FAILED : CDUP_SUCCESS));
	} else {
		free(new_path);
		dprintf(client->client_fd, CDUP_SUCCESS);
	}
}