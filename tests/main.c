/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:12:11 by ealgar-c          #+#    #+#             */
/*   Updated: 2025/02/15 22:51:48 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/ft_malloc.h"

int main(void) {
	char *str = malloc(5 * sizeof(char));
	str = "Hola";
	printf("%p - %s\n", &str, str);
	show_alloc_mem();
	char	*new_str = realloc(str, sizeof(str));
	printf("%p - %s\n", &new_str, new_str);
	printf("%s\n", str);
	return 0;
}