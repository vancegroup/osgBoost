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

// Library/third-party includes
#include <boost/mpl/apply.hpp>
#include <boost/utility/enable_if.hpp>

// Standard includes
// - none

namespace osgTraits {

	namespace invoke_detail {
		using boost::mpl::apply;
		using boost::enable_if;
		template<typename Operation>
		struct UnaryImplementationWrapper
				: UnaryOperatorImplementation <
				typename get_operator<Operation>::type,
				typename get_operation_argument_c<Operation, 0>::type > {};

		template<typename Operation>
		struct BinaryImplementationWrapper
				: BinaryOperatorImplementation <
				typename get_operator<Operation>::type,
				typename get_operation_argument_c<Operation, 0>::type,
				typename get_operation_argument_c<Operation, 1>::type > {};

		template<typename Operation, typename = void>
		struct get_operation_invoker;

		template<typename Operation>
		struct get_operation_invoker<Operation, typename enable_if<	is_operation_unary<Operation> >::type >
				: UnaryImplementationWrapper<typename Operation::sequence_type>::type { };

		template<typename Operation>
		struct get_operation_invoker<Operation, typename enable_if<	is_operation_binary<Operation> >::type>
				: BinaryImplementationWrapper<typename Operation::sequence_type>::type { };
	} // end of invoke_detail
	using invoke_detail::get_operation_invoker;

	template<typename Operation>
	typename get_operation_invoker<Operation>::return_type invokeOperation(typename get_operation_argument_c<Operation, 0>::type const& a) {
		typedef typename boost::mpl::apply<get_operation_invoker<Operation> >::type Invoker;
		return Invoker::performOperation(a);
	}

	template<typename Operation>
	typename get_operation_invoker<Operation>::return_type invokeOperation(typename get_operation_argument_c<Operation, 0>::type const& a, typename get_operation_argument_c<Operation, 1>::type const& b) {
		typedef typename boost::mpl::apply<get_operation_invoker<Operation> >::type Invoker;
		return Invoker::performOperation(a, b);
	}

} // end of namespace osgTraits

#endif // INCLUDED_InvokeOperator_h_GUID_a76515c6_9231_4154_a0cb_168bce258629
