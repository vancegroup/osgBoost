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
#ifndef INCLUDED_Equality_h_GUID_3320559d_0f91_4060_b24e_3fa581f105f1
#define INCLUDED_Equality_h_GUID_3320559d_0f91_4060_b24e_3fa581f105f1

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
	struct Equality : BinaryOperator<Equality> {};

	template<>
	struct OperatorVerb<Equality> {
		static const char * get() {
			return "compare for equality";
		}
	};

	template<typename T1, typename T2>
	struct MatrixEqualityOverride {
		typedef bool return_type;
		static return_type performOperation(T1 const& v1, T2 const& v2) {
			return v1 == v2;
		}
	};

	template<typename T1, typename T2>
	struct BinaryOperatorImplementation < Equality, T1, T2, typename boost::enable_if <
			boost::mpl::and_ <
			is_matrix<T1>,
			boost::is_same<T1, T2> > >::type > : OperatorImplementationBase {
		typedef MatrixEqualityOverride<T1, T2> type;
	};

} // end of namespace osgTraits

#endif // INCLUDED_Equality_h_GUID_3320559d_0f91_4060_b24e_3fa581f105f1
