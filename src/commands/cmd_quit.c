/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#include <stdlib.h>
#include <stdio.h>
#include "cmd.h"

void cmd_quit(client_t *client){
	dprintf(client->client_fd, QUIT_MSG);
	clean_session(client);
	exit(EXIT_SUCCESS);
}