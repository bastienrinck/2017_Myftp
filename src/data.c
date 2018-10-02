/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <zconf.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include "cmd.h"

static void (*fcmd[])(data_t *, char *) = {&data_retr, &data_stor, &data_list};

void clean_session(client_t *client)
{
	if (!client->data.pid)
		return;
	kill(client->data.pid, SIGKILL);
	close(client->data.fd);
	memset(&client->data, 0, sizeof(data_t));
}

void get_and_process(data_t *data)
{
	char idx = 0;
	char msgbuf[1024] = {0};

	read(data->father_fd, &idx, 1);
	read(data->father_fd, &msgbuf, 1024);
	dprintf(data->father_fd, "%c", '0' + (data->client_fd != -1));
	if (data->client_fd == -1)
		exit(EXIT_FAILURE);
	fcmd[idx - '0'](data, msgbuf);
}

void process_active(data_t *data)
{
	struct sockaddr *client = (struct sockaddr *)&data->s_in_client;
	struct sockaddr *father = (struct sockaddr *)&data->s_in_data;
	socklen_t s_size = sizeof(struct sockaddr);

	listen(data->fd, 1024);
	data->father_fd = accept(data->fd, father, &s_size);
	connect(data->client_fd, client, sizeof(*client));
	get_and_process(data);
}

void process_passive(data_t *data)
{
	struct sockaddr *client = (struct sockaddr *)&data->s_in_client;
	struct sockaddr *father = (struct sockaddr *)&data->s_in_data;
	socklen_t s_size = sizeof(struct sockaddr);

	listen(data->fd, 1024);
	data->father_fd = accept(data->fd, father, &s_size);
	data->client_fd = accept(data->fd, client, &s_size);
	get_and_process(data);
}