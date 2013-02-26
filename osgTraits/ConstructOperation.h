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
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/mpl/equal_to.hpp>

// Standard includes
// - none

namespace osgTraits {
	namespace construct_operation_detail {
		namespace mpl = boost::mpl;


		template<typename Operator, typename T1 = OperationArgumentPlaceholder, typename T2 = OperationArgumentPlaceholder>
		struct construct_operation {
			typedef typename mpl::if_ < mpl::equal_to<typename get_operator_arity<Operator>::type, mpl::int_<2> >,
			        Operation<mpl::vector3<Operator, T1, T2> >,
			        Operation<mpl::vector2<Operator, T1> > >::type type ;
		};
	}// end of namespace construct_operation_detail
	using construct_operation_detail::construct_operation;
} // end of namespace osgTraits

#endif // INCLUDED_ConstructOperation_h_GUID_0c1c172f_4fa5_447a_a5e4_09100b41364a
