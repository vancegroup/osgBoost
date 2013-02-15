if(BUILD_TESTING)
	set(TESTS
		OperationArity
		Construct
		IsOperatorAvailable)

	include_directories("${CMAKE_CURRENT_SOURCE_DIR}/..")
	add_custom_target(osgLua_boost_tests)

	foreach(TEST ${TESTS})
		set(stem "osgLua_boost_test_${TEST}")
		add_executable(${stem} ${TEST}.cpp)
		target_link_libraries(${stem} ${OPENSCENEGRAPH_LIBRARIES})
		add_test(NAME ${stem}_executes
			COMMAND $<TARGET_FILE:${stem}>)
		set_target_properties(${stem} PROPERTIES FOLDER "osgLua Tests")
		add_dependencies(osgLua_boost_tests ${stem})
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
		set_target_properties(${stem} PROPERTIES FOLDER "osgLua Tests")
		add_dependencies(osgLua_boost_headercompile ${stem})
	endforeach()

	
endif()
