# Copyright (C) 2024 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Find "ModuleTools" dependencies, which are other ModuleTools packages.
set(Qt6QtOpcUaTools_FOUND FALSE)
set(__qt_QtOpcUaTools_tool_deps "")
foreach(__qt_QtOpcUaTools_target_dep ${__qt_QtOpcUaTools_tool_deps})
    list(GET __qt_QtOpcUaTools_target_dep 0 __qt_QtOpcUaTools_pkg)
    list(GET __qt_QtOpcUaTools_target_dep 1 __qt_QtOpcUaTools_version)

    if (NOT ${__qt_QtOpcUaTools_pkg}_FOUND)
        find_dependency(${__qt_QtOpcUaTools_pkg} ${__qt_QtOpcUaTools_version})
    endif()
endforeach()

set(Qt6QtOpcUaTools_FOUND TRUE)
