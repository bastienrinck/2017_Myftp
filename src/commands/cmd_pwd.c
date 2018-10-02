/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include <string.h>
#include "cmd.h"

void cmd_pwd(client_t *client)
{
	bool equal = strlen(client->home) == strlen(client->cwd);

	dprintf(client->client_fd, ((client->logged) ? PWD_OK : GBL_NOT_LOGGED),
		((equal) ? "/" : client->cwd + strlen(client->home)));
}