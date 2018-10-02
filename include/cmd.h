/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#pragma once

#include "ftp.h"

#define USER_RGX "USER.*"
#define PORT_RGX "^[[:digit:]]{1,3}(,[[:digit:]]{1,3}){5}$"

//Global messages
#define GBL_NOT_LOGGED "530 Please login with USER and PASS.\r\n"
#define GBL_DENIED "530 Permission denied.\r\n"
#define GBL_CMD_UNKNOWN "500 Unknown command.\r\n"
#define GBL_NEW_USER "220 Service ready for new user.\r\n"
#define GBL_CMD_OK "200 command ok.\r\n"

//cmd_help.c
#define HELP_MSG "214 Help message.\r\n"

//cmd_noop.c
#define NOOP_OK "200 NOOP ok.\r\n"

//cmd_pass.c
#define PASS_NO_USER "503 Login with USER first.\r\n"
#define PASS_VALID "230 Login successful.\r\n"
#define PASS_INVALID "530 Login incorrect.\r\n"

//cmd_pwd.c
#define PWD_OK "257 \"%s\"\r\n"

//cmd_quit.c
#define QUIT_MSG "221 Goodbye.\r\n"

//cmd_user.c
#define USER_CONNECTED "530 Can't change from guest user.\r\n"
#define USER_NEED_PASS "331 Please specify the password.\r\n"
#define USER_LOGGED "230 Already logged in.\r\n"

//cmd_cdup.c
#define CDUP_SUCCESS "250 Directory successfully changed.\r\n"
#define CDUP_FAILED "550 Failed to change directory.\r\n"

//cmd_dele.c
#define DELE_DENIED "550 Permission denied.\r\n"
#define DELE_SUCCESS "250 Requested file action okay, completed.\r\n"

//cmd_stor.c
//cmd_retr.c

//cmd_list.c
#define DATA_NOT_SET "425 Use PORT or PASV first.\r\n"
#define DATA_PORT_FAIL "425 Unable to establish data connection.\r\n"
#define DATA_PRE_SEND "150 Here comes the directory listing.\r\n"
#define DATA_POST_SEND "226 Transfer complete.\r\n"
#define DATA_NET_ERROR "426 Network failure.\r\n"
#define DATA_ASCII "150 Opening ASCII mode data connection for %s\r\n"

//cmd_port.c
#define PORT_MISSING "500 Missing/Invalid IP adrdress.\r\n"
#define PORT_OK "200 PORT command successful. Consider using PASV.\r\n"
#define RGX_PORT_FIELD "([[:digit:]]+),([[:digit:]]+),([[:digit:]]+),([[:digit:]]+),([[:digit:]]+),([[:digit:]]+)"

//cmd_retr.c
#define RETR_FAILED "550 Failed to open file.\r\n"

//cmd_stor.c
#define STOR_FAILED "550 Failed to create file.\r\n"

//cmd_feat.c
#define FEAT_MSG "215 UNIX Type L8.\r\n"

//cmd_size.c
#define SIZE_FAILED "550 Could not get file size.\r\n"

void cmd_user(client_t *);
void cmd_pass(client_t *);
void cmd_cwd(client_t *);
void cmd_cdup(client_t *);
void cmd_quit(client_t *);
void cmd_dele(client_t *);
void cmd_pwd(client_t *);
void cmd_pasv(client_t *);
void cmd_port(client_t *);
void cmd_help(client_t *);
void cmd_noop(client_t *);
void cmd_retr(client_t *);
void cmd_stor(client_t *);
void cmd_list(client_t *);
void cmd_type(client_t *);
void cmd_feat(client_t *);
void cmd_size(client_t *);

void data_retr(data_t *, char *);
void data_stor(data_t *, char *);
void data_list(data_t *, char *);
