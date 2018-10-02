/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "cmd.h"

void init_client(srv_t *srv, client_t *client)
{
	memset(client, 0, sizeof(client_t));
	client->home = srv->home;
	client->cwd = strdup(srv->home);
	client->cmd = calloc(2048, sizeof(char));
	client->client_fd = srv->client_fd;
	client->ip = inet_ntoa(srv->s_in_client.sin_addr);
	chdir(client->home);
}

void cmd_unknown(client_t client)
{
	dprintf(client.client_fd,
		((client.logged) ? GBL_CMD_UNKNOWN : GBL_NOT_LOGGED));
}

void proceed_client(srv_t *srv)
{
	client_t client = {0};

	init_client(srv, &client);
	dprintf(client.client_fd, GBL_NEW_USER);
	while (1) {
		get_command(&client);
		proceed_cmd(&client);
		if (client.cmd[0])
			cmd_unknown(client);
	}
}

void start_srv(srv_t *srv)
{
	while (1) {
		if (accept_socket(srv) && !fork()) {
			proceed_client(srv);
			close(srv->client_fd);
		}
	}
}