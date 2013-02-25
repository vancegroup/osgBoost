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
//#include "OperatorBase.h"
#include "OperationArity.h"

// Library/third-party includes
#include <boost/utility/enable_if.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/same_as.hpp>

#include <boost/type_traits/is_same.hpp>


// Standard includes
// - none

namespace osgTraits {
	namespace operation_detail {
		struct Placeholder;
		using boost::enable_if;
		using boost::mpl::if_;
		using boost::mpl::int_;
		using boost::mpl::not_;
		using boost::mpl::equal_to;
		using boost::mpl::at_c;
		using boost::mpl::at;
		using boost::mpl::and_;
		using boost::mpl::apply;
		using boost::mpl::next;
		using boost::is_same;

		using boost::mpl::vector2;
		using boost::mpl::vector3;
		namespace mpl = boost::mpl;


		template<typename Operation>
		struct get_sequence : Operation {};

		typedef mpl::same_as<Placeholder> is_placeholder;
		typedef mpl::not_same_as<Placeholder> is_not_placeholder;
		typedef mpl::lambda<mpl::at < mpl::_1, mpl::next<mpl::_2> > >::type get_operation_arg;

		struct get_operation_argument {
			template<typename Operation, typename Num>
			struct apply {
				typedef typename mpl::at < Operation, typename mpl::next<Num>::type >::type type;
			};
		};

		template<typename Operation, int Num>
		struct get_operation_argument_c : at_c < Operation, Num + 1 > {};

		template<typename Operation, typename Num>
		struct is_operation_argument_missing {
			typedef typename apply<is_placeholder, apply< get_operation_argument, Operation, Num> >::type type;
		};

		template<typename Operation, typename Num>
		struct is_operation_argument_supplied : apply<is_not_placeholder, apply<get_operation_argument, Operation, Num> > {};

		template<typename Sequence>
		struct Operation : Sequence {};

		template<typename Operator, typename T1 = Placeholder, typename T2 = Placeholder>
		struct construct_operation {
			typedef typename if_ < equal_to<typename get_operator_arity<Operator>::type, int_<2> >,
			        Operation<vector3<Operator, T1, T2> >,
			        Operation<vector2<Operator, T1> > >::type type ;
		};

		/*template<typename Operation, typename T, typename = void>
		struct add_argtype;  {
			typedef void type;
		};*/
		template<typename Operation, typename T>
		struct add_argtype {
			typedef get_operator<Operation> the_operator;
			typedef get_operator_arity<the_operator> arity;
			typedef mpl::bind<get_operation_argument, Operation, int_<0> > arg0;
			typedef mpl::bind<get_operation_argument, Operation, int_<1> > arg1;
			typedef typename if_ < is_operation_argument_missing<Operation, int_<0> >,
			        if_ < equal_to<arity, int_<1> >,
			        construct_operation<the_operator, T>,
			        construct_operation<the_operator, T, arg1> > ,
			        typename if_ < is_operation_argument_missing<Operation, int_<1> >,
			        construct_operation<the_operator, arg0, T>
			        >::type
			        >::type type;
		};
		/*
				template<typename Operation, typename T>
				struct add_argtype < Operation, T, typename enable_if < and_ <
						is_operation_unary<Operation>,
						is_operation_argument_missing<Operation, 0>
						> >::type > : construct_operation<typename get_operator<Operation>::type, T> {};

				template<typename Operation, typename T>
				struct add_argtype < Operation, T, typename enable_if < and_ <
						is_operation_binary<Operation>,
						is_operation_argument_missing<Operation, 0>
						> >::type > : construct_operation<typename get_operator<Operation>::type, T, typename get_operation_argument_c<Operation, 1>::type> {};

				template<typename Operation, typename T>
				struct add_argtype < Operation, T,  typename enable_if < and_ <
						is_operation_binary<Operation>,
						is_operation_argument_supplied<Operation, 0>,
						is_operation_argument_missing<Operation, 1>
						> >::type >
						: construct_operation<typename get_operator<Operation>::type, typename get_operation_argument_c<Operation, 0>::type, T> {};
		*/
		template<typename Operator, typename T, int Arg>
		struct construct_bound_operation;

		template<typename Operator, typename T>
		struct construct_bound_operation<Operator, T, 0> : construct_operation<Operator, T, Placeholder> {};

		template<typename Operator, typename T>
		struct construct_bound_operation<Operator, T, 1> : construct_operation<Operator, Placeholder, T> {};


	} // end of namespace operation_detail

	using operation_detail::construct_operation;
	using operation_detail::construct_bound_operation;
	using operation_detail::add_argtype;
	using operation_detail::get_operation_argument_c;
	using operation_detail::get_operation_argument;

} // end of namespace osgTraits

#endif // INCLUDED_Operation_h_GUID_a322cf18_6879_40b5_a317_95e96d46f254
