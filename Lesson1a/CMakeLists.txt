cmake_minimum_required(VERSION 3.20)
project(Lesson1a LANGUAGES CXX RC)

# 추가 구성(Hybrid) 지원 - 기존 멀티 구성 제너레이터에서만 의미 있음
if (CMAKE_CONFIGURATION_TYPES)
    list(APPEND CMAKE_CONFIGURATION_TYPES Hybrid)
    list(REMOVE_DUPLICATES CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "" FORCE)
endif()


# ===================== 사용자 조정 가능 변수 =====================
# 3ds Max SDK 루트 (maxsdk 바로 위 경로 아님: maxsdk 포함 경로 지정)
set(ADSK_3DSMAX_SDK_2024 "C:/Program Files/Autodesk/3ds Max 2024 SDK/maxsdk" CACHE PATH "3ds Max SDK root (contains include, lib 등)")
# (선택) 3ds Max 설치 루트 - 설정 시 빌드 후 플러그인 자동 복사
set(ADSK_3DSMAX_x64_2024 "C:/Program Files/Autodesk/3ds Max 2024" CACHE PATH "3ds Max root for optional deployment")
# Qt 위치 (Qt5Config.cmake 있는 곳). 이미 환경에 맞춰 수정.
set(Qt5_DIR "C:/QtGit/install/lib/cmake/Qt5" CACHE PATH "Qt5 Config path")

# ===================== 기본 컴파일 설정 =====================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    # 3ds Max 와 런타임 호환성 확보 (/MD)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    # 디버그 가독성 향상 (필요 시 조정)
    foreach(cfg Debug RelWithDebInfo)
        string(TOUPPER ${cfg} CFGU)
        set(CMAKE_CXX_FLAGS_${CFGU} "${CMAKE_CXX_FLAGS_${CFGU}} /Zc:__cplusplus /permissive- /MP")
    endforeach()
    set(CMAKE_PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()

# Qt 자동 처리 (moc/uic)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

list(APPEND CMAKE_PREFIX_PATH "${Qt5_DIR}/..")
# Qt 5.15.x 전체 허용 (정확히 5.15.1이 아니어도)
find_package(Qt5 5.15 COMPONENTS Core Gui Widgets REQUIRED)

# =============== 소스 / 리소스 ===============
set(PLUGIN_SOURCES
    DllEntry.cpp
    Lesson1a.cpp
    QtPluginRollup.cpp
    QtPluginRollup.h
    resource.h
    Lesson1a.rc
    plugin_form.ui
)

add_library(Lesson1a SHARED ${PLUGIN_SOURCES})

# =============== 포함 경로 ===============
target_include_directories(Lesson1a
    PRIVATE
        "${ADSK_3DSMAX_SDK_2024}/include"
        "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.29.30133/atlmfc/include"
)

# =============== 구성별 라이브러리 경로 ===============
link_directories("${ADSK_3DSMAX_SDK_2024}/lib/x64/Release")
# 3ds Max SDK 는 통상 lib/x64/Release, lib/x64/Debug 구조 (Debug 폴더 없을 수도 있음)
set(_max_lib_base "${ADSK_3DSMAX_SDK_2024}/lib/x64")
target_link_directories(
    Lesson1a PRIVATE "${ADSK_3DSMAX_SDK_2024}/lib/x64/Release"
)
# foreach(_cfg IN ITEMS Debug Release RelWithDebInfo MinSizeRel Hybrid)
#     string(TOLOWER "${_cfg}" _lcfg)
#     if (EXISTS "${_max_lib_base}/Release/core.lib")
#         # Release 및 Hybrid(커스텀) 구성도 Release 라이브러리 폴더 사용
#         target_link_directories(Lesson1a PRIVATE $<$<CONFIG:${_cfg}>:${_max_lib_base}/Release>)
#     endif()
#     if (EXISTS "${_max_lib_base}/Debug/core.lib")
#         target_link_directories(Lesson1a PRIVATE $<$<CONFIG:Debug>:${_max_lib_base}/Debug>)
#     endif()
# endforeach()

# =============== 컴파일 정의 ===============
target_compile_definitions(Lesson1a
    PRIVATE
        UNICODE _UNICODE
        WIN32 _WINDOWS
        NOMINMAX
        _CRT_SECURE_NO_WARNINGS
        _USRDLL
        QT_NO_UNICODE_LITERAL
        WINVER=0x0601
        _WIN32_WINNT=0x0601
        _WIN32_WINDOWS=0x0601
        _WIN32_IE=0x0800
        ISOLATION_AWARE_ENABLED=1
        $<$<CONFIG:Hybrid>:_HYBRID;IS_HYBRID>
)

# =============== 링크 라이브러리 ===============
target_link_libraries(Lesson1a
    PRIVATE
        bmm.lib
        core.lib
        geom.lib
        gfx.lib
        mesh.lib
        maxutil.lib
        maxscrpt.lib
        gup.lib
        Paramblk2.lib
        CustDlg.lib
        SkinEngine.lib
        Qt5::Core Qt5::Gui Qt5::Widgets
)

# MSVC 전용: UTF-8 소스/실행 문자 집합 지정 (C4819 경고 억제)
if (MSVC)
    target_compile_options(Lesson1a PRIVATE /utf-8 /wd4828)
endif()

# =============== 출력 속성 ===============
set_target_properties(Lesson1a PROPERTIES
    OUTPUT_NAME "lesson1a"    # .vcxproj TargetName 에 맞춤 (소문자)
    SUFFIX ".dlu"            # Utility Plug-in 확장자
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LINK_FLAGS "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/Lesson1a.def"
)

# Hybrid 구성 전용 (Release 최적화 + 디버그 심볼) 옵션 예시
if (MSVC)
    target_compile_options(Lesson1a PRIVATE $<$<CONFIG:Hybrid>:/O2 /Zi>)
    target_link_options(Lesson1a PRIVATE $<$<CONFIG:Hybrid>:/DEBUG>)
endif()

# =============== 선택적: 플러그인 배포 설정 ===============
option(AUTO_DEPLOY_PLUGIN "Build 후 사용자 플러그인 폴더에 자동 복사" ON)
option(INSTALL_TO_MAX_ROOT "Program Files 아래 3ds Max 설치 폴더로도 복사 (관리자 권한 필요)" OFF)
set(THREEDS_MAX_VERSION "2024" CACHE STRING "3ds Max version string for user plugin path (예: 2024)")
set(THREEDS_MAX_PLUGIN_SUBDIR "plugins" CACHE STRING "Plugins subdirectory inside 3ds Max root")

if (WIN32)
    # 사용자 로컬 플러그인 경로 (예: %LOCALAPPDATA%/Autodesk/3dsMax/2024 - 64bit/Plugins)
    if(NOT DEFINED THREEDS_MAX_USER_PLUGIN_DIR)
        set(_default_user_plugin_dir "$ENV{LOCALAPPDATA}/Autodesk/3dsMax/${THREEDS_MAX_VERSION} - 64bit/Plugins")
        set(THREEDS_MAX_USER_PLUGIN_DIR "${_default_user_plugin_dir}" CACHE PATH "User 3ds Max plugins directory" FORCE)
    endif()
endif()

add_custom_target(deploy ALL COMMENT "Aggregate target (does nothing by itself unless AUTO_DEPLOY_PLUGIN/INSTALL_TO_MAX_ROOT enabled)")
add_dependencies(deploy Lesson1a)

if (AUTO_DEPLOY_PLUGIN AND THREEDS_MAX_USER_PLUGIN_DIR)
    add_custom_command(TARGET Lesson1a POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${THREEDS_MAX_USER_PLUGIN_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:Lesson1a>" "${THREEDS_MAX_USER_PLUGIN_DIR}/$<TARGET_FILE_NAME:Lesson1a>"
        COMMENT "Copying Lesson1a.dlu to user plugins folder: ${THREEDS_MAX_USER_PLUGIN_DIR}")
endif()

if (INSTALL_TO_MAX_ROOT AND EXISTS "${THREEDS_MAX_ROOT}")
    add_custom_command(TARGET Lesson1a POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${THREEDS_MAX_ROOT}/${THREEDS_MAX_PLUGIN_SUBDIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:Lesson1a>" "${THREEDS_MAX_ROOT}/${THREEDS_MAX_PLUGIN_SUBDIR}/$<TARGET_FILE_NAME:Lesson1a>"
        COMMENT "Copying Lesson1a.dlu to 3ds Max install plugins folder (may need admin): ${THREEDS_MAX_ROOT}/${THREEDS_MAX_PLUGIN_SUBDIR}")
elseif(INSTALL_TO_MAX_ROOT)
    message(WARNING "INSTALL_TO_MAX_ROOT=ON 이지만 THREEDS_MAX_ROOT 경로가 존재하지 않음: ${THREEDS_MAX_ROOT}")
endif()

# =============== 선택적: Qt DLL 배포 (windeployqt 사용) ===============
option(DEPLOY_QT_RUNTIME "Run windeployqt for produced binary" OFF)
if (DEPLOY_QT_RUNTIME)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${Qt5_DIR}/../../../bin" "${Qt5_DIR}/../../bin")
    if (WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET Lesson1a POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}" --no-translations --no-compiler-runtime "$<TARGET_FILE:Lesson1a>"
            COMMENT "Running windeployqt to deploy Qt dependencies next to plugin (may copy many files)"
        )
    else()
        message(WARNING "windeployqt 실행 파일을 찾을 수 없습니다. Qt 런타임 복사가 생략됩니다.")
    endif()
endif()

message(STATUS "3ds Max SDK: ${ADSK_3DSMAX_SDK_2024}")
message(STATUS "3ds Max Root: ${ADSK_3DSMAX_x64_2024}")
message(STATUS "Qt5 DIR: ${Qt5_DIR}")
