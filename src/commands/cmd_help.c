/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include "cmd.h"

void cmd_help(client_t *client)
{
	if (!client->logged) {
		dprintf(client->client_fd, GBL_NOT_LOGGED);
		return;
	}
	dprintf(client->client_fd, HELP_MSG);
}