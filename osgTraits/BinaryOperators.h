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
#ifndef INCLUDED_BinaryOperators_h_GUID_9d5a8223_67c4_4299_99ef_30fe8607bab4
#define INCLUDED_BinaryOperators_h_GUID_9d5a8223_67c4_4299_99ef_30fe8607bab4

// Internal Includes
#include "MathAndArithmeticTypes.h"

#include "Addition.h"
#include "Subtraction.h"
#include "Multiplication.h"
#include "Pow.h"
#include "Division.h"
#include "Equality.h"
#include "LessThan.h"

// Library/third-party includes
#include <boost/mpl/list/list10.hpp>

// Standard includes
// - none

namespace osgTraits {
	typedef math_and_arithmetic_types other_argument_types;

	typedef boost::mpl::list7<Addition, Subtraction, Multiplication, Pow, Division, Equality, LessThan> BinaryOperators;

} // end of namespace osgTraits
#endif // INCLUDED_BinaryOperators_h_GUID_9d5a8223_67c4_4299_99ef_30fe8607bab4
