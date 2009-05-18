/*
**  RAOpenURL - Reaction preferences for openurl.library
**
**  Copyright (C) 2006 by OpenURL Team
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation; either version 2 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
**  Mailers utility functions declaration
**
**  $Id: mailers.h,v 1.1 2008-09-02 23:24:26 abalabanb Exp $
**
*/
#ifndef MAILERS_H
#define MAILERS_H

#include <intuition/classusr.h>
#include <exec/lists.h>

struct URL_MailerNode;

Object * make_edit_mail_win(void);

BOOL updateMailerList( struct List * list, struct MinList PrefsMailerList );

void updateMailerWindow( struct URL_MailerNode  * pMailer );

#endif // MAILERS_H
