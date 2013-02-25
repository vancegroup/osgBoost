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
#include "Operators.h"
#include "testmain.h"

// Library/third-party includes
// - none

// Standard includes
// - none

typedef construct_bound_operation<Addition, osg::Vec3d, 0>::type bound0;
typedef construct_bound_operation<Addition, osg::Vec3d, 1>::type bound1;
typedef construct_operation<Addition, osg::Vec3d, osg::Vec3d>::type full;

BOOST_MPL_ASSERT((is_same<add_argtype<bound0, osg::Vec3d>::type, full>));
BOOST_MPL_ASSERT((is_same<add_argtype<bound1, osg::Vec3d>::type, full>));
