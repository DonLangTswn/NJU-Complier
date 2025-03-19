/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "syntax.y"

#include <stdio.h>    
#include "lex.yy.c"

void yyerror(const char *msg) {
    if (yylloc.first_line == errorline)  return ;
    errorline = yylloc.first_line;
    // fprintf(stderr, "Error type B at line %d, column %d:  %s\n", \
    //     yylloc.first_line, yylloc.first_column, msg);
    fprintf(stderr, "Error type B at Line %d:  %s\n", yylloc.first_line, msg);
}

// 语法树结点定义
struct levelNode {
    char* msg;
    int line;
    char* typ;
    struct levelNode* childhead, *childtail;
    struct levelNode* next;
}* root;

int errorline = 0;

// Create a new levelNode (Type == "NON_TERMINAL" / "TOKEN")
struct levelNode* createNode(char* msg, int line, char* typ) {
    struct levelNode* newNode = (struct levelNode* )malloc(sizeof(struct levelNode));
    newNode->msg = strdup(msg);
    newNode->line = line;
    newNode->typ = strdup(typ);
    newNode->childhead = NULL; newNode->next = NULL;
    newNode->childtail = newNode->childhead;
    return newNode;
}

// Add a child to a levelNode
void addChild(struct levelNode* parent, struct levelNode* child) {
    if (parent->childtail)
        parent->childtail->next = child;
    else
        parent->childhead = child;
    parent->childtail = child;
}

// Int to String
char* itos(int i) {
    char* res = (char *)malloc(sizeof(char) * 20);
    sprintf(res, "%d", i);
    return res;
}

// 结点为语法单元，打印该语法单元的名称以及行号
char* makeSynMsg(char* msg, int line) {
    char* res = (char *)malloc(sizeof(char) * (3 + strlen(itos(line))));
    strcat(res, msg);
    strcat(res, " (");
    strcat(res, itos(line));
    strcat(res, ")");
    return res;
}

void printNodeMsg(int level, char* msg) {
    for (int i = 0; i < level; i++) 
        printf("  ");
    printf("%s\n", msg);
}

void recurPrintSynTree(struct levelNode* root, int level) {
    struct levelNode* curr = root;
    while (curr) {
        if (strcmp(curr->msg, "EMPTY")) {
            if (strcmp(curr->typ, "TOKEN"))
                printNodeMsg(level, makeSynMsg(curr->msg, curr->line));
            else
                printNodeMsg(level, curr->msg);
            recurPrintSynTree(curr->childhead, level + 1);
        }
        curr = curr->next;
    }
}

#line 152 "syntax.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "syntax.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_TYPE = 6,                       /* TYPE  */
  YYSYMBOL_COMMA = 7,                      /* COMMA  */
  YYSYMBOL_SEMI = 8,                       /* SEMI  */
  YYSYMBOL_ASSIGN = 9,                     /* ASSIGN  */
  YYSYMBOL_RELOP = 10,                     /* RELOP  */
  YYSYMBOL_LP = 11,                        /* LP  */
  YYSYMBOL_RP = 12,                        /* RP  */
  YYSYMBOL_LB = 13,                        /* LB  */
  YYSYMBOL_RB = 14,                        /* RB  */
  YYSYMBOL_LC = 15,                        /* LC  */
  YYSYMBOL_RC = 16,                        /* RC  */
  YYSYMBOL_OR = 17,                        /* OR  */
  YYSYMBOL_AND = 18,                       /* AND  */
  YYSYMBOL_ADD = 19,                       /* ADD  */
  YYSYMBOL_SUB = 20,                       /* SUB  */
  YYSYMBOL_MUL = 21,                       /* MUL  */
  YYSYMBOL_DIV = 22,                       /* DIV  */
  YYSYMBOL_NOT = 23,                       /* NOT  */
  YYSYMBOL_DOT = 24,                       /* DOT  */
  YYSYMBOL_STRUCT = 25,                    /* STRUCT  */
  YYSYMBOL_RETURN = 26,                    /* RETURN  */
  YYSYMBOL_IF = 27,                        /* IF  */
  YYSYMBOL_ELSE = 28,                      /* ELSE  */
  YYSYMBOL_WHILE = 29,                     /* WHILE  */
  YYSYMBOL_LOWER_THAN_ELSE = 30,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_Program = 32,                   /* Program  */
  YYSYMBOL_ExtDefList = 33,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 34,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 35,                /* ExtDecList  */
  YYSYMBOL_Specifier = 36,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 37,           /* StructSpecifier  */
  YYSYMBOL_OptTag = 38,                    /* OptTag  */
  YYSYMBOL_Tag = 39,                       /* Tag  */
  YYSYMBOL_VarDec = 40,                    /* VarDec  */
  YYSYMBOL_FunDec = 41,                    /* FunDec  */
  YYSYMBOL_VarList = 42,                   /* VarList  */
  YYSYMBOL_ParamDec = 43,                  /* ParamDec  */
  YYSYMBOL_CompSt = 44,                    /* CompSt  */
  YYSYMBOL_StmtList = 45,                  /* StmtList  */
  YYSYMBOL_Stmt = 46,                      /* Stmt  */
  YYSYMBOL_DefList = 47,                   /* DefList  */
  YYSYMBOL_Def = 48,                       /* Def  */
  YYSYMBOL_DecList = 49,                   /* DecList  */
  YYSYMBOL_Dec = 50,                       /* Dec  */
  YYSYMBOL_Exp = 51,                       /* Exp  */
  YYSYMBOL_Args = 52                       /* Args  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   411

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  82
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  158

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   116,   116,   123,   127,   134,   141,   147,   154,   160,
     165,   170,   175,   181,   186,   193,   202,   207,   213,   222,
     228,   233,   238,   244,   248,   254,   263,   268,   276,   283,
     291,   298,   305,   312,   318,   328,   336,   342,   346,   353,
     359,   364,   371,   380,   391,   400,   406,   411,   416,   421,
     430,   434,   441,   448,   454,   459,   466,   471,   477,   482,
     489,   494,   502,   509,   516,   523,   530,   537,   544,   551,
     558,   564,   570,   577,   585,   592,   600,   607,   612,   617,
     622,   628,   635
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "ID",
  "TYPE", "COMMA", "SEMI", "ASSIGN", "RELOP", "LP", "RP", "LB", "RB", "LC",
  "RC", "OR", "AND", "ADD", "SUB", "MUL", "DIV", "NOT", "DOT", "STRUCT",
  "RETURN", "IF", "ELSE", "WHILE", "LOWER_THAN_ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-62)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-55)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      12,    94,   -62,    72,    26,   -62,    12,   133,   -62,    20,
     -62,    66,    70,    83,    99,   -62,   -62,   -62,    66,    20,
     -62,   150,    96,    41,    18,    63,   -62,    16,    59,   -62,
     -62,   -62,   116,    65,    13,   -62,   -62,   113,   -62,    65,
     127,   135,    46,    75,   117,    90,   148,   141,    55,   147,
      65,   -62,   -62,   151,   154,   -62,   162,   -62,    -4,   -62,
     -62,   204,   153,   172,   123,   100,   -62,   -62,   174,   209,
     209,   209,   209,   175,   176,   -62,   179,   117,   238,   -62,
     -62,   -62,   -62,   -62,   -62,   -62,   -62,    75,   351,   173,
     -62,    75,    75,   -62,   209,   149,   271,    14,    -9,   255,
     178,   199,   -62,   -62,   -62,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   183,   -62,   -62,   351,   -62,   -62,
     287,   180,   -62,   221,   182,   -62,   -62,   185,   303,   187,
     319,   351,   387,   335,   364,   377,    14,    14,    -9,    -9,
     -62,   -62,   -62,   209,   -62,   144,   144,   -62,   144,   -62,
     -62,   163,   177,   -62,   144,   144,   -62,   -62
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    16,     0,     0,     2,     0,     0,    17,     0,
      12,     0,    20,    25,     0,    19,     1,     4,     0,    26,
       6,     0,     0,     0,     0,     0,     9,     0,     0,     8,
      11,     5,     0,     0,     0,    10,     7,     0,    30,     0,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    26,    14,     0,     0,    31,    34,    29,     0,    53,
      36,     0,    58,     0,     0,     0,    78,    79,    77,     0,
       0,     0,     0,     0,     0,    40,     0,     0,     0,    51,
      21,    22,    18,    15,    28,    27,    32,     0,    61,     0,
      52,     0,     0,    45,     0,     0,     0,    70,    71,     0,
       0,     0,    35,    38,    39,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    57,    60,    59,    56,    55,
       0,     0,    74,    82,     0,    72,    41,     0,     0,     0,
       0,    62,    65,     0,    64,    63,    66,    67,    68,    69,
      76,    48,    80,     0,    73,     0,     0,    49,     0,    75,
      81,    47,    42,    44,     0,     0,    46,    43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -62,   -62,   184,   -62,   -30,     1,   -62,   -62,   -62,    22,
     210,   158,   -62,    89,   129,   -19,   -22,   -62,   -34,   -62,
     -61,    78
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,    21,    43,     8,    14,    15,    62,
      11,    40,    41,    75,    76,    77,    44,    45,    63,    64,
      78,   124
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      88,     7,     2,    52,   107,    47,    49,     7,    96,    97,
      98,    99,    -3,     1,    53,   114,    54,    46,     2,    37,
      83,     3,     2,    79,     2,    39,    16,   107,   117,    22,
      38,    24,   -50,   120,   123,   112,   113,     3,   114,   128,
     130,     3,    35,     3,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   115,    59,    22,    25,   118,   119,    39,
      48,    56,    60,    59,    42,     2,   -50,   -50,   -50,     2,
      51,    81,    22,    12,   -50,   -50,    61,    13,   -50,   -50,
      51,    25,   123,   -50,     3,    27,   -50,   -23,     3,   -50,
     -50,    46,   -50,   -50,   -50,   -50,     2,    32,   -24,     9,
      26,   -50,    10,    33,   -13,   -50,   -50,    29,    93,    34,
     -50,    94,    36,   -50,    28,     3,   -50,   -50,    65,   -50,
      66,    67,    68,    50,    91,    55,   151,   152,    69,   153,
      92,   -54,    25,   -37,    18,   156,   157,    70,    19,    57,
      71,    20,    58,    72,    73,    65,    74,    66,    67,    68,
     121,    30,    66,    67,    68,    69,    59,    80,    31,    25,
      69,   122,    89,    82,    70,    84,    34,    71,    85,    70,
      72,    73,    71,    74,   116,    34,    66,    67,    68,   127,
      90,    66,    67,    68,    69,    95,   100,   101,   140,    69,
      17,   154,   142,    70,   144,   102,    71,   145,    70,   147,
     129,    71,    66,    67,    68,   155,   103,    66,    67,    68,
      69,    87,    66,    67,    68,    69,    86,    23,     0,    70,
      69,   150,    71,     0,    70,     0,     0,    71,   143,    70,
     105,   106,    71,     0,   107,     0,     0,     0,   108,   109,
     110,   111,   112,   113,     0,   114,   104,   105,   106,     0,
       0,   107,     0,     0,     0,   108,   109,   110,   111,   112,
     113,     0,   114,   126,   105,   106,     0,     0,   107,     0,
       0,     0,   108,   109,   110,   111,   112,   113,     0,   114,
     105,   106,     0,   125,   107,     0,     0,     0,   108,   109,
     110,   111,   112,   113,     0,   114,   105,   106,     0,   141,
     107,     0,     0,     0,   108,   109,   110,   111,   112,   113,
       0,   114,   105,   106,     0,   146,   107,     0,     0,     0,
     108,   109,   110,   111,   112,   113,     0,   114,   105,   106,
       0,   148,   107,     0,     0,     0,   108,   109,   110,   111,
     112,   113,     0,   114,   105,   106,     0,     0,   107,   149,
       0,     0,   108,   109,   110,   111,   112,   113,     0,   114,
     105,   106,     0,     0,   107,     0,     0,     0,   108,   109,
     110,   111,   112,   113,   106,   114,     0,   107,     0,     0,
       0,     0,   109,   110,   111,   112,   113,   106,   114,     0,
     107,     0,     0,     0,     0,     0,   110,   111,   112,   113,
     107,   114,     0,     0,     0,     0,   110,   111,   112,   113,
       0,   114
};

static const yytype_int16 yycheck[] =
{
      61,     0,     6,    33,    13,    27,    28,     6,    69,    70,
      71,    72,     0,     1,     1,    24,     3,     1,     6,     1,
      50,    25,     6,    45,     6,    24,     0,    13,    89,     7,
      12,    11,    16,    94,    95,    21,    22,    25,    24,   100,
     101,    25,     1,    25,   105,   106,   107,   108,   109,   110,
     111,   112,   113,    87,     8,    33,    15,    91,    92,    58,
       1,    39,    16,     8,     1,     6,     3,     4,     5,     6,
       5,    16,    50,     1,    11,    16,     1,     5,    15,    16,
       5,    15,   143,    20,    25,    15,    23,    15,    25,    26,
      27,     1,    29,     3,     4,     5,     6,     1,    15,     5,
      11,    11,     8,     7,     8,    15,    16,    18,     8,    13,
      20,    11,    23,    23,    15,    25,    26,    27,     1,    29,
       3,     4,     5,     7,     1,    12,   145,   146,    11,   148,
       7,     8,    15,    16,     1,   154,   155,    20,     5,    12,
      23,     8,     7,    26,    27,     1,    29,     3,     4,     5,
       1,     1,     3,     4,     5,    11,     8,    16,     8,    15,
      11,    12,     9,    16,    20,    14,    13,    23,    14,    20,
      26,    27,    23,    29,     1,    13,     3,     4,     5,     1,
       8,     3,     4,     5,    11,    11,    11,    11,     5,    11,
       6,    28,    12,    20,    12,    16,    23,    12,    20,    12,
       1,    23,     3,     4,     5,    28,    77,     3,     4,     5,
      11,     7,     3,     4,     5,    11,    58,     7,    -1,    20,
      11,   143,    23,    -1,    20,    -1,    -1,    23,     7,    20,
       9,    10,    23,    -1,    13,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    -1,    24,     8,     9,    10,    -1,
      -1,    13,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    -1,    24,     8,     9,    10,    -1,    -1,    13,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    -1,    24,
       9,    10,    -1,    12,    13,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    -1,    24,     9,    10,    -1,    12,
      13,    -1,    -1,    -1,    17,    18,    19,    20,    21,    22,
      -1,    24,     9,    10,    -1,    12,    13,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    22,    -1,    24,     9,    10,
      -1,    12,    13,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    -1,    24,     9,    10,    -1,    -1,    13,    14,
      -1,    -1,    17,    18,    19,    20,    21,    22,    -1,    24,
       9,    10,    -1,    -1,    13,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    10,    24,    -1,    13,    -1,    -1,
      -1,    -1,    18,    19,    20,    21,    22,    10,    24,    -1,
      13,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,    22,
      13,    24,    -1,    -1,    -1,    -1,    19,    20,    21,    22,
      -1,    24
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     6,    25,    32,    33,    34,    36,    37,     5,
       8,    41,     1,     5,    38,    39,     0,    33,     1,     5,
       8,    35,    40,    41,    11,    15,    44,    15,    15,    44,
       1,     8,     1,     7,    13,     1,    44,     1,    12,    36,
      42,    43,     1,    36,    47,    48,     1,    47,     1,    47,
       7,     5,    35,     1,     3,    12,    40,    12,     7,     8,
      16,     1,    40,    49,    50,     1,     3,     4,     5,    11,
      20,    23,    26,    27,    29,    44,    45,    46,    51,    47,
      16,    16,    16,    35,    14,    14,    42,     7,    51,     9,
       8,     1,     7,     8,    11,    11,    51,    51,    51,    51,
      11,    11,    16,    45,     8,     9,    10,    13,    17,    18,
      19,    20,    21,    22,    24,    49,     1,    51,    49,    49,
      51,     1,    12,    51,    52,    12,     8,     1,    51,     1,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
       5,    12,    12,     7,    12,    12,    12,    12,    12,    14,
      52,    46,    46,    46,    28,    28,    46,    46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    34,    34,
      34,    34,    34,    35,    35,    35,    36,    36,    37,    37,
      37,    37,    37,    38,    38,    39,    40,    40,    40,    41,
      41,    41,    42,    42,    43,    44,    44,    45,    45,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      47,    47,    48,    48,    49,    49,    49,    49,    50,    50,
      50,    50,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    52,    52
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     3,     3,     3,
       3,     3,     2,     1,     3,     4,     1,     1,     5,     2,
       2,     5,     5,     0,     1,     1,     1,     4,     4,     4,
       3,     4,     3,     1,     2,     4,     3,     0,     2,     2,
       1,     3,     5,     7,     5,     2,     7,     5,     4,     4,
       0,     2,     3,     2,     1,     3,     3,     3,     1,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     3,     4,     3,     4,     3,     1,     1,     1,
       4,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: ExtDefList  */
#line 116 "syntax.y"
                     {      // 整个程序
        struct levelNode* newNode = createNode("Program", (yyvsp[0].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
        root = (yyval.Node);
    }
#line 1732 "syntax.tab.c"
    break;

  case 3: /* ExtDefList: %empty  */
#line 123 "syntax.y"
             {              // 很多个全局变量定义
        struct levelNode* newNode = createNode("EMPTY", 0, "EMPTY");
        (yyval.Node) = newNode;
    }
#line 1741 "syntax.tab.c"
    break;

  case 4: /* ExtDefList: ExtDef ExtDefList  */
#line 127 "syntax.y"
                        {   // int g1, g2; float m;...
        struct levelNode* newNode = createNode("ExtDefList", (yyvsp[-1].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 1752 "syntax.tab.c"
    break;

  case 5: /* ExtDef: Specifier ExtDecList SEMI  */
#line 134 "syntax.y"
                                   { // 全局变量定义：int g1, g2;
        struct levelNode* newNode = createNode("ExtDef", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 1764 "syntax.tab.c"
    break;

  case 6: /* ExtDef: Specifier SEMI  */
#line 141 "syntax.y"
                      {              // 结构体定义：/struct {...}/ ;/
        struct levelNode* newNode = createNode("ExtDef", (yyvsp[-1].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 1775 "syntax.tab.c"
    break;

  case 7: /* ExtDef: Specifier FunDec CompSt  */
#line 147 "syntax.y"
                              {     // 函数定义：int/ main()/ {...}/
        struct levelNode* newNode = createNode("ExtDef", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 1787 "syntax.tab.c"
    break;

  case 8: /* ExtDef: Specifier error CompSt  */
#line 154 "syntax.y"
                             {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
        // printf("Specifier e CompSt -> ExtDef\n");
    }
#line 1798 "syntax.tab.c"
    break;

  case 9: /* ExtDef: error FunDec CompSt  */
#line 160 "syntax.y"
                          {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 1808 "syntax.tab.c"
    break;

  case 10: /* ExtDef: Specifier FunDec error  */
#line 165 "syntax.y"
                             {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 1818 "syntax.tab.c"
    break;

  case 11: /* ExtDef: Specifier ExtDecList error  */
#line 170 "syntax.y"
                                 {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 1828 "syntax.tab.c"
    break;

  case 12: /* ExtDef: error SEMI  */
#line 175 "syntax.y"
                 {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 1838 "syntax.tab.c"
    break;

  case 13: /* ExtDecList: VarDec  */
#line 181 "syntax.y"
                    {           // 一个变量或多个变量用","连接
        struct levelNode* newNode = createNode("ExtDecList", (yyvsp[0].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 1848 "syntax.tab.c"
    break;

  case 14: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 186 "syntax.y"
                              { // a, A[3], b,...
        struct levelNode* newNode = createNode("ExtDecList", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 1860 "syntax.tab.c"
    break;

  case 15: /* ExtDecList: VarDec error COMMA ExtDecList  */
#line 193 "syntax.y"
                                    {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 1870 "syntax.tab.c"
    break;

  case 16: /* Specifier: TYPE  */
#line 202 "syntax.y"
                 {      // int float
        struct levelNode* newNode = createNode("Specifier", (yyvsp[0].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 1880 "syntax.tab.c"
    break;

  case 17: /* Specifier: StructSpecifier  */
#line 207 "syntax.y"
                      { // 结构体类型
        struct levelNode* newNode = createNode("Specifier", (yyvsp[0].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 1890 "syntax.tab.c"
    break;

  case 18: /* StructSpecifier: STRUCT OptTag LC DefList RC  */
#line 213 "syntax.y"
                                              { // struct Complex(可无) { int real, image; }
        struct levelNode* newNode = createNode("StructSpecifier", (yyvsp[-4].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-4].Node));
        addChild(newNode, (yyvsp[-3].Node));
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 1904 "syntax.tab.c"
    break;

  case 19: /* StructSpecifier: STRUCT Tag  */
#line 222 "syntax.y"
                 {  // struct name
        struct levelNode* newNode = createNode("StructSpecifier", (yyvsp[-1].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 1915 "syntax.tab.c"
    break;

  case 20: /* StructSpecifier: STRUCT error  */
#line 228 "syntax.y"
                   {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 1925 "syntax.tab.c"
    break;

  case 21: /* StructSpecifier: STRUCT error LC DefList RC  */
#line 233 "syntax.y"
                                 {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 1935 "syntax.tab.c"
    break;

  case 22: /* StructSpecifier: STRUCT OptTag LC error RC  */
#line 238 "syntax.y"
                                {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 1945 "syntax.tab.c"
    break;

  case 23: /* OptTag: %empty  */
#line 244 "syntax.y"
         {   // 可有可无的结构体名
        struct levelNode* newNode = createNode("EMPTY", 0, "EMPTY");
        (yyval.Node) = newNode;
    }
#line 1954 "syntax.tab.c"
    break;

  case 24: /* OptTag: ID  */
#line 248 "syntax.y"
         {
        struct levelNode* newNode = createNode("OptTag", (yyvsp[0].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 1964 "syntax.tab.c"
    break;

  case 25: /* Tag: ID  */
#line 254 "syntax.y"
         {   // 结构体名
        struct levelNode* newNode = createNode("Tag", (yyvsp[0].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 1974 "syntax.tab.c"
    break;

  case 26: /* VarDec: ID  */
#line 263 "syntax.y"
            {            // a
        struct levelNode* newNode = createNode("VarDec", (yyvsp[0].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 1984 "syntax.tab.c"
    break;

  case 27: /* VarDec: VarDec LB INT RB  */
#line 268 "syntax.y"
                       { // A[3]
        struct levelNode* newNode = createNode("VarDec", (yyvsp[-3].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-3].Node));
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 1997 "syntax.tab.c"
    break;

  case 28: /* VarDec: VarDec LB error RB  */
#line 276 "syntax.y"
                         {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
        // printf("e RB -> VarDec\n");
    }
#line 2008 "syntax.tab.c"
    break;

  case 29: /* FunDec: ID LP VarList RP  */
#line 283 "syntax.y"
                          { // func(int x, float y[3],...), 内为VarList
        struct levelNode* newNode = createNode("FunDec", (yyvsp[-3].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-3].Node));
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2021 "syntax.tab.c"
    break;

  case 30: /* FunDec: ID LP RP  */
#line 291 "syntax.y"
               {             // func()
        struct levelNode* newNode = createNode("FunDec", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2033 "syntax.tab.c"
    break;

  case 31: /* FunDec: ID LP error RP  */
#line 298 "syntax.y"
                     {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
        // printf("e RP -> FunDec\n");
    }
#line 2044 "syntax.tab.c"
    break;

  case 32: /* VarList: ParamDec COMMA VarList  */
#line 305 "syntax.y"
                                 {  // int a, b, c
        struct levelNode* newNode = createNode("VarList", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2056 "syntax.tab.c"
    break;

  case 33: /* VarList: ParamDec  */
#line 312 "syntax.y"
               {                    // int a
        struct levelNode* newNode = createNode("VarList", (yyvsp[0].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2066 "syntax.tab.c"
    break;

  case 34: /* ParamDec: Specifier VarDec  */
#line 318 "syntax.y"
                            {       // 类型+VarDec, int a  int A[10]
        struct levelNode* newNode = createNode("ParamDec", (yyvsp[-1].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2077 "syntax.tab.c"
    break;

  case 35: /* CompSt: LC DefList StmtList RC  */
#line 328 "syntax.y"
                                {   // 大括号语句块, { 开头定义，之后使用 }
        struct levelNode* newNode = createNode("CompSt", (yyvsp[-3].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-3].Node));
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2090 "syntax.tab.c"
    break;

  case 36: /* CompSt: LC error RC  */
#line 336 "syntax.y"
                  {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 2100 "syntax.tab.c"
    break;

  case 37: /* StmtList: %empty  */
#line 342 "syntax.y"
           { // 多个Stmt的连接, Stmt为一条语句
        struct levelNode* newNode = createNode("EMPTY", 0, "EMPTY");
        (yyval.Node) = newNode;
    }
#line 2109 "syntax.tab.c"
    break;

  case 38: /* StmtList: Stmt StmtList  */
#line 346 "syntax.y"
                    {
        struct levelNode* newNode = createNode("StmtList", (yyvsp[-1].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2120 "syntax.tab.c"
    break;

  case 39: /* Stmt: Exp SEMI  */
#line 353 "syntax.y"
                {               // i + 1; a && b;
        struct levelNode* newNode = createNode("Stmt", (yyvsp[-1].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2131 "syntax.tab.c"
    break;

  case 40: /* Stmt: CompSt  */
#line 359 "syntax.y"
             {                  // 另一个语句块
        struct levelNode* newNode = createNode("Stmt", (yyvsp[0].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2141 "syntax.tab.c"
    break;

  case 41: /* Stmt: RETURN Exp SEMI  */
#line 364 "syntax.y"
                      {         // return 0;
        struct levelNode* newNode = createNode("Stmt", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2153 "syntax.tab.c"
    break;

  case 42: /* Stmt: IF LP Exp RP Stmt  */
#line 371 "syntax.y"
                                              { // if (...) ...
        struct levelNode* newNode = createNode("Stmt", (yyvsp[-4].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-4].Node));
        addChild(newNode, (yyvsp[-3].Node));
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2167 "syntax.tab.c"
    break;

  case 43: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 380 "syntax.y"
                                  {             // if (...) ... else ...
        struct levelNode* newNode = createNode("Stmt", (yyvsp[-6].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-6].Node));
        addChild(newNode, (yyvsp[-5].Node));
        addChild(newNode, (yyvsp[-4].Node));
        addChild(newNode, (yyvsp[-3].Node));
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2183 "syntax.tab.c"
    break;

  case 44: /* Stmt: WHILE LP Exp RP Stmt  */
#line 391 "syntax.y"
                           {    // while (...) ...
        struct levelNode* newNode = createNode("Stmt", (yyvsp[-4].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-4].Node));
        addChild(newNode, (yyvsp[-3].Node));
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2197 "syntax.tab.c"
    break;

  case 45: /* Stmt: error SEMI  */
#line 400 "syntax.y"
                 {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
        // printf("e SEMI -> Stmt\n");
    }
#line 2208 "syntax.tab.c"
    break;

  case 46: /* Stmt: IF LP error RP Stmt ELSE Stmt  */
#line 406 "syntax.y"
                                    {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 2218 "syntax.tab.c"
    break;

  case 47: /* Stmt: IF LP error RP Stmt  */
#line 411 "syntax.y"
                                                {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 2228 "syntax.tab.c"
    break;

  case 48: /* Stmt: error LP Exp RP  */
#line 416 "syntax.y"
                      {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 2238 "syntax.tab.c"
    break;

  case 49: /* Stmt: WHILE LP error RP  */
#line 421 "syntax.y"
                        {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 2248 "syntax.tab.c"
    break;

  case 50: /* DefList: %empty  */
#line 430 "syntax.y"
          {  // 多个Def的连接, Def为一个定义语句
        struct levelNode* newNode = createNode("EMPTY", 0, "EMPTY");
        (yyval.Node) = newNode;
    }
#line 2257 "syntax.tab.c"
    break;

  case 51: /* DefList: Def DefList  */
#line 434 "syntax.y"
                  {
        struct levelNode* newNode = createNode("DefList", (yyvsp[-1].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2268 "syntax.tab.c"
    break;

  case 52: /* Def: Specifier DecList SEMI  */
#line 441 "syntax.y"
                             {   // int a, b = 3, C[4]; struct {..} A[3], B;
        struct levelNode* newNode = createNode("Def", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2280 "syntax.tab.c"
    break;

  case 53: /* Def: error SEMI  */
#line 448 "syntax.y"
                 {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 2290 "syntax.tab.c"
    break;

  case 54: /* DecList: Dec  */
#line 454 "syntax.y"
              {         // 一个Dec  b = 3
        struct levelNode* newNode = createNode("DecList", (yyvsp[0].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2300 "syntax.tab.c"
    break;

  case 55: /* DecList: Dec COMMA DecList  */
#line 459 "syntax.y"
                        { // 多个Dec通过","连接  a, b = 3, C[4]
        struct levelNode* newNode = createNode("DecList", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2312 "syntax.tab.c"
    break;

  case 56: /* DecList: Dec error DecList  */
#line 466 "syntax.y"
                        {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 2322 "syntax.tab.c"
    break;

  case 57: /* DecList: error COMMA DecList  */
#line 471 "syntax.y"
                          {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 2332 "syntax.tab.c"
    break;

  case 58: /* Dec: VarDec  */
#line 477 "syntax.y"
             {            // a  A[3]
        struct levelNode* newNode = createNode("Dec", (yyvsp[0].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2342 "syntax.tab.c"
    break;

  case 59: /* Dec: VarDec ASSIGN Exp  */
#line 482 "syntax.y"
                        { // a = 10
        struct levelNode* newNode = createNode("Dec", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2354 "syntax.tab.c"
    break;

  case 60: /* Dec: VarDec ASSIGN error  */
#line 489 "syntax.y"
                          {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 2364 "syntax.tab.c"
    break;

  case 61: /* Dec: error Exp  */
#line 494 "syntax.y"
                {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 2374 "syntax.tab.c"
    break;

  case 62: /* Exp: Exp ASSIGN Exp  */
#line 502 "syntax.y"
                     {
        struct levelNode* newNode = createNode("Exp", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2386 "syntax.tab.c"
    break;

  case 63: /* Exp: Exp AND Exp  */
#line 509 "syntax.y"
                   {
        struct levelNode* newNode = createNode("Exp", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2398 "syntax.tab.c"
    break;

  case 64: /* Exp: Exp OR Exp  */
#line 516 "syntax.y"
                 {
        struct levelNode* newNode = createNode("Exp", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2410 "syntax.tab.c"
    break;

  case 65: /* Exp: Exp RELOP Exp  */
#line 523 "syntax.y"
                    {
        struct levelNode* newNode = createNode("Exp", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2422 "syntax.tab.c"
    break;

  case 66: /* Exp: Exp ADD Exp  */
#line 530 "syntax.y"
                  {
        struct levelNode* newNode = createNode("Exp", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2434 "syntax.tab.c"
    break;

  case 67: /* Exp: Exp SUB Exp  */
#line 537 "syntax.y"
                  {
        struct levelNode* newNode = createNode("Exp", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2446 "syntax.tab.c"
    break;

  case 68: /* Exp: Exp MUL Exp  */
#line 544 "syntax.y"
                  {
        struct levelNode* newNode = createNode("Exp", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2458 "syntax.tab.c"
    break;

  case 69: /* Exp: Exp DIV Exp  */
#line 551 "syntax.y"
                  {
        struct levelNode* newNode = createNode("Exp", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2470 "syntax.tab.c"
    break;

  case 70: /* Exp: SUB Exp  */
#line 558 "syntax.y"
              {
        struct levelNode* newNode = createNode("Exp", (yyvsp[-1].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2481 "syntax.tab.c"
    break;

  case 71: /* Exp: NOT Exp  */
#line 564 "syntax.y"
              {
        struct levelNode* newNode = createNode("Exp", (yyvsp[-1].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2492 "syntax.tab.c"
    break;

  case 72: /* Exp: LP Exp RP  */
#line 570 "syntax.y"
                {
        struct levelNode* newNode = createNode("Exp", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2504 "syntax.tab.c"
    break;

  case 73: /* Exp: ID LP Args RP  */
#line 577 "syntax.y"
                    {
        struct levelNode* newNode = createNode("Exp", (yyvsp[-3].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-3].Node));
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2517 "syntax.tab.c"
    break;

  case 74: /* Exp: ID LP RP  */
#line 585 "syntax.y"
               {
        struct levelNode* newNode = createNode("Exp", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2529 "syntax.tab.c"
    break;

  case 75: /* Exp: Exp LB Exp RB  */
#line 592 "syntax.y"
                    {
        struct levelNode* newNode = createNode("Exp", (yyvsp[-3].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-3].Node));
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2542 "syntax.tab.c"
    break;

  case 76: /* Exp: Exp DOT ID  */
#line 600 "syntax.y"
                 {
        struct levelNode* newNode = createNode("Exp", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2554 "syntax.tab.c"
    break;

  case 77: /* Exp: ID  */
#line 607 "syntax.y"
         {
        struct levelNode* newNode = createNode("Exp", (yyvsp[0].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2564 "syntax.tab.c"
    break;

  case 78: /* Exp: INT  */
#line 612 "syntax.y"
          {
        struct levelNode* newNode = createNode("Exp", (yyvsp[0].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2574 "syntax.tab.c"
    break;

  case 79: /* Exp: FLOAT  */
#line 617 "syntax.y"
            {
        struct levelNode* newNode = createNode("Exp", (yyvsp[0].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2584 "syntax.tab.c"
    break;

  case 80: /* Exp: ID LP error RP  */
#line 622 "syntax.y"
                     {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        (yyval.Node) = newNode;
    }
#line 2594 "syntax.tab.c"
    break;

  case 81: /* Args: Exp COMMA Args  */
#line 628 "syntax.y"
                      {
        struct levelNode* newNode = createNode("Args", (yyvsp[-2].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[-2].Node));
        addChild(newNode, (yyvsp[-1].Node));
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2606 "syntax.tab.c"
    break;

  case 82: /* Args: Exp  */
#line 635 "syntax.y"
          {
        struct levelNode* newNode = createNode("Args", (yyvsp[0].Node)->line, "NON_TERMINAL");
        addChild(newNode, (yyvsp[0].Node));
        (yyval.Node) = newNode;
    }
#line 2616 "syntax.tab.c"
    break;


#line 2620 "syntax.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 641 "syntax.y"
