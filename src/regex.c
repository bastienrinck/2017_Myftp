/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include <zconf.h>
#include <regex.h>
#include <stdbool.h>
#include "ftp.h"

bool	command_control(const char *expr, const char *cmd) {
	bool ret;
	regex_t regex;

	if (regcomp(&regex, expr, REG_NOSUB | REG_ICASE | REG_EXTENDED))
		return (false);
	ret = regexec(&regex, cmd, 0, NULL, 0) == 0;
	regfree(&regex);
	return (ret);
}