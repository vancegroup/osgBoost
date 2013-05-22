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
#ifndef INCLUDED_OperatorBase_h_GUID_f6f3382a_be9f_4e4c_a166_43dc8bb15d40
#define INCLUDED_OperatorBase_h_GUID_f6f3382a_be9f_4e4c_a166_43dc8bb15d40

// Internal Includes
#include "ArityTags.h"

// Library/third-party includes
// - none

// Standard includes
// - none

namespace osgTraits {
	namespace detail {
		struct UnarySpecializedOperatorBase {};
		struct BinarySpecializedOperatorBase {};
		struct UnimplementedOperationBase {
			typedef void unimplemented_tag;
		};
	} // end of namespace detail


	template<typename Operator, typename T1, typename = void>
	struct UnaryOperatorImplementation : detail::UnimplementedOperationBase {};

	template<typename Operator, typename T1, typename T2, typename = void>
	struct BinaryOperatorImplementation : detail::UnimplementedOperationBase {};

	template<typename Operator>
	struct OperatorVerb;

	struct OperatorBase {};
	struct UnaryOperatorBase : OperatorBase {
		typedef arity_tags::unary_tag arity_tag;
	};

	struct BinaryOperatorBase : OperatorBase {
		typedef arity_tags::binary_tag arity_tag;
	};

	template<typename Op>
	struct UnaryOperator : UnaryOperatorBase {};

	template<typename Op>
	struct BinaryOperator : BinaryOperatorBase {};

} // end of namespace osgTraits

#endif // INCLUDED_OperatorBase_h_GUID_f6f3382a_be9f_4e4c_a166_43dc8bb15d40
