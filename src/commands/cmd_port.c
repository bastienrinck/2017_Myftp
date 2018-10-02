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
#include <regex.h>
#include <malloc.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "cmd.h"

static bool extract_port_args(client_t *client, unsigned char *addr)
{
	bool ret = true;
	unsigned long tmp;
	regex_t preg;
	regmatch_t *pmatch = malloc(sizeof(*pmatch) * 7);

	regcomp(&preg, RGX_PORT_FIELD, REG_EXTENDED);
	regexec(&preg, client->cmd + 5, 7, pmatch, 0);
	for (int m = 0; m < 6; ++m) {
		tmp = strtoul(&(client->cmd + 5)[pmatch[m + 1].rm_so], NULL,
			10);
		ret = ret && tmp < 256;
		addr[m] = (unsigned char)tmp;
	}
	regfree(&preg);
	free(pmatch);
	return (ret);
}

static bool set_client(client_t *client)
{
	unsigned char chunk[6] = {0};
	char addr[INET_ADDRSTRLEN] = {0};
	short port = 0;

	if (!extract_port_args(client, chunk))
		return (false);
	memset(&client->data.s_in_client, 0, sizeof(struct sockaddr_in));
	port = (in_port_t)(chunk[4] * 256 + chunk[5]);
	sprintf(addr, "%d.%d.%d.%d", chunk[0], chunk[1], chunk[2], chunk[3]);
	client->data.client_fd = socket(AF_INET, SOCK_STREAM, 6);
	client->data.s_in_client.sin_family = AF_INET;
	client->data.s_in_client.sin_port = htons((uint16_t)port);
	client->data.s_in_client.sin_addr.s_addr = inet_addr(addr);
	return (true);
}

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
	return (set_client(client));
}

static void connect_data(client_t *client)
{
	struct sockaddr addr;
	int addrlen = sizeof(addr);

	getsockname(client->data.fd, &addr, (socklen_t *)&addrlen);
	close(client->data.fd);
	close(client->data.client_fd);
	client->data.fd = socket(AF_INET, SOCK_STREAM, 6);
	while (connect(client->data.fd, &addr, (socklen_t)addrlen));
	dprintf(client->client_fd, PORT_OK);
}

void cmd_port(client_t *client)
{
	if (!client->logged) {
		dprintf(client->client_fd, GBL_NOT_LOGGED);
		return;
	}
	clean_session(client);
	if (!command_control(PORT_RGX, client->cmd + 5) ||
		!init_session(client)) {
		dprintf(client->client_fd, PORT_MISSING);
		clean_session(client);
		return;
	}
	client->data.pid = fork();
	if (!client->data.pid)
		process_active(&client->data);
	else
		connect_data(client);
}
