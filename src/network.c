/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/


#include <arpa/inet.h>
#include <ifaddrs.h>
#include <stdio.h>
#include "ftp.h"

static bool get_socket_info(int socket, struct sockaddr_in *addr)
{
	socklen_t len = sizeof(*addr);
	return ((bool)(getsockname(socket, (struct sockaddr *)addr, &len) + 1));
}

static void display_addr(client_t *client, struct sockaddr_in *iface, int port)
{
	char ipa[INET_ADDRSTRLEN] = {0};

	inet_ntop(AF_INET, &(iface->sin_addr), ipa, INET_ADDRSTRLEN);
	for (int i = 0; i < INET_ADDRSTRLEN; ++i)
		ipa[i] = (char)((ipa[i] == '.') ? ',' : ipa[i]);
	dprintf(client->client_fd, "227 Entering Passive Mode (%s,%d,%d)\r\n",
		ipa, port / 256, port % 256);
}

void display_network_addr(client_t *client, int port)
{
	struct ifaddrs *ifap;
	struct sockaddr_in addr;
	struct sockaddr_in *iface;

	if (getifaddrs(&ifap) == -1 ||
		!get_socket_info(client->client_fd, &addr)) {
		display_addr(client, NULL, port);
		return;
	}
	for (struct ifaddrs *head = ifap; head; head = head->ifa_next)
		if (head->ifa_addr && head->ifa_addr->sa_family == AF_INET) {
			iface = (struct sockaddr_in *)head->ifa_addr;
			if (iface->sin_addr.s_addr == addr.sin_addr.s_addr) {
				display_addr(client, iface, port);
				freeifaddrs(ifap);
				return;
			}
		}
	display_addr(client, NULL, port);
}