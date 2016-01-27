/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 15:03:43 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/27 17:31:51 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libdodo.h"
# include "op.h"
# include <fcntl.h>

void	print_memory(const void *addr, size_t size);

#endif
