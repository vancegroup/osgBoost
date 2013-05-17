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
#ifndef INCLUDED_CrossProduct_h_GUID_8a1558aa_6ee4_4797_858b_5d19f76dc1cd
#define INCLUDED_CrossProduct_h_GUID_8a1558aa_6ee4_4797_858b_5d19f76dc1cd


// Internal Includes
#include "TypePredicates.h"
#include "PromoteTypeWithScalar.h"
#include "OperatorBase.h"

// Library/third-party includes
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>

// Standard includes
// - none


namespace osgTraits {
	struct Pow;

	template<>
	struct OperatorVerb<Pow> {
		/// @todo if something else uses this: ^ we need a different solution
		static const char * get() {
			return "cross-product";
		}
	};

	template<typename T1, typename T2>
	struct VectorCrossProduct {
		typedef typename promote_type_with_scalar<T1, typename get_scalar<T2>::type>::type return_type;

		template<typename A, typename B>
		static return_type performOperation(A const& v1, B const& v2) {
			return return_type(v1) ^ return_type(v2);
		}
	};
	template<typename T1, typename T2>
	struct BinaryOperatorImplementation < Pow, T1, T2, typename boost::enable_if <
			boost::mpl::and_ <
			has_dimension<T1, 3>,
			has_floating_point_scalar<T1>,
			are_compatible_vectors<T1, T2> > >::type >  {

		typedef VectorCrossProduct<T1, T2> type;
	};

} // end of namespace osgTraits


#endif // INCLUDED_CrossProduct_h_GUID_8a1558aa_6ee4_4797_858b_5d19f76dc1cd
