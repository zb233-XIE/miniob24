/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, SqlCommandFlag flag, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(flag);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

UnboundAggregateExpr *create_aggregate_expression(const char *aggregate_name,
                                           Expression *child,
                                           const char *sql_string,
                                           YYLTYPE *llocp)
{
  UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, child);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

bool is_valid_date(const char *date) {
  struct tm tm; bzero(&tm, sizeof(tm));
  char *result = strptime(date, "%Y-%m-%d", &tm);
  if (result == nullptr || *result != '\0') {
    return false;
  }

  int month2day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int year = tm.tm_year + 1900;
  if (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && tm.tm_mon == 1) {
    return tm.tm_mday <= 29;
  }
  return tm.tm_mday <= month2day[tm.tm_mon];
}

#line 140 "yacc_sql.cpp"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
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
    SEMICOLON = 258,
    BY = 259,
    CREATE = 260,
    DROP = 261,
    GROUP = 262,
    HAVING = 263,
    TABLE = 264,
    TABLES = 265,
    INDEX = 266,
    CALC = 267,
    SELECT = 268,
    DESC = 269,
    SHOW = 270,
    SYNC = 271,
    INSERT = 272,
    DELETE = 273,
    UPDATE = 274,
    LBRACE = 275,
    RBRACE = 276,
    COMMA = 277,
    TRX_BEGIN = 278,
    TRX_COMMIT = 279,
    TRX_ROLLBACK = 280,
    INT_T = 281,
    STRING_T = 282,
    FLOAT_T = 283,
    VECTOR_T = 284,
    DATE_T = 285,
    HELP = 286,
    EXIT = 287,
    DOT = 288,
    INTO = 289,
    VALUES = 290,
    FROM = 291,
    WHERE = 292,
    AND = 293,
    SET = 294,
    ON = 295,
    LOAD = 296,
    DATA = 297,
    INFILE = 298,
    EXPLAIN = 299,
    STORAGE = 300,
    FORMAT = 301,
    EQ = 302,
    LT = 303,
    GT = 304,
    LE = 305,
    GE = 306,
    NE = 307,
    LK = 308,
    NLK = 309,
    IS_T = 310,
    IS_NOT_T = 311,
    MAX = 312,
    MIN = 313,
    COUNT = 314,
    AVG = 315,
    SUM = 316,
    INNER = 317,
    JOIN = 318,
    UNIQUE = 319,
    LBRACKET = 320,
    RBRACKET = 321,
    L2_DISTANCE = 322,
    COSINE_DISTANCE = 323,
    INNER_PRODUCT = 324,
    EXISTS_T = 325,
    NOT = 326,
    IN_T = 327,
    NULL_T = 328,
    NOT_NULL_T = 329,
    ORDER_BY = 330,
    ASC = 331,
    NUMBER = 332,
    FLOAT = 333,
    ID = 334,
    SSS = 335,
    DATE = 336,
    UMINUS = 337
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 161 "yacc_sql.y"

  ParsedSqlNode *                            sql_node;
  ConditionSqlNode *                         condition;
  Value *                                    value;
  enum CompOp                                comp;
  RelAttrSqlNode *                           rel_attr;
  SetClauseSqlNode *                         set_clause;
  std::vector<AttrInfoSqlNode> *             attr_infos;
  AttrInfoSqlNode *                          attr_info;
  Expression *                               expression;
  std::vector<std::unique_ptr<Expression>> * expression_list;
  // std::vector<Expression *> *                agg_fun_attr_list;
  OrderByItem *                              order_by_item;
  std::vector<OrderByItem> *                 order_by_list;
  std::vector<Value> *                       value_list;
  std::vector<ConditionSqlNode> *            condition_list;
  std::tuple<std::vector<std::string> *, std::vector<std::vector<ConditionSqlNode> *> *> *  join_tuple_list;
  std::tuple<std::string, std::vector<ConditionSqlNode> *> *  join_tuple;
  std::vector<RelAttrSqlNode> *              rel_attr_list;
  std::vector<std::string> *                 relation_list;
  std::vector<SetClauseSqlNode> *            set_clause_list;
  std::vector<float> *                       vector_elem_list;
  char *                                     string;
  int                                        number;
  float                                      floats;
  char *                                     date;
  bool                                       nullable_spec;
  bool                                       asc_desc;

#line 305 "yacc_sql.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner, SqlCommandFlag flag);

#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */



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
typedef yytype_int16 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  77
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   403

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  87
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  145
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  298

#define YYUNDEFTOK  2
#define YYMAXUTOK   337


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    84,    82,     2,    83,     2,    85,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    86
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   262,   262,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   293,   299,   304,   310,   316,   322,   328,
     335,   341,   349,   363,   380,   390,   414,   417,   430,   439,
     457,   458,   459,   463,   466,   467,   468,   469,   470,   473,
     490,   493,   504,   508,   512,   518,   530,   540,   546,   550,
     557,   560,   569,   572,   579,   591,   608,   613,   626,   635,
     644,   692,   695,   702,   708,   721,   732,   735,   739,   746,
     755,   760,   771,   774,   777,   780,   783,   787,   790,   793,
     796,   799,   804,   810,   815,   818,   821,   824,   827,   846,
     849,   863,   868,   871,   879,   884,   894,   899,   904,   918,
     921,   937,   944,   947,   953,   956,   961,  1017,  1025,  1034,
    1043,  1053,  1069,  1085,  1095,  1105,  1114,  1125,  1126,  1127,
    1128,  1129,  1130,  1131,  1132,  1133,  1134,  1140,  1144,  1152,
    1155,  1160,  1173,  1181,  1191,  1192
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "BY", "CREATE", "DROP",
  "GROUP", "HAVING", "TABLE", "TABLES", "INDEX", "CALC", "SELECT", "DESC",
  "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE",
  "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "VECTOR_T", "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES",
  "FROM", "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN",
  "STORAGE", "FORMAT", "EQ", "LT", "GT", "LE", "GE", "NE", "LK", "NLK",
  "IS_T", "IS_NOT_T", "MAX", "MIN", "COUNT", "AVG", "SUM", "INNER", "JOIN",
  "UNIQUE", "LBRACKET", "RBRACKET", "L2_DISTANCE", "COSINE_DISTANCE",
  "INNER_PRODUCT", "EXISTS_T", "NOT", "IN_T", "NULL_T", "NOT_NULL_T",
  "ORDER_BY", "ASC", "NUMBER", "FLOAT", "ID", "SSS", "DATE", "'+'", "'-'",
  "'*'", "'/'", "UMINUS", "$accept", "commands", "command_wrapper",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "drop_index_stmt",
  "create_table_stmt", "attr_def_list", "attr_def", "nullable_spec",
  "number", "type", "insert_stmt", "value_list", "value", "vector_elem",
  "vector_value_list", "storage_format", "delete_stmt", "update_stmt",
  "set_clause_list", "set_clause", "select_stmt", "order_by",
  "order_by_list", "order_by_item", "asc_desc", "calc_stmt",
  "expression_list", "expression", "agg_fun_attr_list", "agg_fun_attr",
  "rel_attr", "relation", "rel_list", "join_list", "join", "where",
  "condition_list", "condition", "comp_op", "group_by", "having",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,    43,    45,    42,    47,   337
};
# endif

#define YYPACT_NINF (-225)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     320,     7,    17,   184,   184,   -71,     5,  -225,    -1,    -5,
     -41,  -225,  -225,  -225,  -225,  -225,   -34,    27,   320,    73,
      78,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,    12,    13,    83,    33,    37,   184,    76,    98,    99,
     103,   104,   -30,   106,   112,   113,  -225,  -225,  -225,   107,
    -225,  -225,   184,  -225,  -225,  -225,    45,  -225,   111,  -225,
    -225,    60,    64,   109,   102,   108,  -225,  -225,  -225,  -225,
     132,   119,    90,  -225,   128,     4,   -55,   -55,   -55,   -55,
     -55,  -225,  -225,   148,   184,   184,   184,    96,  -225,   184,
     184,   184,   184,   184,   116,   146,   159,   118,   -38,   120,
     124,   127,   169,   131,  -225,  -225,   191,   196,  -225,   198,
     199,   201,   209,   -30,   165,    89,    95,   100,  -225,  -225,
     -31,   -31,  -225,  -225,  -225,   216,   186,   226,   156,  -225,
     203,   159,   232,  -225,   221,   162,   234,   238,   180,  -225,
    -225,   -55,  -225,  -225,  -225,  -225,   148,  -225,   184,   184,
     184,   116,   211,   159,   186,   -38,    77,   246,   205,   318,
    -225,   244,   121,  -225,   118,   267,  -225,  -225,  -225,  -225,
    -225,    -9,   124,   257,   116,   263,  -225,  -225,    16,    20,
      25,  -225,   116,   277,  -225,   264,   266,   275,   274,  -225,
    -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,   230,
     283,   212,   156,   275,  -225,  -225,   225,   229,  -225,  -225,
    -225,   234,   265,   290,   116,  -225,  -225,  -225,   272,   310,
     307,   -38,   295,   328,   301,   275,   308,    -3,    77,    80,
    -225,   306,  -225,  -225,   309,  -225,   285,  -225,  -225,   319,
     156,   184,   156,   254,   264,  -225,   240,  -225,   321,    -3,
     264,   325,   326,  -225,     6,   294,  -225,  -225,  -225,  -225,
     269,  -225,  -225,    77,    80,  -225,   264,   329,   332,  -225,
    -225,  -225,   270,  -225,   333,     0,   335,   336,  -225,  -225,
    -225,   269,  -225,  -225,  -225,  -225,  -225,  -225
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     144,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    57,    52,    53,   104,
      54,    55,     0,    93,    91,    79,    80,    92,     0,    31,
      30,     0,     0,     0,     0,     0,   142,     1,   145,     2,
       0,     0,     0,    29,     0,     0,   101,   101,   101,   101,
     101,    58,    59,    60,     0,     0,     0,     0,    90,     0,
       0,     0,     0,     0,     0,     0,   112,     0,     0,     0,
       0,     0,     0,     0,    86,   102,     0,    99,   103,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   105,    81,
      82,    83,    84,    85,   106,   107,   109,     0,   114,    64,
       0,   112,    66,   143,     0,     0,    36,     0,     0,    34,
      94,   101,    95,    96,    97,    98,    60,    56,     0,     0,
       0,     0,     0,   112,   109,     0,     0,     0,     0,     0,
     113,   115,     0,    65,     0,     0,    44,    45,    46,    47,
      48,    42,     0,     0,     0,     0,   100,    61,     0,     0,
       0,   108,     0,   137,   110,    50,     0,     0,     0,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,     0,
       0,     0,   114,     0,    68,    67,     0,     0,    40,    41,
      39,    36,    62,     0,     0,    87,    88,    89,     0,     0,
     139,     0,     0,     0,     0,     0,     0,     0,     0,   117,
     116,     0,   141,    43,     0,    37,     0,    35,    32,     0,
     114,     0,   114,    71,    50,    49,     0,   123,     0,     0,
      50,     0,     0,    69,    42,     0,    33,   111,   138,   140,
       0,    70,    51,     0,   125,   124,    50,     0,     0,   119,
     118,    38,     0,    72,    73,    76,     0,     0,   120,   121,
      63,     0,    78,    77,    75,   126,   122,    74
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -225,  -225,   340,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,   133,   178,   122,  -225,  -225,
    -225,  -224,  -106,   239,   207,  -225,  -225,  -225,   213,  -225,
    -153,  -225,    94,  -225,  -225,  -225,    -4,   -45,   -68,  -225,
     -83,   200,  -152,   224,  -225,  -129,  -189,  -225,   158,  -225,
    -225,  -225,  -225,  -225,  -225
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,   183,   146,   220,   244,   181,
      33,   232,    64,    93,   124,   247,    34,    35,   141,   142,
      36,   271,   283,   284,   294,    37,    65,    66,   116,   117,
      67,   135,   136,   163,   164,   139,   170,   171,   211,   230,
     253,    38,    39,    40,    79
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      68,    85,   143,   118,   118,   118,   118,   118,    69,   191,
       4,   217,   173,   196,   292,    70,    41,    98,    42,   119,
     120,   121,   122,   240,    59,   114,    44,    52,    45,   115,
     272,    72,   223,    71,   193,    56,   278,   225,    73,    57,
      58,   226,    60,    61,   234,    74,   227,    91,    92,   125,
     126,   127,   287,   102,   103,   130,   131,   132,   133,   195,
     241,   267,    52,   269,   218,   219,   214,    99,   118,    75,
      56,    43,   249,    77,    57,    58,   293,    60,    61,   218,
     219,    78,   258,   186,   261,   262,   100,   101,   102,   103,
       4,    80,    81,   169,    82,   129,    86,    46,   100,   101,
     102,   103,   100,   101,   102,   103,   277,   100,   101,   102,
     103,   158,    83,   188,   189,   190,    84,   159,    87,    88,
     286,    85,   160,    89,    90,   254,    94,   100,   101,   102,
     103,   260,    95,    96,    47,    48,    49,    50,    51,   105,
      97,   213,    52,   106,    53,    54,    55,   104,   107,   108,
      56,   109,   110,   276,    57,    58,    59,    60,    61,   111,
      62,    63,   100,   101,   102,   103,   239,   169,   113,   112,
     123,   100,   101,   102,   103,   128,   166,   100,   101,   102,
     103,   137,   100,   101,   102,   103,    52,   285,   176,   177,
     178,   179,   180,    85,    56,   134,   138,   140,    57,    58,
     144,    60,    61,   145,    46,   169,   147,   169,   285,   148,
     149,   274,   150,    47,    48,    49,    50,    51,   151,   152,
     153,    52,   154,    53,    54,    55,   167,   168,    85,    56,
     155,   157,   238,    57,    58,    59,    60,    61,   161,    62,
      63,    47,    48,    49,    50,    51,   165,   268,   162,    52,
     172,    53,    54,    55,   174,   175,   182,    56,   184,   185,
     273,    57,    58,    59,    60,    61,   197,    62,    63,    47,
      48,    49,    50,    51,   192,   198,   216,    52,   222,    53,
      54,    55,   212,   224,   229,    56,   231,   233,     4,    57,
      58,    59,    60,    61,   235,    62,    63,    47,    48,    49,
      50,    51,   236,   237,   242,    52,   243,    53,    54,    55,
     246,   248,   250,    56,   251,   252,   255,    57,    58,    59,
      60,    61,   257,    62,    63,     1,     2,   263,   259,   270,
     264,   265,     3,     4,     5,     6,     7,     8,     9,    10,
     266,   282,   275,    11,    12,    13,   279,   280,    59,   290,
     288,    14,    15,   289,   245,   291,   295,   296,    76,    16,
     221,    17,   156,   187,    18,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   297,   281,   215,   194,   209,
     210,   256,   228,     0,     0,     0,     0,     0,     0,     0,
     100,   101,   102,   103
};

static const yytype_int16 yycheck[] =
{
       4,    46,   108,    86,    87,    88,    89,    90,    79,   161,
      13,    20,   141,   166,    14,    10,     9,    62,    11,    87,
      88,    89,    90,   212,    79,    21,     9,    65,    11,    84,
     254,    36,   184,    34,   163,    73,   260,    21,    79,    77,
      78,    21,    80,    81,   197,    79,    21,    77,    78,    94,
      95,    96,   276,    84,    85,   100,   101,   102,   103,   165,
     213,   250,    65,   252,    73,    74,   172,    22,   151,    42,
      73,    64,   224,     0,    77,    78,    76,    80,    81,    73,
      74,     3,   235,   151,   237,   238,    82,    83,    84,    85,
      13,    79,    79,   138,    11,    99,    20,    20,    82,    83,
      84,    85,    82,    83,    84,    85,   259,    82,    83,    84,
      85,    22,    79,   158,   159,   160,    79,    22,    20,    20,
     273,   166,    22,    20,    20,   231,    20,    82,    83,    84,
      85,   237,    20,    20,    57,    58,    59,    60,    61,    79,
      33,    20,    65,    79,    67,    68,    69,    36,    39,    47,
      73,    43,    20,   259,    77,    78,    79,    80,    81,    40,
      83,    84,    82,    83,    84,    85,   211,   212,    40,    79,
      22,    82,    83,    84,    85,    79,    20,    82,    83,    84,
      85,    35,    82,    83,    84,    85,    65,   270,    26,    27,
      28,    29,    30,   238,    73,    79,    37,    79,    77,    78,
      80,    80,    81,    79,    20,   250,    79,   252,   291,    40,
      79,   256,    21,    57,    58,    59,    60,    61,    22,    21,
      21,    65,    21,    67,    68,    69,    70,    71,   273,    73,
      21,    66,    20,    77,    78,    79,    80,    81,    22,    83,
      84,    57,    58,    59,    60,    61,    20,   251,    62,    65,
      47,    67,    68,    69,    22,    34,    22,    73,    20,    79,
      20,    77,    78,    79,    80,    81,    20,    83,    84,    57,
      58,    59,    60,    61,    63,    70,     9,    65,    21,    67,
      68,    69,    38,    20,     7,    73,    22,    21,    13,    77,
      78,    79,    80,    81,    20,    83,    84,    57,    58,    59,
      60,    61,    72,    20,    79,    65,    77,    67,    68,    69,
      45,    21,    40,    73,     4,     8,    21,    77,    78,    79,
      80,    81,    21,    83,    84,     5,     6,    21,    20,    75,
      21,    46,    12,    13,    14,    15,    16,    17,    18,    19,
      21,    47,    21,    23,    24,    25,    21,    21,    79,    79,
      21,    31,    32,    21,   221,    22,    21,    21,    18,    39,
     182,    41,   123,   156,    44,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,   291,   264,   174,   164,    71,
      72,   233,   192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    83,    84,    85
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    12,    13,    14,    15,    16,    17,    18,
      19,    23,    24,    25,    31,    32,    39,    41,    44,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   107,   113,   114,   117,   122,   138,   139,
     140,     9,    11,    64,     9,    11,    20,    57,    58,    59,
      60,    61,    65,    67,    68,    69,    73,    77,    78,    79,
      80,    81,    83,    84,   109,   123,   124,   127,   123,    79,
      10,    34,    36,    79,    79,    42,    89,     0,     3,   141,
      79,    79,    11,    79,    79,   124,    20,    20,    20,    20,
      20,    77,    78,   110,    20,    20,    20,    33,   124,    22,
      82,    83,    84,    85,    36,    79,    79,    39,    47,    43,
      20,    40,    79,    40,    21,    84,   125,   126,   127,   125,
     125,   125,   125,    22,   111,   124,   124,   124,    79,   123,
     124,   124,   124,   124,    79,   128,   129,    35,    37,   132,
      79,   115,   116,   109,    80,    79,   103,    79,    40,    79,
      21,    22,    21,    21,    21,    21,   110,    66,    22,    22,
      22,    22,    62,   130,   131,    20,    20,    70,    71,   124,
     133,   134,    47,   132,    22,    34,    26,    27,    28,    29,
      30,   106,    22,   102,    20,    79,   125,   111,   124,   124,
     124,   129,    63,   132,   130,   109,   117,    20,    70,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    71,
      72,   135,    38,    20,   109,   115,     9,    20,    73,    74,
     104,   103,    21,   129,    20,    21,    21,    21,   128,     7,
     136,    22,   108,    21,   117,    20,    72,    20,    20,   124,
     133,   117,    79,    77,   105,   102,    45,   112,    21,   129,
      40,     4,     8,   137,   109,    21,   135,    21,   117,    20,
     109,   117,   117,    21,    21,    46,    21,   133,   123,   133,
      75,   118,   108,    20,   124,    21,   109,   117,   108,    21,
      21,   104,    47,   119,   120,   127,   117,   108,    21,    21,
      79,    22,    14,    76,   121,    21,    21,   119
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    87,    88,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,    99,   100,   101,   102,   102,   103,   103,
     104,   104,   104,   105,   106,   106,   106,   106,   106,   107,
     108,   108,   109,   109,   109,   109,   109,   109,   110,   110,
     111,   111,   112,   112,   113,   114,   115,   115,   116,   116,
     117,   118,   118,   119,   119,   120,   121,   121,   121,   122,
     123,   123,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   125,
     125,   126,   126,   126,   127,   127,   128,   129,   129,   130,
     130,   131,   132,   132,   133,   133,   133,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   136,   136,   137,
     137,   138,   139,   140,   141,   141
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     8,     9,     5,     8,     0,     3,     6,     3,
       1,     1,     0,     1,     1,     1,     1,     1,     1,     8,
       0,     3,     1,     1,     1,     1,     4,     1,     1,     1,
       0,     3,     0,     4,     4,     5,     1,     3,     3,     5,
       9,     0,     2,     1,     3,     2,     0,     1,     1,     2,
       1,     3,     3,     3,     3,     3,     3,     6,     6,     6,
       2,     1,     1,     1,     4,     4,     4,     4,     4,     1,
       3,     0,     1,     1,     1,     3,     1,     1,     3,     0,
       2,     5,     0,     2,     0,     1,     3,     3,     5,     5,
       6,     6,     7,     4,     5,     5,     7,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     3,     0,
       2,     7,     2,     4,     0,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
        yyerror (&yylloc, sql_string, sql_result, scanner, flag, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, sql_string, sql_result, scanner, flag); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner, SqlCommandFlag flag)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  YYUSE (flag);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner, SqlCommandFlag flag)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp, sql_string, sql_result, scanner, flag);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner, SqlCommandFlag flag)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , sql_string, sql_result, scanner, flag);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner, flag); \
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner, SqlCommandFlag flag)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  YYUSE (flag);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner, SqlCommandFlag flag)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, scanner);
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
  case 2:
#line 263 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1852 "yacc_sql.cpp"
    break;

  case 23:
#line 293 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1861 "yacc_sql.cpp"
    break;

  case 24:
#line 299 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1869 "yacc_sql.cpp"
    break;

  case 25:
#line 304 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1877 "yacc_sql.cpp"
    break;

  case 26:
#line 310 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1885 "yacc_sql.cpp"
    break;

  case 27:
#line 316 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1893 "yacc_sql.cpp"
    break;

  case 28:
#line 322 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1901 "yacc_sql.cpp"
    break;

  case 29:
#line 328 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1911 "yacc_sql.cpp"
    break;

  case 30:
#line 335 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1919 "yacc_sql.cpp"
    break;

  case 31:
#line 341 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1929 "yacc_sql.cpp"
    break;

  case 32:
#line 350 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      create_index.unique = false;
      if ((yyvsp[-1].relation_list) != nullptr) {
        create_index.attributes.swap(*(yyvsp[-1].relation_list));
        delete (yyvsp[-1].relation_list);
      }
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 1947 "yacc_sql.cpp"
    break;

  case 33:
#line 364 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      create_index.unique = true;
      if ((yyvsp[-1].relation_list) != nullptr) {
        create_index.attributes.swap(*(yyvsp[-1].relation_list));
        delete (yyvsp[-1].relation_list);
      }
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 1965 "yacc_sql.cpp"
    break;

  case 34:
#line 381 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1977 "yacc_sql.cpp"
    break;

  case 35:
#line 391 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-3].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-3].attr_info);
      if ((yyvsp[0].string) != nullptr) {
        create_table.storage_format = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 2002 "yacc_sql.cpp"
    break;

  case 36:
#line 414 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2010 "yacc_sql.cpp"
    break;

  case 37:
#line 418 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2024 "yacc_sql.cpp"
    break;

  case 38:
#line 431 "yacc_sql.y"
  {
    (yyval.attr_info) = new AttrInfoSqlNode;
    (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
    (yyval.attr_info)->name = (yyvsp[-5].string);
    (yyval.attr_info)->length = (yyvsp[-2].number);
    (yyval.attr_info)->nullable = (yyvsp[0].nullable_spec);
    free((yyvsp[-5].string));
  }
#line 2037 "yacc_sql.cpp"
    break;

  case 39:
#line 440 "yacc_sql.y"
  {
    (yyval.attr_info) = new AttrInfoSqlNode;
    (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
    (yyval.attr_info)->name = (yyvsp[-2].string);
    if ((AttrType)(yyvsp[-1].number) == AttrType::DATES) {
    (yyval.attr_info)->length = 8;
    } else if ((AttrType)(yyvsp[-1].number) == AttrType::CHARS) {
    (yyval.attr_info)->length = 32;
    } else {
    (yyval.attr_info)->length = 4;
    }
    (yyval.attr_info)->nullable = (yyvsp[0].nullable_spec);
    free((yyvsp[-2].string));
  }
#line 2056 "yacc_sql.cpp"
    break;

  case 40:
#line 457 "yacc_sql.y"
         { (yyval.nullable_spec) = true; }
#line 2062 "yacc_sql.cpp"
    break;

  case 41:
#line 458 "yacc_sql.y"
               { (yyval.nullable_spec) = false; }
#line 2068 "yacc_sql.cpp"
    break;

  case 42:
#line 459 "yacc_sql.y"
                { (yyval.nullable_spec) = true; }
#line 2074 "yacc_sql.cpp"
    break;

  case 43:
#line 463 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2080 "yacc_sql.cpp"
    break;

  case 44:
#line 466 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2086 "yacc_sql.cpp"
    break;

  case 45:
#line 467 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2092 "yacc_sql.cpp"
    break;

  case 46:
#line 468 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2098 "yacc_sql.cpp"
    break;

  case 47:
#line 469 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2104 "yacc_sql.cpp"
    break;

  case 48:
#line 470 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2110 "yacc_sql.cpp"
    break;

  case 49:
#line 474 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
        delete (yyvsp[-1].value_list);
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-5].string));
    }
#line 2127 "yacc_sql.cpp"
    break;

  case 50:
#line 490 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2135 "yacc_sql.cpp"
    break;

  case 51:
#line 493 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2149 "yacc_sql.cpp"
    break;

  case 52:
#line 504 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2158 "yacc_sql.cpp"
    break;

  case 53:
#line 508 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2167 "yacc_sql.cpp"
    break;

  case 54:
#line 512 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2178 "yacc_sql.cpp"
    break;

  case 55:
#line 518 "yacc_sql.y"
          {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      if (!is_valid_date(tmp)) {
        (yyval.value) = new Value(AttrType::UNDEFINED, nullptr);
      } else {
        struct tm tm; bzero(&tm, sizeof(tm));
        strptime(tmp, "%Y-%m-%d", &tm);
        (yyval.value) = new Value(mktime(&tm));
      }
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2195 "yacc_sql.cpp"
    break;

  case 56:
#line 530 "yacc_sql.y"
                                                      {
      vector<float>* cur = (yyvsp[-1].vector_elem_list);
      if((yyvsp[-1].vector_elem_list) == nullptr){
        cur = new vector<float>;
      }
      cur->push_back((float)(yyvsp[-2].floats));
      std::reverse(cur->begin(), cur->end());
      (yyval.value) = new Value(cur->data(), cur->size());
      delete cur;
    }
#line 2210 "yacc_sql.cpp"
    break;

  case 57:
#line 540 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2219 "yacc_sql.cpp"
    break;

  case 58:
#line 546 "yacc_sql.y"
           {
      (yyval.floats) = (float)(yyvsp[0].number);
      (yyloc) = (yylsp[0]);
    }
#line 2228 "yacc_sql.cpp"
    break;

  case 59:
#line 550 "yacc_sql.y"
           {
      (yyval.floats) = (float)(yyvsp[0].floats);
      (yyloc) = (yylsp[0]);
    }
#line 2237 "yacc_sql.cpp"
    break;

  case 60:
#line 557 "yacc_sql.y"
    {
      (yyval.vector_elem_list) = nullptr;
    }
#line 2245 "yacc_sql.cpp"
    break;

  case 61:
#line 560 "yacc_sql.y"
                                         {
      (yyval.vector_elem_list) = (yyvsp[0].vector_elem_list);
      if((yyval.vector_elem_list) == nullptr){
        (yyval.vector_elem_list) = new vector<float>;
      }
      (yyval.vector_elem_list)->push_back((yyvsp[-1].floats));
    }
#line 2257 "yacc_sql.cpp"
    break;

  case 62:
#line 569 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2265 "yacc_sql.cpp"
    break;

  case 63:
#line 573 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2273 "yacc_sql.cpp"
    break;

  case 64:
#line 580 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2287 "yacc_sql.cpp"
    break;

  case 65:
#line 592 "yacc_sql.y"
  {
    (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
    (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);
    if ((yyvsp[-1].set_clause_list) != nullptr) {
      (yyval.sql_node)->update.set_clauses.swap(*(yyvsp[-1].set_clause_list));
      delete (yyvsp[-1].set_clause_list);
    }
    if ((yyvsp[0].condition_list) != nullptr) {
      (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
      delete (yyvsp[0].condition_list);
    }
    free((yyvsp[-3].string));
  }
#line 2305 "yacc_sql.cpp"
    break;

  case 66:
#line 608 "yacc_sql.y"
             {
    (yyval.set_clause_list) = new std::vector<SetClauseSqlNode>;
    (yyval.set_clause_list)->emplace_back(*(yyvsp[0].set_clause));
    delete (yyvsp[0].set_clause);
  }
#line 2315 "yacc_sql.cpp"
    break;

  case 67:
#line 614 "yacc_sql.y"
  {
    if ((yyvsp[0].set_clause_list) != nullptr) {
      (yyval.set_clause_list) = (yyvsp[0].set_clause_list);
    } else {
      (yyval.set_clause_list) = new std::vector<SetClauseSqlNode>;
    }
    (yyval.set_clause_list)->emplace((yyval.set_clause_list)->begin(), *(yyvsp[-2].set_clause));
    delete (yyvsp[-2].set_clause);
  }
#line 2329 "yacc_sql.cpp"
    break;

  case 68:
#line 626 "yacc_sql.y"
              {
    (yyval.set_clause) = new SetClauseSqlNode;
    (yyval.set_clause)->attribute_name = (yyvsp[-2].string);
    (yyval.set_clause)->value = *(yyvsp[0].value);
    (yyval.set_clause)->has_subquery = false;
    (yyval.set_clause)->subquery = nullptr;
    free((yyvsp[-2].string));
    delete (yyvsp[0].value);
  }
#line 2343 "yacc_sql.cpp"
    break;

  case 69:
#line 635 "yacc_sql.y"
                                    {
    (yyval.set_clause) = new SetClauseSqlNode;
    (yyval.set_clause)->attribute_name = (yyvsp[-4].string);
    (yyval.set_clause)->has_subquery = true;
    (yyval.set_clause)->subquery = (yyvsp[-1].sql_node);
    free((yyvsp[-4].string));
  }
#line 2355 "yacc_sql.cpp"
    break;

  case 70:
#line 645 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-7].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-7].expression_list));
        delete (yyvsp[-7].expression_list);
      }

      if ((yyvsp[-5].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-5].relation_list));
        delete (yyvsp[-5].relation_list);
      }

      if ((yyvsp[-4].join_tuple_list) != nullptr) {
        (yyval.sql_node)->selection.join_relations.swap(*(std::get<0>(*(yyvsp[-4].join_tuple_list))));
        (yyval.sql_node)->selection.join_conditions.swap(*(std::get<1>(*(yyvsp[-4].join_tuple_list))));
        delete std::get<0>(*(yyvsp[-4].join_tuple_list));
        delete std::get<1>(*(yyvsp[-4].join_tuple_list));
        std::reverse((yyval.sql_node)->selection.join_relations.begin(), (yyval.sql_node)->selection.join_relations.end());
        std::reverse((yyval.sql_node)->selection.join_conditions.begin(), (yyval.sql_node)->selection.join_conditions.end());
        delete (yyvsp[-4].join_tuple_list);
      }

      if ((yyvsp[-3].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-3].condition_list));
        delete (yyvsp[-3].condition_list);
      }

      if ((yyvsp[-2].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-2].expression_list));
        delete (yyvsp[-2].expression_list);
      }

      // 处理having，having和where不能共存，先不考虑出现这种测试用例
      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.having.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }

			if ((yyvsp[0].order_by_list) != nullptr) {
				(yyval.sql_node)->selection.order_by.swap(*(yyvsp[0].order_by_list));
				delete (yyvsp[0].order_by_list);
			}
	}
#line 2403 "yacc_sql.cpp"
    break;

  case 71:
#line 692 "yacc_sql.y"
        {
		(yyval.order_by_list) = nullptr;
	}
#line 2411 "yacc_sql.cpp"
    break;

  case 72:
#line 696 "yacc_sql.y"
        {
		(yyval.order_by_list) = (yyvsp[0].order_by_list);
	}
#line 2419 "yacc_sql.cpp"
    break;

  case 73:
#line 703 "yacc_sql.y"
        {
		(yyval.order_by_list) = new std::vector<OrderByItem>;
		(yyval.order_by_list)->emplace_back(*(yyvsp[0].order_by_item));
		delete (yyvsp[0].order_by_item);
	}
#line 2429 "yacc_sql.cpp"
    break;

  case 74:
#line 709 "yacc_sql.y"
        {
		if ((yyvsp[0].order_by_list) != nullptr) {
			(yyval.order_by_list) = (yyvsp[0].order_by_list);
		} else {
			(yyval.order_by_list) = new std::vector<OrderByItem>;
		}
		(yyval.order_by_list)->emplace((yyval.order_by_list)->begin(), *(yyvsp[-2].order_by_item));
		delete (yyvsp[-2].order_by_item);
	}
#line 2443 "yacc_sql.cpp"
    break;

  case 75:
#line 722 "yacc_sql.y"
        {
		(yyval.order_by_item) = new OrderByItem;
		(yyval.order_by_item)->attr = *(yyvsp[-1].rel_attr);
		(yyval.order_by_item)->asc = (yyvsp[0].asc_desc);
		delete (yyvsp[-1].rel_attr);
	}
#line 2454 "yacc_sql.cpp"
    break;

  case 76:
#line 732 "yacc_sql.y"
        {
		(yyval.asc_desc) = true; // default is ascending
	}
#line 2462 "yacc_sql.cpp"
    break;

  case 77:
#line 736 "yacc_sql.y"
        {
		(yyval.asc_desc) = true;
	}
#line 2470 "yacc_sql.cpp"
    break;

  case 78:
#line 740 "yacc_sql.y"
        {
		(yyval.asc_desc) = false;
	}
#line 2478 "yacc_sql.cpp"
    break;

  case 79:
#line 747 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2488 "yacc_sql.cpp"
    break;

  case 80:
#line 756 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2497 "yacc_sql.cpp"
    break;

  case 81:
#line 761 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2510 "yacc_sql.cpp"
    break;

  case 82:
#line 771 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2518 "yacc_sql.cpp"
    break;

  case 83:
#line 774 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2526 "yacc_sql.cpp"
    break;

  case 84:
#line 777 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2534 "yacc_sql.cpp"
    break;

  case 85:
#line 780 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2542 "yacc_sql.cpp"
    break;

  case 86:
#line 783 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2551 "yacc_sql.cpp"
    break;

  case 87:
#line 787 "yacc_sql.y"
                                                            {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::L2_DIS, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2559 "yacc_sql.cpp"
    break;

  case 88:
#line 790 "yacc_sql.y"
                                                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::COS_DIS, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2567 "yacc_sql.cpp"
    break;

  case 89:
#line 793 "yacc_sql.y"
                                                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::INN_PDT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2575 "yacc_sql.cpp"
    break;

  case 90:
#line 796 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2583 "yacc_sql.cpp"
    break;

  case 91:
#line 799 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2593 "yacc_sql.cpp"
    break;

  case 92:
#line 804 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2604 "yacc_sql.cpp"
    break;

  case 93:
#line 810 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2612 "yacc_sql.cpp"
    break;

  case 94:
#line 815 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("max", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2620 "yacc_sql.cpp"
    break;

  case 95:
#line 818 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("min", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2628 "yacc_sql.cpp"
    break;

  case 96:
#line 821 "yacc_sql.y"
                                            {
      (yyval.expression) = create_aggregate_expression("count", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2636 "yacc_sql.cpp"
    break;

  case 97:
#line 824 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("avg", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2644 "yacc_sql.cpp"
    break;

  case 98:
#line 827 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("sum", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2652 "yacc_sql.cpp"
    break;

  case 99:
#line 846 "yacc_sql.y"
                 {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2660 "yacc_sql.cpp"
    break;

  case 100:
#line 849 "yacc_sql.y"
                                           {
      (yyval.expression) = nullptr;
      // 到这里肯定有问题
      if ((yyvsp[0].expression)) {
        delete (yyvsp[0].expression);
      }
      if ((yyvsp[-2].expression)) {
        delete (yyvsp[-2].expression);
      }
      yyerror(&(yylsp[-2]), NULL, sql_result, NULL, SCF_ERROR_AGGREGATION, "aggregation func has too many fields");
    }
#line 2676 "yacc_sql.cpp"
    break;

  case 101:
#line 863 "yacc_sql.y"
    {
      std::string null_string = "";
      (yyval.expression) = new UnboundFieldExpr(null_string, null_string);
      (yyval.expression)->set_name(null_string);
    }
#line 2686 "yacc_sql.cpp"
    break;

  case 102:
#line 868 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2694 "yacc_sql.cpp"
    break;

  case 103:
#line 871 "yacc_sql.y"
               {
      (yyval.expression) = new UnboundFieldExpr((yyvsp[0].rel_attr)->relation_name, (yyvsp[0].rel_attr)->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2704 "yacc_sql.cpp"
    break;

  case 104:
#line 879 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2714 "yacc_sql.cpp"
    break;

  case 105:
#line 884 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2726 "yacc_sql.cpp"
    break;

  case 106:
#line 894 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2734 "yacc_sql.cpp"
    break;

  case 107:
#line 899 "yacc_sql.y"
             {
      (yyval.relation_list) = new std::vector<std::string>();
      (yyval.relation_list)->push_back((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2744 "yacc_sql.cpp"
    break;

  case 108:
#line 904 "yacc_sql.y"
                              {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }

      (yyval.relation_list)->insert((yyval.relation_list)->begin(), (yyvsp[-2].string));
      free((yyvsp[-2].string));
    }
#line 2759 "yacc_sql.cpp"
    break;

  case 109:
#line 918 "yacc_sql.y"
    {
      (yyval.join_tuple_list) = nullptr;
    }
#line 2767 "yacc_sql.cpp"
    break;

  case 110:
#line 921 "yacc_sql.y"
                     {
      if ((yyvsp[0].join_tuple_list) == nullptr) {
        std::vector<std::string> *vs = new std::vector<std::string>;
        std::vector<std::vector<ConditionSqlNode> *> *vvc = new std::vector<std::vector<ConditionSqlNode> *>;
        (yyval.join_tuple_list) = new std::tuple<std::vector<std::string> *, std::vector<std::vector<ConditionSqlNode> *> *>(vs, vvc);
      } else {
        (yyval.join_tuple_list) = (yyvsp[0].join_tuple_list);
      }
      std::vector<std::string> *vs = std::get<0>(*(yyval.join_tuple_list));
      std::vector<std::vector<ConditionSqlNode> *> *vvc = std::get<1>(*(yyval.join_tuple_list));
      vs->emplace_back(std::get<0>(*(yyvsp[-1].join_tuple)));
      vvc->emplace_back(std::get<1>(*(yyvsp[-1].join_tuple)));
      delete (yyvsp[-1].join_tuple);
    }
#line 2786 "yacc_sql.cpp"
    break;

  case 111:
#line 937 "yacc_sql.y"
                                          {
      (yyval.join_tuple) = new std::tuple<std::string, std::vector<ConditionSqlNode> *>((yyvsp[-2].string), (yyvsp[0].condition_list));
      free((yyvsp[-2].string));
    }
#line 2795 "yacc_sql.cpp"
    break;

  case 112:
#line 944 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2803 "yacc_sql.cpp"
    break;

  case 113:
#line 947 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2811 "yacc_sql.cpp"
    break;

  case 114:
#line 953 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2819 "yacc_sql.cpp"
    break;

  case 115:
#line 956 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 2829 "yacc_sql.cpp"
    break;

  case 116:
#line 961 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2839 "yacc_sql.cpp"
    break;

  case 117:
#line 1018 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 2851 "yacc_sql.cpp"
    break;

  case 118:
#line 1025 "yacc_sql.y"
                                                   {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-4].expression);
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 2865 "yacc_sql.cpp"
    break;

  case 119:
#line 1034 "yacc_sql.y"
                                                {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-4].expression);
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = CompOp::IN;
    }
#line 2879 "yacc_sql.cpp"
    break;

  case 120:
#line 1043 "yacc_sql.y"
                                                    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-5].expression);
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = CompOp::NOT_IN;
    }
#line 2893 "yacc_sql.cpp"
    break;

  case 121:
#line 1053 "yacc_sql.y"
                                                    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-5].expression);
      std::vector<Value> *values;
      if ((yyvsp[-1].value_list) != nullptr) {
        values = (yyvsp[-1].value_list);
      } else {
        values = new std::vector<Value>();
      }
      values->emplace_back(*(yyvsp[-2].value));
      ValueListExpr *right_expr = new ValueListExpr(values);
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = CompOp::IN;
    }
#line 2914 "yacc_sql.cpp"
    break;

  case 122:
#line 1069 "yacc_sql.y"
                                                        {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-6].expression);
      std::vector<Value> *values;
      if ((yyvsp[-1].value_list) != nullptr) {
        values = (yyvsp[-1].value_list);
      } else {
        values = new std::vector<Value>();
      }
      values->emplace_back(*(yyvsp[-2].value));
      ValueListExpr *right_expr = new ValueListExpr(values);
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = CompOp::NOT_IN;
    }
#line 2935 "yacc_sql.cpp"
    break;

  case 123:
#line 1085 "yacc_sql.y"
                                         {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      DumbExpr *left_expr = new DumbExpr();
      (yyval.condition)->left_expr = left_expr;
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = CompOp::EXISTS;
    }
#line 2950 "yacc_sql.cpp"
    break;

  case 124:
#line 1095 "yacc_sql.y"
                                             {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      DumbExpr *left_expr = new DumbExpr();
      (yyval.condition)->left_expr = left_expr;
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = CompOp::NOT_EXISTS;
    }
#line 2965 "yacc_sql.cpp"
    break;

  case 125:
#line 1105 "yacc_sql.y"
                                                   {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      UnboundSubqueryExpr *left_expr = new UnboundSubqueryExpr((yyvsp[-3].sql_node));
      (yyval.condition)->left_expr = left_expr;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 2979 "yacc_sql.cpp"
    break;

  case 126:
#line 1114 "yacc_sql.y"
                                                                  {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = new UnboundSubqueryExpr((yyvsp[-5].sql_node));
      (yyval.condition)->right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 2992 "yacc_sql.cpp"
    break;

  case 127:
#line 1125 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2998 "yacc_sql.cpp"
    break;

  case 128:
#line 1126 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3004 "yacc_sql.cpp"
    break;

  case 129:
#line 1127 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3010 "yacc_sql.cpp"
    break;

  case 130:
#line 1128 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3016 "yacc_sql.cpp"
    break;

  case 131:
#line 1129 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3022 "yacc_sql.cpp"
    break;

  case 132:
#line 1130 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3028 "yacc_sql.cpp"
    break;

  case 133:
#line 1131 "yacc_sql.y"
         { (yyval.comp) = LIKE; }
#line 3034 "yacc_sql.cpp"
    break;

  case 134:
#line 1132 "yacc_sql.y"
          {(yyval.comp) = NOT_LIKE; }
#line 3040 "yacc_sql.cpp"
    break;

  case 135:
#line 1133 "yacc_sql.y"
           { (yyval.comp) = IS; }
#line 3046 "yacc_sql.cpp"
    break;

  case 136:
#line 1134 "yacc_sql.y"
               { (yyval.comp) = IS_NOT; }
#line 3052 "yacc_sql.cpp"
    break;

  case 137:
#line 1140 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3060 "yacc_sql.cpp"
    break;

  case 138:
#line 1145 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3068 "yacc_sql.cpp"
    break;

  case 139:
#line 1152 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3076 "yacc_sql.cpp"
    break;

  case 140:
#line 1155 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3084 "yacc_sql.cpp"
    break;

  case 141:
#line 1161 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3098 "yacc_sql.cpp"
    break;

  case 142:
#line 1174 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3107 "yacc_sql.cpp"
    break;

  case 143:
#line 1182 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3119 "yacc_sql.cpp"
    break;


#line 3123 "yacc_sql.cpp"

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, sql_string, sql_result, scanner, flag, YY_("syntax error"));
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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
        yyerror (&yylloc, sql_string, sql_result, scanner, flag, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner, flag);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, sql_string, sql_result, scanner, flag);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
  yyerror (&yylloc, sql_string, sql_result, scanner, flag, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner, flag);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp, sql_string, sql_result, scanner, flag);
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
#line 1194 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner, SCF_ERROR);
  yylex_destroy(scanner);
  return result;
}
