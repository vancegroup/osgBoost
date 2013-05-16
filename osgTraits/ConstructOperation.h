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
#ifndef INCLUDED_ConstructOperation_h_GUID_0c1c172f_4fa5_447a_a5e4_09100b41364a
#define INCLUDED_ConstructOperation_h_GUID_0c1c172f_4fa5_447a_a5e4_09100b41364a

// Internal Includes
#include "OperationArgumentPlaceholder.h"
#include "OperatorArity.h"
#include "Operation.h"

// Library/third-party includes
#include <boost/mpl/apply.hpp>
#include <boost/mpl/vector/vector10.hpp>

// Standard includes
// - none

namespace osgTraits {
	namespace construct_operation_detail {
		namespace mpl = boost::mpl;

		template<typename Tag>
		struct construct_operation_impl;

		template<>
		struct construct_operation_impl<arity_tags::binary_tag> {
			template<typename Operator, typename T1, typename T2>
			struct apply {
				typedef Operation<mpl::vector3<Operator, T1, T2> > type;
			};
		};

		template<>
		struct construct_operation_impl<arity_tags::unary_tag> {
			template<typename Operator, typename T1, typename T2>
			struct apply {
				typedef Operation<mpl::vector2<Operator, T1> > type;
			};
		};

		template<typename Operator, typename T1 = OperationArgumentPlaceholder, typename T2 = OperationArgumentPlaceholder>
		struct construct_operation : mpl::apply3<construct_operation_impl<typename get_arity<Operator>::type>, Operator, T1, T2> {};
	}// end of namespace construct_operation_detail
	using construct_operation_detail::construct_operation;
} // end of namespace osgTraits

#endif // INCLUDED_ConstructOperation_h_GUID_0c1c172f_4fa5_447a_a5e4_09100b41364a
