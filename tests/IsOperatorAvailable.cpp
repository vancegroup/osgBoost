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
#include "IsOperatorAvailable.h"
#include "testmain.h"

// Library/third-party includes
// - none

// Standard includes
// - none


BOOST_MPL_ASSERT((is_operator_applicable<UnaryMinus, osg::Vec3d>));

typedef construct_bound_operation<Addition, osg::Vec3d, 0>::type BoundOp;

BOOST_MPL_ASSERT((availability_detail::is_bound_operation_available<BoundOp, osg::Vec3d>));
BOOST_MPL_ASSERT_NOT((availability_detail::is_bound_operation_available<BoundOp, osg::Vec4d>));

BOOST_MPL_ASSERT_NOT((mpl::empty<get_valid_other_arg_types<BoundOp>::type>));
BOOST_MPL_ASSERT((mpl::is_sequence<get_valid_other_arg_types<BoundOp>::type>));

BOOST_MPL_ASSERT((is_operator_applicable<Addition, osg::Vec3d>));

typedef construct_operation<UnaryMinus, osg::Vec3d>::type MyUnaryOperation;
typedef construct_operation<Addition, osg::Vec3d, osg::Vec3d>::type MyBinaryOperation;

BOOST_MPL_ASSERT((is_operation_available<MyUnaryOperation>));
BOOST_MPL_ASSERT((is_operation_available<MyBinaryOperation>));


BOOST_MPL_ASSERT_NOT((is_operation_available<construct_operation<UnaryMinus, osg::Matrixd>::type>));
BOOST_MPL_ASSERT_NOT((is_operation_available<construct_operation<Addition, osg::Vec3d, osg::Vec4d>::type>));


