/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "alacritty"
#define TERMCLASS "alacritty"
#define BROWSER "chromium"
#define BAR_TRANS 0  // Disable transparency for the status bar

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int snap      = 16;       /* snap pixel */
static unsigned int gappih    = 5;       /* horiz inner gap between windows */
static unsigned int gappiv    = 5;       /* vert inner gap between windows */
static unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static char *fonts[]          = { "NerdFontMono-Regular:size=12", "SymbolsNerdFontMono-Regular:pixelsize=14:antialias=true:autohint=true"  };
static char normbgcolor[]           = "#03070a"; // Exterior BG
static char normbordercolor[]       = "#130000";
static char normfgcolor[]           = "#7b9499";
static char selfgcolor[]            = "#64374b";
static char selbordercolor[]        = "#ff2914";
static char selbgcolor[]            = "#03070a";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
    const char *name;
    const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "NerdFontMono-Regular:size=14", "-g", "50x20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
    /* name          cmd  */
    {"spterm",      spcmd1},
    {"spcalc",      spcmd2},
};

/* tagging */
static const char *tags[] = { "󰩖", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
    */
    /* class    instance      title          tags mask    isfloating   isterminal  noswallow  monitor */
    { "Gimp",     NULL,       NULL,          1 << 8,      0,           0,          0,         -1 },
    { TERMCLASS,  NULL,       NULL,          0,           0,           1,          0,         -1 },
    { NULL,       NULL,       "Event Tester", 0,          0,           0,          1,         -1 },
    { TERMCLASS,  "floatterm", NULL,         0,           1,           1,          0,         -1 },
    { TERMCLASS,  "bg",        NULL,         1 << 7,      0,           1,          0,         -1 },
    { TERMCLASS,  "spterm",    NULL,         SPTAG(0),    1,           1,          0,         -1 },
    { TERMCLASS,  "spcalc",    NULL,         SPTAG(1),    1,           1,          0,         -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",    tile },                 /* Default: Master on left, slaves on right */
    { "TTT",    bstack },               /* Master on top, slaves on bottom */

    { "[@]",    spiral },               /* Fibonacci spiral */
    { "[\\]",   dwindle },              /* Decreasing in size right and leftward */

    { "[D]",    deck },                 /* Master on left, slaves in monocle-like mode on right */
    { "[M]",    monocle },              /* All windows on top of eachother */

    { "|M|",    centeredmaster },               /* Master in middle, slaves on sides */
    { ">M>",    centeredfloatingmaster },       /* Same but master floats */

    { "><>",    NULL },                 /* no layout function means floating behavior */
    { NULL,     NULL },
};

/* key definitions */
/* Win / Super */
#define MODKEY Mod4Mask
/* Alt */
#define ALTMOD Mod1Mask   
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
    { ALTMOD,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { ALTMOD|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { ALTMOD|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { ALTMOD|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

    #define STACKKEYS(MOD,ACTION) \
    { MOD,  XK_j,   ACTION##stack,  {.i = INC(+1) } }, \
    { MOD,  XK_k,   ACTION##stack,  {.i = INC(-1) } }, \
    { MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
        { "color0",     STRING, &normbordercolor },
        { "color8",     STRING, &selbordercolor },
        { "color0",     STRING, &normbgcolor },
        { "color4",     STRING, &normfgcolor },
        { "color0",     STRING, &selfgcolor },
        { "color4",     STRING, &selbgcolor },
        { "borderpx",   INTEGER, &borderpx },
        { "snap",       INTEGER, &snap },
        { "showbar",    INTEGER, &showbar },
        { "topbar",     INTEGER, &topbar },
        { "nmaster",    INTEGER, &nmaster },
        { "resizehints",INTEGER, &resizehints },
        { "mfact",      FLOAT,  &mfact },
        { "gappih",     INTEGER, &gappih },
        { "gappiv",     INTEGER, &gappiv },
        { "gappoh",     INTEGER, &gappoh },
        { "gappov",     INTEGER, &gappov },
        { "swallowfloating",    INTEGER, &swallowfloating },
        { "smartgaps",      INTEGER, &smartgaps },
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

static const Key keys[] = {
    /* modifier                     key            function                argument */
    STACKKEYS(MODKEY,                              focus)
    STACKKEYS(ALTMOD,                              focus)
    STACKKEYS(MODKEY|ShiftMask,                    push)
    STACKKEYS(ALTMOD|ShiftMask,                    push)
    { MODKEY,           XK_grave,      spawn,                  {.v = (const char*[]){ "dmenuunicode", NULL } } },
    { ALTMOD,           XK_grave,      spawn,                  {.v = (const char*[]){ "dmenuunicode", NULL } } },

    TAGKEYS(            XK_1,          0)
    TAGKEYS(            XK_2,          1)
    TAGKEYS(            XK_3,          2)
    TAGKEYS(            XK_4,          3)
    TAGKEYS(            XK_5,          4)
    TAGKEYS(            XK_6,          5)
    TAGKEYS(            XK_7,          6)
    TAGKEYS(            XK_8,          7)
    TAGKEYS(            XK_9,          8)
    { MODKEY,           XK_0,          view,                   {.ui = ~0 } },
    { ALTMOD,           XK_0,          view,                   {.ui = ~0 } },
    { MODKEY|ShiftMask, XK_0,          tag,                    {.ui = ~0 } },
    { ALTMOD|ShiftMask, XK_0,          tag,                    {.ui = ~0 } },
    { MODKEY,           XK_minus,      spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)") },
    { ALTMOD,           XK_minus,      spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)") },
    { MODKEY|ShiftMask, XK_minus,      spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%-; kill -44 $(pidof dwmblocks)") },
    { ALTMOD|ShiftMask, XK_minus,      spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%-; kill -44 $(pidof dwmblocks)") },
    { MODKEY,           XK_equal,      spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof dwmblocks)") },
    { ALTMOD,           XK_equal,      spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof dwmblocks)") },
    { MODKEY|ShiftMask, XK_equal,      spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%+; kill -44 $(pidof dwmblocks)") },
    { ALTMOD|ShiftMask, XK_equal,      spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%+; kill -44 $(pidof dwmblocks)") },
    { MODKEY,           XK_BackSpace,  spawn,                  {.v = (const char*[]){ "sysact", NULL } } },
    { ALTMOD,           XK_BackSpace,  spawn,                  {.v = (const char*[]){ "sysact", NULL } } },
    { MODKEY|ShiftMask, XK_BackSpace,  spawn,                  {.v = (const char*[]){ "sysact", NULL } } },
    { ALTMOD|ShiftMask, XK_BackSpace,  spawn,                  {.v = (const char*[]){ "sysact", NULL } } },




    // USER DEFINITIONS
    #define VM "virtualbox"
    #define SLOCK "slock"
    #define NOTES "obsidian"
    // USER MODKEY

/*   Example of browser spawn function. XK is the key, spawn is the action,
    {.v =(const char[]){ BROWSER, NULL } } } is the name of the application we are trying to spawn, we use #define to shortern the application name / generalize it.
        ------------------------------------------------------------------------------------------------------------------
    { MODKEY,           XK_w,          spawn,                  {.v = (const char*[]){ BROWSER, NULL } } },
*/

    { MODKEY,           XK_v,       spawn,          {.v = (const char*[]){ VM, NULL } } },
    { MODKEY,           XK_s,       spawn,          {.v = (const char*[]){ SLOCK, NULL } } },
    { MODKEY,           XK_c,       spawn,          {.v = (const char*[]){ NOTES, NULL } } },
    { ALTMOD,           XK_v,       spawn,          {.v = (const char*[]){ VM, NULL } } },
    { ALTMOD,           XK_s,       spawn,          {.v = (const char*[]){ SLOCK, NULL } } },
    { ALTMOD,           XK_c,       spawn,          {.v = (const char*[]){ NOTES, NULL } } },

    { MODKEY,           XK_Tab,        view,                   {0} },
    { MODKEY,           XK_q,          killclient,             {0} },
    { MODKEY|ShiftMask, XK_q,          spawn,                  {.v = (const char*[]){ "sysact", NULL } } },
    { MODKEY,           XK_w,          spawn,                  {.v = (const char*[]){ BROWSER, NULL } } },
    { MODKEY|ShiftMask, XK_w,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "sudo", "nmtui", NULL } } },
    { MODKEY,           XK_e,          spawn,                  SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks; rmdir ~/.abook 2>/dev/null") },
    { MODKEY|ShiftMask, XK_e,          spawn,                  SHCMD(TERMINAL " -e abook -C ~/.config/abook/abookrc --datafile ~/.config/abook/addressbook") },
    { MODKEY,           XK_r,          spawn,                  {.v = (const char*[]){ "thunar", NULL } } },
    { MODKEY|ShiftMask, XK_r,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
    { MODKEY,           XK_t,          setlayout,              {.v = &layouts[0]} }, /* tile */
    { MODKEY|ShiftMask, XK_t,          setlayout,              {.v = &layouts[1]} }, /* bstack */
    { MODKEY,           XK_y,          setlayout,              {.v = &layouts[2]} }, /* spiral */
    { MODKEY|ShiftMask, XK_y,          setlayout,              {.v = &layouts[3]} }, /* dwindle */
    { MODKEY,           XK_u,          setlayout,              {.v = &layouts[4]} }, /* deck */
    { MODKEY|ShiftMask, XK_u,          setlayout,              {.v = &layouts[5]} }, /* monocle */
    { MODKEY,           XK_i,          setlayout,              {.v = &layouts[6]} }, /* centeredmaster */
    { MODKEY|ShiftMask, XK_i,          setlayout,              {.v = &layouts[7]} }, /* centeredfloatingmaster */
    { MODKEY,           XK_o,          incnmaster,             {.i = +1 } },
    { MODKEY|ShiftMask, XK_o,          incnmaster,             {.i = -1 } },
    { MODKEY,           XK_p,          spawn,                  {.v = (const char*[]){ "mpc", "toggle", NULL } } },
    { MODKEY|ShiftMask, XK_p,          spawn,                  SHCMD("mpc pause; pauseallmpv") },
    { MODKEY,           XK_bracketleft, spawn,                 {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
    { MODKEY|ShiftMask, XK_bracketleft, spawn,                 {.v = (const char*[]){ "mpc", "seek", "-60", NULL } } },
    { MODKEY,           XK_bracketright, spawn,                {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
    { MODKEY|ShiftMask, XK_bracketright, spawn,                {.v = (const char*[]){ "mpc", "seek", "+60", NULL } } },
    { MODKEY,           XK_backslash,  view,                   {0} },
    { MODKEY,           XK_a,          togglegaps,             {0} },
    { MODKEY|ShiftMask, XK_a,          defaultgaps,            {0} },
    { MODKEY,           XK_s,          togglesticky,           {0} },
    { MODKEY,           XK_d,          spawn,                  {.v = (const char*[]){ "dmenu_run", NULL } } },
    { MODKEY|ShiftMask, XK_d,          spawn,                  {.v = (const char*[]){ "passmenu", NULL } } },
    { MODKEY,           XK_f,          togglefullscr,          {0} },
    { MODKEY|ShiftMask, XK_f,          setlayout,              {.v = &layouts[8]} },
    { MODKEY,           XK_g,          shiftview,              { .i = -1 } },
    { MODKEY|ShiftMask, XK_g,          shifttag,               { .i = -1 } },
    { MODKEY,           XK_h,          setmfact,               {.f = -0.05} },
    /* J and K are automatically bound above in STACKEYS */
    { MODKEY,           XK_m,          setmfact,               {.f = +0.05} },
    { MODKEY,           XK_semicolon,  shiftview,              { .i = 1 } },
    { MODKEY|ShiftMask, XK_semicolon,  shifttag,               { .i = 1 } },
    { MODKEY,           XK_apostrophe, togglescratch,          {.ui = 1} },
    { MODKEY|ShiftMask, XK_apostrophe, togglesmartgaps,        {0} },
    { MODKEY,           XK_Return,     spawn,                  SHCMD("terminal-here.sh") },
    { MODKEY|ShiftMask, XK_Return,     togglescratch,          {.ui = 0} },

    { MODKEY,           XK_z,          incrgaps,               {.i = +3 } },
    { MODKEY,           XK_x,          incrgaps,               {.i = -3 } },
    { MODKEY,           XK_c,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "profanity", NULL } } },
    /* V is automatically bound above in STACKKEYS */
    { MODKEY,           XK_b,          togglebar,              {0} },
    { MODKEY,           XK_n,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "nvim", "-c", "VimwikiIndex", NULL } } },
    { MODKEY|ShiftMask, XK_n,          spawn,                  SHCMD(TERMINAL " -e newsboat ; pkill -RTMIN+6 dwmblocks") },
    { MODKEY|ShiftMask, XK_m,          spawn,                  SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
    { MODKEY,           XK_comma,      spawn,                  {.v = (const char*[]){ "mpc", "prev", NULL } } },
    { MODKEY|ShiftMask, XK_comma,      spawn,                  {.v = (const char*[]){ "mpc", "seek", "0%", NULL } } },
    { MODKEY,           XK_period,     spawn,                  {.v = (const char*[]){ "mpc", "next", NULL } } },
    { MODKEY|ShiftMask, XK_period,     spawn,                  {.v = (const char*[]){ "mpc", "repeat", NULL } } },
    { MODKEY,           XK_Left,       focusmon,               {.i = -1 } },
    { MODKEY|ShiftMask, XK_Left,       tagmon,                 {.i = -1 } },
    { MODKEY,           XK_Right,      focusmon,               {.i = +1 } },
    { MODKEY|ShiftMask, XK_Right,      tagmon,                 {.i = +1 } },
    { MODKEY,           XK_Page_Up,    shiftview,              { .i = -1 } },
    { MODKEY|ShiftMask, XK_Page_Up,    shifttag,               { .i = -1 } },
    { MODKEY,           XK_Page_Down,  shiftview,              { .i = +1 } },
    { MODKEY|ShiftMask, XK_Page_Down,  shifttag,               { .i = +1 } },
    { MODKEY,           XK_Insert,     spawn,                  SHCMD("xdotool type $(grep -v '^#' ~/.local/share/larbs/snippets | dmenu -i -l 50 | cut -d' ' -f1)") },
    { MODKEY,           XK_F1,         spawn,                  SHCMD("groff -mom /usr/local/share/dwm/larbs.mom -Tpdf | zathura -") },
    { MODKEY,           XK_F2,         spawn,                  {.v = (const char*[]){ "tutorialvids", NULL } } },
    { MODKEY,           XK_F3,         spawn,                  {.v = (const char*[]){ "displayselect", NULL } } },
    { MODKEY,           XK_F4,         spawn,                  SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)") },
    { MODKEY,           XK_F5,         xrdb,                   {.v = NULL } },
    { MODKEY,           XK_F6,         spawn,                  {.v = (const char*[]){ "torwrap", NULL } } },
    { MODKEY,           XK_F7,         spawn,                  {.v = (const char*[]){ "td-toggle", NULL } } },
    { MODKEY,           XK_F8,         spawn,                  {.v = (const char*[]){ "mailsync", NULL } } },
    { MODKEY,           XK_F9,         spawn,                  {.v = (const char*[]){ "mounter", NULL } } },
    { MODKEY,           XK_F10,        spawn,                  {.v = (const char*[]){ "unmounter", NULL } } },
    { MODKEY,           XK_F11,        spawn,                  SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
    { MODKEY,           XK_F12,        spawn,                  SHCMD("remaps") },
    { MODKEY,           XK_space,      zoom,                   {0} },
    { MODKEY|ShiftMask, XK_space,      togglefloating,         {0} },
    { 0,                XK_Print,      spawn,                  SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
    { ShiftMask,        XK_Print,      spawn,                  {.v = (const char*[]){ "maimpick", NULL } } },
    { MODKEY,           XK_Print,      spawn,              {.v = (const char*[]){ "dmenurecord", NULL } } },
    { MODKEY|ShiftMask, XK_Print,      spawn,                  {.v = (const char*[]){ "dmenurecord", "kill", NULL } } },
    { MODKEY,           XK_Delete,     spawn,                  {.v = (const char*[]){ "dmenurecord", "kill", NULL } } },
    { MODKEY,           XK_Scroll_Lock, spawn,                 SHCMD("killall screenkey || screenkey &") },


    { ALTMOD,           XK_Tab,        view,                   {0} },
    { ALTMOD,           XK_q,          killclient,             {0} },
    { ALTMOD|ShiftMask, XK_q,          spawn,                  {.v = (const char*[]){ "sysact", NULL } } },
    { ALTMOD,           XK_w,          spawn,                  {.v = (const char*[]){ BROWSER, NULL } } },
    { ALTMOD|ShiftMask, XK_w,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "sudo", "nmtui", NULL } } },
    { ALTMOD,           XK_e,          spawn,                  SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks; rmdir ~/.abook 2>/dev/null") },
    { ALTMOD|ShiftMask, XK_e,          spawn,                  SHCMD(TERMINAL " -e abook -C ~/.config/abook/abookrc --datafile ~/.config/abook/addressbook") },
    { ALTMOD,           XK_r,          spawn,                  {.v = (const char*[]){ "thunar", NULL } } },
    { ALTMOD|ShiftMask, XK_r,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
    { ALTMOD,           XK_t,          setlayout,              {.v = &layouts[0]} }, /* tile */
    { ALTMOD|ShiftMask, XK_t,          setlayout,              {.v = &layouts[1]} }, /* bstack */
    { ALTMOD,           XK_y,          setlayout,              {.v = &layouts[2]} }, /* spiral */
    { ALTMOD|ShiftMask, XK_y,          setlayout,              {.v = &layouts[3]} }, /* dwindle */
    { ALTMOD,           XK_u,          setlayout,              {.v = &layouts[4]} }, /* deck */
    { ALTMOD|ShiftMask, XK_u,          setlayout,              {.v = &layouts[5]} }, /* monocle */
    { ALTMOD,           XK_i,          setlayout,              {.v = &layouts[6]} }, /* centeredmaster */
    { ALTMOD|ShiftMask, XK_i,          setlayout,              {.v = &layouts[7]} }, /* centeredfloatingmaster */
    { ALTMOD,           XK_o,          incnmaster,             {.i = +1 } },
    { ALTMOD|ShiftMask, XK_o,          incnmaster,             {.i = -1 } },
    { ALTMOD,           XK_p,          spawn,                  {.v = (const char*[]){ "mpc", "toggle", NULL } } },
    { ALTMOD|ShiftMask, XK_p,          spawn,                  SHCMD("mpc pause; pauseallmpv") },
    { ALTMOD,           XK_bracketleft, spawn,                 {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
    { ALTMOD|ShiftMask, XK_bracketleft, spawn,                 {.v = (const char*[]){ "mpc", "seek", "-60", NULL } } },
    { ALTMOD,           XK_bracketright, spawn,                {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
    { ALTMOD|ShiftMask, XK_bracketright, spawn,                {.v = (const char*[]){ "mpc", "seek", "+60", NULL } } },
    { ALTMOD,           XK_backslash,  view,                   {0} },
    { ALTMOD,           XK_a,          togglegaps,             {0} },
    { ALTMOD|ShiftMask, XK_a,          defaultgaps,            {0} },
    { ALTMOD,           XK_s,          togglesticky,           {0} },
    { ALTMOD,           XK_d,          spawn,                  {.v = (const char*[]){ "dmenu_run", NULL } } },
    { ALTMOD|ShiftMask, XK_d,          spawn,                  {.v = (const char*[]){ "passmenu", NULL } } },
    { ALTMOD,           XK_f,          togglefullscr,          {0} },
    { ALTMOD|ShiftMask, XK_f,          setlayout,              {.v = &layouts[8]} },
    { ALTMOD,           XK_g,          shiftview,              { .i = -1 } },
    { ALTMOD|ShiftMask, XK_g,          shifttag,               { .i = -1 } },
    { ALTMOD,           XK_h,          setmfact,               {.f = -0.05} },
    /* J and K are automatically bound above in STACKEYS */
    { ALTMOD,           XK_m,          setmfact,               {.f = +0.05} },
    { ALTMOD,           XK_semicolon,  shiftview,              { .i = 1 } },
    { ALTMOD|ShiftMask, XK_semicolon,  shifttag,               { .i = 1 } },
    { ALTMOD,           XK_apostrophe, togglescratch,          {.ui = 1} },
    { ALTMOD|ShiftMask, XK_apostrophe, togglesmartgaps,        {0} },
    { ALTMOD,           XK_Return,     spawn,                  SHCMD("terminal-here.sh") },
    { ALTMOD|ShiftMask, XK_Return,     togglescratch,          {.ui = 0} },

    { ALTMOD,           XK_z,          incrgaps,               {.i = +3 } },
    { ALTMOD,           XK_x,          incrgaps,               {.i = -3 } },
    { ALTMOD,           XK_c,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "profanity", NULL } } },
    /* V is automatically bound above in STACKKEYS */
    { ALTMOD,           XK_b,          togglebar,              {0} },
    { ALTMOD,           XK_n,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "nvim", "-c", "VimwikiIndex", NULL } } },
    { ALTMOD|ShiftMask, XK_n,          spawn,                  SHCMD(TERMINAL " -e newsboat ; pkill -RTMIN+6 dwmblocks") },
    { ALTMOD|ShiftMask, XK_m,          spawn,                  SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
    { ALTMOD,           XK_comma,      spawn,                  {.v = (const char*[]){ "mpc", "prev", NULL } } },
    { ALTMOD|ShiftMask, XK_comma,      spawn,                  {.v = (const char*[]){ "mpc", "seek", "0%", NULL } } },
    { ALTMOD,           XK_period,     spawn,                  {.v = (const char*[]){ "mpc", "next", NULL } } },
    { ALTMOD|ShiftMask, XK_period,     spawn,                  {.v = (const char*[]){ "mpc", "repeat", NULL } } },
    { ALTMOD,           XK_Left,       focusmon,               {.i = -1 } },
    { ALTMOD|ShiftMask, XK_Left,       tagmon,                 {.i = -1 } },
    { ALTMOD,           XK_Right,      focusmon,               {.i = +1 } },
    { ALTMOD|ShiftMask, XK_Right,      tagmon,                 {.i = +1 } },
    { ALTMOD,           XK_Page_Up,    shiftview,              { .i = -1 } },
    { ALTMOD|ShiftMask, XK_Page_Up,    shifttag,               { .i = -1 } },
    { ALTMOD,           XK_Page_Down,  shiftview,              { .i = +1 } },
    { ALTMOD|ShiftMask, XK_Page_Down,  shifttag,               { .i = +1 } },
    { ALTMOD,           XK_Insert,     spawn,                  SHCMD("xdotool type $(grep -v '^#' ~/.local/share/larbs/snippets | dmenu -i -l 50 | cut -d' ' -f1)") },
    { ALTMOD,           XK_F1,         spawn,                  SHCMD("groff -mom /usr/local/share/dwm/larbs.mom -Tpdf | zathura -") },
    { ALTMOD,           XK_F2,         spawn,                  {.v = (const char*[]){ "tutorialvids", NULL } } },
    { ALTMOD,           XK_F3,         spawn,                  {.v = (const char*[]){ "displayselect", NULL } } },
    { ALTMOD,           XK_F4,         spawn,                  SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)") },
    { ALTMOD,           XK_F5,         xrdb,                   {.v = NULL } },
    { ALTMOD,           XK_F6,         spawn,                  {.v = (const char*[]){ "torwrap", NULL } } },
    { ALTMOD,           XK_F7,         spawn,                  {.v = (const char*[]){ "td-toggle", NULL } } },
    { ALTMOD,           XK_F8,         spawn,                  {.v = (const char*[]){ "mailsync", NULL } } },
    { ALTMOD,           XK_F9,         spawn,                  {.v = (const char*[]){ "mounter", NULL } } },
    { ALTMOD,           XK_F10,        spawn,                  {.v = (const char*[]){ "unmounter", NULL } } },
    { ALTMOD,           XK_F11,        spawn,                  SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
    { ALTMOD,           XK_F12,        spawn,                  SHCMD("remaps") },
    { ALTMOD,           XK_space,      zoom,                   {0} },
    { ALTMOD|ShiftMask, XK_space,      togglefloating,         {0} },
    { ALTMOD,           XK_Print,      spawn,              {.v = (const char*[]){ "dmenurecord", NULL } } },
    { ALTMOD|ShiftMask, XK_Print,      spawn,                  {.v = (const char*[]){ "dmenurecord", "kill", NULL } } },
    { ALTMOD,           XK_Delete,     spawn,                  {.v = (const char*[]){ "dmenurecord", "kill", NULL } } },
    { ALTMOD,           XK_Scroll_Lock, spawn,                 SHCMD("killall screenkey || screenkey &") },


    { 0, XF86XK_AudioMute,                         spawn,                  SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
    { 0, XF86XK_AudioRaiseVolume,                  spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%- && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%+; kill -44 $(pidof dwmblocks)") },
    { 0, XF86XK_AudioLowerVolume,                  spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%+ && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%-; kill -44 $(pidof dwmblocks)") },
    { 0, XF86XK_AudioPrev,                         spawn,                  {.v = (const char*[]){ "mpc", "prev", NULL } } },
    { 0, XF86XK_AudioNext,                         spawn,                  {.v = (const char*[]){ "mpc",  "next", NULL } } },
    { 0, XF86XK_AudioPause,                        spawn,                  {.v = (const char*[]){ "mpc", "pause", NULL } } },
    { 0, XF86XK_AudioPlay,                         spawn,                  {.v = (const char*[]){ "mpc", "play", NULL } } },
    { 0, XF86XK_AudioStop,                         spawn,                  {.v = (const char*[]){ "mpc", "stop", NULL } } },
    { 0, XF86XK_AudioRewind,                       spawn,                  {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
    { 0, XF86XK_AudioForward,                      spawn,                  {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
    { 0, XF86XK_AudioMedia,                        spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
    { 0, XF86XK_AudioMicMute,                      spawn,                  SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
    { 0, XF86XK_Calculator,                        spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "bc", "-l", NULL } } },
    { 0, XF86XK_Sleep,                             spawn,                  {.v = (const char*[]){ "sudo", "-A", "zzz", NULL } } },
    { 0, XF86XK_WWW,                               spawn,                  {.v = (const char*[]){ BROWSER, NULL } } },
    { 0, XF86XK_DOS,                               spawn,                  {.v = termcmd } },
    { 0, XF86XK_ScreenSaver,                       spawn,                  SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
    { 0, XF86XK_TaskPane,                          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
    { 0, XF86XK_Mail,                              spawn,                  SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
    { 0, XF86XK_MyComputer,                        spawn,                  {.v = (const char*[]){ TERMINAL, "-e",  "lfub",  "/", NULL } } },
    { 0, XF86XK_Launch1,                           spawn,                  {.v = (const char*[]){ "xset", "dpms", "force", "off", NULL } } },
    { 0, XF86XK_TouchpadToggle,                    spawn,                  SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
    { 0, XF86XK_TouchpadOff,                       spawn,                  {.v = (const char*[]){ "synclient", "TouchpadOff=1", NULL } } },
    { 0, XF86XK_TouchpadOn,                        spawn,                  {.v = (const char*[]){ "synclient", "TouchpadOff=0", NULL } } },
    { 0, XF86XK_MonBrightnessUp,                   spawn,                  {.v = (const char*[]){ "xbacklight", "-inc", "15", NULL } } },
    { 0, XF86XK_MonBrightnessDown,                 spawn,                  {.v = (const char*[]){ "xbacklight", "-dec", "15", NULL } } },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask           button          function        argument */
#ifndef __OpenBSD__
    { ClkWinTitle,          0,                   Button2,        zoom,           {0} },
    { ClkStatusText,        0,                   Button1,        sigdwmblocks,   {.i = 1} },
    { ClkStatusText,        0,                   Button2,        sigdwmblocks,   {.i = 2} },
    { ClkStatusText,        0,                   Button3,        sigdwmblocks,   {.i = 3} },
    { ClkStatusText,        0,                   Button4,        sigdwmblocks,   {.i = 4} },
    { ClkStatusText,        0,                   Button5,        sigdwmblocks,   {.i = 5} },
    { ClkStatusText,        ShiftMask,           Button1,        sigdwmblocks,   {.i = 6} },
#endif
    { ClkStatusText,        ShiftMask,           Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },
    { ClkClientWin,         MODKEY,              Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,              Button2,        defaultgaps,    {0} },
    { ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
    { ClkClientWin,         MODKEY,              Button4,        incrgaps,       {.i = +1} },
    { ClkClientWin,         MODKEY,              Button5,        incrgaps,       {.i = -1} },
    { ClkClientWin,         ALTMOD,              Button1,        movemouse,      {0} },
    { ClkClientWin,         ALTMOD,              Button2,        defaultgaps,    {0} },
    { ClkClientWin,         ALTMOD,              Button3,        resizemouse,    {0} },
    { ClkClientWin,         ALTMOD,              Button4,        incrgaps,       {.i = +1} },
    { ClkClientWin,         ALTMOD,              Button5,        incrgaps,       {.i = -1} },
    { ClkTagBar,            0,                   Button1,        view,           {0} },
    { ClkTagBar,            0,                   Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
    { ClkTagBar,            ALTMOD,              Button1,        tag,            {0} },
    { ClkTagBar,            ALTMOD,              Button3,        toggletag,      {0} },
    { ClkTagBar,        0,           Button4,        shiftview,      {.i = -1} },
    { ClkTagBar,        0,           Button5,        shiftview,      {.i = 1} },
    { ClkRootWin,       0,           Button2,        togglebar,      {0} },
};
