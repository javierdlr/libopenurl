/*
**  OpenURL - MUI preferences for openurl.library
**
**  Written by Troels Walsted Hansen <troels@thule.no>
**  Placed in the public domain.
**
**  Developed by:
**  - Alfonso Ranieri <alforan@tin.it>
**  - Stefan Kost <ensonic@sonicpulse.de>
**
**  Ported to OS4 by Alexandre Balaban <alexandre@balaban.name>
**
*/


#include "OpenURL.h"

#if defined(__amigaos4__)
#include <stdarg.h>
#endif

/**************************************************************************/

#define _KEY(k)  ((ULONG)(k)) ? MUIA_ControlChar : TAG_IGNORE, ((ULONG)(k)) ? (ULONG)getKeyChar(NULL,(ULONG)(k)) : 0
#define _HELP(h) ((ULONG)(h)) ? MUIA_ShortHelp   : TAG_IGNORE, ((ULONG)(h)) ? (ULONG)getString((ULONG)(h)) : 0

/***********************************************************************/

#if !defined(__MORPHOS__) && !defined(__amigaos4__)
ULONG STDARGS
DoSuperNew(struct IClass *cl,Object *obj,ULONG tag1,...)
{
    return DoSuperMethod(cl,obj,OM_NEW,&tag1,NULL);
}
#endif

/**************************************************************************/
ULONG
xget(Object *obj,ULONG attribute)
{
    ULONG x;

    get(obj,attribute,&x);

    return x;
}

/**************************************************************************/

Object *
olabel(ULONG id)
{
    return Label((ULONG)getString(id));
}

/****************************************************************************/

Object *
ollabel(ULONG id)
{
    return LLabel((ULONG)getString(id));
}

/****************************************************************************/

Object *
ollabel1(ULONG id)
{
    return LLabel1((ULONG)getString(id));
}

/****************************************************************************/

Object *
olabel1(ULONG id)
{
    return Label1((ULONG)getString(id));
}

/***********************************************************************/

Object *
olabel2(ULONG id)
{
    return Label2((ULONG)getString(id));
}

/****************************************************************************/

Object *
oflabel(ULONG text)
{
    return FreeLabel((ULONG)getString(text));
}

/****************************************************************************/

Object *
obutton(ULONG text,ULONG help)
{
    Object *obj;

    if (obj = MUI_MakeObject(MUIO_Button,(ULONG)getString(text)))
        SetAttrs(obj,MUIA_CycleChain,TRUE,_HELP(help),TAG_DONE);

    return obj;
}

/***********************************************************************/

Object *
oibutton(ULONG spec,ULONG help)
{
    if (spec==IBT_Up) spec = (ULONG)"\33I[6:38]";
    else if (spec==IBT_Down) spec = (ULONG)"\33I[6:39]";
         else return NULL;

    return TextObject,
        _HELP(help),
        MUIA_CycleChain,    TRUE,
        MUIA_Font,          MUIV_Font_Button,
        MUIA_InputMode,     MUIV_InputMode_RelVerify,
        ButtonFrame,
        MUIA_Background,    MUII_ButtonBack,
        MUIA_Text_Contents, spec,
        MUIA_Text_PreParse, MUIX_C,
        MUIA_Text_SetMax,   TRUE,
    End;
}

/****************************************************************************/

Object *
otbutton(ULONG label,ULONG help)
{
    return TextObject,
        _KEY(label),
        _HELP(help),
        MUIA_CycleChain,    TRUE,
        MUIA_Font,          MUIV_Font_Button,
        MUIA_InputMode,     MUIV_InputMode_Toggle,
        ButtonFrame,
        MUIA_Background,    MUII_ButtonBack,
        MUIA_Text_Contents, getString(label),
        MUIA_Text_PreParse, MUIX_C,
        MUIA_Text_HiCharIdx, '_',
    End;
}

/****************************************************************************/

Object *
ocheckmark(ULONG key,ULONG help)
{
    Object *obj;

    if (obj = MUI_MakeObject(MUIO_Checkmark,(ULONG)getString(key)))
        SetAttrs(obj,MUIA_CycleChain,TRUE,_HELP(help),TAG_DONE);

    return obj;
}

/****************************************************************************/

Object *
opopbutton(ULONG img,ULONG help)
{
    Object *obj;

    if (obj = MUI_MakeObject(MUIO_PopButton,img))
        SetAttrs(obj,MUIA_CycleChain,TRUE,_HELP(help),TAG_DONE);

    return obj;
}

/****************************************************************************/

Object *
ostring(ULONG maxlen,ULONG key,ULONG help)
{
    return StringObject,
        _KEY(key),
        _HELP(help),
        MUIA_CycleChain,         TRUE,
        StringFrame,
        MUIA_String_AdvanceOnCR, TRUE,
        MUIA_String_MaxLen,      maxlen,
    End;
}

/***********************************************************************/

Object *
opopport(ULONG maxLen,ULONG key,ULONG help)
{
    return popportObject,
        _HELP(help),
        MUIA_Popport_Key, key,
        MUIA_Popport_Len, maxLen,
    End;
}

/***********************************************************************/

Object *
opopph(UBYTE **syms,UBYTE **names,ULONG maxLen,ULONG key,ULONG asl,ULONG help)
{
    return popphObject,
        _HELP(help),
        MUIA_Popph_Syms,     syms,
        MUIA_Popph_Names,    names,
        MUIA_Popph_MaxLen,   maxLen,
        MUIA_Popph_Key,      key,
        MUIA_Popph_Asl,      asl,
    End;
}

/***********************************************************************/

ULONG
openWindow(Object *app,Object *win)
{
    ULONG v;

    if (win)
    {
        set(win,MUIA_Window_Open,TRUE);
        get(win,MUIA_Window_Open,&v);
        if (!v) get(app,MUIA_Application_Iconified,&v);
    }
    else v = FALSE;

    if (!v) DisplayBeep(0);

    return v;
}

/***********************************************************************/

#ifndef __MORPHOS__
static ULONG fmtfunc = 0x16C04E75;

void STDARGS
msprintf(UBYTE *to,UBYTE *fmt,...)
{
    #if defined(__amigaos4__)
    va_list       va;
    va_startlinear(va,fmt);
    RawDoFmt(fmt,va_getlinearva(va,CONST APTR),(APTR)&fmtfunc,to);
    va_end(va);
    #else
    RawDoFmt(fmt,&fmt+1,(APTR)&fmtfunc,to);
    #endif
}
#endif

/**************************************************************************/

struct stream
{
    UBYTE   *buf;
    int     size;
    int     counter;
    int     stop;
};

#ifdef __MORPHOS__
static void
msnprintfStuff(void)
{
    register struct stream *s = (struct stream *)REG_A3;
    register UBYTE         c  = (UBYTE)REG_D0;
#else
static void SAVEDS ASM
msnprintfStuff(REG(d0,UBYTE c),REG(a3,struct stream *s))
{
#endif
    if (!s->stop)
    {
        if (++s->counter>=s->size)
        {
            *(s->buf) = 0;
            s->stop   = 1;
        }
        else *(s->buf++) = c;
    }
}

#ifdef __MORPHOS__
static struct EmulLibEntry msnprintfStuffTrap = {TRAP_LIB,0,(void *)&msnprintfStuff};
#endif


int
#if !defined( __MORPHOS__ )
STDARGS
#endif
msnprintf(UBYTE *buf,int size,UBYTE *fmt,...)
{
    struct stream s;
    #ifdef __MORPHOS__
    va_list       va;
    va_start(va,fmt);
    #elif defined(__amigaos4__)
    va_list       va;
    va_startlinear(va,fmt);
    #endif

    s.buf     = buf;
    s.size    = size;
    s.counter = 0;
    s.stop    = 0;

    #ifdef __MORPHOS__
    RawDoFmt(fmt,va->overflow_arg_area,(APTR)&msnprintfStuffTrap,&s);
    va_end(va);
    #elif defined(__amigaos4__)
    RawDoFmt(fmt,va_getlinearva(va,CONST APTR),(APTR)msnprintfStuff,&s);
    va_end(va);
    #else
    RawDoFmt(fmt,&fmt+1,(APTR)msnprintfStuff,&s);
    #endif

    return s.counter-1;
}

/**************************************************************************/

ULONG
delEntry(Object *obj,APTR entry)
{
    APTR e;
    int  i;

    for (i = 0; ;i++)
    {
        DoMethod(obj,MUIM_List_GetEntry,i,(ULONG)&e);
        if (!e || e==entry) break;
    }

    if (e) DoMethod(obj,MUIM_List_Remove,i);

    return (ULONG)e;
}

/**************************************************************************/