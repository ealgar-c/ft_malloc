/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:12:11 by ealgar-c          #+#    #+#             */
/*   Updated: 2025/05/24 12:02:48 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/ft_malloc.h"
#include <string.h>

int main(void) {
	char *str = malloc(5 * sizeof(char));
	printf("ENVIADO -> %p\n", (void *)str);
	str[0] = 'H';
	str[1] = 'o';
	str[2] = 'l';
	str[3] = 'a';
	str[4] = '\0';
	printf("%p - %s\n", &str, str);
	show_alloc_mem();
	char	*new_str = realloc(str, strlen(str) * sizeof(char));
	printf("%p - %s\n", &new_str, new_str);
	printf("%s\n", str);
	return 0;
}
