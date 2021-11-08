#!/bin/bash

SCRIPT_DIR=`dirname $0`
source "${SCRIPT_DIR}/common_tools.sh"

# Set and check release global variables.
set_release_global_variables()
{
    exit_if_argc_ne $# 1
    local SWITCH_UPDATE="$1"; shift

    if [[ ${SWITCH_UPDATE} == 0 ]] ; then
        # ZIP to use, defaults to "zip" if not set
        ZIP="${ZIP:-zip}"
        if [ ! -f "`which "${ZIP}"`" ] ; then
            stderr_echo "Cannot find zip! Set ZIP environment variable."
            return 1
        fi
    else
        # GIT to use, defaults to "git" if not set
        GIT="${GIT:-git}"
        if [ ! -f "`which "${GIT}"`" ] ; then
            stderr_echo "Cannot find git! Set GIT environment variable."
            return 1
        fi

        # CMAKE to use, defaults to "cmake" if not set
        CMAKE="${CMAKE:-cmake}"
        if [ ! -f "`which "${CMAKE}"`" ] ; then
            stderr_echo "Cannot find cmake! Set CMAKE environment variable."
            return 1
        fi

        # ANT to use, defaults to "ant" if not set
        ANT="${ANT:-ant}"
        if [ ! -f "`which "${ANT}"`" ] ; then
            stderr_echo "Cannot find cmake! Set ANT environment variable."
            return 1
        fi

        # python to use, defaults to "python3" if not set
        PYTHON="${PYTHON:-python3}"
        if [ ! -f "`which "${PYTHON}"`" ] ; then
            stderr_echo "Cannot find Python! Set PYTHON environment variable."
            return 1
        fi

        # Zserio PyPi directory to use, defaults to "${SCRIPT_DIR}/../../zserio-pypi" if not set
        ZSERIO_PYPI_DIR="${ZSERIO_PYPI_DIR:-${SCRIPT_DIR}/../../zserio-pypi}"
        if [ ! -d "${ZSERIO_PYPI_DIR}" ] ; then
            stderr_echo "Cannot find Zserio PyPi directory! Set ZSERIO_PYPI_DIR environment variable."
            return 1
        fi

        # Zserio Extension Sample directory to use, defaults to "${SCRIPT_DIR}/../../zserio-extension-sample"
        # if not set
        ZSERIO_EXTENSION_SAMPLE_DIR="${ZSERIO_EXTENSION_SAMPLE_DIR:-${SCRIPT_DIR}/../../zserio-extension-sample}"
        if [ ! -d "${ZSERIO_EXTENSION_SAMPLE_DIR}" ] ; then
            stderr_echo "Cannot find Zserio Extension Sample directory! Set ZSERIO_EXTENSION_SAMPLE_DIR" \
                    "environment variable."
            return 1
        fi

        # Zserio Tutorial Cpp directory to use, defaults to "${SCRIPT_DIR}/../../zserio-tutorial-cpp" if not set
        ZSERIO_TUTORIAL_CPP_DIR="${ZSERIO_TUTORIAL_CPP_DIR:-${SCRIPT_DIR}/../../zserio-tutorial-cpp}"
        if [ ! -d "${ZSERIO_TUTORIAL_CPP_DIR}" ] ; then
            stderr_echo "Cannot find Zserio Tutorial Cpp directory! Set ZSERIO_TUTORIAL_CPP_DIR" \
                    "environment variable."
            return 1
        fi

        # Zserio Tutorial Java directory to use, defaults to "${SCRIPT_DIR}/../../zserio-tutorial-java"
        # if not set
        ZSERIO_TUTORIAL_JAVA_DIR="${ZSERIO_TUTORIAL_JAVA_DIR:-${SCRIPT_DIR}/../../zserio-tutorial-java}"
        if [ ! -d "${ZSERIO_TUTORIAL_JAVA_DIR}" ] ; then
            stderr_echo "Cannot find Zserio Tutorial Java directory! Set ZSERIO_TUTORIAL_JAVA_DIR" \
                    "environment variable."
            return 1
        fi

        # Zserio Tutorial Python directory to use, defaults to "${SCRIPT_DIR}/../../zserio-tutorial-python"
        # if not set
        ZSERIO_TUTORIAL_PYTHON_DIR="${ZSERIO_TUTORIAL_PYTHON_DIR:-${SCRIPT_DIR}/../../zserio-tutorial-python}"
        if [ ! -d "${ZSERIO_TUTORIAL_PYTHON_DIR}" ] ; then
            stderr_echo "Cannot find Zserio Tutorial Python directory! Set ZSERIO_TUTORIAL_PYTHON_DIR" \
                    "environment variable."
            return 1
        fi
    fi

    return 0
}

# Print help on the environment variables used for this release script.
print_release_help_env()
{
    cat << EOF
Uses the following environment variables for releasing:
    ZIP    Zip executable to use. Default is "zip".
    GIT    Git executable to use. Default is "git".
    CMAKE  CMake executable to use. Default is "cmake".
    ANT    Ant executable to use. Default is "ant".
    PYTHON Python executable to use. Default is "python3".

    ZSERIO_PYPI_DIR             ZserioPyPi project directory. Default is "../../ZserioPyPi".
    ZSERIO_EXTENSION_SAMPLE_DIR ZserioExtensionSample project directory. Default is "../../ZserioExtensionSample".
    ZSERIO_TUTORIAL_CPP_DIR     ZserioTutorialCpp project directory. Default is "../../ZserioTutorialCpp".
    ZSERIO_TUTORIAL_JAVA_DIR    ZserioTutorialJava project directory. Default is "../../ZserioTutorialJava".
    ZSERIO_TUTORIAL_PYTHON_DIR  ZserioTutorialPython project directory. Default is "../../ZserioTutorialPython".

    Either set these directly, or create 'scripts/build-env.sh' that sets these.
    It's sourced automatically if it exists.

EOF
}

# Assemble Zserio release ZIP file.
#
# This requires the Zserio tool to be already built (by build.sh).
make_release()
{
    exit_if_argc_ne $# 3
    local ZSERIO_VERSION="$1"; shift
    local ZSERIO_RELEASE_SRC_DIR="$1"; shift
    local ZSERIO_RELEASE_ZIP_DIR="$1"; shift

    echo "The release source directory: ${ZSERIO_RELEASE_SRC_DIR}"
    echo "The release target directory: ${ZSERIO_RELEASE_ZIP_DIR}"
    echo

    echo -ne "Creating release ${ZSERIO_VERSION}..."
    rm -rf "${ZSERIO_RELEASE_ZIP_DIR}"
    mkdir -p "${ZSERIO_RELEASE_ZIP_DIR}"

    # create zips
    pushd "${ZSERIO_RELEASE_SRC_DIR}" > /dev/null

    # create zip: jar
    "${ZIP}" -rq "${ZSERIO_RELEASE_ZIP_DIR}/zserio-${ZSERIO_VERSION}-bin.zip" "ant_task" \
            "zserio_libs" "zserio.jar"
    if [ $? -ne 0 ] ; then
        stderr_echo "Can't zip Zserio release (bin)."
        return 1
    fi

    # create zip: runtime-libs
    "${ZIP}" -rq "${ZSERIO_RELEASE_ZIP_DIR}/zserio-${ZSERIO_VERSION}-runtime-libs.zip" "runtime_libs"
    if [ $? -ne 0 ] ; then
        stderr_echo "Can't zip Zserio release (runtime_libs)."
        return 1
    fi

    popd > /dev/null

    echo "Done"

    return 0
}

# Upload Zserio PyPi repository after new Zserio release.
upload_pypi()
{
    exit_if_argc_ne $# 1
    local PYPI_DIR="$1"; shift

    "${PYPI_DIR}/scripts/build.sh" -p
    if [ $? -ne 0 ] ; then
        stderr_echo "Failure to build Zserio PyPi!"
        return 1
    fi

    "${PYPI_DIR}/scripts/test.sh"
    if [ $? -ne 0 ] ; then
        stderr_echo "Failure to test Zserio PyPi!"
        return 1
    fi

    "${PYPI_DIR}/scripts/upload.sh"
    if [ $? -ne 0 ] ; then
        stderr_echo "Failure to upload Zserio PyPi!"
        return 1
    fi
    echo

    return 0
}

# Update Zserio Extension Sample repository after new Zserio release.
update_extension_sample()
{
    exit_if_argc_ne $# 2
    local EXTENSION_SAMPLE_DIR="$1"; shift
    local ZSERIO_VERSION="$1"; shift

    local EXTENSION_FILE="${EXTENSION_SAMPLE_DIR}/src/zserio/extension/sample/SampleExtension.java"
    echo -ne "Updating version to ${ZSERIO_VERSION} in Zserio Extension Sample..."
    sed -i -e 's/[2-9]\+\.[0-9]\+\.[0-9]\+\(\-[A-Za-z0-9]\+\)\?/'"${ZSERIO_VERSION}"'/' "${EXTENSION_FILE}"
    local SED_RESULT=$?
    if [ ${SED_RESULT} -ne 0 ] ; then
        stderr_echo "Sed failed with return code ${SED_RESULT}!"
        return 1
    fi
    echo "Done"
    echo

    "${GIT}" -C "${EXTENSION_SAMPLE_DIR}" diff --exit-code > /dev/null
    if [ $? -eq 0 ] ; then
        echo $'\e[1;33m'"Zserio Extension Sample already up to date."$'\e[0m'
    else
        echo "Committing update of Zserio Extension Sample."
        "${GIT}" -C "${EXTENSION_SAMPLE_DIR}" commit -a \
                -m "Change expected zserio core version to ${ZSERIO_VERSION}"
        local GIT_RESULT=$?
        if [ ${GIT_RESULT} -ne 0 ] ; then
            stderr_echo "Git failed with return code ${GIT_RESULT}!"
            return 1
        fi
    fi
    echo

    return 0
}

# Update Zserio Tutorial Cpp repository after new Zserio release.
update_tutorial_cpp()
{
    exit_if_argc_ne $# 2
    local TUTORIAL_CPP_DIR="$1"; shift
    local ZSERIO_VERSION="$1"; shift

    echo "Updating generated sources in Zserio Tutorial Cpp."
    echo
    local TUTORIAL_CPP_BUILD_DIR="${TUTORIAL_CPP_DIR}/build"
    rm -rf "${TUTORIAL_CPP_BUILD_DIR}"
    mkdir -p "${TUTORIAL_CPP_BUILD_DIR}"
    pushd "${TUTORIAL_CPP_BUILD_DIR}" > /dev/null
    "${CMAKE}" -DREGENERATE_CPP_SOURCES=ON ..
    local CMAKE_RESULT=$?
    popd > /dev/null
    if [ ${CMAKE_RESULT} -ne 0 ] ; then
        stderr_echo "CMake failed with return code ${CMAKE_RESULT}!"
        return 1
    fi
    echo

    "${GIT}" -C "${TUTORIAL_CPP_DIR}" diff --exit-code > /dev/null
    if [ $? -eq 0 ] ; then
        echo $'\e[1;33m'"Zserio Tutorial Cpp already up to date."$'\e[0m'
    else
        echo "Committing update of Zserio Tutorial Cpp."
        "${GIT}" -C "${TUTORIAL_CPP_DIR}" commit -a -m "Update generated sources to version ${ZSERIO_VERSION}"
        local GIT_RESULT=$?
        if [ ${GIT_RESULT} -ne 0 ] ; then
            stderr_echo "Git failed with return code ${GIT_RESULT}!"
            return 1
        fi
    fi
    echo

    return 0
}

# Update Zserio Tutorial Java repository after new Zserio release.
update_tutorial_java()
{
    exit_if_argc_ne $# 2
    local TUTORIAL_JAVA_DIR="$1"; shift
    local ZSERIO_VERSION="$1"; shift

    echo "Updating generated sources in Zserio Tutorial Java."
    echo
    "${ANT}" -buildfile "${TUTORIAL_JAVA_DIR}/build.xml"
    local ANT_RESULT=$?
    if [ ${ANT_RESULT} -ne 0 ] ; then
        stderr_echo "Ant failed with return code ${ANT_RESULT}!"
        return 1
    fi
    echo

    "${GIT}" -C "${TUTORIAL_JAVA_DIR}" diff --exit-code > /dev/null
    if [ $? -eq 0 ] ; then
        echo $'\e[1;33m'"Zserio Tutorial Java already up to date."$'\e[0m'
    else
        echo "Committing update of Zserio Tutorial Java."
        "${GIT}" -C "${TUTORIAL_JAVA_DIR}" commit -a -m "Update generated sources to version ${ZSERIO_VERSION}"
        local GIT_RESULT=$?
        if [ ${GIT_RESULT} -ne 0 ] ; then
            stderr_echo "Git failed with return code ${GIT_RESULT}!"
            return 1
        fi
    fi
    echo

    return 0
}

# Update Zserio Tutorial Python repository after new Zserio release.
update_tutorial_python()
{
    exit_if_argc_ne $# 2
    local TUTORIAL_PYTHON_DIR="$1"; shift
    local ZSERIO_VERSION="$1"; shift

    echo "Updating generated sources in Zserio Tutorial Python."
    echo
    local TUTORIAL_PYTHON_BUILD_DIR="${TUTORIAL_PYTHON_DIR}/build"
    rm -rf "${TUTORIAL_PYTHON_BUILD_DIR}"
    mkdir -p "${TUTORIAL_PYTHON_BUILD_DIR}"

    "${PYTHON}" -m virtualenv "${TUTORIAL_PYTHON_BUILD_DIR}"
    local PYTHON_RESULT=$?
    if [ ${PYTHON_RESULT} -ne 0 ] ; then
        stderr_echo "Python failed with return code ${PYTHON_RESULT}!"
        return 1
    fi
    if [ -f "${TUTORIAL_PYTHON_BUILD_DIR}/bin/activate" ] ; then
        . "${TUTORIAL_PYTHON_BUILD_DIR}/bin/activate"
    else
        . "${TUTORIAL_PYTHON_BUILD_DIR}/Scripts/activate"
    fi
    pip install zserio=="${ZSERIO_VERSION}"
    zserio -src "${TUTORIAL_PYTHON_DIR}" tutorial.zs -python "${TUTORIAL_PYTHON_DIR}/src"
    local ZSERIO_RESULT=$?
    if [ ${ZSERIO_RESULT} -ne 0 ] ; then
        stderr_echo "Zserio failed with return code ${ZSERIO_RESULT}!"
        return 1
    fi
    echo

    "${GIT}" -C "${TUTORIAL_PYTHON_DIR}" diff --exit-code > /dev/null
    if [ $? -eq 0 ] ; then
        echo $'\e[1;33m'"Zserio Tutorial Python already up to date."$'\e[0m'
    else
        echo "Committing update of Zserio Tutorial Python."
        "${GIT}" -C "${TUTORIAL_PYTHON_DIR}" commit -a -m "Update generated sources to version ${ZSERIO_VERSION}"
        local GIT_RESULT=$?
        if [ ${GIT_RESULT} -ne 0 ] ; then
            stderr_echo "Git failed with return code ${GIT_RESULT}!"
            return 1
        fi
    fi
    echo

    return 0
}

# Print help message.
print_help()
{
    cat << EOF
Description:
    Releases Zserio to release-ver directory.

Usage:
    $0 [-h] [-e] [-u]

Arguments:
    -h, --help     Show this help.
    -e, --help-env Show help for enviroment variables.
    -u, --update-dependent-respositories
                   Update all Zserio dependent repositories after Zserio release.

Examples:
    $0

EOF
}

# Parse all command line arguments.
#
# Return codes:
# -------------
# 0 - Success. Arguments have been successfully parsed.
# 1 - Failure. Some arguments are wrong or missing.
# 2 - Help switch is present. Arguments after help switch have not been checked.
# 3 - Environment help switch is present. Arguments after help switch have not been checked.
parse_arguments()
{
    local NUM_OF_ARGS=1
    exit_if_argc_lt $# ${NUM_OF_ARGS}
    local SWITCH_UPDATE_OUT="$1"; shift

    eval ${SWITCH_UPDATE_OUT}=0

    local NUM_PARAMS=0
    local ARG="$1"
    while [ -n "${ARG}" ] ; do
        case "${ARG}" in
            "-h" | "--help")
                return 2
                ;;

            "-e" | "--help-env")
                return 3
                ;;

            "-u" | "--update-dependent-respositories")
                eval ${SWITCH_UPDATE_OUT}=1
                shift
                ;;

            "-"*)
                stderr_echo "Invalid switch ${ARG}!"
                echo
                return 1
                ;;

            *)
                stderr_echo "Invalid parameter ${ARG}!"
                echo
                return 1
                ;;
        esac
        ARG="$1"
    done

    return 0
}

# Main entry of the script to make Zserio release.
main()
{
    # parse command line arguments
    local SWITCH_UPDATE
    parse_arguments SWITCH_UPDATE $@
    local PARSE_RESULT=$?
    if [ ${PARSE_RESULT} -eq 2 ] ; then
        print_help
        return 0
    elif [ ${PARSE_RESULT} -eq 3 ] ; then
        print_release_help_env
        return 0
    elif [ ${PARSE_RESULT} -ne 0 ] ; then
        return 1
    fi

    # set global variables
    set_release_global_variables ${SWITCH_UPDATE}
    if [ $? -ne 0 ] ; then
        return 1
    fi

    # get the project root (the absolute path is necessary for zip)
    local ZSERIO_PROJECT_ROOT
    convert_to_absolute_path "${SCRIPT_DIR}/.." ZSERIO_PROJECT_ROOT

    # get Zserio release directory
    local ZSERIO_RELEASE_DIR
    local ZSERIO_VERSION
    get_release_dir "${ZSERIO_PROJECT_ROOT}" ZSERIO_RELEASE_DIR ZSERIO_VERSION
    if [ $? -ne 0 ] ; then
        return 1
    fi

    # check if we should update dependent repositories after new Zserio release instead of making a release
    if [[ ${SWITCH_UPDATE} == 0 ]] ; then
        echo "Releasing Zserio binaries."
        echo

        local ZSERIO_DISTR_DIR="${ZSERIO_PROJECT_ROOT}/distr"

        rm -rf "${ZSERIO_RELEASE_DIR}"
        mkdir -p "${ZSERIO_RELEASE_DIR}"

        make_release "${ZSERIO_VERSION}" "${ZSERIO_DISTR_DIR}" "${ZSERIO_RELEASE_DIR}"
        if [ $? -ne 0 ] ; then
            return 1
        fi
    else
        echo "Updating dependent repositories after new Zserio release."
        echo

        upload_pypi "${ZSERIO_PYPI_DIR}"
        if [ $? -ne 0 ] ; then
            return 1
        fi

        update_extension_sample "${ZSERIO_EXTENSION_SAMPLE_DIR}" "${ZSERIO_VERSION}"
        if [ $? -ne 0 ] ; then
            return 1
        fi

        update_tutorial_cpp "${ZSERIO_TUTORIAL_CPP_DIR}" "${ZSERIO_VERSION}"
        if [ $? -ne 0 ] ; then
            return 1
        fi

        update_tutorial_java "${ZSERIO_TUTORIAL_JAVA_DIR}" "${ZSERIO_VERSION}"
        if [ $? -ne 0 ] ; then
            return 1
        fi

        update_tutorial_python "${ZSERIO_TUTORIAL_PYTHON_DIR}" "${ZSERIO_VERSION}"
        if [ $? -ne 0 ] ; then
            return 1
        fi
    fi

    return 0
}

main "$@"
