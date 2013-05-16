/** @file
	@brief Header

	@date 2012

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#ifndef INCLUDED_IsOperatorAvailable_h_GUID_ea6e8ae3_7a30_4c88_b99e_5f12b40ee59b
#define INCLUDED_IsOperatorAvailable_h_GUID_ea6e8ae3_7a30_4c88_b99e_5f12b40ee59b

// Internal Includes
#include "InvokeOperator.h"
#include "Operators.h"
#include "OperatorArity.h"
#include "OperationArguments.h"
#include "ConstructOperation.h"
#include "ConstructBoundOperation.h"
#include "AddArgType.h"

// Library/third-party includes
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/list/list10.hpp>
#include <boost/mpl/copy_if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/lambda.hpp>


// Standard includes
// - none

namespace osgTraits {

	namespace availability_detail {
		namespace mpl = boost::mpl;
		using namespace boost::mpl::placeholders;
		using boost::is_base_and_derived;
		using boost::enable_if;

		/// @brief Given an Operation (that is, Operator and argument Type(s)),
		/// return whether there is an implementation to perform that Operation.
		template<typename Operation>
		struct is_operation_available {
			typedef typename get_operation_invoker<Operation>::type invoker;
			typedef typename mpl::not_<typename is_base_and_derived<detail::UnimplementedOperationBase, invoker>::type >::type type;
		};

		/// @brief Given a BoundOperation (a binary Operator with one of
		/// its two argument Types fixed/bound) and a Type, return whether
		/// there is an implementation to perform the operation with the given
		/// Type substituted into the missing argument position.

		template<typename BoundOperation, typename T>
		struct is_bound_operation_available
				: mpl::apply2<is_operation_available<add_argtype<_, _> >, BoundOperation, T> {};

		/// @brief Given a BoundOperation (a binary Operator with one of
		/// its two argument Types fixed/bound), return a list of all
		/// Types that are valid (have implementations) if substituted into
		/// the missing argument position.
		template<typename Operation>
		struct get_valid_other_arg_types :
				mpl::copy_if <
				other_argument_types,
				mpl::lambda<is_bound_operation_available<Operation, _> >
				> {};

		template<typename ArityTag>
		struct is_operator_applicable_impl {
			template<typename Operator, typename T>
			struct apply;
		};

		/// Specialization for unary operators - can directly construct a
		/// full Operation to inquire about.
		template<>
		struct is_operator_applicable_impl <arity_tags::unary_tag>
				: mpl::lambda<is_operation_available<construct_operation<_, _> > >::type {};

		template<typename BoundOperation>
		struct bound_operation_has_implementations {
			typedef typename mpl::apply1<mpl::not_< mpl::empty<get_valid_other_arg_types<_> > >, BoundOperation>::type type;
		};

		/// Specialization for binary operators - must check to see if the
		/// list of other valid arg types is empty for both possible binding
		/// positions for the type given.
		template<>
		struct is_operator_applicable_impl <arity_tags::binary_tag> {
			template<typename Operator, typename T>
			struct apply {
				typedef bound_operation_has_implementations<typename construct_bound_operation<Operator, T, 0>::type > bound_first_implementations;
				typedef bound_operation_has_implementations<typename construct_bound_operation<Operator, T, 1>::type > bound_second_implementations;
				typedef typename mpl::or_ <bound_first_implementations, bound_second_implementations>::type type;
			};
		};

		template<typename Operator, typename T, typename = void>
		struct is_operator_applicable : mpl::apply2<is_operator_applicable_impl<typename get_arity<Operator>::type>, Operator, T> {};

	} // end of namespace availability_detail

	using availability_detail::get_valid_other_arg_types;
	using availability_detail::is_operation_available;
	using availability_detail::is_operator_applicable;

} // end of namespace osgTraits

#endif // INCLUDED_IsOperatorAvailable_h_GUID_ea6e8ae3_7a30_4c88_b99e_5f12b40ee59b
