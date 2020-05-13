FetchContent_Declare(
  ImGui
  GIT_REPOSITORY https://github.com/maciejjaskiewicz/imgui.git
  GIT_TAG origin/docking_tables
)

FetchContent_MakeAvailable(ImGui)

set_target_properties(ImGui PROPERTIES FOLDER Vendor)
set_target_properties(ImGui PROPERTIES PROJECT_LABEL ImGui)