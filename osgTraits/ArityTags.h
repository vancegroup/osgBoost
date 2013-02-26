/** @file
	@brief Header

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

#pragma once
#ifndef INCLUDED_ArityTags_h_GUID_0d85ca73_839a_4ccc_b155_238a59858017
#define INCLUDED_ArityTags_h_GUID_0d85ca73_839a_4ccc_b155_238a59858017

// Internal Includes
#include "GetOperator.h"
#include "OperatorArity.h"

// Library/third-party includes
#include <boost/mpl/if.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/assert.hpp>

// Standard includes
// - none


namespace osgTraits {
	namespace detail {
		namespace mpl = boost::mpl;

		struct UnaryTag;
		struct BinaryTag;
		template<typename Operator>
		struct GetOperatorArityTag {
			typedef typename get_operator_arity<Operator>::type arity;
			typedef typename mpl::if_ < mpl::equal_to<mpl::int_<1>, arity >,
			        UnaryTag,
			        typename mpl::if_ < mpl::equal_to<mpl::int_<2>, arity >,
			        BinaryTag,
			        void >::type
			        >::type type;
			BOOST_MPL_ASSERT((mpl::or_<mpl::equal_to<mpl::int_<1>, arity>, mpl::equal_to<mpl::int_<2>, arity > >));
		};

		template<typename Operation>
		struct GetOperationArityTag : GetOperatorArityTag<typename get_operator<Operation>::type> {};
	} // end of namespace detail
} // end of namespace osgTraits

#endif // INCLUDED_ArityTags_h_GUID_0d85ca73_839a_4ccc_b155_238a59858017
