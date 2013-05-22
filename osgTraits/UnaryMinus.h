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
#ifndef INCLUDED_UnaryMinus_h_GUID_e5c4ce8f_a7df_4171_b7c0_672766d35673
#define INCLUDED_UnaryMinus_h_GUID_e5c4ce8f_a7df_4171_b7c0_672766d35673

// Internal Includes
#include "TypePredicates.h"
#include "PromoteTypeWithScalar.h"
#include "OperatorBase.h"

// Library/third-party includes
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>

// Standard includes
// - none


namespace osgTraits {
	struct UnaryMinus : UnaryOperator<UnaryMinus> {};

	template<>
	struct OperatorVerb<UnaryMinus> {
		static const char * get() {
			return "negate";
		}
	};

	template<typename T>
	struct SimpleUnaryMinus {
		typedef T return_type;
		static return_type performOperation(T const& v) {
			return -v;
		}
	};

	template<typename T>
	struct UnaryOperatorImplementation < UnaryMinus, T,  typename boost::enable_if <
			boost::mpl::and_ <
			boost::mpl::or_ <
			is_vector<T>,
			is_quat<T> > ,
			has_floating_point_scalar<T> > >::type > : OperatorImplementationBase {
		typedef SimpleUnaryMinus<T> type;
	};

} // end of namespace osgTraits


#endif // INCLUDED_UnaryMinus_h_GUID_e5c4ce8f_a7df_4171_b7c0_672766d35673
