#===-- ParallelSTLConfig.cmake.in ----------------------------------------===##
#
# Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#
#===----------------------------------------------------------------------===##

include(CMakeFindDependencyMacro)

set(PSTL_PARALLEL_BACKEND "serial")

if (PSTL_PARALLEL_BACKEND STREQUAL "tbb")
    find_dependency(TBB REQUIRED tbb)
endif()

if (NOT TARGET pstl::ParallelSTL)
    include("${CMAKE_CURRENT_LIST_DIR}/ParallelSTLTargets.cmake")
endif()
