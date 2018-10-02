/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#pragma once

#include <stdbool.h>
#include <netinet/in.h>

#define USG_PORT "port\tis the port number on which the server socket listens\n"
#define USG_PATH "path\tis the path to the home directory for the Anonymous user\n"

#define BUFFER_SIZE 2048
#define CMD_AVAILABLE 17

typedef struct data_s {
	int fd;
	int father_fd;
	int client_fd;
	int pid;
	struct sockaddr_in s_in_data;
	struct sockaddr_in s_in_client;
} data_t;

typedef struct tri_str_tuple_s {
	char *usr;
	char *pw;
	char *cw;
} tri_str_tuple_t;

typedef struct srv_s {
	unsigned short port;
	int master_fd;
	int client_fd;
	char *home;
	struct sockaddr_in s_in;
	struct sockaddr_in s_in_client;
} srv_t;

typedef struct client_s {
	char *ip;
	char *user;
	char *pass;
	char *cmd;
	char *home;
	char *cwd;
	int client_fd;
	bool logged;
	data_t data;
} client_t;

bool my_error(char *);
bool create_socket(srv_t *);
bool bind_socket(srv_t *);
bool listen_socket(srv_t *);
bool accept_socket(srv_t *);
bool command_control(const char *, const char *);
void start_srv(srv_t *);
void process_passive(data_t *);
void process_active(data_t *);
void clean_session(client_t *);
char *generate_path(client_t *);
char *check_tild(client_t *, char *);
char *check_cwd(char *);
char *extract_args(client_t *);
void get_command(client_t *);
void proceed_cmd(client_t *);
void display_network_addr(client_t *, int);