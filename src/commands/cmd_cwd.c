/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "cmd.h"

void cmd_cwd(client_t *client)
{
	char *new_path = NULL;

	if (!client->logged || !(new_path = generate_path(client))) {
		dprintf(client->client_fd,
			((!client->logged) ? GBL_NOT_LOGGED : CDUP_FAILED));
		free(new_path);
		return;
	}
	if (!strstr(new_path, client->home) || !chdir(new_path))
		dprintf(client->client_fd, CDUP_SUCCESS);
	else
		dprintf(client->client_fd, CDUP_FAILED);
	free(new_path);
	free(client->cwd);
	client->cwd = realpath(".", 0);
}