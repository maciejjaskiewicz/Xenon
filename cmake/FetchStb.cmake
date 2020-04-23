FetchContent_Declare(
  stb
  GIT_REPOSITORY https://github.com/maciejjaskiewicz/stb.git
)

FetchContent_MakeAvailable(stb)

set_target_properties(stb PROPERTIES FOLDER Vendor)
set_target_properties(stb PROPERTIES PROJECT_LABEL stb)