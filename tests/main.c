/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:12:11 by ealgar-c          #+#    #+#             */
/*   Updated: 2025/07/05 14:34:13 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_malloc.h"
#include <string.h>

#define GREEN   "\033[0;32m"
#define BLUE    "\033[0;34m"
#define RESET   "\033[0m"
#define YELLOW   "\033[0;33m"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:12:11 by ealgar-c          #+#    #+#             */
/*   Updated: 2025/07/05 15:55:50 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_malloc.h"
#include <string.h>

#define GREEN   "\033[0;32m"
#define BLUE    "\033[0;34m"
#define YELLOW  "\033[0;33m"
#define RESET   "\033[0m"

int test_00(void) {
	char *str = malloc(12);
	if (!str)
		return -1;
	ft_printf(BLUE "\tAllocated 12 bytes string at %p\n" RESET, str);
	ft_strlcpy(str, "Hello world", 12);
	ft_printf(BLUE "\tContents at %p: %s\n" RESET, str, str);
	show_alloc_mem();
	free(str);
	ft_printf(BLUE "\tFreed memory at %p\n" RESET, str);
	show_alloc_mem();
	return 0;
}

int test_01(void) {
	int *arr = malloc(210 * sizeof(int));
	if (!arr)
		return -1;
	ft_printf(BLUE "\tAllocated int array at %p (size: %d bytes)\n" RESET, arr, 210 * (int)sizeof(int));
	for (int i = 0; i < 210; i++)
		arr[i] = i * i;
	ft_printf(BLUE "\tContents at %p: [%d, %d, %d, ...]\n" RESET, arr, arr[0], arr[1], arr[2]);
	show_alloc_mem();
	free(arr);
	ft_printf(BLUE "\tFreed memory at %p\n" RESET, arr);
	show_alloc_mem();
	return 0;
}

int test_02(void) {
	char *big_str = malloc(1024 * 1024);
	if (!big_str)
		return -1;
	ft_printf(BLUE "\tAllocated 1 MB block at %p\n" RESET, big_str);
	ft_memset(big_str, 'A', 1024 * 1024);
	ft_printf(BLUE "\tFirst 16 bytes at %p: ", big_str);
	for (int i = 0; i < 16; i++)
		ft_printf("%c", big_str[i]);
	ft_printf("\n" RESET);
	show_alloc_mem();
	free(big_str);
	ft_printf(BLUE "\tFreed memory at %p\n" RESET, big_str);
	show_alloc_mem();
	return 0;
}

int test_03(void) {
	char *str = malloc(6);
	if (!str)
		return -1;
	ft_strlcpy(str, "Hello", 6);
	ft_printf(BLUE "\tAllocated 6 bytes string at %p\n" RESET, str);
	ft_printf(BLUE "\tContents at %p: %s\n" RESET, str, str);
	show_alloc_mem();
	char *new_str = realloc(str, 12);
	if (!new_str)
		return -1;
	ft_strlcat(new_str, " world", 12);
	ft_printf(BLUE "\tReallocated to 12 bytes at %p\n" RESET, new_str);
	ft_printf(BLUE "\tContents at %p: %s\n" RESET, new_str, new_str);
	show_alloc_mem();
	free(new_str);
	ft_printf(BLUE "\tFreed memory at %p\n" RESET, new_str);
	show_alloc_mem();
	return 0;
}

int test_04(void) {
	int *data = malloc(20 * sizeof(int));
	if (!data)
		return -1;
	ft_printf(BLUE "\tAllocated int array at %p (size: %d bytes)\n" RESET, data, 20 * (int)sizeof(int));
	for (int i = 0; i < 20; i++)
		data[i] = i;
	ft_printf(BLUE "\tContents at %p: [%d, %d, %d, ...]\n" RESET, data, data[0], data[1], data[2]);
	show_alloc_mem();
	free(data);
	ft_printf(BLUE "\tFreed memory at %p\n" RESET, data);
	show_alloc_mem();
	return 0;
}

int test_05(void) {
	void *ptrs[15];
	int sizes[15] = {8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072};

	ft_printf(BLUE "\tAllocating 15 blocks of increasing sizes...\n" RESET);
	for (int i = 0; i < 15; i++) {
		ptrs[i] = malloc(sizes[i]);
		if (!ptrs[i])
			return -1;
		ft_memset(ptrs[i], 'A' + (i % 26), sizes[i]);
		ft_printf(BLUE "\tBlock %d: %d bytes at %p, first 8 bytes: ", i, sizes[i], ptrs[i]);
		for (int j = 0; j < 8; j++)
			ft_printf("%c", ((char *)ptrs[i])[j]);
		ft_printf("\n" RESET);
	}
	show_alloc_mem();

	ft_printf(BLUE "\tFreeing some blocks (3,7,11)...\n" RESET);
	free(ptrs[3]); ft_printf(BLUE "\tFreed memory at %p\n" RESET, ptrs[3]);
	free(ptrs[7]); ft_printf(BLUE "\tFreed memory at %p\n" RESET, ptrs[7]);
	free(ptrs[11]); ft_printf(BLUE "\tFreed memory at %p\n" RESET, ptrs[11]);
	show_alloc_mem();

	ft_printf(BLUE "\tReallocating block 4 from %d to %d bytes\n" RESET, sizes[4], sizes[4] * 2);
	ptrs[4] = realloc(ptrs[4], sizes[4] * 2);
	if (!ptrs[4])
		return -1;
	ft_memset(ptrs[4], '*', sizes[4] * 2);
	ft_printf(BLUE "\tBlock 4 after realloc: %d bytes at %p, first 8 bytes: ", sizes[4] * 2, ptrs[4]);
	for (int j = 0; j < 8; j++)
		ft_printf("%c", ((char *)ptrs[4])[j]);
	ft_printf("\n" RESET);
	show_alloc_mem();

	ft_printf(BLUE "\tFreeing all blocks...\n" RESET);
	for (int i = 0; i < 15; i++)
		if (ptrs[i]) {
			free(ptrs[i]);
			ft_printf(BLUE "\tFreed memory at %p\n" RESET, ptrs[i]);
		}
	show_alloc_mem();
	return 0;
}

int test_150_tiny(void) {
	void *ptrs[150];

	ft_printf(BLUE "\tAllocating 150 TINY blocks...\n" RESET);
	for (int i = 0; i < 150; i++) {
		ptrs[i] = malloc(200);
		if (!ptrs[i])
			return -1;
		ft_memset(ptrs[i], 'a' + (i % 26), 200);
		if (i < 3 || i >= 147) {
			ft_printf(BLUE "\tBlock %d at %p, first 8 bytes: ", i, ptrs[i]);
			for (int j = 0; j < 8; j++)
				ft_printf("%c", ((char *)ptrs[i])[j]);
			ft_printf("\n" RESET);
		}
	}
	show_alloc_mem();

	ft_printf(BLUE "\tFreeing all 150 blocks...\n" RESET);
	for (int i = 0; i < 150; i++) {
		free(ptrs[i]);
		if (i < 3 || i >= 147)
			ft_printf(BLUE "\tFreed memory at %p\n" RESET, ptrs[i]);
	}
	show_alloc_mem();
	return 0;
}



int main(void) {
	ft_printf(GREEN "\t\tSTARTING MALLOC TESTS:\n" RESET);

	ft_printf(YELLOW "\t\t00 - Hello world\n" RESET);
	test_00();

	ft_printf(YELLOW "\n\t\t01 - Int array allocation\n" RESET);
	test_01();

	ft_printf(YELLOW "\n\t\t02 - Large allocation (1 MB)\n" RESET);
	test_02();

	ft_printf(YELLOW "\n\t\t03 - Realloc growing string\n" RESET);
	test_03();

	ft_printf(YELLOW "\n\t\t04 - Allocate and free int array\n" RESET);
	test_04();

	ft_printf(YELLOW "\n\t\t05 - 15 mallocs, realloc and frees\n" RESET);
	test_05();

	ft_printf(YELLOW "\n\t\tFINAL - test_150_tiny_mallocs\n" RESET);
	test_150_tiny();

	return 0;
}
