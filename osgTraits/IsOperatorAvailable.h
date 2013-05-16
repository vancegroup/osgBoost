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
		struct is_bound_operation_available : is_operation_available< add_argtype<BoundOperation, T> > {};

		typedef mpl::back_inserter< mpl::list0<> > inserter_type;

		/// @brief Given a BoundOperation (a binary Operator with one of
		/// its two argument Types fixed/bound), return a list of all
		/// Types that are valid (have implementations) if substituted into
		/// the missing argument position.
		template<typename Operation>
		struct get_valid_other_arg_types :
				mpl::copy_if <
				other_argument_types,
				is_bound_operation_available<Operation, _>,
				inserter_type
				> {};

		template<typename ArityTag>
		struct is_operator_applicable_impl {
			template<typename Operator, typename T>
			struct apply;
		};
		/// Specialization for unary operators - can directly construct a
		/// full Operation to inquire about.
		template<>
		struct is_operator_applicable_impl <arity_tags::unary_tag> {
			template<typename Operator, typename T>
			struct apply {
				typedef typename is_operation_available<typename construct_operation<Operator, T>::type>::type type;
			};
		};

		template<typename BoundOperation>
		struct bound_operation_has_implementations {
			typedef typename mpl::not_<typename mpl::empty<typename get_valid_other_arg_types<BoundOperation>::type >::type >::type type;
		};

		/// Specialization for binary operators - must check to see if the
		/// list of other valid arg types is empty for both possible binding
		/// positions for the type given.
		template<>
		struct is_operator_applicable_impl <arity_tags::binary_tag> {
			template<typename Operator, typename T>
			struct apply {
				typedef typename mpl::or_ <
				bound_operation_has_implementations<construct_bound_operation<Operator, T, 0> >,
				                                    bound_operation_has_implementations<construct_bound_operation<Operator, T, 1> > >::type type;
			};
		};
		/*
				typedef mpl::lambda < mpl::or_ <
				mpl::not_<mpl::empty<get_valid_other_arg_types<construct_bound_operation<_1, _2, 0> > > >,
				    mpl::not_<mpl::empty<get_valid_other_arg_types<construct_bound_operation<_1, _2, 1> > > > > >::type
				    binary_operator_and_type_have_implementations_f;



				/// @brief Given an Operator and a single Type, return whether
				/// any complete, valid Operations can be constructed with the
				/// Operator and Type.
				template<typename Operator, typename T, typename = void>
				struct is_operator_applicable {
					//typedef is_operation_available<construct_operation<Operator, T> > unary_result;
					//typedef mpl::bind<binary_operator_and_type_have_implementations_f, Operator, T> binary_result;
					typedef typename mpl::eval_if < typename is_unary<Operator>::type,
					        is_operation_available<construct_operation<Operator, T> >,
					        mpl::bind<binary_operator_and_type_have_implementations_f, Operator, T>
					        >::type type;


				};
		*/
		template<typename Operator, typename T, typename = void>
		struct is_operator_applicable : is_operator_applicable_impl<typename get_arity<Operator>::type>::template apply<Operator, T> {};

	} // end of namespace availability_detail

	using availability_detail::get_valid_other_arg_types;
	using availability_detail::is_operation_available;
	using availability_detail::is_operator_applicable;

} // end of namespace osgTraits

#endif // INCLUDED_IsOperatorAvailable_h_GUID_ea6e8ae3_7a30_4c88_b99e_5f12b40ee59b
