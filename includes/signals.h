/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:21:06 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/18 11:21:06 by haloztur         ###   ########.fr       */
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
