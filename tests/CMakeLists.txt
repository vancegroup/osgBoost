if(BUILD_TESTING)
	set(TESTS
		AddArgtype
		Construct
		ConstructBound
		IsOperatorAvailable
		OperationArity)


	include_directories(${Boost_INCLUDE_DIRS} ${OPENSCENEGRAPH_INCLUDE_DIRS})
	include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../osgTraits")
	add_custom_target(osgBoost_tests)

	foreach(TEST ${TESTS})
		set(stem "osgBoost_test_${TEST}")
		add_executable(${stem} ${TEST}.cpp)
		target_link_libraries(${stem} ${OPENSCENEGRAPH_LIBRARIES})
		add_test(NAME ${stem}_executes
			COMMAND $<TARGET_FILE:${stem}>)
		set_target_properties(${stem} PROPERTIES FOLDER "osgBoost Tests")
		add_dependencies(osgBoost_tests ${stem})
	endforeach()

	add_custom_target(osgBoost_headercompile)

	file(GLOB ALL_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/../osgTraits" "${CMAKE_CURRENT_SOURCE_DIR}/../osgTraits/*.h")
	set(HEADERS ${ALL_HEADERS})
	set(BLACKLISTED_HEADERS
		Division.h
		Equality.h
		LessThan.h
		Multiplication.h
		Pow.h
		Subtraction.h
		UnaryMinus.h)
	message(STATUS "Not attempting to build headers ${BLACKLISTED_HEADERS}")
	list(REMOVE_ITEM HEADERS ${BLACKLISTED_HEADERS})

	foreach(HEADER ${HEADERS})
		string(REPLACE ".h" "" SHORTNAME "${HEADER}")
		set(stem "test_osgBoost_headercompile_${SHORTNAME}")
		configure_file(test_headercompile.cpp.in "${CMAKE_CURRENT_BINARY_DIR}/${stem}.cpp" @ONLY)

		add_executable(${stem} "${CMAKE_CURRENT_BINARY_DIR}/${stem}.cpp")
		target_link_libraries(${stem} ${OPENSCENEGRAPH_LIBRARIES})
		add_test(${stem}_executes ${stem})
		set_target_properties(${stem} PROPERTIES FOLDER "osgBoost Tests")
		add_dependencies(osgBoost_headercompile ${stem})
	endforeach()


endif()
