#ifndef CMAKE_HH
#define CMAKE_HH

#include <string_view>
#include <cstddef>

namespace cmake {
    inline constexpr std::string_view project_name        = "${PROJECT_NAME}";
    inline constexpr std::string_view project_description = "${PROJECT_DESCRIPTION}";
    inline constexpr std::string_view project_version     = "${PROJECT_VERSION}";

    inline constexpr std::string_view project_ver_major   = "${PROJECT_VERSION_MAJOR}";
    inline constexpr std::string_view project_ver_minor   = "${PROJECT_VERSION_MINOR}";
    inline constexpr std::string_view project_ver_patch   = "${PROJECT_VERSION_PATCH}";

    inline constexpr std::string_view project_fmt         = "${PROJECT_NAME}  Version ${PROJECT_VERSION}  Copyright (C) 2023  vzze\n\n";
    inline constexpr std::string_view project_copyright   = "Copyright (C) 2023  vzze";
}

#endif
