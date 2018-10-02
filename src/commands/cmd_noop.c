/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include "cmd.h"

void cmd_noop(client_t *client)
{
	dprintf(client->client_fd,
		((client->logged) ? NOOP_OK : GBL_NOT_LOGGED));
}