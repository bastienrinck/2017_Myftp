/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "cmd.h"

static void extract_user_args(client_t *client)
{
	int i = (client->cmd[4] == ' ') ? 5 : 4;

	if (client->user) {
		free(client->user);
		client->user = NULL;
	}
	if (client->cmd[i])
		client->user = strdup(&client->cmd[i]);
}

void cmd_user(client_t *client)
{
	if (client->logged) {
		dprintf(client->client_fd, USER_CONNECTED);
		return;
	}
	extract_user_args(client);
	dprintf(client->client_fd,
		((client->user && command_control(USER_RGX, client->cmd)) ?
			USER_NEED_PASS : GBL_DENIED));
}