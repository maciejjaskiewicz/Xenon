function(set_standard_pch project_name)

    set(STD_PCH_HEADERS
        <cstdint>
        <string>
        <sstream>
        <memory>
        <utility>
        <algorithm>
        <functional>
        <array>
        <vector>
        <unordered_map>
        <unordered_set>
    )

    target_precompile_headers(${project_name} INTERFACE ${STD_PCH_HEADERS})

endfunction()