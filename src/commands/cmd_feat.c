/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include "cmd.h"

void cmd_feat(client_t *client)
{
	dprintf(client->client_fd, FEAT_MSG);
}