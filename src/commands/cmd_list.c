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
#include <stdlib.h>
#include <wait.h>
#include <sys/stat.h>
#include "cmd.h"

void data_list(data_t *data, char *pathname)
{
	char *full_cmd = NULL;

	asprintf(&full_cmd, "ls -l %s | tail -n +2", pathname);
	dup2(data->client_fd, 1);
	system(full_cmd);
	exit(EXIT_SUCCESS);
}

static void send_cmd(client_t *client, char *arg)
{
	char c;

	dprintf(client->data.fd, "2");
	dprintf(client->data.fd, "%s", arg);
	read(client->data.fd, &c, 1);
	if (c == '0') {
		dprintf(client->client_fd, DATA_PORT_FAIL);
		return;
	}
	close(client->data.fd);
	dprintf(client->client_fd, DATA_PRE_SEND);
	waitpid(client->data.pid, NULL, 0);
	dprintf(client->client_fd, DATA_POST_SEND);
}

static char *generate_list_path(client_t *client)
{
	char *args = extract_args(client);
	char *tmp;

	if (!args || args[0] == '-') {
		free(args);
		return (strdup(client->cwd));
	}
	if (args[0] == '/') {
		asprintf(&tmp, "%s%s", client->home, args);
		free(args);
		args = tmp;
	}
	args = check_tild(client, args);
	args = check_cwd(args);
	return (args);
}

void cmd_list(client_t *client)
{
	char *arg = NULL;
	struct stat sbuf;

	if (!client->logged || !client->data.pid) {
		dprintf(client->client_fd,
			((!client->logged) ? GBL_NOT_LOGGED : DATA_NOT_SET));
		return;
	}
	arg = generate_list_path(client);
	if (strstr(arg, client->home) && !stat(arg, &sbuf) &&
		S_ISDIR(sbuf.st_mode))
		send_cmd(client, arg);
	else
		dprintf(client->client_fd, GBL_DENIED);
	free(arg);
	clean_session(client);
}