/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:52:48 by smoore            #+#    #+#             */
/*   Updated: 2025/05/26 13:20:38 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STR_ARR_UTILS_H
# define FT_STR_ARR_UTILS_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include "../LIB/LIBFT/libft.h"

// SRC/FT_STR_ARR_UTILS - for easy work with char* arrays
char	**ft_str_arr_init(void);
char	**ft_str_arr_dup(char **str_arr);
int		ft_str_arr_len(const char **arr);
void	ft_str_arr_partial_free(char **str_arr, int count);
void	ft_str_arr_free(char ***head);

bool	ft_str_arr_contains(char **str_arr, char *str);
char	**ft_str_arr_minus(char **str_arr, char *str);
char	**ft_str_arr_add(char **str_arr, char *str);
void	ft_str_arr_printf(char **str_arr);

int		ft_strcmp(const char *s1, const char *s2);

#endif
