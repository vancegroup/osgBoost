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
#ifndef INCLUDED_TypePredicates_h_GUID_746880c7_3f70_40c4_99e6_0717ac100770
#define INCLUDED_TypePredicates_h_GUID_746880c7_3f70_40c4_99e6_0717ac100770

// Internal Includes
#include "OsgMathTraits.h"
#include "GetCompatibleScalar.h"

// Library/third-party includes
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/lambda.hpp>

// Standard includes
// - none

namespace osgTraits {
	namespace UnaryPredicates {
		namespace mpl = boost::mpl;
		using namespace boost::mpl::placeholders;


		template<typename T>
		struct has_floating_point_scalar : boost::is_floating_point<typename get_scalar<T>::type> {};

		typedef mpl::lambda<mpl::equal_to<get_dimension<_1>, _2 > >::type HasDimensionLambda;

		template<typename T, int Dim>
		struct has_dimension : mpl::apply<HasDimensionLambda, T, mpl::int_<Dim> >::type {};


		template<typename V>
		struct is_transformable_vector : mpl::and_ <
				is_vector<V>,
				mpl::or_
				< has_dimension<V, 3>
				, has_dimension<V, 4>
				> >::type {};

	} // end of namespace UnaryPredicates


	using UnaryPredicates::has_dimension;
	using UnaryPredicates::is_transformable_vector;
	using UnaryPredicates::has_floating_point_scalar;

	namespace BinaryPredicates {
		namespace mpl = boost::mpl;
		using namespace boost::mpl::placeholders;
		using boost::is_same;
		using boost::enable_if;

		namespace detail {
			BOOST_MPL_HAS_XXX_TRAIT_DEF(type);
		} // end of namespace detail

		/// @TODO does having a "type" member here metafunction style instead of
		/// inheriting the result make this less compatible
		template<typename T1, typename T2, typename = void>
		struct have_compatible_scalar : mpl::false_ {};

		template<typename T1, typename T2>
		struct have_compatible_scalar < T1, T2,
				typename enable_if<detail::has_type<get_compatible_scalar<typename get_scalar<T1>::type, typename get_scalar<T2>::type> > >::type >
				: mpl::true_ {};

		template<typename T1, typename T2>
		struct have_same_category : is_same<typename get_category<T1>::type, typename get_category<T2>::type>::type {};

		template<typename T1, typename T2>
		struct have_same_dimension : is_same<typename get_dimension<T1>::type, typename get_dimension<T2>::type>::type {};

		template<typename T1, typename T2>
		struct have_same_cat_and_dim_with_compat_scalar : mpl::and_ <
				have_same_category<T1, T2>,
				have_compatible_scalar<T1, T2>,
				have_same_dimension<T1, T2>
				>::type {};

		template<typename T1, typename T2>
		struct are_compatible_vectors : mpl::and_ <
				is_vector<T1>,
				have_same_cat_and_dim_with_compat_scalar<T1, T2> >::type {};

		template<typename T1, typename T2>
		struct are_compatible_quats : mpl::and_ <
				is_quat<T1>,
				have_same_cat_and_dim_with_compat_scalar<T1, T2> >::type {};

		template<typename T1, typename T2>
		struct are_compatible_matrices : mpl::and_ <
				is_matrix<T1>,
				have_same_cat_and_dim_with_compat_scalar<T1, T2> >::type {};
	} // end of namespace BinaryPredicates


	using BinaryPredicates::have_compatible_scalar;
	using BinaryPredicates::have_same_category;
	using BinaryPredicates::have_same_dimension;
	using BinaryPredicates::are_compatible_vectors;
	using BinaryPredicates::are_compatible_quats;
	using BinaryPredicates::are_compatible_matrices;

} // end of namespace osgTraits
#endif // INCLUDED_TypePredicates_h_GUID_746880c7_3f70_40c4_99e6_0717ac100770
