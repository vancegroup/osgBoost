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
#ifndef INCLUDED_LessThan_h_GUID_0d282eed_0a0f_4e86_a94b_a62201d38e7f
#define INCLUDED_LessThan_h_GUID_0d282eed_0a0f_4e86_a94b_a62201d38e7f


// Internal Includes
#include "TypePredicates.h"
#include "OperatorBase.h"

// Library/third-party includes
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/and.hpp>

// Standard includes
// - none

namespace osgTraits {
	struct LessThan : BinaryOperator<LessThan> {};

	template<>
	struct OperatorVerb<LessThan> {
		static const char * get() {
			return "compare for less-than";
		}
	};

	template<typename T1, typename T2>
	struct MatrixLessThanOverride {
		typedef bool return_type;
		static return_type performOperation(T1 const& v1, T2 const& v2) {
			return v1 < v2;
		}
	};

	template<typename T1, typename T2>
	struct BinaryOperatorImplementation < LessThan, T1, T2, typename boost::enable_if <
			boost::mpl::and_ <
			is_matrix<T1>,
			boost::is_same<T1, T2> > >::type >  {
		typedef MatrixLessThanOverride<T1, T2> type;
	};

} // end of namespace osgTraits

#endif // INCLUDED_LessThan_h_GUID_0d282eed_0a0f_4e86_a94b_a62201d38e7f
