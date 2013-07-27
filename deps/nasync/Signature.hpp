#ifndef BOOST_PP_IS_ITERATING
#  ifndef SIGNATURE_HPP_
#    define SIGNATURE_HPP_
#    ifdef PP_ITERATION_LIMIT
#      define PP_SIGNATURE_ITERATION_LIMIT PP_ITERATION_LIMIT
#    else
#      define PP_SIGNATURE_ITERATION_LIMIT 5
#    endif
#    include <boost/preprocessor/arithmetic/sub.hpp>
#    include <boost/preprocessor/logical/and.hpp>
#    include <boost/preprocessor/repetition/enum.hpp>
#    include <boost/preprocessor/repetition/enum_params.hpp>
#    include <boost/preprocessor/iteration/iterate.hpp>
#    include <boost/preprocessor/punctuation/comma_if.hpp>
namespace nasync {
template <typename S>
struct Signature;
} /* namespace nasync */
#    define BOOST_PP_ITERATION_PARAMS_1 (3, (0, PP_SIGNATURE_ITERATION_LIMIT, <nasync/Signature.hpp>))
#    include BOOST_PP_ITERATE()
#  endif /* SIGNATURE_HPP_ */
#elif BOOST_PP_ITERATION_DEPTH() == 1
#  define BOOST_PP_ITERATION_PARAMS_2 (3, (0, PP_SIGNATURE_ITERATION_LIMIT, <nasync/Signature.hpp>))
#  include BOOST_PP_ITERATE()
#elif BOOST_PP_ITERATION_DEPTH() == 2
#  define PP_i BOOST_PP_FRAME_ITERATION(1)
#  define PP_i_ BOOST_PP_SUB(PP_SIGNATURE_ITERATION_LIMIT, PP_i)
#  define PP_j BOOST_PP_FRAME_ITERATION(2)
#  define PP_j_ BOOST_PP_SUB(PP_SIGNATURE_ITERATION_LIMIT, PP_j)
#  define PP_TEXT(z, n, text) text
#  define PP_TP_LIST BOOST_PP_ENUM(PP_SIGNATURE_ITERATION_LIMIT, PP_TEXT, class)
#  define PP_METHOD_ARG BOOST_PP_ENUM_PARAMS(PP_i,class MethodArg)
#  define PP_RETURN_ARG BOOST_PP_ENUM_PARAMS(PP_j,class ReturnArg)
#  define PP_METHOD_SPEC_ARG BOOST_PP_ENUM_PARAMS(PP_i,MethodArg) BOOST_PP_COMMA_IF(BOOST_PP_AND(PP_i,PP_i_)) BOOST_PP_ENUM(PP_i_, PP_TEXT, void)
#  define PP_RETURN_SPEC_ARG BOOST_PP_ENUM_PARAMS(PP_j,ReturnArg) BOOST_PP_COMMA_IF(BOOST_PP_AND(PP_j,PP_j_)) BOOST_PP_ENUM(PP_j_, PP_TEXT, void)
namespace nasync {
template <
  PP_METHOD_ARG BOOST_PP_COMMA_IF(PP_i)
  PP_RETURN_ARG BOOST_PP_COMMA_IF(PP_j)
  template <PP_TP_LIST,class> class M,
  template <PP_TP_LIST,class> class R >
struct Signature <void(*)(const M<PP_METHOD_SPEC_ARG,void>&, R<PP_RETURN_SPEC_ARG,void>&) > {
  static const bool ClassMethod = false;
  typedef M<PP_METHOD_SPEC_ARG,void> MethodArgs;
  typedef R<PP_RETURN_SPEC_ARG,void> ReturnArgs;
  typedef void(*MethodPtr)(const MethodArgs&, ReturnArgs&);
};
template <
  class Class,
  PP_METHOD_ARG BOOST_PP_COMMA_IF(PP_i)
  PP_RETURN_ARG BOOST_PP_COMMA_IF(PP_j)
  template <PP_TP_LIST,class> class M,
  template <PP_TP_LIST,class> class R >
struct Signature <void(Class::*)(const M<PP_METHOD_SPEC_ARG,void>&, R<PP_RETURN_SPEC_ARG,void>&) > {
  static const bool ClassMethod = true;
  typedef M<PP_METHOD_SPEC_ARG,void> MethodArgs;
  typedef R<PP_RETURN_SPEC_ARG,void> ReturnArgs;
  typedef void(Class::*MethodPtr)(const MethodArgs&, ReturnArgs&);
  typedef Class ClassType;
};
} /* namespace nasync */
#  undef PP_i
#  undef PP_i_
#  undef PP_j
#  undef PP_j_
#  undef PP_TEXT
#  undef PP_TP_LIST
#  undef PP_METHOD_ARG
#  undef PP_RETURN_ARG
#  undef PP_METHOD_SPEC_ARG
#  undef PP_RETURN_SPEC_ARG
#endif
