/* A Bison parser, made by GNU Bison 3.0.2.  */

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 26 "awkgram.y" /* yacc.c:339  */

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
static INSTRUCTION *mk_print(INSTRUCTION *op, INSTRUCTION *exp_list, INSTRUCTION *redir);
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
static void split_comment(void);
static void check_comment(void);

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
static bool extensions_used = false;	/* program uses extensions */

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

static INSTRUCTION *comment = NULL;
static INSTRUCTION *program_comment = NULL;
static INSTRUCTION *function_comment = NULL;
static INSTRUCTION *block_comment = NULL;

static bool func_first = true;
static bool first_rule = true;

static inline INSTRUCTION *list_create(INSTRUCTION *x);
static inline INSTRUCTION *list_append(INSTRUCTION *l, INSTRUCTION *x);
static inline INSTRUCTION *list_prepend(INSTRUCTION *l, INSTRUCTION *x);
static inline INSTRUCTION *list_merge(INSTRUCTION *l1, INSTRUCTION *l2);

extern double fmod(double x, double y);

#define YYSTYPE INSTRUCTION *

#line 211 "awkgram.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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
    LEX_PRINT_EXP = 291,
    LEX_PRINTF_EXP = 292,
    LEX_BEGINFILE = 293,
    LEX_ENDFILE = 294,
    LEX_GETLINE = 295,
    LEX_NEXTFILE = 296,
    LEX_IN = 297,
    LEX_AND = 298,
    LEX_OR = 299,
    INCREMENT = 300,
    DECREMENT = 301,
    LEX_BUILTIN = 302,
    LEX_LENGTH = 303,
    LEX_EOF = 304,
    LEX_INCLUDE = 305,
    LEX_EVAL = 306,
    LEX_LOAD = 307,
    NEWLINE = 308,
    SLASH_BEFORE_EQUAL = 309,
    UNARY = 310
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
#define LEX_PRINT_EXP 291
#define LEX_PRINTF_EXP 292
#define LEX_BEGINFILE 293
#define LEX_ENDFILE 294
#define LEX_GETLINE 295
#define LEX_NEXTFILE 296
#define LEX_IN 297
#define LEX_AND 298
#define LEX_OR 299
#define INCREMENT 300
#define DECREMENT 301
#define LEX_BUILTIN 302
#define LEX_LENGTH 303
#define LEX_EOF 304
#define LEX_INCLUDE 305
#define LEX_EVAL 306
#define LEX_LOAD 307
#define NEWLINE 308
#define SLASH_BEFORE_EQUAL 309
#define UNARY 310

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 369 "awkgram.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1356

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  68
/* YYNRULES -- Number of rules.  */
#define YYNRULES  193
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  342

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   310

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    65,     2,     2,    68,    64,     2,     2,
      69,    70,    62,    60,    57,    61,     2,    63,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    56,    76,
      58,     2,    59,    55,    71,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    72,     2,    73,    67,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    74,     2,    75,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      66
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   211,   211,   213,   218,   219,   225,   237,   241,   252,
     258,   263,   271,   279,   281,   286,   295,   297,   303,   311,
     321,   351,   365,   379,   387,   398,   410,   412,   414,   420,
     425,   426,   430,   465,   464,   498,   500,   505,   511,   539,
     544,   545,   549,   551,   553,   560,   650,   692,   734,   847,
     854,   861,   871,   880,   889,   898,   909,   925,   924,   948,
     952,   952,   967,   967,   972,   972,  1005,  1035,  1041,  1042,
    1048,  1049,  1056,  1061,  1073,  1087,  1089,  1097,  1102,  1104,
    1112,  1114,  1119,  1121,  1130,  1131,  1139,  1144,  1144,  1155,
    1159,  1167,  1168,  1171,  1173,  1178,  1179,  1188,  1189,  1194,
    1199,  1205,  1207,  1209,  1216,  1217,  1223,  1224,  1229,  1231,
    1236,  1238,  1246,  1251,  1260,  1267,  1269,  1271,  1287,  1297,
    1304,  1306,  1308,  1313,  1315,  1317,  1325,  1327,  1332,  1334,
    1339,  1341,  1343,  1393,  1395,  1397,  1399,  1401,  1403,  1405,
    1407,  1421,  1426,  1431,  1456,  1462,  1464,  1466,  1468,  1470,
    1472,  1477,  1481,  1513,  1515,  1521,  1527,  1540,  1541,  1542,
    1547,  1552,  1556,  1560,  1575,  1588,  1593,  1629,  1647,  1648,
    1654,  1655,  1660,  1662,  1669,  1686,  1703,  1705,  1712,  1717,
    1725,  1735,  1747,  1756,  1760,  1764,  1768,  1772,  1776,  1779,
    1781,  1785,  1789,  1793
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
  "LEX_FUNCTION", "LEX_PRINT_EXP", "LEX_PRINTF_EXP", "LEX_BEGINFILE",
  "LEX_ENDFILE", "LEX_GETLINE", "LEX_NEXTFILE", "LEX_IN", "LEX_AND",
  "LEX_OR", "INCREMENT", "DECREMENT", "LEX_BUILTIN", "LEX_LENGTH",
  "LEX_EOF", "LEX_INCLUDE", "LEX_EVAL", "LEX_LOAD", "NEWLINE",
  "SLASH_BEFORE_EQUAL", "'?'", "':'", "','", "'<'", "'>'", "'+'", "'-'",
  "'*'", "'/'", "'%'", "'!'", "UNARY", "'^'", "'$'", "'('", "')'", "'@'",
  "'['", "']'", "'{'", "'}'", "';'", "$accept", "program", "rule",
  "source", "library", "pattern", "action", "func_name", "lex_builtin",
  "function_prologue", "regexp", "$@1", "a_slash", "statements",
  "statement_term", "statement", "non_compound_stmt", "$@2",
  "print_expression", "$@3", "simple_stmt", "$@4", "$@5",
  "opt_simple_stmt", "case_statements", "case_statement", "case_value",
  "print", "print_exp", "print_expression_list", "output_redir", "$@6",
  "if_statement", "nls", "opt_nls", "input_redir", "opt_param_list",
  "param_list", "opt_exp", "opt_expression_list", "expression_list", "exp",
  "assign_operator", "relop_or_less", "a_relop", "common_exp", "simp_exp",
  "simp_exp_nc", "non_post_simp_exp", "func_call", "direct_func_call",
  "opt_variable", "delete_subscript_list", "delete_subscript",
  "delete_exp_list", "bracketed_exp_list", "subscript", "subscript_list",
  "simple_variable", "variable", "opt_incdec", "l_brace", "r_brace",
  "r_paren", "opt_semi", "semi", "colon", "comma", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,    63,    58,    44,    60,    62,
      43,    45,    42,    47,    37,    33,   310,    94,    36,    40,
      41,    64,    91,    93,   123,   125,    59
};
# endif

#define YYPACT_NINF -278

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-278)))

#define YYTABLE_NINF -108

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-108)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -278,   400,  -278,  -278,   -46,     5,  -278,  -278,  -278,  -278,
     151,  -278,  -278,  -278,  -278,    29,    29,    29,   -17,    22,
    -278,  -278,  -278,  1229,  1229,  -278,  1229,  1256,   962,   193,
    -278,    69,   -14,  -278,  -278,  -278,  -278,    18,   732,  1181,
     362,   395,  -278,  -278,  -278,  -278,   304,   914,   962,  -278,
       2,  -278,  -278,  -278,  -278,  -278,    37,    45,  -278,    65,
    -278,  -278,  -278,   914,   914,    67,    61,    -3,    61,    61,
    1154,    13,  -278,  -278,     9,   312,    44,    50,  -278,    77,
    -278,  -278,  -278,    18,  -278,    77,  -278,   127,   674,  -278,
    -278,  1154,   129,  1154,  1154,  1154,    77,  -278,  -278,  -278,
    1154,    97,   362,  1229,  1229,  1229,  1229,  1229,  1229,  1229,
    1229,  1229,  1229,  1229,  1229,  -278,  -278,  -278,  -278,   126,
    1154,    71,   322,   881,    10,  -278,  -278,  -278,    30,  1229,
    -278,    71,    71,   312,  -278,  -278,  -278,  1154,    77,  -278,
     102,  1010,  -278,  -278,     8,     4,  -278,    19,     4,    18,
    -278,   626,  -278,  -278,   962,   141,  -278,    17,  -278,   160,
     245,  1297,  1154,   107,    29,   186,   186,    61,    61,    61,
      61,   186,   186,    61,    61,    61,    61,  -278,   881,  -278,
    -278,  -278,  -278,    71,    28,   362,  -278,  -278,   881,  -278,
     129,  -278,   881,  -278,  -278,  -278,  -278,  -278,    81,  -278,
      12,    83,    88,    77,    89,     4,     4,  -278,  -278,     4,
    1154,     4,    77,  -278,  -278,     4,  -278,  -278,   881,  -278,
      84,    77,     9,  -278,  -278,  1154,   881,  -278,    77,  -278,
      40,  -278,  1154,  1154,  -278,   164,  1154,  1154,   818,  1058,
    -278,  -278,  -278,     4,   881,  -278,  -278,  -278,   748,   626,
      77,  -278,  -278,  -278,  1229,   881,  -278,  -278,  -278,   312,
       4,     5,    94,   312,   312,   144,     6,  -278,    84,  -278,
     141,  -278,  -278,  1181,    77,  -278,  -278,    24,  -278,  -278,
    -278,    77,    77,   104,   129,    77,  -278,   818,  -278,  -278,
     -14,   818,  1154,    71,   866,   162,  -278,  -278,   312,    77,
     242,    77,    77,    11,    77,   818,    77,  1106,   818,  -278,
     140,   115,  -278,   109,  -278,  -278,  1106,    71,  -278,  -278,
    -278,   180,   181,  -278,   115,  -278,    77,  -278,    71,    77,
    -278,  -278,    77,  -278,    77,   818,  -278,   474,   818,  -278,
     550,  -278
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     6,     0,   179,   161,   162,    21,    22,
       0,    82,    83,    23,    24,   168,     0,     0,     0,   156,
       5,    91,    36,     0,     0,    35,     0,     0,     0,     0,
       3,     0,     0,   151,    33,   122,    60,     4,    19,   121,
     130,   131,   133,   157,   165,   181,   158,     0,     0,   176,
       0,   180,    27,    26,    30,    31,     0,     0,    28,    95,
     169,   159,   160,     0,     0,     0,   164,   158,   163,   152,
       0,   185,   158,   110,     0,   108,     0,     0,   166,    93,
     191,     7,     8,    40,    37,    93,     9,     0,     0,    92,
     126,     0,     0,     0,     0,     0,    93,   127,   129,   128,
       0,     0,   132,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   124,   123,   141,   142,     0,
       0,     0,     0,   108,     0,   178,   177,    29,     0,     0,
     140,     0,     0,     0,   183,   184,   182,   111,    93,   188,
       0,     0,   153,    14,     0,     0,    17,     0,     0,    94,
     186,     0,    41,    34,     0,    86,    84,   117,   118,   115,
     116,     0,     0,   119,   168,   138,   139,   135,   136,   137,
     134,   149,   150,   146,   147,   148,   145,   125,   114,   167,
     175,   101,    99,     0,     0,    96,   154,   155,   112,   193,
       0,   113,   109,    13,    10,    16,    11,    39,     0,    57,
       0,     0,     0,    93,     0,     0,     0,    80,    81,     0,
     104,     0,    93,    38,    51,     0,    62,    44,    67,    37,
     189,    93,     0,    87,    61,     0,    20,   144,    93,   102,
       0,   143,     0,   104,    64,     0,     0,     0,     0,    68,
      52,    53,    54,     0,   105,    55,   187,    59,     0,     0,
      93,   190,    42,    85,     0,   120,    32,   103,   100,     0,
       0,   170,     0,     0,     0,     0,   179,    69,     0,    56,
      86,    43,    25,    88,    93,    58,    65,     0,   172,   174,
      66,    93,    93,     0,     0,    93,    63,     0,   171,   173,
       0,     0,     0,     0,     0,    89,    70,    46,     0,    93,
       0,    93,    93,     0,    93,     0,    93,    68,     0,    72,
       0,     0,    71,     0,    47,    48,    68,     0,    90,    75,
      78,     0,     0,    79,     0,   192,    93,    45,     0,    93,
      77,    76,    93,    37,    93,     0,    37,     0,     0,    50,
       0,    49
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -278,  -278,  -278,  -278,  -278,  -278,   159,  -278,  -278,  -278,
    -113,  -278,  -278,  -212,   -80,  -149,  -278,  -278,  -278,  -278,
    -234,  -278,  -278,  -277,  -278,  -278,  -278,  -278,  -278,   -43,
     -66,  -278,  -278,     1,    87,  -278,  -278,  -278,   -19,    -9,
     -20,    -1,  -278,  -278,  -278,   -39,   169,  -278,   194,  -278,
     -12,    56,  -278,  -278,   -54,   -44,  -278,  -278,   -73,    -2,
    -278,   -28,  -200,    46,  -278,   -30,   -98,    43
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    30,   145,   148,    31,    81,    57,    58,    32,
      33,    87,    34,   151,    82,   213,   214,   233,    35,    88,
     215,   248,   261,   268,   303,   312,   324,   216,    36,   155,
     224,   254,   217,   149,   150,   130,   183,   184,   243,   156,
     122,   218,   120,    99,   100,    39,    40,    41,    42,    43,
      44,    59,   276,   277,   278,    49,    50,    51,    45,    46,
     136,   219,   220,   142,   250,   221,   326,   141
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      38,    85,    37,    84,    84,   267,   126,   249,    74,   193,
     137,   137,   309,    60,    61,    62,   234,    78,   125,   158,
     195,    67,    67,    47,    67,    72,    90,    75,   124,   229,
     317,   181,    83,     5,   182,   310,   311,    67,   121,   328,
     288,   257,   117,   118,   258,   143,   123,   123,   284,   271,
     144,   146,    63,    78,   131,   132,   147,    21,   134,   135,
      79,   -12,   123,   123,    21,   194,   138,   138,   196,   133,
       4,    89,   -15,   267,    48,    97,    98,    48,    48,   139,
      80,   235,   267,   180,   -12,   138,   -93,   123,   127,   265,
     157,    64,   159,   160,   161,   -15,    48,    27,   -98,   163,
     -97,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,   327,   128,    85,  -108,   231,    85,   178,
     140,   337,    21,   129,   340,   240,   241,    67,   108,   242,
      21,   245,   153,     5,   222,   247,   188,   164,   295,   177,
     192,   139,   297,    79,   190,    80,    83,   319,   320,    83,
     232,   223,   236,    75,    52,    53,   315,   237,   239,   318,
      80,   226,    60,   269,   280,  -108,  -108,   179,   262,    90,
     283,   325,   152,   292,    91,    85,    85,   186,   187,    85,
     275,    85,   302,   162,   212,    85,   339,   330,   331,   341,
     251,    86,    66,    68,    22,    69,     4,   323,    54,    55,
     321,   322,    92,    25,   286,   270,    83,    83,   102,   244,
      83,   293,    83,    85,   260,   273,    83,   279,    97,    98,
     227,    71,    56,   289,   255,   189,   332,   230,     0,   228,
      85,   259,   244,   279,     0,   263,   264,     0,   285,     0,
       0,     0,     0,    76,    83,    77,     0,   123,   105,   106,
     107,    90,    67,   108,    90,     0,    91,     0,     0,    91,
       0,    83,   296,     0,   301,     0,     0,     0,   253,     0,
     306,    67,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,    92,    93,    94,    92,    93,     0,
     238,   298,     0,   300,     0,     0,     0,    95,   185,   246,
      97,    98,     0,    97,    98,   274,     0,     0,   252,   281,
     282,     0,     0,     0,     0,   256,   115,   116,    80,     0,
       0,    90,     0,   137,     0,     0,    91,     0,     0,     0,
       0,  -107,  -107,     0,     0,     0,  -107,   272,     0,   299,
       0,     0,     0,     0,   304,     0,     0,     0,     0,   117,
     118,     0,     0,     0,    92,    93,    94,     0,   119,     0,
       0,   287,     0,   329,  -107,  -107,  -107,    95,   290,   291,
      97,    98,   294,     0,   334,  -107,     0,  -107,  -107,   138,
    -107,  -107,   139,     0,     0,     0,   305,     0,   307,   308,
     313,   314,  -107,   316,     0,  -107,  -107,     0,  -107,     0,
       2,     3,     0,     4,     5,     0,     0,     6,     7,     0,
       0,     0,     0,   333,     0,     0,   335,     8,     9,   336,
       0,   338,   103,   104,   105,   106,   107,     0,     0,   108,
       0,     0,     0,     0,     0,    10,    11,    12,    13,    14,
      15,     0,   102,     0,     0,    16,    17,    18,    19,    20,
       0,     0,     0,    21,    22,   109,   110,   111,   112,   113,
      23,    24,   114,    25,     0,    26,     0,     0,    27,    28,
       0,    29,     0,     0,   -18,   197,   -18,     4,     5,     0,
       0,     6,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   198,     0,   199,   200,   201,   -74,   -74,
     202,   203,   204,   205,   206,   207,   208,   209,   210,     0,
      11,    12,     0,     0,    15,   211,     0,     0,     0,    16,
      17,    18,    19,     0,     0,     0,     0,   -74,    22,     0,
       0,     0,     0,     0,    23,    24,     0,    25,     0,    26,
       0,     0,    27,    28,     0,    65,     0,     0,    79,   -74,
      80,   197,     0,     4,     5,     0,     0,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   198,
       0,   199,   200,   201,   -73,   -73,   202,   203,   204,   205,
     206,   207,   208,   209,   210,     0,    11,    12,     0,     0,
      15,   211,     0,     0,     0,    16,    17,    18,    19,     0,
       0,     0,     0,   -73,    22,     0,     0,     0,     0,     0,
      23,    24,     0,    25,     0,    26,     0,     0,    27,    28,
       0,    65,     0,     0,    79,   -73,    80,   197,     0,     4,
       5,     0,     0,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   198,     0,   199,   200,   201,
       0,     0,   202,   203,   204,   205,   206,   207,   208,   209,
     210,     0,    11,    12,     0,     0,    15,   211,     0,     0,
       0,    16,    17,    18,    19,    73,     0,     4,     5,     0,
      22,     6,     7,  -106,  -106,     0,    23,    24,  -106,    25,
       0,    26,     0,     0,    27,    28,     0,    65,     0,     0,
      79,   212,    80,     0,     0,     0,     0,     0,     0,     0,
      11,    12,     0,     0,    15,     0,  -106,  -106,  -106,    16,
      17,    18,    19,     0,     0,     0,     0,  -106,    22,  -106,
    -106,  -106,  -106,  -106,    23,    24,     0,    25,     0,    26,
       0,    90,    27,   154,  -106,    65,    91,  -106,  -106,    73,
    -106,     4,     5,     0,     0,     6,     7,     0,  -106,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    92,    93,    94,     0,     0,     0,
       0,     0,     0,     0,    11,    12,     0,    95,    15,    96,
      97,    98,     0,    16,    17,    18,    19,     0,     0,     0,
       0,  -106,    22,     0,     0,     0,     0,     0,    23,    24,
       0,    25,     0,    26,     0,     0,    27,   154,  -106,    65,
       0,     4,     5,     0,  -106,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   198,     0,   199,
     200,   201,     0,     0,   202,   203,   204,   205,   206,   207,
     208,   209,   210,     0,    11,    12,     0,     0,    15,   211,
       0,     0,     0,    16,    17,    18,    19,     0,     0,     4,
       5,     0,    22,     6,     7,     0,     0,     0,    23,    24,
       0,    25,     0,    26,     0,     0,    27,    28,     0,    65,
      90,     0,    79,     0,    80,    91,     0,     0,     0,     0,
       0,     0,    11,    12,     0,     0,    15,     0,     0,     0,
       0,    16,    17,    18,    19,    73,     0,     4,     5,     0,
      22,     6,     7,    92,    93,    94,    23,    24,     0,    25,
       0,    26,     0,     0,    27,    28,    95,    65,     0,    97,
      98,     0,    80,     0,     0,     0,     0,     0,     0,     0,
      11,    12,     0,     0,    15,     0,     0,     0,     0,    16,
      17,    18,    19,    73,     0,     4,     5,     0,    22,     6,
       7,     0,     0,     0,    23,    24,     0,    25,     0,    26,
       0,     0,    27,    28,  -106,    65,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    11,    12,
       0,     0,    15,     0,     0,     0,     0,    16,    17,    18,
      19,   191,     0,     4,     5,     0,    22,     6,     7,     0,
       0,     0,    23,    24,     0,    25,     0,    26,     0,     0,
      27,    28,     0,    65,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    11,    12,     0,     0,
      15,     0,     0,     0,     0,    16,    17,    18,    19,     0,
       0,     4,   266,     0,    22,     6,     7,     0,     0,     0,
      23,    24,     0,    25,     0,    26,     0,     0,    27,    28,
     200,    65,     0,     0,     0,     0,     0,     0,     0,   207,
     208,     0,     0,     0,    11,    12,     0,     0,    15,     0,
       0,     0,     0,    16,    17,    18,    19,     0,     0,     4,
       5,     0,    22,     6,     7,     0,     0,     0,    23,    24,
       0,    25,     0,    26,     0,     0,    27,    28,   200,    65,
       0,     0,     0,     0,     0,     0,     0,   207,   208,     0,
       0,     0,    11,    12,     0,     0,    15,     0,     0,     0,
       0,    16,    17,    18,    19,     0,     0,     4,     5,     0,
      22,     6,     7,     0,     0,     0,    23,    24,     0,    25,
       0,    26,     0,     0,    27,    28,     0,    65,     0,     0,
       0,     0,     0,     0,     4,     5,     0,     0,     6,     7,
      11,    12,   101,     0,    15,     0,     0,     0,     0,    16,
      17,    18,    19,     0,     0,     0,     0,     0,    22,     0,
       0,     0,     0,     0,    23,    24,     0,    25,     0,    26,
       0,    15,    27,    28,     0,    65,    16,    17,    18,    19,
       0,     0,     4,     5,     0,    22,     6,     7,     0,     0,
       0,    23,    24,     0,    25,     0,    26,     0,     0,    27,
      28,     0,    65,     0,     0,     0,     0,     0,     0,     4,
       5,     0,     0,     6,     7,     0,     0,     0,     0,    15,
       0,     0,     0,     0,    16,    17,    18,    19,     0,     0,
       0,     0,     0,    22,     0,     0,     0,     0,     0,    23,
      24,     0,    25,     0,    26,     0,     0,    27,    28,     0,
      65,    16,    17,    18,    19,     0,    90,     0,     0,     0,
      22,    91,     0,     0,     0,     0,    23,    24,     0,    25,
       0,    26,     0,     0,    27,    70,     0,    65,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    92,
      93,    94,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    95,   225,     0,    97,    98
};

static const yytype_int16 yycheck[] =
{
       1,    31,     1,    31,    32,   239,    50,   219,    28,     1,
       1,     1,     1,    15,    16,    17,     4,    29,    16,    92,
       1,    23,    24,    69,    26,    27,     9,    28,    48,     1,
     307,     1,    31,     4,     4,    24,    25,    39,    47,   316,
      16,     1,    45,    46,     4,     1,    47,    48,    42,   249,
       6,     1,    69,    65,    63,    64,     6,    53,    45,    46,
      74,    53,    63,    64,    53,   145,    57,    57,   148,    70,
       3,    53,    53,   307,    72,    58,    59,    72,    72,    70,
      76,    69,   316,    73,    76,    57,    75,    88,    51,   238,
      91,    69,    93,    94,    95,    76,    72,    68,    70,   100,
      70,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   313,    69,   145,     9,   190,   148,   120,
      74,   333,    53,    58,   336,   205,   206,   129,    67,   209,
      53,   211,     5,     4,   154,   215,   137,    40,   287,    13,
     141,    70,   291,    74,    42,    76,   145,     7,     8,   148,
      69,    10,    69,   154,     3,     4,   305,    69,    69,   308,
      76,   162,   164,   243,    70,    58,    59,   121,     4,     9,
      26,    56,    85,    69,    14,   205,   206,   131,   132,   209,
     260,   211,    20,    96,    75,   215,   335,     7,     7,   338,
     220,    32,    23,    24,    54,    26,     3,   310,    47,    48,
      60,    61,    42,    63,   270,   248,   205,   206,    39,   210,
     209,   284,   211,   243,   233,   254,   215,   261,    58,    59,
     164,    27,    71,   277,   225,   138,   324,   184,    -1,   183,
     260,   232,   233,   277,    -1,   236,   237,    -1,   268,    -1,
      -1,    -1,    -1,    50,   243,    52,    -1,   248,    62,    63,
      64,     9,   254,    67,     9,    -1,    14,    -1,    -1,    14,
      -1,   260,   290,    -1,   294,    -1,    -1,    -1,   222,    -1,
     300,   273,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,    42,    43,    44,    42,    43,    -1,
     203,   292,    -1,   294,    -1,    -1,    -1,    55,   129,   212,
      58,    59,    -1,    58,    59,   259,    -1,    -1,   221,   263,
     264,    -1,    -1,    -1,    -1,   228,    12,    13,    76,    -1,
      -1,     9,    -1,     1,    -1,    -1,    14,    -1,    -1,    -1,
      -1,     9,    10,    -1,    -1,    -1,    14,   250,    -1,   293,
      -1,    -1,    -1,    -1,   298,    -1,    -1,    -1,    -1,    45,
      46,    -1,    -1,    -1,    42,    43,    44,    -1,    54,    -1,
      -1,   274,    -1,   317,    42,    43,    44,    55,   281,   282,
      58,    59,   285,    -1,   328,    53,    -1,    55,    56,    57,
      58,    59,    70,    -1,    -1,    -1,   299,    -1,   301,   302,
     303,   304,    70,   306,    -1,    73,    74,    -1,    76,    -1,
       0,     1,    -1,     3,     4,    -1,    -1,     7,     8,    -1,
      -1,    -1,    -1,   326,    -1,    -1,   329,    17,    18,   332,
      -1,   334,    60,    61,    62,    63,    64,    -1,    -1,    67,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    -1,   273,    -1,    -1,    45,    46,    47,    48,    49,
      -1,    -1,    -1,    53,    54,    60,    61,    62,    63,    64,
      60,    61,    67,    63,    -1,    65,    -1,    -1,    68,    69,
      -1,    71,    -1,    -1,    74,     1,    76,     3,     4,    -1,
      -1,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    19,    -1,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      36,    37,    -1,    -1,    40,    41,    -1,    -1,    -1,    45,
      46,    47,    48,    -1,    -1,    -1,    -1,    53,    54,    -1,
      -1,    -1,    -1,    -1,    60,    61,    -1,    63,    -1,    65,
      -1,    -1,    68,    69,    -1,    71,    -1,    -1,    74,    75,
      76,     1,    -1,     3,     4,    -1,    -1,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      -1,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    36,    37,    -1,    -1,
      40,    41,    -1,    -1,    -1,    45,    46,    47,    48,    -1,
      -1,    -1,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,
      60,    61,    -1,    63,    -1,    65,    -1,    -1,    68,    69,
      -1,    71,    -1,    -1,    74,    75,    76,     1,    -1,     3,
       4,    -1,    -1,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    -1,    21,    22,    23,
      -1,    -1,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    36,    37,    -1,    -1,    40,    41,    -1,    -1,
      -1,    45,    46,    47,    48,     1,    -1,     3,     4,    -1,
      54,     7,     8,     9,    10,    -1,    60,    61,    14,    63,
      -1,    65,    -1,    -1,    68,    69,    -1,    71,    -1,    -1,
      74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    37,    -1,    -1,    40,    -1,    42,    43,    44,    45,
      46,    47,    48,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    63,    -1,    65,
      -1,     9,    68,    69,    70,    71,    14,    73,    74,     1,
      76,     3,     4,    -1,    -1,     7,     8,    -1,    10,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    37,    -1,    55,    40,    57,
      58,    59,    -1,    45,    46,    47,    48,    -1,    -1,    -1,
      -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    63,    -1,    65,    -1,    -1,    68,    69,    70,    71,
      -1,     3,     4,    -1,    76,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    21,
      22,    23,    -1,    -1,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    -1,    36,    37,    -1,    -1,    40,    41,
      -1,    -1,    -1,    45,    46,    47,    48,    -1,    -1,     3,
       4,    -1,    54,     7,     8,    -1,    -1,    -1,    60,    61,
      -1,    63,    -1,    65,    -1,    -1,    68,    69,    -1,    71,
       9,    -1,    74,    -1,    76,    14,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    37,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,     1,    -1,     3,     4,    -1,
      54,     7,     8,    42,    43,    44,    60,    61,    -1,    63,
      -1,    65,    -1,    -1,    68,    69,    55,    71,    -1,    58,
      59,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    37,    -1,    -1,    40,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,     1,    -1,     3,     4,    -1,    54,     7,
       8,    -1,    -1,    -1,    60,    61,    -1,    63,    -1,    65,
      -1,    -1,    68,    69,    70,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,     1,    -1,     3,     4,    -1,    54,     7,     8,    -1,
      -1,    -1,    60,    61,    -1,    63,    -1,    65,    -1,    -1,
      68,    69,    -1,    71,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    -1,
      -1,     3,     4,    -1,    54,     7,     8,    -1,    -1,    -1,
      60,    61,    -1,    63,    -1,    65,    -1,    -1,    68,    69,
      22,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    36,    37,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    45,    46,    47,    48,    -1,    -1,     3,
       4,    -1,    54,     7,     8,    -1,    -1,    -1,    60,    61,
      -1,    63,    -1,    65,    -1,    -1,    68,    69,    22,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    -1,
      -1,    -1,    36,    37,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    -1,    -1,     3,     4,    -1,
      54,     7,     8,    -1,    -1,    -1,    60,    61,    -1,    63,
      -1,    65,    -1,    -1,    68,    69,    -1,    71,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,    -1,    -1,     7,     8,
      36,    37,    11,    -1,    40,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    60,    61,    -1,    63,    -1,    65,
      -1,    40,    68,    69,    -1,    71,    45,    46,    47,    48,
      -1,    -1,     3,     4,    -1,    54,     7,     8,    -1,    -1,
      -1,    60,    61,    -1,    63,    -1,    65,    -1,    -1,    68,
      69,    -1,    71,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,    -1,    -1,     7,     8,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    -1,    -1,
      -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    60,
      61,    -1,    63,    -1,    65,    -1,    -1,    68,    69,    -1,
      71,    45,    46,    47,    48,    -1,     9,    -1,    -1,    -1,
      54,    14,    -1,    -1,    -1,    -1,    60,    61,    -1,    63,
      -1,    65,    -1,    -1,    68,    69,    -1,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    -1,    58,    59
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    78,     0,     1,     3,     4,     7,     8,    17,    18,
      35,    36,    37,    38,    39,    40,    45,    46,    47,    48,
      49,    53,    54,    60,    61,    63,    65,    68,    69,    71,
      79,    82,    86,    87,    89,    95,   105,   110,   118,   122,
     123,   124,   125,   126,   127,   135,   136,    69,    72,   132,
     133,   134,     3,     4,    47,    48,    71,    84,    85,   128,
     136,   136,   136,    69,    69,    71,   123,   136,   123,   123,
      69,   125,   136,     1,   117,   118,    50,    52,   127,    74,
      76,    83,    91,   110,   138,   142,    83,    88,    96,    53,
       9,    14,    42,    43,    44,    55,    57,    58,    59,   120,
     121,    11,   123,    60,    61,    62,    63,    64,    67,    60,
      61,    62,    63,    64,    67,    12,    13,    45,    46,    54,
     119,   116,   117,   118,   117,    16,   132,    51,    69,    58,
     112,   116,   116,   118,    45,    46,   137,     1,    57,    70,
     140,   144,   140,     1,     6,    80,     1,     6,    81,   110,
     111,    90,   111,     5,    69,   106,   116,   118,   135,   118,
     118,   118,   111,   118,    40,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,    13,   118,   140,
      73,     1,     4,   113,   114,   123,   140,   140,   118,   111,
      42,     1,   118,     1,    91,     1,    91,     1,    19,    21,
      22,    23,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    41,    75,    92,    93,    97,   104,   109,   118,   138,
     139,   142,   117,    10,   107,    56,   118,   128,   140,     1,
     144,   135,    69,    94,     4,    69,    69,    69,   111,    69,
      91,    91,    91,   115,   118,    91,   111,    91,    98,    90,
     141,   142,   111,   140,   108,   118,   111,     1,     4,   118,
     115,    99,     4,   118,   118,    92,     4,    97,   100,    91,
     106,   139,   111,   122,   140,    91,   129,   130,   131,   132,
      70,   140,   140,    26,    42,   142,   107,   111,    16,   131,
     111,   111,    69,   135,   111,    92,   138,    92,   118,   140,
     118,   142,    20,   101,   140,   111,   142,   111,   111,     1,
      24,    25,   102,   111,   111,    92,   111,   100,    92,     7,
       8,    60,    61,    87,   103,    56,   143,   139,   100,   140,
       7,     7,   143,   111,   140,   111,   111,    90,   111,    92,
      90,    92
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    77,    78,    78,    78,    78,    78,    79,    79,    79,
      79,    79,    80,    80,    80,    81,    81,    81,    82,    82,
      82,    82,    82,    82,    82,    83,    84,    84,    84,    84,
      85,    85,    86,    88,    87,    89,    89,    90,    90,    90,
      91,    91,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    93,    93,    93,    93,    93,    94,    93,    93,
      96,    95,    98,    97,    99,    97,    97,    97,   100,   100,
     101,   101,   101,   102,   102,   103,   103,   103,   103,   103,
     104,   104,   105,   105,   106,   106,   107,   108,   107,   109,
     109,   110,   110,   111,   111,   112,   112,   113,   113,   114,
     114,   114,   114,   114,   115,   115,   116,   116,   117,   117,
     117,   117,   117,   117,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   119,   119,   119,   120,   120,   121,   121,
     122,   122,   122,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   124,   124,   124,   124,   124,   124,
     124,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   126,   126,   127,   128,   128,
     129,   129,   130,   130,   131,   132,   133,   133,   134,   135,
     135,   136,   136,   137,   137,   137,   138,   139,   140,   141,
     141,   142,   143,   144
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     2,     2,
       4,     4,     1,     2,     1,     1,     2,     1,     0,     1,
       4,     1,     1,     1,     1,     5,     1,     1,     1,     2,
       1,     1,     6,     0,     3,     1,     1,     0,     2,     2,
       1,     2,     2,     3,     1,     9,     6,     8,     8,    12,
      11,     1,     2,     2,     2,     2,     3,     0,     4,     2,
       0,     4,     0,     4,     0,     4,     4,     1,     0,     1,
       0,     2,     2,     5,     4,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     0,     3,     6,
       9,     1,     2,     0,     1,     0,     2,     0,     1,     1,
       3,     1,     2,     3,     0,     1,     0,     1,     1,     3,
       1,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       5,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     2,     1,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     5,     4,     3,     3,     3,     3,     3,
       3,     1,     2,     3,     4,     4,     1,     1,     1,     2,
       2,     1,     1,     2,     2,     1,     2,     4,     0,     1,
       0,     2,     1,     2,     1,     3,     1,     2,     2,     1,
       2,     1,     3,     1,     1,     0,     2,     2,     1,     0,
       1,     1,     1,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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
      yychar = yylex ();
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
     '$$ = $1'.

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
#line 214 "awkgram.y" /* yacc.c:1646  */
    {
		rule = 0;
		yyerrok;
	  }
#line 1916 "awkgram.c" /* yacc.c:1646  */
    break;

  case 5:
#line 220 "awkgram.y" /* yacc.c:1646  */
    {
		next_sourcefile();
		if (sourcefile == srcfiles)
			process_deferred();
	  }
#line 1926 "awkgram.c" /* yacc.c:1646  */
    break;

  case 6:
#line 226 "awkgram.y" /* yacc.c:1646  */
    {
		rule = 0;
		/*
		 * If errors, give up, don't produce an infinite
		 * stream of syntax error messages.
		 */
  		/* yyerrok; */
	  }
#line 1939 "awkgram.c" /* yacc.c:1646  */
    break;

  case 7:
#line 238 "awkgram.y" /* yacc.c:1646  */
    {
		(void) append_rule((yyvsp[-1]), (yyvsp[0]));
	  }
#line 1947 "awkgram.c" /* yacc.c:1646  */
    break;

  case 8:
#line 242 "awkgram.y" /* yacc.c:1646  */
    {
		if (rule != Rule) {
			msg(_("%s blocks must have an action part"), ruletab[rule]);
			errcount++;
		} else if ((yyvsp[-1]) == NULL) {
			msg(_("each rule must have a pattern or an action part"));
			errcount++;
		} else		/* pattern rule with non-empty pattern */
			(void) append_rule((yyvsp[-1]), NULL);
	  }
#line 1962 "awkgram.c" /* yacc.c:1646  */
    break;

  case 9:
#line 253 "awkgram.y" /* yacc.c:1646  */
    {
		in_function = NULL;
		(void) mk_function((yyvsp[-1]), (yyvsp[0]));
		yyerrok;
	  }
#line 1972 "awkgram.c" /* yacc.c:1646  */
    break;

  case 10:
#line 259 "awkgram.y" /* yacc.c:1646  */
    {
		want_source = false;
		yyerrok;
	  }
#line 1981 "awkgram.c" /* yacc.c:1646  */
    break;

  case 11:
#line 264 "awkgram.y" /* yacc.c:1646  */
    {
		want_source = false;
		yyerrok;
	  }
#line 1990 "awkgram.c" /* yacc.c:1646  */
    break;

  case 12:
#line 272 "awkgram.y" /* yacc.c:1646  */
    {
		if (include_source((yyvsp[0])) < 0)
			YYABORT;
		efree((yyvsp[0])->lextok);
		bcfree((yyvsp[0]));
		(yyval) = NULL;
	  }
#line 2002 "awkgram.c" /* yacc.c:1646  */
    break;

  case 13:
#line 280 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 2008 "awkgram.c" /* yacc.c:1646  */
    break;

  case 14:
#line 282 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 2014 "awkgram.c" /* yacc.c:1646  */
    break;

  case 15:
#line 287 "awkgram.y" /* yacc.c:1646  */
    {
		extensions_used = true;
		if (load_library((yyvsp[0])) < 0)
			YYABORT;
		efree((yyvsp[0])->lextok);
		bcfree((yyvsp[0]));
		(yyval) = NULL;
	  }
#line 2027 "awkgram.c" /* yacc.c:1646  */
    break;

  case 16:
#line 296 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 2033 "awkgram.c" /* yacc.c:1646  */
    break;

  case 17:
#line 298 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 2039 "awkgram.c" /* yacc.c:1646  */
    break;

  case 18:
#line 303 "awkgram.y" /* yacc.c:1646  */
    {
		rule = Rule;
		if (comment != NULL) {
			(yyval) = list_create(comment);
			comment = NULL;
		} else
			(yyval) = NULL;
	  }
#line 2052 "awkgram.c" /* yacc.c:1646  */
    break;

  case 19:
#line 312 "awkgram.y" /* yacc.c:1646  */
    {
		rule = Rule;
		if (comment != NULL) {
			(yyval) = list_prepend((yyvsp[0]), comment);
			comment = NULL;
		} else
			(yyval) = (yyvsp[0]);
	  }
#line 2065 "awkgram.c" /* yacc.c:1646  */
    break;

  case 20:
#line 322 "awkgram.y" /* yacc.c:1646  */
    {
		INSTRUCTION *tp;

		add_lint((yyvsp[-3]), LINT_assign_in_cond);
		add_lint((yyvsp[0]), LINT_assign_in_cond);

		tp = instruction(Op_no_op);
		list_prepend((yyvsp[-3]), bcalloc(Op_line_range, !!do_pretty_print + 1, 0));
		(yyvsp[-3])->nexti->triggered = false;
		(yyvsp[-3])->nexti->target_jmp = (yyvsp[0])->nexti;

		list_append((yyvsp[-3]), instruction(Op_cond_pair));
		(yyvsp[-3])->lasti->line_range = (yyvsp[-3])->nexti;
		(yyvsp[-3])->lasti->target_jmp = tp;

		list_append((yyvsp[0]), instruction(Op_cond_pair));
		(yyvsp[0])->lasti->line_range = (yyvsp[-3])->nexti;
		(yyvsp[0])->lasti->target_jmp = tp;
		if (do_pretty_print) {
			((yyvsp[-3])->nexti + 1)->condpair_left = (yyvsp[-3])->lasti;
			((yyvsp[-3])->nexti + 1)->condpair_right = (yyvsp[0])->lasti;
		}
		if (comment != NULL) {
			(yyval) = list_append(list_merge(list_prepend((yyvsp[-3]), comment), (yyvsp[0])), tp);
			comment = NULL;
		} else
			(yyval) = list_append(list_merge((yyvsp[-3]), (yyvsp[0])), tp);
		rule = Rule;
	  }
#line 2099 "awkgram.c" /* yacc.c:1646  */
    break;

  case 21:
#line 352 "awkgram.y" /* yacc.c:1646  */
    {
		static int begin_seen = 0;

		func_first = false;
		if (do_lint_old && ++begin_seen == 2)
			warning_ln((yyvsp[0])->source_line,
				_("old awk does not support multiple `BEGIN' or `END' rules"));

		(yyvsp[0])->in_rule = rule = BEGIN;
		(yyvsp[0])->source_file = source;
		check_comment();
		(yyval) = (yyvsp[0]);
	  }
#line 2117 "awkgram.c" /* yacc.c:1646  */
    break;

  case 22:
#line 366 "awkgram.y" /* yacc.c:1646  */
    {
		static int end_seen = 0;

		func_first = false;
		if (do_lint_old && ++end_seen == 2)
			warning_ln((yyvsp[0])->source_line,
				_("old awk does not support multiple `BEGIN' or `END' rules"));

		(yyvsp[0])->in_rule = rule = END;
		(yyvsp[0])->source_file = source;
		check_comment();
		(yyval) = (yyvsp[0]);
	  }
#line 2135 "awkgram.c" /* yacc.c:1646  */
    break;

  case 23:
#line 380 "awkgram.y" /* yacc.c:1646  */
    {
		func_first = false;
		(yyvsp[0])->in_rule = rule = BEGINFILE;
		(yyvsp[0])->source_file = source;
		check_comment();
		(yyval) = (yyvsp[0]);
	  }
#line 2147 "awkgram.c" /* yacc.c:1646  */
    break;

  case 24:
#line 388 "awkgram.y" /* yacc.c:1646  */
    {
		func_first = false;
		(yyvsp[0])->in_rule = rule = ENDFILE;
		(yyvsp[0])->source_file = source;
		check_comment();
		(yyval) = (yyvsp[0]);
	  }
#line 2159 "awkgram.c" /* yacc.c:1646  */
    break;

  case 25:
#line 399 "awkgram.y" /* yacc.c:1646  */
    {
		INSTRUCTION *ip;
		if ((yyvsp[-3]) == NULL)
			ip = list_create(instruction(Op_no_op));
		else
			ip = (yyvsp[-3]);
		(yyval) = ip;
	  }
#line 2172 "awkgram.c" /* yacc.c:1646  */
    break;

  case 26:
#line 411 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2178 "awkgram.c" /* yacc.c:1646  */
    break;

  case 27:
#line 413 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2184 "awkgram.c" /* yacc.c:1646  */
    break;

  case 28:
#line 415 "awkgram.y" /* yacc.c:1646  */
    {
		yyerror(_("`%s' is a built-in function, it cannot be redefined"),
					tokstart);
		YYABORT;
	  }
#line 2194 "awkgram.c" /* yacc.c:1646  */
    break;

  case 29:
#line 421 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2200 "awkgram.c" /* yacc.c:1646  */
    break;

  case 32:
#line 431 "awkgram.y" /* yacc.c:1646  */
    {
		/*
		 *  treat any comments between BOF and the first function
		 *  definition (with no intervening BEGIN etc block) as
		 *  program comments.  Special kludge: iff there are more
		 *  than one such comments, treat the last as a function
		 *  comment.
		 */
		if (comment != NULL && func_first
		    && strstr(comment->memory->stptr, "\n\n") != NULL)
			split_comment();
		/* save any other pre-function comment as function comment  */
		if (comment != NULL) {
			function_comment = comment;
			comment = NULL;
		}
		func_first = false;
		(yyvsp[-5])->source_file = source;
		if (install_function((yyvsp[-4])->lextok, (yyvsp[-5]), (yyvsp[-2])) < 0)
			YYABORT;
		in_function = (yyvsp[-4])->lextok;
		(yyvsp[-4])->lextok = NULL;
		bcfree((yyvsp[-4]));
		/* $4 already free'd in install_function */
		(yyval) = (yyvsp[-5]);
	  }
#line 2231 "awkgram.c" /* yacc.c:1646  */
    break;

  case 33:
#line 465 "awkgram.y" /* yacc.c:1646  */
    { want_regexp = true; }
#line 2237 "awkgram.c" /* yacc.c:1646  */
    break;

  case 34:
#line 467 "awkgram.y" /* yacc.c:1646  */
    {
		  NODE *n, *exp;
		  char *re;
		  size_t len;

		  re = (yyvsp[0])->lextok;
		  (yyvsp[0])->lextok = NULL;
		  len = strlen(re);
		  if (do_lint) {
			if (len == 0)
				lintwarn_ln((yyvsp[0])->source_line,
					_("regexp constant `//' looks like a C++ comment, but is not"));
			else if (re[0] == '*' && re[len-1] == '*')
				/* possible C comment */
				lintwarn_ln((yyvsp[0])->source_line,
					_("regexp constant `/%s/' looks like a C comment, but is not"), re);
		  }

		  exp = make_str_node(re, len, ALREADY_MALLOCED);
		  n = make_regnode(Node_regex, exp);
		  if (n == NULL) {
			unref(exp);
			YYABORT;
		  }
		  (yyval) = (yyvsp[0]);
		  (yyval)->opcode = Op_match_rec;
		  (yyval)->memory = n;
		}
#line 2270 "awkgram.c" /* yacc.c:1646  */
    break;

  case 35:
#line 499 "awkgram.y" /* yacc.c:1646  */
    { bcfree((yyvsp[0])); }
#line 2276 "awkgram.c" /* yacc.c:1646  */
    break;

  case 37:
#line 505 "awkgram.y" /* yacc.c:1646  */
    {
		if (comment != NULL) {
			(yyval) = list_create(comment);
			comment = NULL;
		} else (yyval) = NULL;
	  }
#line 2287 "awkgram.c" /* yacc.c:1646  */
    break;

  case 38:
#line 512 "awkgram.y" /* yacc.c:1646  */
    {
		if ((yyvsp[0]) == NULL) {
			if (comment == NULL)
				(yyval) = (yyvsp[-1]);
			else {
				(yyval) = list_append((yyvsp[-1]), comment);
				comment = NULL;
			}
		} else {
			add_lint((yyvsp[0]), LINT_no_effect);
			if ((yyvsp[-1]) == NULL) {
				if (comment == NULL)
					(yyval) = (yyvsp[0]);
				else {
					(yyval) = list_append((yyvsp[0]), comment);
					comment = NULL;
				}
			} else {
				if (comment != NULL) {
					list_append((yyvsp[0]), comment);
					comment = NULL;
				}
				(yyval) = list_merge((yyvsp[-1]), (yyvsp[0]));
			}
		}
		yyerrok;
	  }
#line 2319 "awkgram.c" /* yacc.c:1646  */
    break;

  case 39:
#line 540 "awkgram.y" /* yacc.c:1646  */
    {	(yyval) = NULL; }
#line 2325 "awkgram.c" /* yacc.c:1646  */
    break;

  case 42:
#line 550 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 2331 "awkgram.c" /* yacc.c:1646  */
    break;

  case 43:
#line 552 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 2337 "awkgram.c" /* yacc.c:1646  */
    break;

  case 44:
#line 554 "awkgram.y" /* yacc.c:1646  */
    {
		if (do_pretty_print)
			(yyval) = list_prepend((yyvsp[0]), instruction(Op_exec_count));
		else
			(yyval) = (yyvsp[0]);
 	  }
#line 2348 "awkgram.c" /* yacc.c:1646  */
    break;

  case 45:
#line 561 "awkgram.y" /* yacc.c:1646  */
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

		if ((yyvsp[-2]) != NULL) {
			curr = (yyvsp[-2])->nexti;
			bcfree((yyvsp[-2]));	/* Op_list */
		} /*  else
				curr = NULL; */

		for (; curr != NULL; curr = nextc) {
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

		ip = (yyvsp[-6]);
		if (do_pretty_print) {
			(void) list_prepend(ip, (yyvsp[-8]));
			(void) list_prepend(ip, instruction(Op_exec_count));
			(yyvsp[-8])->target_break = tbreak;
			((yyvsp[-8]) + 1)->switch_start = cexp->nexti;
			((yyvsp[-8]) + 1)->switch_end = cexp->lasti;
		}/* else
				$1 is NULL */

		(void) list_append(cexp, dflt);
		(void) list_merge(ip, cexp);
		(yyval) = list_merge(ip, cstmt);

		break_allowed--;			
		fix_break_continue(ip, tbreak, NULL);
	  }
#line 2442 "awkgram.c" /* yacc.c:1646  */
    break;

  case 46:
#line 651 "awkgram.y" /* yacc.c:1646  */
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
		add_lint((yyvsp[-3]), LINT_assign_in_cond);
		tcont = (yyvsp[-3])->nexti;
		ip = list_append((yyvsp[-3]), instruction(Op_jmp_false));
		ip->lasti->target_jmp = tbreak;

		if (do_pretty_print) {
			(void) list_append(ip, instruction(Op_exec_count));
			(yyvsp[-5])->target_break = tbreak;
			(yyvsp[-5])->target_continue = tcont;
			((yyvsp[-5]) + 1)->while_body = ip->lasti;
			(void) list_prepend(ip, (yyvsp[-5]));
		}/* else
				$1 is NULL */

		if ((yyvsp[0]) != NULL)
			(void) list_merge(ip, (yyvsp[0]));
		(void) list_append(ip, instruction(Op_jmp));
		ip->lasti->target_jmp = tcont;
		(yyval) = list_append(ip, tbreak);

		break_allowed--;
		continue_allowed--;
		fix_break_continue(ip, tbreak, tcont);
	  }
#line 2488 "awkgram.c" /* yacc.c:1646  */
    break;

  case 47:
#line 693 "awkgram.y" /* yacc.c:1646  */
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
		tcont = (yyvsp[-2])->nexti;
		add_lint((yyvsp[-2]), LINT_assign_in_cond);
		if ((yyvsp[-5]) != NULL)
			ip = list_merge((yyvsp[-5]), (yyvsp[-2]));
		else
			ip = list_prepend((yyvsp[-2]), instruction(Op_no_op));
		if (do_pretty_print)
			(void) list_prepend(ip, instruction(Op_exec_count));
		(void) list_append(ip, instruction(Op_jmp_true));
		ip->lasti->target_jmp = ip->nexti;
		(yyval) = list_append(ip, tbreak);

		break_allowed--;
		continue_allowed--;
		fix_break_continue(ip, tbreak, tcont);

		if (do_pretty_print) {
			(yyvsp[-7])->target_break = tbreak;
			(yyvsp[-7])->target_continue = tcont;
			((yyvsp[-7]) + 1)->doloop_cond = tcont;
			(yyval) = list_prepend(ip, (yyvsp[-7]));
			bcfree((yyvsp[-4]));
		} /* else
			$1 and $4 are NULLs */
	  }
#line 2534 "awkgram.c" /* yacc.c:1646  */
    break;

  case 48:
#line 735 "awkgram.y" /* yacc.c:1646  */
    {
		INSTRUCTION *ip;
		char *var_name = (yyvsp[-5])->lextok;

		if ((yyvsp[0]) != NULL
				&& (yyvsp[0])->lasti->opcode == Op_K_delete
				&& (yyvsp[0])->lasti->expr_count == 1
				&& (yyvsp[0])->nexti->opcode == Op_push
				&& ((yyvsp[0])->nexti->memory->type != Node_var || !((yyvsp[0])->nexti->memory->var_update))
				&& strcmp((yyvsp[0])->nexti->memory->vname, var_name) == 0
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

			ip = (yyvsp[0])->nexti->nexti; 
			if ((yyvsp[-3])->nexti->opcode == Op_push && (yyvsp[-3])->lasti == (yyvsp[-3])->nexti)
				arr = (yyvsp[-3])->nexti->memory;
			if (arr != NULL
					&& ip->opcode == Op_no_op
					&& ip->nexti->opcode == Op_push_array
					&& strcmp(ip->nexti->memory->vname, arr->vname) == 0
					&& ip->nexti->nexti == (yyvsp[0])->lasti
			) {
				(void) make_assignable((yyvsp[0])->nexti);
				(yyvsp[0])->lasti->opcode = Op_K_delete_loop;
				(yyvsp[0])->lasti->expr_count = 0;
				if ((yyvsp[-7]) != NULL)
					bcfree((yyvsp[-7]));
				efree(var_name);
				bcfree((yyvsp[-5]));
				bcfree((yyvsp[-4]));
				bcfree((yyvsp[-3]));
				(yyval) = (yyvsp[0]);
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
			ip = (yyvsp[-3]);
			ip->nexti->opcode = Op_push_array;

			tbreak = instruction(Op_arrayfor_final);
			(yyvsp[-4])->opcode = Op_arrayfor_incr;
			(yyvsp[-4])->array_var = variable((yyvsp[-5])->source_line, var_name, Node_var);
			(yyvsp[-4])->target_jmp = tbreak;
			tcont = (yyvsp[-4]);
			(yyvsp[-5])->opcode = Op_arrayfor_init;
			(yyvsp[-5])->target_jmp = tbreak;
			(void) list_append(ip, (yyvsp[-5]));

			if (do_pretty_print) {
				(yyvsp[-7])->opcode = Op_K_arrayfor;
				(yyvsp[-7])->target_continue = tcont;
				(yyvsp[-7])->target_break = tbreak;
				(void) list_append(ip, (yyvsp[-7]));
			} /* else
					$1 is NULL */

			/* add update_FOO instruction if necessary */ 
			if ((yyvsp[-4])->array_var->type == Node_var && (yyvsp[-4])->array_var->var_update) {
				(void) list_append(ip, instruction(Op_var_update));
				ip->lasti->update_var = (yyvsp[-4])->array_var->var_update;
			}
			(void) list_append(ip, (yyvsp[-4]));

			/* add set_FOO instruction if necessary */
			if ((yyvsp[-4])->array_var->type == Node_var && (yyvsp[-4])->array_var->var_assign) {
				(void) list_append(ip, instruction(Op_var_assign));
				ip->lasti->assign_var = (yyvsp[-4])->array_var->var_assign;
			}

			if (do_pretty_print) {
				(void) list_append(ip, instruction(Op_exec_count));
				((yyvsp[-7]) + 1)->forloop_cond = (yyvsp[-4]);
				((yyvsp[-7]) + 1)->forloop_body = ip->lasti; 
			}

			if ((yyvsp[0]) != NULL)
				(void) list_merge(ip, (yyvsp[0]));

			(void) list_append(ip, instruction(Op_jmp));
			ip->lasti->target_jmp = (yyvsp[-4]);
			(yyval) = list_append(ip, tbreak);
			fix_break_continue(ip, tbreak, tcont);
		} 

		break_allowed--;
		continue_allowed--;
	  }
#line 2651 "awkgram.c" /* yacc.c:1646  */
    break;

  case 49:
#line 848 "awkgram.y" /* yacc.c:1646  */
    {
		(yyval) = mk_for_loop((yyvsp[-11]), (yyvsp[-9]), (yyvsp[-6]), (yyvsp[-3]), (yyvsp[0]));

		break_allowed--;
		continue_allowed--;
	  }
#line 2662 "awkgram.c" /* yacc.c:1646  */
    break;

  case 50:
#line 855 "awkgram.y" /* yacc.c:1646  */
    {
		(yyval) = mk_for_loop((yyvsp[-10]), (yyvsp[-8]), (INSTRUCTION *) NULL, (yyvsp[-3]), (yyvsp[0]));

		break_allowed--;
		continue_allowed--;
	  }
#line 2673 "awkgram.c" /* yacc.c:1646  */
    break;

  case 51:
#line 862 "awkgram.y" /* yacc.c:1646  */
    {
		if (do_pretty_print)
			(yyval) = list_prepend((yyvsp[0]), instruction(Op_exec_count));
		else
			(yyval) = (yyvsp[0]);
	  }
#line 2684 "awkgram.c" /* yacc.c:1646  */
    break;

  case 52:
#line 872 "awkgram.y" /* yacc.c:1646  */
    { 
		if (! break_allowed)
			error_ln((yyvsp[-1])->source_line,
				_("`break' is not allowed outside a loop or switch"));
		(yyvsp[-1])->target_jmp = NULL;
		(yyval) = list_create((yyvsp[-1]));

	  }
#line 2697 "awkgram.c" /* yacc.c:1646  */
    break;

  case 53:
#line 881 "awkgram.y" /* yacc.c:1646  */
    {
		if (! continue_allowed)
			error_ln((yyvsp[-1])->source_line,
				_("`continue' is not allowed outside a loop"));
		(yyvsp[-1])->target_jmp = NULL;
		(yyval) = list_create((yyvsp[-1]));

	  }
#line 2710 "awkgram.c" /* yacc.c:1646  */
    break;

  case 54:
#line 890 "awkgram.y" /* yacc.c:1646  */
    {
		/* if inside function (rule = 0), resolve context at run-time */
		if (rule && rule != Rule)
			error_ln((yyvsp[-1])->source_line,
				_("`next' used in %s action"), ruletab[rule]);
		(yyvsp[-1])->target_jmp = ip_rec;
		(yyval) = list_create((yyvsp[-1]));
	  }
#line 2723 "awkgram.c" /* yacc.c:1646  */
    break;

  case 55:
#line 899 "awkgram.y" /* yacc.c:1646  */
    {
		/* if inside function (rule = 0), resolve context at run-time */
		if (rule == BEGIN || rule == END || rule == ENDFILE)
			error_ln((yyvsp[-1])->source_line,
				_("`nextfile' used in %s action"), ruletab[rule]);

		(yyvsp[-1])->target_newfile = ip_newfile;
		(yyvsp[-1])->target_endfile = ip_endfile;
		(yyval) = list_create((yyvsp[-1]));
	  }
#line 2738 "awkgram.c" /* yacc.c:1646  */
    break;

  case 56:
#line 910 "awkgram.y" /* yacc.c:1646  */
    {
		/* Initialize the two possible jump targets, the actual target
		 * is resolved at run-time. 
		 */
		(yyvsp[-2])->target_end = ip_end;	/* first instruction in end_block */
		(yyvsp[-2])->target_atexit = ip_atexit;	/* cleanup and go home */

		if ((yyvsp[-1]) == NULL) {
			(yyval) = list_create((yyvsp[-2]));
			(void) list_prepend((yyval), instruction(Op_push_i));
			(yyval)->nexti->memory = dupnode(Nnull_string);
		} else
			(yyval) = list_append((yyvsp[-1]), (yyvsp[-2]));
	  }
#line 2757 "awkgram.c" /* yacc.c:1646  */
    break;

  case 57:
#line 925 "awkgram.y" /* yacc.c:1646  */
    {
		if (! in_function)
			yyerror(_("`return' used outside function context"));
	  }
#line 2766 "awkgram.c" /* yacc.c:1646  */
    break;

  case 58:
#line 928 "awkgram.y" /* yacc.c:1646  */
    {
		if ((yyvsp[-1]) == NULL) {
			(yyval) = list_create((yyvsp[-3]));
			(void) list_prepend((yyval), instruction(Op_push_i));
			(yyval)->nexti->memory = dupnode(Nnull_string);
		} else {
			if (do_optimize
				&& (yyvsp[-1])->lasti->opcode == Op_func_call
				&& strcmp((yyvsp[-1])->lasti->func_name, in_function) == 0
			) {
				/* Do tail recursion optimization. Tail
				 * call without a return value is recognized
				 * in mk_function().
				 */
				((yyvsp[-1])->lasti + 1)->tail_call = true;
			}

			(yyval) = list_append((yyvsp[-1]), (yyvsp[-3]));
		}
	  }
#line 2791 "awkgram.c" /* yacc.c:1646  */
    break;

  case 60:
#line 952 "awkgram.y" /* yacc.c:1646  */
    { in_print = true; in_parens = 0; }
#line 2797 "awkgram.c" /* yacc.c:1646  */
    break;

  case 61:
#line 953 "awkgram.y" /* yacc.c:1646  */
    {
		(yyval) = mk_print((yyvsp[-3]), (yyvsp[-1]), (yyvsp[0]));
	  }
#line 2805 "awkgram.c" /* yacc.c:1646  */
    break;

  case 62:
#line 967 "awkgram.y" /* yacc.c:1646  */
    { in_print = true; in_parens = 0; }
#line 2811 "awkgram.c" /* yacc.c:1646  */
    break;

  case 63:
#line 968 "awkgram.y" /* yacc.c:1646  */
    {
		(yyval) = mk_print((yyvsp[-3]), (yyvsp[-1]), (yyvsp[0]));
	  }
#line 2819 "awkgram.c" /* yacc.c:1646  */
    break;

  case 64:
#line 972 "awkgram.y" /* yacc.c:1646  */
    { sub_counter = 0; }
#line 2825 "awkgram.c" /* yacc.c:1646  */
    break;

  case 65:
#line 973 "awkgram.y" /* yacc.c:1646  */
    {
		char *arr = (yyvsp[-2])->lextok;

		(yyvsp[-2])->opcode = Op_push_array;
		(yyvsp[-2])->memory = variable((yyvsp[-2])->source_line, arr, Node_var_new);

		if (! do_posix && ! do_traditional) {
			if ((yyvsp[-2])->memory == symbol_table)
				fatal(_("`delete' is not allowed with SYMTAB"));
			else if ((yyvsp[-2])->memory == func_table)
				fatal(_("`delete' is not allowed with FUNCTAB"));
		}

		if ((yyvsp[0]) == NULL) {
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
			(yyvsp[-3])->expr_count = 0;
			(yyval) = list_append(list_create((yyvsp[-2])), (yyvsp[-3]));
		} else {
			(yyvsp[-3])->expr_count = sub_counter;
			(yyval) = list_append(list_append((yyvsp[0]), (yyvsp[-2])), (yyvsp[-3]));
		}
	  }
#line 2862 "awkgram.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1010 "awkgram.y" /* yacc.c:1646  */
    {
		static bool warned = false;
		char *arr = (yyvsp[-1])->lextok;

		if (do_lint && ! warned) {
			warned = true;
			lintwarn_ln((yyvsp[-3])->source_line,
				_("`delete(array)' is a non-portable tawk extension"));
		}
		if (do_traditional) {
			error_ln((yyvsp[-3])->source_line,
				_("`delete(array)' is a non-portable tawk extension"));
		}
		(yyvsp[-1])->memory = variable((yyvsp[-1])->source_line, arr, Node_var_new);
		(yyvsp[-1])->opcode = Op_push_array;
		(yyvsp[-3])->expr_count = 0;
		(yyval) = list_append(list_create((yyvsp[-1])), (yyvsp[-3]));

		if (! do_posix && ! do_traditional) {
			if ((yyvsp[-1])->memory == symbol_table)
				fatal(_("`delete' is not allowed with SYMTAB"));
			else if ((yyvsp[-1])->memory == func_table)
				fatal(_("`delete' is not allowed with FUNCTAB"));
		}
	  }
#line 2892 "awkgram.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1036 "awkgram.y" /* yacc.c:1646  */
    {	(yyval) = optimize_assignment((yyvsp[0])); }
#line 2898 "awkgram.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1041 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 2904 "awkgram.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1043 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2910 "awkgram.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1048 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 2916 "awkgram.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1050 "awkgram.y" /* yacc.c:1646  */
    {
		if ((yyvsp[-1]) == NULL)
			(yyval) = list_create((yyvsp[0]));
		else
			(yyval) = list_prepend((yyvsp[-1]), (yyvsp[0]));
	  }
#line 2927 "awkgram.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1057 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 2933 "awkgram.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1062 "awkgram.y" /* yacc.c:1646  */
    {
		INSTRUCTION *casestmt = (yyvsp[0]);
		if ((yyvsp[0]) == NULL)
			casestmt = list_create(instruction(Op_no_op));	
		if (do_pretty_print)
			(void) list_prepend(casestmt, instruction(Op_exec_count));
		(yyvsp[-4])->case_exp = (yyvsp[-3]);
		(yyvsp[-4])->case_stmt = casestmt;
		bcfree((yyvsp[-2]));
		(yyval) = (yyvsp[-4]);
	  }
#line 2949 "awkgram.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1074 "awkgram.y" /* yacc.c:1646  */
    {
		INSTRUCTION *casestmt = (yyvsp[0]);
		if ((yyvsp[0]) == NULL)
			casestmt = list_create(instruction(Op_no_op));
		if (do_pretty_print)
			(void) list_prepend(casestmt, instruction(Op_exec_count));
		bcfree((yyvsp[-2]));
		(yyvsp[-3])->case_stmt = casestmt;
		(yyval) = (yyvsp[-3]);
	  }
#line 2964 "awkgram.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1088 "awkgram.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2970 "awkgram.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1090 "awkgram.y" /* yacc.c:1646  */
    { 
		NODE *n = (yyvsp[0])->memory;
		(void) force_number(n);
		negate_num(n);
		bcfree((yyvsp[-1]));
		(yyval) = (yyvsp[0]);
	  }
#line 2982 "awkgram.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1098 "awkgram.y" /* yacc.c:1646  */
    {
		bcfree((yyvsp[-1]));
		(yyval) = (yyvsp[0]);
	  }
#line 2991 "awkgram.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1103 "awkgram.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 2997 "awkgram.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1105 "awkgram.y" /* yacc.c:1646  */
    {
		(yyvsp[0])->opcode = Op_push_re;
		(yyval) = (yyvsp[0]);
	  }
#line 3006 "awkgram.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1113 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 3012 "awkgram.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1115 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 3018 "awkgram.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1120 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 3024 "awkgram.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1122 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 3030 "awkgram.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1132 "awkgram.y" /* yacc.c:1646  */
    {
		(yyval) = (yyvsp[-1]);
	  }
#line 3038 "awkgram.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1139 "awkgram.y" /* yacc.c:1646  */
    {
		in_print = false;
		in_parens = 0;
		(yyval) = NULL;
	  }
#line 3048 "awkgram.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1144 "awkgram.y" /* yacc.c:1646  */
    { in_print = false; in_parens = 0; }
#line 3054 "awkgram.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1145 "awkgram.y" /* yacc.c:1646  */
    {
		if ((yyvsp[-2])->redir_type == redirect_twoway
		    	&& (yyvsp[0])->lasti->opcode == Op_K_getline_redir
		   	 	&& (yyvsp[0])->lasti->redir_type == redirect_twoway)
			yyerror(_("multistage two-way pipelines don't work"));
		(yyval) = list_prepend((yyvsp[0]), (yyvsp[-2]));
	  }
#line 3066 "awkgram.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1156 "awkgram.y" /* yacc.c:1646  */
    {
		(yyval) = mk_condition((yyvsp[-3]), (yyvsp[-5]), (yyvsp[0]), NULL, NULL);
	  }
#line 3074 "awkgram.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1161 "awkgram.y" /* yacc.c:1646  */
    {
		(yyval) = mk_condition((yyvsp[-6]), (yyvsp[-8]), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[0]));
	  }
#line 3082 "awkgram.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1178 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 3088 "awkgram.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1180 "awkgram.y" /* yacc.c:1646  */
    {
		bcfree((yyvsp[-1]));
		(yyval) = (yyvsp[0]);
	  }
#line 3097 "awkgram.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1188 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 3103 "awkgram.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1190 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 3109 "awkgram.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1195 "awkgram.y" /* yacc.c:1646  */
    {
		(yyvsp[0])->param_count = 0;
		(yyval) = list_create((yyvsp[0]));
	  }
#line 3118 "awkgram.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1200 "awkgram.y" /* yacc.c:1646  */
    {
		(yyvsp[0])->param_count =  (yyvsp[-2])->lasti->param_count + 1;
		(yyval) = list_append((yyvsp[-2]), (yyvsp[0]));
		yyerrok;
	  }
#line 3128 "awkgram.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1206 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 3134 "awkgram.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1208 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 3140 "awkgram.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1210 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-2]); }
#line 3146 "awkgram.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1216 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 3152 "awkgram.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1218 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 3158 "awkgram.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1223 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 3164 "awkgram.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1225 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 3170 "awkgram.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1230 "awkgram.y" /* yacc.c:1646  */
    {	(yyval) = mk_expression_list(NULL, (yyvsp[0])); }
#line 3176 "awkgram.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1232 "awkgram.y" /* yacc.c:1646  */
    {
		(yyval) = mk_expression_list((yyvsp[-2]), (yyvsp[0]));
		yyerrok;
	  }
#line 3185 "awkgram.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1237 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 3191 "awkgram.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1239 "awkgram.y" /* yacc.c:1646  */
    {
		/*
		 * Returning the expression list instead of NULL lets
		 * snode get a list of arguments that it can count.
		 */
		(yyval) = (yyvsp[-1]);
	  }
#line 3203 "awkgram.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1247 "awkgram.y" /* yacc.c:1646  */
    {
		/* Ditto */
		(yyval) = mk_expression_list((yyvsp[-2]), (yyvsp[0]));
	  }
#line 3212 "awkgram.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1252 "awkgram.y" /* yacc.c:1646  */
    {
		/* Ditto */
		(yyval) = (yyvsp[-2]);
	  }
#line 3221 "awkgram.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1261 "awkgram.y" /* yacc.c:1646  */
    {
		if (do_lint && (yyvsp[0])->lasti->opcode == Op_match_rec)
			lintwarn_ln((yyvsp[-1])->source_line,
				_("regular expression on right of assignment"));
		(yyval) = mk_assignment((yyvsp[-2]), (yyvsp[0]), (yyvsp[-1]));
	  }
#line 3232 "awkgram.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1268 "awkgram.y" /* yacc.c:1646  */
    {	(yyval) = mk_boolean((yyvsp[-2]), (yyvsp[0]), (yyvsp[-1])); }
#line 3238 "awkgram.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1270 "awkgram.y" /* yacc.c:1646  */
    {	(yyval) = mk_boolean((yyvsp[-2]), (yyvsp[0]), (yyvsp[-1])); }
#line 3244 "awkgram.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1272 "awkgram.y" /* yacc.c:1646  */
    {
		if ((yyvsp[-2])->lasti->opcode == Op_match_rec)
			warning_ln((yyvsp[-1])->source_line,
				_("regular expression on left of `~' or `!~' operator"));

		if ((yyvsp[0])->lasti == (yyvsp[0])->nexti && (yyvsp[0])->nexti->opcode == Op_match_rec) {
			(yyvsp[-1])->memory = (yyvsp[0])->nexti->memory;
			bcfree((yyvsp[0])->nexti);	/* Op_match_rec */
			bcfree((yyvsp[0]));			/* Op_list */
			(yyval) = list_append((yyvsp[-2]), (yyvsp[-1]));
		} else {
			(yyvsp[-1])->memory = make_regnode(Node_dynregex, NULL);
			(yyval) = list_append(list_merge((yyvsp[-2]), (yyvsp[0])), (yyvsp[-1]));
		}
	  }
#line 3264 "awkgram.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1288 "awkgram.y" /* yacc.c:1646  */
    {
		if (do_lint_old)
			warning_ln((yyvsp[-1])->source_line,
				_("old awk does not support the keyword `in' except after `for'"));
		(yyvsp[0])->nexti->opcode = Op_push_array;
		(yyvsp[-1])->opcode = Op_in_array;
		(yyvsp[-1])->expr_count = 1;
		(yyval) = list_append(list_merge((yyvsp[-2]), (yyvsp[0])), (yyvsp[-1]));
	  }
#line 3278 "awkgram.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1298 "awkgram.y" /* yacc.c:1646  */
    {
		if (do_lint && (yyvsp[0])->lasti->opcode == Op_match_rec)
			lintwarn_ln((yyvsp[-1])->source_line,
				_("regular expression on right of comparison"));
		(yyval) = list_append(list_merge((yyvsp[-2]), (yyvsp[0])), (yyvsp[-1]));
	  }
#line 3289 "awkgram.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1305 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = mk_condition((yyvsp[-4]), (yyvsp[-3]), (yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])); }
#line 3295 "awkgram.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1307 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 3301 "awkgram.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1309 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 3307 "awkgram.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1314 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 3313 "awkgram.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1316 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 3319 "awkgram.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1318 "awkgram.y" /* yacc.c:1646  */
    {	
		(yyvsp[0])->opcode = Op_assign_quotient;
		(yyval) = (yyvsp[0]);
	  }
#line 3328 "awkgram.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1326 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 3334 "awkgram.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1328 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 3340 "awkgram.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1333 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 3346 "awkgram.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1335 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 3352 "awkgram.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1340 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 3358 "awkgram.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1342 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 3364 "awkgram.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1344 "awkgram.y" /* yacc.c:1646  */
    {
		int count = 2;
		bool is_simple_var = false;

		if ((yyvsp[-1])->lasti->opcode == Op_concat) {
			/* multiple (> 2) adjacent strings optimization */
			is_simple_var = ((yyvsp[-1])->lasti->concat_flag & CSVAR);
			count = (yyvsp[-1])->lasti->expr_count + 1;
			(yyvsp[-1])->lasti->opcode = Op_no_op;
		} else {
			is_simple_var = ((yyvsp[-1])->nexti->opcode == Op_push
					&& (yyvsp[-1])->lasti == (yyvsp[-1])->nexti); /* first exp. is a simple
					                             * variable?; kludge for use
					                             * in Op_assign_concat.
		 			                             */
		}

		if (do_optimize
			&& (yyvsp[-1])->nexti == (yyvsp[-1])->lasti && (yyvsp[-1])->nexti->opcode == Op_push_i
			&& (yyvsp[0])->nexti == (yyvsp[0])->lasti && (yyvsp[0])->nexti->opcode == Op_push_i
		) {
			NODE *n1 = (yyvsp[-1])->nexti->memory;
			NODE *n2 = (yyvsp[0])->nexti->memory;
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
			bcfree((yyvsp[0])->nexti);
			bcfree((yyvsp[0]));
			(yyval) = (yyvsp[-1]);
		} else {
			(yyval) = list_append(list_merge((yyvsp[-1]), (yyvsp[0])), instruction(Op_concat));
			(yyval)->lasti->concat_flag = (is_simple_var ? CSVAR : 0);
			(yyval)->lasti->expr_count = count;
			if (count > max_args)
				max_args = count;
		}
	  }
#line 3415 "awkgram.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1396 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = mk_binary((yyvsp[-2]), (yyvsp[0]), (yyvsp[-1])); }
#line 3421 "awkgram.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1398 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = mk_binary((yyvsp[-2]), (yyvsp[0]), (yyvsp[-1])); }
#line 3427 "awkgram.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1400 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = mk_binary((yyvsp[-2]), (yyvsp[0]), (yyvsp[-1])); }
#line 3433 "awkgram.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1402 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = mk_binary((yyvsp[-2]), (yyvsp[0]), (yyvsp[-1])); }
#line 3439 "awkgram.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1404 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = mk_binary((yyvsp[-2]), (yyvsp[0]), (yyvsp[-1])); }
#line 3445 "awkgram.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1406 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = mk_binary((yyvsp[-2]), (yyvsp[0]), (yyvsp[-1])); }
#line 3451 "awkgram.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1408 "awkgram.y" /* yacc.c:1646  */
    {
		/*
		 * In BEGINFILE/ENDFILE, allow `getline [var] < file'
		 */

		if ((rule == BEGINFILE || rule == ENDFILE) && (yyvsp[0]) == NULL)
			error_ln((yyvsp[-2])->source_line,
				 _("non-redirected `getline' invalid inside `%s' rule"), ruletab[rule]);
		if (do_lint && rule == END && (yyvsp[0]) == NULL)
			lintwarn_ln((yyvsp[-2])->source_line,
				_("non-redirected `getline' undefined inside END action"));
		(yyval) = mk_getline((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0]), redirect_input);
	  }
#line 3469 "awkgram.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1422 "awkgram.y" /* yacc.c:1646  */
    {
		(yyvsp[0])->opcode = Op_postincrement;
		(yyval) = mk_assignment((yyvsp[-1]), NULL, (yyvsp[0]));
	  }
#line 3478 "awkgram.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1427 "awkgram.y" /* yacc.c:1646  */
    {
		(yyvsp[0])->opcode = Op_postdecrement;
		(yyval) = mk_assignment((yyvsp[-1]), NULL, (yyvsp[0]));
	  }
#line 3487 "awkgram.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1432 "awkgram.y" /* yacc.c:1646  */
    {
		if (do_lint_old) {
		    warning_ln((yyvsp[-1])->source_line,
				_("old awk does not support the keyword `in' except after `for'"));
		    warning_ln((yyvsp[-1])->source_line,
				_("old awk does not support multidimensional arrays"));
		}
		(yyvsp[0])->nexti->opcode = Op_push_array;
		(yyvsp[-1])->opcode = Op_in_array;
		if ((yyvsp[-3]) == NULL) {	/* error */
			errcount++;
			(yyvsp[-1])->expr_count = 0;
			(yyval) = list_merge((yyvsp[0]), (yyvsp[-1]));
		} else {
			INSTRUCTION *t = (yyvsp[-3]);
			(yyvsp[-1])->expr_count = count_expressions(&t, false);
			(yyval) = list_append(list_merge(t, (yyvsp[0])), (yyvsp[-1]));
		}
	  }
#line 3511 "awkgram.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1457 "awkgram.y" /* yacc.c:1646  */
    {
		  (yyval) = mk_getline((yyvsp[-1]), (yyvsp[0]), (yyvsp[-3]), (yyvsp[-2])->redir_type);
		  bcfree((yyvsp[-2]));
		}
#line 3520 "awkgram.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1463 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = mk_binary((yyvsp[-2]), (yyvsp[0]), (yyvsp[-1])); }
#line 3526 "awkgram.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1465 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = mk_binary((yyvsp[-2]), (yyvsp[0]), (yyvsp[-1])); }
#line 3532 "awkgram.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1467 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = mk_binary((yyvsp[-2]), (yyvsp[0]), (yyvsp[-1])); }
#line 3538 "awkgram.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1469 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = mk_binary((yyvsp[-2]), (yyvsp[0]), (yyvsp[-1])); }
#line 3544 "awkgram.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1471 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = mk_binary((yyvsp[-2]), (yyvsp[0]), (yyvsp[-1])); }
#line 3550 "awkgram.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1473 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = mk_binary((yyvsp[-2]), (yyvsp[0]), (yyvsp[-1])); }
#line 3556 "awkgram.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1478 "awkgram.y" /* yacc.c:1646  */
    {
		(yyval) = list_create((yyvsp[0]));
	  }
#line 3564 "awkgram.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1482 "awkgram.y" /* yacc.c:1646  */
    {
		if ((yyvsp[0])->opcode == Op_match_rec) {
			(yyvsp[0])->opcode = Op_nomatch;
			(yyvsp[-1])->opcode = Op_push_i;
			(yyvsp[-1])->memory = make_number(0.0);	
			(yyval) = list_append(list_append(list_create((yyvsp[-1])),
						instruction(Op_field_spec)), (yyvsp[0]));
		} else {
			if (do_optimize && (yyvsp[0])->nexti == (yyvsp[0])->lasti
					&& (yyvsp[0])->nexti->opcode == Op_push_i
					&& ((yyvsp[0])->nexti->memory->flags & (MPFN|MPZN)) == 0
			) {
				NODE *n = (yyvsp[0])->nexti->memory;
				if ((n->flags & (STRCUR|STRING)) != 0) {
					n->numbr = (AWKNUM) (n->stlen == 0);
					n->flags &= ~(STRCUR|STRING);
					n->flags |= (NUMCUR|NUMBER);
					efree(n->stptr);
					n->stptr = NULL;
					n->stlen = 0;
				} else
					n->numbr = (AWKNUM) (n->numbr == 0.0);
				bcfree((yyvsp[-1]));
				(yyval) = (yyvsp[0]);
			} else {
				(yyvsp[-1])->opcode = Op_not;
				add_lint((yyvsp[0]), LINT_assign_in_cond);
				(yyval) = list_append((yyvsp[0]), (yyvsp[-1]));
			}
		}
	   }
#line 3600 "awkgram.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1514 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 3606 "awkgram.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1516 "awkgram.y" /* yacc.c:1646  */
    {
		(yyval) = snode((yyvsp[-1]), (yyvsp[-3]));
		if ((yyval) == NULL)
			YYABORT;
	  }
#line 3616 "awkgram.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1522 "awkgram.y" /* yacc.c:1646  */
    {
		(yyval) = snode((yyvsp[-1]), (yyvsp[-3]));
		if ((yyval) == NULL)
			YYABORT;
	  }
#line 3626 "awkgram.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1528 "awkgram.y" /* yacc.c:1646  */
    {
		static bool warned = false;

		if (do_lint && ! warned) {
			warned = true;
			lintwarn_ln((yyvsp[0])->source_line,
				_("call of `length' without parentheses is not portable"));
		}
		(yyval) = snode(NULL, (yyvsp[0]));
		if ((yyval) == NULL)
			YYABORT;
	  }
#line 3643 "awkgram.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1543 "awkgram.y" /* yacc.c:1646  */
    {
		(yyvsp[-1])->opcode = Op_preincrement;
		(yyval) = mk_assignment((yyvsp[0]), NULL, (yyvsp[-1]));
	  }
#line 3652 "awkgram.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1548 "awkgram.y" /* yacc.c:1646  */
    {
		(yyvsp[-1])->opcode = Op_predecrement;
		(yyval) = mk_assignment((yyvsp[0]), NULL, (yyvsp[-1]));
	  }
#line 3661 "awkgram.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1553 "awkgram.y" /* yacc.c:1646  */
    {
		(yyval) = list_create((yyvsp[0]));
	  }
#line 3669 "awkgram.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1557 "awkgram.y" /* yacc.c:1646  */
    {
		(yyval) = list_create((yyvsp[0]));
	  }
#line 3677 "awkgram.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1561 "awkgram.y" /* yacc.c:1646  */
    {
		if ((yyvsp[0])->lasti->opcode == Op_push_i
			&& ((yyvsp[0])->lasti->memory->flags & (STRCUR|STRING)) == 0
		) {
			NODE *n = (yyvsp[0])->lasti->memory;
			(void) force_number(n);
			negate_num(n);			
			(yyval) = (yyvsp[0]);
			bcfree((yyvsp[-1]));
		} else {
			(yyvsp[-1])->opcode = Op_unary_minus;
			(yyval) = list_append((yyvsp[0]), (yyvsp[-1]));
		}
	  }
#line 3696 "awkgram.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1576 "awkgram.y" /* yacc.c:1646  */
    {
	    /*
	     * was: $$ = $2
	     * POSIX semantics: force a conversion to numeric type
	     */
		(yyvsp[-1])->opcode = Op_plus_i;
		(yyvsp[-1])->memory = make_number(0.0);
		(yyval) = list_append((yyvsp[0]), (yyvsp[-1]));
	  }
#line 3710 "awkgram.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1589 "awkgram.y" /* yacc.c:1646  */
    {
		func_use((yyvsp[0])->lasti->func_name, FUNC_USE);
		(yyval) = (yyvsp[0]);
	  }
#line 3719 "awkgram.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1594 "awkgram.y" /* yacc.c:1646  */
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
		
		f = (yyvsp[0])->lasti;
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

		(yyval) = list_prepend((yyvsp[0]), t);
	  }
#line 3756 "awkgram.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1630 "awkgram.y" /* yacc.c:1646  */
    {
		param_sanity((yyvsp[-1]));
		(yyvsp[-3])->opcode = Op_func_call;
		(yyvsp[-3])->func_body = NULL;
		if ((yyvsp[-1]) == NULL) {	/* no argument or error */
			((yyvsp[-3]) + 1)->expr_count = 0;
			(yyval) = list_create((yyvsp[-3]));
		} else {
			INSTRUCTION *t = (yyvsp[-1]);
			((yyvsp[-3]) + 1)->expr_count = count_expressions(&t, true); 
			(yyval) = list_append(t, (yyvsp[-3]));
		}
	  }
#line 3774 "awkgram.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1647 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 3780 "awkgram.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1649 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 3786 "awkgram.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1654 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 3792 "awkgram.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1656 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 3798 "awkgram.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1661 "awkgram.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 3804 "awkgram.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1663 "awkgram.y" /* yacc.c:1646  */
    {
		(yyval) = list_merge((yyvsp[-1]), (yyvsp[0]));
	  }
#line 3812 "awkgram.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1670 "awkgram.y" /* yacc.c:1646  */
    {
		INSTRUCTION *ip = (yyvsp[0])->lasti; 
		int count = ip->sub_count;	/* # of SUBSEP-seperated expressions */
		if (count > 1) {
			/* change Op_subscript or Op_sub_array to Op_concat */
			ip->opcode = Op_concat;
			ip->concat_flag = CSUBSEP;
			ip->expr_count = count;
		} else
			ip->opcode = Op_no_op;
		sub_counter++;	/* count # of dimensions */
		(yyval) = (yyvsp[0]);
	  }
#line 3830 "awkgram.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1687 "awkgram.y" /* yacc.c:1646  */
    {
		INSTRUCTION *t = (yyvsp[-1]);
		if ((yyvsp[-1]) == NULL) {
			error_ln((yyvsp[0])->source_line,
				_("invalid subscript expression"));
			/* install Null string as subscript. */
			t = list_create(instruction(Op_push_i));
			t->nexti->memory = dupnode(Nnull_string);
			(yyvsp[0])->sub_count = 1;			
		} else
			(yyvsp[0])->sub_count = count_expressions(&t, false);
		(yyval) = list_append(t, (yyvsp[0]));
	  }
#line 3848 "awkgram.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1704 "awkgram.y" /* yacc.c:1646  */
    {	(yyval) = (yyvsp[0]); }
#line 3854 "awkgram.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1706 "awkgram.y" /* yacc.c:1646  */
    {
		(yyval) = list_merge((yyvsp[-1]), (yyvsp[0]));
	  }
#line 3862 "awkgram.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1713 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 3868 "awkgram.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1718 "awkgram.y" /* yacc.c:1646  */
    {
		char *var_name = (yyvsp[0])->lextok;

		(yyvsp[0])->opcode = Op_push;
		(yyvsp[0])->memory = variable((yyvsp[0])->source_line, var_name, Node_var_new);
		(yyval) = list_create((yyvsp[0]));
	  }
#line 3880 "awkgram.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1726 "awkgram.y" /* yacc.c:1646  */
    {
		char *arr = (yyvsp[-1])->lextok;
		(yyvsp[-1])->memory = variable((yyvsp[-1])->source_line, arr, Node_var_new);
		(yyvsp[-1])->opcode = Op_push_array;
		(yyval) = list_prepend((yyvsp[0]), (yyvsp[-1]));
	  }
#line 3891 "awkgram.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1736 "awkgram.y" /* yacc.c:1646  */
    {
		INSTRUCTION *ip = (yyvsp[0])->nexti;
		if (ip->opcode == Op_push
			&& ip->memory->type == Node_var
			&& ip->memory->var_update
		) {
			(yyval) = list_prepend((yyvsp[0]), instruction(Op_var_update));
			(yyval)->nexti->update_var = ip->memory->var_update;
		} else
			(yyval) = (yyvsp[0]);
	  }
#line 3907 "awkgram.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1748 "awkgram.y" /* yacc.c:1646  */
    {
		(yyval) = list_append((yyvsp[-1]), (yyvsp[-2]));
		if ((yyvsp[0]) != NULL)
			mk_assignment((yyvsp[-1]), NULL, (yyvsp[0]));
	  }
#line 3917 "awkgram.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1757 "awkgram.y" /* yacc.c:1646  */
    {
		(yyvsp[0])->opcode = Op_postincrement;
	  }
#line 3925 "awkgram.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1761 "awkgram.y" /* yacc.c:1646  */
    {
		(yyvsp[0])->opcode = Op_postdecrement;
	  }
#line 3933 "awkgram.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1764 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 3939 "awkgram.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1772 "awkgram.y" /* yacc.c:1646  */
    { yyerrok; }
#line 3945 "awkgram.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1776 "awkgram.y" /* yacc.c:1646  */
    { yyerrok; }
#line 3951 "awkgram.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1785 "awkgram.y" /* yacc.c:1646  */
    { yyerrok; }
#line 3957 "awkgram.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1789 "awkgram.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); yyerrok; }
#line 3963 "awkgram.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1793 "awkgram.y" /* yacc.c:1646  */
    { yyerrok; }
#line 3969 "awkgram.c" /* yacc.c:1646  */
    break;


#line 3973 "awkgram.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 1795 "awkgram.y" /* yacc.c:1906  */


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
#	define	DEBUG_USE	0x2000	/* for use by developers */
	
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
{"adump",	Op_builtin,    LEX_BUILTIN,	GAWKX|A(1)|A(2)|DEBUG_USE,	do_adump,	0},
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
{"div",		Op_builtin,	 LEX_BUILTIN,	GAWKX|A(3),	do_div,	MPF(div)},
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
{"stopme",	Op_builtin,	LEX_BUILTIN,	GAWKX|A(0)|DEBUG_USE,	stopme,		0},
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

/* getfname --- return name of a builtin function (for pretty printing) */

const char *
getfname(NODE *(*fptr)(int))
{
	int i, j;

	j = sizeof(tokentab) / sizeof(tokentab[0]);
	/* linear search, no other way to do it */
	for (i = 0; i < j; i++) 
		if (tokentab[i].ptr == fptr || tokentab[i].ptr2 == fptr)
			return tokentab[i].operator;

	return NULL;
}

/* negate_num --- negate a number in NODE */

void
negate_num(NODE *n)
{
#ifdef HAVE_MPFR
	int tval = 0;
#endif

	if (! is_mpg_number(n)) {
		n->numbr = -n->numbr;
		return;
	}

#ifdef HAVE_MPFR
	if (is_mpg_integer(n)) {
		if (! iszero(n)) {
			mpz_neg(n->mpg_i, n->mpg_i);
			return;
		}

		/*
		 * 0 --> -0 conversion. Requires turning the MPG integer
		 * into an MPFR float.
		 */

		mpz_clear(n->mpg_i);	/* release the integer storage */

		/* Convert and fall through. */
		tval = mpfr_set_d(n->mpg_numbr, 0.0, ROUND_MODE);
		IEEE_FMT(n->mpg_numbr, tval);
		n->flags &= ~MPZN;
		n->flags |= MPFN;
	}

	/* mpfr float case */
	tval = mpfr_neg(n->mpg_numbr, n->mpg_numbr, ROUND_MODE);
	IEEE_FMT(n->mpg_numbr, tval);
#endif
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
			if (program_comment != NULL) {
				(void) list_prepend(cp, program_comment);
			}  
			if (comment != NULL)
				(void) list_append(cp, comment);
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

	if (program_comment != NULL) {
		(void) list_prepend(cp, program_comment);
	}  
	if (comment != NULL) {
		(void) list_append(cp, comment);
	} 
	(void) list_append(cp, ip_atexit);
	(void) list_append(cp, instruction(Op_stop));

out:
	/* delete the Op_list, not needed */
	tmp = cp->nexti;
	bcfree(cp);
	/* these variables are not used again but zap them anyway.  */
	comment = NULL;
	function_comment = NULL;
	program_comment = NULL;
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

/* free_srcfile --- free a SRCFILE struct */

void
free_srcfile(SRCFILE *thisfile)
{
	efree(thisfile->src);
	efree(thisfile);
}

/* do_add_srcfile --- add one item to srcfiles */

static SRCFILE *
do_add_srcfile(enum srctype stype, char *src, char *path, SRCFILE *thisfile)
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
	if (stype == SRC_EXTLIB)
		extensions_used = true;
	return s;
}

/* add_srcfile --- add one item to srcfiles after checking if
 *				a source file exists and not already in list.
 */

SRCFILE *
add_srcfile(enum srctype stype, char *src, SRCFILE *thisfile, bool *already_included, int *errcode)
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
			if (do_lint && newfile && ! warned) {
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

/* check_bad_char --- fatal if c isn't allowed in gawk source code */

/*
 * The error message was inspired by someone who decided to put
 * a physical \0 byte into the source code to see what would
 * happen and then filed a bug report about it.  Sigh.
 */

static void
check_bad_char(int c)
{
	/* allow escapes. needed for autoconf. bleah. */
	switch (c) {
	case '\a':
	case '\b':
	case '\f':
	case '\n':
	case '\r':
	case '\t':
		return;
	default:
		break;
	}

	if (iscntrl(c) && ! isspace(c))
		fatal(_("PEBKAC error: invalid character '\\%03o' in source code"), c & 0xFF);
}

/* nextc --- get the next input character */

static int
nextc(bool check_for_bad)
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
	
			for (idx = 0; lexptr + idx < lexend; idx++) {
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
		if (check_for_bad)
			check_bad_char(*lexptr);

		return (int) (unsigned char) *lexptr++;
	} else {
		do {
			if (lexeof)
				return END_FILE;
			if (lexptr && lexptr < lexend) {
				if (check_for_bad)
					check_bad_char(*lexptr);
				return ((int) (unsigned char) *lexptr++);
			}
		} while (get_src_buf());
		return END_SRC;
	}
}

/* pushback --- push a character back on the input */

static inline void
pushback(void)
{
	if (gawk_mb_cur_max > 1)
		cur_ring_idx = (cur_ring_idx == 0)? RING_BUFFER_SIZE - 1 :
			cur_ring_idx - 1;
	(! lexeof && lexptr && lexptr > lexptr_begin ? lexptr-- : lexptr);
}

/* check_comment --- check for block comment */

void
check_comment(void)
{
	if (comment != NULL) {
		if (first_rule) {
			program_comment = comment;
		} else 
			block_comment = comment;
		comment = NULL;
	}
	first_rule = false;
}

/*
 * get_comment --- collect comment text.
 * 	Flag = EOL_COMMENT for end-of-line comments.
 * 	Flag = FULL_COMMENT for self-contained comments.
 */

int
get_comment(int flag)
{
	int c;
	int sl;
	tok = tokstart;
	tokadd('#');
	sl = sourceline;

	while (true) {
		while ((c = nextc(false)) != '\n' && c != END_FILE) {
			tokadd(c);
		}
		if (flag == EOL_COMMENT) {
			/* comment at end of line.  */
			if (c == '\n')
				tokadd(c);
			break;
		}
		if (c == '\n') {
			tokadd(c);
			sourceline++;
			do {
				c = nextc(false);
				if (c == '\n') {
					sourceline++;
					tokadd(c);
				}
			} while (isspace(c) && c != END_FILE);
			if (c == END_FILE)
				break;
			else if (c != '#') {
				pushback();
				sourceline--;
				break;
			} else
				tokadd(c);
		} else
			break;
	}
	comment = bcalloc(Op_comment, 1, sl);
	comment->source_file = source;
	comment->memory = make_str_node(tokstart, tok - tokstart, 0);
	comment->memory->comment_type = flag;

	return c;
}

/* split_comment --- split initial comment text into program and function parts */

static void
split_comment(void)
{
	char *p;
	int l;
	NODE *n;

	p = comment->memory->stptr;
	l = comment->memory->stlen - 3;
	/* have at least two comments so split at last blank line (\n\n)  */
	while (l >= 0) {
		if (p[l] == '\n' && p[l+1] == '\n') {
			function_comment = comment;
			n = function_comment->memory;
			function_comment->memory = make_str_node(p + l + 2, n->stlen - l - 2, 0);
			/* create program comment  */
			program_comment = bcalloc(Op_comment, 1, sourceline);
			program_comment->source_file = comment->source_file;
			p[l + 2] = 0;
			program_comment->memory = make_str_node(p, l + 2, 0);
			comment = NULL;
			freenode(n);
			break;
		}
		else
			l--;
	}
}

/* allow_newline --- allow newline after &&, ||, ? and : */

static void
allow_newline(void)
{
	int c;

	for (;;) {
		c = nextc(true);
		if (c == END_FILE) {
			pushback();
			break;
		}
		if (c == '#') {
			if (do_pretty_print && ! do_profile) {
			/* collect comment byte code iff doing pretty print but not profiling.  */
				c = get_comment(EOL_COMMENT);
			} else {
				while ((c = nextc(false)) != '\n' && c != END_FILE)
					continue;
			}
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

static int
newline_eof()
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

	c = nextc(true);
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
			c = nextc(true);

			if (gawk_mb_cur_max == 1 || nextc_is_1stbyte) switch (c) {
			case '[':
				/* one day check for `.' and `=' too */
				if (nextc(true) == ':' || in_brack == 0)
					in_brack++;
				pushback();
				break;
			case ']':
				if (tok[-1] == '['
				    || (tok[-2] == '[' && tok[-1] == '^'))
					/* do nothing */;
				else
					in_brack--;
				break;
			case '\\':
				if ((c = nextc(true)) == END_FILE) {
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
					int peek = nextc(true);

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
	while ((c = nextc(true)) == ' ' || c == '\t' || c == '\r')
		continue;

	lexeme = lexptr ? lexptr - 1 : lexptr;
	thisline = NULL;
	tok = tokstart;

	if (gawk_mb_cur_max == 1 || nextc_is_1stbyte)
	switch (c) {
	case END_SRC:
		return 0;

	case END_FILE:
		return lasttok = NEWLINE_EOF;

	case '\n':
		sourceline++;
		return lasttok = NEWLINE;

	case '#':		/* it's a comment */
		if (do_pretty_print && ! do_profile) {
			/*
			 * Collect comment byte code iff doing pretty print
			 * but not profiling.
			 */
			if (lasttok == NEWLINE || lasttok == 0)
				c = get_comment(FULL_COMMENT);
			else
				c = get_comment(EOL_COMMENT);

			if (c == END_FILE)
				return lasttok = NEWLINE_EOF;
		} else {
			while ((c = nextc(false)) != '\n') {
				if (c == END_FILE)
					return lasttok = NEWLINE_EOF;
			}
		}
		sourceline++;
		return lasttok = NEWLINE;

	case '@':
		return lasttok = '@';

	case '\\':
#ifdef RELAXED_CONTINUATION
		/*
		 * This code purports to allow comments and/or whitespace
		 * after the `\' at the end of a line used for continuation.
		 * Use it at your own risk. We think it's a bad idea, which
		 * is why it's not on by default.
		 */
		if (! do_traditional) {
			/* strip trailing white-space and/or comment */
			while ((c = nextc(true)) == ' ' || c == '\t' || c == '\r')
				continue;
			if (c == '#') {
				static bool warned = false;

				if (do_lint && ! warned) {
					warned = true;
					lintwarn(
		_("use of `\\ #...' line continuation is not portable"));
				}
				if (do_pretty_print && ! do_profile)
					c = get_comment(EOL_COMMENT);
				else {
					while ((c = nextc(false)) != '\n')
						if (c == END_FILE)
							break;
				}
			}
			pushback();
		}
#endif /* RELAXED_CONTINUATION */
		c = nextc(true);
		if (c == '\r')	/* allow MS-DOS files. bleah */
			c = nextc(true);
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
		c = nextc(true);
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
		if ((c = nextc(true)) == '=') {
			yylval = GET_INSTRUCTION(Op_assign_times);
			return lasttok = ASSIGNOP;
		} else if (do_posix) {
			pushback();
			yylval = GET_INSTRUCTION(Op_times);
			return lasttok = '*';
		} else if (c == '*') {
			/* make ** and **= aliases for ^ and ^= */
			static bool did_warn_op = false, did_warn_assgn = false;

			if (nextc(true) == '=') {
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
		if (nextc(true) == '=') {
			pushback();
			return lasttok = SLASH_BEFORE_EQUAL;
		}
		pushback();
		yylval = GET_INSTRUCTION(Op_quotient);
		return lasttok = '/';

	case '%':
		if (nextc(true) == '=') {
			yylval = GET_INSTRUCTION(Op_assign_mod);
			return lasttok = ASSIGNOP;
		}
		pushback();
		yylval = GET_INSTRUCTION(Op_mod);
		return lasttok = '%';

	case '^':
	{
		static bool did_warn_op = false, did_warn_assgn = false;

		if (nextc(true) == '=') {
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
		if ((c = nextc(true)) == '=') {
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
		if ((c = nextc(true)) == '=') {
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
		if (nextc(true) == '=') {
			yylval = GET_INSTRUCTION(Op_leq);
			return lasttok = RELOP;
		}
		yylval = GET_INSTRUCTION(Op_less);
		pushback();
		return lasttok = '<';

	case '=':
		if (nextc(true) == '=') {
			yylval = GET_INSTRUCTION(Op_equal);
			return lasttok = RELOP;
		}
		yylval = GET_INSTRUCTION(Op_assign);
		pushback();
		return lasttok = ASSIGN;

	case '>':
		if ((c = nextc(true)) == '=') {
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
		did_newline = true;
		--lexptr;	/* pick up } next time */
		return lasttok = NEWLINE;

	case '"':
	string:
		esc_seen = false;
		/*
		 * Allow any kind of junk in quoted string,
		 * so pass false to nextc().
		 */
		while ((c = nextc(false)) != '"') {
			if (c == '\n') {
				pushback();
				yyerror(_("unterminated string"));
				return lasttok = LEX_EOF;
			}
			if ((gawk_mb_cur_max == 1 || nextc_is_1stbyte) &&
			    c == '\\') {
				c = nextc(true);
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
		if ((c = nextc(true)) == '=') {
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
		c = nextc(true);
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
					int peek = nextc(true);

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
				if ((c = nextc(true)) == '-' || c == '+') {
					int c2 = nextc(true);

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
			c = nextc(true);
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
		if ((c = nextc(true)) == '&') {
			yylval = GET_INSTRUCTION(Op_and);
			allow_newline();
			return lasttok = LEX_AND;
		}
		pushback();
		yylval = GET_INSTRUCTION(Op_symbol);
		return lasttok = '&';

	case '|':
		if ((c = nextc(true)) == '|') {
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

	if (c != '_' && ! is_alpha(c)) {
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
		if ((c = nextc(true)) == '"') {
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
		c = nextc(true);
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
			if (! do_traditional
			    && (class == LEX_PRINT || class == LEX_PRINTF)) {
				switch (lasttok) {
				case NEWLINE:
				case LEX_ELSE:
				case ':':	/* from case */
				case ';':
				case '{':
				case ')':
					break;
				default:
					if (class == LEX_PRINT) {
						class = LEX_PRINT_EXP;
						yylval->opcode = Op_K_print_exp;
					}
					if (class == LEX_PRINTF) {
						class = LEX_PRINTF_EXP;
						yylval->opcode = Op_K_printf_exp;
					}
					break;
				}
			}
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
	/* N.B.: If necessary, add special processing for alternate builtin, below */
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
	} else if (r->builtin == do_div
#ifdef HAVE_MPFR
		   || r->builtin == MPF(div)
#endif
			) {
		arg = subn->nexti->lasti->nexti->lasti->nexti;	/* 3rd arg list */
		ip = arg->lasti;
		if (ip->opcode == Op_push)
			ip->opcode = Op_push_array;
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

	if (do_optimize && def->lasti->opcode == Op_pop) {
		/* tail call which does not return any value. */

		INSTRUCTION *t;

		for (t = def->nexti; t->nexti != def->lasti; t = t->nexti)
			;
		if (t->opcode == Op_func_call
		    && strcmp(t->func_name, thisfunc->vname) == 0)
			(t + 1)->tail_call = true;
	}

	/* add any pre-function comment to start of action for profile.c  */

	if (function_comment != NULL) {
		function_comment->source_line = 0;
		(void) list_prepend(def, function_comment);
		function_comment = NULL;
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

	for (fp = ftable[ind]; fp != NULL; fp = fp->next)
		if (strcmp(fp->name, name) == 0)
			goto update_value;

	/* not in the table, fall through to allocate a new one */

	emalloc(fp, struct fdesc *, sizeof(struct fdesc), "func_use");
	memset(fp, '\0', sizeof(struct fdesc));
	emalloc(fp->name, char *, len + 1, "func_use");
	strcpy(fp->name, name);
	fp->next = ftable[ind];
	ftable[ind] = fp;

update_value:
	if (how == FUNC_DEFINE)
		fp->defined++;
	else if (how == FUNC_EXT) {
		fp->defined++;
		fp->extension++;
	} else
		fp->used++;
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

/* process_deferred --- if the program uses SYMTAB or extensions, load deferred variables */

static void
process_deferred()
{
	struct deferred_variable *dv;

	if (symtab_used || extensions_used) {
		for (dv = deferred_variables; dv != NULL; dv = dv->next) {
			(void) dv->load_func();
		}
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
		if (do_optimize
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
		if (block_comment != NULL) {
			ip = list_prepend(list_prepend(action, block_comment), rp);
			block_comment = NULL;
		} else
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
	case Op_field_assign:
		yyerror(_("cannot assign a value to the result of a field post-increment expression"));
		break;
	default:
		yyerror(_("invalid target of assignment (opcode %s)"),
				opcode2str(tp->opcode));
		break;
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

	if (   i1->opcode != Op_assign
	    && i1->opcode != Op_field_assign) 
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
				if (isnoeffect(ip->opcode))
					lintwarn_ln(ip->source_line, ("statement may have no effect"));
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

/* mk_print --- print or printf */

static INSTRUCTION *
mk_print(INSTRUCTION *op, INSTRUCTION *exp_list, INSTRUCTION *redir)
{
	INSTRUCTION *ret = NULL;

	/*
	 * Optimization: plain `print' has no expression list, so exp_list is null.
	 * If exp_list is NULL or is a bytecode list for $0 use Op_K_print_rec,
	 * which is faster for these two cases.
	 */

	if ((op->opcode == Op_K_print || op->opcode == Op_K_print_exp) &&
		(exp_list == NULL
			|| (exp_list->lasti->opcode == Op_field_spec
				&& exp_list->nexti->nexti->nexti == exp_list->lasti
				&& exp_list->nexti->nexti->opcode == Op_push_i
				&& exp_list->nexti->nexti->memory->type == Node_val)
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

		if (exp_list != NULL) {
			NODE *n = exp_list->nexti->nexti->memory;

			if (! iszero(n))
				goto regular_print;

			bcfree(exp_list->lasti);			/* Op_field_spec */
			unref(n);				/* Node_val */
			bcfree(exp_list->nexti->nexti);		/* Op_push_i */
			bcfree(exp_list->nexti);			/* Op_list */
			bcfree(exp_list);				/* Op_list */
		} else {
			if (do_lint && (rule == BEGIN || rule == END) && ! warned) {
				warned = true;
				lintwarn_ln(op->source_line,
	_("plain `print' in BEGIN or END rule should probably be `print \"\"'"));
			}
		}

		op->expr_count = 0;
		op->opcode = (op->opcode == Op_K_print ? Op_K_print_rec : Op_K_print_rec_exp);
		if (redir == NULL) {    /* no redircetion */
			op->redir_type = redirect_none;
			ret = list_create(op);
		} else {
			INSTRUCTION *ip;
			ip = redir->nexti;
			op->redir_type = ip->redir_type;
			redir->nexti = ip->nexti;
			bcfree(ip);
			ret = list_append(redir, op);
		}
	} else {
		/*   -----------------
		 *    [ output_redir    ]
		 *    [ redirect exp    ]
		 *   -----------------
		 *    [ expression_list ]
		 *   ------------------
		 *    [op | NULL | redir_type | expr_count]
		 *
		 */
regular_print:	 
		if (redir == NULL) {		/* no redirection */
			if (exp_list == NULL)	{	/* printf without arg */
				op->expr_count = 0;
				op->redir_type = redirect_none;
				ret = list_create(op);
			} else {
				INSTRUCTION *t = exp_list;
				op->expr_count = count_expressions(&t, false);
				op->redir_type = redirect_none;
				ret = list_append(t, op);
			}
		} else {
			INSTRUCTION *ip;
			ip = redir->nexti;
			op->redir_type = ip->redir_type;
			redir->nexti = ip->nexti;
			bcfree(ip);
			if (exp_list == NULL) {
				op->expr_count = 0;
				ret = list_append(redir, op);
			} else {
				INSTRUCTION *t = exp_list;
				op->expr_count = count_expressions(&t, false);
				ret = list_append(list_merge(redir, t), op);
			}
		}
	}

	assert(ret != NULL);
	return ret;
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


/* lookup_builtin --- find a builtin function or return NULL */

builtin_func_t
lookup_builtin(const char *name)
{
	int mid = check_special(name);

	if (mid == -1 || tokentab[mid].class != LEX_BUILTIN)
		return NULL;
#ifdef HAVE_MPFR
	if (do_mpfr)
		return tokentab[mid].ptr2;
#endif

	return tokentab[mid].ptr;
}

/* install_builtins --- add built-in functions to FUNCTAB */

void
install_builtins(void)
{
	int i, j;

	j = sizeof(tokentab) / sizeof(tokentab[0]);
	for (i = 0; i < j; i++) {
		if (    tokentab[i].class == LEX_BUILTIN
		    && (tokentab[i].flags & DEBUG_USE) == 0) {
			(void) install_symbol(tokentab[i].operator, Node_builtin_func);
		}
	}
}

/*
 * 9/2014: Gawk cannot use <ctype.h> isalpha or isalnum when
 * parsing the program since that can let through non-English
 * letters.  So, we supply our own. !@#$%^&*()-ing locales!
 */

/* is_alpha --- return true if c is an English letter */

/*
 * The scene of the murder was grisly to look upon.  When the inspector
 * arrived, the sergeant turned to him and said, "Another programmer stabbed
 * in the back. He never knew what happened."
 * 
 * The inspector replied, "Looks like the MO of isalpha, and his even meaner
 * big brother, isalnum. The Locale brothers."  The sergeant merely
 * shuddered in horror.
 */

bool
is_alpha(int c)
{
#ifdef I_DONT_KNOW_WHAT_IM_DOING
	return isalpha(c);
#else /* ! I_DONT_KNOW_WHAT_IM_DOING */
	switch (c) {
	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
	case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
	case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
	case 's': case 't': case 'u': case 'v': case 'w': case 'x':
	case 'y': case 'z':
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
	case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
	case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
	case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
	case 'Y': case 'Z':
		return true;
	}
	return false;
#endif /* ! I_DONT_KNOW_WHAT_IM_DOING */
}

/* is_alnum --- return true for alphanumeric, English only letters */

bool
is_alnum(int c)
{
	/* digit test is good for EBCDIC too. so there. */
	return (is_alpha(c) || ('0' <= c && c <= '9'));
}


/* is_identchar --- return true if c can be in an identifier */

bool
is_identchar(int c)
{
	return (is_alnum(c) || c == '_');
}
