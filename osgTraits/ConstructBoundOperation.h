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
#ifndef INCLUDED_ConstructBoundOperation_h_GUID_3b588bd8_744e_45a5_950e_6f1d3b62d0e7
#define INCLUDED_ConstructBoundOperation_h_GUID_3b588bd8_744e_45a5_950e_6f1d3b62d0e7

// Internal Includes
#include "OperationArgumentPlaceholder.h"
#include "ConstructOperation.h"

// Library/third-party includes
// - none

// Standard includes
// - none

namespace osgTraits {
	namespace construct_bound_operation_detail {
		template<typename Operator, typename T, int Arg>
		struct construct_bound_operation;

		template<typename Operator, typename T>
		struct construct_bound_operation<Operator, T, 0> : construct_operation<Operator, T, OperationArgumentPlaceholder> {};

		template<typename Operator, typename T>
		struct construct_bound_operation<Operator, T, 1> : construct_operation<Operator, OperationArgumentPlaceholder, T> {};

	} // end of construct_bound_operation_detail

	using construct_bound_operation_detail::construct_bound_operation;

} // end of namespace osgTraits

#endif // INCLUDED_ConstructBoundOperation_h_GUID_3b588bd8_744e_45a5_950e_6f1d3b62d0e7
