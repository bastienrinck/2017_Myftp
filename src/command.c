/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#include <malloc.h>
#include <string.h>
#include <zconf.h>
#include "cmd.h"

static const char *cmd_name[] = {"USER", "PASS", "CWD", "CDUP", "QUIT", "DELE",
	"PWD", "PASV", "PORT", "HELP", "NOOP", "RETR", "STOR", "LIST", "TYPE",
	"FEAT", "SIZE"};

static void epur_command(const char *str, char *tmp, int i, int k) {
	while (str && str[i]) {
		tmp[k++] = str[i++];
		while ((str[i] == ' ') || (str[i] == '\t'))
			i++;
		if (((str[i - 1] == ' ') || (str[i - 1] == '\t')) &&
			(str[i] != '\0')) {
			tmp[k] = ' ';
			k++;
		}
	}
	tmp[k] = 0;
}

void epur_str(char *str)
{
	char *tmp;
	int i = 0;
	int k = 0;

	tmp = malloc(strlen(str) + 1);
	if (!tmp)
		return ;
	while (str && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str && !str[i])
		return;
	epur_command(str, tmp, i, k);
	memset(str, 0, 2048);
	memcpy(str, tmp, strlen(tmp));
	free(tmp);
}

void get_command(client_t *client)
{
	char msgbuf = 0;

	for (int idx = -1; msgbuf != '\r' && msgbuf != '\n';) {
		if (read(client->client_fd, &msgbuf, 1)) {
			client->cmd[++idx % BUFFER_SIZE] = msgbuf;
			client->cmd[(idx + 1) % BUFFER_SIZE] = 0;
		}
	}
	read(client->client_fd, &msgbuf, 1);
	client->cmd[strlen(client->cmd) - 1] = 0;
	epur_str(client->cmd);
	printf("[%s] %s\n", client->ip, client->cmd);
}

void proceed_cmd(client_t *client)
{
	static void (*fcmd[])(client_t *) = {&cmd_user, &cmd_pass, &cmd_cwd,
		&cmd_cdup, &cmd_quit, &cmd_dele, &cmd_pwd, &cmd_pasv, &cmd_port,
		&cmd_help, &cmd_noop, &cmd_retr, &cmd_stor, &cmd_list,
		&cmd_type, &cmd_feat, &cmd_size};

	for (int i = 0; i < CMD_AVAILABLE; i++) {
		if (!strncasecmp(cmd_name[i], client->cmd,
			strlen(cmd_name[i]))) {
			fcmd[i](client);
			memset(client->cmd, 0, 2048);
			break;
		}
	}
}
