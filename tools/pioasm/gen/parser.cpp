// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "parser.hpp"


// Unqualified %code blocks.

    #include "pio_assembler.h"
  #ifdef _MSC_VER
  #pragma warning(disable : 4244) // possible loss of data (valid warning, but there is a software check / missing cast)
  #endif



#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
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
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  parser::parser (pio_assembler& pioasm_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      pioasm (pioasm_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 92: // if_full
      case 93: // if_empty
      case 94: // blocking
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 83: // condition
        value.YY_MOVE_OR_COPY< enum condition > (YY_MOVE (that.value));
        break;

      case 86: // in_source
      case 87: // out_target
      case 91: // set_target
        value.YY_MOVE_OR_COPY< enum in_out_set > (YY_MOVE (that.value));
        break;

      case 95: // irq_modifiers
        value.YY_MOVE_OR_COPY< enum irq > (YY_MOVE (that.value));
        break;

      case 88: // mov_target
      case 89: // mov_source
        value.YY_MOVE_OR_COPY< enum mov > (YY_MOVE (that.value));
        break;

      case 90: // mov_op
        value.YY_MOVE_OR_COPY< enum mov_op > (YY_MOVE (that.value));
        break;

      case 69: // "integer"
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 79: // instruction
      case 80: // base_instruction
        value.YY_MOVE_OR_COPY< std::shared_ptr<instruction> > (YY_MOVE (that.value));
        break;

      case 77: // value
      case 78: // expression
      case 81: // delay
      case 82: // sideset
        value.YY_MOVE_OR_COPY< std::shared_ptr<resolvable> > (YY_MOVE (that.value));
        break;

      case 75: // label_decl
      case 96: // symbol_def
        value.YY_MOVE_OR_COPY< std::shared_ptr<symbol> > (YY_MOVE (that.value));
        break;

      case 84: // wait_source
        value.YY_MOVE_OR_COPY< std::shared_ptr<wait_source> > (YY_MOVE (that.value));
        break;

      case 63: // "identifier"
      case 64: // "string"
      case 65: // "text"
      case 66: // "code block"
      case 67: // "%}"
      case 68: // UNKNOWN_DIRECTIVE
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 92: // if_full
      case 93: // if_empty
      case 94: // blocking
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 83: // condition
        value.move< enum condition > (YY_MOVE (that.value));
        break;

      case 86: // in_source
      case 87: // out_target
      case 91: // set_target
        value.move< enum in_out_set > (YY_MOVE (that.value));
        break;

      case 95: // irq_modifiers
        value.move< enum irq > (YY_MOVE (that.value));
        break;

      case 88: // mov_target
      case 89: // mov_source
        value.move< enum mov > (YY_MOVE (that.value));
        break;

      case 90: // mov_op
        value.move< enum mov_op > (YY_MOVE (that.value));
        break;

      case 69: // "integer"
        value.move< int > (YY_MOVE (that.value));
        break;

      case 79: // instruction
      case 80: // base_instruction
        value.move< std::shared_ptr<instruction> > (YY_MOVE (that.value));
        break;

      case 77: // value
      case 78: // expression
      case 81: // delay
      case 82: // sideset
        value.move< std::shared_ptr<resolvable> > (YY_MOVE (that.value));
        break;

      case 75: // label_decl
      case 96: // symbol_def
        value.move< std::shared_ptr<symbol> > (YY_MOVE (that.value));
        break;

      case 84: // wait_source
        value.move< std::shared_ptr<wait_source> > (YY_MOVE (that.value));
        break;

      case 63: // "identifier"
      case 64: // "string"
      case 65: // "text"
      case 66: // "code block"
      case 67: // "%}"
      case 68: // UNKNOWN_DIRECTIVE
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 92: // if_full
      case 93: // if_empty
      case 94: // blocking
        value.copy< bool > (that.value);
        break;

      case 83: // condition
        value.copy< enum condition > (that.value);
        break;

      case 86: // in_source
      case 87: // out_target
      case 91: // set_target
        value.copy< enum in_out_set > (that.value);
        break;

      case 95: // irq_modifiers
        value.copy< enum irq > (that.value);
        break;

      case 88: // mov_target
      case 89: // mov_source
        value.copy< enum mov > (that.value);
        break;

      case 90: // mov_op
        value.copy< enum mov_op > (that.value);
        break;

      case 69: // "integer"
        value.copy< int > (that.value);
        break;

      case 79: // instruction
      case 80: // base_instruction
        value.copy< std::shared_ptr<instruction> > (that.value);
        break;

      case 77: // value
      case 78: // expression
      case 81: // delay
      case 82: // sideset
        value.copy< std::shared_ptr<resolvable> > (that.value);
        break;

      case 75: // label_decl
      case 96: // symbol_def
        value.copy< std::shared_ptr<symbol> > (that.value);
        break;

      case 84: // wait_source
        value.copy< std::shared_ptr<wait_source> > (that.value);
        break;

      case 63: // "identifier"
      case 64: // "string"
      case 65: // "text"
      case 66: // "code block"
      case 67: // "%}"
      case 68: // UNKNOWN_DIRECTIVE
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 92: // if_full
      case 93: // if_empty
      case 94: // blocking
        value.move< bool > (that.value);
        break;

      case 83: // condition
        value.move< enum condition > (that.value);
        break;

      case 86: // in_source
      case 87: // out_target
      case 91: // set_target
        value.move< enum in_out_set > (that.value);
        break;

      case 95: // irq_modifiers
        value.move< enum irq > (that.value);
        break;

      case 88: // mov_target
      case 89: // mov_source
        value.move< enum mov > (that.value);
        break;

      case 90: // mov_op
        value.move< enum mov_op > (that.value);
        break;

      case 69: // "integer"
        value.move< int > (that.value);
        break;

      case 79: // instruction
      case 80: // base_instruction
        value.move< std::shared_ptr<instruction> > (that.value);
        break;

      case 77: // value
      case 78: // expression
      case 81: // delay
      case 82: // sideset
        value.move< std::shared_ptr<resolvable> > (that.value);
        break;

      case 75: // label_decl
      case 96: // symbol_def
        value.move< std::shared_ptr<symbol> > (that.value);
        break;

      case 84: // wait_source
        value.move< std::shared_ptr<wait_source> > (that.value);
        break;

      case 63: // "identifier"
      case 64: // "string"
      case 65: // "text"
      case 66: // "code block"
      case 67: // "%}"
      case 68: // UNKNOWN_DIRECTIVE
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
      case 63: // "identifier"
                 { yyo << "..."; }
        break;

      case 64: // "string"
                 { yyo << "..."; }
        break;

      case 65: // "text"
                 { yyo << "..."; }
        break;

      case 66: // "code block"
                 { yyo << "..."; }
        break;

      case 67: // "%}"
                 { yyo << "..."; }
        break;

      case 68: // UNKNOWN_DIRECTIVE
                 { yyo << "..."; }
        break;

      case 69: // "integer"
                 { yyo << "..."; }
        break;

      case 75: // label_decl
                 { yyo << "..."; }
        break;

      case 77: // value
                 { yyo << "..."; }
        break;

      case 78: // expression
                 { yyo << "..."; }
        break;

      case 79: // instruction
                 { yyo << "..."; }
        break;

      case 80: // base_instruction
                 { yyo << "..."; }
        break;

      case 81: // delay
                 { yyo << "..."; }
        break;

      case 82: // sideset
                 { yyo << "..."; }
        break;

      case 83: // condition
                 { yyo << "..."; }
        break;

      case 84: // wait_source
                 { yyo << "..."; }
        break;

      case 86: // in_source
                 { yyo << "..."; }
        break;

      case 87: // out_target
                 { yyo << "..."; }
        break;

      case 88: // mov_target
                 { yyo << "..."; }
        break;

      case 89: // mov_source
                 { yyo << "..."; }
        break;

      case 90: // mov_op
                 { yyo << "..."; }
        break;

      case 91: // set_target
                 { yyo << "..."; }
        break;

      case 92: // if_full
                 { yyo << "..."; }
        break;

      case 93: // if_empty
                 { yyo << "..."; }
        break;

      case 94: // blocking
                 { yyo << "..."; }
        break;

      case 95: // irq_modifiers
                 { yyo << "..."; }
        break;

      case 96: // symbol_def
                 { yyo << "..."; }
        break;

      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    /// Discard the LAC context in case there still is one left from a
    /// previous invocation.
    yy_lac_discard_ ("init");

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (pioasm));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        if (!yy_lac_establish_ (yyla.type_get ()))
           goto yyerrlab;
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        if (!yy_lac_establish_ (yyla.type_get ()))
           goto yyerrlab;

        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    yy_lac_discard_ ("shift");
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 92: // if_full
      case 93: // if_empty
      case 94: // blocking
        yylhs.value.emplace< bool > ();
        break;

      case 83: // condition
        yylhs.value.emplace< enum condition > ();
        break;

      case 86: // in_source
      case 87: // out_target
      case 91: // set_target
        yylhs.value.emplace< enum in_out_set > ();
        break;

      case 95: // irq_modifiers
        yylhs.value.emplace< enum irq > ();
        break;

      case 88: // mov_target
      case 89: // mov_source
        yylhs.value.emplace< enum mov > ();
        break;

      case 90: // mov_op
        yylhs.value.emplace< enum mov_op > ();
        break;

      case 69: // "integer"
        yylhs.value.emplace< int > ();
        break;

      case 79: // instruction
      case 80: // base_instruction
        yylhs.value.emplace< std::shared_ptr<instruction> > ();
        break;

      case 77: // value
      case 78: // expression
      case 81: // delay
      case 82: // sideset
        yylhs.value.emplace< std::shared_ptr<resolvable> > ();
        break;

      case 75: // label_decl
      case 96: // symbol_def
        yylhs.value.emplace< std::shared_ptr<symbol> > ();
        break;

      case 84: // wait_source
        yylhs.value.emplace< std::shared_ptr<wait_source> > ();
        break;

      case 63: // "identifier"
      case 64: // "string"
      case 65: // "text"
      case 66: // "code block"
      case 67: // "%}"
      case 68: // UNKNOWN_DIRECTIVE
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
              { if (pioasm.error_count || pioasm.write_output()) YYABORT; }
    break;

  case 5:
                                                { if (!pioasm.add_program(yylhs.location, yystack_[0].value.as < std::string > ())) { std::stringstream msg; msg << "program " << yystack_[0].value.as < std::string > () << " already exists"; error(yylhs.location, msg.str()); abort(); } }
    break;

  case 7:
                                                { pioasm.get_current_program(yystack_[0].location, "instruction").add_instruction(yystack_[0].value.as < std::shared_ptr<instruction> > ()); }
    break;

  case 8:
                                                { auto &p = pioasm.get_current_program(yystack_[0].location, "instruction"); p.add_label(yystack_[1].value.as < std::shared_ptr<symbol> > ()); p.add_instruction(yystack_[0].value.as < std::shared_ptr<instruction> > ()); }
    break;

  case 9:
                                                { pioasm.get_current_program(yystack_[0].location, "label").add_label(yystack_[0].value.as < std::shared_ptr<symbol> > ()); }
    break;

  case 12:
                                                { if (pioasm.error_count > 6) { std::cerr << "\ntoo many errors; aborting.\n"; YYABORT; } }
    break;

  case 13:
                                                { std::string of = yystack_[1].value.as < std::string > (); if (of.empty()) of = output_format::default_name; pioasm.get_current_program(yylhs.location, "code block", false, false).add_code_block( code_block(yylhs.location, of, yystack_[0].value.as < std::string > ())); }
    break;

  case 14:
                            { yystack_[1].value.as < std::shared_ptr<symbol> > ()->is_label = true; yylhs.value.as < std::shared_ptr<symbol> > () = yystack_[1].value.as < std::shared_ptr<symbol> > (); }
    break;

  case 15:
                                      { yystack_[1].value.as < std::shared_ptr<symbol> > ()->is_label = false; yystack_[1].value.as < std::shared_ptr<symbol> > ()->value = yystack_[0].value.as < std::shared_ptr<resolvable> > (); pioasm.get_current_program(yystack_[2].location, ".define", false, false).add_symbol(yystack_[1].value.as < std::shared_ptr<symbol> > ()); }
    break;

  case 16:
                                      { pioasm.get_current_program(yystack_[1].location, ".origin", true).set_origin(yylhs.location, yystack_[0].value.as < std::shared_ptr<resolvable> > ()); }
    break;

  case 17:
                                      { pioasm.get_current_program(yystack_[3].location, ".side_set", true).set_sideset(yylhs.location, yystack_[2].value.as < std::shared_ptr<resolvable> > (), true, true); }
    break;

  case 18:
                                      { pioasm.get_current_program(yystack_[2].location, ".side_set", true).set_sideset(yylhs.location, yystack_[1].value.as < std::shared_ptr<resolvable> > (), true, false); }
    break;

  case 19:
                                      { pioasm.get_current_program(yystack_[2].location, ".side_set", true).set_sideset(yylhs.location, yystack_[1].value.as < std::shared_ptr<resolvable> > (), false, true); }
    break;

  case 20:
                                      { pioasm.get_current_program(yystack_[1].location, ".side_set", true).set_sideset(yylhs.location, yystack_[0].value.as < std::shared_ptr<resolvable> > (), false, false); }
    break;

  case 21:
                                      { pioasm.get_current_program(yystack_[0].location, ".wrap_target").set_wrap_target(yylhs.location); }
    break;

  case 22:
                                      { pioasm.get_current_program(yystack_[0].location, ".wrap").set_wrap(yylhs.location); }
    break;

  case 23:
                                      { pioasm.get_current_program(yystack_[1].location, "instruction").add_instruction(std::shared_ptr<instruction>(new instr_word(yylhs.location, yystack_[0].value.as < std::shared_ptr<resolvable> > ()))); }
    break;

  case 24:
                                      { pioasm.get_current_program(yystack_[4].location, ".lang_opt").add_lang_opt(yystack_[3].value.as < std::string > (), yystack_[2].value.as < std::string > (), std::to_string(yystack_[0].value.as < int > ())); }
    break;

  case 25:
                                        { pioasm.get_current_program(yystack_[4].location, ".lang_opt").add_lang_opt(yystack_[3].value.as < std::string > (), yystack_[2].value.as < std::string > (), yystack_[0].value.as < std::string > ()); }
    break;

  case 26:
                                        { pioasm.get_current_program(yystack_[4].location, ".lang_opt").add_lang_opt(yystack_[3].value.as < std::string > (), yystack_[2].value.as < std::string > (), yystack_[0].value.as < std::string > ()); }
    break;

  case 27:
                                      { error(yylhs.location, "expected format is .lang_opt language option_name = option_value"); }
    break;

  case 28:
                                      { std::stringstream msg; msg << "unknown directive " << yystack_[0].value.as < std::string > (); throw syntax_error(yylhs.location, msg.str()); }
    break;

  case 29:
           { yylhs.value.as < std::shared_ptr<resolvable> > () = resolvable_int(yylhs.location, yystack_[0].value.as < int > ()); }
    break;

  case 30:
          { yylhs.value.as < std::shared_ptr<resolvable> > () = std::shared_ptr<resolvable>(new name_ref(yylhs.location, yystack_[0].value.as < std::string > ())); }
    break;

  case 31:
                                { yylhs.value.as < std::shared_ptr<resolvable> > () = yystack_[1].value.as < std::shared_ptr<resolvable> > (); }
    break;

  case 32:
     { yylhs.value.as < std::shared_ptr<resolvable> > () = yystack_[0].value.as < std::shared_ptr<resolvable> > (); }
    break;

  case 33:
                                  { yylhs.value.as < std::shared_ptr<resolvable> > () = std::shared_ptr<binary_operation>(new binary_operation(yylhs.location, binary_operation::add, yystack_[2].value.as < std::shared_ptr<resolvable> > (), yystack_[0].value.as < std::shared_ptr<resolvable> > ())); }
    break;

  case 34:
                                   { yylhs.value.as < std::shared_ptr<resolvable> > () = std::shared_ptr<binary_operation>(new binary_operation(yylhs.location, binary_operation::subtract, yystack_[2].value.as < std::shared_ptr<resolvable> > (), yystack_[0].value.as < std::shared_ptr<resolvable> > ())); }
    break;

  case 35:
                                      { yylhs.value.as < std::shared_ptr<resolvable> > () = std::shared_ptr<binary_operation>(new binary_operation(yylhs.location, binary_operation::multiply, yystack_[2].value.as < std::shared_ptr<resolvable> > (), yystack_[0].value.as < std::shared_ptr<resolvable> > ()));  }
    break;

  case 36:
                                    { yylhs.value.as < std::shared_ptr<resolvable> > () = std::shared_ptr<binary_operation>(new binary_operation(yylhs.location, binary_operation::divide, yystack_[2].value.as < std::shared_ptr<resolvable> > (), yystack_[0].value.as < std::shared_ptr<resolvable> > ())); }
    break;

  case 37:
                                { yylhs.value.as < std::shared_ptr<resolvable> > () = std::shared_ptr<binary_operation>(new binary_operation(yylhs.location, binary_operation::or_, yystack_[2].value.as < std::shared_ptr<resolvable> > (), yystack_[0].value.as < std::shared_ptr<resolvable> > ())); }
    break;

  case 38:
                                 { yylhs.value.as < std::shared_ptr<resolvable> > () = std::shared_ptr<binary_operation>(new binary_operation(yylhs.location, binary_operation::and_, yystack_[2].value.as < std::shared_ptr<resolvable> > (), yystack_[0].value.as < std::shared_ptr<resolvable> > ())); }
    break;

  case 39:
                                 { yylhs.value.as < std::shared_ptr<resolvable> > () = std::shared_ptr<binary_operation>(new binary_operation(yylhs.location, binary_operation::xor_, yystack_[2].value.as < std::shared_ptr<resolvable> > (), yystack_[0].value.as < std::shared_ptr<resolvable> > ())); }
    break;

  case 40:
                        { yylhs.value.as < std::shared_ptr<resolvable> > () = std::shared_ptr<unary_operation>(new unary_operation(yylhs.location, unary_operation::negate, yystack_[0].value.as < std::shared_ptr<resolvable> > ())); }
    break;

  case 41:
                          { yylhs.value.as < std::shared_ptr<resolvable> > () = std::shared_ptr<unary_operation>(new unary_operation(yylhs.location, unary_operation::reverse, yystack_[0].value.as < std::shared_ptr<resolvable> > ())); }
    break;

  case 42:
                                   { yylhs.value.as < std::shared_ptr<instruction> > () = yystack_[2].value.as < std::shared_ptr<instruction> > (); yylhs.value.as < std::shared_ptr<instruction> > ()->sideset = yystack_[1].value.as < std::shared_ptr<resolvable> > (); yylhs.value.as < std::shared_ptr<instruction> > ()->delay = yystack_[0].value.as < std::shared_ptr<resolvable> > (); }
    break;

  case 43:
                                   { yylhs.value.as < std::shared_ptr<instruction> > () = yystack_[2].value.as < std::shared_ptr<instruction> > (); yylhs.value.as < std::shared_ptr<instruction> > ()->delay = yystack_[1].value.as < std::shared_ptr<resolvable> > (); yylhs.value.as < std::shared_ptr<instruction> > ()->sideset = yystack_[0].value.as < std::shared_ptr<resolvable> > (); }
    break;

  case 44:
                             { yylhs.value.as < std::shared_ptr<instruction> > () = yystack_[1].value.as < std::shared_ptr<instruction> > (); yylhs.value.as < std::shared_ptr<instruction> > ()->sideset = yystack_[0].value.as < std::shared_ptr<resolvable> > (); yylhs.value.as < std::shared_ptr<instruction> > ()->delay = resolvable_int(yylhs.location, 0); }
    break;

  case 45:
                           { yylhs.value.as < std::shared_ptr<instruction> > () = yystack_[1].value.as < std::shared_ptr<instruction> > (); yylhs.value.as < std::shared_ptr<instruction> > ()->delay = yystack_[0].value.as < std::shared_ptr<resolvable> > (); }
    break;

  case 46:
                     { yylhs.value.as < std::shared_ptr<instruction> > () = yystack_[0].value.as < std::shared_ptr<instruction> > (); yylhs.value.as < std::shared_ptr<instruction> > ()->delay = resolvable_int(yylhs.location, 0); }
    break;

  case 47:
                                                          { yylhs.value.as < std::shared_ptr<instruction> > () = std::shared_ptr<instruction>(new instr_nop(yylhs.location)); }
    break;

  case 48:
                                                          { yylhs.value.as < std::shared_ptr<instruction> > () = std::shared_ptr<instruction>(new instr_jmp(yylhs.location, yystack_[2].value.as < enum condition > (), yystack_[0].value.as < std::shared_ptr<resolvable> > ())); }
    break;

  case 49:
                                                          { yylhs.value.as < std::shared_ptr<instruction> > () = std::shared_ptr<instruction>(new instr_wait(yylhs.location, yystack_[1].value.as < std::shared_ptr<resolvable> > (), yystack_[0].value.as < std::shared_ptr<wait_source> > ())); }
    break;

  case 50:
                                                          { std::stringstream msg; location l; l.begin = yystack_[2].location.end; l.end = yystack_[1].location.end; msg << "expected irq, gpio or pin after the polarity value and before the \",\""; throw yy::parser::syntax_error(l, msg.str()); }
    break;

  case 51:
                                                          { yylhs.value.as < std::shared_ptr<instruction> > () = std::shared_ptr<instruction>(new instr_wait(yylhs.location, resolvable_int(yylhs.location, 1),  yystack_[0].value.as < std::shared_ptr<wait_source> > ())); }
    break;

  case 52:
                                                          { yylhs.value.as < std::shared_ptr<instruction> > () = std::shared_ptr<instruction>(new instr_in(yylhs.location, yystack_[2].value.as < enum in_out_set > (), yystack_[0].value.as < std::shared_ptr<resolvable> > ())); }
    break;

  case 53:
                                                          { yylhs.value.as < std::shared_ptr<instruction> > () = std::shared_ptr<instruction>(new instr_out(yylhs.location, yystack_[2].value.as < enum in_out_set > (), yystack_[0].value.as < std::shared_ptr<resolvable> > ())); }
    break;

  case 54:
                                                          { yylhs.value.as < std::shared_ptr<instruction> > () = std::shared_ptr<instruction>(new instr_push(yylhs.location, yystack_[1].value.as < bool > (), yystack_[0].value.as < bool > ())); }
    break;

  case 55:
                                                          { yylhs.value.as < std::shared_ptr<instruction> > () = std::shared_ptr<instruction>(new instr_pull(yylhs.location, yystack_[1].value.as < bool > (), yystack_[0].value.as < bool > ())); }
    break;

  case 56:
                                                          { yylhs.value.as < std::shared_ptr<instruction> > () = std::shared_ptr<instruction>(new instr_mov(yylhs.location, yystack_[3].value.as < enum mov > (), yystack_[0].value.as < enum mov > (), yystack_[1].value.as < enum mov_op > ())); }
    break;

  case 57:
                                                          { yylhs.value.as < std::shared_ptr<instruction> > () = std::shared_ptr<instruction>(new instr_irq(yylhs.location, yystack_[2].value.as < enum irq > (), yystack_[1].value.as < std::shared_ptr<resolvable> > (), true)); }
    break;

  case 58:
                                                          { yylhs.value.as < std::shared_ptr<instruction> > () = std::shared_ptr<instruction>(new instr_irq(yylhs.location, yystack_[1].value.as < enum irq > (), yystack_[0].value.as < std::shared_ptr<resolvable> > ())); }
    break;

  case 59:
                                                          { yylhs.value.as < std::shared_ptr<instruction> > () = std::shared_ptr<instruction>(new instr_set(yylhs.location, yystack_[2].value.as < enum in_out_set > (), yystack_[0].value.as < std::shared_ptr<resolvable> > ())); }
    break;

  case 60:
                                 { yylhs.value.as < std::shared_ptr<resolvable> > () = yystack_[1].value.as < std::shared_ptr<resolvable> > (); }
    break;

  case 61:
               { yylhs.value.as < std::shared_ptr<resolvable> > () = yystack_[0].value.as < std::shared_ptr<resolvable> > (); }
    break;

  case 62:
                            { yylhs.value.as < enum condition > () = condition::xz; }
    break;

  case 63:
                            { yylhs.value.as < enum condition > () = condition::xnz__; }
    break;

  case 64:
                            { yylhs.value.as < enum condition > () = condition::yz; }
    break;

  case 65:
                            { yylhs.value.as < enum condition > () = condition::ynz__; }
    break;

  case 66:
                            { yylhs.value.as < enum condition > () = condition::xney; }
    break;

  case 67:
                            { yylhs.value.as < enum condition > () = condition::pin; }
    break;

  case 68:
                            { yylhs.value.as < enum condition > () = condition::osrez; }
    break;

  case 69:
                            { yylhs.value.as < enum condition > () = condition::al; }
    break;

  case 70:
                            { yylhs.value.as < std::shared_ptr<wait_source> > () = std::shared_ptr<wait_source>(new wait_source(wait_source::irq, yystack_[1].value.as < std::shared_ptr<resolvable> > (), true)); }
    break;

  case 71:
                            { yylhs.value.as < std::shared_ptr<wait_source> > () = std::shared_ptr<wait_source>(new wait_source(wait_source::irq, yystack_[0].value.as < std::shared_ptr<resolvable> > (), false)); }
    break;

  case 72:
                            { yylhs.value.as < std::shared_ptr<wait_source> > () = std::shared_ptr<wait_source>(new wait_source(wait_source::gpio, yystack_[0].value.as < std::shared_ptr<resolvable> > ())); }
    break;

  case 73:
                            { yylhs.value.as < std::shared_ptr<wait_source> > () = std::shared_ptr<wait_source>(new wait_source(wait_source::pin, yystack_[0].value.as < std::shared_ptr<resolvable> > ())); }
    break;

  case 76:
                { yylhs.value.as < enum in_out_set > () = in_out_set::in_out_set_pins; }
    break;

  case 77:
                { yylhs.value.as < enum in_out_set > () = in_out_set::in_out_set_x; }
    break;

  case 78:
                { yylhs.value.as < enum in_out_set > () = in_out_set::in_out_set_y; }
    break;

  case 79:
                { yylhs.value.as < enum in_out_set > () = in_out_set::in_out_null; }
    break;

  case 80:
                { yylhs.value.as < enum in_out_set > () = in_out_set::in_out_isr; }
    break;

  case 81:
                { yylhs.value.as < enum in_out_set > () = in_out_set::in_osr; }
    break;

  case 82:
                { yylhs.value.as < enum in_out_set > () = in_out_set::in_status; }
    break;

  case 83:
                 { yylhs.value.as < enum in_out_set > () = in_out_set::in_out_set_pins; }
    break;

  case 84:
                 { yylhs.value.as < enum in_out_set > () = in_out_set::in_out_set_x; }
    break;

  case 85:
                 { yylhs.value.as < enum in_out_set > () = in_out_set::in_out_set_y; }
    break;

  case 86:
                 { yylhs.value.as < enum in_out_set > () = in_out_set::in_out_null; }
    break;

  case 87:
                 { yylhs.value.as < enum in_out_set > () = in_out_set::in_out_set_pindirs; }
    break;

  case 88:
                 { yylhs.value.as < enum in_out_set > () = in_out_set::in_out_isr; }
    break;

  case 89:
                 { yylhs.value.as < enum in_out_set > () = in_out_set::out_set_pc; }
    break;

  case 90:
                 { yylhs.value.as < enum in_out_set > () = in_out_set::out_exec; }
    break;

  case 91:
                 { yylhs.value.as < enum mov > () = mov::pins; }
    break;

  case 92:
                 { yylhs.value.as < enum mov > () = mov::x; }
    break;

  case 93:
                 { yylhs.value.as < enum mov > () = mov::y; }
    break;

  case 94:
                 { yylhs.value.as < enum mov > () = mov::exec; }
    break;

  case 95:
                 { yylhs.value.as < enum mov > () = mov::pc; }
    break;

  case 96:
                 { yylhs.value.as < enum mov > () = mov::isr; }
    break;

  case 97:
                 { yylhs.value.as < enum mov > () = mov::osr; }
    break;

  case 98:
                 { yylhs.value.as < enum mov > () = mov::pins; }
    break;

  case 99:
                 { yylhs.value.as < enum mov > () = mov::x; }
    break;

  case 100:
                 { yylhs.value.as < enum mov > () = mov::y; }
    break;

  case 101:
                 { yylhs.value.as < enum mov > () = mov::null; }
    break;

  case 102:
                 { yylhs.value.as < enum mov > () = mov::status; }
    break;

  case 103:
                 { yylhs.value.as < enum mov > () = mov::isr; }
    break;

  case 104:
                 { yylhs.value.as < enum mov > () = mov::osr; }
    break;

  case 105:
                { yylhs.value.as < enum mov_op > () = mov_op::invert; }
    break;

  case 106:
                { yylhs.value.as < enum mov_op > () = mov_op::bit_reverse; }
    break;

  case 107:
                { yylhs.value.as < enum mov_op > () = mov_op::none; }
    break;

  case 108:
                { yylhs.value.as < enum in_out_set > () = in_out_set::in_out_set_pins; }
    break;

  case 109:
                { yylhs.value.as < enum in_out_set > () = in_out_set::in_out_set_x; }
    break;

  case 110:
                { yylhs.value.as < enum in_out_set > () = in_out_set::in_out_set_y; }
    break;

  case 111:
                { yylhs.value.as < enum in_out_set > () = in_out_set::in_out_set_pindirs; }
    break;

  case 112:
           { yylhs.value.as < bool > () = true; }
    break;

  case 113:
           { yylhs.value.as < bool > () = false; }
    break;

  case 114:
            { yylhs.value.as < bool > () = true; }
    break;

  case 115:
            { yylhs.value.as < bool > () = false; }
    break;

  case 116:
            { yylhs.value.as < bool > () = true; }
    break;

  case 117:
            { yylhs.value.as < bool > () = false; }
    break;

  case 118:
            { yylhs.value.as < bool > () = true; }
    break;

  case 119:
                   { yylhs.value.as < enum irq > () = irq::clear; }
    break;

  case 120:
                   { yylhs.value.as < enum irq > () = irq::set_wait; }
    break;

  case 121:
                   { yylhs.value.as < enum irq > () = irq::set; }
    break;

  case 122:
                   { yylhs.value.as < enum irq > () = irq::set; }
    break;

  case 123:
                   { yylhs.value.as < enum irq > () = irq::set; }
    break;

  case 124:
                    { yylhs.value.as < std::shared_ptr<symbol> > () = std::shared_ptr<symbol>(new symbol(yylhs.location, yystack_[0].value.as < std::string > ())); }
    break;

  case 125:
                    { yylhs.value.as < std::shared_ptr<symbol> > () = std::shared_ptr<symbol>(new symbol(yylhs.location, yystack_[0].value.as < std::string > (), true)); }
    break;

  case 126:
                    { yylhs.value.as < std::shared_ptr<symbol> > () = std::shared_ptr<symbol>(new symbol(yylhs.location, yystack_[0].value.as < std::string > (), true)); }
    break;



            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      yy_lac_discard_ ("error recovery");
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
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


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  bool
  parser::yy_lac_check_ (int yytoken) const
  {
    // Logically, the yylac_stack's lifetime is confined to this function.
    // Clear it, to get rid of potential left-overs from previous call.
    yylac_stack_.clear ();
    // Reduce until we encounter a shift and thereby accept the token.
#if YYDEBUG
    YYCDEBUG << "LAC: checking lookahead " << yytname_[yytoken] << ':';
#endif
    std::ptrdiff_t lac_top = 0;
    while (true)
      {
        state_type top_state = (yylac_stack_.empty ()
                                ? yystack_[lac_top].state
                                : yylac_stack_.back ());
        int yyrule = yypact_[+top_state];
        if (yy_pact_value_is_default_ (yyrule)
            || (yyrule += yytoken) < 0 || yylast_ < yyrule
            || yycheck_[yyrule] != yytoken)
          {
            // Use the default action.
            yyrule = yydefact_[+top_state];
            if (yyrule == 0)
              {
                YYCDEBUG << " Err\n";
                return false;
              }
          }
        else
          {
            // Use the action from yytable.
            yyrule = yytable_[yyrule];
            if (yy_table_value_is_error_ (yyrule))
              {
                YYCDEBUG << " Err\n";
                return false;
              }
            if (0 < yyrule)
              {
                YYCDEBUG << " S" << yyrule << '\n';
                return true;
              }
            yyrule = -yyrule;
          }
        // By now we know we have to simulate a reduce.
        YYCDEBUG << " R" << yyrule - 1;
        // Pop the corresponding number of values from the stack.
        {
          std::ptrdiff_t yylen = yyr2_[yyrule];
          // First pop from the LAC stack as many tokens as possible.
          std::ptrdiff_t lac_size = std::ptrdiff_t (yylac_stack_.size ());
          if (yylen < lac_size)
            {
              yylac_stack_.resize (std::size_t (lac_size - yylen));
              yylen = 0;
            }
          else if (lac_size)
            {
              yylac_stack_.clear ();
              yylen -= lac_size;
            }
          // Only afterwards look at the main stack.
          // We simulate popping elements by incrementing lac_top.
          lac_top += yylen;
        }
        // Keep top_state in sync with the updated stack.
        top_state = (yylac_stack_.empty ()
                     ? yystack_[lac_top].state
                     : yylac_stack_.back ());
        // Push the resulting state of the reduction.
        state_type state = yy_lr_goto_state_ (top_state, yyr1_[yyrule]);
        YYCDEBUG << " G" << state;
        yylac_stack_.push_back (state);
      }
  }

  // Establish the initial context if no initial context currently exists.
  bool
  parser::yy_lac_establish_ (int yytoken)
  {
    /* Establish the initial context for the current lookahead if no initial
       context is currently established.

       We define a context as a snapshot of the parser stacks.  We define
       the initial context for a lookahead as the context in which the
       parser initially examines that lookahead in order to select a
       syntactic action.  Thus, if the lookahead eventually proves
       syntactically unacceptable (possibly in a later context reached via a
       series of reductions), the initial context can be used to determine
       the exact set of tokens that would be syntactically acceptable in the
       lookahead's place.  Moreover, it is the context after which any
       further semantic actions would be erroneous because they would be
       determined by a syntactically unacceptable token.

       yy_lac_establish_ should be invoked when a reduction is about to be
       performed in an inconsistent state (which, for the purposes of LAC,
       includes consistent states that don't know they're consistent because
       their default reductions have been disabled).

       For parse.lac=full, the implementation of yy_lac_establish_ is as
       follows.  If no initial context is currently established for the
       current lookahead, then check if that lookahead can eventually be
       shifted if syntactic actions continue from the current context.  */
    if (!yy_lac_established_)
      {
#if YYDEBUG
        YYCDEBUG << "LAC: initial context established for "
                 << yytname_[yytoken] << '\n';
#endif
        yy_lac_established_ = true;
        return yy_lac_check_ (yytoken);
      }
    return true;
  }

  // Discard any previous initial lookahead context.
  void
  parser::yy_lac_discard_ (const char* evt)
  {
   /* Discard any previous initial lookahead context because of Event,
      which may be a lookahead change or an invalidation of the currently
      established initial context for the current lookahead.

      The most common example of a lookahead change is a shift.  An example
      of both cases is syntax error recovery.  That is, a syntax error
      occurs when the lookahead is syntactically erroneous for the
      currently established initial context, so error recovery manipulates
      the parser stacks to try to find a new initial context in which the
      current lookahead is syntactically acceptable.  If it fails to find
      such a context, it discards the lookahead.  */
    if (yy_lac_established_)
      {
        YYCDEBUG << "LAC: initial context discarded due to "
                 << evt << '\n';
        yy_lac_established_ = false;
      }
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
         In the first two cases, it might appear that the current syntax
         error should have been detected in the previous state when
         yy_lac_check was invoked.  However, at that time, there might
         have been a different syntax error that discarded a different
         initial context during error recovery, leaving behind the
         current lookahead.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

#if YYDEBUG
        // Execute LAC once. We don't care if it is succesful, we
        // only do it for the sake of debugging output.
        if (!yy_lac_established_)
          yy_lac_check_ (yytoken);
#endif

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            for (int yyx = 0; yyx < yyntokens_; ++yyx)
              if (yyx != yy_error_token_ && yyx != yy_undef_token_
                  && yy_lac_check_ (yyx))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -52;

  const signed char parser::yytable_ninf_ = -12;

  const short
  parser::yypact_[] =
  {
       3,   -52,   -41,   -39,   -52,   -52,    -3,     5,     5,     5,
       7,    44,    10,     0,   101,    18,    30,    94,    51,    50,
     -52,    20,   -52,    13,   -52,    88,    17,   -52,   -52,   129,
     -52,   -52,     2,    85,   -52,   -52,     1,     1,   -52,   -52,
      40,   -52,   -52,   -52,    42,    58,   -52,    28,    96,   120,
     120,   120,   120,    15,   -52,   -52,   -52,   -52,   -52,   -52,
     -52,   -52,   120,   -52,   -52,   -52,   -52,   -52,   -52,   -52,
     -52,   120,   -52,    63,   -52,    63,   -52,   -52,   -52,   -52,
     -52,   -52,   -52,   120,   -52,   -52,   -52,   -52,     5,   -52,
     -52,   -52,   -52,   120,   -52,   -52,   -52,   -52,     3,   -52,
       1,     5,    45,   130,   -52,     1,     1,   -52,   177,   162,
     -52,    97,   132,   -52,   -52,   -52,   -52,    87,   -52,   -52,
       1,     5,     5,     5,     5,   -52,     5,     5,   -52,   -52,
     -52,   -52,    29,   118,     5,   -52,   170,   -52,   -52,   -52,
     182,   177,     1,     1,     1,     1,     1,     1,     1,   -52,
     -52,   -51,   -52,   177,   119,   -52,   -52,   -52,   -52,   -52,
     -52,   -52,    82,   -52,   -52,   -52,   182,   182,   107,   107,
     -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,
     -52,   -52,   -52,   -52,   -52
  };

  const signed char
  parser::yydefact_[] =
  {
       0,    12,     0,     0,    21,    22,     0,     0,     0,     0,
       0,    69,     0,     0,     0,   113,   115,     0,   123,     0,
      47,     0,   124,     0,    28,     0,     0,     3,    10,     9,
       6,     7,    46,     0,   126,     5,     0,     0,    30,    29,
      20,    23,    16,    27,     0,     0,    67,     0,     0,    75,
      75,    75,    75,     0,    51,    76,    79,    77,    78,    80,
      81,    82,    75,    83,    86,    87,    84,    85,    90,    89,
      88,    75,   112,   118,   114,   118,    91,    92,    93,    94,
      95,    96,    97,    75,   120,   122,   121,   119,     0,   108,
     111,   109,   110,    75,   125,    13,     1,     2,     0,     8,
       0,     0,    45,    44,    14,     0,     0,    32,    15,     0,
      19,    18,     0,    68,    62,    64,    63,     0,    65,    74,
       0,     0,     0,     0,     0,    49,     0,     0,   116,   117,
      54,    55,   107,    58,     0,     4,     0,    61,    43,    42,
      40,    41,     0,     0,     0,     0,     0,     0,     0,    31,
      17,     0,    66,    48,    71,    73,    72,    50,    52,    53,
     105,   106,     0,    57,    59,    60,    33,    34,    35,    36,
      37,    38,    39,    25,    26,    24,    70,    98,   101,    99,
     100,   103,   104,   102,    56
  };

  const short
  parser::yypgoto_[] =
  {
     -52,   -52,   -52,   102,   -52,   -52,   -52,    -7,   -14,   172,
     -52,    99,   103,   -52,   146,    25,   -52,   -52,   -52,   -52,
     -52,   -52,   -52,   -52,   128,   -52,   198
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,    25,    26,    27,    28,    29,    30,   107,   108,    31,
      32,   102,   103,    49,    54,   120,    62,    71,    83,   184,
     162,    93,    73,    75,   130,    88,    33
  };

  const short
  parser::yytable_[] =
  {
      40,    41,    42,   -11,     1,    53,   -11,    37,    43,     2,
     100,    37,   105,   173,   174,     2,    37,    97,   175,   124,
      98,   106,    34,   109,    35,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    55,    56,   116,   117,    50,   160,   161,
      51,    52,    50,    57,    58,    51,    52,    59,    60,    21,
      22,    61,   101,    45,    38,    21,    22,    72,    38,    23,
      39,    24,    44,    38,    39,   121,   122,   123,    74,    39,
      95,   133,    84,    94,    46,   110,   136,   126,    96,    85,
     104,   140,   141,    89,   137,    90,   127,    47,    48,   111,
     113,    86,    87,    91,    92,   101,   153,   112,   132,   128,
     129,   114,   115,   118,   154,   155,   156,   157,   134,   158,
     159,   146,   147,   148,   119,   177,   178,   164,   166,   167,
     168,   169,   170,   171,   172,   179,   180,    76,   100,   181,
     182,   152,   150,   183,    63,    64,    65,    77,    78,    79,
      80,    81,    82,   151,    66,    67,    68,    69,    70,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,   149,
     163,   176,   142,   143,   144,   145,   146,   147,   148,   165,
     142,   143,   144,   145,   146,   147,   148,   142,   143,   144,
     145,   146,   147,   148,   144,   145,   146,   147,   148,   125,
     135,    99,   139,   131,    36,   138
  };

  const unsigned char
  parser::yycheck_[] =
  {
       7,     8,     9,     0,     1,    12,     3,     6,     1,    12,
       8,     6,    11,    64,    65,    12,     6,     0,    69,     4,
       3,    20,    63,    37,    63,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    43,    44,    17,    18,    37,    19,    20,
      40,    41,    37,    53,    54,    40,    41,    57,    58,    62,
      63,    61,    60,    19,    63,    62,    63,    49,    63,    66,
      69,    68,    65,    63,    69,    50,    51,    52,    48,    69,
      67,    88,    31,    63,    40,    45,   100,    62,     0,    38,
       5,   105,   106,    43,   101,    45,    71,    53,    54,    59,
      42,    50,    51,    53,    54,    60,   120,    65,    83,    46,
      47,    53,    54,    17,   121,   122,   123,   124,    93,   126,
     127,    14,    15,    16,     4,    43,    44,   134,   142,   143,
     144,   145,   146,   147,   148,    53,    54,    43,     8,    57,
      58,    54,    45,    61,    43,    44,    45,    53,    54,    55,
      56,    57,    58,    21,    53,    54,    55,    56,    57,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     7,
      52,    52,    10,    11,    12,    13,    14,    15,    16,     9,
      10,    11,    12,    13,    14,    15,    16,    10,    11,    12,
      13,    14,    15,    16,    12,    13,    14,    15,    16,    53,
      98,    29,   103,    75,     6,   102
  };

  const signed char
  parser::yystos_[] =
  {
       0,     1,    12,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    62,    63,    66,    68,    71,    72,    73,    74,    75,
      76,    79,    80,    96,    63,    63,    96,     6,    63,    69,
      77,    77,    77,     1,    65,    19,    40,    53,    54,    83,
      37,    40,    41,    77,    84,    43,    44,    53,    54,    57,
      58,    61,    86,    43,    44,    45,    53,    54,    55,    56,
      57,    87,    49,    92,    48,    93,    43,    53,    54,    55,
      56,    57,    58,    88,    31,    38,    50,    51,    95,    43,
      45,    53,    54,    91,    63,    67,     0,     0,     3,    79,
       8,    60,    81,    82,     5,    11,    20,    77,    78,    78,
      45,    59,    65,    42,    53,    54,    17,    18,    17,     4,
      85,    85,    85,    85,     4,    84,    85,    85,    46,    47,
      94,    94,    85,    77,    85,    73,    78,    77,    82,    81,
      78,    78,    10,    11,    12,    13,    14,    15,    16,     7,
      45,    21,    54,    78,    77,    77,    77,    77,    77,    77,
      19,    20,    90,    52,    77,     9,    78,    78,    78,    78,
      78,    78,    78,    64,    65,    69,    52,    43,    44,    53,
      54,    57,    58,    61,    89
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    70,    71,    72,    72,    73,    73,    73,    73,    73,
      73,    73,    73,    74,    75,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    77,
      77,    77,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    79,    79,    79,    79,    79,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      81,    82,    83,    83,    83,    83,    83,    83,    83,    83,
      84,    84,    84,    84,    85,    85,    86,    86,    86,    86,
      86,    86,    86,    87,    87,    87,    87,    87,    87,    87,
      87,    88,    88,    88,    88,    88,    88,    88,    89,    89,
      89,    89,    89,    89,    89,    90,    90,    90,    91,    91,
      91,    91,    92,    92,    93,    93,    94,    94,    94,    95,
      95,    95,    95,    95,    96,    96,    96
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     1,     3,     2,     1,     1,     2,     1,
       1,     0,     1,     2,     2,     3,     2,     4,     3,     3,
       2,     1,     1,     2,     5,     5,     5,     2,     1,     1,
       1,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     3,     3,     2,     2,     1,     1,     4,     3,
       4,     2,     4,     4,     3,     3,     5,     4,     3,     4,
       3,     2,     2,     2,     2,     2,     3,     1,     2,     0,
       4,     3,     3,     3,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     1,     1,
       1,     1,     1,     0,     1,     0,     1,     1,     0,     1,
       1,     1,     1,     0,     1,     2,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"end of line\"", "\",\"",
  "\":\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"+\"", "\"-\"", "\"*\"",
  "\"/\"", "\"|\"", "\"&\"", "\"^\"", "\"--\"", "\"!=\"", "\"!\"",
  "\"::\"", "\"=\"", "\".program\"", "\".wrap_target\"", "\".wrap\"",
  "\".define\"", "\".side_set\"", "\".word\"", "\".origin\"",
  "\".lang_opt\"", "\"jmp\"", "\"wait\"", "\"in\"", "\"out\"", "\"push\"",
  "\"pull\"", "\"mov\"", "\"irq\"", "\"set\"", "\"nop\"", "\"pin\"",
  "\"gpio\"", "\"osre\"", "\"pins\"", "\"null\"", "\"pindirs\"",
  "\"block\"", "\"noblock\"", "\"ifempty\"", "\"iffull\"", "\"nowait\"",
  "\"clear\"", "\"rel\"", "\"x\"", "\"y\"", "\"exec\"", "\"pc\"",
  "\"isr\"", "\"osr\"", "\"opt\"", "\"side\"", "\"status\"", "\"public\"",
  "\"identifier\"", "\"string\"", "\"text\"", "\"code block\"", "\"%}\"",
  "UNKNOWN_DIRECTIVE", "\"integer\"", "$accept", "file", "lines", "line",
  "code_block", "label_decl", "directive", "value", "expression",
  "instruction", "base_instruction", "delay", "sideset", "condition",
  "wait_source", "comma", "in_source", "out_target", "mov_target",
  "mov_source", "mov_op", "set_target", "if_full", "if_empty", "blocking",
  "irq_modifiers", "symbol_def", YY_NULLPTR
  };

#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   136,   136,   140,   141,   144,   145,   146,   147,   148,
     149,   150,   151,   155,   159,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   180,
     181,   182,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   199,   200,   201,   202,   203,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     224,   228,   232,   233,   234,   235,   236,   237,   238,   239,
     243,   244,   245,   246,   248,   248,   251,   252,   253,   254,
     255,   256,   257,   260,   261,   262,   263,   264,   265,   266,
     267,   270,   271,   272,   273,   274,   275,   276,   279,   280,
     281,   282,   283,   284,   285,   289,   290,   291,   295,   296,
     297,   298,   302,   303,   307,   308,   312,   313,   314,   318,
     319,   320,   321,   322,   326,   327,   328
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy


void yy::parser::error(const location_type& l, const std::string& m)
{
   if (l.begin.filename) {
      std::cerr << l << ": " << m << '\n';
      pioasm.error_count++;
      if (l.begin.line == l.end.line && *l.begin.filename == *l.end.filename) {
        std::ifstream file(l.begin.filename->c_str());
        std::string line;
        for(int i = 0; i < l.begin.line; ++i) {
             std::getline(file, line);
        }
        fprintf(stderr, "%5d | %s\n", l.begin.line, line.c_str());
        fprintf(stderr, "%5s | %*s", "", l.begin.column, "^");
        for (int i = l.begin.column; i < l.end.column - 1; i++) {
              putc ('~', stderr);
        }
        putc ('\n', stderr);
      }
  } else {
      std::cerr << m << '\n';
  }
}

