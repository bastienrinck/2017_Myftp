/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <zconf.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/stat.h>
#include "cmd.h"

void data_retr(data_t *data, char *pathname)
{
	dup2(data->client_fd, 1);
	execlp("cat", "cat", pathname, NULL);
}

static void send_cmd(client_t *client, char *arg)
{
	char c;

	dprintf(client->data.fd, "0");
	dprintf(client->data.fd, "%s", arg);
	read(client->data.fd, &c, 1);
	if (c == '0') {
		dprintf(client->client_fd, DATA_PORT_FAIL);
		return;
	}
	close(client->data.fd);
	dprintf(client->client_fd, DATA_ASCII, client->cmd + 5);
	waitpid(client->data.pid, NULL, 0);
	dprintf(client->client_fd, DATA_POST_SEND);
}

void cmd_retr(client_t *client)
{
	char *command;
	struct stat sbuf;

	if (!client->logged || !client->data.pid) {
		dprintf(client->client_fd,
			((!client->logged) ? GBL_NOT_LOGGED : DATA_NOT_SET));
		return;
	}
	command = generate_path(client);
	if (command && strstr(command, client->home) && !stat(command, &sbuf) &&
		S_ISREG(sbuf.st_mode) && !access(command, R_OK))
		send_cmd(client, command);
	else
		dprintf(client->client_fd, RETR_FAILED);
	free(command);
	clean_session(client);
}