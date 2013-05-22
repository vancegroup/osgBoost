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
#ifndef INCLUDED_Subtraction_h_GUID_fec3e459_c1e7_441b_9a1b_bc11a65a8336
#define INCLUDED_Subtraction_h_GUID_fec3e459_c1e7_441b_9a1b_bc11a65a8336

// Internal Includes
#include "TypePredicates.h"
#include "PromoteTypeWithScalar.h"
#include "OperatorBase.h"

// Library/third-party includes
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/or.hpp>

// Standard includes
// - none


namespace osgTraits {
	struct Subtraction : BinaryOperator<Subtraction> {};

	template<>
	struct OperatorVerb<Subtraction> {
		static const char * get() {
			return "subtract";
		}
	};

	template<typename T1, typename T2>
	struct ComponentwiseSubtraction {
		typedef typename promote_type_with_scalar<T1, typename get_scalar<T2>::type>::type return_type;
		static return_type performOperation(T1 const& v1, T2 const& v2) {
			return return_type(v1) - return_type(v2);
		}
	};
	template<typename T1, typename T2>
	struct BinaryOperatorImplementation < Subtraction, T1, T2, typename boost::enable_if <
			boost::mpl::or_ <
			are_compatible_vectors<T1, T2>,
			are_compatible_quats<T1, T2> > >::type > : OperatorImplementationBase {
		typedef ComponentwiseSubtraction<T1, T2> type;
	};

} // end of namespace osgTraits

#endif // INCLUDED_Subtraction_h_GUID_fec3e459_c1e7_441b_9a1b_bc11a65a8336
