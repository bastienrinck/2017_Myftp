/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include "ftp.h"

bool my_error(char *error_msg)
{
	dprintf(2, "%s\n", error_msg);
	return (false);
}

static bool set_socket(srv_t *srv, char **av)
{
	srv->home = realpath(av[2], NULL);
	srv->port = (unsigned short)atoi(av[1]);
	srv->s_in.sin_family = AF_INET;
	srv->s_in.sin_port = htons(srv->port);
	srv->s_in.sin_addr.s_addr = INADDR_ANY;
	if (!create_socket(srv) || !bind_socket(srv) || !listen_socket(srv))
		return (false);
	return (true);
}

static int usage(char *name)
{
	dprintf(2, "USAGE:\t%s port path\n", name);
	dprintf(2, USG_PORT);
	dprintf(2, USG_PATH);
	return 84;
}

int main(int ac, char **av)
{
	srv_t srv;

	if (ac == 2 && !strcmp(av[1], "-help"))
		return (usage(av[0]));
	else if (ac != 3)
		return (84);
	if (!set_socket(&srv, av))
		return (84);
	start_srv(&srv);
}