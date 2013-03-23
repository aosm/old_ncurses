/****************************************************************************
 * Copyright (c) 1998,2000,2001 Free Software Foundation, Inc.              *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, distribute with modifications, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is    *
 * furnished to do so, subject to the following conditions:                 *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR    *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR    *
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 *                                                                          *
 * Except as contained in this notice, the name(s) of the above copyright   *
 * holders shall not be used in advertising or otherwise to promote the     *
 * sale, use or other dealings in this Software without prior written       *
 * authorization.                                                           *
 ****************************************************************************/

/****************************************************************************
 *  Author: Zeyd M. Ben-Halim <zmbenhal@netcom.com> 1992,1995               *
 *     and: Eric S. Raymond <esr@snark.thyrsus.com>                         *
 ****************************************************************************/

/*
**	lib_insch.c
**
**	The routine winsch().
**
*/

#include <curses.priv.h>

MODULE_ID("$Id: lib_insch.c,v 1.1.1.1 2001/11/29 20:40:56 jevans Exp $")

NCURSES_EXPORT(int)
winsch(WINDOW *win, chtype c)
{
    int code = ERR;

    T((T_CALLED("winsch(%p, %s)"), win, _tracechtype(c)));

    if (win) {
	struct ldat *line = &(win->_line[win->_cury]);
	NCURSES_CH_T *end = &(line->text[win->_curx]);
	NCURSES_CH_T *temp1 = &(line->text[win->_maxx]);
	NCURSES_CH_T *temp2 = temp1 - 1;
	NCURSES_CH_T wch;
	SetChar2(wch, c);

	CHANGED_TO_EOL(line, win->_curx, win->_maxx);
	while (temp1 > end)
	    *temp1-- = *temp2--;

	*temp1 = _nc_render(win, wch);
	code = OK;
    }
    returnCode(code);
}
