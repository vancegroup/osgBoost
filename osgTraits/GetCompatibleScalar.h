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
#ifndef INCLUDED_GetCompatibleScalar_h_GUID_d27674ff_6057_4136_9268_f854370bc94c
#define INCLUDED_GetCompatibleScalar_h_GUID_d27674ff_6057_4136_9268_f854370bc94c

// Internal Includes
#include "GetScalar.h"

// Library/third-party includes
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

// Standard includes
// - none

namespace osgTraits {
	namespace compatible_scalar_detail {
		template<typename T1, typename T2, typename = void>
		struct get_compatible_scalarImpl {};

		template<typename T1, typename T2>
struct get_compatible_scalarImpl < T1, T2, typename boost::enable_if_c< (sizeof(typename get_scalar<T1>::type) < sizeof(typename get_scalar<T2>::type)) >::type> : get_compatible_scalarImpl<T2, T1> {};

		template<typename T>
		struct get_compatible_scalarImpl<T, T, void> {
			typedef T type;
		};

		template<>
		struct get_compatible_scalarImpl<double, float, void> {
			typedef double type;
		};

		template<>
		struct get_compatible_scalarImpl<double, long int, void> {
			typedef double type;
		};

		template<>
		struct get_compatible_scalarImpl<double, int, void> {
			typedef double type;
		};
		
		template<typename T1, typename T2>
		struct get_compatible_scalar
				: get_compatible_scalarImpl<typename get_scalar<T1>::type, typename get_scalar<T2>::type> {};
	} // end of namespace compatible_scalar_detail
	
	using compatible_scalar_detail::get_compatible_scalar;


};

#endif // INCLUDED_GetCompatibleScalar_h_GUID_d27674ff_6057_4136_9268_f854370bc94c
