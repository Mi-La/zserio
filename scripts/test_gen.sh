#!/bin/bash

SCRIPT_DIR=`dirname $0`
source "${SCRIPT_DIR}/common_test_tools.sh"
source "${SCRIPT_DIR}/test_zs.sh"

# Check generator report.
check()
{
    exit_if_argc_ne $# 3
    local TEST_OUT_DIR="$1"; shift
    local GENERATOR="$1"; shift
    local REPORT="$1"; shift

    local ZSERIO_LOG="${TEST_OUT_DIR}"/zserio_log.txt

    if [[ "${GENERATOR}" != "" ]] ; then
        echo -ne "Checking ${GENERATOR} report..."
        local ACTUAL=$(grep -A1 "${GENERATOR}" "${ZSERIO_LOG}" | tail -n 1)
        echo "${ACTUAL}" | grep -q "${REPORT}"
        if [ $? -ne 0 ] ; then
            stderr_echo "Unexpected generator report!"
            echo "Expected: ${REPORT}"
            echo "Actual: ${ACTUAL}"
            return 1
        fi
        echo "OK"
    fi

    return 0
}

# Run zserio generators tests.
test_gen()
{
    exit_if_argc_ne $# 9
    local UNPACKED_ZSERIO_RELEASE_DIR="$1"; shift
    local ZSERIO_PROJECT_ROOT="$1"; shift
    local ZSERIO_BUILD_DIR="$1"; shift
    local TEST_OUT_DIR="$1"; shift
    local MSYS_WORKAROUND_TEMP=("${!1}"); shift
    local CPP_TARGETS=("${MSYS_WORKAROUND_TEMP[@]}")
    local PARAM_JAVA="$1"; shift
    local PARAM_PYTHON="$1"; shift
    local PARAM_XML="$1"; shift
    local PARAM_DOC="$1"; shift

    local TEST_NAME="gif"
    local TEST_ZS_DIR="${TEST_OUT_DIR}/gif"
    local TEST_ZS_MAIN="gif.zs"
    rm -rf "${TEST_ZS_DIR}"
    cp -r "${ZSERIO_PROJECT_ROOT}/test/others/gif/zs" "${TEST_ZS_DIR}"

    local SWITCH_WERROR=1

    local JAVA_GENERATOR
    if [ ${PARAM_JAVA} -ne 0 ] ; then
        local JAVA_GENERATOR="Java Generator"
    fi

    local CPP_GENERATOR
    if [ ${#CPP_TARGETS[@]} -ne 0 ] ; then
        local CPP_GENERATOR="C++11 Generator"
    fi

    local PYTHON_GENERATOR
    if [ ${PARAM_PYTHON} -ne 0 ] ; then
        local PYTHON_GENERATOR="Python Generator"
    fi

    local DOC_GENERATOR
    if [ ${PARAM_DOC} -ne 0 ] ; then
        local DOC_GENERATOR="Doc Generator"
    fi

    local XML_GENERATOR
    if [ ${PARAM_XML} -ne 0 ] ; then
        local XML_GENERATOR="XML Generator"
    fi

    echo "First time generation"
    echo

    # make sure that just copied source will be at least 1s older than output newly generated by this test
    # (needed by "repeated generation" test to produce expected report)
    sleep 1

    local CLEAN=1
    test_zs "${UNPACKED_ZSERIO_RELEASE_DIR}" "${ZSERIO_PROJECT_ROOT}" "${ZSERIO_BUILD_DIR}" "${TEST_OUT_DIR}" \
            PARAM_CPP_TARGET_ARRAY[@] ${PARAM_JAVA} ${PARAM_PYTHON} ${PARAM_XML} ${PARAM_DOC} \
            "${TEST_ZS_DIR}" "${TEST_ZS_MAIN}" "${TEST_NAME}" ${SWITCH_WERROR} ${CLEAN}
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${JAVA_GENERATOR}" "Generated 23 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${CPP_GENERATOR}" "Generated 29 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${PYTHON_GENERATOR}" "Generated 35 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${XML_GENERATOR}" "Generated 1 file"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${DOC_GENERATOR}" "Generated 34 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    echo
    echo "Repeated generation"
    echo

    CLEAN=0
    test_zs "${UNPACKED_ZSERIO_RELEASE_DIR}" "${ZSERIO_PROJECT_ROOT}" "${ZSERIO_BUILD_DIR}" "${TEST_OUT_DIR}" \
            PARAM_CPP_TARGET_ARRAY[@] ${PARAM_JAVA} ${PARAM_PYTHON} ${PARAM_XML} ${PARAM_DOC} \
            "${TEST_ZS_DIR}" "${TEST_ZS_MAIN}" "${TEST_NAME}" ${SWITCH_WERROR} ${CLEAN}
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${JAVA_GENERATOR}" "Generated 0 files, skipped 23 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${CPP_GENERATOR}" "Generated 0 files, skipped 29 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${PYTHON_GENERATOR}" "Generated 0 files, skipped 35 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${XML_GENERATOR}" "Generated 1 file"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${DOC_GENERATOR}" "Generated 34 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    echo
    echo "Repeated generation, newer sources"
    echo

    # touch some inner source file
    touch "${TEST_ZS_DIR}/gif/gif_data.zs"

    # make sure that just touched source will be at least 1s older than output newly generated by this test
    # (needed by "missing ouptut" test to produce expected report)
    sleep 1

    CLEAN=0
    test_zs "${UNPACKED_ZSERIO_RELEASE_DIR}" "${ZSERIO_PROJECT_ROOT}" "${ZSERIO_BUILD_DIR}" "${TEST_OUT_DIR}" \
            PARAM_CPP_TARGET_ARRAY[@] ${PARAM_JAVA} ${PARAM_PYTHON} ${PARAM_XML} ${PARAM_DOC} \
            "${TEST_ZS_DIR}" "${TEST_ZS_MAIN}" "${TEST_NAME}" ${SWITCH_WERROR} ${CLEAN}
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${JAVA_GENERATOR}" "Generated 23 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${CPP_GENERATOR}" "Generated 29 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${PYTHON_GENERATOR}" "Generated 35 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${XML_GENERATOR}" "Generated 1 file"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${DOC_GENERATOR}" "Generated 34 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    echo
    echo "Repeated generation, missing output"
    echo

    # remove one output file
    if [[ "${JAVA_GENERATOR}" != "" ]] ; then
        rm "${TEST_OUT_DIR}/java/gen/gif/gif_data/GifData.java"
    fi
    if [[ "${CPP_GENERATOR}" != "" ]] ; then
        rm "${TEST_OUT_DIR}/cpp/gen/gif/gif_data/GifData.cpp"
    fi
    if [[ "${PYTHON_GENERATOR}" != "" ]] ; then
        rm "${TEST_OUT_DIR}/python/gen/gif/gif_data/gif_data.py"
    fi
    if [[ "${XML_GENERATOR}" != "" ]] ; then
        rm "${TEST_OUT_DIR}/xml/abstract_syntax_tree.xml"
    fi
    if [[ "${DOC_GENERATOR}" != "" ]] ; then
        rm "${TEST_OUT_DIR}/doc/css/stylesheet.css"
    fi

    CLEAN=0
    test_zs "${UNPACKED_ZSERIO_RELEASE_DIR}" "${ZSERIO_PROJECT_ROOT}" "${ZSERIO_BUILD_DIR}" "${TEST_OUT_DIR}" \
            PARAM_CPP_TARGET_ARRAY[@] ${PARAM_JAVA} ${PARAM_PYTHON} ${PARAM_XML} ${PARAM_DOC} \
            "${TEST_ZS_DIR}" "${TEST_ZS_MAIN}" "${TEST_NAME}" ${SWITCH_WERROR} ${CLEAN}
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${JAVA_GENERATOR}" "Generated 1 file, skipped 22 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${CPP_GENERATOR}" "Generated 1 file, skipped 28 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${PYTHON_GENERATOR}" "Generated 1 file, skipped 34 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${XML_GENERATOR}" "Generated 1 file"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${DOC_GENERATOR}" "Generated 34 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    echo
    echo "Repeated generation, add switch -withoutSourcesAmalgamation"
    echo

    # C++ note: Almalgamated C++ files will be overriden by newly generated sources thanks to well choosen
    #           example to compile. It's enough to remove just one Gif.cpp which will not be newly generated.
    if [[ "${CPP_GENERATOR}" != "" ]] ; then
        rm "${TEST_OUT_DIR}/cpp/gen/gif/Gif.cpp"
    fi

    CLEAN=0
    ZSERIO_EXTRA_ARGS="-withoutSourcesAmalgamation" \
    test_zs "${UNPACKED_ZSERIO_RELEASE_DIR}" "${ZSERIO_PROJECT_ROOT}" "${ZSERIO_BUILD_DIR}" "${TEST_OUT_DIR}" \
            PARAM_CPP_TARGET_ARRAY[@] ${PARAM_JAVA} ${PARAM_PYTHON} ${PARAM_XML} ${PARAM_DOC} \
            "${TEST_ZS_DIR}" "${TEST_ZS_MAIN}" "${TEST_NAME}" ${SWITCH_WERROR} ${CLEAN}
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${JAVA_GENERATOR}" "Generated 0 files, skipped 23 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${CPP_GENERATOR}" "Generated 46 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${PYTHON_GENERATOR}" "Generated 0 files, skipped 35 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${XML_GENERATOR}" "Generated 1 file"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${DOC_GENERATOR}" "Generated 34 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    echo
    echo "Repeated generation, add switch -withRangeCheckCode"
    echo

    CLEAN=0
    ZSERIO_EXTRA_ARGS="-withoutSourcesAmalgamation -withRangeCheckCode" \
    test_zs "${UNPACKED_ZSERIO_RELEASE_DIR}" "${ZSERIO_PROJECT_ROOT}" "${ZSERIO_BUILD_DIR}" "${TEST_OUT_DIR}" \
            PARAM_CPP_TARGET_ARRAY[@] ${PARAM_JAVA} ${PARAM_PYTHON} ${PARAM_XML} ${PARAM_DOC} \
            "${TEST_ZS_DIR}" "${TEST_ZS_MAIN}" "${TEST_NAME}" ${SWITCH_WERROR} ${CLEAN}
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${JAVA_GENERATOR}" "Generated 23 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${CPP_GENERATOR}" "Generated 46 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${PYTHON_GENERATOR}" "Generated 35 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${XML_GENERATOR}" "Generated 1 file"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    check "${TEST_OUT_DIR}" "${DOC_GENERATOR}" "Generated 34 files"
    if [ $? -ne 0 ] ; then
        return 1
    fi

    return 0
}

# Print help message.
print_help()
{
    cat << EOF
Description:
    Tests given zserio sources with zserio release compiled in release-ver directory.

Usage:
    $0 [-h] [-e] [-p] [-o <dir>] generator...

Arguments:
    -h, --help            Show this help.
    -e, --help-env        Show help for enviroment variables.
    -p, --purge           Purge test build directory.
    -o <dir>, --output-directory <dir>
                          Output directory where tests will be run.
    generator             Specify the generator to test.

Generator can be:
    cpp-linux32           Generate C++ sources and compile them for linux32 target (GCC).
    cpp-linux64           Generate C++ sources and compile them for for linux64 target (GCC).
    cpp-windows32-mingw   Generate C++ sources and compile them for for windows32 target (MinGW).
    cpp-windows64-mingw   Generate C++ sources and compile them for for windows64 target (MinGW64).
    cpp-windows32-msvc    Generate C++ sources and compile them for for windows32 target (MSVC).
    cpp-windows64-msvc    Generate C++ sources and compile them for for windows64 target (MSVC).
    java                  Generate Java sources and compile them.
    python                Generate python sources.
    xml                   Generate XML.
    doc                   Generate HTML documentation.
    all-linux32           Test all generators and compile all possible linux32 sources (GCC).
    all-linux64           Test all generators and compile all possible linux64 sources (GCC).
    all-windows32-mingw   Test all generators and compile all possible windows32 sources (MinGW).
    all-windows64-mingw   Test all generators and compile all possible windows64 sources (MinGW64).
    all-windows32-msvc    Test all generators and compile all possible windows32 sources (MSVC).
    all-windows64-msvc    Test all generators and compile all possible windows64 sources (MSVC).

Examples:
    $0 cpp-linux64 java python xml doc
    $0 all-linux64
EOF
}

# Parse all command line arguments.
#
# Return codes:
# -------------
# 0 - Success. Arguments have been successfully parsed.
# 1 - Failure. Some arguments are wrong or missing.
# 2 - Help switch is present. Arguments after help switch have not been checked.
parse_arguments()
{
    exit_if_argc_lt $# 7
    local PARAM_CPP_TARGET_ARRAY_OUT="$1"; shift
    local PARAM_JAVA_OUT="$1"; shift
    local PARAM_PYTHON_OUT="$1"; shift
    local PARAM_XML_OUT="$1"; shift
    local PARAM_DOC_OUT="$1"; shift
    local PARAM_OUT_DIR_OUT="$1"; shift
    local SWITCH_PURGE_OUT="$1"; shift

    eval ${PARAM_JAVA_OUT}=0
    eval ${PARAM_PYTHON_OUT}=0
    eval ${PARAM_XML_OUT}=0
    eval ${PARAM_DOC_OUT}=0
    eval ${SWITCH_PURGE_OUT}=0

    local NUM_PARAMS=0
    local PARAM_ARRAY=()
    local ARG="$1"
    while [ -n "${ARG}" ] ; do
        case "${ARG}" in
            "-h" | "--help")
                return 2
                ;;

            "-e" | "--help-env")
                return 3
                ;;

            "-p" | "--purge")
                eval ${SWITCH_PURGE_OUT}=1
                shift
                ;;

            "-o" | "--output-directory")
                eval ${PARAM_OUT_DIR_OUT}="$2"
                shift 2
                ;;

            "-"*)
                stderr_echo "Invalid switch ${ARG}!"
                echo
                return 1
                ;;

            *)
                PARAM_ARRAY[NUM_PARAMS]=${ARG}
                NUM_PARAMS=$((NUM_PARAMS + 1))
                shift
                ;;
        esac
        ARG="$1"
    done

    local NUM_CPP_TARGETS=0
    local PARAM
    for PARAM in "${PARAM_ARRAY[@]}" ; do
        case "${PARAM}" in
            "cpp-linux32" | "cpp-linux64" | "cpp-windows32-"* | "cpp-windows64-"*)
                eval ${PARAM_CPP_TARGET_ARRAY_OUT}[${NUM_CPP_TARGETS}]="${PARAM#cpp-}"
                NUM_CPP_TARGETS=$((NUM_CPP_TARGETS + 1))
                ;;

            "java")
                eval ${PARAM_JAVA_OUT}=1
                ;;

            "python")
                eval ${PARAM_PYTHON_OUT}=1
                ;;

            "xml")
                eval ${PARAM_XML_OUT}=1
                ;;

            "doc")
                eval ${PARAM_DOC_OUT}=1
                ;;

            "all-linux32" | "all-linux64" | "all-windows32-"* | "all-windows64-"*)
                eval ${PARAM_CPP_TARGET_ARRAY_OUT}[${NUM_CPP_TARGETS}]="${PARAM#all-}"
                eval ${PARAM_JAVA_OUT}=1
                eval ${PARAM_PYTHON_OUT}=1
                eval ${PARAM_XML_OUT}=1
                eval ${PARAM_DOC_OUT}=1
                NUM_CPP_TARGETS=$((NUM_CPP_TARGETS + 1))
                ;;

            *)
                stderr_echo "Invalid argument ${PARAM}!"
                echo
                return 1
        esac
    done

    if [[ ${NUM_CPP_TARGETS} -eq 0 &&
          ${!PARAM_JAVA_OUT} == 0 &&
          ${!PARAM_PYTHON_OUT} == 0 &&
          ${!PARAM_XML_OUT} == 0 &&
          ${!PARAM_DOC_OUT} == 0 &&
          ${!SWITCH_PURGE_OUT} == 0 ]] ; then
        stderr_echo "Generator to test is not specified!"
        echo
        return 1
    fi

    return 0
}

main()
{
    # get the project root, absolute path is necessary only for CMake
    local ZSERIO_PROJECT_ROOT
    convert_to_absolute_path "${SCRIPT_DIR}/.." ZSERIO_PROJECT_ROOT

    # parse command line arguments
    local PARAM_CPP_TARGET_ARRAY=()
    local PARAM_JAVA
    local PARAM_PYTHON
    local PARAM_XML
    local PARAM_DOC
    local PARAM_OUT_DIR="${ZSERIO_PROJECT_ROOT}"
    local SWITCH_PURGE
    parse_arguments PARAM_CPP_TARGET_ARRAY PARAM_JAVA PARAM_PYTHON PARAM_XML PARAM_DOC PARAM_OUT_DIR \
                    SWITCH_PURGE $@
    local PARSE_RESULT=$?
    if [ ${PARSE_RESULT} -eq 2 ] ; then
        print_help
        return 0
    elif [ ${PARSE_RESULT} -eq 3 ] ; then
        print_test_help_env
        print_test_zs_help_env
        print_help_env
        return 0
    elif [ ${PARSE_RESULT} -ne 0 ] ; then
        return 1
    fi

    echo "Testing generators repeated execution."
    echo

    # set global variables
    set_global_common_variables
    if [ $? -ne 0 ] ; then
        return 1
    fi

    set_test_global_variables
    if [ $? -ne 0 ] ; then
        return 1
    fi

    set_test_zs_global_variables
    if [ $? -ne 0 ] ; then
        return 1
    fi

    if [[ ${#PARAM_CPP_TARGET_ARRAY[@]} -ne 0 ]] ; then
        set_global_cpp_variables
        if [ $? -ne 0 ] ; then
            return 1
        fi
    fi

    if [[ ${PARAM_JAVA} != 0 ]] ; then
        set_global_java_variables
        if [ $? -ne 0 ] ; then
            return 1
        fi
    fi

    if [[ ${PARAM_PYTHON} != 0 ]] ; then
        set_global_python_variables "${ZSERIO_PROJECT_ROOT}"
        if [ $? -ne 0 ] ; then
            return 1
        fi
    fi

    if [[ ${PARAM_DOC} != 0 ]] ; then
        set_global_doc_variables
        if [ $? -ne 0 ] ; then
            return 1
        fi
    fi

    # purge if requested and then create test output directory
    local ZSERIO_BUILD_DIR="${PARAM_OUT_DIR}/build"
    local TEST_OUT_DIR="${ZSERIO_BUILD_DIR}/test_gen"
    if [[ ${SWITCH_PURGE} == 1 ]] ; then
        echo "Purging test directory." # purges all tests in test_zs directory
        echo
        rm -rf "${TEST_OUT_DIR}/"

        if [[ ${#PARAM_CPP_TARGET_ARRAY[@]} == 0 &&
              ${PARAM_JAVA} == 0 &&
              ${PARAM_PYTHON} == 0 &&
              ${PARAM_XML} == 0 &&
              ${PARAM_DOC} == 0 ]] ; then
            return 0 # purge only
        fi
    fi
    mkdir -p "${TEST_OUT_DIR}"

    # get zserio release directory
    local ZSERIO_RELEASE_DIR
    local ZSERIO_VERSION
    get_release_dir "${ZSERIO_PROJECT_ROOT}" ZSERIO_RELEASE_DIR ZSERIO_VERSION
    if [ $? -ne 0 ] ; then
        return 1
    fi

    # print information
    echo "Testing release: ${ZSERIO_RELEASE_DIR}"
    echo "Test output directory: ${TEST_OUT_DIR}"
    echo

    # unpack testing release
    local UNPACKED_ZSERIO_RELEASE_DIR
    unpack_release "${TEST_OUT_DIR}" "${ZSERIO_RELEASE_DIR}" "${ZSERIO_VERSION}" UNPACKED_ZSERIO_RELEASE_DIR
    if [ $? -ne 0 ] ; then
        return 1
    fi

    # run test
    test_gen "${UNPACKED_ZSERIO_RELEASE_DIR}" "${ZSERIO_PROJECT_ROOT}" "${ZSERIO_BUILD_DIR}" "${TEST_OUT_DIR}" \
             PARAM_CPP_TARGET_ARRAY[@] ${PARAM_JAVA} ${PARAM_PYTHON} ${PARAM_XML} ${PARAM_DOC}
    if [ $? -ne 0 ] ; then
        return 1
    fi

    return 0
}

if [[ "${BASH_SOURCE[0]}" == "${0}" ]] ; then
    main "$@"
fi
