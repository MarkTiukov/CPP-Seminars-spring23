add_executable(sem15-malloc memory/malloc.cpp)
add_executable(sem15-simple-new memory/simple_new.cpp)
add_executable(sem15-new-overloading memory/operator_new.cpp)

add_executable(sem15-simple-allocator allocators/simple_allocator.cpp)
add_executable(sem15-pool-allocator allocators/stupid_pool_allocator.cpp)
add_executable(sem15-usable-allocator allocators/allocator_for_container.cpp)
