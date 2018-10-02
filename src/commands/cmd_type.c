/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include "cmd.h"

void cmd_type(client_t *client)
{
	dprintf(client->client_fd, GBL_CMD_OK);
}