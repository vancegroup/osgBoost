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
#ifndef INCLUDED_OperationArguments_h_GUID_ceac10aa_e033_424d_873b_0edb8531a66f
#define INCLUDED_OperationArguments_h_GUID_ceac10aa_e033_424d_873b_0edb8531a66f

// Internal Includes
#include "OperationArgumentPlaceholder.h"

// Library/third-party includes
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>

// Standard includes
// - none

namespace osgTraits {
	namespace operation_arguments_details {
		namespace mpl = boost::mpl;
		using namespace mpl::placeholders;

		template<typename Operation, typename N>
		struct get_operation_argument : mpl::at <Operation, mpl::plus<mpl::int_<1>, N> > {};

		template<typename Operation, int Num>
		struct get_operation_argument_c : mpl::at_c < Operation, Num + 1 > {};

		template<typename Operation, typename Num>
		struct is_operation_argument_missing : boost::is_same<OperationArgumentPlaceholder, typename get_operation_argument<Operation, Num>::type >  {};

		template<typename Operation, typename Num>
		struct is_operation_argument_supplied : mpl::not_<is_operation_argument_missing<Operation, Num> > {};
	} // end of namespace operation_arguments_details


	using operation_arguments_details::is_operation_argument_supplied;
	using operation_arguments_details::is_operation_argument_missing;
	using operation_arguments_details::get_operation_argument;
	using operation_arguments_details::get_operation_argument_c;

} // end of namespace osgTraits

#endif // INCLUDED_OperationArguments_h_GUID_ceac10aa_e033_424d_873b_0edb8531a66f
