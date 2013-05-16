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
#ifndef INCLUDED_AddArgType_h_GUID_d35bb727_9aab_4585_9fe3_13e3e466b4d4
#define INCLUDED_AddArgType_h_GUID_d35bb727_9aab_4585_9fe3_13e3e466b4d4

// Internal Includes
#include "OperatorArity.h"
#include "GetOperator.h"
#include "OperationArgumentPlaceholder.h"
#include "OperationArguments.h"
#include "ConstructOperation.h"

// Library/third-party includes
#include <boost/mpl/assert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply.hpp>

// Standard includes
// - none


namespace osgTraits {
	namespace add_arg_type_detail {
		namespace mpl = boost::mpl;
		using namespace mpl::placeholders;

		template <typename ArityTag>
		struct add_argtype_impl {
			template<typename Operation, typename T>
			struct apply;
		};

		template<>
		struct add_argtype_impl<arity_tags::unary_tag> {
			template<typename Operation, typename T>
			struct apply {
				BOOST_MPL_ASSERT((is_operation_argument_missing<Operation, mpl::int_<0> >));
				typedef typename get_operator<Operation>::type Operator;
				typedef typename construct_operation<Operator, T>::type type;
			};
		};

		template<>
		struct add_argtype_impl<arity_tags::binary_tag> {
			template<typename Operation, typename T>
			struct apply {
				BOOST_MPL_ASSERT((mpl::or_ <
				                  is_operation_argument_missing<Operation, mpl::int_<0> >,
				                  is_operation_argument_missing<Operation, mpl::int_<1> > >));

				//typedef mpl::bind<get_operation_argument, Operation, _1> get_arg;
				typedef typename get_operator<Operation>::type Operator;
				typedef typename mpl::eval_if < typename is_operation_argument_missing<Operation, mpl::int_<0> >::type,
				        get_operation_argument<Operation, mpl::int_<1> >,
				        get_operation_argument<Operation, mpl::int_<0> > >::type Arg;
				typedef typename mpl::eval_if < typename is_operation_argument_missing<Operation, mpl::int_<0> >::type,
				        construct_operation<Operator, T, Arg >,
				        construct_operation<Operator, Arg, T > >::type type;
			};
		};

		template<typename Operation, typename T>
		struct add_argtype : add_argtype_impl<typename get_arity<Operation>::type>::template apply<Operation, T> {};
	} // end of namespace add_arg_type_detail

	using add_arg_type_detail::add_argtype;

} // end of namespace osgTraits

#endif // INCLUDED_AddArgType_h_GUID_d35bb727_9aab_4585_9fe3_13e3e466b4d4
