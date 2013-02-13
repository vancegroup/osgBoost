if(BUILD_TESTING)
	set(TESTS)

	include_directories("${CMAKE_CURRENT_SOURCE_DIR}/..")

	foreach(TEST ${TESTS})
		add_executable(osgLua_boost_test_${TEST} ${TEST}.cpp)
		target_link_libraries(osgLua_boost_test_${TEST} ${OPENSCENEGRAPH_LIBRARIES})
		add_test(NAME osgLua_boost_test_${TEST}
			COMMAND $<TARGET_FILE:osgLua_boost_test_${TEST}>)
		set_target_properties(osgLua_boost_test_${TEST} PROPERTIES FOLDER "osgLua Tests")
	endforeach()
	
	add_custom_target(osgLua_boost_headercompile)

	#file(GLOB HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/.." "${CMAKE_CURRENT_SOURCE_DIR}/../*.h")
	set(HEADERS
		Addition.h
		ArithmeticTypes.h
		BinaryOperators.h
		ComputeCategoryTag.h
		CopyToFlatSequence.h
		#Division.h
		#Equality.h
		GetCategory.h
		GetCompatibleScalar.h
		GetDimension.h
		GetScalar.h
		InvokeOperator.h
		IsMathOrScalar.h
		IsMathType.h
		IsOperatorAvailable.h
		IsScalar.h
		#LessThan.h
		MathAndArithmeticTypes.h
		MathTypes.h
		#Multiplication.h
		Operation.h
		OperatorBase.h
		Operators.h
		OsgMathTraits.h
		#Pow.h
		PromoteTypeWithScalar.h
		#ReplaceFirst.h
		SelectType.h
		#Subtraction.h
		Tags.h
		TypeLists.h
		TypePredicates.h
		#UnaryMinus.h
		UnaryOperators.h
	)

	foreach(HEADER ${HEADERS})
		string(REPLACE ".h" "" SHORTNAME "${HEADER}")
		set(stem "test_osgLua_headercompile_${SHORTNAME}")
		configure_file(test_headercompile.cpp.in "${CMAKE_CURRENT_BINARY_DIR}/${stem}.cpp" @ONLY)

		add_executable(${stem} "${CMAKE_CURRENT_BINARY_DIR}/${stem}.cpp")
		target_link_libraries(${stem} ${OPENSCENEGRAPH_LIBRARIES})
		add_test(${stem}_executes ${stem})
		add_dependencies(osgLua_boost_headercompile ${stem})
	endforeach()

	
endif()
