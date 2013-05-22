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
#ifndef INCLUDED_InvokeOperator_h_GUID_a76515c6_9231_4154_a0cb_168bce258629
#define INCLUDED_InvokeOperator_h_GUID_a76515c6_9231_4154_a0cb_168bce258629

// Internal Includes
#include "Operators.h"
#include "GetOperator.h"
#include "OperatorArity.h"
#include "OperationArguments.h"

// Library/third-party includes
#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/unpack_args.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/lambda.hpp>

// Standard includes
// - none

namespace osgTraits {

	namespace invoke_detail {
		using namespace boost::mpl::placeholders;
		namespace mpl = boost::mpl;

		template<typename Operation>
		struct get_operation_invoker {

			typedef typename mpl::eval_if <
			typename mpl::apply<is_unary<_1>, Operation>::type,
			         mpl::apply<mpl::unpack_args<UnaryOperatorImplementation<_1, _2>  >, Operation>,
			         mpl::apply<mpl::unpack_args<BinaryOperatorImplementation<_1, _2, _3>  >, Operation>
			         >::type type;


		};
	} // end of invoke_detail
	using invoke_detail::get_operation_invoker;

	template<typename Operation>
	typename get_operation_invoker<Operation>::type::return_type
	invokeOperation(typename get_operation_argument_c<Operation, 0>::type const& a) {
		typedef typename get_operation_invoker<Operation>::type Invoker;
		return Invoker::performOperation(a);
	}

	template<typename Operation>
	typename get_operation_invoker<Operation>::type::return_type
	invokeOperation(typename get_operation_argument_c<Operation, 0>::type const& a,
	                typename get_operation_argument_c<Operation, 1>::type const& b) {
		typedef typename get_operation_invoker<Operation>::type Invoker;
		return Invoker::performOperation(a, b);
	}

} // end of namespace osgTraits

#endif // INCLUDED_InvokeOperator_h_GUID_a76515c6_9231_4154_a0cb_168bce258629
