/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    BY = 259,                      /* BY  */
    CREATE = 260,                  /* CREATE  */
    DROP = 261,                    /* DROP  */
    GROUP = 262,                   /* GROUP  */
    HAVING = 263,                  /* HAVING  */
    TABLE = 264,                   /* TABLE  */
    TABLES = 265,                  /* TABLES  */
    INDEX = 266,                   /* INDEX  */
    CALC = 267,                    /* CALC  */
    SELECT = 268,                  /* SELECT  */
    DESC = 269,                    /* DESC  */
    SHOW = 270,                    /* SHOW  */
    SYNC = 271,                    /* SYNC  */
    INSERT = 272,                  /* INSERT  */
    DELETE = 273,                  /* DELETE  */
    UPDATE = 274,                  /* UPDATE  */
    LBRACE = 275,                  /* LBRACE  */
    RBRACE = 276,                  /* RBRACE  */
    COMMA = 277,                   /* COMMA  */
    TRX_BEGIN = 278,               /* TRX_BEGIN  */
    TRX_COMMIT = 279,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 280,            /* TRX_ROLLBACK  */
    INT_T = 281,                   /* INT_T  */
    STRING_T = 282,                /* STRING_T  */
    FLOAT_T = 283,                 /* FLOAT_T  */
    VECTOR_T = 284,                /* VECTOR_T  */
    DATE_T = 285,                  /* DATE_T  */
    HELP = 286,                    /* HELP  */
    EXIT = 287,                    /* EXIT  */
    DOT = 288,                     /* DOT  */
    INTO = 289,                    /* INTO  */
    VALUES = 290,                  /* VALUES  */
    FROM = 291,                    /* FROM  */
    WHERE = 292,                   /* WHERE  */
    AND = 293,                     /* AND  */
    SET = 294,                     /* SET  */
    ON = 295,                      /* ON  */
    LOAD = 296,                    /* LOAD  */
    DATA = 297,                    /* DATA  */
    INFILE = 298,                  /* INFILE  */
    EXPLAIN = 299,                 /* EXPLAIN  */
    STORAGE = 300,                 /* STORAGE  */
    FORMAT = 301,                  /* FORMAT  */
    EQ = 302,                      /* EQ  */
    LT = 303,                      /* LT  */
    GT = 304,                      /* GT  */
    LE = 305,                      /* LE  */
    GE = 306,                      /* GE  */
    NE = 307,                      /* NE  */
    LK = 308,                      /* LK  */
    NLK = 309,                     /* NLK  */
    IS_T = 310,                    /* IS_T  */
    IS_NOT_T = 311,                /* IS_NOT_T  */
    MAX = 312,                     /* MAX  */
    MIN = 313,                     /* MIN  */
    COUNT = 314,                   /* COUNT  */
    AVG = 315,                     /* AVG  */
    SUM = 316,                     /* SUM  */
    INNER = 317,                   /* INNER  */
    JOIN = 318,                    /* JOIN  */
    UNIQUE = 319,                  /* UNIQUE  */
    LBRACKET = 320,                /* LBRACKET  */
    RBRACKET = 321,                /* RBRACKET  */
    L2_DISTANCE = 322,             /* L2_DISTANCE  */
    COSINE_DISTANCE = 323,         /* COSINE_DISTANCE  */
    INNER_PRODUCT = 324,           /* INNER_PRODUCT  */
    NULL_T = 325,                  /* NULL_T  */
    NOT_NULL_T = 326,              /* NOT_NULL_T  */
    ORDER_BY = 327,                /* ORDER_BY  */
    ASC = 328,                     /* ASC  */
    NUMBER = 329,                  /* NUMBER  */
    FLOAT = 330,                   /* FLOAT  */
    ID = 331,                      /* ID  */
    SSS = 332,                     /* SSS  */
    DATE = 333,                    /* DATE  */
    UMINUS = 334                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 157 "yacc_sql.y"

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

#line 173 "yacc_sql.hpp"

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
