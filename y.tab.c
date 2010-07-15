
# line 198 "awk.y"
#ifdef DEBUG
#define YYDEBUG 12
#endif
#define YYIMPROVE

#include "awk.h"

extern void msg();
extern struct re_pattern_buffer *mk_re_parse();

NODE *node();
NODE *lookup();
NODE *install();

static NODE *snode();
static NODE *mkrangenode();
static FILE *pathopen();
static NODE *make_for_loop();
static NODE *append_right();
static void func_install();
static NODE *make_param();
static int hashf();
static void pop_params();
static void pop_var();
static int yylex ();
static void yyerror();

static int want_regexp;         /* lexical scanning kludge */
static int lineno = 1;          /* for error msgs */
static char *lexptr;            /* pointer to next char during parsing */
static char *lexptr_begin;      /* keep track of where we were for error msgs */
static int curinfile = -1;      /* index into sourcefiles[] */

NODE *variables[HASHSIZE];

extern int errcount;
extern NODE *begin_block;
extern NODE *end_block;
extern int param_counter;

# line 239 "awk.y"
typedef union  {
        long lval;
        AWKNUM fval;
        NODE *nodeval;
        NODETYPE nodetypeval;
        char *sval;
        NODE *(*ptrval)();
} YYSTYPE;
# define FUNC_CALL 257
# define NAME 258
# define REGEXP 259
# define YSTRING 260
# define ERROR 261
# define INCDEC 262
# define NUMBER 263
# define RELOP 264
# define APPEND_OP 265
# define ASSIGNOP 266
# define MATCHOP 267
# define NEWLINE 268
# define CONCAT_OP 269
# define LEX_BEGIN 270
# define LEX_END 271
# define LEX_IF 272
# define LEX_ELSE 273
# define LEX_RETURN 274
# define LEX_DELETE 275
# define LEX_WHILE 276
# define LEX_DO 277
# define LEX_FOR 278
# define LEX_BREAK 279
# define LEX_CONTINUE 280
# define LEX_PRINT 281
# define LEX_PRINTF 282
# define LEX_NEXT 283
# define LEX_EXIT 284
# define LEX_FUNCTION 285
# define LEX_GETLINE 286
# define LEX_SUB 287
# define LEX_MATCH 288
# define LEX_IN 289
# define LEX_AND 290
# define LEX_OR 291
# define INCREMENT 292
# define DECREMENT 293
# define LEX_BUILTIN 294
# define UNARY 295
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern short yyerrflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
YYSTYPE yylval, yyval;
# define YYERRCODE 256

# line 833 "awk.y"


struct token {
        char *operator;         /* text to match */
        NODETYPE value;         /* node type */
        int class;              /* lexical class */
        short nostrict;         /* ignore if in strict compatibility mode */
        NODE *(*ptr) ();        /* function that implements this keyword */
};

#ifndef NULL
#define NULL 0
#endif

extern NODE
        *do_exp(),      *do_getline(),  *do_index(),    *do_length(),
        *do_sqrt(),     *do_log(),      *do_sprintf(),  *do_substr(),
        *do_split(),    *do_system(),   *do_int(),      *do_close(),
        *do_atan2(),    *do_sin(),      *do_cos(),      *do_rand(),
        *do_srand(),    *do_match(),    *do_tolower(),  *do_toupper();

/* Special functions for debugging */
#ifdef DEBUG
NODE *do_prvars(), *do_bp();
#endif

/* Tokentab is sorted ascii ascending order, so it can be binary searched. */

static struct token tokentab[] = {
        { "BEGIN",      Node_illegal,           LEX_BEGIN,      0,      0 },
        { "END",        Node_illegal,           LEX_END,        0,      0 },
        { "atan2",      Node_builtin,           LEX_BUILTIN,    0,      do_atan2 },
#ifdef DEBUG
        { "bp",         Node_builtin,           LEX_BUILTIN,    0,      do_bp },
#endif
        { "break",      Node_K_break,           LEX_BREAK,      0,      0 },
        { "close",      Node_builtin,           LEX_BUILTIN,    0,      do_close },
        { "continue",   Node_K_continue,        LEX_CONTINUE,   0,      0 },
        { "cos",        Node_builtin,           LEX_BUILTIN,    0,      do_cos },
        { "delete",     Node_K_delete,          LEX_DELETE,     0,      0 },
        { "do",         Node_K_do,              LEX_DO,         0,      0 },
        { "else",       Node_illegal,           LEX_ELSE,       0,      0 },
        { "exit",       Node_K_exit,            LEX_EXIT,       0,      0 },
        { "exp",        Node_builtin,           LEX_BUILTIN,    0,      do_exp },
        { "for",        Node_K_for,             LEX_FOR,        0,      0 },
        { "func",       Node_K_function,        LEX_FUNCTION,   0,      0 },
        { "function",   Node_K_function,        LEX_FUNCTION,   0,      0 },
        { "getline",    Node_K_getline,         LEX_GETLINE,    0,      0 },
        { "gsub",       Node_gsub,              LEX_SUB,        0,      0 },
        { "if",         Node_K_if,              LEX_IF,         0,      0 },
        { "in",         Node_illegal,           LEX_IN,         0,      0 },
        { "index",      Node_builtin,           LEX_BUILTIN,    0,      do_index },
        { "int",        Node_builtin,           LEX_BUILTIN,    0,      do_int },
        { "length",     Node_builtin,           LEX_BUILTIN,    0,      do_length },
        { "log",        Node_builtin,           LEX_BUILTIN,    0,      do_log },
        { "match",      Node_K_match,           LEX_MATCH,      0,      0 },
        { "next",       Node_K_next,            LEX_NEXT,       0,      0 },
        { "print",      Node_K_print,           LEX_PRINT,      0,      0 },
        { "printf",     Node_K_printf,          LEX_PRINTF,     0,      0 },
#ifdef DEBUG
        { "prvars",     Node_builtin,           LEX_BUILTIN,    0,      do_prvars },
#endif
        { "rand",       Node_builtin,           LEX_BUILTIN,    0,      do_rand },
        { "return",     Node_K_return,          LEX_RETURN,     0,      0 },
        { "sin",        Node_builtin,           LEX_BUILTIN,    0,      do_sin },
        { "split",      Node_builtin,           LEX_BUILTIN,    0,      do_split },
        { "sprintf",    Node_builtin,           LEX_BUILTIN,    0,      do_sprintf },
        { "sqrt",       Node_builtin,           LEX_BUILTIN,    0,      do_sqrt },
        { "srand",      Node_builtin,           LEX_BUILTIN,    0,      do_srand },
        { "sub",        Node_sub,               LEX_SUB,        0,      0 },
        { "substr",     Node_builtin,           LEX_BUILTIN,    0,      do_substr },
        { "system",     Node_builtin,           LEX_BUILTIN,    0,      do_system },
        { "tolower",    Node_builtin,           LEX_BUILTIN,    1,      do_tolower },
        { "toupper",    Node_builtin,           LEX_BUILTIN,    1,      do_toupper },
        { "while",      Node_K_while,           LEX_WHILE,      0,      0 },
};

/* VARARGS0 */
static void
yyerror(va_alist)
va_dcl
{
        va_list args;
        char *mesg;
        char *a1;
        register char *ptr, *beg;
        static int list = 0;
        char *scan;

        errcount++;
        va_start(args);
        mesg = va_arg(args, char *);
        if (! list)
                a1 = va_arg(args, char *);
        va_end(args);
        if (mesg || !list) {
                /* Find the current line in the input file */
                if (!lexptr) {
                        beg = "(END OF FILE)";
                        ptr = beg + 13;
                } else {
                        if (*lexptr == '\n' && lexptr != lexptr_begin)
                                --lexptr;
                        for (beg = lexptr; beg != lexptr_begin && *beg != '\n'; --beg)
                                ;
                        /* NL isn't guaranteed */
                        for (ptr = lexptr; *ptr && *ptr != '\n'; ptr++)
                                ;
                        if (beg != lexptr_begin)
                                beg++;
                }
                msg("syntax error near line %d:\n%.*s", lineno, ptr - beg, beg);
                scan = beg;
                while (scan <= lexptr)
                        if (*scan++ == '\t')
                                putc('\t', stderr);
                        else
                                putc(' ', stderr);
                putc('^', stderr);
                putc(' ', stderr);
                if (mesg) {
                        vfprintf(stderr, mesg, args);
                        putc('\n', stderr);
                        exit(1);
                } else {
                        if (a1) {
                                fputs("expecting: ", stderr);
                                fputs(a1, stderr);
                                list = 1;
                                return;
                        }
                }
                return;
        }
        if (a1) {
                fputs(" or ", stderr);
                fputs(a1, stderr);
                putc('\n', stderr);
                return;
        }
        putc('\n', stderr);
        list = 0;
}

/*
 * Parse a C escape sequence.  STRING_PTR points to a variable containing a
 * pointer to the string to parse.  That pointer is updated past the
 * characters we use.  The value of the escape sequence is returned. 
 *
 * A negative value means the sequence \ newline was seen, which is supposed to
 * be equivalent to nothing at all. 
 *
 * If \ is followed by a null character, we return a negative value and leave
 * the string pointer pointing at the null character. 
 *
 * If \ is followed by 000, we return 0 and leave the string pointer after the
 * zeros.  A value of 0 does not mean end of string.  
 */

static int
parse_escape(string_ptr)
char **string_ptr;
{
        register int c = *(*string_ptr)++;
        register int i;

        switch (c) {
        case 'a':
                if (strict)
                        goto def;
                else
                        return BELL;
        case 'b':
                return '\b';
        case 'f':
                return '\f';
        case 'n':
                return '\n';
        case 'r':
                return '\r';
        case 't':
                return '\t';
        case 'v':
                if (strict)
                        goto def;
                else
                        return '\v';
        case '\n':
                return -2;
        case 0:
                (*string_ptr)--;
                return 0;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
                {
                        register int i = c - '0';
                        register int count = 0;

                        while (++count < 3) {
                                if ((c = *(*string_ptr)++) >= '0' && c <= '7') {
                                        i *= 8;
                                        i += c - '0';
                                } else {
                                        (*string_ptr)--;
                                        break;
                                }
                        }
                        return i;
                }
        case 'x':
                if (strict)
                        goto def;

                i = 0;
                while (1) {
                        if (isxdigit((c = *(*string_ptr)++))) {
                                if (isdigit(c))
                                        i += c - '0';
                                else if (isupper(c))
                                        i += c - 'A' + 10;
                                else
                                        i += c - 'a' + 10;
                        } else {
                                (*string_ptr)--;
                                break;
                        }
                }
                return i;
        default:
        def:
                return c;
        }
}

/*
 * Read the input and turn it into tokens. Input is now read from a file
 * instead of from malloc'ed memory. The main program takes a program
 * passed as a command line argument and writes it to a temp file. Otherwise
 * the file name is made available in an external variable.
 */
#line 1080 "awk.y"
static int
yylex()
{
        register int c;
        register int namelen;
        register char *tokstart;
        char *tokkey;
        static did_newline = 0; /* the grammar insists that actions end
                                 * with newlines.  This was easier than
                                 * hacking the grammar. */
        int seen_e = 0;         /* These are for numbers */
        int seen_point = 0;
        extern char **sourcefile;
        extern int tempsource, numfiles;
        static int file_opened = 0;
        static FILE *fin;
        static char cbuf[BUFSIZ];
        int low, mid, high;
#ifdef DEBUG
        extern int debugging;
#endif

        if (! file_opened) {
                file_opened = 1;
#ifdef DEBUG
                if (debugging) {
                        int i;

                        for (i = 0; i <= numfiles; i++)
                                fprintf (stderr, "sourcefile[%d] = %s\n", i,
                                                sourcefile[i]);
                }
#endif
        nextfile:
                if ((fin = pathopen (sourcefile[++curinfile])) == NULL)
                        fatal("cannot open `%s' for reading (%s)",
                                sourcefile[curinfile],
                                sys_errlist[errno]);
                *(lexptr = cbuf) = '\0';
                /*
                 * immediately unlink the tempfile so that it will
                 * go away cleanly if we bomb.
                 */
                if (tempsource && curinfile == 0)
                        (void) unlink (sourcefile[curinfile]);
        }

retry:
        if (! *lexptr)
                if (fgets (cbuf, sizeof cbuf, fin) == NULL) {
                        if (fin != NULL)
                                fclose (fin);   /* be neat and clean */
                        if (curinfile < numfiles)
                                goto nextfile;
                        return 0;
                } else
                        lexptr = lexptr_begin = cbuf;

        if (want_regexp) {
                want_regexp = 0;

                /*
                 * there is a potential bug if a regexp is followed by an
                 * equal sign: "/foo/=bar" would result in assign_quotient
                 * being returned as the next token.  Nothing is done about
                 * it since it is not valid awk, but maybe something should
                 * be done anyway. 
                 */

                tokstart = lexptr;
                while (c = *lexptr++) {
                        switch (c) {
                        case '\\':
                                if (*lexptr++ == '\0') {
                                        yyerror("unterminated regexp ends with \\");
                                        return ERROR;
                                } else if (lexptr[-1] == '\n')
                                        goto retry;
                                break;
                        case '/':       /* end of the regexp */
                                lexptr--;
                                yylval.sval = tokstart;
                                return REGEXP;
                        case '\n':
                                lineno++;
                        case '\0':
                                lexptr--;       /* so error messages work */
                                yyerror("unterminated regexp");
                                return ERROR;
                        }
                }
        }

        if (*lexptr == '\n') {
                lexptr++;
                lineno++;
                return NEWLINE;
        }

        while (*lexptr == ' ' || *lexptr == '\t')
                lexptr++;

        tokstart = lexptr;

        switch (c = *lexptr++) {
        case 0:
                return 0;

        case '\n':
                lineno++;
                return NEWLINE;

        case '#':               /* it's a comment */
                while (*lexptr != '\n' && *lexptr != '\0')
                        lexptr++;
                goto retry;

        case '\\':
                if (*lexptr == '\n') {
                        lineno++;
                        lexptr++;
                        goto retry;
                } else
                        break;
        case ')':
        case ']':
        case '(':       
        case '[':
        case '$':
        case ';':
        case ':':
        case '?':

                /*
                 * set node type to ILLEGAL because the action should set it
                 * to the right thing 
                 */
                yylval.nodetypeval = Node_illegal;
                return c;

        case '{':
        case ',':
                yylval.nodetypeval = Node_illegal;
                return c;

        case '*':
                if (*lexptr == '=') {
                        yylval.nodetypeval = Node_assign_times;
                        lexptr++;
                        return ASSIGNOP;
                } else if (*lexptr == '*') {    /* make ** and **= aliases
                                                 * for ^ and ^= */
                        if (lexptr[1] == '=') {
                                yylval.nodetypeval = Node_assign_exp;
                                lexptr += 2;
                                return ASSIGNOP;
                        } else {
                                yylval.nodetypeval = Node_illegal;
                                lexptr++;
                                return '^';
                        }
                }
                yylval.nodetypeval = Node_illegal;
                return c;

        case '/':
                if (*lexptr == '=') {
                        yylval.nodetypeval = Node_assign_quotient;
                        lexptr++;
                        return ASSIGNOP;
                }
                yylval.nodetypeval = Node_illegal;
                return c;

        case '%':
                if (*lexptr == '=') {
                        yylval.nodetypeval = Node_assign_mod;
                        lexptr++;
                        return ASSIGNOP;
                }
                yylval.nodetypeval = Node_illegal;
                return c;

        case '^':
                if (*lexptr == '=') {
                        yylval.nodetypeval = Node_assign_exp;
                        lexptr++;
                        return ASSIGNOP;
                }
                yylval.nodetypeval = Node_illegal;
                return c;

        case '+':
                if (*lexptr == '=') {
                        yylval.nodetypeval = Node_assign_plus;
                        lexptr++;
                        return ASSIGNOP;
                }
                if (*lexptr == '+') {
                        yylval.nodetypeval = Node_illegal;
                        lexptr++;
                        return INCREMENT;
                }
                yylval.nodetypeval = Node_illegal;
                return c;

        case '!':
                if (*lexptr == '=') {
                        yylval.nodetypeval = Node_notequal;
                        lexptr++;
                        return RELOP;
                }
                if (*lexptr == '~') {
                        yylval.nodetypeval = Node_nomatch;
                        lexptr++;
                        return MATCHOP;
                }
                yylval.nodetypeval = Node_illegal;
                return c;

        case '<':
                if (*lexptr == '=') {
                        yylval.nodetypeval = Node_leq;
                        lexptr++;
                        return RELOP;
                }
                yylval.nodetypeval = Node_less;
                return c;

        case '=':
                if (*lexptr == '=') {
                        yylval.nodetypeval = Node_equal;
                        lexptr++;
                        return RELOP;
                }
                yylval.nodetypeval = Node_assign;
                return ASSIGNOP;

        case '>':
                if (*lexptr == '=') {
                        yylval.nodetypeval = Node_geq;
                        lexptr++;
                        return RELOP;
                } else if (*lexptr == '>') {
                        yylval.nodetypeval = Node_redirect_append;
                        lexptr++;
                        return APPEND_OP;
                }
                yylval.nodetypeval = Node_greater;
                return c;

        case '~':
                yylval.nodetypeval = Node_match;
                return MATCHOP;

        case '}':
                /*
                 * Added did newline stuff.  Easier than
                 * hacking the grammar
                 */
                if (did_newline) {
                        did_newline = 0;
                        return c;
                }
                did_newline++;
                --lexptr;
                return NEWLINE;

        case '"':
                while (*lexptr != '\0') {
                        switch (*lexptr++) {
                        case '\\':
                                if (*lexptr++ != '\0')
                                        break;
                                /* fall through */
                        case '\n':
                                yyerror("unterminated string");
                                return ERROR;
                        case '\"':
                                /* Skip the doublequote */
                                yylval.sval = tokstart + 1;
                                return YSTRING;
                        }
                }
                return ERROR;

        case '-':
                if (*lexptr == '=') {
                        yylval.nodetypeval = Node_assign_minus;
                        lexptr++;
                        return ASSIGNOP;
                }
                if (*lexptr == '-') {
                        yylval.nodetypeval = Node_illegal;
                        lexptr++;
                        return DECREMENT;
                }

                /*
                 * It looks like space tab comma and newline are the legal
                 * places for a UMINUS.  Have we missed any? 
                 */
                if ((! isdigit(*lexptr) && *lexptr != '.') ||
                        (lexptr > lexptr_begin + 1 &&
                                    ! index(" \t,\n", lexptr[-2]))) {

                        /*
                         * set node type to ILLEGAL because the action should
                         * set it to the right thing 
                         */
                        yylval.nodetypeval = Node_illegal;
                        return c;
                }
                /* FALL through into number code */
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
                /* It's a number */
                if (c == '-')
                        namelen = 1;
                else
                        namelen = 0;
                for (; (c = tokstart[namelen]) != '\0'; namelen++) {
                        switch (c) {
                        case '.':
                                if (seen_point)
                                        goto got_number;
                                ++seen_point;
                                break;
                        case 'e':
                        case 'E':
                                if (seen_e)
                                        goto got_number;
                                ++seen_e;
                                if (tokstart[namelen + 1] == '-' ||
                                    tokstart[namelen + 1] == '+')
                                        namelen++;
                                break;
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9':
                                break;
                        default:
                                goto got_number;
                        }
                }

got_number:
                lexptr = tokstart + namelen;
                yylval.fval = atof(tokstart);
                return NUMBER;

        case '&':
                if (*lexptr == '&') {
                        yylval.nodetypeval = Node_and;
                        while (c = *++lexptr) {
                                if (c == '#')
                                        while ((c = *++lexptr) != '\n'
                                               && c != '\0')
                                                ;
                                if (c == '\n')
                                        lineno++;
                                else if (!isspace(c))
                                        break;
                        }
                        return LEX_AND;
                }
                return ERROR;

        case '|':
                if (*lexptr == '|') {
                        yylval.nodetypeval = Node_or;
                        while (c = *++lexptr) {
                                if (c == '#')
                                        while ((c = *++lexptr) != '\n'
                                               && c != '\0')
                                                ;
                                if (c == '\n')
                                        lineno++;
                                else if (!isspace(c))
                                        break;
                        }
                        return LEX_OR;
                }
                        yylval.nodetypeval = Node_illegal;
                        return c;
                }

        if (c != '_' && !isalpha(c)) {
                yyerror("Invalid char '%c' in expression\n", c);
                return ERROR;
        }

        /* it's some type of name-type-thing.  Find its length */
        for (namelen = 0; is_identchar(tokstart[namelen]); namelen++)
                /* null */ ;
        emalloc(tokkey, char *, namelen+1, "yylex");
        (void) strncpy (tokkey, tokstart, namelen);
        tokkey[namelen] = '\0';

        /* See if it is a special token.  */
        low = 0;
        high = (sizeof (tokentab) / sizeof (tokentab[0])) - 1;
        while (low <= high) {
                int i, c;

                mid = (low + high) / 2;

        compare:
                c = *tokstart - tokentab[mid].operator[0];
                i = c ? c : strcmp (tokkey, tokentab[mid].operator);

                if (i < 0) {            /* token < mid */
                        high = mid - 1;
                } else if (i > 0) {     /* token > mid */
                        low = mid + 1;
                } else {
                        lexptr = tokstart + namelen;
                        if (strict && tokentab[mid].nostrict)
                                break;
                        if (tokentab[mid].class == LEX_BUILTIN)
                                yylval.ptrval = tokentab[mid].ptr;
                        else
                                yylval.nodetypeval = tokentab[mid].value;
                        return tokentab[mid].class;
                }
        }

        /* It's a name.  See how long it is.  */
        yylval.sval = tokkey;
        lexptr = tokstart + namelen;
        if (*lexptr == '(')
                return FUNC_CALL;
        else
                return NAME;
}

#ifndef DEFPATH
#ifdef MSDOS
#define DEFPATH "."
#define ENVSEP  ';'
#else
#define DEFPATH ".:/usr/lib/awk:/usr/local/lib/awk"
#define ENVSEP  ':'
#endif
#endif

static FILE *
pathopen (file)
char *file;
{
        static char *savepath = DEFPATH;
        static int first = 1;
        char *awkpath, *cp;
        char trypath[BUFSIZ];
        FILE *fp;
        extern int debugging;

        if (strcmp (file, "-") == 0)
                return (stdin);

        if (strict)
                return (fopen (file, "r"));

        if (first) {
                first = 0;
                if ((awkpath = getenv ("AWKPATH")) != NULL && *awkpath)
                        savepath = awkpath;     /* used for restarting */
#ifdef MSDOS
                else if ((awkpath = getenv ("INIT")) != NULL && *awkpath)
                        savepath = awkpath;     /* MSC 5.1 users may prefer */
                                                /* to use INIT              */
#endif
        }
        awkpath = savepath;

        /* some kind of path name, no search */
#ifndef MSDOS
        if (index (file, '/') != NULL)
#else
        if (index (file, '/') != NULL || index (file, '\\') != NULL
                        || index (file, ':') != NULL)
#endif
                return (fdopen(devopen (file, "r"), "r"));

        do {
                /* this should take into account limits on size of trypath */
                for (cp = trypath; *awkpath && *awkpath != ENVSEP; )
                        *cp++ = *awkpath++;
                *cp++ = '/';
                *cp = '\0';     /* clear left over junk */
                strcat (cp, file);
                if ((fp = fdopen(devopen (trypath, "r"), "r")) != NULL)
                        return (fp);

                /* no luck, keep going */
                if(*awkpath)
                        awkpath++;      /* skip colon */
        } while (*awkpath);
#ifdef MSDOS
/*
** under DOS (and probably elsewhere) you might have one of the awk paths
** defined, WITHOUT the current working directory in it.  Therefore you
** should try to open the file in the current directory
*/
        return fdopen(devopen(file,"r"),"r");
#else
        return (NULL);
#endif
}

static NODE *
node_common(op)
NODETYPE op;
{
        register NODE *r;
        extern int numfiles;
        extern int tempsource;
        extern char **sourcefile;

        r = newnode(op);
        r->source_line = lineno;
        if (numfiles > 1 && !tempsource)
                r->source_file = sourcefile[curinfile];
        else
                r->source_file = NULL;
        return r;
}

/*
 * This allocates a node with defined lnode and rnode. 
 * This should only be used by yyparse+co while reading in the program 
 */
NODE *
node(left, op, right)
NODE *left, *right;
NODETYPE op;
{
        register NODE *r;

        r = node_common(op);
        r->lnode = left;
        r->rnode = right;
        return r;
}

/*
 * This allocates a node with defined subnode and proc
 * Otherwise like node()
 */
static NODE *
snode(subn, op, procp)
NODETYPE op;
NODE *(*procp) ();
NODE *subn;
{
        register NODE *r;

        r = node_common(op);
        r->subnode = subn;
        r->proc = procp;
        return r;
}

/*
 * This allocates a Node_line_range node with defined condpair and
 * zeroes the trigger word to avoid the temptation of assuming that calling
 * 'node( foo, Node_line_range, 0)' will properly initialize 'triggered'. 
 */
/* Otherwise like node() */
static NODE *
mkrangenode(cpair)
NODE *cpair;
{
        register NODE *r;

        r = newnode(Node_line_range);
        r->condpair = cpair;
        r->triggered = 0;
        return r;
}

/* Build a for loop */
static NODE *
make_for_loop(init, cond, incr)
NODE *init, *cond, *incr;
{
        register FOR_LOOP_HEADER *r;
        NODE *n;

        emalloc(r, FOR_LOOP_HEADER *, sizeof(FOR_LOOP_HEADER), "make_for_loop");
        n = newnode(Node_illegal);
        r->init = init;
        r->cond = cond;
        r->incr = incr;
        n->sub.nodep.r.hd = r;
        return n;
}

/*
 * Install a name in the hash table specified, even if it is already there.
 * Name stops with first non alphanumeric. Caller must check against
 * redefinition if that is desired. 
 */
NODE *
install(table, name, value)
NODE **table;
char *name;
NODE *value;
{
        register NODE *hp;
        register int len, bucket;
        register char *p;

        len = 0;
        p = name;
        while (is_identchar(*p))
                p++;
        len = p - name;

        hp = newnode(Node_hashnode);
        bucket = hashf(name, len, HASHSIZE);
        hp->hnext = table[bucket];
        table[bucket] = hp;
        hp->hlength = len;
        hp->hvalue = value;
        emalloc(hp->hname, char *, len + 1, "install");
        bcopy(name, hp->hname, len);
        hp->hname[len] = '\0';
        hp->hvalue->varname = hp->hname;
        return hp->hvalue;
}

/*
 * find the most recent hash node for name name (ending with first
 * non-identifier char) installed by install 
 */
NODE *
lookup(table, name)
NODE **table;
char *name;
{
        register char *bp;
        register NODE *bucket;
        register int len;

        for (bp = name; is_identchar(*bp); bp++)
                ;
        len = bp - name;
        bucket = table[hashf(name, len, HASHSIZE)];
        while (bucket) {
                if (bucket->hlength == len && STREQN(bucket->hname, name, len))
                        return bucket->hvalue;
                bucket = bucket->hnext;
        }
        return NULL;
}

#define HASHSTEP(old, c) ((old << 1) + c)
#define MAKE_POS(v) (v & ~0x80000000)   /* make number positive */

/*
 * return hash function on name.
 */
static int
hashf(name, len, hashsize)
register char *name;
register int len;
int hashsize;
{
        register int r = 0;

        while (len--)
                r = HASHSTEP(r, *name++);

        r = MAKE_POS(r) % hashsize;
        return r;
}

/*
 * Add new to the rightmost branch of LIST.  This uses n^2 time, but doesn't
 * get used enough to make optimizing worth it. . . 
 */
/* You don't believe me?  Profile it yourself! */
static NODE *
append_right(list, new)
NODE *list, *new;

{
        register NODE *oldlist;

        oldlist = list;
        while (list->rnode != NULL)
                list = list->rnode;
        list->rnode = new;
        return oldlist;
}

/*
 * check if name is already installed;  if so, it had better have Null value,
 * in which case def is added as the value. Otherwise, install name with def
 * as value. 
 */
static void
func_install(params, def)
NODE *params;
NODE *def;
{
        NODE *r;

        pop_params(params->rnode);
        pop_var(params, 0);
        r = lookup(variables, params->param);
        if (r != NULL) {
                fatal("function name `%s' previously defined", params->param);
        } else
                (void) install(variables, params->param,
                        node(params, Node_func, def));
}

static void
pop_var(np, freeit)
NODE *np;
int freeit;
{
        register char *bp;
        register NODE *bucket, **save;
        register int len;
        char *name;

        name = np->param;
        for (bp = name; is_identchar(*bp); bp++)
                ;
        len = bp - name;
        save = &(variables[hashf(name, len, HASHSIZE)]);
        for (bucket = *save; bucket; bucket = bucket->hnext) {
                if (len == bucket->hlength && STREQN(bucket->hname, name, len)) {
                        *save = bucket->hnext;
                        freenode(bucket);
                        free(bucket->hname);
                        if (freeit)
                                free(np->param);
                        return;
                }
                save = &(bucket->hnext);
        }
}

static void
pop_params(params)
NODE *params;
{
        register NODE *np;

        for (np = params; np != NULL; np = np->rnode)
                pop_var(np, 1);
}

static NODE *
make_param(name)
char *name;
{
        NODE *r;

        r = newnode(Node_param_list);
        r->param = name;
        r->rnode = NULL;
        r->param_cnt = param_counter++;
        return (install(variables, name, r));
}

/* Name points to a variable name.  Make sure its in the symbol table */
NODE *
variable(name)
char *name;
{
        register NODE *r;

        if ((r = lookup(variables, name)) == NULL)
                r = install(variables, name,
                        node(Nnull_string, Node_var, (NODE *) NULL));
        return r;
}
short yyexca[] ={
-1, 1,
        0, -1,
        -2, 0,
-1, 161,
        267, 0,
        -2, 101,
-1, 163,
        264, 0,
        60, 0,
        62, 0,
        124, 0,
        -2, 103,
-1, 164,
        264, 0,
        60, 0,
        62, 0,
        124, 0,
        -2, 104,
-1, 165,
        264, 0,
        60, 0,
        62, 0,
        124, 0,
        -2, 105,
-1, 251,
        267, 0,
        -2, 114,
-1, 253,
        264, 0,
        -2, 116,
        };
# define YYNPROD 156
# define YYLAST 2052
short yyact[]={

  88, 101, 102,  16, 215, 111,  16, 100,  89,  90,
 227, 157, 237, 148,  45,  72,  77, 301,   4,  26,
  97,  38,  45, 296,  26, 295,  36, 172,  35, 193,
 101, 102, 271, 101, 102, 203,  77, 264, 262,  26,
 261,  52, 252,  93, 156, 155,  36, 162,  35, 151,
  37, 177,  72,  16, 126,  53,  72, 171, 103, 202,
  53,  72,  54,  20, 108, 187, 105,  53,  53, 106,
 149, 149,  13, 219, 107, 111,  45,  97,  20, 178,
  53, 158, 159, 161, 150, 163, 164, 165, 166,  53,
  16,  16,  55, 235, 169,  53, 171, 205, 270, 221,
 108, 176, 153, 121, 276, 106, 109, 136, 110, 134,
 107, 116, 186, 115, 186, 190, 191, 186, 128,  21,
 114, 105, 113,  78,  72, 124,   6,  24,  17, 229,
 154,  67,  39, 259,  72, 197,  72, 149,  94,  61,
  97, 140, 104, 141, 123, 260,  94,  91,  95,  11,
 200, 117, 118, 133, 220,  94,  94, 105,  41,  46,
  48,  10, 167, 168,   5,   1,  50,  12,   0, 206,
   0,   0,   0, 224, 226,  23,   0,   0,  77,   0,
   0,  26, 192, 195,   0,  76, 194, 144,  36,   0,
  35,   0,   0,   0,  92,   0, 196,  94,   0,   0,
   0,   0, 112, 238, 216,  85,   0,  86,   0,   0,
 160, 119, 120,   0,   0,   0, 222, 231, 232, 233,
 186,   0,   0,   4, 263,  94,  94,  94,  94,  94,
  94,   4, 186, 186, 268,   0,   0,   0, 204,   0,
 272,   0, 189, 146,   0,   0,  25,  77,   0,   0,
  26,   0,   0,  92,  76,   0,   0,  36,   0,  35,
  30,  25, 144,  34,   0, 104,  33, 173, 256,  79,
  72, 286, 173,  45, 149,  31,  32, 104,  72, 280,
 173, 179, 180, 181, 182, 183, 184, 289, 279, 149,
  28,  29, 173,   0,   0,  31,  32,  27,  94,  72,
 274, 207, 299,   0,   0,   0,  72,  72,  72,   0,
  77,   0,   0,  26,   0,   0,   0,  76, 146,   0,
  36,   0,  35,  94,  94,  94, 144, 144, 144, 144,
 144,   0, 144, 144, 144, 144,  45,  20, 250,  56,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
  77,   0,   0,  26, 228,   0,   0,  76,   0,   0,
  36, 267,  35,   0,   0, 144,   0, 144, 144, 144,
   0, 144,   0, 144, 144, 144,  45,   0,   0, 242,
 243, 244, 146, 146, 146, 146, 146,   0, 146, 146,
 146, 146,   0,   0,  77, 144,   0,  26,   0,   0,
  20,  76,  56,  25,  36,  34,  35,   0,   0,  84,
   0, 144,   0,   0,   0,   0,   0,   0,   0,   0,
  45, 146,   0, 146, 146, 146,   0, 146,   0, 146,
 146, 146,  77,   0,  83,  26,   0,  31,  32,  76,
  20,   0,  36,   0,  35,  77,   0,   0,  26,   0,
   0, 146,  93,   0,   0,  36,   0,  35,  45,  85,
   0,  86,  87,   0,   0,   0,   0, 146,   0,   0,
 130,  30,  25,   0,  34,   0,   0,  33,   0,   0,
   0,   0,   0,   0,  20,   0,  73,   0,  70,  71,
  62,  63,  64,  65,  66,  74,  75,  68,  69,   0,
  22,  28,  29,   0,   0,   0,  31,  32,  27,   0,
   0,   0,   0, 214,   0,   0,   0,  77,   0,   0,
  26,   0,   0,  79,  76, 171,   0,  36,   0,  35,
   0,   0,   0,  58,  30,  25,   0,  34,   0,   0,
  33,   0,   0,   0,  85,   0,  86,  87,   0,  73,
   0,  70,  71,  62,  63,  64,  65,  66,  74,  75,
  68,  69,   0,  22,  28,  29,   0,   0,   0,  31,
  32,  27,   0,  58,  30,  25,  57,  34,   0,   0,
  33, 142,   0,   0,   0,   0,   0,   0,   0,  73,
   0,  70,  71,  62,  63,  64,  65,  66,  74,  75,
  68,  69,   0,  22,  28,  29,   0,   0,  79,  31,
  32,  27,   0,   0,   0,   0,   0,   0,  30,  25,
  96,  34,   0,   0,  33,   0,   0,   0,   0,   0,
   0,   0, 129,  73,   0,  70,  71,  62,  63,  64,
  65,  66,  74,  75,  68,  69,   0,  22,  28,  29,
   0,   0,   0,  31,  32,  27,  30,  25,   0,  34,
   0,   0,  33,  84,   0,   0,  82,   4,  77,   0,
  25,  26,  34,   0,   0,  76, 212,   0,  36,   0,
  35,   0,   0,   0,   0,  22,  28,  29,  83,  80,
  81,  31,  32,  27,  45,  85,   0,  86,  87,   0,
 129, 211,   0,   0,  31,  32,  77,   0,   0,  26,
 129,   0, 198,  76,   0,   0,  36,  53,  35,   0,
 245, 247, 248, 249, 251,   0, 253, 254,   0, 255,
   0,   0, 185,  85, 188,  86,  87, 188,   0,   0,
   0,  30,  25,   0,  34,   0,   2,  33,  84,   0,
   0,  82,   0,   0,  77,   0,   0,  26,   0,  79,
 201,  76,   0,   0,  36,   0,  35,  99,   0,   0,
  22,  28,  29,  83,  80,  81,  31,  32,  27, 223,
   0,  85,   0,  86,  87,   0,   0,   0,   0, 291,
   0, 122,   0,   0,   0,   0,   0,  79,   0,   0,
 125,   0,   0, 131,   0,  77, 132,   0,  26,   0,
 135,   0,  76,  60,   0,  36,  14,  35,   0,  14,
   0,   0,  14,  14,  14,   0,  51,   0,   0,   0,
   0,   0,  85,   0,  86,  87,   0,   0,   0,   0,
 257,   0,   0,   0,   0,  79, 285,   0,  77,   0,
   0,  26, 265, 266, 293,  93,   0,   0,  36,  77,
  35,   0,  26,   0,   0,   0,  76,   0,   0,  36,
   0,  35,   0, 275,   0, 303,   0,   0, 213,   0,
   0,   0, 308, 309, 310,   0,  85,   0,  86,   0,
   0,   0,  30,  25,   0,  34,  79,  77,  33,  84,
  26,   0,  82,   0,  93,   0,   0,  36,   0,  35,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,  22,  28,  29,  83,  80,  81,  31,  32,  27,
  30,  25,   0,  34,   0,   0,  33,  84,   0,  77,
  82, 175,  26,   0,   0,   0,  93,   0,   0,  36,
  79,  35,   0,   0,   0,   0,   0,   0,   0,  22,
  28,  29,  83,  80,  81,  31,  32,  27,   0, 213,
   0,   0,   0,   0,   0,   0,   0,   0,  30,  25,
   0,  34,   0, 269,  33,  84,   0,   0,  82,   0,
  77,   0,   0,  26,   0,   0,   0,  76,   0,   0,
  36,   0,  35,   0,   0, 277,   0,  22,  28,  29,
  83,  80,  81,  31,  32,  27,   0,  85,   0,  86,
   0,   0,   0,   0,   0, 294,   0,   0,   0,  30,
  25,   0,  34,   0, 298,  33,  84, 170, 174,  82,
   0,   0,  18,   0, 302,  26,   0, 305, 306,  19,
   0, 307,  36,   0,  35,   0,  37,   0,  22,  28,
  29,  83,  80,  81,  31,  32,  27,   0,   0,   0,
   0,   0,  30,  25,   0,  34,   0,   0,  33, 212,
   0,  79, 210,  30,  25,  18,  34,   0,  26,  33,
  84,   0,  19,  82,   0,  36,   0,  35,   0,  37,
   0, 145,  28,  29, 211, 208, 209,  31,  32,  27,
   0,   0,  22,  28,  29,  83,  80,   0,  31,  32,
  27,  30,  25,  77,  34,   0,  26,  33, 212, 230,
  93, 210,  20,  36, 234,  35,   0,   0,   0, 236,
   0,   0,   0, 240,   0,   0,   0,   0,   0,   0,
 145,  28,  29, 211, 208,   0,  31,  32,  27,   0,
   0,   0, 258,  30,  25,   0,  34,   0,   0,  33,
 212,  77,   0, 210,  26,  20,   0,   0,  76,   0,
   0,  36,   0,  35,   0,  37,   0,   0,   0,   0,
   0,   0, 145,  28,  29, 211, 208, 209,  31,  32,
  27, 278,   0,   0,   0,   0,   0, 281, 282, 283,
 284,   0,   0, 287,  30,  25,   0,  34,   0,   0,
  33,  84,  77,   0,  82,  26,   0,   0, 297,  76,
   0, 300,  36,   0,  35,   0,   0,   0,   0,   0,
   0, 304,   0,  22,  28,  29,  83,   0,  45,  31,
  32,  27,   0,   0,   0,   0,   0,   0,   0,   0,
   0,  77,   0,   0,  26,  40,  30,  25,  76,  34,
   0,  36,  33,  35,  77,  37,   0,  26,   0,   8,
   9,  76,   0,   0,  36,   0,  35,   0,   0,   0,
   0,   0,   0,   0,  15,  22,  28,  29,   0,   0,
   0,  31,  32,  27,   0,   0,   0,   0,   7,  30,
  25,   0,  34,   0,  77,  33,   0,  26,   0,   0,
   0,  93,   8,   9,  36,   0,  35,   0,  37,   0,
   0,   0,   0,   0,   0,   0,   0,  15,  22,  28,
  29,   0,   0,   0,  31,  32,  27,  30,  25,   0,
  34,   0,   0,  33, 212,  77,   0, 210,  26,   0,
   0,   0,  93,   0,   0,  36,   0,  35,   0,   0,
   0,   0,   0,   0,   0,   0, 145,  28,  29, 211,
   0,   0,  31,  32,  27,   0,   0,   0,   0,   0,
   0,   0,   0,   0,  98,  30,  25,  77,  34,   0,
  26,  33,   0,   0,  76,   0,   0,  36,  18,  35,
   0,  26,   0,   0,   0,  19,   0,   0,  36,   0,
  35,   0,  37,   0,  22,  28,  29,   0,   0,   0,
  31,  32,  27,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,  30,  25,  77,  34,
   0,  26,  33,   0,   0, 139,   0,   0,  36,  77,
  35,   0,  26,   0,   0,   0,  76,   0,   0,  36,
   0,  35,   0,   0,   0,  22,  28,  29,   0,   0,
   0,  31,  32,  27,   0,  30,  25,   0,  34,   0,
   0,  33,   0,   0,   0,   0,   0,  98,  30,  25,
  77,  34,   0,  26,  33,   0,   0,  93,   0,   0,
  36,   0,  35,   0,  22,  28,  29,   0,   0,   0,
  31,  32,  27,   0,   0,   0,   0,  22,  28,  29,
   0,   0,   0,  31,  32,  27,   0,   0,  30,  25,
  77,  34,   0,  26,  33,   0,   0,  76,  77,   0,
  36,  26,  35,   0,  77,  93,   0,  26,  36,   0,
  35,  93,   0,   0,  36,   0,  35, 145,  28,  29,
   0,   0,   0,  31,  32,  27,   0,   0, 246,  30,
  25,   0,  34,   0,   0,  33,   0,   0,   0,   0,
  77,   0,   0,  26,   0,   0,   0,  76,   0,   0,
  36,   0,  35,   0,   0,   0,   0,   0, 145,  28,
  29,   0,   0,   0,  31,  32,  27,   0,   0,   0,
 225,  30,  25,   0,  34,   0,   0,  33,   0,   0,
   0,   3,  30,  25,   0,  34,   0,   0,  33,   0,
  43,  43,  43,   0,   0,   0,   0,   0,   0,   0,
  22,  28,  29,   0,   0,   0,  31,  32,  27,   0,
   0,  22,  28,  29,   0,   0,   0,  31,  32,  27,
  42, 143,  30,  25,   0,  34,   0,   0,  33,   0,
  47,  49,   0,  30,  25,   0,  34,   0,   0,  33,
   0,   0,   0,   0,   0,   0,   0,  43,  43,   0,
  43, 145,  28,  29,  43,   0,   0,  31,  32,  27,
   0,   0,  22,  28,  29,   0,   0,   0,  31,  32,
  27,   0,   0,   0,  30,  25,   0,  34,   0,   0,
  33,   0,   0,   0,   0,   0, 137, 138,   0, 147,
   0,   0,   0, 152,   0,   0,   0,   0,   0,   0,
   0,   0,   0, 145,  28,  29,   0,   0,   0,  31,
  32,  27,   0,   0,  30, 199,   0,  34,   0,   0,
  33,   0,  30,  25,  59,  34,   0,   0,  33,  25,
  43,  34,  43,  44,  44,  44,   0,   0,   0,   0,
   0,   0,   0,  22,  28,  29,   0,   0,   0,  31,
  32,  27,  28,  29,   0,   0,   0,  31,  32,  27,
 211,   0,   0,  31,  32,  25,   0,  34,   0, 217,
   0, 218,   0,   0,   0,   0,   0,   0,   0, 127,
   0,   0,   0,   0,  43,   0,   0,   0,   0,   0,
  44,  44,   0,  44,   0,   0,  83,  44,   0,  31,
  32,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0, 241,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0, 127,   0,   0,  43,   0,  43,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,  44,   0,  44,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0, 290,   0, 292,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0, 239,   0,  44,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0, 273,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0, 288,   0,  44,
   0,  44 };
short yypact[]={

-250,-1000,1052,-247,-1000,1009,-1000,-1000, -45, -45,
 -45,-1000, -60,  51, 277,-1000, 772,-282,   3,1138,
-250,-259, -12,  63,-1000, -16,1515,  82,  80,  73,
  71, -12, -12,-1000,-1000,1515,1515,-1000,-1000,-1000,
-1000,-1000,-1000,-247,-250,-1000,-1000,-1000,-1000,-1000,
-1000, 317,1375,-250,  17, 214,-250,-1000,-1000,-250,
 317,-1000,  69,-250,  67, -37, -37,1415, -37,1426,
1426,-209, 399,  62,-1000,-1000,1241,1515,-213,-275,
1426,1426,1228,-211,1426,1426,1426,1426, -17,1375,
1375,-1000, -28,1426,-291,  55,  16, 484,-1000,-1000,
1426,-1000,-1000,  19,-1000,1515,1515,1515,1515,1515,
1515,1241,-1000,1241,1228,1426,1241,-1000,-1000, -28,
 -28,-230,-1000, 214,-1000,-1000,-1000,-1000,  17,-1000,
-1000,-1000,-1000, 214,1426, 361,1507,-1000,-1000,1241,
 -27,  45, 906,-1000,-262, -12,  63,-1000, -37, 772,
 -37, -18,-1000,1426,  59,-1000,-1000, -12, 957, 826,
-1000, 145,-1000,1557,1557,1557, 721,-1000,-1000, 484,
-1000,-1000,1364,1426,-279,-1000, 772,-1000,1515, -28,
 -28, -28, -28,  27,  27,  36, 772,  55,  24,  51,
 673, 673,  55,  46,-1000,-1000,-1000, 484,-264, -86,
  17,  16, -37,1515,1515,1515,1322,1467,1467,1467,
1281,-216,1467,1467, -17,1467,  19,-1000,-1000,1241,
 484,-218,-1000,1426, 772,-1000, 772,-221,  63,-1000,
-1000,1241,1241,1228,-1000,-1000,-250,  58,-226,1189,
 -27,-1000,  63,  63,  63, 906,-1000, 906,1090, 864,
-1000, 412,-1000,1521, 815, 906,-1000,  11,-250,  55,
  23,-1000,-1000, 772,-1000,  16,  16,  55, 484, 361,
1426,  55, 635,1426, -37,1467, -37, 361,-250,-233,
-1000,-1000,-1000,-1000,-1000,-1000, 484,-250,1426,  55,
-1000, 906,-1000,-256,-1000,-1000,-1000,-250, 361,  55,
-250,-250,-1000,-1000,-250, 361, 361, 361,-1000,-1000,
-1000 };
short yypgo[]={

   0, 167, 166, 513,   0, 165, 164, 126, 175,  72,
 161, 149, 119, 145, 143, 141, 620,  65,  92, 576,
 139, 133,  13,  58, 127, 128,  51,  59, 941,  27,
1631, 746, 131, 130,1670, 123, 813,  62, 103,  54,
1774 };
short yyr1[]={

   0,   5,   6,   6,   6,   6,   7,   7,   7,   7,
   7,   7,   7,   7,  33,  33,  35,   1,   2,   9,
   9,   9,   9,   9,   9,  10,  10,  25,  38,  24,
  11,  11,  18,  18,  18,  18,  34,  34,  19,  19,
  19,  19,  19,  19,  19,  19,  19,  19,  19,  19,
  19,  19,  19,  19,  19,  32,  32,  20,  20,  30,
  30,  31,  31,  26,  26,  27,  27,  27,  27,  21,
  21,  13,  13,  13,  13,  13,  22,  22,  15,  15,
  14,  14,  14,  14,  14,  14,  17,  17,  16,  16,
  16,  16,  16,  16,   4,   4,   4,   4,   4,   4,
   4,   4,   4,   4,   4,   4,   4,   4,   4,   3,
   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,
   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,
   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,
   8,   8,   8,   8,  23,  23,  12,  12,  12,  36,
  37,  28,  39,  39,  40,  29 };
short yyr2[]={

   0,   2,   1,   2,   1,   2,   2,   2,   2,   2,
   2,   1,   2,   2,   1,   1,   0,   7,   3,   1,
   1,   3,   3,   2,   3,   1,   3,   1,   0,   4,
   3,   4,   1,   2,   1,   2,   1,   2,   2,   3,
   1,   6,   8,   8,  10,   9,   2,   2,   6,   4,
   2,   3,   3,   6,   2,   1,   1,   6,   9,   1,
   2,   0,   1,   0,   2,   0,   2,   2,   2,   0,
   1,   1,   3,   1,   2,   3,   0,   1,   0,   1,
   1,   3,   1,   2,   3,   3,   0,   1,   1,   3,
   1,   2,   3,   3,   3,   5,   4,   3,   3,   3,
   3,   3,   3,   3,   3,   3,   5,   2,   1,   3,
   3,   3,   3,   3,   3,   3,   3,   5,   2,   1,
   2,   3,   4,   1,   6,   6,   6,   6,   4,   2,
   2,   2,   2,   1,   1,   1,   3,   3,   3,   3,
   3,   3,   2,   2,   0,   1,   1,   4,   2,   2,
   2,   1,   0,   1,   1,   2 };
short yychk[]={

-1000,  -5, -31, -30, 268,  -6,  -7, 256, 270, 271,
 -10, -11,  -1,  -9, -36, 285,  -4, -25,  33,  40,
 123, -12, 286,  -8, -24, 258,  36, 294, 287, 288,
 257, 292, 293, 263, 260,  45,  43,  47, 268,  -7,
 256, -11, -34, -30, -40,  59, -11, -34, -11, -34,
  -2, -36, -29,  44, -37, -18, 125, -19, 256, -40,
 -36, -20, 276, 277, 278, 279, 280, -32, 283, 284,
 274, 275,  -4, 272, 281, 282,  40,  33, -35, 124,
 290, 291, 267, 289, 264,  60,  62,  63,  -4, 290,
 291, -25,  -8,  40, -12, -25, -16,  -4, 256, -31,
 266, 292, 293, -23, -12,  94,  42,  47,  37,  43,
  45,  91,  -8,  40,  40,  40,  40, -12, -12,  -8,
  -8, -38, -31, -18,  -9, -31, -39, -40, -37, -19,
 256, -31, -31, -18,  40, -31,  40, -34, -34,  40,
 -15, -14,  -3, 256, -12, 286,  -8, -34, -22,  -4,
 -22, 258, -34,  40, -33, 258, 257, 286,  -4,  -4,
 -24,  -4, 258,  -4,  -4,  -4,  -4,  -9,  -9,  -4,
 -28,  41, -29, 256, -28, -28,  -4, -26,  60,  -8,
  -8,  -8,  -8,  -8,  -8, -16,  -4, -17, -16, -24,
  -4,  -4, -17, 259, -37, -39, -37,  -4, -19, 258,
 -22, -16, -27,  62, 265, 124, -29, 256, 290, 291,
 267, 289, 264,  63,  -3, 266, -23, -34, -34,  91,
  -4,  40, -23,  58,  -4, 256,  -4, 289,  -8,  93,
 -28, -29, -29, -29, -28,  47, -28, 276, 289, -40,
 -28, -34,  -8,  -8,  -8,  -3, 256,  -3,  -3,  -3,
 -24,  -3, 258,  -3,  -3,  -3, -26, -16, -28, -21,
 -13, 258, 256,  -4, 258, -16, -16, -24,  -4, -31,
  40, 258,  -4, -40, -27,  58,  93, -31, -28, -29,
 256, -28, -28, -28, -28, -19,  -4, -28, -40, -22,
 -34,  -3, -34, -19, -31, 258, 256, -28, -31, -22,
 -28, 273, -31, -19, -28, -31, -31, -31, -19, -19,
 -19 };
short yydef[]={

  61,  -2,   0,  62,  59,   1,   2,   4,   0,   0,
   0,  11,   0,  25,   0,  16,  19,  20,   0,   0,
  61, 133, 144, 108,  27, 146,   0, 123,   0,   0,
   0,   0,   0, 134, 135,   0,   0,  28,  60,   3,
   5,   6,   8,  36,  61, 154,   7,   9,  10,  12,
  13,   0,   0,  61, 152,   0,  61,  32,  34,  61,
   0,  40,   0,  61,   0,   0,   0,  78,   0,  76,
  76,   0,   0,   0,  55,  56,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0, 107,   0,
   0,  23, 120,   0, 133,   0,   0,  88,  90, 149,
   0, 131, 132,  63, 145,   0,   0,   0,   0,   0,
   0,   0, 148,  86,   0,   0,  86, 129, 130, 142,
 143,   0,  37,   0,  26, 155,  30, 153, 152,  33,
  35, 150,  38,   0,   0,   0,  76,  46,  47,   0,
  65,  79,  80,  82, 133, 144, 119,  50,   0,  77,
   0,   0,  54,   0,   0,  14,  15, 144,  98,  99,
 100,  -2, 102,  -2,  -2,  -2,   0,  21,  22,   0,
  24, 151,   0,  91,   0, 121,  94,  97,   0, 136,
 137, 138, 139, 140, 141,   0,  88,   0,  87,   0,
   0,   0,   0,   0,  18,  31,  39,   0,   0, 146,
   0,   0,   0,   0,   0,   0,   0,  83,   0,   0,
   0,   0,   0,   0, 118,   0,  63,  51,  52,   0,
   0,  69,  96,   0,  89,  93,  92,   0,  64, 147,
 122,   0,   0,   0, 128,  29,  61,   0,   0,   0,
  65,  49,  66,  67,  68,  81,  85,  84, 110, 111,
 113,  -2, 115,  -2,   0, 109, 112,   0,  61,   0,
  70,  71,  73, 106,  95,   0,   0,   0,   0,   0,
   0,   0,   0,  76,   0,   0,   0,   0,  61,   0,
  74, 124, 125, 126, 127,  41,   0,  61,  76,   0,
  48, 117,  53,  57,  17,  72,  75,  61,   0,   0,
  61,  61,  42,  43,  61,   0,   0,   0,  45,  58,
  44 };
#ifndef lint
static char yaccpar_sccsid[] = "@(#)yaccpar     4.1     (Berkeley)      2/11/83";
#endif not lint

#
# define YYFLAG -1000
# define YYERROR goto yyerrlab
# define YYACCEPT return(0)
# define YYABORT return(1)

/*      parser for yacc output  */

#ifdef YYDEBUG
int yydebug = 0; /* 1 for debugging */
#endif
YYSTYPE yyv[YYMAXDEPTH]; /* where the values are stored */
int yychar = -1; /* current input token number */
int yynerrs = 0;  /* number of errors */
short yyerrflag = 0;  /* error recovery flag */

yyparse() {

        short yys[YYMAXDEPTH];
        short yyj, yym;
        register YYSTYPE *yypvt;
        register short yystate, *yyps, yyn;
        register YYSTYPE *yypv;
        register short *yyxi;

        yystate = 0;
        yychar = -1;
        yynerrs = 0;
        yyerrflag = 0;
        yyps= &yys[-1];
        yypv= &yyv[-1];

 yystack:    /* put a state and value onto the stack */

#ifdef YYDEBUG
        if( yydebug  ) printf( "state %d, char 0%o\n", yystate, yychar );
#endif
                if( ++yyps> &yys[YYMAXDEPTH] ) { yyerror( "yacc stack overflow" ); return(1); }
                *yyps = yystate;
                ++yypv;
                *yypv = yyval;

 yynewstate:

        yyn = yypact[yystate];

        if( yyn<= YYFLAG ) goto yydefault; /* simple state */

        if( yychar<0 ) if( (yychar=yylex())<0 ) yychar=0;
        if( (yyn += yychar)<0 || yyn >= YYLAST ) goto yydefault;

        if( yychk[ yyn=yyact[ yyn ] ] == yychar ){ /* valid shift */
                yychar = -1;
                yyval = yylval;
                yystate = yyn;
                if( yyerrflag > 0 ) --yyerrflag;
                goto yystack;
                }

 yydefault:
        /* default state action */

        if( (yyn=yydef[yystate]) == -2 ) {
                if( yychar<0 ) if( (yychar=yylex())<0 ) yychar = 0;
                /* look through exception table */

                for( yyxi=yyexca; (*yyxi!= (-1)) || (yyxi[1]!=yystate) ; yyxi += 2 ) ; /* VOID */

                while( *(yyxi+=2) >= 0 ){
                        if( *yyxi == yychar ) break;
                        }
                if( (yyn = yyxi[1]) < 0 ) return(0);   /* accept */
                }

        if( yyn == 0 ){ /* error */
                /* error ... attempt to resume parsing */

                switch( yyerrflag ){

                case 0:   /* brand new error */

                        yyerror( "syntax error" );
                yyerrlab:
                        ++yynerrs;

                case 1:
                case 2: /* incompletely recovered error ... try again */

                        yyerrflag = 3;

                        /* find a state where "error" is a legal shift action */

                        while ( yyps >= yys ) {
                           yyn = yypact[*yyps] + YYERRCODE;
                           if( yyn>= 0 && yyn < YYLAST && yychk[yyact[yyn]] == YYERRCODE ){
                              yystate = yyact[yyn];  /* simulate a shift of "error" */
                              goto yystack;
                              }
                           yyn = yypact[*yyps];

                           /* the current yyps has no shift onn "error", pop stack */

#ifdef YYDEBUG
                           if( yydebug ) printf( "error recovery pops state %d, uncovers %d\n", *yyps, yyps[-1] );
#endif
                           --yyps;
                           --yypv;
                           }

                        /* there is no state on the stack with an error shift ... abort */

        yyabort:
                        return(1);


                case 3:  /* no shift yet; clobber input char */

#ifdef YYDEBUG
                        if( yydebug ) printf( "error recovery discards char %d\n", yychar );
#endif

                        if( yychar == 0 ) goto yyabort; /* don't discard EOF, quit */
                        yychar = -1;
                        goto yynewstate;   /* try again in the same state */

                        }

                }

        /* reduction by production yyn */

#ifdef YYDEBUG
                if( yydebug ) printf("reduce %d\n",yyn);
#endif
                yyps -= yyr2[yyn];
                yypvt = yypv;
                yypv -= yyr2[yyn];
                yyval = yypv[1];
                yym=yyn;
                        /* consult goto table to find next state */
                yyn = yyr1[yyn];
                yyj = yypgo[yyn] + *yyps + 1;
                if( yyj>=YYLAST || yychk[ yystate = yyact[yyj] ] != -yyn ) yystate = yyact[yypgo[yyn]];
                switch(yym){
                        
case 1:
# line 301 "awk.y"
{ expression_value = yypvt[-0].nodeval; } break;
case 2:
# line 306 "awk.y"
{ 
                        if (yypvt[-0].nodeval != NULL)
                                yyval.nodeval = yypvt[-0].nodeval;
                        else
                                yyval.nodeval = NULL;
                        yyerrok;
                } break;
case 3:
# line 315 "awk.y"
{
                        if (yypvt[-0].nodeval == NULL)
                                yyval.nodeval = yypvt[-1].nodeval;
                        else if (yypvt[-1].nodeval == NULL)
                                yyval.nodeval = yypvt[-0].nodeval;
                        else {
                                if (yypvt[-1].nodeval->type != Node_rule_list)
                                        yypvt[-1].nodeval = node(yypvt[-1].nodeval, Node_rule_list,
                                                (NODE*)NULL);
                                yyval.nodeval = append_right (yypvt[-1].nodeval,
                                   node(yypvt[-0].nodeval, Node_rule_list,(NODE *) NULL));
                        }
                        yyerrok;
                } break;
case 4:
# line 329 "awk.y"
{ yyval.nodeval = NULL; } break;
case 5:
# line 330 "awk.y"
{ yyval.nodeval = NULL; } break;
case 6:
# line 335 "awk.y"
{
                if (begin_block) {
                        if (begin_block->type != Node_rule_list)
                                begin_block = node(begin_block, Node_rule_list,
                                        (NODE *)NULL);
                        append_right (begin_block, node(
                            node((NODE *)NULL, Node_rule_node, yypvt[-0].nodeval),
                            Node_rule_list, (NODE *)NULL) );
                } else
                        begin_block = node((NODE *)NULL, Node_rule_node, yypvt[-0].nodeval);
                yyval.nodeval = NULL;
                yyerrok;
          } break;
case 7:
# line 349 "awk.y"
{
                if (end_block) {
                        if (end_block->type != Node_rule_list)
                                end_block = node(end_block, Node_rule_list,
                                        (NODE *)NULL);
                        append_right (end_block, node(
                            node((NODE *)NULL, Node_rule_node, yypvt[-0].nodeval),
                            Node_rule_list, (NODE *)NULL));
                } else
                        end_block = node((NODE *)NULL, Node_rule_node, yypvt[-0].nodeval);
                yyval.nodeval = NULL;
                yyerrok;
          } break;
case 8:
# line 363 "awk.y"
{
                msg ("error near line %d: BEGIN blocks must have an action part", lineno);
                errcount++;
                yyerrok;
          } break;
case 9:
# line 369 "awk.y"
{
                msg ("error near line %d: END blocks must have an action part", lineno);
                errcount++;
                yyerrok;
          } break;
case 10:
# line 375 "awk.y"
{ yyval.nodeval = node (yypvt[-1].nodeval, Node_rule_node, yypvt[-0].nodeval); yyerrok; } break;
case 11:
# line 377 "awk.y"
{ yyval.nodeval = node ((NODE *)NULL, Node_rule_node, yypvt[-0].nodeval); yyerrok; } break;
case 12:
# line 379 "awk.y"
{ if(yypvt[-1].nodeval) yyval.nodeval = node (yypvt[-1].nodeval, Node_rule_node, (NODE *)NULL); yyerrok; } break;
case 13:
# line 381 "awk.y"
{
                        func_install(yypvt[-1].nodeval, yypvt[-0].nodeval);
                        yyval.nodeval = NULL;
                        yyerrok;
                } break;
case 14:
# line 390 "awk.y"
{ yyval.sval = yypvt[-0].sval; } break;
case 15:
# line 392 "awk.y"
{ yyval.sval = yypvt[-0].sval; } break;
case 16:
# line 397 "awk.y"
{
                        param_counter = 0;
                } break;
case 17:
# line 401 "awk.y"
{
                        yyval.nodeval = append_right(make_param(yypvt[-4].sval), yypvt[-2].nodeval);
                } break;
case 18:
# line 408 "awk.y"
{ yyval.nodeval = yypvt[-1].nodeval; } break;
case 19:
# line 414 "awk.y"
{ yyval.nodeval = yypvt[-0].nodeval; } break;
case 20:
# line 416 "awk.y"
{ yyval.nodeval = yypvt[-0].nodeval; } break;
case 21:
# line 418 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, Node_and, yypvt[-0].nodeval); } break;
case 22:
# line 420 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, Node_or, yypvt[-0].nodeval); } break;
case 23:
# line 422 "awk.y"
{ yyval.nodeval = node (yypvt[-0].nodeval, Node_not,(NODE *) NULL); } break;
case 24:
# line 424 "awk.y"
{ yyval.nodeval = yypvt[-1].nodeval; } break;
case 25:
# line 429 "awk.y"
{ yyval.nodeval = yypvt[-0].nodeval; } break;
case 26:
# line 431 "awk.y"
{ yyval.nodeval = mkrangenode ( node(yypvt[-2].nodeval, Node_cond_pair, yypvt[-0].nodeval) ); } break;
case 27:
# line 436 "awk.y"
{ 
                  yyval.nodeval = node(
                       node(make_number((AWKNUM)0),Node_field_spec,(NODE*)NULL),
                       Node_match, yypvt[-0].nodeval);
                } break;
case 28:
# line 449 "awk.y"
{ ++want_regexp; } break;
case 29:
# line 451 "awk.y"
{
                  want_regexp = 0;
                  yyval.nodeval = node((NODE *)NULL,Node_regex,(NODE *)mk_re_parse(yypvt[-1].sval, 0));
                  yyval.nodeval -> re_case = 0;
                  emalloc (yyval.nodeval -> re_text, char *, strlen(yypvt[-1].sval)+1, "regexp");
                  strcpy (yyval.nodeval -> re_text, yypvt[-1].sval);
                } break;
case 30:
# line 462 "awk.y"
{
                        /* empty actions are different from missing actions */
                        yyval.nodeval = node ((NODE *) NULL, Node_illegal, (NODE *) NULL);
                } break;
case 31:
# line 467 "awk.y"
{ yyval.nodeval = yypvt[-2].nodeval ; } break;
case 32:
# line 472 "awk.y"
{ yyval.nodeval = yypvt[-0].nodeval; } break;
case 33:
# line 474 "awk.y"
{
                        if (yypvt[-1].nodeval->type != Node_statement_list)
                                yypvt[-1].nodeval = node(yypvt[-1].nodeval, Node_statement_list,(NODE *)NULL);
                        yyval.nodeval = append_right(yypvt[-1].nodeval,
                                node( yypvt[-0].nodeval, Node_statement_list, (NODE *)NULL));
                        yyerrok;
                } break;
case 34:
# line 482 "awk.y"
{ yyval.nodeval = NULL; } break;
case 35:
# line 484 "awk.y"
{ yyval.nodeval = NULL; } break;
case 36:
# line 489 "awk.y"
{ yyval.nodetypeval = Node_illegal; } break;
case 37:
# line 491 "awk.y"
{ yyval.nodetypeval = Node_illegal; } break;
case 38:
# line 497 "awk.y"
{ yyval.nodeval = NULL; } break;
case 39:
# line 499 "awk.y"
{ yyval.nodeval = yypvt[-1].nodeval; } break;
case 40:
# line 501 "awk.y"
{ yyval.nodeval = yypvt[-0].nodeval; } break;
case 41:
# line 503 "awk.y"
{ yyval.nodeval = node (yypvt[-3].nodeval, Node_K_while, yypvt[-0].nodeval); } break;
case 42:
# line 505 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, Node_K_do, yypvt[-5].nodeval); } break;
case 43:
# line 507 "awk.y"
{
                yyval.nodeval = node (yypvt[-0].nodeval, Node_K_arrayfor, make_for_loop(variable(yypvt[-5].sval),
                        (NODE *)NULL, variable(yypvt[-3].sval)));
          } break;
case 44:
# line 512 "awk.y"
{
                yyval.nodeval = node(yypvt[-0].nodeval, Node_K_for, (NODE *)make_for_loop(yypvt[-7].nodeval, yypvt[-5].nodeval, yypvt[-3].nodeval));
          } break;
case 45:
# line 516 "awk.y"
{
                yyval.nodeval = node (yypvt[-0].nodeval, Node_K_for,
                        (NODE *)make_for_loop(yypvt[-6].nodeval, (NODE *)NULL, yypvt[-3].nodeval));
          } break;
case 46:
# line 522 "awk.y"
{ yyval.nodeval = node ((NODE *)NULL, Node_K_break, (NODE *)NULL); } break;
case 47:
# line 525 "awk.y"
{ yyval.nodeval = node ((NODE *)NULL, Node_K_continue, (NODE *)NULL); } break;
case 48:
# line 527 "awk.y"
{ yyval.nodeval = node (yypvt[-3].nodeval, yypvt[-5].nodetypeval, yypvt[-1].nodeval); } break;
case 49:
# line 529 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, yypvt[-3].nodetypeval, yypvt[-1].nodeval); } break;
case 50:
# line 531 "awk.y"
{ yyval.nodeval = node ((NODE *)NULL, Node_K_next, (NODE *)NULL); } break;
case 51:
# line 533 "awk.y"
{ yyval.nodeval = node (yypvt[-1].nodeval, Node_K_exit, (NODE *)NULL); } break;
case 52:
# line 535 "awk.y"
{ yyval.nodeval = node (yypvt[-1].nodeval, Node_K_return, (NODE *)NULL); } break;
case 53:
# line 537 "awk.y"
{ yyval.nodeval = node (variable(yypvt[-4].sval), Node_K_delete, yypvt[-2].nodeval); } break;
case 54:
# line 539 "awk.y"
{ yyval.nodeval = yypvt[-1].nodeval; } break;
case 55:
# line 544 "awk.y"
{ yyval.nodetypeval = yypvt[-0].nodetypeval; } break;
case 56:
# line 546 "awk.y"
{ yyval.nodetypeval = yypvt[-0].nodetypeval; } break;
case 57:
# line 551 "awk.y"
{
                yyval.nodeval = node(yypvt[-3].nodeval, Node_K_if, 
                        node(yypvt[-0].nodeval, Node_if_branches, (NODE *)NULL));
          } break;
case 58:
# line 557 "awk.y"
{ yyval.nodeval = node (yypvt[-6].nodeval, Node_K_if,
                                node (yypvt[-3].nodeval, Node_if_branches, yypvt[-0].nodeval)); } break;
case 59:
# line 563 "awk.y"
{ yyval.nodetypeval = NULL; } break;
case 60:
# line 565 "awk.y"
{ yyval.nodetypeval = NULL; } break;
case 61:
# line 570 "awk.y"
{ yyval.nodetypeval = NULL; } break;
case 62:
# line 572 "awk.y"
{ yyval.nodetypeval = NULL; } break;
case 63:
# line 577 "awk.y"
{ yyval.nodeval = NULL; } break;
case 64:
# line 579 "awk.y"
{ yyval.nodeval = node (yypvt[-0].nodeval, Node_redirect_input, (NODE *)NULL); } break;
case 65:
# line 584 "awk.y"
{ yyval.nodeval = NULL; } break;
case 66:
# line 586 "awk.y"
{ yyval.nodeval = node (yypvt[-0].nodeval, Node_redirect_output, (NODE *)NULL); } break;
case 67:
# line 588 "awk.y"
{ yyval.nodeval = node (yypvt[-0].nodeval, Node_redirect_append, (NODE *)NULL); } break;
case 68:
# line 590 "awk.y"
{ yyval.nodeval = node (yypvt[-0].nodeval, Node_redirect_pipe, (NODE *)NULL); } break;
case 69:
# line 595 "awk.y"
{ yyval.nodeval = NULL; } break;
case 70:
# line 597 "awk.y"
{ yyval.nodeval = yypvt[-0].nodeval; } break;
case 71:
# line 602 "awk.y"
{ yyval.nodeval = make_param(yypvt[-0].sval); } break;
case 72:
# line 604 "awk.y"
{ yyval.nodeval = append_right(yypvt[-2].nodeval, make_param(yypvt[-0].sval)); yyerrok; } break;
case 73:
# line 606 "awk.y"
{ yyval.nodeval = NULL; } break;
case 74:
# line 608 "awk.y"
{ yyval.nodeval = NULL; } break;
case 75:
# line 610 "awk.y"
{ yyval.nodeval = NULL; } break;
case 76:
# line 616 "awk.y"
{ yyval.nodeval = NULL; } break;
case 77:
# line 618 "awk.y"
{ yyval.nodeval = yypvt[-0].nodeval; } break;
case 78:
# line 623 "awk.y"
{ yyval.nodeval = NULL; } break;
case 79:
# line 625 "awk.y"
{ yyval.nodeval = yypvt[-0].nodeval; } break;
case 80:
# line 630 "awk.y"
{ yyval.nodeval = node (yypvt[-0].nodeval, Node_expression_list, (NODE *)NULL); } break;
case 81:
# line 632 "awk.y"
{
                yyval.nodeval = append_right(yypvt[-2].nodeval,
                        node( yypvt[-0].nodeval, Node_expression_list, (NODE *)NULL));
                yyerrok;
          } break;
case 82:
# line 638 "awk.y"
{ yyval.nodeval = NULL; } break;
case 83:
# line 640 "awk.y"
{ yyval.nodeval = NULL; } break;
case 84:
# line 642 "awk.y"
{ yyval.nodeval = NULL; } break;
case 85:
# line 644 "awk.y"
{ yyval.nodeval = NULL; } break;
case 86:
# line 649 "awk.y"
{ yyval.nodeval = NULL; } break;
case 87:
# line 651 "awk.y"
{ yyval.nodeval = yypvt[-0].nodeval; } break;
case 88:
# line 656 "awk.y"
{ yyval.nodeval = node (yypvt[-0].nodeval, Node_expression_list, (NODE *)NULL); } break;
case 89:
# line 658 "awk.y"
{
                        yyval.nodeval = append_right(yypvt[-2].nodeval,
                                node( yypvt[-0].nodeval, Node_expression_list, (NODE *)NULL));
                        yyerrok;
                } break;
case 90:
# line 664 "awk.y"
{ yyval.nodeval = NULL; } break;
case 91:
# line 666 "awk.y"
{ yyval.nodeval = NULL; } break;
case 92:
# line 668 "awk.y"
{ yyval.nodeval = NULL; } break;
case 93:
# line 670 "awk.y"
{ yyval.nodeval = NULL; } break;
case 94:
# line 675 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, yypvt[-1].nodetypeval, yypvt[-0].nodeval); } break;
case 95:
# line 677 "awk.y"
{ yyval.nodeval = node (variable(yypvt[-0].sval), Node_in_array, yypvt[-3].nodeval); } break;
case 96:
# line 679 "awk.y"
{
                  yyval.nodeval = node (yypvt[-0].nodeval, Node_K_getline,
                         node (yypvt[-3].nodeval, Node_redirect_pipein, (NODE *)NULL));
                } break;
case 97:
# line 684 "awk.y"
{
                  yyval.nodeval = node (yypvt[-1].nodeval, Node_K_getline, yypvt[-0].nodeval);
                } break;
case 98:
# line 688 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, Node_and, yypvt[-0].nodeval); } break;
case 99:
# line 690 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, Node_or, yypvt[-0].nodeval); } break;
case 100:
# line 692 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, yypvt[-1].nodetypeval, yypvt[-0].nodeval); } break;
case 101:
# line 694 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, yypvt[-1].nodetypeval, yypvt[-0].nodeval); } break;
case 102:
# line 696 "awk.y"
{ yyval.nodeval = node (variable(yypvt[-0].sval), Node_in_array, yypvt[-2].nodeval); } break;
case 103:
# line 698 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, yypvt[-1].nodetypeval, yypvt[-0].nodeval); } break;
case 104:
# line 700 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, Node_less, yypvt[-0].nodeval); } break;
case 105:
# line 702 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, Node_greater, yypvt[-0].nodeval); } break;
case 106:
# line 704 "awk.y"
{ yyval.nodeval = node(yypvt[-4].nodeval, Node_cond_exp, node(yypvt[-2].nodeval, Node_if_branches, yypvt[-0].nodeval));} break;
case 107:
# line 706 "awk.y"
{ yyval.nodeval = node (yypvt[-1].nodeval, Node_concat, yypvt[-0].nodeval); } break;
case 108:
# line 708 "awk.y"
{ yyval.nodeval = yypvt[-0].nodeval; } break;
case 109:
# line 713 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, yypvt[-1].nodetypeval, yypvt[-0].nodeval); } break;
case 110:
# line 715 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, Node_and, yypvt[-0].nodeval); } break;
case 111:
# line 717 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, Node_or, yypvt[-0].nodeval); } break;
case 112:
# line 719 "awk.y"
{
                  yyval.nodeval = node (yypvt[-1].nodeval, Node_K_getline, yypvt[-0].nodeval);
                } break;
case 113:
# line 723 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, yypvt[-1].nodetypeval, yypvt[-0].nodeval); } break;
case 114:
# line 725 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, yypvt[-1].nodetypeval, yypvt[-0].nodeval); } break;
case 115:
# line 727 "awk.y"
{ yyval.nodeval = node (variable(yypvt[-0].sval), Node_in_array, yypvt[-2].nodeval); } break;
case 116:
# line 729 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, yypvt[-1].nodetypeval, yypvt[-0].nodeval); } break;
case 117:
# line 731 "awk.y"
{ yyval.nodeval = node(yypvt[-4].nodeval, Node_cond_exp, node(yypvt[-2].nodeval, Node_if_branches, yypvt[-0].nodeval));} break;
case 118:
# line 733 "awk.y"
{ yyval.nodeval = node (yypvt[-1].nodeval, Node_concat, yypvt[-0].nodeval); } break;
case 119:
# line 735 "awk.y"
{ yyval.nodeval = yypvt[-0].nodeval; } break;
case 120:
# line 740 "awk.y"
{ yyval.nodeval = node (yypvt[-0].nodeval, Node_not,(NODE *) NULL); } break;
case 121:
# line 742 "awk.y"
{ yyval.nodeval = yypvt[-1].nodeval; } break;
case 122:
# line 744 "awk.y"
{ yyval.nodeval = snode (yypvt[-1].nodeval, Node_builtin, yypvt[-3].ptrval); } break;
case 123:
# line 746 "awk.y"
{ yyval.nodeval = snode ((NODE *)NULL, Node_builtin, yypvt[-0].ptrval); } break;
case 124:
# line 748 "awk.y"
{ yyval.nodeval = node(yypvt[-1].nodeval, yypvt[-5].nodetypeval, yypvt[-3].nodeval); } break;
case 125:
# line 750 "awk.y"
{ yyval.nodeval = node(yypvt[-1].nodeval, yypvt[-5].nodetypeval, yypvt[-3].nodeval); } break;
case 126:
# line 752 "awk.y"
{ yyval.nodeval = node(yypvt[-3].nodeval, yypvt[-5].nodetypeval, yypvt[-1].nodeval); } break;
case 127:
# line 754 "awk.y"
{ yyval.nodeval = node(yypvt[-3].nodeval, yypvt[-5].nodetypeval, yypvt[-1].nodeval); } break;
case 128:
# line 756 "awk.y"
{
                yyval.nodeval = node (yypvt[-1].nodeval, Node_func_call, make_string(yypvt[-3].sval, strlen(yypvt[-3].sval)));
          } break;
case 129:
# line 760 "awk.y"
{ yyval.nodeval = node (yypvt[-0].nodeval, Node_preincrement, (NODE *)NULL); } break;
case 130:
# line 762 "awk.y"
{ yyval.nodeval = node (yypvt[-0].nodeval, Node_predecrement, (NODE *)NULL); } break;
case 131:
# line 764 "awk.y"
{ yyval.nodeval = node (yypvt[-1].nodeval, Node_postincrement, (NODE *)NULL); } break;
case 132:
# line 766 "awk.y"
{ yyval.nodeval = node (yypvt[-1].nodeval, Node_postdecrement, (NODE *)NULL); } break;
case 133:
# line 768 "awk.y"
{ yyval.nodeval = yypvt[-0].nodeval; } break;
case 134:
# line 770 "awk.y"
{ yyval.nodeval = make_number (yypvt[-0].fval); } break;
case 135:
# line 772 "awk.y"
{ yyval.nodeval = make_string (yypvt[-0].sval, -1); } break;
case 136:
# line 776 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, Node_exp, yypvt[-0].nodeval); } break;
case 137:
# line 778 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, Node_times, yypvt[-0].nodeval); } break;
case 138:
# line 780 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, Node_quotient, yypvt[-0].nodeval); } break;
case 139:
# line 782 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, Node_mod, yypvt[-0].nodeval); } break;
case 140:
# line 784 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, Node_plus, yypvt[-0].nodeval); } break;
case 141:
# line 786 "awk.y"
{ yyval.nodeval = node (yypvt[-2].nodeval, Node_minus, yypvt[-0].nodeval); } break;
case 142:
# line 788 "awk.y"
{ yyval.nodeval = node (yypvt[-0].nodeval, Node_unary_minus, (NODE *)NULL); } break;
case 143:
# line 790 "awk.y"
{ yyval.nodeval = yypvt[-0].nodeval; } break;
case 144:
# line 795 "awk.y"
{ yyval.nodeval = NULL; } break;
case 145:
# line 797 "awk.y"
{ yyval.nodeval = yypvt[-0].nodeval; } break;
case 146:
# line 802 "awk.y"
{ yyval.nodeval = variable (yypvt[-0].sval); } break;
case 147:
# line 804 "awk.y"
{ yyval.nodeval = node (variable(yypvt[-3].sval), Node_subscript, yypvt[-1].nodeval); } break;
case 148:
# line 806 "awk.y"
{ yyval.nodeval = node (yypvt[-0].nodeval, Node_field_spec, (NODE *)NULL); } break;
case 150:
# line 814 "awk.y"
{ yyerrok; } break;
case 151:
# line 818 "awk.y"
{ yyval.nodetypeval = Node_illegal; yyerrok; } break;
case 154:
# line 827 "awk.y"
{ yyerrok; } break;
case 155:
# line 830 "awk.y"
{ yyval.nodetypeval = Node_illegal; yyerrok; } break;
                }
                goto yystack;  /* stack new state and value */

        }
