/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:20:20 by marvin            #+#    #+#             */
/*   Updated: 2024/03/21 15:20:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Localiser les sep. (pipe & redirections) < > >> << |
Tout ce qui est entre on met dans le noeud (entiereté de la cmd)
On split ensuite
*/


