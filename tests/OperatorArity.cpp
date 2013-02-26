/**
	@file
	@brief Implementation

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

// Internal Includes
#include "OperatorArity.h"
#include "Addition.h"
#include "testmain.h"

// Library/third-party includes
// - none

// Standard includes
// - none


BOOST_MPL_ASSERT_NOT((is_operator_unary<Addition>));
BOOST_MPL_ASSERT((is_operator_binary<Addition>));
