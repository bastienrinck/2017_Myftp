/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#define _GNU_SOURCE

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ftp.h"

char *extract_args(client_t *client)
{
	int i = (client->cmd[4] == ' ') ? 5 : 4;
	char *str = NULL;

	if (client->cmd[i])
		str = strdup(client->cmd + i);
	return (str);
}

char *check_cwd(char *args)
{
	char *full_path;

	if (args[0] == '/')
		return (args);
	full_path = realpath(args, 0);
	free(args);
	return (full_path);
}

char *check_tild(client_t *client, char *args)
{
	char *full_path = NULL;

	if (args[0] != '~')
		return (args);
	full_path = malloc(strlen(client->home) + strlen(args));
	memset(full_path, 0, strlen(client->home) + strlen(args));
	memcpy(full_path, client->home, strlen(client->home));
	strcat(full_path, args + 1);
	free(args);
	return (full_path);
}

char *generate_path(client_t *client)
{
	char *args = extract_args(client);
	char *tmp;

	if (!args) {
		free(args);
		return (NULL);
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