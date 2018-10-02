/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "cmd.h"

void cmd_dele(client_t *client)
{
	char *file_path = NULL;

	if (!client->user) {
		dprintf(client->client_fd, PASS_NO_USER);
		return;
	} else if (!client->cmd[4] || !(file_path = generate_path(client)) ||
		!strstr(file_path, client->home)) {
		dprintf(client->client_fd, DELE_DENIED);
		if (file_path)
			free(file_path);
		return;
	}
	dprintf(client->client_fd,
		((remove(file_path)) ? DELE_DENIED : DELE_SUCCESS));
}