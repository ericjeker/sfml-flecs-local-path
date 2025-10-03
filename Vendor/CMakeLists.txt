add_library(Vendor INTERFACE)

message("--- Using SFE from submodule")
add_subdirectory(sfml-flecs-engine)

target_link_libraries(Vendor INTERFACE SFE::Core)
