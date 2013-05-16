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
#ifndef INCLUDED_GetOperator_h_GUID_4518d04a_19de_43f0_be33_b7428f7ad117
#define INCLUDED_GetOperator_h_GUID_4518d04a_19de_43f0_be33_b7428f7ad117

// Internal Includes
// - none

// Library/third-party includes
#include <boost/mpl/at.hpp>

// Standard includes
// - none

namespace osgTraits {
	template<typename Operation>
	struct get_operator : boost::mpl::at_c<Operation, 0> {};
} // end of namespace osgTraits

#endif // INCLUDED_GetOperator_h_GUID_4518d04a_19de_43f0_be33_b7428f7ad117
