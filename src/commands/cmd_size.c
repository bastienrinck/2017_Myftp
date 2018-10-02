/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/


#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "cmd.h"

void cmd_size(client_t *client)
{
	char *command;
	bool res;
	struct stat sbuf;

	if (!client->logged) {
		dprintf(client->client_fd, GBL_NOT_LOGGED);
		return;
	}
	command = generate_path(client);
	res = (command && strstr(command, client->home) &&
		!stat(command, &sbuf) && S_ISREG(sbuf.st_mode));
	dprintf(client->client_fd, ((res) ? "213 %li\r\n" : SIZE_FAILED),
		sbuf.st_size);
	free(command);
}