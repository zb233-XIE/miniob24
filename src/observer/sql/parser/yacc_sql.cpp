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
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include <cstdint>
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
#include "common/type/attr_type.h"

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

#line 143 "yacc_sql.cpp"

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

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_BY = 4,                         /* BY  */
  YYSYMBOL_CREATE = 5,                     /* CREATE  */
  YYSYMBOL_DROP = 6,                       /* DROP  */
  YYSYMBOL_GROUP = 7,                      /* GROUP  */
  YYSYMBOL_HAVING = 8,                     /* HAVING  */
  YYSYMBOL_TABLE = 9,                      /* TABLE  */
  YYSYMBOL_TABLES = 10,                    /* TABLES  */
  YYSYMBOL_INDEX = 11,                     /* INDEX  */
  YYSYMBOL_CALC = 12,                      /* CALC  */
  YYSYMBOL_SELECT = 13,                    /* SELECT  */
  YYSYMBOL_DESC = 14,                      /* DESC  */
  YYSYMBOL_SHOW = 15,                      /* SHOW  */
  YYSYMBOL_SYNC = 16,                      /* SYNC  */
  YYSYMBOL_INSERT = 17,                    /* INSERT  */
  YYSYMBOL_DELETE = 18,                    /* DELETE  */
  YYSYMBOL_UPDATE = 19,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 20,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 21,                    /* RBRACE  */
  YYSYMBOL_COMMA = 22,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 23,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 24,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 25,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 26,                     /* INT_T  */
  YYSYMBOL_STRING_T = 27,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 28,                   /* FLOAT_T  */
  YYSYMBOL_VECTOR_T = 29,                  /* VECTOR_T  */
  YYSYMBOL_DATE_T = 30,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 31,                    /* TEXT_T  */
  YYSYMBOL_HELP = 32,                      /* HELP  */
  YYSYMBOL_EXIT = 33,                      /* EXIT  */
  YYSYMBOL_DOT = 34,                       /* DOT  */
  YYSYMBOL_INTO = 35,                      /* INTO  */
  YYSYMBOL_VALUES = 36,                    /* VALUES  */
  YYSYMBOL_FROM = 37,                      /* FROM  */
  YYSYMBOL_WHERE = 38,                     /* WHERE  */
  YYSYMBOL_AND = 39,                       /* AND  */
  YYSYMBOL_OR = 40,                        /* OR  */
  YYSYMBOL_SET = 41,                       /* SET  */
  YYSYMBOL_ON = 42,                        /* ON  */
  YYSYMBOL_LOAD = 43,                      /* LOAD  */
  YYSYMBOL_DATA = 44,                      /* DATA  */
  YYSYMBOL_INFILE = 45,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 46,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 47,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 48,                    /* FORMAT  */
  YYSYMBOL_EQ = 49,                        /* EQ  */
  YYSYMBOL_LT = 50,                        /* LT  */
  YYSYMBOL_GT = 51,                        /* GT  */
  YYSYMBOL_LE = 52,                        /* LE  */
  YYSYMBOL_GE = 53,                        /* GE  */
  YYSYMBOL_NE = 54,                        /* NE  */
  YYSYMBOL_LK = 55,                        /* LK  */
  YYSYMBOL_NLK = 56,                       /* NLK  */
  YYSYMBOL_IS_T = 57,                      /* IS_T  */
  YYSYMBOL_IS_NOT_T = 58,                  /* IS_NOT_T  */
  YYSYMBOL_MAX = 59,                       /* MAX  */
  YYSYMBOL_MIN = 60,                       /* MIN  */
  YYSYMBOL_COUNT = 61,                     /* COUNT  */
  YYSYMBOL_AVG = 62,                       /* AVG  */
  YYSYMBOL_SUM = 63,                       /* SUM  */
  YYSYMBOL_INNER = 64,                     /* INNER  */
  YYSYMBOL_JOIN = 65,                      /* JOIN  */
  YYSYMBOL_UNIQUE = 66,                    /* UNIQUE  */
  YYSYMBOL_LBRACKET = 67,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 68,                  /* RBRACKET  */
  YYSYMBOL_L2_DISTANCE = 69,               /* L2_DISTANCE  */
  YYSYMBOL_COSINE_DISTANCE = 70,           /* COSINE_DISTANCE  */
  YYSYMBOL_INNER_PRODUCT = 71,             /* INNER_PRODUCT  */
  YYSYMBOL_EXISTS_T = 72,                  /* EXISTS_T  */
  YYSYMBOL_NOT = 73,                       /* NOT  */
  YYSYMBOL_IN_T = 74,                      /* IN_T  */
  YYSYMBOL_VIEW = 75,                      /* VIEW  */
  YYSYMBOL_NULL_T = 76,                    /* NULL_T  */
  YYSYMBOL_NOT_NULL_T = 77,                /* NOT_NULL_T  */
  YYSYMBOL_ORDER_BY = 78,                  /* ORDER_BY  */
  YYSYMBOL_ASC = 79,                       /* ASC  */
  YYSYMBOL_AS = 80,                        /* AS  */
  YYSYMBOL_NUMBER = 81,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 82,                     /* FLOAT  */
  YYSYMBOL_ID = 83,                        /* ID  */
  YYSYMBOL_SSS = 84,                       /* SSS  */
  YYSYMBOL_DATE = 85,                      /* DATE  */
  YYSYMBOL_86_ = 86,                       /* '+'  */
  YYSYMBOL_87_ = 87,                       /* '-'  */
  YYSYMBOL_88_ = 88,                       /* '*'  */
  YYSYMBOL_89_ = 89,                       /* '/'  */
  YYSYMBOL_UMINUS = 90,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 91,                  /* $accept  */
  YYSYMBOL_commands = 92,                  /* commands  */
  YYSYMBOL_command_wrapper = 93,           /* command_wrapper  */
  YYSYMBOL_id_list = 94,                   /* id_list  */
  YYSYMBOL_exit_stmt = 95,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 96,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 97,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 98,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 99,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 100,            /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 101,          /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 102,         /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 103,          /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 104,        /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 105,          /* drop_index_stmt  */
  YYSYMBOL_as_select = 106,                /* as_select  */
  YYSYMBOL_create_table_stmt = 107,        /* create_table_stmt  */
  YYSYMBOL_create_view_stmt = 108,         /* create_view_stmt  */
  YYSYMBOL_attr_def_list = 109,            /* attr_def_list  */
  YYSYMBOL_attr_def = 110,                 /* attr_def  */
  YYSYMBOL_nullable_spec = 111,            /* nullable_spec  */
  YYSYMBOL_number = 112,                   /* number  */
  YYSYMBOL_type = 113,                     /* type  */
  YYSYMBOL_insert_stmt = 114,              /* insert_stmt  */
  YYSYMBOL_value_list = 115,               /* value_list  */
  YYSYMBOL_value = 116,                    /* value  */
  YYSYMBOL_vector_elem = 117,              /* vector_elem  */
  YYSYMBOL_vector_value_list = 118,        /* vector_value_list  */
  YYSYMBOL_storage_format = 119,           /* storage_format  */
  YYSYMBOL_delete_stmt = 120,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 121,              /* update_stmt  */
  YYSYMBOL_set_clause_list = 122,          /* set_clause_list  */
  YYSYMBOL_set_clause = 123,               /* set_clause  */
  YYSYMBOL_select_stmt = 124,              /* select_stmt  */
  YYSYMBOL_order_by = 125,                 /* order_by  */
  YYSYMBOL_order_by_list = 126,            /* order_by_list  */
  YYSYMBOL_order_by_item = 127,            /* order_by_item  */
  YYSYMBOL_asc_desc = 128,                 /* asc_desc  */
  YYSYMBOL_calc_stmt = 129,                /* calc_stmt  */
  YYSYMBOL_expression_list = 130,          /* expression_list  */
  YYSYMBOL_expression = 131,               /* expression  */
  YYSYMBOL_agg_fun_attr_list = 132,        /* agg_fun_attr_list  */
  YYSYMBOL_agg_fun_attr = 133,             /* agg_fun_attr  */
  YYSYMBOL_rel_attr = 134,                 /* rel_attr  */
  YYSYMBOL_relation = 135,                 /* relation  */
  YYSYMBOL_rel_list = 136,                 /* rel_list  */
  YYSYMBOL_join_list = 137,                /* join_list  */
  YYSYMBOL_join = 138,                     /* join  */
  YYSYMBOL_where = 139,                    /* where  */
  YYSYMBOL_condition_list = 140,           /* condition_list  */
  YYSYMBOL_condition = 141,                /* condition  */
  YYSYMBOL_comp_op = 142,                  /* comp_op  */
  YYSYMBOL_group_by = 143,                 /* group_by  */
  YYSYMBOL_having = 144,                   /* having  */
  YYSYMBOL_load_data_stmt = 145,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 146,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 147,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 148             /* opt_semicolon  */
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
#define YYFINAL  79
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   445

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  91
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  164
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  331

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   341


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
       2,     2,    88,    86,     2,    87,     2,    89,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    90
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   271,   271,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   303,   306,   311,   320,   326,   332,
     337,   343,   349,   355,   361,   368,   374,   382,   401,   422,
     433,   436,   439,   444,   473,   488,   502,   505,   518,   527,
     547,   548,   549,   553,   556,   557,   558,   559,   560,   561,
     564,   581,   584,   595,   599,   603,   609,   621,   631,   637,
     641,   648,   651,   660,   663,   670,   682,   699,   704,   717,
     726,   735,   789,   792,   799,   805,   818,   829,   832,   836,
     843,   852,   857,   864,   871,   880,   892,   906,   909,   912,
     915,   918,   922,   925,   928,   931,   934,   939,   945,   948,
     953,   956,   959,   962,   965,   984,   987,  1001,  1006,  1009,
    1017,  1022,  1032,  1038,  1045,  1054,  1059,  1073,  1076,  1092,
    1099,  1102,  1108,  1111,  1116,  1121,  1181,  1189,  1198,  1207,
    1217,  1233,  1249,  1259,  1269,  1278,  1289,  1290,  1291,  1292,
    1293,  1294,  1295,  1296,  1297,  1298,  1304,  1308,  1316,  1319,
    1324,  1337,  1345,  1355,  1356
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
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "BY",
  "CREATE", "DROP", "GROUP", "HAVING", "TABLE", "TABLES", "INDEX", "CALC",
  "SELECT", "DESC", "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE",
  "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T",
  "STRING_T", "FLOAT_T", "VECTOR_T", "DATE_T", "TEXT_T", "HELP", "EXIT",
  "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "OR", "SET", "ON",
  "LOAD", "DATA", "INFILE", "EXPLAIN", "STORAGE", "FORMAT", "EQ", "LT",
  "GT", "LE", "GE", "NE", "LK", "NLK", "IS_T", "IS_NOT_T", "MAX", "MIN",
  "COUNT", "AVG", "SUM", "INNER", "JOIN", "UNIQUE", "LBRACKET", "RBRACKET",
  "L2_DISTANCE", "COSINE_DISTANCE", "INNER_PRODUCT", "EXISTS_T", "NOT",
  "IN_T", "VIEW", "NULL_T", "NOT_NULL_T", "ORDER_BY", "ASC", "AS",
  "NUMBER", "FLOAT", "ID", "SSS", "DATE", "'+'", "'-'", "'*'", "'/'",
  "UMINUS", "$accept", "commands", "command_wrapper", "id_list",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "drop_index_stmt", "as_select",
  "create_table_stmt", "create_view_stmt", "attr_def_list", "attr_def",
  "nullable_spec", "number", "type", "insert_stmt", "value_list", "value",
  "vector_elem", "vector_value_list", "storage_format", "delete_stmt",
  "update_stmt", "set_clause_list", "set_clause", "select_stmt",
  "order_by", "order_by_list", "order_by_item", "asc_desc", "calc_stmt",
  "expression_list", "expression", "agg_fun_attr_list", "agg_fun_attr",
  "rel_attr", "relation", "rel_list", "join_list", "join", "where",
  "condition_list", "condition", "comp_op", "group_by", "having",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-271)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     358,   135,    31,   214,   214,   -62,    13,  -271,    18,   -10,
     -38,  -271,  -271,  -271,  -271,  -271,   -15,    26,   358,    74,
      91,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,
    -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,
    -271,  -271,    45,    59,   134,    65,    70,    75,   214,   139,
     140,   142,   143,   145,   -34,   149,   150,   156,  -271,  -271,
    -271,   144,  -271,  -271,   214,  -271,  -271,  -271,    -8,  -271,
     154,  -271,  -271,    96,   102,   141,   138,   147,  -271,  -271,
    -271,  -271,     6,   151,   114,    10,  -271,   158,    28,   -59,
     -59,   -59,   -59,   -59,  -271,  -271,   176,   214,   214,   214,
     -50,  -271,   214,   120,   180,   214,   214,   214,   214,   126,
     177,   174,   131,    99,   132,   136,   205,  -271,  -271,   137,
     179,    10,   201,   159,   153,  -271,   191,  -271,   206,   209,
    -271,   207,   219,   221,   227,   -34,   181,    68,    85,   119,
    -271,  -271,  -271,   228,   214,   -54,   -54,  -271,  -271,   -39,
     230,   194,   241,   184,  -271,   213,   174,   248,  -271,   243,
     367,   258,  -271,   262,   203,   242,    10,   205,  -271,   204,
    -271,   -59,  -271,  -271,  -271,  -271,   176,  -271,   214,   214,
     214,   214,  -271,   208,  -271,   126,   223,   174,   194,    99,
      42,   269,   220,   356,  -271,    17,   148,  -271,   131,   284,
    -271,  -271,  -271,  -271,  -271,  -271,     0,   136,   279,   126,
     288,  -271,  -271,  -271,  -271,  -271,    33,    48,    63,  -271,
    -271,  -271,   126,   302,  -271,   290,   289,   205,   296,  -271,
    -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,  -271,   245,
     297,   244,   184,   184,   205,  -271,  -271,   235,   240,  -271,
    -271,  -271,   258,   275,   303,   126,  -271,  -271,  -271,   281,
     326,   330,    99,   318,   366,   319,   205,   322,    15,    42,
     -22,  -271,  -271,   325,  -271,  -271,   327,  -271,   299,    12,
    -271,   328,   184,   214,   184,   273,   290,  -271,   274,  -271,
     331,    15,   290,   332,   333,  -271,    62,   311,  -271,  -271,
    -271,  -271,  -271,   282,  -271,  -271,    42,   -22,  -271,   290,
     345,   346,  -271,  -271,  -271,   285,  -271,   347,    29,   357,
     359,  -271,  -271,  -271,   282,  -271,  -271,  -271,  -271,  -271,
    -271
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    30,     0,     0,
       0,    31,    32,    33,    29,    28,     0,     0,     0,     0,
     163,    23,    22,    15,    16,    17,    18,    10,    11,    12,
      13,    14,     8,     9,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    68,    63,
      64,   120,    65,    66,     0,   108,   106,    90,    91,   107,
       0,    36,    35,     0,     0,     0,     0,     0,   161,     1,
     164,     2,    40,     0,     0,    24,    34,     0,     0,   117,
     117,   117,   117,   117,    69,    70,    71,     0,     0,     0,
       0,   105,     0,     0,    92,     0,     0,     0,     0,     0,
       0,   130,     0,     0,     0,     0,     0,    44,    42,     0,
       0,    24,    25,     0,     0,   101,   120,   118,     0,   115,
     119,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     121,   109,    94,    93,     0,    97,    98,    99,   100,   122,
     125,   127,     0,   132,    75,     0,   130,    77,   162,     0,
       0,    46,    41,     0,     0,     0,    24,     0,    39,     0,
     110,   117,   111,   112,   113,   114,    71,    67,     0,     0,
       0,     0,    95,     0,   123,     0,     0,   130,   127,     0,
       0,     0,     0,     0,   131,   133,     0,    76,     0,     0,
      54,    55,    56,    57,    58,    59,    52,     0,     0,     0,
       0,    27,    26,    45,   116,    72,     0,     0,     0,    96,
     124,   126,     0,   156,   128,    61,     0,     0,     0,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,     0,
       0,     0,   132,   132,     0,    79,    78,     0,     0,    50,
      51,    49,    46,    73,     0,     0,   102,   103,   104,     0,
       0,   158,     0,     0,     0,     0,     0,     0,     0,     0,
     136,   134,   135,     0,   160,    53,     0,    47,     0,    40,
      37,     0,   132,     0,   132,    82,    61,    60,     0,   142,
       0,     0,    61,     0,     0,    80,    52,     0,    43,    38,
     129,   157,   159,     0,    81,    62,     0,   144,   143,    61,
       0,     0,   138,   137,    48,     0,    83,    84,    87,     0,
       0,   139,   140,    74,     0,    89,    88,    86,   145,   141,
      85
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -271,  -271,   361,  -103,  -271,  -271,  -271,  -271,  -271,  -271,
    -271,  -271,  -271,  -271,  -271,   105,  -271,  -271,   133,   182,
      90,  -271,  -271,  -271,  -270,  -101,   252,   212,  -271,  -271,
    -271,   202,  -271,   -80,  -271,    78,  -271,  -271,  -271,    -4,
     -47,   -82,  -271,   -86,   170,  -172,   215,  -271,  -141,  -211,
    -271,   161,  -271,  -271,  -271,  -271,  -271,  -271
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,   123,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,   117,    32,    33,   208,   161,
     251,   276,   206,    34,   263,    66,    96,   136,   279,    35,
      36,   156,   157,    37,   304,   316,   317,   327,    38,    67,
      68,   128,   129,    69,   150,   151,   187,   188,   154,   194,
     195,   241,   261,   285,    39,    40,    41,    81
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,    88,   118,   130,   130,   130,   130,   130,   131,   132,
     133,   134,   158,   221,   102,   197,   305,   101,   165,     4,
     248,    71,   311,    72,   126,     4,   115,    74,     4,   127,
     121,   271,   272,   140,   107,   108,   162,   254,   141,   320,
      46,   183,    47,   325,   184,    75,   223,    94,    95,   125,
     137,   138,   139,    73,   256,     4,   242,   243,   145,   146,
     147,   148,    48,   212,   105,   106,   107,   108,    76,   257,
      77,   300,   103,   302,    79,   104,   249,   250,   105,   106,
     107,   108,    54,   281,   258,   130,   116,   213,   225,   214,
     178,    58,   116,   122,    80,   245,    59,    60,   142,    62,
      63,    49,    50,    51,    52,    53,   193,   179,   326,    54,
     226,    55,    56,    57,   105,   106,   107,   108,    58,   105,
     106,   107,   108,    59,    60,    61,    62,    63,    82,    64,
      65,   216,   217,   218,   105,   106,   107,   108,   249,   250,
     182,   180,    83,    88,    42,    84,    43,   265,    85,   105,
     106,   107,   108,    86,   105,   106,   107,   108,    87,    89,
      90,   286,    91,    92,   273,    93,    54,   292,   244,    97,
      98,   105,   106,   107,   108,    58,    99,   219,   100,   110,
      59,    60,   112,    62,    63,   111,   290,   113,   293,   294,
     309,   109,   114,   119,   270,   193,   193,   120,   135,   118,
     124,    44,   144,   143,   190,   105,   106,   107,   108,   149,
      45,   310,   153,   152,   155,    54,   159,   318,     4,   160,
     163,   164,    88,   166,    58,   169,   319,   170,   172,    59,
      60,   171,    62,    63,    48,   193,   168,   193,   318,   167,
     173,   307,   174,    49,    50,    51,    52,    53,   175,   177,
     181,    54,   185,    55,    56,    57,   191,   192,   186,    88,
      58,   189,   196,   211,   269,    59,    60,    61,    62,    63,
     198,    64,    65,    49,    50,    51,    52,    53,   199,   301,
     207,    54,   209,    55,    56,    57,   210,   140,   222,   227,
      58,   220,   228,   247,   306,    59,    60,    61,    62,    63,
     253,    64,    65,    49,    50,    51,    52,    53,   255,   260,
     264,    54,   262,    55,    56,    57,   266,   268,   274,   267,
      58,   275,   278,   282,   280,    59,    60,    61,    62,    63,
     283,    64,    65,    49,    50,    51,    52,    53,   284,   287,
     289,    54,   291,    55,    56,    57,   295,   297,   296,   299,
      58,   303,   308,   312,   313,    59,    60,    61,    62,    63,
     315,    64,    65,     1,     2,   126,   321,   322,   323,   324,
       3,     4,     5,     6,     7,     8,     9,    10,   328,    78,
     329,    11,    12,    13,   298,   277,   314,   176,   215,   252,
      14,    15,   259,   200,   201,   202,   203,   204,   205,    16,
     246,    17,   330,   224,    18,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   288,     0,     0,     0,   239,
     240,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   105,   106,   107,   108
};

static const yytype_int16 yycheck[] =
{
       4,    48,    82,    89,    90,    91,    92,    93,    90,    91,
      92,    93,   113,   185,    22,   156,   286,    64,   121,    13,
      20,    83,   292,    10,    83,    13,    20,    37,    13,    88,
      20,   242,   243,    83,    88,    89,   116,   209,    88,   309,
       9,    80,    11,    14,    83,    83,   187,    81,    82,    21,
      97,    98,    99,    35,    21,    13,    39,    40,   105,   106,
     107,   108,    20,   166,    86,    87,    88,    89,    83,    21,
      44,   282,    80,   284,     0,    83,    76,    77,    86,    87,
      88,    89,    67,   255,    21,   171,    80,   167,   189,   171,
      22,    76,    80,    83,     3,   196,    81,    82,   102,    84,
      85,    59,    60,    61,    62,    63,   153,    22,    79,    67,
     190,    69,    70,    71,    86,    87,    88,    89,    76,    86,
      87,    88,    89,    81,    82,    83,    84,    85,    83,    87,
      88,   178,   179,   180,    86,    87,    88,    89,    76,    77,
     144,    22,    83,   190,     9,    11,    11,   227,    83,    86,
      87,    88,    89,    83,    86,    87,    88,    89,    83,    20,
      20,   262,    20,    20,   244,    20,    67,   268,    20,    20,
      20,    86,    87,    88,    89,    76,    20,   181,    34,    83,
      81,    82,    41,    84,    85,    83,   266,    49,   268,   269,
     291,    37,    45,    42,   241,   242,   243,    83,    22,   279,
      42,    66,    22,    83,    20,    86,    87,    88,    89,    83,
      75,   291,    38,    36,    83,    67,    84,   303,    13,    83,
      83,    42,   269,    22,    76,    34,   306,    21,    21,    81,
      82,    22,    84,    85,    20,   282,    83,   284,   324,    80,
      21,   288,    21,    59,    60,    61,    62,    63,    21,    68,
      22,    67,    22,    69,    70,    71,    72,    73,    64,   306,
      76,    20,    49,    21,    20,    81,    82,    83,    84,    85,
      22,    87,    88,    59,    60,    61,    62,    63,    35,   283,
      22,    67,    20,    69,    70,    71,    83,    83,    65,    20,
      76,    83,    72,     9,    20,    81,    82,    83,    84,    85,
      21,    87,    88,    59,    60,    61,    62,    63,    20,     7,
      21,    67,    22,    69,    70,    71,    20,    20,    83,    74,
      76,    81,    47,    42,    21,    81,    82,    83,    84,    85,
       4,    87,    88,    59,    60,    61,    62,    63,     8,    21,
      21,    67,    20,    69,    70,    71,    21,    48,    21,    21,
      76,    78,    21,    21,    21,    81,    82,    83,    84,    85,
      49,    87,    88,     5,     6,    83,    21,    21,    83,    22,
      12,    13,    14,    15,    16,    17,    18,    19,    21,    18,
      21,    23,    24,    25,   279,   252,   296,   135,   176,   207,
      32,    33,   222,    26,    27,    28,    29,    30,    31,    41,
     198,    43,   324,   188,    46,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,   264,    -1,    -1,    -1,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    87,    88,    89
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    12,    13,    14,    15,    16,    17,    18,
      19,    23,    24,    25,    32,    33,    41,    43,    46,    92,
      93,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   107,   108,   114,   120,   121,   124,   129,   145,
     146,   147,     9,    11,    66,    75,     9,    11,    20,    59,
      60,    61,    62,    63,    67,    69,    70,    71,    76,    81,
      82,    83,    84,    85,    87,    88,   116,   130,   131,   134,
     130,    83,    10,    35,    37,    83,    83,    44,    93,     0,
       3,   148,    83,    83,    11,    83,    83,    83,   131,    20,
      20,    20,    20,    20,    81,    82,   117,    20,    20,    20,
      34,   131,    22,    80,    83,    86,    87,    88,    89,    37,
      83,    83,    41,    49,    45,    20,    80,   106,   124,    42,
      83,    20,    83,    94,    42,    21,    83,    88,   132,   133,
     134,   132,   132,   132,   132,    22,   118,   131,   131,   131,
      83,    88,   130,    83,    22,   131,   131,   131,   131,    83,
     135,   136,    36,    38,   139,    83,   122,   123,   116,    84,
      83,   110,   124,    83,    42,    94,    22,    80,    83,    34,
      21,    22,    21,    21,    21,    21,   117,    68,    22,    22,
      22,    22,   130,    80,    83,    22,    64,   137,   138,    20,
      20,    72,    73,   131,   140,   141,    49,   139,    22,    35,
      26,    27,    28,    29,    30,    31,   113,    22,   109,    20,
      83,    21,    94,   124,   132,   118,   131,   131,   131,   130,
      83,   136,    65,   139,   137,   116,   124,    20,    72,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    73,
      74,   142,    39,    40,    20,   116,   122,     9,    20,    76,
      77,   111,   110,    21,   136,    20,    21,    21,    21,   135,
       7,   143,    22,   115,    21,   124,    20,    74,    20,    20,
     131,   140,   140,   124,    83,    81,   112,   109,    47,   119,
      21,   136,    42,     4,     8,   144,   116,    21,   142,    21,
     124,    20,   116,   124,   124,    21,    21,    48,   106,    21,
     140,   130,   140,    78,   125,   115,    20,   131,    21,   116,
     124,   115,    21,    21,   111,    49,   126,   127,   134,   124,
     115,    21,    21,    83,    22,    14,    79,   128,    21,    21,
     126
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    91,    92,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    94,    94,    94,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   104,   105,
     106,   106,   106,   107,   107,   108,   109,   109,   110,   110,
     111,   111,   111,   112,   113,   113,   113,   113,   113,   113,
     114,   115,   115,   116,   116,   116,   116,   116,   116,   117,
     117,   118,   118,   119,   119,   120,   121,   122,   122,   123,
     123,   124,   125,   125,   126,   126,   127,   128,   128,   128,
     129,   130,   130,   130,   130,   130,   130,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   132,   132,   133,   133,   133,
     134,   134,   135,   135,   135,   136,   136,   137,   137,   138,
     139,   139,   140,   140,   140,   140,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   143,   143,   144,   144,
     145,   146,   147,   148,   148
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     3,     2,     2,     8,     9,     5,
       0,     2,     1,     9,     4,     6,     0,     3,     6,     3,
       1,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       8,     0,     3,     1,     1,     1,     1,     4,     1,     1,
       1,     0,     3,     0,     4,     4,     5,     1,     3,     3,
       5,     9,     0,     2,     1,     3,     2,     0,     1,     1,
       2,     1,     2,     3,     3,     4,     5,     3,     3,     3,
       3,     3,     6,     6,     6,     2,     1,     1,     1,     3,
       4,     4,     4,     4,     4,     1,     3,     0,     1,     1,
       1,     3,     1,     2,     3,     1,     3,     0,     2,     5,
       0,     2,     0,     1,     3,     3,     3,     5,     5,     6,
       6,     7,     4,     5,     5,     7,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     3,     0,     2,
       7,     2,     4,     0,     1
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
        yyerror (&yylloc, sql_string, sql_result, scanner, flag, YY_("syntax error: cannot back up")); \
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
                  Kind, Value, Location, sql_string, sql_result, scanner, flag); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner, SqlCommandFlag flag)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  YY_USE (flag);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner, SqlCommandFlag flag)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner, flag);
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
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner, SqlCommandFlag flag)
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
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner, flag);
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner, SqlCommandFlag flag)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  YY_USE (flag);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner, SqlCommandFlag flag)
{
/* Lookahead token kind.  */
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
    int yynerrs = 0;

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
      yychar = yylex (&yylval, &yylloc, scanner);
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
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 272 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1947 "yacc_sql.cpp"
    break;

  case 24: /* id_list: %empty  */
#line 303 "yacc_sql.y"
  {
    (yyval.id_list) = nullptr;
  }
#line 1955 "yacc_sql.cpp"
    break;

  case 25: /* id_list: ID  */
#line 306 "yacc_sql.y"
       {
    (yyval.id_list) = new std::vector<std::string>;
    (yyval.id_list)->emplace_back((yyvsp[0].string));
    free((yyvsp[0].string));
  }
#line 1965 "yacc_sql.cpp"
    break;

  case 26: /* id_list: ID COMMA id_list  */
#line 311 "yacc_sql.y"
                     {
    if ((yyvsp[0].id_list) != nullptr) {
      (yyval.id_list) = (yyvsp[0].id_list);
    } else {
      (yyval.id_list) = new std::vector<std::string>;
    }
    (yyval.id_list)->emplace((yyval.id_list)->begin(), (yyvsp[-2].string));
    free((yyvsp[-2].string));
  }
#line 1979 "yacc_sql.cpp"
    break;

  case 27: /* id_list: LBRACE id_list RBRACE  */
#line 320 "yacc_sql.y"
                          {
    (yyval.id_list) = (yyvsp[-1].id_list);
  }
#line 1987 "yacc_sql.cpp"
    break;

  case 28: /* exit_stmt: EXIT  */
#line 326 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1996 "yacc_sql.cpp"
    break;

  case 29: /* help_stmt: HELP  */
#line 332 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 2004 "yacc_sql.cpp"
    break;

  case 30: /* sync_stmt: SYNC  */
#line 337 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 2012 "yacc_sql.cpp"
    break;

  case 31: /* begin_stmt: TRX_BEGIN  */
#line 343 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 2020 "yacc_sql.cpp"
    break;

  case 32: /* commit_stmt: TRX_COMMIT  */
#line 349 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 2028 "yacc_sql.cpp"
    break;

  case 33: /* rollback_stmt: TRX_ROLLBACK  */
#line 355 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2036 "yacc_sql.cpp"
    break;

  case 34: /* drop_table_stmt: DROP TABLE ID  */
#line 361 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2046 "yacc_sql.cpp"
    break;

  case 35: /* show_tables_stmt: SHOW TABLES  */
#line 368 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2054 "yacc_sql.cpp"
    break;

  case 36: /* desc_table_stmt: DESC ID  */
#line 374 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2064 "yacc_sql.cpp"
    break;

  case 37: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE rel_list RBRACE  */
#line 383 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      create_index.unique = false;

      if ((yyvsp[-1].relation_list) != nullptr) {
        std::vector<std::string> attributes;
        for (auto &rel : *(yyvsp[-1].relation_list)) {
          attributes.emplace_back(rel.name);
        }
        create_index.attributes.swap(attributes);
        delete (yyvsp[-1].relation_list);
      }
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 2087 "yacc_sql.cpp"
    break;

  case 38: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE rel_list RBRACE  */
#line 402 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-5].string);
      create_index.relation_name = (yyvsp[-3].string);
      create_index.unique = true;
      if ((yyvsp[-1].relation_list) != nullptr) {        
        std::vector<std::string> attributes;
        for (auto &rel : *(yyvsp[-1].relation_list)) {
          attributes.emplace_back(rel.name);
        }
        create_index.attributes.swap(attributes);
        delete (yyvsp[-1].relation_list);
      }
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 2109 "yacc_sql.cpp"
    break;

  case 39: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 423 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2121 "yacc_sql.cpp"
    break;

  case 40: /* as_select: %empty  */
#line 433 "yacc_sql.y"
  {
    (yyval.sql_node) = nullptr;
  }
#line 2129 "yacc_sql.cpp"
    break;

  case 41: /* as_select: AS select_stmt  */
#line 436 "yacc_sql.y"
                   {
    (yyval.sql_node) = (yyvsp[0].sql_node);
  }
#line 2137 "yacc_sql.cpp"
    break;

  case 42: /* as_select: select_stmt  */
#line 439 "yacc_sql.y"
                {
    (yyval.sql_node) = (yyvsp[0].sql_node);
  }
#line 2145 "yacc_sql.cpp"
    break;

  case 43: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format as_select  */
#line 445 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-6].string);
      free((yyvsp[-6].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-3].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-4].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-4].attr_info);
      if ((yyvsp[-1].string) != nullptr) {
        create_table.storage_format = (yyvsp[-1].string);
        free((yyvsp[-1].string));
      }

      if ((yyvsp[0].sql_node) != nullptr) {
        create_table.has_subquery = true;
        create_table.subquery = (yyvsp[0].sql_node);
      } else {
        create_table.has_subquery = false;
        create_table.subquery = nullptr;
      }
    }
#line 2178 "yacc_sql.cpp"
    break;

  case 44: /* create_table_stmt: CREATE TABLE ID as_select  */
#line 473 "yacc_sql.y"
                                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-1].string);
      free((yyvsp[-1].string));
      if ((yyvsp[0].sql_node) != nullptr) {
        create_table.has_subquery = true;
        create_table.subquery = (yyvsp[0].sql_node);
      } else {
        create_table.has_subquery = false;
        create_table.subquery = nullptr;
      }
    }
#line 2196 "yacc_sql.cpp"
    break;

  case 45: /* create_view_stmt: CREATE VIEW ID id_list AS select_stmt  */
#line 488 "yacc_sql.y"
                                        {
    (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VIEW);
    (yyval.sql_node)->create_view.view_name = (yyvsp[-3].string);
    free((yyvsp[-3].string));
    if ((yyvsp[-2].id_list) != nullptr) {
      (yyval.sql_node)->create_view.col_names.swap(*(yyvsp[-2].id_list));
      delete (yyvsp[-2].id_list);
    }
    (yyval.sql_node)->create_view.selection = (yyvsp[0].sql_node);
    (yyval.sql_node)->create_view.sql_str = (yyvsp[0].sql_node)->sql_str;
  }
#line 2212 "yacc_sql.cpp"
    break;

  case 46: /* attr_def_list: %empty  */
#line 502 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2220 "yacc_sql.cpp"
    break;

  case 47: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 506 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2234 "yacc_sql.cpp"
    break;

  case 48: /* attr_def: ID type LBRACE number RBRACE nullable_spec  */
#line 519 "yacc_sql.y"
  {
    (yyval.attr_info) = new AttrInfoSqlNode;
    (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
    (yyval.attr_info)->name = (yyvsp[-5].string);
    (yyval.attr_info)->length = (yyvsp[-2].number);
    (yyval.attr_info)->nullable = (yyvsp[0].nullable_spec);
    free((yyvsp[-5].string));
  }
#line 2247 "yacc_sql.cpp"
    break;

  case 49: /* attr_def: ID type nullable_spec  */
#line 528 "yacc_sql.y"
  {
    (yyval.attr_info) = new AttrInfoSqlNode;
    (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
    (yyval.attr_info)->name = (yyvsp[-2].string);
    if ((AttrType)(yyvsp[-1].number) == AttrType::DATES) {
      (yyval.attr_info)->length = 8;
    } else if ((AttrType)(yyvsp[-1].number) == AttrType::CHARS) {
    (yyval.attr_info)->length = 32;
      } else if ((AttrType)(yyvsp[-1].number) == AttrType::TEXTS) {
        (yyval.attr_info)->length = LOB_OVERFLOW_THRESHOLD;
    } else {
      (yyval.attr_info)->length = 4;
    }
    (yyval.attr_info)->nullable = (yyvsp[0].nullable_spec);
    free((yyvsp[-2].string));
  }
#line 2268 "yacc_sql.cpp"
    break;

  case 50: /* nullable_spec: NULL_T  */
#line 547 "yacc_sql.y"
         { (yyval.nullable_spec) = true; }
#line 2274 "yacc_sql.cpp"
    break;

  case 51: /* nullable_spec: NOT_NULL_T  */
#line 548 "yacc_sql.y"
               { (yyval.nullable_spec) = false; }
#line 2280 "yacc_sql.cpp"
    break;

  case 52: /* nullable_spec: %empty  */
#line 549 "yacc_sql.y"
                { (yyval.nullable_spec) = true; }
#line 2286 "yacc_sql.cpp"
    break;

  case 53: /* number: NUMBER  */
#line 553 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2292 "yacc_sql.cpp"
    break;

  case 54: /* type: INT_T  */
#line 556 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2298 "yacc_sql.cpp"
    break;

  case 55: /* type: STRING_T  */
#line 557 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2304 "yacc_sql.cpp"
    break;

  case 56: /* type: FLOAT_T  */
#line 558 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2310 "yacc_sql.cpp"
    break;

  case 57: /* type: VECTOR_T  */
#line 559 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2316 "yacc_sql.cpp"
    break;

  case 58: /* type: DATE_T  */
#line 560 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2322 "yacc_sql.cpp"
    break;

  case 59: /* type: TEXT_T  */
#line 561 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2328 "yacc_sql.cpp"
    break;

  case 60: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 565 "yacc_sql.y"
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
#line 2345 "yacc_sql.cpp"
    break;

  case 61: /* value_list: %empty  */
#line 581 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2353 "yacc_sql.cpp"
    break;

  case 62: /* value_list: COMMA value value_list  */
#line 584 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2367 "yacc_sql.cpp"
    break;

  case 63: /* value: NUMBER  */
#line 595 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2376 "yacc_sql.cpp"
    break;

  case 64: /* value: FLOAT  */
#line 599 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2385 "yacc_sql.cpp"
    break;

  case 65: /* value: SSS  */
#line 603 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2396 "yacc_sql.cpp"
    break;

  case 66: /* value: DATE  */
#line 609 "yacc_sql.y"
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
#line 2413 "yacc_sql.cpp"
    break;

  case 67: /* value: LBRACKET vector_elem vector_value_list RBRACKET  */
#line 621 "yacc_sql.y"
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
#line 2428 "yacc_sql.cpp"
    break;

  case 68: /* value: NULL_T  */
#line 631 "yacc_sql.y"
             {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2437 "yacc_sql.cpp"
    break;

  case 69: /* vector_elem: NUMBER  */
#line 637 "yacc_sql.y"
           {
      (yyval.floats) = (float)(yyvsp[0].number);
      (yyloc) = (yylsp[0]);
    }
#line 2446 "yacc_sql.cpp"
    break;

  case 70: /* vector_elem: FLOAT  */
#line 641 "yacc_sql.y"
           {
      (yyval.floats) = (float)(yyvsp[0].floats);
      (yyloc) = (yylsp[0]);
    }
#line 2455 "yacc_sql.cpp"
    break;

  case 71: /* vector_value_list: %empty  */
#line 648 "yacc_sql.y"
    {
      (yyval.vector_elem_list) = nullptr;
    }
#line 2463 "yacc_sql.cpp"
    break;

  case 72: /* vector_value_list: COMMA vector_elem vector_value_list  */
#line 651 "yacc_sql.y"
                                         {
      (yyval.vector_elem_list) = (yyvsp[0].vector_elem_list);
      if((yyval.vector_elem_list) == nullptr){
        (yyval.vector_elem_list) = new vector<float>;
      }
      (yyval.vector_elem_list)->push_back((yyvsp[-1].floats));
    }
#line 2475 "yacc_sql.cpp"
    break;

  case 73: /* storage_format: %empty  */
#line 660 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2483 "yacc_sql.cpp"
    break;

  case 74: /* storage_format: STORAGE FORMAT EQ ID  */
#line 664 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2491 "yacc_sql.cpp"
    break;

  case 75: /* delete_stmt: DELETE FROM ID where  */
#line 671 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2505 "yacc_sql.cpp"
    break;

  case 76: /* update_stmt: UPDATE ID SET set_clause_list where  */
#line 683 "yacc_sql.y"
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
#line 2523 "yacc_sql.cpp"
    break;

  case 77: /* set_clause_list: set_clause  */
#line 699 "yacc_sql.y"
             {
    (yyval.set_clause_list) = new std::vector<SetClauseSqlNode>;
    (yyval.set_clause_list)->emplace_back(*(yyvsp[0].set_clause));
    delete (yyvsp[0].set_clause);
  }
#line 2533 "yacc_sql.cpp"
    break;

  case 78: /* set_clause_list: set_clause COMMA set_clause_list  */
#line 705 "yacc_sql.y"
  {
    if ((yyvsp[0].set_clause_list) != nullptr) {
      (yyval.set_clause_list) = (yyvsp[0].set_clause_list);
    } else {
      (yyval.set_clause_list) = new std::vector<SetClauseSqlNode>;
    }
    (yyval.set_clause_list)->emplace((yyval.set_clause_list)->begin(), *(yyvsp[-2].set_clause));
    delete (yyvsp[-2].set_clause);
  }
#line 2547 "yacc_sql.cpp"
    break;

  case 79: /* set_clause: ID EQ value  */
#line 717 "yacc_sql.y"
              {
    (yyval.set_clause) = new SetClauseSqlNode;
    (yyval.set_clause)->attribute_name = (yyvsp[-2].string);
    (yyval.set_clause)->value = *(yyvsp[0].value);
    (yyval.set_clause)->has_subquery = false;
    (yyval.set_clause)->subquery = nullptr;
    free((yyvsp[-2].string));
    delete (yyvsp[0].value);
  }
#line 2561 "yacc_sql.cpp"
    break;

  case 80: /* set_clause: ID EQ LBRACE select_stmt RBRACE  */
#line 726 "yacc_sql.y"
                                    {
    (yyval.set_clause) = new SetClauseSqlNode;
    (yyval.set_clause)->attribute_name = (yyvsp[-4].string);
    (yyval.set_clause)->has_subquery = true;
    (yyval.set_clause)->subquery = (yyvsp[-1].sql_node);
    free((yyvsp[-4].string));
  }
#line 2573 "yacc_sql.cpp"
    break;

  case 81: /* select_stmt: SELECT expression_list FROM rel_list join_list where group_by having order_by  */
#line 736 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      (yyval.sql_node)->sql_str = token_name(sql_string, &(yyloc));
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
        ConditionSqlNode last = (yyvsp[-3].condition_list)->back();
        if (last.flag) {
          (yyvsp[-3].condition_list)->pop_back();
          (yyval.sql_node)->selection.is_and = 0;
        }
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
#line 2627 "yacc_sql.cpp"
    break;

  case 82: /* order_by: %empty  */
#line 789 "yacc_sql.y"
        {
		(yyval.order_by_list) = nullptr;
	}
#line 2635 "yacc_sql.cpp"
    break;

  case 83: /* order_by: ORDER_BY order_by_list  */
#line 793 "yacc_sql.y"
        {
		(yyval.order_by_list) = (yyvsp[0].order_by_list);
	}
#line 2643 "yacc_sql.cpp"
    break;

  case 84: /* order_by_list: order_by_item  */
#line 800 "yacc_sql.y"
        {
		(yyval.order_by_list) = new std::vector<OrderByItem>;
		(yyval.order_by_list)->emplace_back(*(yyvsp[0].order_by_item));
		delete (yyvsp[0].order_by_item);
	}
#line 2653 "yacc_sql.cpp"
    break;

  case 85: /* order_by_list: order_by_item COMMA order_by_list  */
#line 806 "yacc_sql.y"
        {
		if ((yyvsp[0].order_by_list) != nullptr) {
			(yyval.order_by_list) = (yyvsp[0].order_by_list);
		} else {
			(yyval.order_by_list) = new std::vector<OrderByItem>;
		}
		(yyval.order_by_list)->emplace((yyval.order_by_list)->begin(), *(yyvsp[-2].order_by_item));
		delete (yyvsp[-2].order_by_item);
	}
#line 2667 "yacc_sql.cpp"
    break;

  case 86: /* order_by_item: rel_attr asc_desc  */
#line 819 "yacc_sql.y"
        {
		(yyval.order_by_item) = new OrderByItem;
		(yyval.order_by_item)->attr = *(yyvsp[-1].rel_attr);
		(yyval.order_by_item)->asc = (yyvsp[0].asc_desc);
		delete (yyvsp[-1].rel_attr);
	}
#line 2678 "yacc_sql.cpp"
    break;

  case 87: /* asc_desc: %empty  */
#line 829 "yacc_sql.y"
        {
		(yyval.asc_desc) = true; // default is ascending
	}
#line 2686 "yacc_sql.cpp"
    break;

  case 88: /* asc_desc: ASC  */
#line 833 "yacc_sql.y"
        {
		(yyval.asc_desc) = true;
	}
#line 2694 "yacc_sql.cpp"
    break;

  case 89: /* asc_desc: DESC  */
#line 837 "yacc_sql.y"
        {
		(yyval.asc_desc) = false;
	}
#line 2702 "yacc_sql.cpp"
    break;

  case 90: /* calc_stmt: CALC expression_list  */
#line 844 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2712 "yacc_sql.cpp"
    break;

  case 91: /* expression_list: expression  */
#line 853 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2721 "yacc_sql.cpp"
    break;

  case 92: /* expression_list: expression ID  */
#line 857 "yacc_sql.y"
                    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
      (yyval.expression_list)->back()->set_name((yyvsp[0].string));
      (yyval.expression_list)->back()->set_aliased(true);
      free((yyvsp[0].string));
    }
#line 2733 "yacc_sql.cpp"
    break;

  case 93: /* expression_list: expression AS ID  */
#line 864 "yacc_sql.y"
                       {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
      (yyval.expression_list)->back()->set_name((yyvsp[0].string));
      (yyval.expression_list)->back()->set_aliased(true);
      free((yyvsp[0].string));
    }
#line 2745 "yacc_sql.cpp"
    break;

  case 94: /* expression_list: expression COMMA expression_list  */
#line 872 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2758 "yacc_sql.cpp"
    break;

  case 95: /* expression_list: expression ID COMMA expression_list  */
#line 881 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-3].expression));
      (yyval.expression_list)->front()->set_name((yyvsp[-2].string));
      (yyval.expression_list)->front()->set_aliased(true);
      free((yyvsp[-2].string));
    }
#line 2774 "yacc_sql.cpp"
    break;

  case 96: /* expression_list: expression AS ID COMMA expression_list  */
#line 893 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-4].expression));
      (yyval.expression_list)->front()->set_name((yyvsp[-2].string));
      (yyval.expression_list)->front()->set_aliased(true);
      free((yyvsp[-2].string));
    }
#line 2790 "yacc_sql.cpp"
    break;

  case 97: /* expression: expression '+' expression  */
#line 906 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2798 "yacc_sql.cpp"
    break;

  case 98: /* expression: expression '-' expression  */
#line 909 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2806 "yacc_sql.cpp"
    break;

  case 99: /* expression: expression '*' expression  */
#line 912 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2814 "yacc_sql.cpp"
    break;

  case 100: /* expression: expression '/' expression  */
#line 915 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2822 "yacc_sql.cpp"
    break;

  case 101: /* expression: LBRACE expression RBRACE  */
#line 918 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2831 "yacc_sql.cpp"
    break;

  case 102: /* expression: L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 922 "yacc_sql.y"
                                                            {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::L2_DIS, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2839 "yacc_sql.cpp"
    break;

  case 103: /* expression: COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 925 "yacc_sql.y"
                                                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::COS_DIS, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2847 "yacc_sql.cpp"
    break;

  case 104: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 928 "yacc_sql.y"
                                                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::INN_PDT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2855 "yacc_sql.cpp"
    break;

  case 105: /* expression: '-' expression  */
#line 931 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2863 "yacc_sql.cpp"
    break;

  case 106: /* expression: value  */
#line 934 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2873 "yacc_sql.cpp"
    break;

  case 107: /* expression: rel_attr  */
#line 939 "yacc_sql.y"
               {
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2884 "yacc_sql.cpp"
    break;

  case 108: /* expression: '*'  */
#line 945 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2892 "yacc_sql.cpp"
    break;

  case 109: /* expression: ID DOT '*'  */
#line 948 "yacc_sql.y"
                 {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
    }
#line 2900 "yacc_sql.cpp"
    break;

  case 110: /* expression: MAX LBRACE agg_fun_attr_list RBRACE  */
#line 953 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("max", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2908 "yacc_sql.cpp"
    break;

  case 111: /* expression: MIN LBRACE agg_fun_attr_list RBRACE  */
#line 956 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("min", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2916 "yacc_sql.cpp"
    break;

  case 112: /* expression: COUNT LBRACE agg_fun_attr_list RBRACE  */
#line 959 "yacc_sql.y"
                                            {
      (yyval.expression) = create_aggregate_expression("count", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2924 "yacc_sql.cpp"
    break;

  case 113: /* expression: AVG LBRACE agg_fun_attr_list RBRACE  */
#line 962 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("avg", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2932 "yacc_sql.cpp"
    break;

  case 114: /* expression: SUM LBRACE agg_fun_attr_list RBRACE  */
#line 965 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression("sum", (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2940 "yacc_sql.cpp"
    break;

  case 115: /* agg_fun_attr_list: agg_fun_attr  */
#line 984 "yacc_sql.y"
                 {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2948 "yacc_sql.cpp"
    break;

  case 116: /* agg_fun_attr_list: agg_fun_attr COMMA agg_fun_attr_list  */
#line 987 "yacc_sql.y"
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
#line 2964 "yacc_sql.cpp"
    break;

  case 117: /* agg_fun_attr: %empty  */
#line 1001 "yacc_sql.y"
    {
      std::string null_string = "";
      (yyval.expression) = new UnboundFieldExpr(null_string, null_string);
      (yyval.expression)->set_name(null_string);
    }
#line 2974 "yacc_sql.cpp"
    break;

  case 118: /* agg_fun_attr: '*'  */
#line 1006 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2982 "yacc_sql.cpp"
    break;

  case 119: /* agg_fun_attr: rel_attr  */
#line 1009 "yacc_sql.y"
               {
      (yyval.expression) = new UnboundFieldExpr((yyvsp[0].rel_attr)->relation_name, (yyvsp[0].rel_attr)->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2992 "yacc_sql.cpp"
    break;

  case 120: /* rel_attr: ID  */
#line 1017 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3002 "yacc_sql.cpp"
    break;

  case 121: /* rel_attr: ID DOT ID  */
#line 1022 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3014 "yacc_sql.cpp"
    break;

  case 122: /* relation: ID  */
#line 1032 "yacc_sql.y"
       {
      (yyval.relation) = new RelationSqlNode();
      (yyval.relation)->name = (yyvsp[0].string);
      (yyval.relation)->alias = "";
      free((yyvsp[0].string));
    }
#line 3025 "yacc_sql.cpp"
    break;

  case 123: /* relation: ID ID  */
#line 1038 "yacc_sql.y"
            {
      (yyval.relation) = new RelationSqlNode();
      (yyval.relation)->name = (yyvsp[-1].string);
      (yyval.relation)->alias = (yyvsp[0].string);
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3037 "yacc_sql.cpp"
    break;

  case 124: /* relation: ID AS ID  */
#line 1045 "yacc_sql.y"
               {
      (yyval.relation) = new RelationSqlNode();
      (yyval.relation)->name = (yyvsp[-2].string);
      (yyval.relation)->alias = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3049 "yacc_sql.cpp"
    break;

  case 125: /* rel_list: relation  */
#line 1054 "yacc_sql.y"
             {
      (yyval.relation_list) = new std::vector<RelationSqlNode>();
      (yyval.relation_list)->push_back(*(yyvsp[0].relation));
      delete((yyvsp[0].relation));
    }
#line 3059 "yacc_sql.cpp"
    break;

  case 126: /* rel_list: relation COMMA rel_list  */
#line 1059 "yacc_sql.y"
                              {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<RelationSqlNode>;
      }

      (yyval.relation_list)->insert((yyval.relation_list)->begin(), *(yyvsp[-2].relation));
      delete((yyvsp[-2].relation));
    }
#line 3074 "yacc_sql.cpp"
    break;

  case 127: /* join_list: %empty  */
#line 1073 "yacc_sql.y"
    {
      (yyval.join_tuple_list) = nullptr;
    }
#line 3082 "yacc_sql.cpp"
    break;

  case 128: /* join_list: join join_list  */
#line 1076 "yacc_sql.y"
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
#line 3101 "yacc_sql.cpp"
    break;

  case 129: /* join: INNER JOIN relation ON condition_list  */
#line 1092 "yacc_sql.y"
                                          {
      (yyval.join_tuple) = new std::tuple<std::string, std::vector<ConditionSqlNode> *>((yyvsp[-2].relation)->name, (yyvsp[0].condition_list));
      delete (yyvsp[-2].relation);
    }
#line 3110 "yacc_sql.cpp"
    break;

  case 130: /* where: %empty  */
#line 1099 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3118 "yacc_sql.cpp"
    break;

  case 131: /* where: WHERE condition_list  */
#line 1102 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3126 "yacc_sql.cpp"
    break;

  case 132: /* condition_list: %empty  */
#line 1108 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3134 "yacc_sql.cpp"
    break;

  case 133: /* condition_list: condition  */
#line 1111 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3144 "yacc_sql.cpp"
    break;

  case 134: /* condition_list: condition AND condition_list  */
#line 1116 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3154 "yacc_sql.cpp"
    break;

  case 135: /* condition_list: condition OR condition_list  */
#line 1121 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      ConditionSqlNode *tmp = new ConditionSqlNode;
      tmp->flag = 1;
      (yyval.condition_list)->emplace_back(*tmp);
      delete (yyvsp[-2].condition);
      delete tmp;
    }
#line 3168 "yacc_sql.cpp"
    break;

  case 136: /* condition: expression comp_op expression  */
#line 1182 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->left_expr = (yyvsp[-2].expression);
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3180 "yacc_sql.cpp"
    break;

  case 137: /* condition: expression comp_op LBRACE select_stmt RBRACE  */
#line 1189 "yacc_sql.y"
                                                   {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-4].expression);
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 3194 "yacc_sql.cpp"
    break;

  case 138: /* condition: expression IN_T LBRACE select_stmt RBRACE  */
#line 1198 "yacc_sql.y"
                                                {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-4].expression);
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = CompOp::IN;
    }
#line 3208 "yacc_sql.cpp"
    break;

  case 139: /* condition: expression NOT IN_T LBRACE select_stmt RBRACE  */
#line 1207 "yacc_sql.y"
                                                    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = (yyvsp[-5].expression);
      UnboundSubqueryExpr *right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->right_expr = right_expr;
      (yyval.condition)->comp = CompOp::NOT_IN;
    }
#line 3222 "yacc_sql.cpp"
    break;

  case 140: /* condition: expression IN_T LBRACE value value_list RBRACE  */
#line 1217 "yacc_sql.y"
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
#line 3243 "yacc_sql.cpp"
    break;

  case 141: /* condition: expression NOT IN_T LBRACE value value_list RBRACE  */
#line 1233 "yacc_sql.y"
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
#line 3264 "yacc_sql.cpp"
    break;

  case 142: /* condition: EXISTS_T LBRACE select_stmt RBRACE  */
#line 1249 "yacc_sql.y"
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
#line 3279 "yacc_sql.cpp"
    break;

  case 143: /* condition: NOT EXISTS_T LBRACE select_stmt RBRACE  */
#line 1259 "yacc_sql.y"
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
#line 3294 "yacc_sql.cpp"
    break;

  case 144: /* condition: LBRACE select_stmt RBRACE comp_op expression  */
#line 1269 "yacc_sql.y"
                                                   {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      UnboundSubqueryExpr *left_expr = new UnboundSubqueryExpr((yyvsp[-3].sql_node));
      (yyval.condition)->left_expr = left_expr;
      (yyval.condition)->right_expr = (yyvsp[0].expression);
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3308 "yacc_sql.cpp"
    break;

  case 145: /* condition: LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE  */
#line 1278 "yacc_sql.y"
                                                                  {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->neither = 1;
      (yyval.condition)->is_subquery = 1;
      (yyval.condition)->left_expr = new UnboundSubqueryExpr((yyvsp[-5].sql_node));
      (yyval.condition)->right_expr = new UnboundSubqueryExpr((yyvsp[-1].sql_node));
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 3321 "yacc_sql.cpp"
    break;

  case 146: /* comp_op: EQ  */
#line 1289 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3327 "yacc_sql.cpp"
    break;

  case 147: /* comp_op: LT  */
#line 1290 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3333 "yacc_sql.cpp"
    break;

  case 148: /* comp_op: GT  */
#line 1291 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3339 "yacc_sql.cpp"
    break;

  case 149: /* comp_op: LE  */
#line 1292 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3345 "yacc_sql.cpp"
    break;

  case 150: /* comp_op: GE  */
#line 1293 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3351 "yacc_sql.cpp"
    break;

  case 151: /* comp_op: NE  */
#line 1294 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3357 "yacc_sql.cpp"
    break;

  case 152: /* comp_op: LK  */
#line 1295 "yacc_sql.y"
         { (yyval.comp) = LIKE; }
#line 3363 "yacc_sql.cpp"
    break;

  case 153: /* comp_op: NLK  */
#line 1296 "yacc_sql.y"
          {(yyval.comp) = NOT_LIKE; }
#line 3369 "yacc_sql.cpp"
    break;

  case 154: /* comp_op: IS_T  */
#line 1297 "yacc_sql.y"
           { (yyval.comp) = IS; }
#line 3375 "yacc_sql.cpp"
    break;

  case 155: /* comp_op: IS_NOT_T  */
#line 1298 "yacc_sql.y"
               { (yyval.comp) = IS_NOT; }
#line 3381 "yacc_sql.cpp"
    break;

  case 156: /* group_by: %empty  */
#line 1304 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3389 "yacc_sql.cpp"
    break;

  case 157: /* group_by: GROUP BY expression_list  */
#line 1309 "yacc_sql.y"
    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3397 "yacc_sql.cpp"
    break;

  case 158: /* having: %empty  */
#line 1316 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3405 "yacc_sql.cpp"
    break;

  case 159: /* having: HAVING condition_list  */
#line 1319 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3413 "yacc_sql.cpp"
    break;

  case 160: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1325 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3427 "yacc_sql.cpp"
    break;

  case 161: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1338 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3436 "yacc_sql.cpp"
    break;

  case 162: /* set_variable_stmt: SET ID EQ value  */
#line 1346 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3448 "yacc_sql.cpp"
    break;


#line 3452 "yacc_sql.cpp"

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
        yyerror (&yylloc, sql_string, sql_result, scanner, flag, yymsgp);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner, flag);
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
  yyerror (&yylloc, sql_string, sql_result, scanner, flag, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner, flag);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner, flag);
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

#line 1358 "yacc_sql.y"

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
