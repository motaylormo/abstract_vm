/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unix_text.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 12:36:10 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/09 12:36:11 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIX_TEXT_H
# define UNIX_TEXT_H

/*
**	Off
*/
# define COLOR_OFF	"\e[0m"

/*
**	Text variations
**		Does not work: BLINK, HIDDEN, STRIKETHU
*/
# define BOLD		"\e[1m"
# define DIM		"\e[2m"
# define ITALIC		"\e[3m"
# define UNDERLINE	"\e[4m"
# define BLINK		"\e[5m"
# define INVERSE	"\e[7m"
# define HIDDEN		"\e[8m"
# define STRIKETHU	"\e[9m"

/*
**	Text colors
*/
# define BLK	"\e[30m"
# define RED	"\e[31m"
# define GRN	"\e[32m"
# define YLW	"\e[33m"
# define BLU	"\e[34m"
# define VIO	"\e[35m"
# define CYN	"\e[36m"
# define WHT	"\e[37m"

/*
**	Bright/light/intense text colors
*/
# define B_BLK	"\e[90m"
# define B_RED	"\e[91m"
# define B_GRN	"\e[92m"
# define B_YLW	"\e[93m"
# define B_BLU	"\e[94m"
# define B_VIO	"\e[95m"
# define B_CYN	"\e[96m"
# define B_WHT	"\e[97m"

/*
**	Background colors
*/
# define ON_BLK		"\e[40m"
# define ON_RED		"\e[41m"
# define ON_GRN		"\e[42m"
# define ON_YLW		"\e[43m"
# define ON_BLU		"\e[44m"
# define ON_VIO		"\e[45m"
# define ON_CYN		"\e[46m"
# define ON_WHT		"\e[47m"

/*
**	Bright/light/intense background colors
*/
# define ON_B_BLK	"\e[100m"
# define ON_B_RED	"\e[101m"
# define ON_B_GRN	"\e[102m"
# define ON_B_YLW	"\e[103m"
# define ON_B_BLU	"\e[104m"
# define ON_B_VIO	"\e[105m"
# define ON_B_CYN	"\e[106m"
# define ON_B_WHT	"\e[107m"

#endif