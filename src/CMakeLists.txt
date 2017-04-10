cmake_minimum_required(VERSION 3.5)

set(
	source_list
	"data_structures/bin_heap/bin_heap.h"
	"data_structures/bin_heap/bin_heap_impl.h"

	"data_structures/bin_tree/bin_tree.h"
	"data_structures/bin_tree/bin_tree_impl.h"

	"data_structures/hash_table/hash_table.h"
	"data_structures/hash_table/hash_table_impl.h"
	
	"1_intro/part_one.h"
	"2_sorting/part_two.h"
	"3_search/part_three.h"
	"main.cpp"
)

add_executable(${PROJECT_NAME} ${source_list})

foreach(source IN LISTS source_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()
