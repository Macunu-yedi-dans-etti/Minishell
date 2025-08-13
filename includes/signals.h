/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:28:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/07/19 21:28:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "types.h"

/* Signal handling */
void			handle_sigint(int sig);
void			handle_sigquit(int sig);
void			setup_signals(t_req *req);
void			reset_signals(void);
void			set_signal_req(t_req *req);

#endif
