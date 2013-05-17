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
#ifndef INCLUDED_Multiplication_h_GUID_d7c2cc4f_5b7d_4891_bc1d_6b3a21a9b3c9
#define INCLUDED_Multiplication_h_GUID_d7c2cc4f_5b7d_4891_bc1d_6b3a21a9b3c9

// Internal Includes
#include "TypePredicates.h"
#include "PromoteTypeWithScalar.h"
#include "OperatorBase.h"

// Library/third-party includes
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>

// Standard includes
// - none


namespace osgTraits {
	struct Multiplication : BinaryOperator<Multiplication> {};

	template<>
	struct OperatorVerb<Multiplication> {
		static const char * get() {
			return "multiply/dot";
		}
	};

	template<typename T1, typename T2, typename ReturnType>
	struct GeneralMultiplication {
		typedef ReturnType return_type;
		static return_type performOperation(T1 const& v1, T2 const& v2) {
			return v1 * v2;
		}
	};

	namespace MultiplicationDetail {
		using namespace ::osgTraits::BinaryPredicates;
		using boost::enable_if;
		using boost::mpl::and_;
		using boost::mpl::or_;
		template<typename T1, typename T2>
		struct SimilarFloatTypes : and_ < have_same_category<T1, T2>,
				have_same_dimension<T1, T2>,
				has_floating_point_scalar<T1>,
				has_floating_point_scalar<T2>,
				have_compatible_scalar<T1, T2>
				> {};

		template<typename T1, typename T2>
		struct ComposeTransform : and_ < SimilarFloatTypes<T1, T2>,
				or_<is_matrix<T1>, is_quat<T1> > > {};

		/// @todo does this have to be a float?
		template<typename T1, typename T2>
		struct DotProduct : and_ < SimilarFloatTypes<T1, T2>,
				is_vector<T1> > {};

		template<typename T1, typename T2>
		struct VectorAndTransform : and_ <
				is_transformable_vector<T1>,
				or_< and_<is_matrix<T2>, has_dimension<T2, 4> >, is_quat<T2> >,
				have_compatible_scalar<T1, T2> > {};

		template<typename T1, typename T2>
		struct ScalarAndVector : and_ <
				is_scalar<T1>,
				is_vector<T2>,
				have_compatible_scalar<T1, T2> > {};

	} // end of namespace MultiplicationDetail

	/// Transform composition
	template<typename T1, typename T2>
	struct BinaryOperatorImplementation < Multiplication, T1, T2,
			typename boost::enable_if < typename MultiplicationDetail::ComposeTransform<T1, T2>::type >::type > {
		typedef typename promote_type_with_scalar<T1, typename get_scalar<T2>::type>::type return_type;
		typedef GeneralMultiplication<T1, T2, return_type> type;
	};

	/// Vector dot product
	template<typename T1, typename T2>
	struct BinaryOperatorImplementation < Multiplication, T1, T2,
			typename boost::enable_if < typename MultiplicationDetail::DotProduct<T1, T2>::type >::type > {
		typedef typename promote_type_with_scalar<typename get_scalar<T1>::type, typename get_scalar<T2>::type>::type return_type;
		typedef GeneralMultiplication<T1, T2, return_type> type;
	};

	/// Transformable Vector times a Transform
	template<typename Vec, typename Xform>
	struct BinaryOperatorImplementation < Multiplication, Vec, Xform,
			typename boost::enable_if < typename MultiplicationDetail::VectorAndTransform<Vec, Xform>::type >::type > {
		typedef typename promote_type_with_scalar<Vec, typename get_scalar<Xform>::type>::type return_type;
		typedef GeneralMultiplication<Vec, Xform, return_type> type;
	};

	/// Transform times a Transformable Vector
	template<typename Xform, typename Vec>
	struct BinaryOperatorImplementation < Multiplication, Xform, Vec,
			typename boost::enable_if < typename MultiplicationDetail::VectorAndTransform<Vec, Xform>::type >::type > {
		typedef typename promote_type_with_scalar<Vec, typename get_scalar<Xform>::type>::type return_type;
		typedef GeneralMultiplication<Xform, Vec, return_type> type;
	};

	/// Scalar times Vector
	template<typename Scalar, typename Vec>
	struct BinaryOperatorImplementation < Multiplication, Scalar, Vec,
			typename boost::enable_if < typename MultiplicationDetail::ScalarAndVector<Scalar, Vec>::type >::type > {
		typedef typename promote_type_with_scalar<Vec, typename get_scalar<Scalar>::type>::type return_type;
		typedef GeneralMultiplication<Scalar, Vec, return_type> type;
	};

	/// Vector times Scalar
	template<typename Vec, typename Scalar>
	struct BinaryOperatorImplementation < Multiplication, Vec, Scalar,
			typename boost::enable_if < typename MultiplicationDetail::ScalarAndVector<Scalar, Vec>::type >::type > {
		typedef typename promote_type_with_scalar<Vec, typename get_scalar<Scalar>::type>::type return_type;
		typedef GeneralMultiplication<Vec, Scalar, return_type> type;
	};

} // end of namespace osgTraits

#endif // INCLUDED_Multiplication_h_GUID_d7c2cc4f_5b7d_4891_bc1d_6b3a21a9b3c9
