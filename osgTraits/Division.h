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
#ifndef INCLUDED_Division_h_GUID_b4eea61a_3c03_4428_a458_6f74aae5a470
#define INCLUDED_Division_h_GUID_b4eea61a_3c03_4428_a458_6f74aae5a470

// Internal Includes
#include "TypePredicates.h"
#include "OperatorBase.h"

// Library/third-party includes
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>

// Standard includes
// - none


namespace osgTraits {
	struct Division : BinaryOperator<Division> {};

	template<>
	struct OperatorVerb<Division> {
		static const char * get() {
			return "divide";
		}
	};

	template<typename Ret, typename T1, typename T2>
	struct GenericDivision {
		typedef Ret return_type;
		static return_type performOperation(T1 const& v1, T2 const& v2) {
			return v1 / v2;
		}
	};

	/// Two quats: division
	template<typename T1, typename T2>
	struct BinaryOperatorImplementation < Division, T1, T2, typename boost::enable_if <
			are_compatible_quats<T1, T2> >::type >  {
		typedef T1 return_type;
		typedef GenericDivision<return_type, T1, T2> type;
	};

	/// Vector divided by scalar: just scale down
	template<typename T1, typename T2>
	struct BinaryOperatorImplementation < Division, T1, T2, typename boost::enable_if <
			boost::mpl::and_ <
			is_vector<T1>,
			is_scalar<T2> > >::type >  {
		typedef T1 return_type;
		typedef GenericDivision<return_type, T1, T2> type;
	};


} // end of namespace osgTraits

#endif // INCLUDED_Division_h_GUID_b4eea61a_3c03_4428_a458_6f74aae5a470
