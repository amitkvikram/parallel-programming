#ifndef TYPE_DEFINITION_H
#define TYPE_DEFINITION_H

#include <termios.h>
#include <time.h>

typedef struct{
    int idx;
    int size;
    int rsize;
    char *chars;
    char *render;
    unsigned char *hl;
    int hl_open_comment;
} erow;

typedef struct {
    const char *filetype;
    const char **filematch;
    const char **keywords;
    const char *singleline_comment_start;
    const char *multiline_comment_start;
    const char *multiline_comment_end;
    int flags;
}editorSyntax;

typedef struct
{
    int cx, cy;
    int rx;
    int rowoff;
    int coloff;
    int screenrows;
    int screencols;
    int numrows;
    char *filename;
    char statusmsg[80];
    time_t statusmsg_time;
    erow *row;
    int dirty;
    editorSyntax *syntax;
    struct termios orig_termios;
} editorConfig;

typedef struct {
    char *b;
    int len;
}abuf;

enum editorKey {
    BACKSPACE = 127,
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    DEL_KEY,
    HOME_KEY,
    END_KEY,
    PAGE_UP,
    PAGE_DOWN
};

enum editorHighlight {
    HL_NORMAL = 0,
    HL_COMMENT,
    HL_MLCOMMENT,
    HL_KEYWORD1,
    HL_KEYWORD2,
    HL_STRING,
    HL_NUMBER,
    HL_MATCH
};

#endif