/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "ftp.h"

bool accept_socket(srv_t *srv)
{
	socklen_t s_size = sizeof(struct sockaddr);

	if ((srv->client_fd = accept(srv->master_fd,
		(struct sockaddr *)&(srv->s_in_client), &s_size)) == -1)
		return (my_error(strerror(errno)));
	printf("[%s] Connection established\n",
		inet_ntoa(srv->s_in_client.sin_addr));
	return (true);
}

bool listen_socket(srv_t *srv)
{
	if (listen(srv->master_fd, 1024) == -1)
		return (my_error(strerror(errno)));
	return (true);
}

bool bind_socket(srv_t *srv)
{
	if (bind(srv->master_fd, (const struct sockaddr *)&srv->s_in,
		sizeof(srv->s_in)) == -1)
		return (my_error(strerror(errno)));
	return (true);
}

bool create_socket(srv_t *srv)
{
	srv->master_fd = socket(AF_INET, SOCK_STREAM, 6);
	if (srv->master_fd == -1)
		return (my_error(strerror(errno)));
	if ((setsockopt(srv->master_fd, SOL_SOCKET, SO_REUSEADDR, &(int){1},
		sizeof(int))) == -1)
		return (my_error(strerror(errno)));
	return (true);
}
