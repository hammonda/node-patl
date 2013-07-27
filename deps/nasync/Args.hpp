#ifndef BOOST_PP_IS_ITERATING
#  ifndef ARGS_HPP
#    define ARGS_HPP
#    ifdef PP_ITERATION_LIMIT
#      define PP_ARGS_ITERATION_LIMIT PP_ITERATION_LIMIT
#    else
#      define PP_ARGS_ITERATION_LIMIT 5
#    endif
#    include <boost/preprocessor/arithmetic/add.hpp>
#    include <boost/preprocessor/repetition/enum.hpp>
#    include <boost/preprocessor/repetition/enum_params.hpp>
#    include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#    include <boost/preprocessor/iteration/iterate.hpp>
#    include <boost/preprocessor/repetition/repeat.hpp>

#    include <nasync/FromV8.hpp>
#    include <nasync/ToV8.hpp>
namespace nasync {
template <
  BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
  BOOST_PP_ADD(PP_ARGS_ITERATION_LIMIT, 1), class Arg, void) >
class Args;
} /* namespace nasync */
#    define BOOST_PP_ITERATION_LIMITS (0, PP_ARGS_ITERATION_LIMIT)
#    define BOOST_PP_FILENAME_1 <nasync/Args.hpp>
#    include BOOST_PP_ITERATE()
#  endif /* ARGS_HPP */
#else
#  define PP_i BOOST_PP_ITERATION()
#  define PP_DECL_ARGS(z, n, text) Arg ## n arg ## n;
#  define PP_FROMV8(z, n, text) arg ## n (FromV8<Arg ## n>::exec(args[n]))
#  define PP_TOV8(z, n, text) argv[n] = ToV8(arg ## n);
namespace nasync {
template < BOOST_PP_ENUM_PARAMS(PP_i, class Arg) >
class Args < BOOST_PP_ENUM_PARAMS(PP_i, Arg) > {
public:
  static const uint32_t Size = PP_i;
  Args (const v8::Arguments &args)
#if PP_i
  : BOOST_PP_ENUM(PP_i, PP_FROMV8, ~)
#endif
  { }
  Args () { }

  inline void toV8 (v8::Handle<v8::Value> *argv) {
    BOOST_PP_REPEAT(PP_i, PP_TOV8, ~)
  }
  BOOST_PP_REPEAT(PP_i, PP_DECL_ARGS, ~)
};
} /* namespace nasync */
#  undef PP_i
#  undef PP_DECL_ARGS
#  undef PP_FROMV8
#  undef PP_TOV8
#  undef PP_ARGS_ITERATION_LIMIT
#endif
