/** @file
	@brief Header

	@date 2013

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#ifndef INCLUDED_OperatorArity_h_GUID_8ff9af97_2009_454d_a842_25a761c96e74
#define INCLUDED_OperatorArity_h_GUID_8ff9af97_2009_454d_a842_25a761c96e74

// Internal Includes
#include "OperatorBase.h"
#include "GetOperator.h"

// Library/third-party includes
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/lambda.hpp>


// Standard includes
// - none

namespace osgTraits {

	namespace operator_arity_detail {
		namespace mpl = boost::mpl;
		using namespace ::boost::mpl::placeholders;

		typedef mpl::lambda < mpl::if_ < boost::is_base_and_derived<OperatorBase, _1>,
		        mpl::if_ < boost::is_base_and_derived<UnaryOperatorBase, _1>,
		        mpl::int_<1>,
		        mpl::int_<2> > > >::type get_arity_lambda;

		template<typename Operator>
		struct get_operator_arity {
			typedef typename mpl::apply<get_arity_lambda, Operator>::type type;
		};

		template<typename Operator, typename N>
		struct is_operator_arity : mpl::equal_to<typename get_operator_arity<Operator>::type, N > {};

		template<typename Operation>
		struct is_operator_unary : is_operator_arity<Operation, mpl::int_<1> > {};

		template<typename Operation>
		struct is_operator_binary : is_operator_arity<Operation, mpl::int_<2> > {};

		template<typename Operation, typename N>
		struct is_operation_arity : is_operator_arity<get_operator<Operation>, N> {};

		template<typename Operation>
		struct get_operation_arity : get_operator_arity<typename get_operator<Operation>::type> {};

		template<typename Operation>
		struct is_operation_unary : is_operation_arity<Operation, mpl::int_<1> > {};

		template<typename Operation>
		struct is_operation_binary : is_operation_arity<Operation, mpl::int_<2> > {};
	} // end of namespace operator_arity_detail
	using operator_arity_detail::get_operator_arity;
	using operator_arity_detail::is_operator_unary;
	using operator_arity_detail::is_operator_binary;
	using operator_arity_detail::is_operation_unary;
	using operator_arity_detail::is_operation_binary;
} // end of namespace osgTraits
#endif // INCLUDED_OperatorArity_h_GUID_8ff9af97_2009_454d_a842_25a761c96e74
