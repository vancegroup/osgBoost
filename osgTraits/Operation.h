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
#ifndef INCLUDED_Operation_h_GUID_a322cf18_6879_40b5_a317_95e96d46f254
#define INCLUDED_Operation_h_GUID_a322cf18_6879_40b5_a317_95e96d46f254

// Internal Includes
// - none

// Library/third-party includes
// - none


// Standard includes
// - none

namespace osgTraits {
	namespace operation_detail {

		template<typename Operation>
		struct get_sequence {
			typedef Operation type;
		};

		template<typename Sequence>
		struct Operation : Sequence {};

	} // end of namespace operation_detail
	using operation_detail::Operation;
} // end of namespace osgTraits

#endif // INCLUDED_Operation_h_GUID_a322cf18_6879_40b5_a317_95e96d46f254
