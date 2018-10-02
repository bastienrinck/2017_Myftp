/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include <zconf.h>
#include <string.h>
#include <errno.h>
#include "cmd.h"

static bool init_session(client_t *client)
{
	client->data.fd = socket(AF_INET, SOCK_STREAM, 6);
	if (client->data.fd == -1)
		return (my_error(strerror(errno)));
	client->data.s_in_data.sin_family = AF_INET;
	client->data.s_in_data.sin_port = 0;
	client->data.s_in_data.sin_addr.s_addr = INADDR_ANY;
	if (bind(client->data.fd,
		(const struct sockaddr *)&client->data.s_in_data,
		sizeof(client->data.s_in_data)) == -1)
		return (false);
	return (true);
}

static void connect_data(client_t *client)
{
	struct sockaddr addr;
	int addrlen = sizeof(addr);

	getsockname(client->data.fd, &addr, (socklen_t *)&addrlen);
	close(client->data.fd);
	client->data.fd = socket(AF_INET, SOCK_STREAM, 6);
	while (connect(client->data.fd, &addr, (socklen_t)addrlen));
	display_network_addr(client,
		ntohs(((struct sockaddr_in *)&addr)->sin_port));
}

void cmd_pasv(client_t *client)
{
	if (!client->logged) {
		dprintf(client->client_fd, GBL_NOT_LOGGED);
		return;
	}
	clean_session(client);
	init_session(client);
	client->data.pid = fork();
	if (!client->data.pid)
		process_passive(&client->data);
	else
		connect_data(client);
}
