/* A Bison parser, made by GNU Bison 2.7.1.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 26 "awkgram.y"

#ifdef GAWKDEBUG
#define YYDEBUG 12
#endif

#include "awk.h"

#if defined(__STDC__) && __STDC__ < 1	/* VMS weirdness, maybe elsewhere */
#define signed /**/
#endif

static void yyerror(const char *m, ...) ATTRIBUTE_PRINTF_1;
static void error_ln(int line, const char *m, ...) ATTRIBUTE_PRINTF_2;
static void lintwarn_ln(int line, const char *m, ...) ATTRIBUTE_PRINTF_2;
static void warning_ln(int line, const char *m, ...) ATTRIBUTE_PRINTF_2;
static char *get_src_buf(void);
static int yylex(void);
int	yyparse(void); 
static INSTRUCTION *snode(INSTRUCTION *subn, INSTRUCTION *op);
static char **check_params(char *fname, int pcount, INSTRUCTION *list);
static int install_function(char *fname, INSTRUCTION *fi, INSTRUCTION *plist);
static NODE *mk_rexp(INSTRUCTION *exp);
static void param_sanity(INSTRUCTION *arglist);
static int parms_shadow(INSTRUCTION *pc, bool *shadow);
#ifndef NO_LINT
static int isnoeffect(OPCODE type);
#endif
static INSTRUCTION *make_assignable(INSTRUCTION *ip);
static void dumpintlstr(const char *str, size_t len);
static void dumpintlstr2(const char *str1, size_t len1, const char *str2, size_t len2);
static int include_source(INSTRUCTION *file);
static int load_library(INSTRUCTION *file);
static void next_sourcefile(void);
static char *tokexpand(void);
static bool is_deferred_variable(const char *name);

#define instruction(t)	bcalloc(t, 1, 0)

static INSTRUCTION *mk_program(void);
static INSTRUCTION *append_rule(INSTRUCTION *pattern, INSTRUCTION *action);
static INSTRUCTION *mk_function(INSTRUCTION *fi, INSTRUCTION *def);
static INSTRUCTION *mk_condition(INSTRUCTION *cond, INSTRUCTION *ifp, INSTRUCTION *true_branch,
		INSTRUCTION *elsep,	INSTRUCTION *false_branch);
static INSTRUCTION *mk_expression_list(INSTRUCTION *list, INSTRUCTION *s1);
static INSTRUCTION *mk_for_loop(INSTRUCTION *forp, INSTRUCTION *init, INSTRUCTION *cond,
		INSTRUCTION *incr, INSTRUCTION *body);
static void fix_break_continue(INSTRUCTION *list, INSTRUCTION *b_target, INSTRUCTION *c_target);
static INSTRUCTION *mk_binary(INSTRUCTION *s1, INSTRUCTION *s2, INSTRUCTION *op);
static INSTRUCTION *mk_boolean(INSTRUCTION *left, INSTRUCTION *right, INSTRUCTION *op);
static INSTRUCTION *mk_assignment(INSTRUCTION *lhs, INSTRUCTION *rhs, INSTRUCTION *op);
static INSTRUCTION *mk_getline(INSTRUCTION *op, INSTRUCTION *opt_var, INSTRUCTION *redir, int redirtype);
static NODE *make_regnode(int type, NODE *exp);
static int count_expressions(INSTRUCTION **list, bool isarg);
static INSTRUCTION *optimize_assignment(INSTRUCTION *exp);
static void add_lint(INSTRUCTION *list, LINTTYPE linttype);

static void process_deferred();

enum defref { FUNC_DEFINE, FUNC_USE, FUNC_EXT };
static void func_use(const char *name, enum defref how);
static void check_funcs(void);

static ssize_t read_one_line(int fd, void *buffer, size_t count);
static int one_line_close(int fd);

static bool want_source = false;
static bool want_regexp = false;	/* lexical scanning kludge */
static char *in_function;		/* parsing kludge */
static bool symtab_used = false;	/* program used SYMTAB */
static int rule = 0;

const char *const ruletab[] = {
	"?",
	"BEGIN",
	"Rule",
	"END",
	"BEGINFILE",
	"ENDFILE",
};

static bool in_print = false;	/* lexical scanning kludge for print */
static int in_parens = 0;	/* lexical scanning kludge for print */
static int sub_counter = 0;	/* array dimension counter for use in delete */
static char *lexptr = NULL;		/* pointer to next char during parsing */
static char *lexend;
static char *lexptr_begin;	/* keep track of where we were for error msgs */
static char *lexeme;		/* beginning of lexeme for debugging */
static bool lexeof;		/* seen EOF for current source? */  
static char *thisline = NULL;
static int in_braces = 0;	/* count braces for firstline, lastline in an 'action' */
static int lastline = 0;
static int firstline = 0;
static SRCFILE *sourcefile = NULL;	/* current program source */
static int lasttok = 0;
static bool eof_warned = false;	/* GLOBAL: want warning for each file */
static int break_allowed;	/* kludge for break */
static int continue_allowed;	/* kludge for continue */

#define END_FILE	-1000
#define END_SRC  	-2000

#define YYDEBUG_LEXER_TEXT (lexeme)
static char *tokstart = NULL;
static char *tok = NULL;
static char *tokend;
static int errcount = 0;

extern char *source;
extern int sourceline;
extern SRCFILE *srcfiles;
extern INSTRUCTION *rule_list;
extern int max_args;
extern NODE **args_array;

static INSTRUCTION *rule_block[sizeof(ruletab)];

static INSTRUCTION *ip_rec;
static INSTRUCTION *ip_newfile;
static INSTRUCTION *ip_atexit = NULL;
static INSTRUCTION *ip_end;
static INSTRUCTION *ip_endfile;
static INSTRUCTION *ip_beginfile;

static inline INSTRUCTION *list_create(INSTRUCTION *x);
static inline INSTRUCTION *list_append(INSTRUCTION *l, INSTRUCTION *x);
static inline INSTRUCTION *list_prepend(INSTRUCTION *l, INSTRUCTION *x);
static inline INSTRUCTION *list_merge(INSTRUCTION *l1, INSTRUCTION *l2);

extern double fmod(double x, double y);

#define YYSTYPE INSTRUCTION *

#define is_identchar(c)		(isalnum(c) || (c) == '_')

/* Line 371 of yacc.c  */
#line 203 "awkgram.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     FUNC_CALL = 258,
     NAME = 259,
     REGEXP = 260,
     FILENAME = 261,
     YNUMBER = 262,
     YSTRING = 263,
     RELOP = 264,
     IO_OUT = 265,
     IO_IN = 266,
     ASSIGNOP = 267,
     ASSIGN = 268,
     MATCHOP = 269,
     CONCAT_OP = 270,
     SUBSCRIPT = 271,
     LEX_BEGIN = 272,
     LEX_END = 273,
     LEX_IF = 274,
     LEX_ELSE = 275,
     LEX_RETURN = 276,
     LEX_DELETE = 277,
     LEX_SWITCH = 278,
     LEX_CASE = 279,
     LEX_DEFAULT = 280,
     LEX_WHILE = 281,
     LEX_DO = 282,
     LEX_FOR = 283,
     LEX_BREAK = 284,
     LEX_CONTINUE = 285,
     LEX_PRINT = 286,
     LEX_PRINTF = 287,
     LEX_NEXT = 288,
     LEX_EXIT = 289,
     LEX_FUNCTION = 290,
     LEX_BEGINFILE = 291,
     LEX_ENDFILE = 292,
     LEX_GETLINE = 293,
     LEX_NEXTFILE = 294,
     LEX_IN = 295,
     LEX_AND = 296,
     LEX_OR = 297,
     INCREMENT = 298,
     DECREMENT = 299,
     LEX_BUILTIN = 300,
     LEX_LENGTH = 301,
     LEX_EOF = 302,
     LEX_INCLUDE = 303,
     LEX_EVAL = 304,
     LEX_LOAD = 305,
     NEWLINE = 306,
     SLASH_BEFORE_EQUAL = 307,
     UNARY = 308
   };
#endif
/* Tokens.  */
#define FUNC_CALL 258
#define NAME 259
#define REGEXP 260
#define FILENAME 261
#define YNUMBER 262
#define YSTRING 263
#define RELOP 264
#define IO_OUT 265
#define IO_IN 266
#define ASSIGNOP 267
#define ASSIGN 268
#define MATCHOP 269
#define CONCAT_OP 270
#define SUBSCRIPT 271
#define LEX_BEGIN 272
#define LEX_END 273
#define LEX_IF 274
#define LEX_ELSE 275
#define LEX_RETURN 276
#define LEX_DELETE 277
#define LEX_SWITCH 278
#define LEX_CASE 279
#define LEX_DEFAULT 280
#define LEX_WHILE 281
#define LEX_DO 282
#define LEX_FOR 283
#define LEX_BREAK 284
#define LEX_CONTINUE 285
#define LEX_PRINT 286
#define LEX_PRINTF 287
#define LEX_NEXT 288
#define LEX_EXIT 289
#define LEX_FUNCTION 290
#define LEX_BEGINFILE 291
#define LEX_ENDFILE 292
#define LEX_GETLINE 293
#define LEX_NEXTFILE 294
#define LEX_IN 295
#define LEX_AND 296
#define LEX_OR 297
#define INCREMENT 298
#define DECREMENT 299
#define LEX_BUILTIN 300
#define LEX_LENGTH 301
#define LEX_EOF 302
#define LEX_INCLUDE 303
#define LEX_EVAL 304
#define LEX_LOAD 305
#define NEWLINE 306
#define SLASH_BEFORE_EQUAL 307
#define UNARY 308



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 372 "awkgram.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1155

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  188
/* YYNRULES -- Number of states.  */
#define YYNSTATES  335

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    63,     2,     2,    66,    62,     2,     2,
      67,    68,    60,    58,    55,    59,     2,    61,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    54,    74,
      56,     2,    57,    53,    69,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    70,     2,    71,    65,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    72,     2,    73,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    64
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    16,    19,    22,
      25,    30,    35,    37,    40,    42,    44,    47,    49,    50,
      52,    57,    59,    61,    63,    65,    71,    73,    75,    77,
      80,    82,    84,    91,    92,    96,    98,   100,   101,   104,
     107,   109,   112,   115,   119,   121,   131,   138,   147,   156,
     169,   181,   183,   186,   189,   192,   195,   199,   200,   205,
     208,   209,   214,   215,   220,   225,   227,   228,   230,   231,
     234,   237,   243,   248,   250,   253,   256,   258,   260,   262,
     264,   266,   270,   271,   272,   276,   283,   293,   295,   298,
     299,   301,   302,   305,   306,   308,   310,   314,   316,   319,
     323,   324,   326,   327,   329,   331,   335,   337,   340,   344,
     348,   352,   356,   360,   364,   368,   372,   378,   380,   382,
     384,   387,   389,   391,   393,   395,   397,   399,   402,   404,
     408,   412,   416,   420,   424,   428,   432,   435,   438,   444,
     449,   453,   457,   461,   465,   469,   473,   475,   478,   482,
     487,   492,   494,   496,   498,   501,   504,   506,   508,   511,
     514,   516,   519,   524,   525,   527,   528,   531,   533,   536,
     538,   542,   544,   547,   550,   552,   555,   557,   561,   563,
     565,   566,   569,   572,   574,   575,   577,   579,   581
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      76,     0,    -1,    -1,    76,    77,    -1,    76,   105,    -1,
      76,    47,    -1,    76,     1,    -1,    80,    81,    -1,    80,
      89,    -1,    84,    81,    -1,    69,    48,    78,    89,    -1,
      69,    50,    79,    89,    -1,     6,    -1,     6,     1,    -1,
       1,    -1,     6,    -1,     6,     1,    -1,     1,    -1,    -1,
     113,    -1,   113,    55,   106,   113,    -1,    17,    -1,    18,
      -1,    36,    -1,    37,    -1,   133,    88,   134,   136,   106,
      -1,     4,    -1,     3,    -1,    83,    -1,    69,    49,    -1,
      45,    -1,    46,    -1,    35,    82,    67,   108,   135,   106,
      -1,    -1,    87,    86,     5,    -1,    61,    -1,    52,    -1,
      -1,    88,    90,    -1,    88,     1,    -1,   105,    -1,   137,
     106,    -1,   137,   106,    -1,   133,    88,   134,    -1,   104,
      -1,    23,    67,   113,   135,   106,   133,    97,   106,   134,
      -1,    26,    67,   113,   135,   106,    90,    -1,    27,   106,
      90,    26,    67,   113,   135,   106,    -1,    28,    67,     4,
      40,   130,   135,   106,    90,    -1,    28,    67,    96,   137,
     106,   113,   137,   106,    96,   135,   106,    90,    -1,    28,
      67,    96,   137,   106,   137,   106,    96,   135,   106,    90,
      -1,    91,    -1,    29,    89,    -1,    30,    89,    -1,    33,
      89,    -1,    39,    89,    -1,    34,   110,    89,    -1,    -1,
      21,    92,   110,    89,    -1,    93,    89,    -1,    -1,   100,
      94,   101,   102,    -1,    -1,    22,     4,    95,   124,    -1,
      22,    67,     4,    68,    -1,   113,    -1,    -1,    93,    -1,
      -1,    97,    98,    -1,    97,     1,    -1,    24,    99,   138,
     106,    88,    -1,    25,   138,   106,    88,    -1,     7,    -1,
      59,     7,    -1,    58,     7,    -1,     8,    -1,    85,    -1,
      31,    -1,    32,    -1,   111,    -1,    67,   112,   135,    -1,
      -1,    -1,    10,   103,   117,    -1,    19,    67,   113,   135,
     106,    90,    -1,    19,    67,   113,   135,   106,    90,    20,
     106,    90,    -1,    51,    -1,   105,    51,    -1,    -1,   105,
      -1,    -1,    56,   118,    -1,    -1,   109,    -1,     4,    -1,
     109,   139,     4,    -1,     1,    -1,   109,     1,    -1,   109,
     139,     1,    -1,    -1,   113,    -1,    -1,   112,    -1,   113,
      -1,   112,   139,   113,    -1,     1,    -1,   112,     1,    -1,
     112,     1,   113,    -1,   112,   139,     1,    -1,   131,   114,
     113,    -1,   113,    41,   113,    -1,   113,    42,   113,    -1,
     113,    14,   113,    -1,   113,    40,   130,    -1,   113,   116,
     113,    -1,   113,    53,   113,    54,   113,    -1,   117,    -1,
      13,    -1,    12,    -1,    52,    13,    -1,     9,    -1,    56,
      -1,   115,    -1,    57,    -1,   118,    -1,   119,    -1,   117,
     118,    -1,   120,    -1,   118,    65,   118,    -1,   118,    60,
     118,    -1,   118,    61,   118,    -1,   118,    62,   118,    -1,
     118,    58,   118,    -1,   118,    59,   118,    -1,    38,   123,
     107,    -1,   131,    43,    -1,   131,    44,    -1,    67,   112,
     135,    40,   130,    -1,   117,    11,    38,   123,    -1,   119,
      65,   118,    -1,   119,    60,   118,    -1,   119,    61,   118,
      -1,   119,    62,   118,    -1,   119,    58,   118,    -1,   119,
      59,   118,    -1,    85,    -1,    63,   118,    -1,    67,   113,
     135,    -1,    45,    67,   111,   135,    -1,    46,    67,   111,
     135,    -1,    46,    -1,   121,    -1,   131,    -1,    43,   131,
      -1,    44,   131,    -1,     7,    -1,     8,    -1,    59,   118,
      -1,    58,   118,    -1,   122,    -1,    69,   122,    -1,     3,
      67,   111,   135,    -1,    -1,   131,    -1,    -1,   125,    16,
      -1,   126,    -1,   125,   126,    -1,   127,    -1,    70,   112,
      71,    -1,   127,    -1,   128,   127,    -1,   128,    16,    -1,
       4,    -1,     4,   129,    -1,   130,    -1,    66,   120,   132,
      -1,    43,    -1,    44,    -1,    -1,    72,   106,    -1,    73,
     106,    -1,    68,    -1,    -1,   137,    -1,    74,    -1,    54,
      -1,    55,   106,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   200,   200,   202,   207,   208,   214,   226,   230,   241,
     247,   252,   260,   268,   270,   275,   283,   285,   291,   292,
     294,   320,   331,   342,   348,   357,   367,   369,   371,   377,
     382,   383,   387,   406,   405,   439,   441,   446,   447,   460,
     465,   466,   470,   472,   474,   481,   571,   613,   655,   768,
     775,   782,   792,   801,   810,   819,   830,   846,   845,   869,
     881,   881,   979,   979,  1012,  1042,  1048,  1049,  1055,  1056,
    1063,  1068,  1080,  1094,  1096,  1104,  1109,  1111,  1119,  1121,
    1130,  1131,  1139,  1144,  1144,  1155,  1159,  1167,  1168,  1171,
    1173,  1178,  1179,  1188,  1189,  1194,  1199,  1205,  1207,  1209,
    1216,  1217,  1223,  1224,  1229,  1231,  1236,  1238,  1246,  1251,
    1260,  1267,  1269,  1271,  1287,  1297,  1304,  1306,  1311,  1313,
    1315,  1323,  1325,  1330,  1332,  1337,  1339,  1341,  1391,  1393,
    1395,  1397,  1399,  1401,  1403,  1405,  1428,  1433,  1438,  1463,
    1469,  1471,  1473,  1475,  1477,  1479,  1484,  1488,  1520,  1522,
    1528,  1534,  1547,  1548,  1549,  1554,  1559,  1563,  1567,  1582,
    1595,  1600,  1636,  1654,  1655,  1661,  1662,  1667,  1669,  1676,
    1693,  1710,  1712,  1719,  1724,  1732,  1742,  1754,  1763,  1767,
    1771,  1775,  1779,  1783,  1786,  1788,  1792,  1796,  1800
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FUNC_CALL", "NAME", "REGEXP",
  "FILENAME", "YNUMBER", "YSTRING", "RELOP", "IO_OUT", "IO_IN", "ASSIGNOP",
  "ASSIGN", "MATCHOP", "CONCAT_OP", "SUBSCRIPT", "LEX_BEGIN", "LEX_END",
  "LEX_IF", "LEX_ELSE", "LEX_RETURN", "LEX_DELETE", "LEX_SWITCH",
  "LEX_CASE", "LEX_DEFAULT", "LEX_WHILE", "LEX_DO", "LEX_FOR", "LEX_BREAK",
  "LEX_CONTINUE", "LEX_PRINT", "LEX_PRINTF", "LEX_NEXT", "LEX_EXIT",
  "LEX_FUNCTION", "LEX_BEGINFILE", "LEX_ENDFILE", "LEX_GETLINE",
  "LEX_NEXTFILE", "LEX_IN", "LEX_AND", "LEX_OR", "INCREMENT", "DECREMENT",
  "LEX_BUILTIN", "LEX_LENGTH", "LEX_EOF", "LEX_INCLUDE", "LEX_EVAL",
  "LEX_LOAD", "NEWLINE", "SLASH_BEFORE_EQUAL", "'?'", "':'", "','", "'<'",
  "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "UNARY", "'^'", "'$'",
  "'('", "')'", "'@'", "'['", "']'", "'{'", "'}'", "';'", "$accept",
  "program", "rule", "source", "library", "pattern", "action", "func_name",
  "lex_builtin", "function_prologue", "regexp", "$@1", "a_slash",
  "statements", "statement_term", "statement", "non_compound_stmt", "$@2",
  "simple_stmt", "$@3", "$@4", "opt_simple_stmt", "case_statements",
  "case_statement", "case_value", "print", "print_expression_list",
  "output_redir", "$@5", "if_statement", "nls", "opt_nls", "input_redir",
  "opt_param_list", "param_list", "opt_exp", "opt_expression_list",
  "expression_list", "exp", "assign_operator", "relop_or_less", "a_relop",
  "common_exp", "simp_exp", "simp_exp_nc", "non_post_simp_exp",
  "func_call", "direct_func_call", "opt_variable", "delete_subscript_list",
  "delete_subscript", "delete_exp_list", "bracketed_exp_list", "subscript",
  "subscript_list", "simple_variable", "variable", "opt_incdec", "l_brace",
  "r_brace", "r_paren", "opt_semi", "semi", "colon", "comma", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,    63,    58,    44,    60,    62,    43,    45,
      42,    47,    37,    33,   308,    94,    36,    40,    41,    64,
      91,    93,   123,   125,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    75,    76,    76,    76,    76,    76,    77,    77,    77,
      77,    77,    78,    78,    78,    79,    79,    79,    80,    80,
      80,    80,    80,    80,    80,    81,    82,    82,    82,    82,
      83,    83,    84,    86,    85,    87,    87,    88,    88,    88,
      89,    89,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    91,    91,    91,    91,    91,    92,    91,    91,
      94,    93,    95,    93,    93,    93,    96,    96,    97,    97,
      97,    98,    98,    99,    99,    99,    99,    99,   100,   100,
     101,   101,   102,   103,   102,   104,   104,   105,   105,   106,
     106,   107,   107,   108,   108,   109,   109,   109,   109,   109,
     110,   110,   111,   111,   112,   112,   112,   112,   112,   112,
     113,   113,   113,   113,   113,   113,   113,   113,   114,   114,
     114,   115,   115,   116,   116,   117,   117,   117,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   119,
     119,   119,   119,   119,   119,   119,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     121,   121,   122,   123,   123,   124,   124,   125,   125,   126,
     127,   128,   128,   129,   130,   130,   131,   131,   132,   132,
     132,   133,   134,   135,   136,   136,   137,   138,   139
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     2,     2,
       4,     4,     1,     2,     1,     1,     2,     1,     0,     1,
       4,     1,     1,     1,     1,     5,     1,     1,     1,     2,
       1,     1,     6,     0,     3,     1,     1,     0,     2,     2,
       1,     2,     2,     3,     1,     9,     6,     8,     8,    12,
      11,     1,     2,     2,     2,     2,     3,     0,     4,     2,
       0,     4,     0,     4,     4,     1,     0,     1,     0,     2,
       2,     5,     4,     1,     2,     2,     1,     1,     1,     1,
       1,     3,     0,     0,     3,     6,     9,     1,     2,     0,
       1,     0,     2,     0,     1,     1,     3,     1,     2,     3,
       0,     1,     0,     1,     1,     3,     1,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     5,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     2,     1,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     5,     4,
       3,     3,     3,     3,     3,     3,     1,     2,     3,     4,
       4,     1,     1,     1,     2,     2,     1,     1,     2,     2,
       1,     2,     4,     0,     1,     0,     2,     1,     2,     1,
       3,     1,     2,     2,     1,     2,     1,     3,     1,     1,
       0,     2,     2,     1,     0,     1,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     6,     0,   174,   156,   157,    21,    22,
       0,    23,    24,   163,     0,     0,     0,   151,     5,    87,
      36,     0,     0,    35,     0,     0,     0,     0,     3,     0,
       0,   146,    33,     4,    19,   117,   125,   126,   128,   152,
     160,   176,   153,     0,     0,   171,     0,   175,    27,    26,
      30,    31,     0,     0,    28,    91,   164,   154,   155,     0,
       0,     0,   159,   153,   158,   147,     0,   180,   153,   106,
       0,   104,     0,     0,   161,    89,   186,     7,     8,    40,
      37,    89,     9,     0,    88,   121,     0,     0,     0,     0,
       0,    89,   122,   124,   123,     0,     0,   127,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     119,   118,   136,   137,     0,     0,     0,     0,   104,     0,
     173,   172,    29,     0,     0,   135,     0,     0,     0,   178,
     179,   177,   107,    89,   183,     0,     0,   148,    14,     0,
       0,    17,     0,     0,    90,   181,     0,    41,    34,   113,
     114,   111,   112,     0,     0,   115,   163,   133,   134,   130,
     131,   132,   129,   144,   145,   141,   142,   143,   140,   120,
     110,   162,   170,    97,    95,     0,     0,    92,   149,   150,
     108,   188,     0,   109,   105,    13,    10,    16,    11,    39,
       0,    57,     0,     0,     0,    89,     0,     0,     0,    78,
      79,     0,   100,     0,    89,    38,    51,     0,    60,    44,
      65,    37,   184,    89,     0,    20,   139,    89,    98,     0,
     138,     0,   100,    62,     0,     0,     0,     0,    66,    52,
      53,    54,     0,   101,    55,   182,    59,     0,     0,    89,
     185,    42,   116,    32,    99,    96,     0,     0,   165,     0,
       0,     0,     0,   174,    67,     0,    56,     0,    82,    80,
      43,    25,    89,    58,    63,     0,   167,   169,    64,    89,
      89,     0,     0,    89,     0,    83,    61,     0,   166,   168,
       0,     0,     0,     0,     0,    81,     0,    85,    68,    46,
       0,    89,     0,    89,    84,    89,     0,    89,     0,    89,
      66,     0,    70,     0,     0,    69,     0,    47,    48,    66,
       0,    86,    73,    76,     0,     0,    77,     0,   187,    89,
      45,     0,    89,    75,    74,    89,    37,    89,     0,    37,
       0,     0,    50,     0,    49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    28,   140,   143,    29,    77,    53,    54,    30,
      31,    83,    32,   146,    78,   205,   206,   222,   207,   237,
     248,   255,   296,   305,   317,   208,   258,   276,   286,   209,
     144,   145,   125,   175,   176,   232,   116,   117,   210,   115,
      94,    95,    35,    36,    37,    38,    39,    40,    55,   264,
     265,   266,    45,    46,    47,    41,    42,   131,   211,   212,
     137,   239,   213,   319,   136
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -273
static const yytype_int16 yypact[] =
{
    -273,   376,  -273,  -273,   -27,   -21,  -273,  -273,  -273,  -273,
     157,  -273,  -273,    11,    11,    11,    -5,    -3,  -273,  -273,
    -273,  1019,  1019,  -273,  1019,  1065,   821,   116,  -273,   -20,
       1,  -273,  -273,    35,   758,   992,   252,   296,  -273,  -273,
    -273,  -273,   233,   789,   821,  -273,     2,  -273,  -273,  -273,
    -273,  -273,    63,    54,  -273,    69,  -273,  -273,  -273,   789,
     789,   127,    87,   115,    87,    87,  1019,   131,  -273,  -273,
      55,   295,    40,    47,  -273,    83,  -273,  -273,  -273,    35,
    -273,    83,  -273,   151,  -273,  -273,  1019,   132,  1019,  1019,
    1019,    83,  -273,  -273,  -273,  1019,   124,   252,  1019,  1019,
    1019,  1019,  1019,  1019,  1019,  1019,  1019,  1019,  1019,  1019,
    -273,  -273,  -273,  -273,   152,  1019,   100,    16,  1034,    37,
    -273,  -273,  -273,    43,  1019,  -273,   100,   100,   295,  -273,
    -273,  -273,  1019,    83,  -273,   137,   867,  -273,  -273,    75,
     -19,  -273,    77,   -19,    35,  -273,   596,  -273,  -273,   123,
    -273,   141,   175,  1098,  1019,   161,    11,   -26,   -26,    87,
      87,    87,    87,   -26,   -26,    87,    87,    87,    87,  -273,
    1034,  -273,  -273,  -273,  -273,   100,    65,   252,  -273,  -273,
    1034,  -273,   132,  -273,  1034,  -273,  -273,  -273,  -273,  -273,
     104,  -273,    26,   118,   119,    83,   121,   -19,   -19,  -273,
    -273,   -19,  1019,   -19,    83,  -273,  -273,   -19,  -273,  -273,
    1034,  -273,   117,    83,  1019,  1034,  -273,    83,  -273,   112,
    -273,  1019,  1019,  -273,   188,  1019,  1019,   710,   900,  -273,
    -273,  -273,   -19,  1034,  -273,  -273,  -273,   642,   596,    83,
    -273,  -273,  1034,  -273,  -273,  -273,   295,   -19,   -21,   126,
     295,   295,   169,   -13,  -273,   117,  -273,   821,   186,  -273,
    -273,  -273,    83,  -273,  -273,    13,  -273,  -273,  -273,    83,
      83,   139,   132,    83,    55,  -273,  -273,   710,  -273,  -273,
       1,   710,  1019,   100,   743,   137,  1019,   192,  -273,  -273,
     295,    83,   286,    83,   992,    83,    44,    83,   710,    83,
     946,   710,  -273,   247,   154,  -273,   156,  -273,  -273,   946,
     100,  -273,  -273,  -273,   226,   228,  -273,   154,  -273,    83,
    -273,   100,    83,  -273,  -273,    83,  -273,    83,   710,  -273,
     448,   710,  -273,   522,  -273
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -273,  -273,  -273,  -273,  -273,  -273,   208,  -273,  -273,  -273,
     -64,  -273,  -273,  -202,    71,   -58,  -273,  -273,  -218,  -273,
    -273,  -272,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
      50,    76,  -273,  -273,  -273,    19,   -54,   -23,    -1,  -273,
    -273,  -273,   -44,    39,  -273,   224,  -273,   -11,    94,  -273,
    -273,    -7,   -38,  -273,  -273,   -73,    -2,  -273,   -28,  -231,
     -46,  -273,   -25,   -57,    85
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -104
static const yytype_int16 yytable[] =
{
      34,    80,    80,    70,    81,   126,   127,   260,   121,   238,
     254,    56,    57,    58,   150,     5,    74,   132,   120,    63,
      63,   119,    63,    68,   135,    71,  -103,   272,   310,   278,
     223,    19,    19,    63,   100,   101,   102,   321,   132,   103,
      43,   138,   118,   118,   173,   302,   139,   174,   141,    44,
      74,    33,    75,   142,    76,    76,   132,    44,   118,   118,
      62,    64,    59,    65,    60,   128,   218,  -103,   303,   304,
     171,   133,    44,    75,    97,   320,   185,    25,   187,    79,
     178,   179,   254,    44,  -103,   149,    84,   151,   152,   153,
    -103,   254,   133,   224,   155,    19,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,   172,   220,
     133,   -93,   122,   244,   170,    81,   245,   -89,    81,     4,
     133,   123,    63,   134,   330,   124,   -12,   333,   -15,   217,
       4,   180,    85,   -94,    19,   184,     5,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   -12,
      85,   -15,   103,   215,    56,    86,   148,   147,   112,   113,
      48,    49,   156,   177,    72,   169,    73,   154,   134,   252,
    -104,   221,    81,    81,   129,   130,    81,   182,    81,    92,
      93,    87,    81,   259,    85,   225,   226,   240,   228,    86,
      79,    76,   249,    79,   268,   271,   275,    92,    93,   283,
     262,   233,    50,    51,   269,   270,   282,    81,   318,   181,
     267,   186,   295,   242,   188,    87,    88,  -104,  -104,   287,
     246,   233,    81,   289,   250,   251,    52,   267,   285,   204,
     273,    92,    93,   323,   274,   324,   118,   291,    82,   316,
     308,   247,   294,   311,   297,   110,   111,    79,    79,    67,
     216,    79,   288,    79,   312,   313,    71,    79,   279,   293,
     325,   219,     0,     0,   322,     0,     0,   299,   229,   230,
     332,   227,   231,   334,   234,   327,   112,   113,   236,     0,
     235,   290,    79,   292,    63,   114,     0,     0,     0,   241,
       0,     0,    63,   243,     0,    85,     0,    79,     0,    20,
      86,     0,     0,   256,    85,   314,   315,     0,    23,    86,
      98,    99,   100,   101,   102,   261,     0,   103,   263,     0,
       0,     0,     0,     0,     0,     0,    87,    88,    89,     0,
       0,     0,     0,    97,     0,    87,    88,    89,   277,    90,
       0,     0,    92,    93,     0,   280,   281,     0,    90,   284,
       0,    92,    93,     0,   104,   105,   106,   107,   108,     0,
      76,   109,     0,   134,     0,     0,     0,   298,     0,   300,
       0,   301,   306,   307,     0,   309,     2,     3,     0,     4,
       5,     0,     0,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     8,     9,   326,     0,     0,   328,     0,
       0,   329,     0,   331,     0,     0,     0,     0,     0,     0,
       0,    10,    11,    12,    13,     0,     0,     0,     0,    14,
      15,    16,    17,    18,     0,     0,     0,    19,    20,     0,
       0,     0,     0,     0,    21,    22,     0,    23,     0,    24,
       0,     0,    25,    26,     0,    27,     0,     0,   -18,   189,
     -18,     4,     5,     0,     0,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   190,     0,   191,
     192,   193,   -72,   -72,   194,   195,   196,   197,   198,   199,
     200,   201,   202,     0,     0,     0,    13,   203,     0,     0,
       0,    14,    15,    16,    17,     0,     0,     0,     0,   -72,
      20,     0,     0,     0,     0,     0,    21,    22,     0,    23,
       0,    24,     0,     0,    25,    26,     0,    61,     0,     0,
      75,   -72,    76,   189,     0,     4,     5,     0,     0,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   190,     0,   191,   192,   193,   -71,   -71,   194,   195,
     196,   197,   198,   199,   200,   201,   202,     0,     0,     0,
      13,   203,     0,     0,     0,    14,    15,    16,    17,     0,
       0,     0,     0,   -71,    20,     0,     0,     0,     0,     0,
      21,    22,     0,    23,     0,    24,     0,     0,    25,    26,
       0,    61,     0,     0,    75,   -71,    76,   189,     0,     4,
       5,     0,     0,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   190,     0,   191,   192,   193,
       0,     0,   194,   195,   196,   197,   198,   199,   200,   201,
     202,     0,     0,     0,    13,   203,     0,     0,     0,    14,
      15,    16,    17,    69,     0,     4,     5,     0,    20,     6,
       7,     0,  -102,     0,    21,    22,     0,    23,     0,    24,
       0,     0,    25,    26,     0,    61,     0,     0,    75,   204,
      76,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      13,     0,     0,     0,     0,    14,    15,    16,    17,     0,
       0,     0,     0,  -102,    20,     0,     0,     0,     0,     0,
      21,    22,     0,    23,     0,    24,     0,     0,    25,   257,
    -102,    61,     0,     4,     5,     0,  -102,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   190,
       0,   191,   192,   193,     0,     0,   194,   195,   196,   197,
     198,   199,   200,   201,   202,     0,     4,     5,    13,   203,
       6,     7,     0,    14,    15,    16,    17,     0,     0,     0,
       0,     0,    20,     0,     0,     0,     0,    85,    21,    22,
       0,    23,    86,    24,     0,     0,    25,    26,     0,    61,
       0,    13,    75,     0,    76,     0,    14,    15,    16,    17,
      69,     0,     4,     5,     0,    20,     6,     7,    87,    88,
      89,    21,    22,     0,    23,     0,    24,     0,     0,    25,
      26,    90,    61,    91,    92,    93,     0,    76,     0,     0,
       0,     0,    69,     0,     4,     5,     0,    13,     6,     7,
       0,     0,    14,    15,    16,    17,     0,     0,     0,     0,
       0,    20,     0,     0,     0,     0,     0,    21,    22,     0,
      23,     0,    24,     0,     0,    25,    26,  -102,    61,    13,
       0,     0,     0,     0,    14,    15,    16,    17,   183,     0,
       4,     5,     0,    20,     6,     7,     0,     0,     0,    21,
      22,     0,    23,     0,    24,     0,     0,    25,    26,     0,
      61,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     4,   253,    13,     0,     6,     7,     0,
      14,    15,    16,    17,     0,     0,     0,     0,     0,    20,
       0,     0,   192,     0,     0,    21,    22,     0,    23,     0,
      24,   199,   200,    25,    26,     0,    61,     0,    13,     0,
       0,     0,     0,    14,    15,    16,    17,     0,     0,     4,
       5,     0,    20,     6,     7,     0,     0,     0,    21,    22,
       0,    23,     0,    24,     0,     0,    25,    26,   192,    61,
       0,     0,     0,     0,     0,     0,     0,   199,   200,     0,
       0,     0,     0,     0,    13,     0,     0,     0,     0,    14,
      15,    16,    17,     0,     0,     4,     5,     0,    20,     6,
       7,     0,     0,    96,    21,    22,     0,    23,     0,    24,
       0,     0,    25,    26,     0,    61,     0,     0,     0,     0,
       0,     0,     4,     5,     0,     0,     6,     7,     0,     0,
      13,     0,     0,     0,     0,    14,    15,    16,    17,     0,
       0,     0,     0,    85,    20,     0,     0,     0,    86,     0,
      21,    22,     0,    23,     0,    24,     0,    13,    25,    26,
       0,    61,    14,    15,    16,    17,     0,     0,     4,     5,
       0,    20,     6,     7,    87,    88,    89,    21,    22,     0,
      23,     0,    24,     0,     0,    25,    26,    90,    61,     0,
      92,    93,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    85,    14,    15,
      16,    17,    86,     0,     0,     0,     0,    20,     0,     0,
       0,     0,     0,    21,    22,     0,    23,     0,    24,     0,
       0,    25,    66,     0,    61,     0,     0,     0,    87,    88,
      89,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    90,   214,     0,    92,    93
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-273)))

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-104)))

static const yytype_int16 yycheck[] =
{
       1,    29,    30,    26,    29,    59,    60,   238,    46,   211,
     228,    13,    14,    15,    87,     4,    27,     1,    16,    21,
      22,    44,    24,    25,    70,    26,    10,    40,   300,    16,
       4,    51,    51,    35,    60,    61,    62,   309,     1,    65,
      67,     1,    43,    44,     1,     1,     6,     4,     1,    70,
      61,     1,    72,     6,    74,    74,     1,    70,    59,    60,
      21,    22,    67,    24,    67,    66,     1,    51,    24,    25,
     116,    55,    70,    72,    35,   306,     1,    66,     1,    29,
     126,   127,   300,    70,    68,    86,    51,    88,    89,    90,
      74,   309,    55,    67,    95,    51,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,    71,   182,
      55,    68,    49,     1,   115,   140,     4,    73,   143,     3,
      55,    67,   124,    68,   326,    56,    51,   329,    51,   175,
       3,   132,     9,    68,    51,   136,     4,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,    74,
       9,    74,    65,   154,   156,    14,     5,    81,    43,    44,
       3,     4,    38,   124,    48,    13,    50,    91,    68,   227,
       9,    67,   197,   198,    43,    44,   201,    40,   203,    56,
      57,    40,   207,   237,     9,    67,    67,   212,    67,    14,
     140,    74,     4,   143,    68,    26,    10,    56,    57,   272,
     246,   202,    45,    46,   250,   251,    67,   232,    54,   133,
     248,   140,    20,   214,   143,    40,    41,    56,    57,   277,
     221,   222,   247,   281,   225,   226,    69,   265,   274,    73,
     255,    56,    57,     7,   257,     7,   237,   283,    30,   303,
     298,   222,   286,   301,   290,    12,    13,   197,   198,    25,
     156,   201,   280,   203,     7,     8,   257,   207,   265,   284,
     317,   176,    -1,    -1,   310,    -1,    -1,   292,   197,   198,
     328,   195,   201,   331,   203,   321,    43,    44,   207,    -1,
     204,   282,   232,   284,   286,    52,    -1,    -1,    -1,   213,
      -1,    -1,   294,   217,    -1,     9,    -1,   247,    -1,    52,
      14,    -1,    -1,   232,     9,    58,    59,    -1,    61,    14,
      58,    59,    60,    61,    62,   239,    -1,    65,   247,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,
      -1,    -1,    -1,   294,    -1,    40,    41,    42,   262,    53,
      -1,    -1,    56,    57,    -1,   269,   270,    -1,    53,   273,
      -1,    56,    57,    -1,    58,    59,    60,    61,    62,    -1,
      74,    65,    -1,    68,    -1,    -1,    -1,   291,    -1,   293,
      -1,   295,   296,   297,    -1,   299,     0,     1,    -1,     3,
       4,    -1,    -1,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    17,    18,   319,    -1,    -1,   322,    -1,
      -1,   325,    -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    -1,    -1,    -1,    51,    52,    -1,
      -1,    -1,    -1,    -1,    58,    59,    -1,    61,    -1,    63,
      -1,    -1,    66,    67,    -1,    69,    -1,    -1,    72,     1,
      74,     3,     4,    -1,    -1,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    38,    39,    -1,    -1,
      -1,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    51,
      52,    -1,    -1,    -1,    -1,    -1,    58,    59,    -1,    61,
      -1,    63,    -1,    -1,    66,    67,    -1,    69,    -1,    -1,
      72,    73,    74,     1,    -1,     3,     4,    -1,    -1,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    19,    -1,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      38,    39,    -1,    -1,    -1,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,
      58,    59,    -1,    61,    -1,    63,    -1,    -1,    66,    67,
      -1,    69,    -1,    -1,    72,    73,    74,     1,    -1,     3,
       4,    -1,    -1,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    -1,    21,    22,    23,
      -1,    -1,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    38,    39,    -1,    -1,    -1,    43,
      44,    45,    46,     1,    -1,     3,     4,    -1,    52,     7,
       8,    -1,    10,    -1,    58,    59,    -1,    61,    -1,    63,
      -1,    -1,    66,    67,    -1,    69,    -1,    -1,    72,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    -1,    -1,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,
      58,    59,    -1,    61,    -1,    63,    -1,    -1,    66,    67,
      68,    69,    -1,     3,     4,    -1,    74,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      -1,    21,    22,    23,    -1,    -1,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,     3,     4,    38,    39,
       7,     8,    -1,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    -1,     9,    58,    59,
      -1,    61,    14,    63,    -1,    -1,    66,    67,    -1,    69,
      -1,    38,    72,    -1,    74,    -1,    43,    44,    45,    46,
       1,    -1,     3,     4,    -1,    52,     7,     8,    40,    41,
      42,    58,    59,    -1,    61,    -1,    63,    -1,    -1,    66,
      67,    53,    69,    55,    56,    57,    -1,    74,    -1,    -1,
      -1,    -1,     1,    -1,     3,     4,    -1,    38,     7,     8,
      -1,    -1,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    58,    59,    -1,
      61,    -1,    63,    -1,    -1,    66,    67,    68,    69,    38,
      -1,    -1,    -1,    -1,    43,    44,    45,    46,     1,    -1,
       3,     4,    -1,    52,     7,     8,    -1,    -1,    -1,    58,
      59,    -1,    61,    -1,    63,    -1,    -1,    66,    67,    -1,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,    38,    -1,     7,     8,    -1,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    22,    -1,    -1,    58,    59,    -1,    61,    -1,
      63,    31,    32,    66,    67,    -1,    69,    -1,    38,    -1,
      -1,    -1,    -1,    43,    44,    45,    46,    -1,    -1,     3,
       4,    -1,    52,     7,     8,    -1,    -1,    -1,    58,    59,
      -1,    61,    -1,    63,    -1,    -1,    66,    67,    22,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    -1,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    -1,    -1,     3,     4,    -1,    52,     7,
       8,    -1,    -1,    11,    58,    59,    -1,    61,    -1,    63,
      -1,    -1,    66,    67,    -1,    69,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,    -1,    -1,     7,     8,    -1,    -1,
      38,    -1,    -1,    -1,    -1,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,     9,    52,    -1,    -1,    -1,    14,    -1,
      58,    59,    -1,    61,    -1,    63,    -1,    38,    66,    67,
      -1,    69,    43,    44,    45,    46,    -1,    -1,     3,     4,
      -1,    52,     7,     8,    40,    41,    42,    58,    59,    -1,
      61,    -1,    63,    -1,    -1,    66,    67,    53,    69,    -1,
      56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    43,    44,
      45,    46,    14,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    58,    59,    -1,    61,    -1,    63,    -1,
      -1,    66,    67,    -1,    69,    -1,    -1,    -1,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    -1,    56,    57
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    76,     0,     1,     3,     4,     7,     8,    17,    18,
      35,    36,    37,    38,    43,    44,    45,    46,    47,    51,
      52,    58,    59,    61,    63,    66,    67,    69,    77,    80,
      84,    85,    87,   105,   113,   117,   118,   119,   120,   121,
     122,   130,   131,    67,    70,   127,   128,   129,     3,     4,
      45,    46,    69,    82,    83,   123,   131,   131,   131,    67,
      67,    69,   118,   131,   118,   118,    67,   120,   131,     1,
     112,   113,    48,    50,   122,    72,    74,    81,    89,   105,
     133,   137,    81,    86,    51,     9,    14,    40,    41,    42,
      53,    55,    56,    57,   115,   116,    11,   118,    58,    59,
      60,    61,    62,    65,    58,    59,    60,    61,    62,    65,
      12,    13,    43,    44,    52,   114,   111,   112,   113,   112,
      16,   127,    49,    67,    56,   107,   111,   111,   113,    43,
      44,   132,     1,    55,    68,   135,   139,   135,     1,     6,
      78,     1,     6,    79,   105,   106,    88,   106,     5,   113,
     130,   113,   113,   113,   106,   113,    38,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,    13,
     113,   135,    71,     1,     4,   108,   109,   118,   135,   135,
     113,   106,    40,     1,   113,     1,    89,     1,    89,     1,
      19,    21,    22,    23,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    39,    73,    90,    91,    93,   100,   104,
     113,   133,   134,   137,    54,   113,   123,   135,     1,   139,
     130,    67,    92,     4,    67,    67,    67,   106,    67,    89,
      89,    89,   110,   113,    89,   106,    89,    94,    88,   136,
     137,   106,   113,   106,     1,     4,   113,   110,    95,     4,
     113,   113,    90,     4,    93,    96,    89,    67,   101,   111,
     134,   106,   135,    89,   124,   125,   126,   127,    68,   135,
     135,    26,    40,   137,   112,    10,   102,   106,    16,   126,
     106,   106,    67,   130,   106,   135,   103,    90,   133,    90,
     113,   135,   113,   137,   117,    20,    97,   135,   106,   137,
     106,   106,     1,    24,    25,    98,   106,   106,    90,   106,
      96,    90,     7,     8,    58,    59,    85,    99,    54,   138,
     134,    96,   135,     7,     7,   138,   106,   135,   106,   106,
      88,   106,    90,    88,    90
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
/* Line 1787 of yacc.c  */
#line 203 "awkgram.y"
    {
		rule = 0;
		yyerrok;
	  }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 209 "awkgram.y"
    {
		next_sourcefile();
		if (sourcefile == srcfiles)
			process_deferred();
	  }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 215 "awkgram.y"
    {
		rule = 0;
		/*
		 * If errors, give up, don't produce an infinite
		 * stream of syntax error messages.
		 */
  		/* yyerrok; */
	  }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 227 "awkgram.y"
    {
		(void) append_rule((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
	  }
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 231 "awkgram.y"
    {
		if (rule != Rule) {
			msg(_("%s blocks must have an action part"), ruletab[rule]);
			errcount++;
		} else if ((yyvsp[(1) - (2)]) == NULL) {
			msg(_("each rule must have a pattern or an action part"));
			errcount++;
		} else		/* pattern rule with non-empty pattern */
			(void) append_rule((yyvsp[(1) - (2)]), NULL);
	  }
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 242 "awkgram.y"
    {
		in_function = NULL;
		(void) mk_function((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
		yyerrok;
	  }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 248 "awkgram.y"
    {
		want_source = false;
		yyerrok;
	  }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 253 "awkgram.y"
    {
		want_source = false;
		yyerrok;
	  }
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 261 "awkgram.y"
    {
		if (include_source((yyvsp[(1) - (1)])) < 0)
			YYABORT;
		efree((yyvsp[(1) - (1)])->lextok);
		bcfree((yyvsp[(1) - (1)]));
		(yyval) = NULL;
	  }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 269 "awkgram.y"
    { (yyval) = NULL; }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 271 "awkgram.y"
    { (yyval) = NULL; }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 276 "awkgram.y"
    {
		if (load_library((yyvsp[(1) - (1)])) < 0)
			YYABORT;
		efree((yyvsp[(1) - (1)])->lextok);
		bcfree((yyvsp[(1) - (1)]));
		(yyval) = NULL;
	  }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 284 "awkgram.y"
    { (yyval) = NULL; }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 286 "awkgram.y"
    { (yyval) = NULL; }
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 291 "awkgram.y"
    {	(yyval) = NULL; rule = Rule; }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 293 "awkgram.y"
    {	(yyval) = (yyvsp[(1) - (1)]); rule = Rule; }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 295 "awkgram.y"
    {
		INSTRUCTION *tp;

		add_lint((yyvsp[(1) - (4)]), LINT_assign_in_cond);
		add_lint((yyvsp[(4) - (4)]), LINT_assign_in_cond);

		tp = instruction(Op_no_op);
		list_prepend((yyvsp[(1) - (4)]), bcalloc(Op_line_range, !!do_pretty_print + 1, 0));
		(yyvsp[(1) - (4)])->nexti->triggered = false;
		(yyvsp[(1) - (4)])->nexti->target_jmp = (yyvsp[(4) - (4)])->nexti;

		list_append((yyvsp[(1) - (4)]), instruction(Op_cond_pair));
		(yyvsp[(1) - (4)])->lasti->line_range = (yyvsp[(1) - (4)])->nexti;
		(yyvsp[(1) - (4)])->lasti->target_jmp = tp;

		list_append((yyvsp[(4) - (4)]), instruction(Op_cond_pair));
		(yyvsp[(4) - (4)])->lasti->line_range = (yyvsp[(1) - (4)])->nexti;
		(yyvsp[(4) - (4)])->lasti->target_jmp = tp;
		if (do_pretty_print) {
			((yyvsp[(1) - (4)])->nexti + 1)->condpair_left = (yyvsp[(1) - (4)])->lasti;
			((yyvsp[(1) - (4)])->nexti + 1)->condpair_right = (yyvsp[(4) - (4)])->lasti;
		}
		(yyval) = list_append(list_merge((yyvsp[(1) - (4)]), (yyvsp[(4) - (4)])), tp);
		rule = Rule;
	  }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 321 "awkgram.y"
    {
		static int begin_seen = 0;
		if (do_lint_old && ++begin_seen == 2)
			warning_ln((yyvsp[(1) - (1)])->source_line,
				_("old awk does not support multiple `BEGIN' or `END' rules"));

		(yyvsp[(1) - (1)])->in_rule = rule = BEGIN;
		(yyvsp[(1) - (1)])->source_file = source;
		(yyval) = (yyvsp[(1) - (1)]);
	  }
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 332 "awkgram.y"
    {
		static int end_seen = 0;
		if (do_lint_old && ++end_seen == 2)
			warning_ln((yyvsp[(1) - (1)])->source_line,
				_("old awk does not support multiple `BEGIN' or `END' rules"));

		(yyvsp[(1) - (1)])->in_rule = rule = END;
		(yyvsp[(1) - (1)])->source_file = source;
		(yyval) = (yyvsp[(1) - (1)]);
	  }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 343 "awkgram.y"
    {
		(yyvsp[(1) - (1)])->in_rule = rule = BEGINFILE;
		(yyvsp[(1) - (1)])->source_file = source;
		(yyval) = (yyvsp[(1) - (1)]);
	  }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 349 "awkgram.y"
    {
		(yyvsp[(1) - (1)])->in_rule = rule = ENDFILE;
		(yyvsp[(1) - (1)])->source_file = source;
		(yyval) = (yyvsp[(1) - (1)]);
	  }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 358 "awkgram.y"
    {
		if ((yyvsp[(2) - (5)]) == NULL)
			(yyval) = list_create(instruction(Op_no_op));
		else
			(yyval) = (yyvsp[(2) - (5)]);
	  }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 368 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 370 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 372 "awkgram.y"
    {
		yyerror(_("`%s' is a built-in function, it cannot be redefined"),
					tokstart);
		YYABORT;
	  }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 378 "awkgram.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 388 "awkgram.y"
    {
		(yyvsp[(1) - (6)])->source_file = source;
		if (install_function((yyvsp[(2) - (6)])->lextok, (yyvsp[(1) - (6)]), (yyvsp[(4) - (6)])) < 0)
			YYABORT;
		in_function = (yyvsp[(2) - (6)])->lextok;
		(yyvsp[(2) - (6)])->lextok = NULL;
		bcfree((yyvsp[(2) - (6)]));
		/* $4 already free'd in install_function */
		(yyval) = (yyvsp[(1) - (6)]);
	  }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 406 "awkgram.y"
    { want_regexp = true; }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 408 "awkgram.y"
    {
		  NODE *n, *exp;
		  char *re;
		  size_t len;

		  re = (yyvsp[(3) - (3)])->lextok;
		  (yyvsp[(3) - (3)])->lextok = NULL;
		  len = strlen(re);
		  if (do_lint) {
			if (len == 0)
				lintwarn_ln((yyvsp[(3) - (3)])->source_line,
					_("regexp constant `//' looks like a C++ comment, but is not"));
			else if (re[0] == '*' && re[len-1] == '*')
				/* possible C comment */
				lintwarn_ln((yyvsp[(3) - (3)])->source_line,
					_("regexp constant `/%s/' looks like a C comment, but is not"), re);
		  }

		  exp = make_str_node(re, len, ALREADY_MALLOCED);
		  n = make_regnode(Node_regex, exp);
		  if (n == NULL) {
			unref(exp);
			YYABORT;
		  }
		  (yyval) = (yyvsp[(3) - (3)]);
		  (yyval)->opcode = Op_match_rec;
		  (yyval)->memory = n;
		}
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 440 "awkgram.y"
    { bcfree((yyvsp[(1) - (1)])); }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 446 "awkgram.y"
    {	(yyval) = NULL; }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 448 "awkgram.y"
    {
		if ((yyvsp[(2) - (2)]) == NULL)
			(yyval) = (yyvsp[(1) - (2)]);
		else {
			add_lint((yyvsp[(2) - (2)]), LINT_no_effect);
			if ((yyvsp[(1) - (2)]) == NULL)
				(yyval) = (yyvsp[(2) - (2)]);
			else
				(yyval) = list_merge((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
		}
	    yyerrok;
	  }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 461 "awkgram.y"
    {	(yyval) = NULL; }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 471 "awkgram.y"
    { (yyval) = NULL; }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 473 "awkgram.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 475 "awkgram.y"
    {
		if (do_pretty_print)
			(yyval) = list_prepend((yyvsp[(1) - (1)]), instruction(Op_exec_count));
		else
			(yyval) = (yyvsp[(1) - (1)]);
 	  }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 482 "awkgram.y"
    {
		INSTRUCTION *dflt, *curr = NULL, *cexp, *cstmt;
		INSTRUCTION *ip, *nextc, *tbreak;
		const char **case_values = NULL;
		int maxcount = 128;
		int case_count = 0;
		int i;

		tbreak = instruction(Op_no_op);	
		cstmt = list_create(tbreak);
		cexp = list_create(instruction(Op_pop));
		dflt = instruction(Op_jmp);
		dflt->target_jmp = tbreak;	/* if no case match and no explicit default */

		if ((yyvsp[(7) - (9)]) != NULL) {
			curr = (yyvsp[(7) - (9)])->nexti;
			bcfree((yyvsp[(7) - (9)]));	/* Op_list */
		} /*  else
				curr = NULL; */

		for(; curr != NULL; curr = nextc) {
			INSTRUCTION *caseexp = curr->case_exp;
			INSTRUCTION *casestmt = curr->case_stmt;

			nextc = curr->nexti;
			if (curr->opcode == Op_K_case) {
				if (caseexp->opcode == Op_push_i) {
					/* a constant scalar */
					char *caseval;
					caseval = force_string(caseexp->memory)->stptr;
					for (i = 0; i < case_count; i++) {
						if (strcmp(caseval, case_values[i]) == 0)
							error_ln(curr->source_line,
								_("duplicate case values in switch body: %s"), caseval);
					}
 
					if (case_values == NULL)
						emalloc(case_values, const char **, sizeof(char *) * maxcount, "statement");
					else if (case_count >= maxcount) {
						maxcount += 128;
						erealloc(case_values, const char **, sizeof(char*) * maxcount, "statement");
					}
					case_values[case_count++] = caseval;
				} else {
					/* match a constant regex against switch expression. */
					(curr + 1)->match_exp = true;
				}
				curr->stmt_start = casestmt->nexti;
				curr->stmt_end	= casestmt->lasti;
				(void) list_prepend(cexp, curr);
				(void) list_prepend(cexp, caseexp);
			} else {
				if (dflt->target_jmp != tbreak)
					error_ln(curr->source_line,
						_("duplicate `default' detected in switch body"));
				else
					dflt->target_jmp = casestmt->nexti;

				if (do_pretty_print) {
					curr->stmt_start = casestmt->nexti;
					curr->stmt_end = casestmt->lasti;
					(void) list_prepend(cexp, curr);
				} else
					bcfree(curr);
			}

			cstmt = list_merge(casestmt, cstmt);
		}

		if (case_values != NULL)
			efree(case_values);

		ip = (yyvsp[(3) - (9)]);
		if (do_pretty_print) {
			(void) list_prepend(ip, (yyvsp[(1) - (9)]));
			(void) list_prepend(ip, instruction(Op_exec_count));
			(yyvsp[(1) - (9)])->target_break = tbreak;
			((yyvsp[(1) - (9)]) + 1)->switch_start = cexp->nexti;
			((yyvsp[(1) - (9)]) + 1)->switch_end = cexp->lasti;
		}/* else
				$1 is NULL */

		(void) list_append(cexp, dflt);
		(void) list_merge(ip, cexp);
		(yyval) = list_merge(ip, cstmt);

		break_allowed--;			
		fix_break_continue(ip, tbreak, NULL);
	  }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 572 "awkgram.y"
    { 
		/*
		 *    -----------------
		 * tc:
		 *         cond
		 *    -----------------
		 *    [Op_jmp_false tb   ]
		 *    -----------------   
		 *         body
		 *    -----------------
		 *    [Op_jmp      tc    ]
		 * tb:[Op_no_op          ]
		 */

		INSTRUCTION *ip, *tbreak, *tcont;

		tbreak = instruction(Op_no_op);
		add_lint((yyvsp[(3) - (6)]), LINT_assign_in_cond);
		tcont = (yyvsp[(3) - (6)])->nexti;
		ip = list_append((yyvsp[(3) - (6)]), instruction(Op_jmp_false));
		ip->lasti->target_jmp = tbreak;

		if (do_pretty_print) {
			(void) list_append(ip, instruction(Op_exec_count));
			(yyvsp[(1) - (6)])->target_break = tbreak;
			(yyvsp[(1) - (6)])->target_continue = tcont;
			((yyvsp[(1) - (6)]) + 1)->while_body = ip->lasti;
			(void) list_prepend(ip, (yyvsp[(1) - (6)]));
		}/* else
				$1 is NULL */

		if ((yyvsp[(6) - (6)]) != NULL)
			(void) list_merge(ip, (yyvsp[(6) - (6)]));
		(void) list_append(ip, instruction(Op_jmp));
		ip->lasti->target_jmp = tcont;
		(yyval) = list_append(ip, tbreak);

		break_allowed--;
		continue_allowed--;
		fix_break_continue(ip, tbreak, tcont);
	  }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 614 "awkgram.y"
    {
		/*
		 *    -----------------
		 * z:
		 *         body
		 *    -----------------
		 * tc: 
		 *         cond
		 *    -----------------
		 *    [Op_jmp_true | z  ]
		 * tb:[Op_no_op         ]
		 */

		INSTRUCTION *ip, *tbreak, *tcont;

		tbreak = instruction(Op_no_op);
		tcont = (yyvsp[(6) - (8)])->nexti;
		add_lint((yyvsp[(6) - (8)]), LINT_assign_in_cond);
		if ((yyvsp[(3) - (8)]) != NULL)
			ip = list_merge((yyvsp[(3) - (8)]), (yyvsp[(6) - (8)]));
		else
			ip = list_prepend((yyvsp[(6) - (8)]), instruction(Op_no_op));
		if (do_pretty_print)
			(void) list_prepend(ip, instruction(Op_exec_count));
		(void) list_append(ip, instruction(Op_jmp_true));
		ip->lasti->target_jmp = ip->nexti;
		(yyval) = list_append(ip, tbreak);

		break_allowed--;
		continue_allowed--;
		fix_break_continue(ip, tbreak, tcont);

		if (do_pretty_print) {
			(yyvsp[(1) - (8)])->target_break = tbreak;
			(yyvsp[(1) - (8)])->target_continue = tcont;
			((yyvsp[(1) - (8)]) + 1)->doloop_cond = tcont;
			(yyval) = list_prepend(ip, (yyvsp[(1) - (8)]));
			bcfree((yyvsp[(4) - (8)]));
		} /* else
				$1 and $4 are NULLs */
	  }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 656 "awkgram.y"
    {
		INSTRUCTION *ip;
		char *var_name = (yyvsp[(3) - (8)])->lextok;

		if ((yyvsp[(8) - (8)]) != NULL
				&& (yyvsp[(8) - (8)])->lasti->opcode == Op_K_delete
				&& (yyvsp[(8) - (8)])->lasti->expr_count == 1
				&& (yyvsp[(8) - (8)])->nexti->opcode == Op_push
				&& ((yyvsp[(8) - (8)])->nexti->memory->type != Node_var || !((yyvsp[(8) - (8)])->nexti->memory->var_update))
				&& strcmp((yyvsp[(8) - (8)])->nexti->memory->vname, var_name) == 0
		) {
		
		/* Efficiency hack.  Recognize the special case of
		 *
		 * 	for (iggy in foo)
		 * 		delete foo[iggy]
		 *
		 * and treat it as if it were
		 *
		 * 	delete foo
		 *
		 * Check that the body is a `delete a[i]' statement,
		 * and that both the loop var and array names match.
		 */		 
			NODE *arr = NULL;

			ip = (yyvsp[(8) - (8)])->nexti->nexti; 
			if ((yyvsp[(5) - (8)])->nexti->opcode == Op_push && (yyvsp[(5) - (8)])->lasti == (yyvsp[(5) - (8)])->nexti)
				arr = (yyvsp[(5) - (8)])->nexti->memory;
			if (arr != NULL
					&& ip->opcode == Op_no_op
					&& ip->nexti->opcode == Op_push_array
					&& strcmp(ip->nexti->memory->vname, arr->vname) == 0
					&& ip->nexti->nexti == (yyvsp[(8) - (8)])->lasti
			) {
				(void) make_assignable((yyvsp[(8) - (8)])->nexti);
				(yyvsp[(8) - (8)])->lasti->opcode = Op_K_delete_loop;
				(yyvsp[(8) - (8)])->lasti->expr_count = 0;
				if ((yyvsp[(1) - (8)]) != NULL)
					bcfree((yyvsp[(1) - (8)]));
				efree(var_name);
				bcfree((yyvsp[(3) - (8)]));
				bcfree((yyvsp[(4) - (8)]));
				bcfree((yyvsp[(5) - (8)]));
				(yyval) = (yyvsp[(8) - (8)]);
			} else
				goto regular_loop;
		} else {
			INSTRUCTION *tbreak, *tcont;

			/*    [ Op_push_array a       ]
			 *    [ Op_arrayfor_init | ib ]
			 * ic:[ Op_arrayfor_incr | ib ] 
			 *    [ Op_var_assign if any  ]
			 *
			 *              body
			 *
			 *    [Op_jmp | ic            ]
			 * ib:[Op_arrayfor_final      ]
			 */
regular_loop:
			ip = (yyvsp[(5) - (8)]);
			ip->nexti->opcode = Op_push_array;

			tbreak = instruction(Op_arrayfor_final);
			(yyvsp[(4) - (8)])->opcode = Op_arrayfor_incr;
			(yyvsp[(4) - (8)])->array_var = variable((yyvsp[(3) - (8)])->source_line, var_name, Node_var);
			(yyvsp[(4) - (8)])->target_jmp = tbreak;
			tcont = (yyvsp[(4) - (8)]);
			(yyvsp[(3) - (8)])->opcode = Op_arrayfor_init;
			(yyvsp[(3) - (8)])->target_jmp = tbreak;
			(void) list_append(ip, (yyvsp[(3) - (8)]));

			if (do_pretty_print) {
				(yyvsp[(1) - (8)])->opcode = Op_K_arrayfor;
				(yyvsp[(1) - (8)])->target_continue = tcont;
				(yyvsp[(1) - (8)])->target_break = tbreak;
				(void) list_append(ip, (yyvsp[(1) - (8)]));
			} /* else
					$1 is NULL */

			/* add update_FOO instruction if necessary */ 
			if ((yyvsp[(4) - (8)])->array_var->type == Node_var && (yyvsp[(4) - (8)])->array_var->var_update) {
				(void) list_append(ip, instruction(Op_var_update));
				ip->lasti->update_var = (yyvsp[(4) - (8)])->array_var->var_update;
			}
			(void) list_append(ip, (yyvsp[(4) - (8)]));

			/* add set_FOO instruction if necessary */
			if ((yyvsp[(4) - (8)])->array_var->type == Node_var && (yyvsp[(4) - (8)])->array_var->var_assign) {
				(void) list_append(ip, instruction(Op_var_assign));
				ip->lasti->assign_var = (yyvsp[(4) - (8)])->array_var->var_assign;
			}

			if (do_pretty_print) {
				(void) list_append(ip, instruction(Op_exec_count));
				((yyvsp[(1) - (8)]) + 1)->forloop_cond = (yyvsp[(4) - (8)]);
				((yyvsp[(1) - (8)]) + 1)->forloop_body = ip->lasti; 
			}

			if ((yyvsp[(8) - (8)]) != NULL)
				(void) list_merge(ip, (yyvsp[(8) - (8)]));

			(void) list_append(ip, instruction(Op_jmp));
			ip->lasti->target_jmp = (yyvsp[(4) - (8)]);
			(yyval) = list_append(ip, tbreak);
			fix_break_continue(ip, tbreak, tcont);
		} 

		break_allowed--;
		continue_allowed--;
	  }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 769 "awkgram.y"
    {
		(yyval) = mk_for_loop((yyvsp[(1) - (12)]), (yyvsp[(3) - (12)]), (yyvsp[(6) - (12)]), (yyvsp[(9) - (12)]), (yyvsp[(12) - (12)]));

		break_allowed--;
		continue_allowed--;
	  }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 776 "awkgram.y"
    {
		(yyval) = mk_for_loop((yyvsp[(1) - (11)]), (yyvsp[(3) - (11)]), (INSTRUCTION *) NULL, (yyvsp[(8) - (11)]), (yyvsp[(11) - (11)]));

		break_allowed--;
		continue_allowed--;
	  }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 783 "awkgram.y"
    {
		if (do_pretty_print)
			(yyval) = list_prepend((yyvsp[(1) - (1)]), instruction(Op_exec_count));
		else
			(yyval) = (yyvsp[(1) - (1)]);
	  }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 793 "awkgram.y"
    { 
		if (! break_allowed)
			error_ln((yyvsp[(1) - (2)])->source_line,
				_("`break' is not allowed outside a loop or switch"));
		(yyvsp[(1) - (2)])->target_jmp = NULL;
		(yyval) = list_create((yyvsp[(1) - (2)]));

	  }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 802 "awkgram.y"
    {
		if (! continue_allowed)
			error_ln((yyvsp[(1) - (2)])->source_line,
				_("`continue' is not allowed outside a loop"));
		(yyvsp[(1) - (2)])->target_jmp = NULL;
		(yyval) = list_create((yyvsp[(1) - (2)]));

	  }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 811 "awkgram.y"
    {
		/* if inside function (rule = 0), resolve context at run-time */
		if (rule && rule != Rule)
			error_ln((yyvsp[(1) - (2)])->source_line,
				_("`next' used in %s action"), ruletab[rule]);
		(yyvsp[(1) - (2)])->target_jmp = ip_rec;
		(yyval) = list_create((yyvsp[(1) - (2)]));
	  }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 820 "awkgram.y"
    {
		/* if inside function (rule = 0), resolve context at run-time */
		if (rule == BEGIN || rule == END || rule == ENDFILE)
			error_ln((yyvsp[(1) - (2)])->source_line,
				_("`nextfile' used in %s action"), ruletab[rule]);

		(yyvsp[(1) - (2)])->target_newfile = ip_newfile;
		(yyvsp[(1) - (2)])->target_endfile = ip_endfile;
		(yyval) = list_create((yyvsp[(1) - (2)]));
	  }
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 831 "awkgram.y"
    {
		/* Initialize the two possible jump targets, the actual target
		 * is resolved at run-time. 
		 */
		(yyvsp[(1) - (3)])->target_end = ip_end;	/* first instruction in end_block */
		(yyvsp[(1) - (3)])->target_atexit = ip_atexit;	/* cleanup and go home */

		if ((yyvsp[(2) - (3)]) == NULL) {
			(yyval) = list_create((yyvsp[(1) - (3)]));
			(void) list_prepend((yyval), instruction(Op_push_i));
			(yyval)->nexti->memory = dupnode(Nnull_string);
		} else
			(yyval) = list_append((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]));
	  }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 846 "awkgram.y"
    {
		if (! in_function)
			yyerror(_("`return' used outside function context"));
	  }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 849 "awkgram.y"
    {
		if ((yyvsp[(3) - (4)]) == NULL) {
			(yyval) = list_create((yyvsp[(1) - (4)]));
			(void) list_prepend((yyval), instruction(Op_push_i));
			(yyval)->nexti->memory = dupnode(Nnull_string);
		} else {
			if (do_optimize > 1
				&& (yyvsp[(3) - (4)])->lasti->opcode == Op_func_call
				&& strcmp((yyvsp[(3) - (4)])->lasti->func_name, in_function) == 0
			) {
				/* Do tail recursion optimization. Tail
				 * call without a return value is recognized
				 * in mk_function().
				 */
				((yyvsp[(3) - (4)])->lasti + 1)->tail_call = true;
			}

			(yyval) = list_append((yyvsp[(3) - (4)]), (yyvsp[(1) - (4)]));
		}
	  }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 881 "awkgram.y"
    { in_print = true; in_parens = 0; }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 882 "awkgram.y"
    {
		/*
		 * Optimization: plain `print' has no expression list, so $3 is null.
		 * If $3 is NULL or is a bytecode list for $0 use Op_K_print_rec,
		 * which is faster for these two cases.
		 */

		if ((yyvsp[(1) - (4)])->opcode == Op_K_print &&
			((yyvsp[(3) - (4)]) == NULL
				|| ((yyvsp[(3) - (4)])->lasti->opcode == Op_field_spec
					&& (yyvsp[(3) - (4)])->nexti->nexti->nexti == (yyvsp[(3) - (4)])->lasti
					&& (yyvsp[(3) - (4)])->nexti->nexti->opcode == Op_push_i
					&& (yyvsp[(3) - (4)])->nexti->nexti->memory->type == Node_val)
			)
		) {
			static bool warned = false;
			/*   -----------------
			 *      output_redir
			 *    [ redirect exp ]
			 *   -----------------
			 *     expression_list
			 *   ------------------
			 *    [Op_K_print_rec | NULL | redir_type | expr_count]
			 */

			if ((yyvsp[(3) - (4)]) != NULL) {
				NODE *n = (yyvsp[(3) - (4)])->nexti->nexti->memory;

				if (! iszero(n))
					goto regular_print;

				bcfree((yyvsp[(3) - (4)])->lasti);			/* Op_field_spec */
				unref(n);				/* Node_val */
				bcfree((yyvsp[(3) - (4)])->nexti->nexti);		/* Op_push_i */
				bcfree((yyvsp[(3) - (4)])->nexti);			/* Op_list */
				bcfree((yyvsp[(3) - (4)]));				/* Op_list */
			} else {
				if (do_lint && (rule == BEGIN || rule == END) && ! warned) {
					warned = true;
					lintwarn_ln((yyvsp[(1) - (4)])->source_line,
		_("plain `print' in BEGIN or END rule should probably be `print \"\"'"));
				}
			}

			(yyvsp[(1) - (4)])->expr_count = 0;
			(yyvsp[(1) - (4)])->opcode = Op_K_print_rec;
			if ((yyvsp[(4) - (4)]) == NULL) {    /* no redircetion */
				(yyvsp[(1) - (4)])->redir_type = redirect_none;
				(yyval) = list_create((yyvsp[(1) - (4)]));
			} else {
				INSTRUCTION *ip;
				ip = (yyvsp[(4) - (4)])->nexti;
				(yyvsp[(1) - (4)])->redir_type = ip->redir_type;
				(yyvsp[(4) - (4)])->nexti = ip->nexti;
				bcfree(ip);
				(yyval) = list_append((yyvsp[(4) - (4)]), (yyvsp[(1) - (4)]));
			}
		} else {
			/*   -----------------
			 *    [ output_redir    ]
			 *    [ redirect exp    ]
			 *   -----------------
			 *    [ expression_list ]
			 *   ------------------
			 *    [$1 | NULL | redir_type | expr_count]
			 *
			 */
regular_print:	 
			if ((yyvsp[(4) - (4)]) == NULL) {		/* no redirection */
				if ((yyvsp[(3) - (4)]) == NULL)	{	/* printf without arg */
					(yyvsp[(1) - (4)])->expr_count = 0;
					(yyvsp[(1) - (4)])->redir_type = redirect_none;
					(yyval) = list_create((yyvsp[(1) - (4)]));
				} else {
					INSTRUCTION *t = (yyvsp[(3) - (4)]);
					(yyvsp[(1) - (4)])->expr_count = count_expressions(&t, false);
					(yyvsp[(1) - (4)])->redir_type = redirect_none;
					(yyval) = list_append(t, (yyvsp[(1) - (4)]));
				}
			} else {
				INSTRUCTION *ip;
				ip = (yyvsp[(4) - (4)])->nexti;
				(yyvsp[(1) - (4)])->redir_type = ip->redir_type;
				(yyvsp[(4) - (4)])->nexti = ip->nexti;
				bcfree(ip);
				if ((yyvsp[(3) - (4)]) == NULL) {
					(yyvsp[(1) - (4)])->expr_count = 0;
					(yyval) = list_append((yyvsp[(4) - (4)]), (yyvsp[(1) - (4)]));
				} else {
					INSTRUCTION *t = (yyvsp[(3) - (4)]);
					(yyvsp[(1) - (4)])->expr_count = count_expressions(&t, false);
					(yyval) = list_append(list_merge((yyvsp[(4) - (4)]), t), (yyvsp[(1) - (4)]));
				}
			}
		}
	  }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 979 "awkgram.y"
    { sub_counter = 0; }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 980 "awkgram.y"
    {
		char *arr = (yyvsp[(2) - (4)])->lextok;

		(yyvsp[(2) - (4)])->opcode = Op_push_array;
		(yyvsp[(2) - (4)])->memory = variable((yyvsp[(2) - (4)])->source_line, arr, Node_var_new);

		if (! do_posix && ! do_traditional) {
			if ((yyvsp[(2) - (4)])->memory == symbol_table)
				fatal(_("`delete' is not allowed with SYMTAB"));
			else if ((yyvsp[(2) - (4)])->memory == func_table)
				fatal(_("`delete' is not allowed with FUNCTAB"));
		}

		if ((yyvsp[(4) - (4)]) == NULL) {
			/*
			 * As of September 2012, POSIX has added support
			 * for `delete array'. See:
			 * http://austingroupbugs.net/view.php?id=544
			 *
			 * Thanks to Nathan Weeks for the initiative.
			 *
			 * Thus we no longer warn or check do_posix.
			 * Also, since BWK awk supports it, we don't have to
			 * check do_traditional either.
			 */
			(yyvsp[(1) - (4)])->expr_count = 0;
			(yyval) = list_append(list_create((yyvsp[(2) - (4)])), (yyvsp[(1) - (4)]));
		} else {
			(yyvsp[(1) - (4)])->expr_count = sub_counter;
			(yyval) = list_append(list_append((yyvsp[(4) - (4)]), (yyvsp[(2) - (4)])), (yyvsp[(1) - (4)]));
		}
	  }
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 1017 "awkgram.y"
    {
		static bool warned = false;
		char *arr = (yyvsp[(3) - (4)])->lextok;

		if (do_lint && ! warned) {
			warned = true;
			lintwarn_ln((yyvsp[(1) - (4)])->source_line,
				_("`delete(array)' is a non-portable tawk extension"));
		}
		if (do_traditional) {
			error_ln((yyvsp[(1) - (4)])->source_line,
				_("`delete(array)' is a non-portable tawk extension"));
		}
		(yyvsp[(3) - (4)])->memory = variable((yyvsp[(3) - (4)])->source_line, arr, Node_var_new);
		(yyvsp[(3) - (4)])->opcode = Op_push_array;
		(yyvsp[(1) - (4)])->expr_count = 0;
		(yyval) = list_append(list_create((yyvsp[(3) - (4)])), (yyvsp[(1) - (4)]));

		if (! do_posix && ! do_traditional) {
			if ((yyvsp[(3) - (4)])->memory == symbol_table)
				fatal(_("`delete' is not allowed with SYMTAB"));
			else if ((yyvsp[(3) - (4)])->memory == func_table)
				fatal(_("`delete' is not allowed with FUNCTAB"));
		}
	  }
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 1043 "awkgram.y"
    {	(yyval) = optimize_assignment((yyvsp[(1) - (1)])); }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 1048 "awkgram.y"
    { (yyval) = NULL; }
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 1050 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 1055 "awkgram.y"
    { (yyval) = NULL; }
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 1057 "awkgram.y"
    {
		if ((yyvsp[(1) - (2)]) == NULL)
			(yyval) = list_create((yyvsp[(2) - (2)]));
		else
			(yyval) = list_prepend((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
	  }
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 1064 "awkgram.y"
    { (yyval) = NULL; }
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 1069 "awkgram.y"
    {
		INSTRUCTION *casestmt = (yyvsp[(5) - (5)]);
		if ((yyvsp[(5) - (5)]) == NULL)
			casestmt = list_create(instruction(Op_no_op));	
		if (do_pretty_print)
			(void) list_prepend(casestmt, instruction(Op_exec_count));
		(yyvsp[(1) - (5)])->case_exp = (yyvsp[(2) - (5)]);
		(yyvsp[(1) - (5)])->case_stmt = casestmt;
		bcfree((yyvsp[(3) - (5)]));
		(yyval) = (yyvsp[(1) - (5)]);
	  }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 1081 "awkgram.y"
    {
		INSTRUCTION *casestmt = (yyvsp[(4) - (4)]);
		if ((yyvsp[(4) - (4)]) == NULL)
			casestmt = list_create(instruction(Op_no_op));
		if (do_pretty_print)
			(void) list_prepend(casestmt, instruction(Op_exec_count));
		bcfree((yyvsp[(2) - (4)]));
		(yyvsp[(1) - (4)])->case_stmt = casestmt;
		(yyval) = (yyvsp[(1) - (4)]);
	  }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 1095 "awkgram.y"
    {	(yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 1097 "awkgram.y"
    { 
		NODE *n = (yyvsp[(2) - (2)])->memory;
		(void) force_number(n);
		negate_num(n);
		bcfree((yyvsp[(1) - (2)]));
		(yyval) = (yyvsp[(2) - (2)]);
	  }
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 1105 "awkgram.y"
    {
		bcfree((yyvsp[(1) - (2)]));
		(yyval) = (yyvsp[(2) - (2)]);
	  }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 1110 "awkgram.y"
    {	(yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 1112 "awkgram.y"
    {
		(yyvsp[(1) - (1)])->opcode = Op_push_re;
		(yyval) = (yyvsp[(1) - (1)]);
	  }
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 1120 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 1122 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 1132 "awkgram.y"
    {
		(yyval) = (yyvsp[(2) - (3)]);
	  }
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 1139 "awkgram.y"
    {
		in_print = false;
		in_parens = 0;
		(yyval) = NULL;
	  }
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 1144 "awkgram.y"
    { in_print = false; in_parens = 0; }
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 1145 "awkgram.y"
    {
		if ((yyvsp[(1) - (3)])->redir_type == redirect_twoway
		    	&& (yyvsp[(3) - (3)])->lasti->opcode == Op_K_getline_redir
		   	 	&& (yyvsp[(3) - (3)])->lasti->redir_type == redirect_twoway)
			yyerror(_("multistage two-way pipelines don't work"));
		(yyval) = list_prepend((yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]));
	  }
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 1156 "awkgram.y"
    {
		(yyval) = mk_condition((yyvsp[(3) - (6)]), (yyvsp[(1) - (6)]), (yyvsp[(6) - (6)]), NULL, NULL);
	  }
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 1161 "awkgram.y"
    {
		(yyval) = mk_condition((yyvsp[(3) - (9)]), (yyvsp[(1) - (9)]), (yyvsp[(6) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)]));
	  }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 1178 "awkgram.y"
    { (yyval) = NULL; }
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 1180 "awkgram.y"
    {
		bcfree((yyvsp[(1) - (2)]));
		(yyval) = (yyvsp[(2) - (2)]);
	  }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 1188 "awkgram.y"
    { (yyval) = NULL; }
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 1190 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]) ; }
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 1195 "awkgram.y"
    {
		(yyvsp[(1) - (1)])->param_count = 0;
		(yyval) = list_create((yyvsp[(1) - (1)]));
	  }
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 1200 "awkgram.y"
    {
		(yyvsp[(3) - (3)])->param_count =  (yyvsp[(1) - (3)])->lasti->param_count + 1;
		(yyval) = list_append((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
		yyerrok;
	  }
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 1206 "awkgram.y"
    { (yyval) = NULL; }
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 1208 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (2)]); }
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 1210 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (3)]); }
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 1216 "awkgram.y"
    { (yyval) = NULL; }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 1218 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 1223 "awkgram.y"
    { (yyval) = NULL; }
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 1225 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 1230 "awkgram.y"
    {	(yyval) = mk_expression_list(NULL, (yyvsp[(1) - (1)])); }
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 1232 "awkgram.y"
    {
		(yyval) = mk_expression_list((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
		yyerrok;
	  }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 1237 "awkgram.y"
    { (yyval) = NULL; }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 1239 "awkgram.y"
    {
		/*
		 * Returning the expression list instead of NULL lets
		 * snode get a list of arguments that it can count.
		 */
		(yyval) = (yyvsp[(1) - (2)]);
	  }
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 1247 "awkgram.y"
    {
		/* Ditto */
		(yyval) = mk_expression_list((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	  }
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 1252 "awkgram.y"
    {
		/* Ditto */
		(yyval) = (yyvsp[(1) - (3)]);
	  }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 1261 "awkgram.y"
    {
		if (do_lint && (yyvsp[(3) - (3)])->lasti->opcode == Op_match_rec)
			lintwarn_ln((yyvsp[(2) - (3)])->source_line,
				_("regular expression on right of assignment"));
		(yyval) = mk_assignment((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)]));
	  }
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 1268 "awkgram.y"
    {	(yyval) = mk_boolean((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 1270 "awkgram.y"
    {	(yyval) = mk_boolean((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 1272 "awkgram.y"
    {
		if ((yyvsp[(1) - (3)])->lasti->opcode == Op_match_rec)
			warning_ln((yyvsp[(2) - (3)])->source_line,
				_("regular expression on left of `~' or `!~' operator"));

		if ((yyvsp[(3) - (3)])->lasti == (yyvsp[(3) - (3)])->nexti && (yyvsp[(3) - (3)])->nexti->opcode == Op_match_rec) {
			(yyvsp[(2) - (3)])->memory = (yyvsp[(3) - (3)])->nexti->memory;
			bcfree((yyvsp[(3) - (3)])->nexti);	/* Op_match_rec */
			bcfree((yyvsp[(3) - (3)]));			/* Op_list */
			(yyval) = list_append((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]));
		} else {
			(yyvsp[(2) - (3)])->memory = make_regnode(Node_dynregex, NULL);
			(yyval) = list_append(list_merge((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])), (yyvsp[(2) - (3)]));
		}
	  }
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 1288 "awkgram.y"
    {
		if (do_lint_old)
			warning_ln((yyvsp[(2) - (3)])->source_line,
				_("old awk does not support the keyword `in' except after `for'"));
		(yyvsp[(3) - (3)])->nexti->opcode = Op_push_array;
		(yyvsp[(2) - (3)])->opcode = Op_in_array;
		(yyvsp[(2) - (3)])->expr_count = 1;
		(yyval) = list_append(list_merge((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])), (yyvsp[(2) - (3)]));
	  }
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 1298 "awkgram.y"
    {
		if (do_lint && (yyvsp[(3) - (3)])->lasti->opcode == Op_match_rec)
			lintwarn_ln((yyvsp[(2) - (3)])->source_line,
				_("regular expression on right of comparison"));
		(yyval) = list_append(list_merge((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])), (yyvsp[(2) - (3)]));
	  }
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 1305 "awkgram.y"
    { (yyval) = mk_condition((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)])); }
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 1307 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 1312 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 1314 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 1316 "awkgram.y"
    {	
		(yyvsp[(2) - (2)])->opcode = Op_assign_quotient;
		(yyval) = (yyvsp[(2) - (2)]);
	  }
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 1324 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 1326 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 1331 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 1333 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 1338 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 1340 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 1342 "awkgram.y"
    {
		int count = 2;
		bool is_simple_var = false;

		if ((yyvsp[(1) - (2)])->lasti->opcode == Op_concat) {
			/* multiple (> 2) adjacent strings optimization */
			is_simple_var = ((yyvsp[(1) - (2)])->lasti->concat_flag & CSVAR);
			count = (yyvsp[(1) - (2)])->lasti->expr_count + 1;
			(yyvsp[(1) - (2)])->lasti->opcode = Op_no_op;
		} else {
			is_simple_var = ((yyvsp[(1) - (2)])->nexti->opcode == Op_push
					&& (yyvsp[(1) - (2)])->lasti == (yyvsp[(1) - (2)])->nexti); /* first exp. is a simple
					                             * variable?; kludge for use
					                             * in Op_assign_concat.
		 			                             */
		}

		if (do_optimize > 1
			&& (yyvsp[(1) - (2)])->nexti == (yyvsp[(1) - (2)])->lasti && (yyvsp[(1) - (2)])->nexti->opcode == Op_push_i
			&& (yyvsp[(2) - (2)])->nexti == (yyvsp[(2) - (2)])->lasti && (yyvsp[(2) - (2)])->nexti->opcode == Op_push_i
		) {
			NODE *n1 = (yyvsp[(1) - (2)])->nexti->memory;
			NODE *n2 = (yyvsp[(2) - (2)])->nexti->memory;
			size_t nlen;

			n1 = force_string(n1);
			n2 = force_string(n2);
			nlen = n1->stlen + n2->stlen;
			erealloc(n1->stptr, char *, nlen + 2, "constant fold");
			memcpy(n1->stptr + n1->stlen, n2->stptr, n2->stlen);
			n1->stlen = nlen;
			n1->stptr[nlen] = '\0';
			n1->flags &= ~(NUMCUR|NUMBER|NUMINT);
			n1->flags |= (STRING|STRCUR);
			unref(n2);
			bcfree((yyvsp[(2) - (2)])->nexti);
			bcfree((yyvsp[(2) - (2)]));
			(yyval) = (yyvsp[(1) - (2)]);
		} else {
			(yyval) = list_append(list_merge((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])), instruction(Op_concat));
			(yyval)->lasti->concat_flag = (is_simple_var ? CSVAR : 0);
			(yyval)->lasti->expr_count = count;
			if (count > max_args)
				max_args = count;
		}
	  }
    break;

  case 129:
/* Line 1787 of yacc.c  */
#line 1394 "awkgram.y"
    { (yyval) = mk_binary((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 1396 "awkgram.y"
    { (yyval) = mk_binary((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 1398 "awkgram.y"
    { (yyval) = mk_binary((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 1400 "awkgram.y"
    { (yyval) = mk_binary((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 1402 "awkgram.y"
    { (yyval) = mk_binary((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 1404 "awkgram.y"
    { (yyval) = mk_binary((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 135:
/* Line 1787 of yacc.c  */
#line 1406 "awkgram.y"
    {
		/*
		 * In BEGINFILE/ENDFILE, allow `getline var < file'
		 */

		if (rule == BEGINFILE || rule == ENDFILE) {
			if ((yyvsp[(2) - (3)]) != NULL && (yyvsp[(3) - (3)]) != NULL)
				;	 /* all  ok */
			else {
				if ((yyvsp[(2) - (3)]) != NULL)
					error_ln((yyvsp[(1) - (3)])->source_line,
						_("`getline var' invalid inside `%s' rule"), ruletab[rule]);
				else
					error_ln((yyvsp[(1) - (3)])->source_line,
						_("`getline' invalid inside `%s' rule"), ruletab[rule]);
			}
		}
		if (do_lint && rule == END && (yyvsp[(3) - (3)]) == NULL)
			lintwarn_ln((yyvsp[(1) - (3)])->source_line,
				_("non-redirected `getline' undefined inside END action"));
		(yyval) = mk_getline((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), redirect_input);
	  }
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 1429 "awkgram.y"
    {
		(yyvsp[(2) - (2)])->opcode = Op_postincrement;
		(yyval) = mk_assignment((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
	  }
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 1434 "awkgram.y"
    {
		(yyvsp[(2) - (2)])->opcode = Op_postdecrement;
		(yyval) = mk_assignment((yyvsp[(1) - (2)]), NULL, (yyvsp[(2) - (2)]));
	  }
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 1439 "awkgram.y"
    {
		if (do_lint_old) {
		    warning_ln((yyvsp[(4) - (5)])->source_line,
				_("old awk does not support the keyword `in' except after `for'"));
		    warning_ln((yyvsp[(4) - (5)])->source_line,
				_("old awk does not support multidimensional arrays"));
		}
		(yyvsp[(5) - (5)])->nexti->opcode = Op_push_array;
		(yyvsp[(4) - (5)])->opcode = Op_in_array;
		if ((yyvsp[(2) - (5)]) == NULL) {	/* error */
			errcount++;
			(yyvsp[(4) - (5)])->expr_count = 0;
			(yyval) = list_merge((yyvsp[(5) - (5)]), (yyvsp[(4) - (5)]));
		} else {
			INSTRUCTION *t = (yyvsp[(2) - (5)]);
			(yyvsp[(4) - (5)])->expr_count = count_expressions(&t, false);
			(yyval) = list_append(list_merge(t, (yyvsp[(5) - (5)])), (yyvsp[(4) - (5)]));
		}
	  }
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 1464 "awkgram.y"
    {
		  (yyval) = mk_getline((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]), (yyvsp[(1) - (4)]), (yyvsp[(2) - (4)])->redir_type);
		  bcfree((yyvsp[(2) - (4)]));
		}
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 1470 "awkgram.y"
    { (yyval) = mk_binary((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 1472 "awkgram.y"
    { (yyval) = mk_binary((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 1474 "awkgram.y"
    { (yyval) = mk_binary((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 1476 "awkgram.y"
    { (yyval) = mk_binary((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 1478 "awkgram.y"
    { (yyval) = mk_binary((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 1480 "awkgram.y"
    { (yyval) = mk_binary((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); }
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 1485 "awkgram.y"
    {
		(yyval) = list_create((yyvsp[(1) - (1)]));
	  }
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 1489 "awkgram.y"
    {
		if ((yyvsp[(2) - (2)])->opcode == Op_match_rec) {
			(yyvsp[(2) - (2)])->opcode = Op_nomatch;
			(yyvsp[(1) - (2)])->opcode = Op_push_i;
			(yyvsp[(1) - (2)])->memory = make_number(0.0);	
			(yyval) = list_append(list_append(list_create((yyvsp[(1) - (2)])),
						instruction(Op_field_spec)), (yyvsp[(2) - (2)]));
		} else {
			if (do_optimize > 1 && (yyvsp[(2) - (2)])->nexti == (yyvsp[(2) - (2)])->lasti
					&& (yyvsp[(2) - (2)])->nexti->opcode == Op_push_i
					&& ((yyvsp[(2) - (2)])->nexti->memory->flags & (MPFN|MPZN)) == 0
			) {
				NODE *n = (yyvsp[(2) - (2)])->nexti->memory;
				if ((n->flags & (STRCUR|STRING)) != 0) {
					n->numbr = (AWKNUM) (n->stlen == 0);
					n->flags &= ~(STRCUR|STRING);
					n->flags |= (NUMCUR|NUMBER);
					efree(n->stptr);
					n->stptr = NULL;
					n->stlen = 0;
				} else
					n->numbr = (AWKNUM) (n->numbr == 0.0);
				bcfree((yyvsp[(1) - (2)]));
				(yyval) = (yyvsp[(2) - (2)]);
			} else {
				(yyvsp[(1) - (2)])->opcode = Op_not;
				add_lint((yyvsp[(2) - (2)]), LINT_assign_in_cond);
				(yyval) = list_append((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));
			}
		}
	   }
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 1521 "awkgram.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 1523 "awkgram.y"
    {
		(yyval) = snode((yyvsp[(3) - (4)]), (yyvsp[(1) - (4)]));
		if ((yyval) == NULL)
			YYABORT;
	  }
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 1529 "awkgram.y"
    {
		(yyval) = snode((yyvsp[(3) - (4)]), (yyvsp[(1) - (4)]));
		if ((yyval) == NULL)
			YYABORT;
	  }
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 1535 "awkgram.y"
    {
		static bool warned = false;

		if (do_lint && ! warned) {
			warned = true;
			lintwarn_ln((yyvsp[(1) - (1)])->source_line,
				_("call of `length' without parentheses is not portable"));
		}
		(yyval) = snode(NULL, (yyvsp[(1) - (1)]));
		if ((yyval) == NULL)
			YYABORT;
	  }
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 1550 "awkgram.y"
    {
		(yyvsp[(1) - (2)])->opcode = Op_preincrement;
		(yyval) = mk_assignment((yyvsp[(2) - (2)]), NULL, (yyvsp[(1) - (2)]));
	  }
    break;

  case 155:
/* Line 1787 of yacc.c  */
#line 1555 "awkgram.y"
    {
		(yyvsp[(1) - (2)])->opcode = Op_predecrement;
		(yyval) = mk_assignment((yyvsp[(2) - (2)]), NULL, (yyvsp[(1) - (2)]));
	  }
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 1560 "awkgram.y"
    {
		(yyval) = list_create((yyvsp[(1) - (1)]));
	  }
    break;

  case 157:
/* Line 1787 of yacc.c  */
#line 1564 "awkgram.y"
    {
		(yyval) = list_create((yyvsp[(1) - (1)]));
	  }
    break;

  case 158:
/* Line 1787 of yacc.c  */
#line 1568 "awkgram.y"
    {
		if ((yyvsp[(2) - (2)])->lasti->opcode == Op_push_i
			&& ((yyvsp[(2) - (2)])->lasti->memory->flags & (STRCUR|STRING)) == 0
		) {
			NODE *n = (yyvsp[(2) - (2)])->lasti->memory;
			(void) force_number(n);
			negate_num(n);			
			(yyval) = (yyvsp[(2) - (2)]);
			bcfree((yyvsp[(1) - (2)]));
		} else {
			(yyvsp[(1) - (2)])->opcode = Op_unary_minus;
			(yyval) = list_append((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));
		}
	  }
    break;

  case 159:
/* Line 1787 of yacc.c  */
#line 1583 "awkgram.y"
    {
	    /*
	     * was: $$ = $2
	     * POSIX semantics: force a conversion to numeric type
	     */
		(yyvsp[(1) - (2)])->opcode = Op_plus_i;
		(yyvsp[(1) - (2)])->memory = make_number(0.0);
		(yyval) = list_append((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));
	  }
    break;

  case 160:
/* Line 1787 of yacc.c  */
#line 1596 "awkgram.y"
    {
		func_use((yyvsp[(1) - (1)])->lasti->func_name, FUNC_USE);
		(yyval) = (yyvsp[(1) - (1)]);
	  }
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 1601 "awkgram.y"
    {
		/* indirect function call */
		INSTRUCTION *f, *t;
		char *name;
		NODE *indirect_var;
		static bool warned = false;
		const char *msg = _("indirect function calls are a gawk extension");

		if (do_traditional || do_posix)
			yyerror("%s", msg);
		else if (do_lint && ! warned) {
			warned = true;
			lintwarn("%s", msg);
		}
		
		f = (yyvsp[(2) - (2)])->lasti;
		f->opcode = Op_indirect_func_call;
		name = estrdup(f->func_name, strlen(f->func_name));
		if (is_std_var(name))
			yyerror(_("can not use special variable `%s' for indirect function call"), name);
		indirect_var = variable(f->source_line, name, Node_var_new);
		t = instruction(Op_push);
		t->memory = indirect_var;

		/* prepend indirect var instead of appending to arguments (opt_expression_list),
		 * and pop it off in setup_frame (eval.c) (left to right evaluation order); Test case:
		 *		f = "fun"
		 *		@f(f="real_fun")
		 */

		(yyval) = list_prepend((yyvsp[(2) - (2)]), t);
	  }
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 1637 "awkgram.y"
    {
		param_sanity((yyvsp[(3) - (4)]));
		(yyvsp[(1) - (4)])->opcode = Op_func_call;
		(yyvsp[(1) - (4)])->func_body = NULL;
		if ((yyvsp[(3) - (4)]) == NULL) {	/* no argument or error */
			((yyvsp[(1) - (4)]) + 1)->expr_count = 0;
			(yyval) = list_create((yyvsp[(1) - (4)]));
		} else {
			INSTRUCTION *t = (yyvsp[(3) - (4)]);
			((yyvsp[(1) - (4)]) + 1)->expr_count = count_expressions(&t, true); 
			(yyval) = list_append(t, (yyvsp[(1) - (4)]));
		}
	  }
    break;

  case 163:
/* Line 1787 of yacc.c  */
#line 1654 "awkgram.y"
    { (yyval) = NULL; }
    break;

  case 164:
/* Line 1787 of yacc.c  */
#line 1656 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 165:
/* Line 1787 of yacc.c  */
#line 1661 "awkgram.y"
    { (yyval) = NULL; }
    break;

  case 166:
/* Line 1787 of yacc.c  */
#line 1663 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (2)]); }
    break;

  case 167:
/* Line 1787 of yacc.c  */
#line 1668 "awkgram.y"
    {	(yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 168:
/* Line 1787 of yacc.c  */
#line 1670 "awkgram.y"
    {
		(yyval) = list_merge((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
	  }
    break;

  case 169:
/* Line 1787 of yacc.c  */
#line 1677 "awkgram.y"
    {
		INSTRUCTION *ip = (yyvsp[(1) - (1)])->lasti; 
		int count = ip->sub_count;	/* # of SUBSEP-seperated expressions */
		if (count > 1) {
			/* change Op_subscript or Op_sub_array to Op_concat */
			ip->opcode = Op_concat;
			ip->concat_flag = CSUBSEP;
			ip->expr_count = count;
		} else
			ip->opcode = Op_no_op;
		sub_counter++;	/* count # of dimensions */
		(yyval) = (yyvsp[(1) - (1)]);
	  }
    break;

  case 170:
/* Line 1787 of yacc.c  */
#line 1694 "awkgram.y"
    {
		INSTRUCTION *t = (yyvsp[(2) - (3)]);
		if ((yyvsp[(2) - (3)]) == NULL) {
			error_ln((yyvsp[(3) - (3)])->source_line,
				_("invalid subscript expression"));
			/* install Null string as subscript. */
			t = list_create(instruction(Op_push_i));
			t->nexti->memory = dupnode(Nnull_string);
			(yyvsp[(3) - (3)])->sub_count = 1;			
		} else
			(yyvsp[(3) - (3)])->sub_count = count_expressions(&t, false);
		(yyval) = list_append(t, (yyvsp[(3) - (3)]));
	  }
    break;

  case 171:
/* Line 1787 of yacc.c  */
#line 1711 "awkgram.y"
    {	(yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 172:
/* Line 1787 of yacc.c  */
#line 1713 "awkgram.y"
    {
		(yyval) = list_merge((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
	  }
    break;

  case 173:
/* Line 1787 of yacc.c  */
#line 1720 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (2)]); }
    break;

  case 174:
/* Line 1787 of yacc.c  */
#line 1725 "awkgram.y"
    {
		char *var_name = (yyvsp[(1) - (1)])->lextok;

		(yyvsp[(1) - (1)])->opcode = Op_push;
		(yyvsp[(1) - (1)])->memory = variable((yyvsp[(1) - (1)])->source_line, var_name, Node_var_new);
		(yyval) = list_create((yyvsp[(1) - (1)]));
	  }
    break;

  case 175:
/* Line 1787 of yacc.c  */
#line 1733 "awkgram.y"
    {
		char *arr = (yyvsp[(1) - (2)])->lextok;
		(yyvsp[(1) - (2)])->memory = variable((yyvsp[(1) - (2)])->source_line, arr, Node_var_new);
		(yyvsp[(1) - (2)])->opcode = Op_push_array;
		(yyval) = list_prepend((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));
	  }
    break;

  case 176:
/* Line 1787 of yacc.c  */
#line 1743 "awkgram.y"
    {
		INSTRUCTION *ip = (yyvsp[(1) - (1)])->nexti;
		if (ip->opcode == Op_push
			&& ip->memory->type == Node_var
			&& ip->memory->var_update
		) {
			(yyval) = list_prepend((yyvsp[(1) - (1)]), instruction(Op_var_update));
			(yyval)->nexti->update_var = ip->memory->var_update;
		} else
			(yyval) = (yyvsp[(1) - (1)]);
	  }
    break;

  case 177:
/* Line 1787 of yacc.c  */
#line 1755 "awkgram.y"
    {
		(yyval) = list_append((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]));
		if ((yyvsp[(3) - (3)]) != NULL)
			mk_assignment((yyvsp[(2) - (3)]), NULL, (yyvsp[(3) - (3)]));
	  }
    break;

  case 178:
/* Line 1787 of yacc.c  */
#line 1764 "awkgram.y"
    {
		(yyvsp[(1) - (1)])->opcode = Op_postincrement;
	  }
    break;

  case 179:
/* Line 1787 of yacc.c  */
#line 1768 "awkgram.y"
    {
		(yyvsp[(1) - (1)])->opcode = Op_postdecrement;
	  }
    break;

  case 180:
/* Line 1787 of yacc.c  */
#line 1771 "awkgram.y"
    { (yyval) = NULL; }
    break;

  case 182:
/* Line 1787 of yacc.c  */
#line 1779 "awkgram.y"
    { yyerrok; }
    break;

  case 183:
/* Line 1787 of yacc.c  */
#line 1783 "awkgram.y"
    { yyerrok; }
    break;

  case 186:
/* Line 1787 of yacc.c  */
#line 1792 "awkgram.y"
    { yyerrok; }
    break;

  case 187:
/* Line 1787 of yacc.c  */
#line 1796 "awkgram.y"
    { (yyval) = (yyvsp[(1) - (1)]); yyerrok; }
    break;

  case 188:
/* Line 1787 of yacc.c  */
#line 1800 "awkgram.y"
    { yyerrok; }
    break;


/* Line 1787 of yacc.c  */
#line 4118 "awkgram.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2050 of yacc.c  */
#line 1802 "awkgram.y"


struct token {
	const char *operator;	/* text to match */
	OPCODE value;			/*  type */
	int class;				/* lexical class */
	unsigned flags;			/* # of args. allowed and compatability */
#	define	ARGS	0xFF	/* 0, 1, 2, 3 args allowed (any combination */
#	define	A(n)	(1<<(n))
#	define	VERSION_MASK	0xFF00	/* old awk is zero */
#	define	NOT_OLD		0x0100	/* feature not in old awk */
#	define	NOT_POSIX	0x0200	/* feature not in POSIX */
#	define	GAWKX		0x0400	/* gawk extension */
#	define	BREAK		0x0800	/* break allowed inside */
#	define	CONTINUE	0x1000	/* continue allowed inside */
	
	NODE *(*ptr)(int);	/* function that implements this keyword */
	NODE *(*ptr2)(int);	/* alternate arbitrary-precision function */
};

#if 'a' == 0x81 /* it's EBCDIC */
/* tokcompare --- lexicographically compare token names for sorting */

static int
tokcompare(const void *l, const void *r)
{
	struct token *lhs, *rhs;

	lhs = (struct token *) l;
	rhs = (struct token *) r;

	return strcmp(lhs->operator, rhs->operator);
}
#endif

/*
 * Tokentab is sorted ASCII ascending order, so it can be binary searched.
 * See check_special(), which sorts the table on EBCDIC systems.
 * Function pointers come from declarations in awk.h.
 */

#ifdef HAVE_MPFR
#define MPF(F) do_mpfr_##F
#else
#define MPF(F) 0
#endif

static const struct token tokentab[] = {
{"BEGIN",	Op_rule,	 LEX_BEGIN,	0,		0,	0},
{"BEGINFILE",	Op_rule,	 LEX_BEGINFILE,	GAWKX,		0,	0},
{"END",		Op_rule,	 LEX_END,	0,		0,	0},
{"ENDFILE",		Op_rule,	 LEX_ENDFILE,	GAWKX,		0,	0},
#ifdef ARRAYDEBUG
{"adump",	Op_builtin,    LEX_BUILTIN,	GAWKX|A(1)|A(2),	do_adump,	0},
#endif
{"and",		Op_builtin,    LEX_BUILTIN,	GAWKX,		do_and,	MPF(and)},
{"asort",	Op_builtin,	 LEX_BUILTIN,	GAWKX|A(1)|A(2)|A(3),	do_asort,	0},
{"asorti",	Op_builtin,	 LEX_BUILTIN,	GAWKX|A(1)|A(2)|A(3),	do_asorti,	0},
{"atan2",	Op_builtin,	 LEX_BUILTIN,	NOT_OLD|A(2),	do_atan2,	MPF(atan2)},
{"bindtextdomain",	Op_builtin,	 LEX_BUILTIN,	GAWKX|A(1)|A(2),	do_bindtextdomain,	0},
{"break",	Op_K_break,	 LEX_BREAK,	0,		0,	0},
{"case",	Op_K_case,	 LEX_CASE,	GAWKX,		0,	0},
{"close",	Op_builtin,	 LEX_BUILTIN,	NOT_OLD|A(1)|A(2),	do_close,	0},
{"compl",	Op_builtin,    LEX_BUILTIN,	GAWKX|A(1),	do_compl,	MPF(compl)},
{"continue",	Op_K_continue, LEX_CONTINUE,	0,		0,	0},
{"cos",		Op_builtin,	 LEX_BUILTIN,	NOT_OLD|A(1),	do_cos,	MPF(cos)},
{"dcgettext",	Op_builtin,	 LEX_BUILTIN,	GAWKX|A(1)|A(2)|A(3),	do_dcgettext,	0},
{"dcngettext",	Op_builtin,	 LEX_BUILTIN,	GAWKX|A(1)|A(2)|A(3)|A(4)|A(5),	do_dcngettext,	0},
{"default",	Op_K_default,	 LEX_DEFAULT,	GAWKX,		0,	0},
{"delete",	Op_K_delete,	 LEX_DELETE,	NOT_OLD,	0,	0},
{"do",		Op_K_do,	 LEX_DO,	NOT_OLD|BREAK|CONTINUE,	0,	0},
{"else",	Op_K_else,	 LEX_ELSE,	0,		0,	0},
{"eval",	Op_symbol,	 LEX_EVAL,	0,		0,	0},
{"exit",	Op_K_exit,	 LEX_EXIT,	0,		0,	0},
{"exp",		Op_builtin,	 LEX_BUILTIN,	A(1),		do_exp,	MPF(exp)},
#ifdef DYNAMIC
{"extension",	Op_builtin,	 LEX_BUILTIN,	GAWKX|A(1)|A(2)|A(3),	do_ext,	0},
#endif
{"fflush",	Op_builtin,	 LEX_BUILTIN,	A(0)|A(1), do_fflush,	0},
{"for",		Op_K_for,	 LEX_FOR,	BREAK|CONTINUE,	0,	0},
{"func",	Op_func, LEX_FUNCTION,	NOT_POSIX|NOT_OLD,	0,	0},
{"function",Op_func, LEX_FUNCTION,	NOT_OLD,	0,	0},
{"gensub",	Op_sub_builtin,	 LEX_BUILTIN,	GAWKX|A(3)|A(4), 0,	0},
{"getline",	Op_K_getline_redir,	 LEX_GETLINE,	NOT_OLD,	0,	0},
{"gsub",	Op_sub_builtin,	 LEX_BUILTIN,	NOT_OLD|A(2)|A(3), 0,	0},
{"if",		Op_K_if,	 LEX_IF,	0,		0,	0},
{"in",		Op_symbol,	 LEX_IN,	0,		0,	0},
{"include",	Op_symbol,	 LEX_INCLUDE,	GAWKX,	0,	0},
{"index",	Op_builtin,	 LEX_BUILTIN,	A(2),		do_index,	0},
{"int",		Op_builtin,	 LEX_BUILTIN,	A(1),		do_int,	MPF(int)},
{"isarray",	Op_builtin,	 LEX_BUILTIN,	GAWKX|A(1),	do_isarray,	0},
{"length",	Op_builtin,	 LEX_LENGTH,	A(0)|A(1),	do_length,	0},
{"load",  	Op_symbol,	 LEX_LOAD,	GAWKX,		0,	0},
{"log",		Op_builtin,	 LEX_BUILTIN,	A(1),		do_log,	MPF(log)},
{"lshift",	Op_builtin,    LEX_BUILTIN,	GAWKX|A(2),	do_lshift,	MPF(lshift)},
{"match",	Op_builtin,	 LEX_BUILTIN,	NOT_OLD|A(2)|A(3), do_match,	0},
{"mktime",	Op_builtin,	 LEX_BUILTIN,	GAWKX|A(1),	do_mktime,	0},
{"next",	Op_K_next,	 LEX_NEXT,	0,		0,	0},
{"nextfile",	Op_K_nextfile, LEX_NEXTFILE,	0,		0,	0},
{"or",		Op_builtin,    LEX_BUILTIN,	GAWKX,		do_or,	MPF(or)},
{"patsplit",	Op_builtin,    LEX_BUILTIN,	GAWKX|A(2)|A(3)|A(4), do_patsplit,	0},
{"print",	Op_K_print,	 LEX_PRINT,	0,		0,	0},
{"printf",	Op_K_printf,	 LEX_PRINTF,	0,		0,	0},
{"rand",	Op_builtin,	 LEX_BUILTIN,	NOT_OLD|A(0),	do_rand,	MPF(rand)},
{"return",	Op_K_return,	 LEX_RETURN,	NOT_OLD,	0,	0},
{"rshift",	Op_builtin,    LEX_BUILTIN,	GAWKX|A(2),	do_rshift,	MPF(rshift)},
{"sin",		Op_builtin,	 LEX_BUILTIN,	NOT_OLD|A(1),	do_sin,	MPF(sin)},
{"split",	Op_builtin,	 LEX_BUILTIN,	A(2)|A(3)|A(4),	do_split,	0},
{"sprintf",	Op_builtin,	 LEX_BUILTIN,	0,		do_sprintf,	0},
{"sqrt",	Op_builtin,	 LEX_BUILTIN,	A(1),		do_sqrt,	MPF(sqrt)},
{"srand",	Op_builtin,	 LEX_BUILTIN,	NOT_OLD|A(0)|A(1), do_srand,	MPF(srand)},
#if defined(GAWKDEBUG) || defined(ARRAYDEBUG) /* || ... */
{"stopme",	Op_builtin,	LEX_BUILTIN,	GAWKX|A(0),	stopme,		0},
#endif
{"strftime",	Op_builtin,	 LEX_BUILTIN,	GAWKX|A(0)|A(1)|A(2)|A(3), do_strftime,	0},
{"strtonum",	Op_builtin,    LEX_BUILTIN,	GAWKX|A(1),	do_strtonum, MPF(strtonum)},
{"sub",		Op_sub_builtin,	 LEX_BUILTIN,	NOT_OLD|A(2)|A(3), 0,	0},
{"substr",	Op_builtin,	 LEX_BUILTIN,	A(2)|A(3),	do_substr,	0},
{"switch",	Op_K_switch,	 LEX_SWITCH,	GAWKX|BREAK,	0,	0},
{"system",	Op_builtin,	 LEX_BUILTIN,	NOT_OLD|A(1),	do_system,	0},
{"systime",	Op_builtin,	 LEX_BUILTIN,	GAWKX|A(0),	do_systime,	0},
{"tolower",	Op_builtin,	 LEX_BUILTIN,	NOT_OLD|A(1),	do_tolower,	0},
{"toupper",	Op_builtin,	 LEX_BUILTIN,	NOT_OLD|A(1),	do_toupper,	0},
{"while",	Op_K_while,	 LEX_WHILE,	BREAK|CONTINUE,	0,	0},
{"xor",		Op_builtin,    LEX_BUILTIN,	GAWKX,		do_xor,	MPF(xor)},
};

#if MBS_SUPPORT
/* Variable containing the current shift state.  */
static mbstate_t cur_mbstate;
/* Ring buffer containing current characters.  */
#define MAX_CHAR_IN_RING_BUFFER 8
#define RING_BUFFER_SIZE (MAX_CHAR_IN_RING_BUFFER * MB_LEN_MAX)
static char cur_char_ring[RING_BUFFER_SIZE];
/* Index for ring buffers.  */
static int cur_ring_idx;
/* This macro means that last nextc() return a singlebyte character
   or 1st byte of a multibyte character.  */
#define nextc_is_1stbyte (cur_char_ring[cur_ring_idx] == 1)
#else /* MBS_SUPPORT */
/* a dummy */
#define nextc_is_1stbyte 1
#endif /* MBS_SUPPORT */

/* getfname --- return name of a builtin function (for pretty printing) */

const char *
getfname(NODE *(*fptr)(int))
{
	int i, j;

	j = sizeof(tokentab) / sizeof(tokentab[0]);
	/* linear search, no other way to do it */
	for (i = 0; i < j; i++) 
		if (tokentab[i].ptr == fptr)
			return tokentab[i].operator;

	return NULL;
}

/* negate_num --- negate a number in NODE */

void
negate_num(NODE *n)
{
#ifdef HAVE_MPFR
	if (is_mpg_float(n)) {
		int tval;
		tval = mpfr_neg(n->mpg_numbr, n->mpg_numbr, ROUND_MODE);
		IEEE_FMT(n->mpg_numbr, tval);
	} else if (is_mpg_integer(n)) {
		mpz_neg(n->mpg_i, n->mpg_i);
	} else
#endif
		n->numbr = -n->numbr;
}

/* print_included_from --- print `Included from ..' file names and locations */

static void
print_included_from()
{
	int saveline, line;
	SRCFILE *s;

	/* suppress current file name, line # from `.. included from ..' msgs */ 
	saveline = sourceline;
	sourceline = 0;

	for (s = sourcefile; s != NULL && s->stype == SRC_INC; ) {
		s = s->next;
		if (s == NULL || s->fd <= INVALID_HANDLE)
			continue;
		line = s->srclines;

		/* if last token is NEWLINE, line number is off by 1. */
		if (s->lasttok == NEWLINE)
			line--;
		msg("%s %s:%d%c",
			s->prev == sourcefile ? "In file included from"
					  : "                 from",
			(s->stype == SRC_INC ||
				 s->stype == SRC_FILE) ? s->src : "cmd. line",
			line,
			s->stype == SRC_INC ? ',' : ':'
		);
	}
	sourceline = saveline;
}

/* warning_ln --- print a warning message with location */

static void
warning_ln(int line, const char *mesg, ...)
{
	va_list args;
	int saveline;

	saveline = sourceline;
	sourceline = line;
	print_included_from();
	va_start(args, mesg);
	err(false, _("warning: "), mesg, args);
	va_end(args);
	sourceline = saveline;
}

/* lintwarn_ln --- print a lint warning and location */

static void
lintwarn_ln(int line, const char *mesg, ...)
{
	va_list args;
	int saveline;

	saveline = sourceline;
	sourceline = line;
	print_included_from();
	va_start(args, mesg);
	if (lintfunc == r_fatal)
		err(true, _("fatal: "), mesg, args);
	else
		err(false, _("warning: "), mesg, args);
	va_end(args);
	sourceline = saveline;
	if (lintfunc == r_fatal)
		gawk_exit(EXIT_FATAL);
}

/* error_ln --- print an error message and location */

static void
error_ln(int line, const char *m, ...)
{
	va_list args;
	int saveline;

	saveline = sourceline;
	sourceline = line;
	print_included_from();
	errcount++;
	va_start(args, m);
	err(false, "error: ", m, args);
	va_end(args);
	sourceline = saveline;
}

/* yyerror --- print a syntax error message, show where */

static void
yyerror(const char *m, ...)
{
	va_list args;
	const char *mesg = NULL;
	char *bp, *cp;
	char *scan;
	char *buf;
	int count;
	static char end_of_file_line[] = "(END OF FILE)";
	char save;

	print_included_from();

	errcount++;
	/* Find the current line in the input file */
	if (lexptr && lexeme) {
		if (thisline == NULL) {
			cp = lexeme;
			if (*cp == '\n') {
				cp--;
				mesg = _("unexpected newline or end of string");
			}
			for (; cp != lexptr_begin && *cp != '\n'; --cp)
				continue;
			if (*cp == '\n')
				cp++;
			thisline = cp;
		}
		/* NL isn't guaranteed */
		bp = lexeme;
		while (bp < lexend && *bp && *bp != '\n')
			bp++;
	} else {
		thisline = end_of_file_line;
		bp = thisline + strlen(thisline);
	}

	/*
	 * Saving and restoring *bp keeps valgrind happy,
	 * since the guts of glibc uses strlen, even though
	 * we're passing an explict precision. Sigh.
	 *
	 * 8/2003: We may not need this anymore.
	 */
	save = *bp;
	*bp = '\0';

	msg("%.*s", (int) (bp - thisline), thisline);

	*bp = save;
	va_start(args, m);
	if (mesg == NULL)
		mesg = m;

	count = (bp - thisline) + strlen(mesg) + 2 + 1;
	emalloc(buf, char *, count, "yyerror");

	bp = buf;

	if (lexptr != NULL) {
		scan = thisline;
		while (scan < lexeme)
			if (*scan++ == '\t')
				*bp++ = '\t';
			else
				*bp++ = ' ';
		*bp++ = '^';
		*bp++ = ' ';
	}
	strcpy(bp, mesg);
	err(false, "", buf, args);
	va_end(args);
	efree(buf);
}

/* mk_program --- create a single list of instructions */

static INSTRUCTION *
mk_program()
{
	INSTRUCTION *cp, *tmp;

#define begin_block         rule_block[BEGIN]
#define end_block           rule_block[END]
#define prog_block          rule_block[Rule]
#define beginfile_block     rule_block[BEGINFILE]
#define endfile_block       rule_block[ENDFILE]

	if (end_block == NULL)
		end_block = list_create(ip_end);
	else
		(void) list_prepend(end_block, ip_end);

	if (! in_main_context()) {
		if (begin_block != NULL && prog_block != NULL)
			cp = list_merge(begin_block, prog_block);
		else
			cp = (begin_block != NULL) ? begin_block : prog_block;

		if (cp != NULL)
			(void) list_merge(cp, end_block);
		else
			cp = end_block;

		(void) list_append(cp, instruction(Op_stop));
		goto out;
	}

	if (endfile_block == NULL)
		endfile_block = list_create(ip_endfile);
	else {
		ip_rec->has_endfile = true;
		(void) list_prepend(endfile_block, ip_endfile);
	}

	if (beginfile_block == NULL)
		beginfile_block = list_create(ip_beginfile);
	else
		(void) list_prepend(beginfile_block, ip_beginfile);

	if (prog_block == NULL) {
		if (end_block->nexti == end_block->lasti
				&& beginfile_block->nexti == beginfile_block->lasti 
				&& endfile_block->nexti == endfile_block->lasti
		) {
			/* no pattern-action and (real) end, beginfile or endfile blocks */
			bcfree(ip_rec);
			bcfree(ip_newfile);
			ip_rec = ip_newfile = NULL;

			list_append(beginfile_block, instruction(Op_after_beginfile));
			(void) list_append(endfile_block, instruction(Op_after_endfile));

			if (begin_block == NULL)     /* no program at all */
				cp = end_block;
			else
				cp = list_merge(begin_block, end_block);
			(void) list_append(cp, ip_atexit);
			(void) list_append(cp, instruction(Op_stop));

			/* append beginfile_block and endfile_block for sole use
			 * in getline without redirection (Op_K_getline).
			 */

			(void) list_merge(cp, beginfile_block);
			(void) list_merge(cp, endfile_block);

			goto out;

		} else {
			/* install a do-nothing prog block */
			prog_block = list_create(instruction(Op_no_op));
		}
	}

	(void) list_append(endfile_block, instruction(Op_after_endfile));
	(void) list_prepend(prog_block, ip_rec);
	(void) list_append(prog_block, instruction(Op_jmp));
	prog_block->lasti->target_jmp = ip_rec;
		
	list_append(beginfile_block, instruction(Op_after_beginfile));

	cp = list_merge(beginfile_block, prog_block);
	(void) list_prepend(cp, ip_newfile);
	(void) list_merge(cp, endfile_block);
	(void) list_merge(cp, end_block);
	if (begin_block != NULL)
		cp = list_merge(begin_block, cp);

	(void) list_append(cp, ip_atexit);
	(void) list_append(cp, instruction(Op_stop));

out:
	/* delete the Op_list, not needed */
	tmp = cp->nexti;
	bcfree(cp);
	return tmp;

#undef begin_block
#undef end_block
#undef prog_block
#undef beginfile_block
#undef endfile_block 
}

/* parse_program --- read in the program and convert into a list of instructions */

int
parse_program(INSTRUCTION **pcode)
{
	int ret;

	/* pre-create non-local jump targets
	 * ip_end (Op_no_op) -- used as jump target for `exit'
	 * outside an END block.
	 */
	ip_end = instruction(Op_no_op);

	if (! in_main_context())
		ip_newfile = ip_rec = ip_atexit = ip_beginfile = ip_endfile = NULL;
	else {
		ip_endfile = instruction(Op_no_op);
		ip_beginfile = instruction(Op_no_op);
		ip_rec = instruction(Op_get_record); /* target for `next', also ip_newfile */
		ip_newfile = bcalloc(Op_newfile, 2, 0); /* target for `nextfile' */
		ip_newfile->target_jmp = ip_end;
		ip_newfile->target_endfile = ip_endfile;
		(ip_newfile + 1)->target_get_record = ip_rec;
		ip_rec->target_newfile = ip_newfile;
		ip_atexit = instruction(Op_atexit);	/* target for `exit' in END block */
	}

	for (sourcefile = srcfiles->next; sourcefile->stype == SRC_EXTLIB;
			sourcefile = sourcefile->next)
		;

	lexeof = false;
	lexptr = NULL;
	lasttok = 0;
	memset(rule_block, 0, sizeof(ruletab) * sizeof(INSTRUCTION *));
	errcount = 0;
	tok = tokstart != NULL ? tokstart : tokexpand();

	ret = yyparse();
	*pcode = mk_program();

	/* avoid false source indications */
	source = NULL;
	sourceline = 0;
	if (ret == 0)	/* avoid spurious warning if parser aborted with YYABORT */
		check_funcs();

	if (args_array == NULL)
		emalloc(args_array, NODE **, (max_args + 2) * sizeof(NODE *), "parse_program");
	else
		erealloc(args_array, NODE **, (max_args + 2) * sizeof(NODE *), "parse_program");

	return (ret || errcount);
}

/* do_add_srcfile --- add one item to srcfiles */

static SRCFILE *
do_add_srcfile(int stype, char *src, char *path, SRCFILE *thisfile)
{
	SRCFILE *s;

	emalloc(s, SRCFILE *, sizeof(SRCFILE), "do_add_srcfile");
	memset(s, 0, sizeof(SRCFILE));
	s->src = estrdup(src, strlen(src));
	s->fullpath = path;
	s->stype = stype;
	s->fd = INVALID_HANDLE;
	s->next = thisfile;
	s->prev = thisfile->prev;
	thisfile->prev->next = s;
	thisfile->prev = s;
	return s;
}

/* add_srcfile --- add one item to srcfiles after checking if
 *				a source file exists and not already in list.
 */

SRCFILE *
add_srcfile(int stype, char *src, SRCFILE *thisfile, bool *already_included, int *errcode)
{
	SRCFILE *s;
	struct stat sbuf;
	char *path;
	int errno_val = 0;

	if (already_included)
		*already_included = false;
	if (errcode)
		*errcode = 0;
	if (stype == SRC_CMDLINE || stype == SRC_STDIN)
		return do_add_srcfile(stype, src, NULL, thisfile);

	path = find_source(src, & sbuf, &errno_val, stype == SRC_EXTLIB);
	if (path == NULL) {
		if (errcode) {
			*errcode = errno_val;
			return NULL;
		}
		/* use full messages to ease translation */
		fatal(stype != SRC_EXTLIB
			? _("can't open source file `%s' for reading (%s)")
			: _("can't open shared library `%s' for reading (%s)"),
				src,
				errno_val ? strerror(errno_val) : _("reason unknown"));
	}

	/* N.B. We do not eliminate duplicate SRC_FILE (-f) programs. */
	for (s = srcfiles->next; s != srcfiles; s = s->next) {
		if ((s->stype == SRC_FILE || s->stype == SRC_INC || s->stype == SRC_EXTLIB) && files_are_same(path, s)) {
			if (stype == SRC_INC || stype == SRC_EXTLIB) {
				/* eliminate duplicates */
				if ((stype == SRC_INC) && (s->stype == SRC_FILE))
					fatal(_("can't include `%s' and use it as a program file"), src);

				if (do_lint) {
					int line = sourceline;
					/* Kludge: the line number may be off for `@include file'.
					 * Since, this function is also used for '-f file' in main.c,
					 * sourceline > 1 check ensures that the call is at
					 * parse time.
					 */
					if (sourceline > 1 && lasttok == NEWLINE)
						line--;
					lintwarn_ln(line,
						    stype != SRC_EXTLIB
						      ? _("already included source file `%s'")
						      : _("already loaded shared library `%s'"),
						    src);
				}
				efree(path);
				if (already_included)
					*already_included = true;
				return NULL;
			} else {
				/* duplicates are allowed for -f */ 
				if (s->stype == SRC_INC)
					fatal(_("can't include `%s' and use it as a program file"), src);
				/* no need to scan for further matches, since
				 * they must be of homogeneous type */
				break;
			}
		}
	}

	s = do_add_srcfile(stype, src, path, thisfile);
	s->sbuf = sbuf;
	s->mtime = sbuf.st_mtime;
	return s;
}

/* include_source --- read program from source included using `@include' */

static int
include_source(INSTRUCTION *file)
{
	SRCFILE *s;
	char *src = file->lextok;
	int errcode;
	bool already_included;

	if (do_traditional || do_posix) {
		error_ln(file->source_line, _("@include is a gawk extension"));
		return -1;
	}

	if (strlen(src) == 0) {
		if (do_lint)
			lintwarn_ln(file->source_line, _("empty filename after @include"));
		return 0;
	}

	s = add_srcfile(SRC_INC, src, sourcefile, &already_included, &errcode);
	if (s == NULL) {
		if (already_included)
			return 0;
		error_ln(file->source_line,
			_("can't open source file `%s' for reading (%s)"),
			src, errcode ? strerror(errcode) : _("reason unknown"));
		return -1;
	}

	/* save scanner state for the current sourcefile */
	sourcefile->srclines = sourceline;
	sourcefile->lexptr = lexptr;
	sourcefile->lexend = lexend;
	sourcefile->lexptr_begin = lexptr_begin;        
	sourcefile->lexeme = lexeme;
	sourcefile->lasttok = lasttok;

	/* included file becomes the current source */ 
	sourcefile = s;
	lexptr = NULL;
	sourceline = 0;
	source = NULL;
	lasttok = 0;
	lexeof = false;
	eof_warned = false;
	return 0;
}

/* load_library --- load a shared library */

static int
load_library(INSTRUCTION *file)
{
	SRCFILE *s;
	char *src = file->lextok;
	int errcode;
	bool already_included;

	if (do_traditional || do_posix) {
		error_ln(file->source_line, _("@load is a gawk extension"));
		return -1;
	}

	if (strlen(src) == 0) {
		if (do_lint)
			lintwarn_ln(file->source_line, _("empty filename after @load"));
		return 0;
	}

	s = add_srcfile(SRC_EXTLIB, src, sourcefile, &already_included, &errcode);
	if (s == NULL) {
		if (already_included)
			return 0;
		error_ln(file->source_line,
			_("can't open shared library `%s' for reading (%s)"),
			src, errcode ? strerror(errcode) : _("reason unknown"));
		return -1;
	}

	load_ext(s->fullpath);
	return 0;
}

/* next_sourcefile --- read program from the next source in srcfiles */

static void
next_sourcefile()
{
	static int (*closefunc)(int fd) = NULL;

	if (closefunc == NULL) {
		char *cp = getenv("AWKREADFUNC");

		/* If necessary, one day, test value for different functions.  */
		if (cp == NULL)
			closefunc = close;
		else
			closefunc = one_line_close;
	}

	/*
	 * This won't be true if there's an invalid character in
	 * the source file or source string (e.g., user typo).
	 * Previous versions of gawk did not core dump in such a
	 * case.
	 *
	 * assert(lexeof == true);
	 */

	lexeof = false;
	eof_warned = false;
	sourcefile->srclines = sourceline;	/* total no of lines in current file */
	if (sourcefile->fd > INVALID_HANDLE) {
		if (sourcefile->fd != fileno(stdin))  /* safety */
			(*closefunc)(sourcefile->fd);
		sourcefile->fd = INVALID_HANDLE;
	}
	if (sourcefile->buf != NULL) {
		efree(sourcefile->buf);
		sourcefile->buf = NULL;
		sourcefile->lexptr_begin = NULL;
	}

	while ((sourcefile = sourcefile->next) != NULL) {
		if (sourcefile == srcfiles)
			return;
		if (sourcefile->stype != SRC_EXTLIB)
			break;
	}

	if (sourcefile->lexptr_begin != NULL) {
		/* resume reading from already opened file (postponed to process '@include') */
		lexptr = sourcefile->lexptr;
		lexend = sourcefile->lexend;
		lasttok = sourcefile->lasttok;
		lexptr_begin = sourcefile->lexptr_begin;
		lexeme = sourcefile->lexeme;
		sourceline = sourcefile->srclines;
		source = sourcefile->src;
	} else {
		lexptr = NULL;
		sourceline = 0;
		source = NULL;
		lasttok = 0;
	}
}

/* get_src_buf --- read the next buffer of source program */

static char *
get_src_buf()
{
	int n;
	char *scan;
	bool newfile;
	int savelen;
	struct stat sbuf;

	/*
	 * No argument prototype on readfunc on purpose,
	 * avoids problems with some ancient systems where
	 * the types of arguments to read() aren't up to date.
	 */
	static ssize_t (*readfunc)() = 0;

	if (readfunc == NULL) {
		char *cp = getenv("AWKREADFUNC");

		/* If necessary, one day, test value for different functions.  */
		if (cp == NULL)
			/*
			 * cast is to remove warnings on systems with
			 * different return types for read.
			 */
			readfunc = ( ssize_t(*)() ) read;
		else
			readfunc = read_one_line;
	}

	newfile = false;
	if (sourcefile == srcfiles)
		return NULL;

	if (sourcefile->stype == SRC_CMDLINE) {
		if (sourcefile->bufsize == 0) {
			sourcefile->bufsize = strlen(sourcefile->src);
			lexptr = lexptr_begin = lexeme = sourcefile->src;
			lexend = lexptr + sourcefile->bufsize;
			sourceline = 1;
			if (sourcefile->bufsize == 0) {
				/*
				 * Yet Another Special case:
				 *	gawk '' /path/name
				 * Sigh.
				 */
				static bool warned = false;

				if (do_lint && ! warned) {
					warned = true;
					lintwarn(_("empty program text on command line"));
				}
				lexeof = true;
			}
		} else if (sourcefile->buf == NULL  && *(lexptr-1) != '\n') {
			/*
			 * The following goop is to ensure that the source
			 * ends with a newline and that the entire current
			 * line is available for error messages.
			 */
			int offset;
			char *buf;

			offset = lexptr - lexeme;
			for (scan = lexeme; scan > lexptr_begin; scan--)
				if (*scan == '\n') {
					scan++;
					break;
				}
			savelen = lexptr - scan;
			emalloc(buf, char *, savelen + 1, "get_src_buf");
			memcpy(buf, scan, savelen);
			thisline = buf;
			lexptr = buf + savelen;
			*lexptr = '\n';
			lexeme = lexptr - offset;
			lexptr_begin = buf;
			lexend = lexptr + 1;
			sourcefile->buf = buf;
		} else
			lexeof = true;
		return lexptr;
	}

	if (sourcefile->fd <= INVALID_HANDLE) {
		int fd;
		int l;

		source = sourcefile->src;
		if (source == NULL)
			return NULL;
		fd = srcopen(sourcefile);
		if (fd <= INVALID_HANDLE) {
			char *in;

			/* suppress file name and line no. in error mesg */
			in = source;
			source = NULL;
			error(_("can't open source file `%s' for reading (%s)"),
				in, strerror(errno));
			errcount++;
			lexeof = true;
			return sourcefile->src;
		}

		sourcefile->fd = fd;
		l = optimal_bufsize(fd, &sbuf);
		/*
		 * Make sure that something silly like
		 * 	AWKBUFSIZE=8 make check
		 * works ok.
		 */
#define A_DECENT_BUFFER_SIZE	128
		if (l < A_DECENT_BUFFER_SIZE)
			l = A_DECENT_BUFFER_SIZE;
#undef A_DECENT_BUFFER_SIZE
		sourcefile->bufsize = l;
		newfile = true;
		emalloc(sourcefile->buf, char *, sourcefile->bufsize, "get_src_buf");
		lexptr = lexptr_begin = lexeme = sourcefile->buf;
		savelen = 0;
		sourceline = 1;
		thisline = NULL;
	} else {
		/*
		 * Here, we retain the current source line in the beginning of the buffer.
		 */
		int offset;
		for (scan = lexeme; scan > lexptr_begin; scan--)
			if (*scan == '\n') {
				scan++;
				break;
			}

		savelen = lexptr - scan;
		offset = lexptr - lexeme;

		if (savelen > 0) {
			/*
			 * Need to make sure we have room left for reading new text;
			 * grow the buffer (by doubling, an arbitrary choice), if the retained line
			 * takes up more than a certain percentage (50%, again an arbitrary figure)
			 * of the available space.
			 */

			if (savelen > sourcefile->bufsize / 2) { /* long line or token  */
				sourcefile->bufsize *= 2;
				erealloc(sourcefile->buf, char *, sourcefile->bufsize, "get_src_buf");
				scan = sourcefile->buf + (scan - lexptr_begin);
				lexptr_begin = sourcefile->buf;
			}

			thisline = lexptr_begin;
			memmove(thisline, scan, savelen);
			lexptr = thisline + savelen;
			lexeme = lexptr - offset;
		} else {
			savelen = 0;
			lexptr = lexeme = lexptr_begin;
			thisline = NULL;
		}
	}

	n = (*readfunc)(sourcefile->fd, lexptr, sourcefile->bufsize - savelen);
	if (n == -1) {
		error(_("can't read sourcefile `%s' (%s)"),
				source, strerror(errno));
		errcount++;
		lexeof = true;
	} else {
		lexend = lexptr + n;
		if (n == 0) {
			static bool warned = false;
			if (do_lint && newfile && ! warned){
				warned = true;
				sourceline = 0;
				lintwarn(_("source file `%s' is empty"), source);
			}
			lexeof = true;
		}
	}
	return sourcefile->buf;
}

/* tokadd --- add a character to the token buffer */

#define	tokadd(x) (*tok++ = (x), tok == tokend ? tokexpand() : tok)

/* tokexpand --- grow the token buffer */

static char *
tokexpand()
{
	static int toksize;
	int tokoffset;
			
	if (tokstart != NULL) {
		tokoffset = tok - tokstart;
		toksize *= 2;
		erealloc(tokstart, char *, toksize, "tokexpand");
		tok = tokstart + tokoffset;
	} else {
		toksize = 60;
		emalloc(tokstart, char *, toksize, "tokexpand");
		tok = tokstart;
	}
	tokend = tokstart + toksize;
	return tok;
}

/* nextc --- get the next input character */

#if MBS_SUPPORT

static int
nextc(void)
{
	if (gawk_mb_cur_max > 1) {
again:
		if (lexeof)
			return END_FILE;
		if (lexptr == NULL || lexptr >= lexend) {
			if (get_src_buf())
				goto again;
			return END_SRC;
		}

		/* Update the buffer index.  */
		cur_ring_idx = (cur_ring_idx == RING_BUFFER_SIZE - 1)? 0 :
			cur_ring_idx + 1;

		/* Did we already check the current character?  */
		if (cur_char_ring[cur_ring_idx] == 0) {
			/* No, we need to check the next character on the buffer.  */
			int idx, work_ring_idx = cur_ring_idx;
			mbstate_t tmp_state;
			size_t mbclen;
	
			for (idx = 0 ; lexptr + idx < lexend ; idx++) {
				tmp_state = cur_mbstate;
				mbclen = mbrlen(lexptr, idx + 1, &tmp_state);

				if (mbclen == 1 || mbclen == (size_t)-1 || mbclen == 0) {
					/* It is a singlebyte character, non-complete multibyte
					   character or EOF.  We treat it as a singlebyte
					   character.  */
					cur_char_ring[work_ring_idx] = 1;
					break;
				} else if (mbclen == (size_t)-2) {
					/* It is not a complete multibyte character.  */
					cur_char_ring[work_ring_idx] = idx + 1;
				} else {
					/* mbclen > 1 */
					cur_char_ring[work_ring_idx] = mbclen;
					break;
				}
				work_ring_idx = (work_ring_idx == RING_BUFFER_SIZE - 1)?
					0 : work_ring_idx + 1;
			}
			cur_mbstate = tmp_state;

			/* Put a mark on the position on which we write next character.  */
			work_ring_idx = (work_ring_idx == RING_BUFFER_SIZE - 1)?
				0 : work_ring_idx + 1;
			cur_char_ring[work_ring_idx] = 0;
		}

		return (int) (unsigned char) *lexptr++;
	} else {
		do {
			if (lexeof)
				return END_FILE;
			if (lexptr && lexptr < lexend)
					return ((int) (unsigned char) *lexptr++);
		} while (get_src_buf());
		return END_SRC;
	}
}

#else /* MBS_SUPPORT */

int
nextc()
{
	do {
		if (lexeof)
			return END_FILE;
		if (lexptr && lexptr < lexend)
			return ((int) (unsigned char) *lexptr++);
	} while (get_src_buf());
	return END_SRC;
}

#endif /* MBS_SUPPORT */

/* pushback --- push a character back on the input */

static inline void
pushback(void)
{
#if MBS_SUPPORT
	if (gawk_mb_cur_max > 1)
		cur_ring_idx = (cur_ring_idx == 0)? RING_BUFFER_SIZE - 1 :
			cur_ring_idx - 1;
#endif
	(! lexeof && lexptr && lexptr > lexptr_begin ? lexptr-- : lexptr);
}


/* allow_newline --- allow newline after &&, ||, ? and : */

static void
allow_newline(void)
{
	int c;

	for (;;) {
		c = nextc();
		if (c == END_FILE) {
			pushback();
			break;
		}
		if (c == '#') {
			while ((c = nextc()) != '\n' && c != END_FILE)
				continue;
			if (c == END_FILE) {
				pushback();
				break;
			}
		}
		if (c == '\n')
			sourceline++;
		if (! isspace(c)) {
			pushback();
			break;
		}
	}
}

/* newline_eof --- return newline or EOF as needed and adjust variables */

/*
 * This routine used to be a macro, however GCC 4.6.2 warned about
 * the result of a computation not being used.  Converting to a function
 * removes the warnings.
 */

static int newline_eof()
{
	/* NB: a newline at end does not start a source line. */
	if (lasttok != NEWLINE) {
                pushback();
		if (do_lint && ! eof_warned) {
        		lintwarn(_("source file does not end in newline"));
			eof_warned = true;
		}
		sourceline++;
		return NEWLINE;
	}

	sourceline--;
	eof_warned = false;
	return LEX_EOF;
}

/* yylex --- Read the input and turn it into tokens. */

static int
yylex(void)
{
	int c;
	bool seen_e = false;		/* These are for numbers */
	bool seen_point = false;
	bool esc_seen;		/* for literal strings */
	int mid;
	int base;
	static bool did_newline = false;
	char *tokkey;
	bool inhex = false;
	bool intlstr = false;
	AWKNUM d;

#define GET_INSTRUCTION(op) bcalloc(op, 1, sourceline)

#define NEWLINE_EOF newline_eof()

	yylval = (INSTRUCTION *) NULL;
	if (lasttok == SUBSCRIPT) {
		lasttok = 0;
		return SUBSCRIPT;
	}
 
	if (lasttok == LEX_EOF)		/* error earlier in current source, must give up !! */
		return 0;

	c = nextc();
	if (c == END_SRC)
		return 0;
	if (c == END_FILE)
		return lasttok = NEWLINE_EOF;
	pushback();

#if defined __EMX__
	/*
	 * added for OS/2's extproc feature of cmd.exe
	 * (like #! in BSD sh)
	 */
	if (strncasecmp(lexptr, "extproc ", 8) == 0) {
		while (*lexptr && *lexptr != '\n')
			lexptr++;
	}
#endif

	lexeme = lexptr;
	thisline = NULL;
	if (want_regexp) {
		int in_brack = 0;	/* count brackets, [[:alnum:]] allowed */
		/*
		 * Counting brackets is non-trivial. [[] is ok,
		 * and so is [\]], with a point being that /[/]/ as a regexp
		 * constant has to work.
		 *
		 * Do not count [ or ] if either one is preceded by a \.
		 * A `[' should be counted if
		 *  a) it is the first one so far (in_brack == 0)
		 *  b) it is the `[' in `[:'
		 * A ']' should be counted if not preceded by a \, since
		 * it is either closing `:]' or just a plain list.
		 * According to POSIX, []] is how you put a ] into a set.
		 * Try to handle that too.
		 *
		 * The code for \ handles \[ and \].
		 */

		want_regexp = false;
		tok = tokstart;
		for (;;) {
			c = nextc();

			if (gawk_mb_cur_max == 1 || nextc_is_1stbyte) switch (c) {
			case '[':
				/* one day check for `.' and `=' too */
				if (nextc() == ':' || in_brack == 0)
					in_brack++;
				pushback();
				break;
			case ']':
				if (tokstart[0] == '['
				    && (tok == tokstart + 1
					|| (tok == tokstart + 2
					    && tokstart[1] == '^')))
					/* do nothing */;
				else
					in_brack--;
				break;
			case '\\':
				if ((c = nextc()) == END_FILE) {
					pushback();
					yyerror(_("unterminated regexp ends with `\\' at end of file"));
					goto end_regexp; /* kludge */
				} else if (c == '\n') {
					sourceline++;
					continue;
				} else {
					tokadd('\\');
					tokadd(c);
					continue;
				}
				break;
			case '/':	/* end of the regexp */
				if (in_brack > 0)
					break;
end_regexp:
				yylval = GET_INSTRUCTION(Op_token);
				yylval->lextok = estrdup(tokstart, tok - tokstart);
				if (do_lint) {
					int peek = nextc();

					pushback();
					if (peek == 'i' || peek == 's') {
						if (source)
							lintwarn(
						_("%s: %d: tawk regex modifier `/.../%c' doesn't work in gawk"),
								source, sourceline, peek);
						else
							lintwarn(
						_("tawk regex modifier `/.../%c' doesn't work in gawk"),
								peek);
					}
				}
				return lasttok = REGEXP;
			case '\n':
				pushback();
				yyerror(_("unterminated regexp"));
				goto end_regexp;	/* kludge */
			case END_FILE:
				pushback();
				yyerror(_("unterminated regexp at end of file"));
				goto end_regexp;	/* kludge */
			}
			tokadd(c);
		}
	}
retry:

	/* skipping \r is a hack, but windows is just too pervasive. sigh. */
	while ((c = nextc()) == ' ' || c == '\t' || c == '\r')
		continue;

	lexeme = lexptr ? lexptr - 1 : lexptr;
	thisline = NULL;
	tok = tokstart;

#if MBS_SUPPORT
	if (gawk_mb_cur_max == 1 || nextc_is_1stbyte)
#endif
	switch (c) {
	case END_SRC:
		return 0;

	case END_FILE:
		return lasttok = NEWLINE_EOF;

	case '\n':
		sourceline++;
		return lasttok = NEWLINE;

	case '#':		/* it's a comment */
		while ((c = nextc()) != '\n') {
			if (c == END_FILE)
				return lasttok = NEWLINE_EOF;
		}
		sourceline++;
		return lasttok = NEWLINE;

	case '@':
		return lasttok = '@';

	case '\\':
#ifdef RELAXED_CONTINUATION
		/*
		 * This code puports to allow comments and/or whitespace
		 * after the `\' at the end of a line used for continuation.
		 * Use it at your own risk. We think it's a bad idea, which
		 * is why it's not on by default.
		 */
		if (! do_traditional) {
			/* strip trailing white-space and/or comment */
			while ((c = nextc()) == ' ' || c == '\t' || c == '\r')
				continue;
			if (c == '#') {
				static bool warned = false;

				if (do_lint && ! warned) {
					warned = true;
					lintwarn(
		_("use of `\\ #...' line continuation is not portable"));
				}
				while ((c = nextc()) != '\n')
					if (c == END_FILE)
						break;
			}
			pushback();
		}
#endif /* RELAXED_CONTINUATION */
		c = nextc();
		if (c == '\r')	/* allow MS-DOS files. bleah */
			c = nextc();
		if (c == '\n') {
			sourceline++;
			goto retry;
		} else {
			yyerror(_("backslash not last character on line"));
			return lasttok = LEX_EOF;
		}
		break;

	case ':':
	case '?':
		yylval = GET_INSTRUCTION(Op_cond_exp);
		if (! do_posix)
			allow_newline();
		return lasttok = c;

		/*
		 * in_parens is undefined unless we are parsing a print
		 * statement (in_print), but why bother with a check?
		 */
	case ')':
		in_parens--;
		return lasttok = c;

	case '(':	
		in_parens++;
		return lasttok = c;
	case '$':
		yylval = GET_INSTRUCTION(Op_field_spec);
		return lasttok = c;
	case '{':
		if (++in_braces == 1)
			firstline = sourceline;
	case ';':
	case ',':
	case '[':
			return lasttok = c;
	case ']':
		c = nextc();
		pushback();
		if (c == '[') {
			yylval = GET_INSTRUCTION(Op_sub_array);
			lasttok = ']';
		} else {
			yylval = GET_INSTRUCTION(Op_subscript);
			lasttok = SUBSCRIPT;	/* end of subscripts */
		}
		return ']';

	case '*':
		if ((c = nextc()) == '=') {
			yylval = GET_INSTRUCTION(Op_assign_times);
			return lasttok = ASSIGNOP;
		} else if (do_posix) {
			pushback();
			yylval = GET_INSTRUCTION(Op_times);
			return lasttok = '*';
		} else if (c == '*') {
			/* make ** and **= aliases for ^ and ^= */
			static bool did_warn_op = false, did_warn_assgn = false;

			if (nextc() == '=') {
				if (! did_warn_assgn) {
					did_warn_assgn = true;
					if (do_lint)
						lintwarn(_("POSIX does not allow operator `**='"));
					if (do_lint_old)
						warning(_("old awk does not support operator `**='"));
				}
				yylval = GET_INSTRUCTION(Op_assign_exp);
				return ASSIGNOP;
			} else {
				pushback();
				if (! did_warn_op) {
					did_warn_op = true;
					if (do_lint)
						lintwarn(_("POSIX does not allow operator `**'"));
					if (do_lint_old)
						warning(_("old awk does not support operator `**'"));
				}
				yylval = GET_INSTRUCTION(Op_exp);
				return lasttok = '^';
			}
		}
		pushback();
		yylval = GET_INSTRUCTION(Op_times);
		return lasttok = '*';

	case '/':
		if (nextc() == '=') {
			pushback();
			return lasttok = SLASH_BEFORE_EQUAL;
		}
		pushback();
		yylval = GET_INSTRUCTION(Op_quotient);
		return lasttok = '/';

	case '%':
		if (nextc() == '=') {
			yylval = GET_INSTRUCTION(Op_assign_mod);
			return lasttok = ASSIGNOP;
		}
		pushback();
		yylval = GET_INSTRUCTION(Op_mod);
		return lasttok = '%';

	case '^':
	{
		static bool did_warn_op = false, did_warn_assgn = false;

		if (nextc() == '=') {
			if (do_lint_old && ! did_warn_assgn) {
				did_warn_assgn = true;
				warning(_("operator `^=' is not supported in old awk"));
			}
			yylval = GET_INSTRUCTION(Op_assign_exp);
			return lasttok = ASSIGNOP;
		}
		pushback();
		if (do_lint_old && ! did_warn_op) {
			did_warn_op = true;
			warning(_("operator `^' is not supported in old awk"));
		}
		yylval = GET_INSTRUCTION(Op_exp);	
		return lasttok = '^';
	}

	case '+':
		if ((c = nextc()) == '=') {
			yylval = GET_INSTRUCTION(Op_assign_plus);
			return lasttok = ASSIGNOP;
		}
		if (c == '+') {
			yylval = GET_INSTRUCTION(Op_symbol);
			return lasttok = INCREMENT;
		}
		pushback();
		yylval = GET_INSTRUCTION(Op_plus);
		return lasttok = '+';

	case '!':
		if ((c = nextc()) == '=') {
			yylval = GET_INSTRUCTION(Op_notequal);
			return lasttok = RELOP;
		}
		if (c == '~') {
			yylval = GET_INSTRUCTION(Op_nomatch);
			return lasttok = MATCHOP;
		}
		pushback();
		yylval = GET_INSTRUCTION(Op_symbol);
		return lasttok = '!';

	case '<':
		if (nextc() == '=') {
			yylval = GET_INSTRUCTION(Op_leq);
			return lasttok = RELOP;
		}
		yylval = GET_INSTRUCTION(Op_less);
		pushback();
		return lasttok = '<';

	case '=':
		if (nextc() == '=') {
			yylval = GET_INSTRUCTION(Op_equal);
			return lasttok = RELOP;
		}
		yylval = GET_INSTRUCTION(Op_assign);
		pushback();
		return lasttok = ASSIGN;

	case '>':
		if ((c = nextc()) == '=') {
			yylval = GET_INSTRUCTION(Op_geq);
			return lasttok = RELOP;
		} else if (c == '>') {
			yylval = GET_INSTRUCTION(Op_symbol);
			yylval->redir_type = redirect_append;
			return lasttok = IO_OUT;
		}
		pushback();
		if (in_print && in_parens == 0) {
			yylval = GET_INSTRUCTION(Op_symbol);
			yylval->redir_type = redirect_output;
			return lasttok = IO_OUT;
		}
		yylval = GET_INSTRUCTION(Op_greater);
		return lasttok = '>';

	case '~':
		yylval = GET_INSTRUCTION(Op_match);
		return lasttok = MATCHOP;

	case '}':
		/*
		 * Added did newline stuff.  Easier than
		 * hacking the grammar.
		 */
		if (did_newline) {
			did_newline = false;
			if (--in_braces == 0)
				lastline = sourceline;
			return lasttok = c;
		}
		did_newline++;
		--lexptr;	/* pick up } next time */
		return lasttok = NEWLINE;

	case '"':
	string:
		esc_seen = false;
		while ((c = nextc()) != '"') {
			if (c == '\n') {
				pushback();
				yyerror(_("unterminated string"));
				return lasttok = LEX_EOF;
			}
			if ((gawk_mb_cur_max == 1 || nextc_is_1stbyte) &&
			    c == '\\') {
				c = nextc();
				if (c == '\n') {
					sourceline++;
					continue;
				}
				esc_seen = true;
				if (! want_source || c != '"')
					tokadd('\\');
			}
			if (c == END_FILE) {
				pushback();
				yyerror(_("unterminated string"));
				return lasttok = LEX_EOF;
			}
			tokadd(c);
		}
		yylval = GET_INSTRUCTION(Op_token);
		if (want_source) {
			yylval->lextok = estrdup(tokstart, tok - tokstart);
			return lasttok = FILENAME;
		}
		
		yylval->opcode = Op_push_i;
		yylval->memory = make_str_node(tokstart,
					tok - tokstart, esc_seen ? SCAN : 0);
		if (intlstr) {
			yylval->memory->flags |= INTLSTR;
			intlstr = false;
			if (do_intl)
				dumpintlstr(yylval->memory->stptr, yylval->memory->stlen);
		}
		return lasttok = YSTRING;

	case '-':
		if ((c = nextc()) == '=') {
			yylval = GET_INSTRUCTION(Op_assign_minus);
			return lasttok = ASSIGNOP;
		}
		if (c == '-') {
			yylval = GET_INSTRUCTION(Op_symbol);
			return lasttok = DECREMENT;
		}
		pushback();
		yylval = GET_INSTRUCTION(Op_minus);
		return lasttok = '-';

	case '.':
		c = nextc();
		pushback();
		if (! isdigit(c))
			return lasttok = '.';
		else
			c = '.';
		/* FALL THROUGH */
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
		/* It's a number */
		for (;;) {
			bool gotnumber = false;

			tokadd(c);
			switch (c) {
			case 'x':
			case 'X':
				if (do_traditional)
					goto done;
				if (tok == tokstart + 2) {
					int peek = nextc();

					if (isxdigit(peek)) {
						inhex = true;
						pushback();	/* following digit */
					} else {
						pushback();	/* x or X */
						goto done;
					}
				}
				break;
			case '.':
				/* period ends exponent part of floating point number */
				if (seen_point || seen_e) {
					gotnumber = true;
					break;
				}
				seen_point = true;
				break;
			case 'e':
			case 'E':
				if (inhex)
					break;
				if (seen_e) {
					gotnumber = true;
					break;
				}
				seen_e = true;
				if ((c = nextc()) == '-' || c == '+') {
					int c2 = nextc();

					if (isdigit(c2)) {
						tokadd(c);
						tokadd(c2);
					} else {
						pushback();	/* non-digit after + or - */
						pushback();	/* + or - */
						pushback();	/* e or E */
					}
				} else if (! isdigit(c)) {
					pushback();	/* character after e or E */
					pushback();	/* e or E */
				} else {
					pushback();	/* digit */
				}
				break;
			case 'a':
			case 'A':
			case 'b':
			case 'B':
			case 'c':
			case 'C':
			case 'D':
			case 'd':
			case 'f':
			case 'F':
				if (do_traditional || ! inhex)
					goto done;
				/* fall through */
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
			done:
				gotnumber = true;
			}
			if (gotnumber)
				break;
			c = nextc();
		}
		pushback();

		tokadd('\0');
		yylval = GET_INSTRUCTION(Op_push_i);

		base = 10;
		if (! do_traditional) {
			base = get_numbase(tokstart, false);
			if (do_lint) {
				if (base == 8)
					lintwarn("numeric constant `%.*s' treated as octal",
						(int) strlen(tokstart)-1, tokstart);
				else if (base == 16)
					lintwarn("numeric constant `%.*s' treated as hexadecimal",
						(int) strlen(tokstart)-1, tokstart);
			}
		}

#ifdef HAVE_MPFR
		if (do_mpfr) {
			NODE *r;

			if (! seen_point && ! seen_e) {
				r = mpg_integer();
				mpg_strtoui(r->mpg_i, tokstart, strlen(tokstart), NULL, base);
				errno = 0;
			} else {
				int tval;
				r = mpg_float();
				tval = mpfr_strtofr(r->mpg_numbr, tokstart, NULL, base, ROUND_MODE);
				errno = 0;
				IEEE_FMT(r->mpg_numbr, tval);
			}
			yylval->memory = r;
			return lasttok = YNUMBER;
		}
#endif
		if (base != 10)
			d = nondec2awknum(tokstart, strlen(tokstart));
		else
			d = atof(tokstart);
		yylval->memory = make_number(d);
		if (d <= INT32_MAX && d >= INT32_MIN && d == (int32_t) d)
			yylval->memory->flags |= NUMINT;
		return lasttok = YNUMBER;

	case '&':
		if ((c = nextc()) == '&') {
			yylval = GET_INSTRUCTION(Op_and);
			allow_newline();
			return lasttok = LEX_AND;
		}
		pushback();
		yylval = GET_INSTRUCTION(Op_symbol);
		return lasttok = '&';

	case '|':
		if ((c = nextc()) == '|') {
			yylval = GET_INSTRUCTION(Op_or);
			allow_newline();
			return lasttok = LEX_OR;
		} else if (! do_traditional && c == '&') {
			yylval = GET_INSTRUCTION(Op_symbol);
			yylval->redir_type = redirect_twoway;
			return lasttok = (in_print && in_parens == 0 ? IO_OUT : IO_IN);
		}
		pushback();
		if (in_print && in_parens == 0) {
			yylval = GET_INSTRUCTION(Op_symbol);
			yylval->redir_type = redirect_pipe;
			return lasttok = IO_OUT;
		} else {
			yylval = GET_INSTRUCTION(Op_symbol);
			yylval->redir_type = redirect_pipein;
			return lasttok = IO_IN;
		}
	}

	if (c != '_' && ! isalpha(c)) {
		yyerror(_("invalid char '%c' in expression"), c);
		return lasttok = LEX_EOF;
	}

	/*
	 * Lots of fog here.  Consider:
	 *
	 * print "xyzzy"$_"foo"
	 *
	 * Without the check for ` lasttok != '$' ', this is parsed as
	 *
	 * print "xxyzz" $(_"foo")
	 *
	 * With the check, it is "correctly" parsed as three
	 * string concatenations.  Sigh.  This seems to be
	 * "more correct", but this is definitely one of those
	 * occasions where the interactions are funny.
	 */
	if (! do_traditional && c == '_' && lasttok != '$') {
		if ((c = nextc()) == '"') {
			intlstr = true;
			goto string;
		}
		pushback();
		c = '_';
	}

	/* it's some type of name-type-thing.  Find its length. */
	tok = tokstart;
	while (c != END_FILE && is_identchar(c)) {
		tokadd(c);
		c = nextc();
	}
	tokadd('\0');
	pushback();

	/* See if it is a special token. */
	if ((mid = check_special(tokstart)) >= 0) {
		static int warntab[sizeof(tokentab) / sizeof(tokentab[0])];
		int class = tokentab[mid].class;

		if ((class == LEX_INCLUDE || class == LEX_LOAD || class == LEX_EVAL)
				&& lasttok != '@')
			goto out;

		if (do_lint) {
			if ((tokentab[mid].flags & GAWKX) != 0 && (warntab[mid] & GAWKX) == 0) {
				lintwarn(_("`%s' is a gawk extension"),
					tokentab[mid].operator);
				warntab[mid] |= GAWKX;
			}
			if ((tokentab[mid].flags & NOT_POSIX) != 0 && (warntab[mid] & NOT_POSIX) == 0) {
				lintwarn(_("POSIX does not allow `%s'"),
					tokentab[mid].operator);
				warntab[mid] |= NOT_POSIX;
			}
		}
		if (do_lint_old && (tokentab[mid].flags & NOT_OLD) != 0
				 && (warntab[mid] & NOT_OLD) == 0
		) {
			warning(_("`%s' is not supported in old awk"),
					tokentab[mid].operator);
			warntab[mid] |= NOT_OLD;
		}

		if ((tokentab[mid].flags & BREAK) != 0)
			break_allowed++;
		if ((tokentab[mid].flags & CONTINUE) != 0)
			continue_allowed++;

		switch (class) {
		case LEX_INCLUDE:
		case LEX_LOAD:
			want_source = true;
			break;
		case LEX_EVAL:
			if (in_main_context())
				goto out;
			emalloc(tokkey, char *, tok - tokstart + 1, "yylex");
			tokkey[0] = '@';
			memcpy(tokkey + 1, tokstart, tok - tokstart);
			yylval = GET_INSTRUCTION(Op_token);
			yylval->lextok = tokkey;
			break;

		case LEX_FUNCTION:
		case LEX_BEGIN:
		case LEX_END:
		case LEX_BEGINFILE:
		case LEX_ENDFILE:		
			yylval = bcalloc(tokentab[mid].value, 3, sourceline);
			break;

		case LEX_FOR:
		case LEX_WHILE:
		case LEX_DO:
		case LEX_SWITCH:
			if (! do_pretty_print)
				return lasttok = class;
			/* fall through */
		case LEX_CASE:
			yylval = bcalloc(tokentab[mid].value, 2, sourceline);
			break;

		/*
		 * These must be checked here, due to the LALR nature of the parser,
		 * the rules for continue and break may not be reduced until after
		 * a token that increments the xxx_allowed varibles is seen. Bleah.
		 */
		case LEX_CONTINUE:
			if (! continue_allowed) {
				error_ln(sourceline,
					_("`continue' is not allowed outside a loop"));
				errcount++;
			}
			goto make_instruction;

		case LEX_BREAK:
			if (! break_allowed) {
				error_ln(sourceline,
					_("`break' is not allowed outside a loop or switch"));
				errcount++;
			}
			goto make_instruction;

		default:
make_instruction:
			yylval = GET_INSTRUCTION(tokentab[mid].value);
			if (class == LEX_BUILTIN || class == LEX_LENGTH)
				yylval->builtin_idx = mid;
			break;
		}
		return lasttok = class;
	}
out:
	tokkey = estrdup(tokstart, tok - tokstart);
	if (*lexptr == '(') {
		yylval = bcalloc(Op_token, 2, sourceline);
		yylval->lextok = tokkey;	
		return lasttok = FUNC_CALL;
	} else {
		static bool goto_warned = false;

		yylval = GET_INSTRUCTION(Op_token);
		yylval->lextok = tokkey;

#define SMART_ALECK	1
		if (SMART_ALECK && do_lint
		    && ! goto_warned && strcasecmp(tokkey, "goto") == 0) {
			goto_warned = true;
			lintwarn(_("`goto' considered harmful!\n"));
		}
		return lasttok = NAME;
	}

#undef GET_INSTRUCTION
#undef NEWLINE_EOF
}

/* snode --- instructions for builtin functions. Checks for arg. count
             and supplies defaults where possible. */

static INSTRUCTION *
snode(INSTRUCTION *subn, INSTRUCTION *r)
{
	INSTRUCTION *arg;
	INSTRUCTION *ip;
	NODE *n;
	int nexp = 0;
	int args_allowed;
	int idx = r->builtin_idx;

	if (subn != NULL) {
		INSTRUCTION *tp;
		for (tp = subn->nexti; tp; tp = tp->nexti) {
			tp = tp->lasti;
			nexp++;
		}
		assert(nexp > 0);
	}		

	/* check against how many args. are allowed for this builtin */
	args_allowed = tokentab[idx].flags & ARGS;
	if (args_allowed && (args_allowed & A(nexp)) == 0) {
		yyerror(_("%d is invalid as number of arguments for %s"),
				nexp, tokentab[idx].operator);
		return NULL;
	}

	/* special processing for sub, gsub and gensub */

	if (tokentab[idx].value == Op_sub_builtin) {
		const char *operator = tokentab[idx].operator;

		r->sub_flags = 0;

		arg = subn->nexti;		/* first arg list */
		(void) mk_rexp(arg);

		if (strcmp(operator, "gensub") != 0) {
			/* sub and gsub */

			if (strcmp(operator, "gsub") == 0)
				r->sub_flags |= GSUB;

			arg = arg->lasti->nexti;	/* 2nd arg list */
			if (nexp == 2) {
				INSTRUCTION *expr;

				expr = list_create(instruction(Op_push_i));
				expr->nexti->memory = make_number(0.0);
				(void) mk_expression_list(subn,
						list_append(expr, instruction(Op_field_spec)));
			}

			arg = arg->lasti->nexti; 	/* third arg list */
			ip = arg->lasti;
			if (ip->opcode == Op_push_i) {
				if (do_lint)
					lintwarn(_("%s: string literal as last arg of substitute has no effect"),
						operator);
				r->sub_flags |=	LITERAL;
			} else {
				if (make_assignable(ip) == NULL)
					yyerror(_("%s third parameter is not a changeable object"),
						operator);
				else
					ip->do_reference = true;
			}

			r->expr_count = count_expressions(&subn, false);
			ip = subn->lasti;

			(void) list_append(subn, r);

			/* add after_assign code */
			if (ip->opcode == Op_push_lhs && ip->memory->type == Node_var && ip->memory->var_assign) {
				(void) list_append(subn, instruction(Op_var_assign));
				subn->lasti->assign_ctxt = Op_sub_builtin;
				subn->lasti->assign_var = ip->memory->var_assign;
			} else if (ip->opcode == Op_field_spec_lhs) {
				(void) list_append(subn, instruction(Op_field_assign));
				subn->lasti->assign_ctxt = Op_sub_builtin;
				subn->lasti->field_assign = (Func_ptr) 0;
				ip->target_assign = subn->lasti;
			} else if (ip->opcode == Op_subscript_lhs) {
				(void) list_append(subn, instruction(Op_subscript_assign));
				subn->lasti->assign_ctxt = Op_sub_builtin;
			}

			return subn;	

		} else {
			/* gensub */

			r->sub_flags |= GENSUB;
			if (nexp == 3) {
				ip = instruction(Op_push_i);
				ip->memory = make_number(0.0);
				(void) mk_expression_list(subn,
						list_append(list_create(ip), instruction(Op_field_spec)));
			}

			r->expr_count = count_expressions(&subn, false);
			return list_append(subn, r);
		}
	}

#ifdef HAVE_MPFR
	/* N.B.: There isn't any special processing for an alternate function below */
	if (do_mpfr && tokentab[idx].ptr2)
		r->builtin =  tokentab[idx].ptr2;
	else
#endif
		r->builtin = tokentab[idx].ptr;

	/* special case processing for a few builtins */

	if (r->builtin == do_length) {
		if (nexp == 0) {		
		    /* no args. Use $0 */

			INSTRUCTION *list;
			r->expr_count = 1;			
			list = list_create(r);
			(void) list_prepend(list, instruction(Op_field_spec));
			(void) list_prepend(list, instruction(Op_push_i));
			list->nexti->memory = make_number(0.0);
			return list; 
		} else {
			arg = subn->nexti;
			if (arg->nexti == arg->lasti && arg->nexti->opcode == Op_push)
				arg->nexti->opcode = Op_push_arg;	/* argument may be array */
 		}
	} else if (r->builtin == do_isarray) {
		arg = subn->nexti;
		if (arg->nexti == arg->lasti && arg->nexti->opcode == Op_push)
			arg->nexti->opcode = Op_push_arg;	/* argument may be array */
	} else if (r->builtin == do_match) {
		static bool warned = false;

		arg = subn->nexti->lasti->nexti;	/* 2nd arg list */
		(void) mk_rexp(arg);

		if (nexp == 3) {	/* 3rd argument there */
			if (do_lint && ! warned) {
				warned = true;
				lintwarn(_("match: third argument is a gawk extension"));
			}
			if (do_traditional) {
				yyerror(_("match: third argument is a gawk extension"));
				return NULL;
			}

			arg = arg->lasti->nexti; 	/* third arg list */
			ip = arg->lasti;
			if (/*ip == arg->nexti  && */ ip->opcode == Op_push)
				ip->opcode = Op_push_array;
		}
	} else if (r->builtin == do_split) {
		arg = subn->nexti->lasti->nexti;	/* 2nd arg list */
		ip = arg->lasti;
		if (ip->opcode == Op_push)
			ip->opcode = Op_push_array;
		if (nexp == 2) {
			INSTRUCTION *expr;
			expr = list_create(instruction(Op_push));
			expr->nexti->memory = FS_node;
			(void) mk_expression_list(subn, expr);
		}
		arg = arg->lasti->nexti;
		n = mk_rexp(arg);
		if (nexp == 2)
			n->re_flags |= FS_DFLT;
		if (nexp == 4) {
			arg = arg->lasti->nexti;
			ip = arg->lasti;
			if (ip->opcode == Op_push)
				ip->opcode = Op_push_array;
		}
	} else if (r->builtin == do_patsplit) {
		arg = subn->nexti->lasti->nexti;	/* 2nd arg list */
		ip = arg->lasti;
		if (ip->opcode == Op_push)
			ip->opcode = Op_push_array;
		if (nexp == 2) {
			INSTRUCTION *expr;
			expr = list_create(instruction(Op_push));
			expr->nexti->memory = FPAT_node;
			(void) mk_expression_list(subn, expr);
		}
		arg = arg->lasti->nexti;
		n = mk_rexp(arg);
		if (nexp == 4) {
			arg = arg->lasti->nexti;
			ip = arg->lasti;
			if (ip->opcode == Op_push)
				ip->opcode = Op_push_array;
		}
	} else if (r->builtin == do_close) {
		static bool warned = false;
		if (nexp == 2) {
			if (do_lint && ! warned) {
				warned = true;
				lintwarn(_("close: second argument is a gawk extension"));
			}
			if (do_traditional) {
				yyerror(_("close: second argument is a gawk extension"));
				return NULL;
			}
		}
	} else if (do_intl					/* --gen-po */
			&& r->builtin == do_dcgettext		/* dcgettext(...) */
			&& subn->nexti->lasti->opcode == Op_push_i	/* 1st arg is constant */
			&& (subn->nexti->lasti->memory->flags & STRCUR) != 0) {	/* it's a string constant */
		/* ala xgettext, dcgettext("some string" ...) dumps the string */
		NODE *str = subn->nexti->lasti->memory;

		if ((str->flags & INTLSTR) != 0)
			warning(_("use of dcgettext(_\"...\") is incorrect: remove leading underscore"));
			/* don't dump it, the lexer already did */
		else
			dumpintlstr(str->stptr, str->stlen);
	} else if (do_intl					/* --gen-po */
			&& r->builtin == do_dcngettext		/* dcngettext(...) */
			&& subn->nexti->lasti->opcode == Op_push_i	/* 1st arg is constant */
			&& (subn->nexti->lasti->memory->flags & STRCUR) != 0	/* it's a string constant */
			&& subn->nexti->lasti->nexti->lasti->opcode == Op_push_i	/* 2nd arg is constant too */
			&& (subn->nexti->lasti->nexti->lasti->memory->flags & STRCUR) != 0) {	/* it's a string constant */
		/* ala xgettext, dcngettext("some string", "some plural" ...) dumps the string */
		NODE *str1 = subn->nexti->lasti->memory;
		NODE *str2 = subn->nexti->lasti->nexti->lasti->memory;

		if (((str1->flags | str2->flags) & INTLSTR) != 0)
			warning(_("use of dcngettext(_\"...\") is incorrect: remove leading underscore"));
		else
			dumpintlstr2(str1->stptr, str1->stlen, str2->stptr, str2->stlen);
	} else if (r->builtin == do_asort || r->builtin == do_asorti) {
		arg = subn->nexti;	/* 1st arg list */
		ip = arg->lasti;
		if (ip->opcode == Op_push)
			ip->opcode = Op_push_array;
		if (nexp >= 2) {
			arg = ip->nexti;
			ip = arg->lasti;
			if (ip->opcode == Op_push)
				ip->opcode = Op_push_array;
		}
	}
	else if (r->builtin == do_index) {
		arg = subn->nexti->lasti->nexti;	/* 2nd arg list */
		ip = arg->lasti;
		if (ip->opcode == Op_match_rec)
			fatal(_("index: regexp constant as second argument is not allowed"));
	}
#ifdef ARRAYDEBUG
	else if (r->builtin == do_adump) {
		ip = subn->nexti->lasti;
		if (ip->opcode == Op_push)
			ip->opcode = Op_push_array;
	}
#endif

	if (subn != NULL) {
		r->expr_count = count_expressions(&subn, false);
		return list_append(subn, r);
	}

	r->expr_count = 0;
	return list_create(r);
}


/* parms_shadow --- check if parameters shadow globals */

static int
parms_shadow(INSTRUCTION *pc, bool *shadow)
{
	int pcount, i;
	bool ret = false;
	NODE *func, *fp;
	char *fname;

	func = pc->func_body;
	fname = func->vname;
	fp = func->fparms;

#if 0	/* can't happen, already exited if error ? */
	if (fname == NULL || func == NULL)	/* error earlier */
		return false;
#endif

	pcount = func->param_cnt;

	if (pcount == 0)		/* no args, no problem */
		return 0;

	source = pc->source_file;
	sourceline = pc->source_line;
	/*
	 * Use warning() and not lintwarn() so that can warn
	 * about all shadowed parameters.
	 */
	for (i = 0; i < pcount; i++) {
		if (lookup(fp[i].param) != NULL) {
			warning(
	_("function `%s': parameter `%s' shadows global variable"),
					fname, fp[i].param);
			ret = true;
		}
	}

	*shadow |= ret;
	return 0;
}

/* valinfo --- dump var info */

void
valinfo(NODE *n, Func_print print_func, FILE *fp)
{
	if (n == Nnull_string)
		print_func(fp, "uninitialized scalar\n");
	else if (n->flags & STRING) {
		pp_string_fp(print_func, fp, n->stptr, n->stlen, '"', false);
		print_func(fp, "\n");
	} else if (n->flags & NUMBER) {
#ifdef HAVE_MPFR
		if (is_mpg_float(n))
			print_func(fp, "%s\n", mpg_fmt("%.17R*g", ROUND_MODE, n->mpg_numbr));
		else if (is_mpg_integer(n))
			print_func(fp, "%s\n", mpg_fmt("%Zd", n->mpg_i));
		else
#endif
		print_func(fp, "%.17g\n", n->numbr);
	} else if (n->flags & STRCUR) {
		pp_string_fp(print_func, fp, n->stptr, n->stlen, '"', false);
		print_func(fp, "\n");
	} else if (n->flags & NUMCUR) {
#ifdef HAVE_MPFR
		if (is_mpg_float(n))
			print_func(fp, "%s\n", mpg_fmt("%.17R*g", ROUND_MODE, n->mpg_numbr));
		else if (is_mpg_integer(n))
			print_func(fp, "%s\n", mpg_fmt("%Zd", n->mpg_i));
		else
#endif
		print_func(fp, "%.17g\n", n->numbr);
	} else
		print_func(fp, "?? flags %s\n", flags2str(n->flags));
}


/* dump_vars --- dump the symbol table */

void
dump_vars(const char *fname)
{
	FILE *fp;
	NODE **vars;

	if (fname == NULL)
		fp = stderr;
	else if ((fp = fopen(fname, "w")) == NULL) {
		warning(_("could not open `%s' for writing (%s)"), fname, strerror(errno));
		warning(_("sending variable list to standard error"));
		fp = stderr;
	}

	vars = variable_list();
	print_vars(vars, fprintf, fp);
	efree(vars);
	if (fp != stderr && fclose(fp) != 0)
		warning(_("%s: close failed (%s)"), fname, strerror(errno));
}

/* dump_funcs --- print all functions */

void
dump_funcs()
{
	NODE **funcs;
	funcs = function_list(true);
	(void) foreach_func(funcs, (int (*)(INSTRUCTION *, void *)) pp_func, (void *) 0);
	efree(funcs);
}


/* shadow_funcs --- check all functions for parameters that shadow globals */

void
shadow_funcs()
{
	static int calls = 0;
	bool shadow = false;
	NODE **funcs;

	if (calls++ != 0)
		fatal(_("shadow_funcs() called twice!"));

	funcs = function_list(true);
	(void) foreach_func(funcs, (int (*)(INSTRUCTION *, void *)) parms_shadow, & shadow);
	efree(funcs);

	/* End with fatal if the user requested it.  */
	if (shadow && lintfunc != warning)
		lintwarn(_("there were shadowed variables."));
}


/* mk_function --- finalize function definition node; remove parameters
 *	out of the symbol table.
 */

static INSTRUCTION *
mk_function(INSTRUCTION *fi, INSTRUCTION *def)
{
	NODE *thisfunc;

	thisfunc = fi->func_body;
	assert(thisfunc != NULL);

	if (do_optimize > 1 && def->lasti->opcode == Op_pop) {
		/* tail call which does not return any value. */

		INSTRUCTION *t;

		for (t = def->nexti; t->nexti != def->lasti; t = t->nexti)
			;
		if (t->opcode == Op_func_call
		    && strcmp(t->func_name, thisfunc->vname) == 0)
			(t + 1)->tail_call = true;
	}

	/* add an implicit return at end;
	 * also used by 'return' command in debugger
	 */

	(void) list_append(def, instruction(Op_push_i));
	def->lasti->memory = dupnode(Nnull_string);
	(void) list_append(def, instruction(Op_K_return));

	if (do_pretty_print)
		(void) list_prepend(def, instruction(Op_exec_count));

	/* fi->opcode = Op_func */
	(fi + 1)->firsti = def->nexti;
	(fi + 1)->lasti = def->lasti;
	(fi + 2)->first_line = fi->source_line;
	(fi + 2)->last_line = lastline;
	fi->nexti = def->nexti;
	bcfree(def);

	(void) list_append(rule_list, fi + 1);	/* debugging */

	/* update lint table info */
	func_use(thisfunc->vname, FUNC_DEFINE);

	/* remove params from symbol table */
	remove_params(thisfunc);
	return fi;
}

/* 
 * install_function:
 * install function name in the symbol table.
 * Extra work, build up and install a list of the parameter names.
 */

static int
install_function(char *fname, INSTRUCTION *fi, INSTRUCTION *plist)
{
	NODE *r, *f;
	int pcount = 0;

	r = lookup(fname);
	if (r != NULL || is_deferred_variable(fname)) {
		error_ln(fi->source_line, _("function name `%s' previously defined"), fname);
		return -1;
	}

	if (plist != NULL)
		pcount = plist->lasti->param_count + 1;
	f = install_symbol(fname, Node_func);
	fi->func_body = f;
	f->param_cnt = pcount;
	f->code_ptr = fi;
	f->fparms = NULL; 
	if (pcount > 0) {
		char **pnames;
		pnames = check_params(fname, pcount, plist);	/* frees plist */
		f->fparms = make_params(pnames, pcount);
		efree(pnames);
		install_params(f);
	}
	return 0;
}


/* check_params --- build a list of function parameter names after
 *	making sure that the names are valid and there are no duplicates.
 */

static char **
check_params(char *fname, int pcount, INSTRUCTION *list)
{
	INSTRUCTION *p, *np;
	int i, j;
	char *name;
	char **pnames;

	assert(pcount > 0);

	emalloc(pnames, char **, pcount * sizeof(char *), "check_params");

	for (i = 0, p = list->nexti; p != NULL; i++, p = np) {
		np = p->nexti;
		name = p->lextok;
		p->lextok = NULL;

		if (strcmp(name, fname) == 0) {
			/* check for function foo(foo) { ... }.  bleah. */
			error_ln(p->source_line,
				_("function `%s': can't use function name as parameter name"), fname);
		} else if (is_std_var(name)) {
			error_ln(p->source_line,
				_("function `%s': can't use special variable `%s' as a function parameter"),
					fname, name);
		}

		/* check for duplicate parameters */
		for (j = 0; j < i; j++) {
			if (strcmp(name, pnames[j]) == 0) {
				error_ln(p->source_line,
					_("function `%s': parameter #%d, `%s', duplicates parameter #%d"),
					fname, i + 1, name, j + 1);
			}
		}

		pnames[i] = name;
		bcfree(p);
	}
	bcfree(list);

	return pnames; 
}


#ifdef HASHSIZE
undef HASHSIZE
#endif
#define HASHSIZE 1021
 
static struct fdesc {
	char *name;
	short used;
	short defined;
	short extension;
	struct fdesc *next;
} *ftable[HASHSIZE];

/* func_use --- track uses and definitions of functions */

static void
func_use(const char *name, enum defref how)
{
	struct fdesc *fp;
	int len;
	int ind;

	len = strlen(name);
	ind = hash(name, len, HASHSIZE, NULL);

	for (fp = ftable[ind]; fp != NULL; fp = fp->next) {
		if (strcmp(fp->name, name) == 0) {
			if (how == FUNC_DEFINE)
				fp->defined++;
			else if (how == FUNC_EXT) {
				fp->defined++;
				fp->extension++;
			} else
				fp->used++;
			return;
		}
	}

	/* not in the table, fall through to allocate a new one */

	emalloc(fp, struct fdesc *, sizeof(struct fdesc), "func_use");
	memset(fp, '\0', sizeof(struct fdesc));
	emalloc(fp->name, char *, len + 1, "func_use");
	strcpy(fp->name, name);
	if (how == FUNC_DEFINE)
		fp->defined++;
	else if (how == FUNC_EXT) {
		fp->defined++;
		fp->extension++;
	} else
		fp->used++;
	fp->next = ftable[ind];
	ftable[ind] = fp;
}

/* track_ext_func --- add an extension function to the table */

void
track_ext_func(const char *name)
{
	func_use(name, FUNC_EXT);
}

/* check_funcs --- verify functions that are called but not defined */

static void
check_funcs()
{
	struct fdesc *fp, *next;
	int i;

	if (! in_main_context())
		goto free_mem;
 
	for (i = 0; i < HASHSIZE; i++) {
		for (fp = ftable[i]; fp != NULL; fp = fp->next) {
#ifdef REALLYMEAN
			/* making this the default breaks old code. sigh. */
			if (fp->defined == 0 && ! fp->extension) {
				error(
		_("function `%s' called but never defined"), fp->name);
				errcount++;
			}
#else
			if (do_lint && fp->defined == 0 && ! fp->extension)
				lintwarn(
		_("function `%s' called but never defined"), fp->name);
#endif

			if (do_lint && fp->used == 0 && ! fp->extension) {
				lintwarn(_("function `%s' defined but never called directly"),
					fp->name);
			}
		}
	}

free_mem:
	/* now let's free all the memory */
	for (i = 0; i < HASHSIZE; i++) {
		for (fp = ftable[i]; fp != NULL; fp = next) {
			next = fp->next;
			efree(fp->name);
			efree(fp);
		}
		ftable[i] = NULL;
	}
}

/* param_sanity --- look for parameters that are regexp constants */

static void
param_sanity(INSTRUCTION *arglist)
{
	INSTRUCTION *argl, *arg;
	int i = 1;

	if (arglist == NULL)
		return;
	for (argl = arglist->nexti; argl; ) {
		arg = argl->lasti;
		if (arg->opcode == Op_match_rec)
			warning_ln(arg->source_line,
				_("regexp constant for parameter #%d yields boolean value"), i);
		argl = arg->nexti;
		i++;
	}
}

/* deferred variables --- those that are only defined if needed. */

/*
 * Is there any reason to use a hash table for deferred variables?  At the
 * moment, there are only 1 to 3 such variables, so it may not be worth
 * the overhead.  If more modules start using this facility, it should
 * probably be converted into a hash table.
 */

static struct deferred_variable {
	NODE *(*load_func)(void);
	struct deferred_variable *next;
	char name[1];	/* variable-length array */
} *deferred_variables;

/* register_deferred_variable --- add a var name and loading function to the list */

void
register_deferred_variable(const char *name, NODE *(*load_func)(void))
{
	struct deferred_variable *dv;
	size_t sl = strlen(name);

	emalloc(dv, struct deferred_variable *, sizeof(*dv)+sl,
		"register_deferred_variable");
	dv->load_func = load_func;
	dv->next = deferred_variables;
	memcpy(dv->name, name, sl+1);
	deferred_variables = dv;
}

/* is_deferred_variable --- check if NAME is a deferred variable */

static bool
is_deferred_variable(const char *name)
{
	struct deferred_variable *dv;
	for (dv = deferred_variables; dv != NULL; dv = dv->next)
		if (strcmp(name, dv->name) == 0)
			return true;
	return false;
}


/* variable --- make sure NAME is in the symbol table */

NODE *
variable(int location, char *name, NODETYPE type)
{
	NODE *r;

	if ((r = lookup(name)) != NULL) {
		if (r->type == Node_func || r->type == Node_ext_func )
			error_ln(location, _("function `%s' called with space between name and `(',\nor used as a variable or an array"),
				r->vname);
		if (r == symbol_table)
			symtab_used = true;
	} else {
		/* not found */
		struct deferred_variable *dv;

		for (dv = deferred_variables; true; dv = dv->next) {
			if (dv == NULL) {
				/*
				 * This is the only case in which we may not free the string.
				 */
				return install_symbol(name, type);
			}
			if (strcmp(name, dv->name) == 0) {
				r = (*dv->load_func)();
				break;
			}
		}
	}
	efree(name);
	return r;
}

/* process_deferred --- if the program uses SYMTAB, load deferred variables */

static void
process_deferred()
{
	struct deferred_variable *dv;

	if (! symtab_used)
		return;

	for (dv = deferred_variables; dv != NULL; dv = dv->next) {
		(void) dv->load_func();
	}
}

/* make_regnode --- make a regular expression node */

static NODE *
make_regnode(int type, NODE *exp)
{
	NODE *n;

	getnode(n);
	memset(n, 0, sizeof(NODE));
	n->type = type;
	n->re_cnt = 1;

	if (type == Node_regex) {
		n->re_reg = make_regexp(exp->stptr, exp->stlen, false, true, false);
		if (n->re_reg == NULL) {
			freenode(n);
			return NULL;
		}
		n->re_exp = exp;
		n->re_flags = CONSTANT;
	}
	return n;
}


/* mk_rexp --- make a regular expression constant */

static NODE *
mk_rexp(INSTRUCTION *list)
{
	INSTRUCTION *ip;

	ip = list->nexti;
	if (ip == list->lasti && ip->opcode == Op_match_rec)
		ip->opcode = Op_push_re;
	else {
		ip = instruction(Op_push_re);
		ip->memory = make_regnode(Node_dynregex, NULL);
		ip->nexti = list->lasti->nexti;
		list->lasti->nexti = ip;
		list->lasti = ip;
	}
	return ip->memory;
}

#ifndef NO_LINT
/* isnoeffect --- when used as a statement, has no side effects */

static int
isnoeffect(OPCODE type)
{
	switch (type) {
	case Op_times:
	case Op_times_i:
	case Op_quotient:
	case Op_quotient_i:
	case Op_mod:
	case Op_mod_i:
	case Op_plus:
	case Op_plus_i:
	case Op_minus:
	case Op_minus_i:
	case Op_subscript:
	case Op_concat:
	case Op_exp:
	case Op_exp_i:
	case Op_unary_minus:
	case Op_field_spec:
	case Op_and_final:
	case Op_or_final:
	case Op_equal:
	case Op_notequal:
	case Op_less:
	case Op_greater:
	case Op_leq:
	case Op_geq:
	case Op_match:
	case Op_nomatch:
	case Op_match_rec:
	case Op_not:
	case Op_in_array:
		return true;
	default:
		break;	/* keeps gcc -Wall happy */
	}

	return false;
}
#endif /* NO_LINT */


/* make_assignable --- make this operand an assignable one if posiible */

static INSTRUCTION *
make_assignable(INSTRUCTION *ip)
{
	switch (ip->opcode) {
	case Op_push:
		ip->opcode = Op_push_lhs;
		return ip;
	case Op_field_spec:
		ip->opcode = Op_field_spec_lhs;
		return ip;
	case Op_subscript:
		ip->opcode = Op_subscript_lhs;
		return ip;
	default:
		break;	/* keeps gcc -Wall happy */
	}
	return NULL;
}

/* stopme --- for debugging */

NODE *
stopme(int nargs ATTRIBUTE_UNUSED)
{
	return make_number(0.0);
}

/* dumpintlstr --- write out an initial .po file entry for the string */

static void
dumpintlstr(const char *str, size_t len)
{
	char *cp;

	/* See the GNU gettext distribution for details on the file format */

	if (source != NULL) {
		/* ala the gettext sources, remove leading `./'s */
		for (cp = source; cp[0] == '.' && cp[1] == '/'; cp += 2)
			continue;
		printf("#: %s:%d\n", cp, sourceline);
	}

	printf("msgid ");
	pp_string_fp(fprintf, stdout, str, len, '"', true);
	putchar('\n');
	printf("msgstr \"\"\n\n");
	fflush(stdout);
}

/* dumpintlstr2 --- write out an initial .po file entry for the string and its plural */

static void
dumpintlstr2(const char *str1, size_t len1, const char *str2, size_t len2)
{
	char *cp;

	/* See the GNU gettext distribution for details on the file format */

	if (source != NULL) {
		/* ala the gettext sources, remove leading `./'s */
		for (cp = source; cp[0] == '.' && cp[1] == '/'; cp += 2)
			continue;
		printf("#: %s:%d\n", cp, sourceline);
	}

	printf("msgid ");
	pp_string_fp(fprintf, stdout, str1, len1, '"', true);
	putchar('\n');
	printf("msgid_plural ");
	pp_string_fp(fprintf, stdout, str2, len2, '"', true);
	putchar('\n');
	printf("msgstr[0] \"\"\nmsgstr[1] \"\"\n\n");
	fflush(stdout);
}

/* mk_binary --- instructions for binary operators */

static INSTRUCTION *
mk_binary(INSTRUCTION *s1, INSTRUCTION *s2, INSTRUCTION *op)
{
	INSTRUCTION *ip1,*ip2;
	AWKNUM res;

	ip2 = s2->nexti;
	if (s2->lasti == ip2 && ip2->opcode == Op_push_i) {
	/* do any numeric constant folding */
		ip1 = s1->nexti;
		if (do_optimize > 1
				&& ip1 == s1->lasti && ip1->opcode == Op_push_i
				&& (ip1->memory->flags & (MPFN|MPZN|STRCUR|STRING)) == 0
				&& (ip2->memory->flags & (MPFN|MPZN|STRCUR|STRING)) == 0
		) {
			NODE *n1 = ip1->memory, *n2 = ip2->memory;
			res = force_number(n1)->numbr;
			(void) force_number(n2);
			switch (op->opcode) {
			case Op_times:
				res *= n2->numbr;
				break;
			case Op_quotient:
				if (n2->numbr == 0.0) {
					/* don't fatalize, allow parsing rest of the input */
					error_ln(op->source_line, _("division by zero attempted"));
					goto regular;
				}

				res /= n2->numbr;
				break;
			case Op_mod:
				if (n2->numbr == 0.0) {
					/* don't fatalize, allow parsing rest of the input */
					error_ln(op->source_line, _("division by zero attempted in `%%'"));
					goto regular;
				}
#ifdef HAVE_FMOD
				res = fmod(res, n2->numbr);
#else	/* ! HAVE_FMOD */
				(void) modf(res / n2->numbr, &res);
				res = n1->numbr - res * n2->numbr;
#endif	/* ! HAVE_FMOD */
				break;
			case Op_plus:
				res += n2->numbr;
				break;
			case Op_minus:
				res -= n2->numbr;
				break;
			case Op_exp:
				res = calc_exp(res, n2->numbr);
				break;
			default:
				goto regular;
			}

			op->opcode = Op_push_i;
			op->memory = make_number(res);
			unref(n1);
			unref(n2);
			bcfree(ip1);
			bcfree(ip2);
			bcfree(s1);
			bcfree(s2);
			return list_create(op);
		} else {
		/* do basic arithmetic optimisation */
		/* convert (Op_push_i Node_val) + (Op_plus) to (Op_plus_i Node_val) */
			switch (op->opcode) {
			case Op_times:
				op->opcode = Op_times_i;
				break;
			case Op_quotient:
				op->opcode = Op_quotient_i;
				break;
			case Op_mod:
				op->opcode = Op_mod_i;
				break;
			case Op_plus:
				op->opcode = Op_plus_i;
				break;
			case Op_minus:
				op->opcode = Op_minus_i;
				break;
			case Op_exp:
				op->opcode = Op_exp_i;
				break;
			default:
				goto regular;
			}	

			op->memory = ip2->memory;
			bcfree(ip2);
			bcfree(s2);	/* Op_list */
			return list_append(s1, op);
		}
	}

regular:
	/* append lists s1, s2 and add `op' bytecode */
	(void) list_merge(s1, s2);
	return list_append(s1, op);
}

/* mk_boolean --- instructions for boolean and, or */
 
static INSTRUCTION *
mk_boolean(INSTRUCTION *left, INSTRUCTION *right, INSTRUCTION *op)
{
	INSTRUCTION *tp;
	OPCODE opc, final_opc;

	opc = op->opcode;		/* Op_and or Op_or */
	final_opc = (opc == Op_or) ? Op_or_final : Op_and_final;

	add_lint(right, LINT_assign_in_cond);

	tp = left->lasti;

	if (tp->opcode != final_opc) {	/* x || y */
		list_append(right, instruction(final_opc));
		add_lint(left, LINT_assign_in_cond);
		(void) list_append(left, op);
		left->lasti->target_jmp = right->lasti;

		/* NB: target_stmt points to previous Op_and(Op_or) in a chain;
		 *     target_stmt only used in the parser (see below).
		 */

		left->lasti->target_stmt = left->lasti;
		right->lasti->target_stmt = left->lasti;
	} else {		/* optimization for x || y || z || ... */
		INSTRUCTION *ip;
		
		op->opcode = final_opc;
		(void) list_append(right, op);
		op->target_stmt = tp;
		tp->opcode = opc;
		tp->target_jmp = op;

		/* update jump targets */
		for (ip = tp->target_stmt; ; ip = ip->target_stmt) {
			assert(ip->opcode == opc);
			assert(ip->target_jmp == tp);
			/* if (ip->opcode == opc &&  ip->target_jmp == tp) */
			ip->target_jmp = op;
			if (ip->target_stmt == ip)
				break;
		}
	}

	return list_merge(left, right);
}

/* mk_condition --- if-else and conditional */

static INSTRUCTION *
mk_condition(INSTRUCTION *cond, INSTRUCTION *ifp, INSTRUCTION *true_branch,
		INSTRUCTION *elsep, INSTRUCTION *false_branch)
{
	/*
	 *    ----------------
	 *       cond
	 *    ----------------
	 * t: [Op_jmp_false f ]
	 *    ----------------
	 *       true_branch
	 *
	 *    ----------------
	 *    [Op_jmp y]
	 *    ---------------- 
	 * f:
	 *      false_branch
	 *    ----------------
	 * y: [Op_no_op]
	 *    ----------------
	 */

	INSTRUCTION *ip;

	if (false_branch == NULL) {
		false_branch = list_create(instruction(Op_no_op));
		if (elsep != NULL) {		/* else { } */
			if (do_pretty_print)
				(void) list_prepend(false_branch, elsep);
			else
				bcfree(elsep);
		}
	} else {
		/* assert(elsep != NULL); */

		/* avoid a series of no_op's: if .. else if .. else if .. */
		if (false_branch->lasti->opcode != Op_no_op)
			(void) list_append(false_branch, instruction(Op_no_op));
		if (do_pretty_print) {
			(void) list_prepend(false_branch, elsep);
			false_branch->nexti->branch_end = false_branch->lasti;
			(void) list_prepend(false_branch, instruction(Op_exec_count));
		} else
			bcfree(elsep);
	}

	(void) list_prepend(false_branch, instruction(Op_jmp));
	false_branch->nexti->target_jmp = false_branch->lasti;

	add_lint(cond, LINT_assign_in_cond);
	ip = list_append(cond, instruction(Op_jmp_false));
	ip->lasti->target_jmp = false_branch->nexti->nexti;

	if (do_pretty_print) {
		(void) list_prepend(ip, ifp);
		(void) list_append(ip, instruction(Op_exec_count));
		ip->nexti->branch_if = ip->lasti;
		ip->nexti->branch_else = false_branch->nexti;
	} else
		bcfree(ifp);

	if (true_branch != NULL)
		list_merge(ip, true_branch);
	return list_merge(ip, false_branch);
}

enum defline { FIRST_LINE, LAST_LINE };

/* find_line -- find the first(last) line in a list of (pattern) instructions */

static int
find_line(INSTRUCTION *pattern, enum defline what)
{
	INSTRUCTION *ip;
	int lineno = 0;

	for (ip = pattern->nexti; ip; ip = ip->nexti) {
		if (what == LAST_LINE) {
			if (ip->source_line > lineno)
				lineno = ip->source_line;
		} else {	/* FIRST_LINE */
			if (ip->source_line > 0
					&& (lineno == 0 || ip->source_line < lineno))
				lineno = ip->source_line;
		}
		if (ip == pattern->lasti)
			break;
	}
	assert(lineno > 0);
	return lineno;
}

/* append_rule --- pattern-action instructions */

static INSTRUCTION *
append_rule(INSTRUCTION *pattern, INSTRUCTION *action)
{
	/*
	 *    ----------------
	 *       pattern
	 *    ----------------
	 *    [Op_jmp_false f ]
	 *    ----------------
	 *       action
	 *    ----------------
	 * f: [Op_no_op       ]
	 *    ----------------
	 */

	INSTRUCTION *rp;
	INSTRUCTION *tp;
	INSTRUCTION *ip;

	if (rule != Rule) {
		rp = pattern;
		if (do_pretty_print)
			(void) list_append(action, instruction(Op_no_op));
		(rp + 1)->firsti = action->nexti;
		(rp + 1)->lasti = action->lasti;
		(rp + 2)->first_line = pattern->source_line;
		(rp + 2)->last_line = lastline;
		ip = list_prepend(action, rp);

	} else {
		rp = bcalloc(Op_rule, 3, 0);
		rp->in_rule = Rule;
		rp->source_file = source;
		tp = instruction(Op_no_op);

		if (pattern == NULL) {
			/* assert(action != NULL); */
			if (do_pretty_print)
				(void) list_prepend(action, instruction(Op_exec_count));
			(rp + 1)->firsti = action->nexti;
			(rp + 1)->lasti = tp;
			(rp + 2)->first_line = firstline;
			(rp + 2)->last_line = lastline;
			rp->source_line = firstline;
			ip = list_prepend(list_append(action, tp), rp);
		} else {
			(void) list_append(pattern, instruction(Op_jmp_false));
			pattern->lasti->target_jmp = tp;
			(rp + 2)->first_line = find_line(pattern, FIRST_LINE);
			rp->source_line = (rp + 2)->first_line;
			if (action == NULL) {
				(rp + 2)->last_line = find_line(pattern, LAST_LINE);
				action = list_create(instruction(Op_K_print_rec));
				if (do_pretty_print)
					(void) list_prepend(action, instruction(Op_exec_count));
			} else
				(rp + 2)->last_line = lastline;

			if (do_pretty_print) {
				(void) list_prepend(pattern, instruction(Op_exec_count));
				(void) list_prepend(action, instruction(Op_exec_count));
			}
 			(rp + 1)->firsti = action->nexti;
			(rp + 1)->lasti = tp;
			ip = list_append(
					list_merge(list_prepend(pattern, rp),
						action),
					tp);
		}

	}

	list_append(rule_list, rp + 1);

	if (rule_block[rule] == NULL)
		rule_block[rule] = ip;
	else
		(void) list_merge(rule_block[rule], ip);
	
	return rule_block[rule];
}

/* mk_assignment --- assignment bytecodes */

static INSTRUCTION *
mk_assignment(INSTRUCTION *lhs, INSTRUCTION *rhs, INSTRUCTION *op)
{
	INSTRUCTION *tp;
	INSTRUCTION *ip;

	tp = lhs->lasti;
	switch (tp->opcode) {
	case Op_field_spec:
		tp->opcode = Op_field_spec_lhs;
		break;
	case Op_subscript:
		tp->opcode = Op_subscript_lhs;
		break;
	case Op_push:
	case Op_push_array:
		tp->opcode = Op_push_lhs; 
		break;
	default:
		cant_happen();
	}

	tp->do_reference = (op->opcode != Op_assign);	/* check for uninitialized reference */

	if (rhs != NULL)
		ip = list_merge(rhs, lhs);
	else
		ip = lhs;

	(void) list_append(ip, op);

	if (tp->opcode == Op_push_lhs
			&& tp->memory->type == Node_var
			&& tp->memory->var_assign
	) {
		tp->do_reference = false; /* no uninitialized reference checking
		                           * for a special variable.
		                           */
		(void) list_append(ip, instruction(Op_var_assign));
		ip->lasti->assign_var = tp->memory->var_assign;
	} else if (tp->opcode == Op_field_spec_lhs) {
		(void) list_append(ip, instruction(Op_field_assign));
		ip->lasti->field_assign = (Func_ptr) 0;
		tp->target_assign = ip->lasti;
	} else if (tp->opcode == Op_subscript_lhs) {
		(void) list_append(ip, instruction(Op_subscript_assign));
	}

	return ip;
}

/* optimize_assignment --- peephole optimization for assignment */

static INSTRUCTION *
optimize_assignment(INSTRUCTION *exp)
{
	INSTRUCTION *i1, *i2, *i3;

	/*
	 * Optimize assignment statements array[subs] = x; var = x; $n = x;
	 * string concatenation of the form s = s t.
	 *
	 * 1) Array element assignment array[subs] = x:
	 *   Replaces Op_push_array + Op_subscript_lhs + Op_assign + Op_pop
	 *   with single instruction Op_store_sub.
	 *	 Limitation: 1 dimension and sub is simple var/value.
	 * 
	 * 2) Simple variable assignment var = x:
	 *   Replaces Op_push_lhs + Op_assign + Op_pop with Op_store_var.
	 *
	 * 3) Field assignment $n = x:
	 *   Replaces Op_field_spec_lhs + Op_assign + Op_field_assign + Op_pop
	 *   with Op_store_field.
	 *
	 * 4) Optimization for string concatenation:
	 *   For cases like x = x y, uses realloc to include y in x;
	 *   also eliminates instructions Op_push_lhs and Op_pop.
	 */

	/*
	 * N.B.: do not append Op_pop instruction to the returned
	 * instruction list if optimized. None of these
	 * optimized instructions pushes the r-value of assignment
	 * onto the runtime stack.
	 */

	i2 = NULL;
	i1 = exp->lasti;

	if (   ! do_optimize
	    || (   i1->opcode != Op_assign
		&& i1->opcode != Op_field_assign)
	) 
		return list_append(exp, instruction(Op_pop));

	for (i2 = exp->nexti; i2 != i1; i2 = i2->nexti) {
		switch (i2->opcode) {
		case Op_concat:
			if (i2->nexti->opcode == Op_push_lhs    /* l.h.s is a simple variable */
				&& (i2->concat_flag & CSVAR)        /* 1st exp in r.h.s is a simple variable;
				                                     * see Op_concat in the grammer above.
				                                     */
				&& i2->nexti->memory == exp->nexti->memory	 /* and the same as in l.h.s */
				&& i2->nexti->nexti == i1
				&& i1->opcode == Op_assign
			) {
				/* s = s ... optimization */

				/* avoid stuff like x = x (x = y) or x = x gsub(/./, "b", x);
				 * check for l-value reference to this variable in the r.h.s.
				 * Also, avoid function calls in general to guard against
				 * global variable assignment.
				 */

				for (i3 = exp->nexti->nexti; i3 != i2; i3 = i3->nexti) {
					if ((i3->opcode == Op_push_lhs && i3->memory == i2->nexti->memory)
							|| i3->opcode == Op_func_call)
						return list_append(exp, instruction(Op_pop)); /* no optimization */
				}

				/* remove the variable from r.h.s */
				i3 = exp->nexti;
				exp->nexti = i3->nexti;
				bcfree(i3);

				if (--i2->expr_count == 1)	/* one less expression in Op_concat */
					i2->opcode = Op_no_op;

				i3 = i2->nexti;
				assert(i3->opcode == Op_push_lhs);
				i3->opcode = Op_assign_concat;	/* change Op_push_lhs to Op_assign_concat */
				i3->nexti = NULL;
				bcfree(i1);          /* Op_assign */
				exp->lasti = i3;     /* update Op_list */
				return exp;
			}
			break;

		case Op_field_spec_lhs:
			if (i2->nexti->opcode == Op_assign
					&& i2->nexti->nexti == i1
					&& i1->opcode == Op_field_assign
			) {
				/* $n = .. */
				i2->opcode = Op_store_field;
				bcfree(i2->nexti);  /* Op_assign */
				i2->nexti = NULL;
				bcfree(i1);          /* Op_field_assign */
				exp->lasti = i2;    /* update Op_list */
				return exp;
			}
			break;

		case Op_push_array:
			if (i2->nexti->nexti->opcode == Op_subscript_lhs) {
				i3 = i2->nexti->nexti;
				if (i3->sub_count == 1
						&& i3->nexti == i1
						&& i1->opcode == Op_assign
				) {
					/* array[sub] = .. */
					i3->opcode = Op_store_sub;
					i3->memory = i2->memory;
					i3->expr_count = 1;  /* sub_count shadows memory,
                                          * so use expr_count instead.
				                          */
					i3->nexti = NULL;
					i2->opcode = Op_no_op;					
					bcfree(i1);          /* Op_assign */
					exp->lasti = i3;     /* update Op_list */
					return exp;
				}
			}
			break;

		case Op_push_lhs:
			if (i2->nexti == i1
					&& i1->opcode == Op_assign
			) {
				/* var = .. */
				i2->opcode = Op_store_var;
				i2->nexti = NULL;
				bcfree(i1);          /* Op_assign */
				exp->lasti = i2;     /* update Op_list */

				i3 = exp->nexti;
				if (i3->opcode == Op_push_i
					&& (i3->memory->flags & INTLSTR) == 0
					&& i3->nexti == i2
				) {
					/* constant initializer */ 
					i2->initval = i3->memory;
					bcfree(i3);
					exp->nexti = i2;
				} else
					i2->initval = NULL;

				return exp;
			}
			break;

		default:
			break;
		}
	}

	/* no optimization  */
	return list_append(exp, instruction(Op_pop));
}


/* mk_getline --- make instructions for getline */

static INSTRUCTION *
mk_getline(INSTRUCTION *op, INSTRUCTION *var, INSTRUCTION *redir, int redirtype)
{
	INSTRUCTION *ip;
	INSTRUCTION *tp;
	INSTRUCTION *asgn = NULL;

	/*
	 *  getline [var] < [file]
	 *
	 *  [ file (simp_exp)]
	 *  [ [ var ] ]
	 *  [ Op_K_getline_redir|NULL|redir_type|into_var]
	 *  [ [var_assign] ] 
	 *
	 */

	if (redir == NULL) {
		int sline = op->source_line;
		bcfree(op);
		op = bcalloc(Op_K_getline, 2, sline);
		(op + 1)->target_endfile = ip_endfile;
		(op + 1)->target_beginfile = ip_beginfile;	
	}

	if (var != NULL) {
		tp = make_assignable(var->lasti);
		assert(tp != NULL);

		/* check if we need after_assign bytecode */
		if (tp->opcode == Op_push_lhs
				&& tp->memory->type == Node_var
				&& tp->memory->var_assign
		) {
			asgn = instruction(Op_var_assign);
			asgn->assign_ctxt = op->opcode;
			asgn->assign_var = tp->memory->var_assign;
		} else if (tp->opcode == Op_field_spec_lhs) {
			asgn = instruction(Op_field_assign);
			asgn->assign_ctxt = op->opcode;
			asgn->field_assign = (Func_ptr) 0;   /* determined at run time */
			tp->target_assign = asgn;
		} else if (tp->opcode == Op_subscript_lhs) {
			asgn = instruction(Op_subscript_assign);
			asgn->assign_ctxt = op->opcode;
		}

		if (redir != NULL) {
			ip = list_merge(redir, var);
			(void) list_append(ip, op);
		} else
			ip = list_append(var, op);
	} else if (redir != NULL)
		ip = list_append(redir, op);
	else
		ip = list_create(op);
	op->into_var = (var != NULL);
	op->redir_type = (redir != NULL) ? redirtype : redirect_none;

	return (asgn == NULL ? ip : list_append(ip, asgn));
}


/* mk_for_loop --- for loop bytecodes */

static INSTRUCTION *
mk_for_loop(INSTRUCTION *forp, INSTRUCTION *init, INSTRUCTION *cond,
				INSTRUCTION *incr, INSTRUCTION *body)
{
	/*
	 *   ------------------------
	 *        init                 (may be NULL)
	 *   ------------------------
	 * x:
	 *        cond                 (Op_no_op if NULL)
	 *   ------------------------
	 *    [ Op_jmp_false tb      ]
	 *   ------------------------
	 *        body                 (may be NULL)
	 *   ------------------------
	 * tc: 
	 *    incr                      (may be NULL)
	 *    [ Op_jmp x             ] 
	 *   ------------------------
	 * tb:[ Op_no_op             ] 
	 */

	INSTRUCTION *ip, *tbreak, *tcont;
	INSTRUCTION *jmp;
	INSTRUCTION *pp_cond;
	INSTRUCTION *ret;

	tbreak = instruction(Op_no_op);

	if (cond != NULL) {
		add_lint(cond, LINT_assign_in_cond);
		pp_cond = cond->nexti;
		ip = cond;
		(void) list_append(ip, instruction(Op_jmp_false));
		ip->lasti->target_jmp = tbreak;
	} else {
		pp_cond = instruction(Op_no_op);
		ip = list_create(pp_cond);
	}

	if (init != NULL)
		ip = list_merge(init, ip);

	if (do_pretty_print) {
		(void) list_append(ip, instruction(Op_exec_count));
		(forp + 1)->forloop_cond = pp_cond;
		(forp + 1)->forloop_body = ip->lasti;
	}

	if (body != NULL)
		(void) list_merge(ip, body);

	jmp = instruction(Op_jmp);
	jmp->target_jmp = pp_cond;
	if (incr == NULL)
		tcont = jmp;
	else {
		tcont = incr->nexti;
		(void) list_merge(ip, incr);
	}

	(void) list_append(ip, jmp);
	ret = list_append(ip, tbreak);
	fix_break_continue(ret, tbreak, tcont);

	if (do_pretty_print) {
		forp->target_break = tbreak;
		forp->target_continue = tcont;
		ret = list_prepend(ret, forp);
	} /* else
			forp is NULL */

	return ret;
}

/* add_lint --- add lint warning bytecode if needed */

static void
add_lint(INSTRUCTION *list, LINTTYPE linttype)
{
#ifndef NO_LINT
	INSTRUCTION *ip;

	switch (linttype) {
	case LINT_assign_in_cond:
		ip = list->lasti;
		if (ip->opcode == Op_var_assign || ip->opcode == Op_field_assign) {
			assert(ip != list->nexti);
			for (ip = list->nexti; ip->nexti != list->lasti; ip = ip->nexti)
				;
		}

		if (ip->opcode == Op_assign || ip->opcode == Op_assign_concat) {
			list_append(list, instruction(Op_lint));
			list->lasti->lint_type = linttype;
		}
		break;

	case LINT_no_effect:
		if (list->lasti->opcode == Op_pop && list->nexti != list->lasti) {
			for (ip = list->nexti; ip->nexti != list->lasti; ip = ip->nexti)
				;

			if (do_lint) {		/* compile-time warning */
#ifndef NO_LINT
				if (isnoeffect(ip->opcode))
					lintwarn_ln(ip->source_line, ("statement may have no effect"));
#endif
			}

			if (ip->opcode == Op_push) {		/* run-time warning */
				list_append(list, instruction(Op_lint));
				list->lasti->lint_type = linttype;
			}
		}
		break;

	default:
		break;
	}
#endif
}

/* mk_expression_list --- list of bytecode lists */

static INSTRUCTION *
mk_expression_list(INSTRUCTION *list, INSTRUCTION *s1)
{
	INSTRUCTION *r;

	/* we can't just combine all bytecodes, since we need to
	 * process individual expressions for a few builtins in snode() (-:
	 */
	
	/* -- list of lists     */
	/* [Op_list| ... ]------
	 *                       |
	 * [Op_list| ... ]   --  |
	 *  ...               |  |
	 *  ...       <-------   |
	 * [Op_list| ... ]   --  |
	 *  ...               |  |
	 *  ...               |  |
	 *  ...       <------- --
	 */

	assert(s1 != NULL && s1->opcode == Op_list);
	if (list == NULL) {
		list = instruction(Op_list);
		list->nexti = s1;
		list->lasti = s1->lasti;
		return list;
	}

	/* append expression to the end of the list */

	r = list->lasti;
	r->nexti = s1;
	list->lasti = s1->lasti;
	return list;
}

/* count_expressions --- fixup expression_list from mk_expression_list.
 *                       returns no of expressions in list. isarg is true
 *                       for function arguments.
 */

static int
count_expressions(INSTRUCTION **list, bool isarg)
{
	INSTRUCTION *expr;
	INSTRUCTION *r = NULL;
	int count = 0;

	if (*list == NULL)	/* error earlier */
		return 0;

	for (expr = (*list)->nexti; expr; ) {
		INSTRUCTION *t1, *t2;
		t1 = expr->nexti;
		t2 = expr->lasti;
		if (isarg && t1 == t2 && t1->opcode == Op_push)
			t1->opcode = Op_push_param;
		if (++count == 1)
			r = expr;
		else
			(void) list_merge(r, expr);
		expr = t2->nexti;
	}
 
	assert(count > 0);
	if (! isarg && count > max_args)
		max_args = count;
	bcfree(*list);
	*list = r;
	return count;
}

/* fix_break_continue --- fix up break & continue codes in loop bodies */

static void
fix_break_continue(INSTRUCTION *list, INSTRUCTION *b_target, INSTRUCTION *c_target)
{
	INSTRUCTION *ip;

	list->lasti->nexti = NULL;	/* just to make sure */

	for (ip = list->nexti; ip != NULL; ip = ip->nexti) {
		switch (ip->opcode) {
		case Op_K_break:
			if (ip->target_jmp == NULL)
				ip->target_jmp = b_target;
			break;

		case Op_K_continue:
			if (ip->target_jmp == NULL)
				ip->target_jmp = c_target;
			break;

		default:
			/* this is to keep the compiler happy. sheesh. */
			break;
		}
	}
}

static inline INSTRUCTION *
list_create(INSTRUCTION *x)
{
	INSTRUCTION *l;

	l = instruction(Op_list);
	l->nexti = x;
	l->lasti = x;
	return l;
}

static inline INSTRUCTION *
list_append(INSTRUCTION *l, INSTRUCTION *x)
{
#ifdef GAWKDEBUG
	if (l->opcode != Op_list)
		cant_happen();
#endif
	l->lasti->nexti = x;
	l->lasti = x;
	return l;
}

static inline INSTRUCTION *
list_prepend(INSTRUCTION *l, INSTRUCTION *x)
{
#ifdef GAWKDEBUG
	if (l->opcode != Op_list)
		cant_happen();
#endif
	x->nexti = l->nexti;
	l->nexti = x;
	return l;
}

static inline INSTRUCTION *
list_merge(INSTRUCTION *l1, INSTRUCTION *l2)
{
#ifdef GAWKDEBUG
	if (l1->opcode != Op_list)
		cant_happen();
	if (l2->opcode != Op_list)
		cant_happen();
#endif
	l1->lasti->nexti = l2->nexti;
	l1->lasti = l2->lasti;
	bcfree(l2);
	return l1;
}

/* See if name is a special token. */

int
check_special(const char *name)
{
	int low, high, mid;
	int i;
#if 'a' == 0x81 /* it's EBCDIC */
	static bool did_sort = false;

	if (! did_sort) {
		qsort((void *) tokentab,
				sizeof(tokentab) / sizeof(tokentab[0]),
				sizeof(tokentab[0]), tokcompare);
		did_sort = true;
	}
#endif

	low = 0;
	high = (sizeof(tokentab) / sizeof(tokentab[0])) - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		i = *name - tokentab[mid].operator[0];
		if (i == 0)
			i = strcmp(name, tokentab[mid].operator);

		if (i < 0)		/* token < mid */
			high = mid - 1;
		else if (i > 0)		/* token > mid */
			low = mid + 1;
		else {
			if ((do_traditional && (tokentab[mid].flags & GAWKX))
					|| (do_posix && (tokentab[mid].flags & NOT_POSIX)))
				return -1;
			return mid;
		}
	}
	return -1;
}

/*
 * This provides a private version of functions that act like VMS's
 * variable-length record filesystem, where there was a bug on
 * certain source files.
 */

static FILE *fp = NULL;

/* read_one_line --- return one input line at a time. mainly for debugging. */

static ssize_t
read_one_line(int fd, void *buffer, size_t count)
{
	char buf[BUFSIZ];

	/* Minor potential memory leak here. Too bad. */
	if (fp == NULL) {
		fp = fdopen(fd, "r");
		if (fp == NULL) {
			fprintf(stderr, "ugh. fdopen: %s\n", strerror(errno));
			gawk_exit(EXIT_FAILURE);
		}
	}

	if (fgets(buf, sizeof buf, fp) == NULL)
		return 0;

	memcpy(buffer, buf, strlen(buf));
	return strlen(buf);
}

/* one_line_close --- close the open file being read with read_one_line() */

static int
one_line_close(int fd)
{
	int ret;

	if (fp == NULL || fd != fileno(fp))
		fatal("debugging read/close screwed up!");

	ret = fclose(fp);
	fp = NULL;
	return ret;
}


