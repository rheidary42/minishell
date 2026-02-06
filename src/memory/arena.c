/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:08:31 by rheidary          #+#    #+#             */
/*   Updated: 2026/02/02 20:28:41 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mem_arena	*arena_create(t_u64 capacity)
{
	t_mem_arena	*arena;

	arena = (t_mem_arena *)malloc(capacity);
	if (arena == NULL)
	{
		return (NULL);
	}
	arena->capacity = capacity;
	arena->pos = sizeof(t_mem_arena);
	return (arena);
}

void	*arena_push(t_mem_arena *arena, t_u64 size, t_b32 non_zero,
	t_shell *shell)
{
	t_u64	pos_aligned;
	t_u64	new_pos;
	t_u8	*out;

	pos_aligned = (((t_u64)(arena->pos) + ((t_u64)(sizeof(void *)) - 1))
			& (~((t_u64)(sizeof(void *)) - 1)));
	new_pos = pos_aligned + size;
	if (new_pos > arena->capacity)
	{
		full_exit(shell);
		write(STDERR_FILENO, "Ran out of memory\n", 19);
		exit(1);
	}
	arena->pos = new_pos;
	out = (t_u8 *)arena + pos_aligned;
	if (!non_zero)
	{
		ft_memset(out, 0, size);
	}
	return (out);
}

void	arena_pop(t_mem_arena *arena, t_u64 size)
{
	t_u64	max_pop;

	max_pop = arena->pos - sizeof(t_mem_arena);
	if (size > max_pop)
		size = max_pop;
	arena->pos -= size;
}

void	arena_pop_to(t_mem_arena *arena, t_u64 pos)
{
	t_u64	size;

	size = 0;
	if (pos < arena->pos)
		size = arena->pos - pos;
	arena_pop(arena, size);
}

void	arena_clear(t_mem_arena *arena)
{
	arena_pop_to(arena, sizeof(void *));
}

