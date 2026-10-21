cmake_minimum_required(VERSION 3.22)

if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "Build Universal Binary for macOS" FORCE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum macOS version" FORCE)
endif()

project(ProLoFi VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================================
# 1. Pure C++ DSP Library (Reverse-engineered Pro Tools Lo-Fi Algorithm)
#    Builds without any external dependencies.
# ============================================================================
add_library(ProLoFiDSP STATIC
    Source/AAX_Original/LoFiAlgMono_Decompiled.cpp
    Source/AAX_Original/LoFi_EffectParameters.cpp
    Source/DSP/LoFiDSP.cpp
)
target_include_directories(ProLoFiDSP PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Source
)
if(MSVC)
    target_compile_definitions(ProLoFiDSP PRIVATE NOMINMAX _USE_MATH_DEFINES)
endif()

# Standalone CLI / Verification test target
add_executable(ProLoFiDSPTest
    Tests/test_lofi_dsp.cpp
)
target_link_libraries(ProLoFiDSPTest PRIVATE ProLoFiDSP)

# ============================================================================
# 2. Optional JUCE Plugin Target (VST3 / AU / Standalone)
#    Automatically enabled if JUCE is provided via -DJUCE_DIR=/path/to/JUCE
#    or automatically fetched via FetchContent if not found locally.
# ============================================================================
option(PROLOFI_FETCH_JUCE "Fetch JUCE 7.0.12 from GitHub to build VST3/AU/Standalone" OFF)

if(NOT DEFINED JUCE_DIR)
    set(JUCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../JUCE")
endif()

if(NOT PROLOFI_FETCH_JUCE AND EXISTS "${JUCE_DIR}/CMakeLists.txt")
    add_subdirectory("${JUCE_DIR}" JUCE EXCLUDE_FROM_ALL)
    set(PROLOFI_HAS_JUCE TRUE)
else()
    include(FetchContent)
    FetchContent_Declare(
        JUCE
        GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
        GIT_TAG        7.0.12
    )
    FetchContent_MakeAvailable(JUCE)
    set(PROLOFI_HAS_JUCE TRUE)
endif()

if(NOT DEFINED PROLOFI_COPY_AFTER_BUILD)
    if(APPLE)
        set(PROLOFI_COPY_AFTER_BUILD ON)
    else()
        set(PROLOFI_COPY_AFTER_BUILD OFF)
    endif()
endif()

if(PROLOFI_HAS_JUCE)
    if(APPLE)
        set(PROFI_PLUGIN_FORMATS AU VST3 Standalone)
    else()
        set(PROFI_PLUGIN_FORMATS VST3 Standalone)
    endif()

    juce_add_plugin(ProLoFi
        COMPANY_NAME                "MORI Sounds"
        BUNDLE_ID                   "com.morisounds.profi"
        PLUGIN_MANUFACTURER_CODE    Mori
        PLUGIN_CODE                 PrFi
        FORMATS                     ${PROFI_PLUGIN_FORMATS}
        PRODUCT_NAME                "Pro-Fi"
        IS_SYNTH                    FALSE
        NEEDS_MIDI_INPUT            FALSE
        NEEDS_MIDI_OUTPUT           FALSE
        IS_MIDI_EFFECT              FALSE
        COPY_PLUGIN_AFTER_BUILD     ${PROLOFI_COPY_AFTER_BUILD}
    )

    target_sources(ProLoFi PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp
        Source/ProFiBinaryData.cpp
    )

    target_compile_definitions(ProLoFi PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
    )

    if(MSVC)
        target_compile_definitions(ProLoFi PRIVATE NOMINMAX _USE_MATH_DEFINES)
    endif()

    target_link_libraries(ProLoFi PRIVATE
        ProLoFiDSP
        juce::juce_audio_utils
        juce::juce_dsp
    )
endif()
