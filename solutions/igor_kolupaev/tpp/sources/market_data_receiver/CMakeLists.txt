
find_package( Boost ${SEARCH_PARAMETERS} COMPONENTS
	filesystem
	regex
	program_options
	system
	date_time
	thread
	chrono
)

find_package( system_utilities ${SEARCH_PARAMETERS} COMPONENTS
	logger
	file_logger
	system_processor
	property_reader
) 

compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries multicast_communication Boost system_utilities )

