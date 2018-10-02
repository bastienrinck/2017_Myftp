/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/


#include <stdio.h>
#include <zconf.h>
#include <fcntl.h>
#include <string.h>
#include <wait.h>
#include <malloc.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "cmd.h"

void data_stor(data_t *data, char *pathname)
{
	int fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0644);

	dup2(fd, 1);
	dup2(data->client_fd, 0);
	execlp("cat", "cat", NULL);
}

static void send_cmd(client_t *client, char *arg)
{
	char c;

	dprintf(client->data.fd, "1");
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

void cmd_stor(client_t *client)
{
	char *command = NULL;
	struct stat sbuf;

	if (!client->logged || !client->data.pid) {
		dprintf(client->client_fd,
			((!client->logged) ? GBL_NOT_LOGGED : DATA_NOT_SET));
		return;
	}
	command = generate_path(client);
	if (command && strstr(command, client->home) &&
		(access(command, F_OK) ||
			(!stat(command, &sbuf) && S_ISREG(sbuf.st_mode) &&
				!access(command, W_OK))))
		send_cmd(client, command);
	else
		dprintf(client->client_fd, GBL_DENIED);
	free(command);
	clean_session(client);
}