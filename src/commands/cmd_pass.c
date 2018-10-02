/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <zconf.h>
#include "cmd.h"

static const tri_str_tuple_t db[2] = {{"Anonymous", 0, 0},
	{"Bastien", "bite", "/home"}};

static void extract_pass_args(client_t *client)
{
	int i = (client->cmd[4] == ' ') ? 5 : 4;

	if (client->pass) {
		free(client->pass);
		client->pass = NULL;
	}
	if (client->cmd[4])
		client->pass = strdup(client->cmd + i);
}

static void client_connected(client_t *client, int i) {
	if (db[i].cw) {
		client->home = db[i].cw;
		free(client->cwd);
		client->cwd = strdup(db[i].cw);
		chdir(client->cwd);
	}
	client->logged = true;
}

void cmd_pass(client_t *client)
{
	bool valid = false;
	int i = -1;

	if (!client->user || client->logged) {
		dprintf(client->client_fd,
			((client->logged) ? USER_LOGGED : PASS_NO_USER));
		return;
	}
	extract_pass_args(client);
	while (!valid && ++i < 2)
		valid = !strcasecmp(db[i].usr, client->user) && (!db[i].pw ||
			(client->pass && !strcmp(db[i].pw, client->pass)));
	if (valid)
		client_connected(client, i);
	dprintf(client->client_fd, ((valid) ? PASS_VALID : PASS_INVALID));
}