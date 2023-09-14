# Check if install manifest exists
IF(NOT EXISTS "/home/daslab/BlockSci-daslab/cmake-build-debug/external/bitcoin-api-cpp/install_manifest.txt")
    MESSAGE(FATAL_ERROR "Cannot find install manifest: \"/home/daslab/BlockSci-daslab/cmake-build-debug/external/bitcoin-api-cpp/install_manifest.txt\"")
ENDIF(NOT EXISTS "/home/daslab/BlockSci-daslab/cmake-build-debug/external/bitcoin-api-cpp/install_manifest.txt")

# Read install manifest
FILE(READ "/home/daslab/BlockSci-daslab/cmake-build-debug/external/bitcoin-api-cpp/install_manifest.txt" files)
STRING(REGEX REPLACE "\n" ";" files "${files}")
LIST(REVERSE files)

FOREACH(file ${files})
    MESSAGE(STATUS "Uninstalling \"${file}\"")
    IF(EXISTS "$ENV{DESTDIR}${file}")

        EXECUTE_PROCESS(
            COMMAND /home/daslab/.cache/JetBrains/RemoteDev/dist/d665901452acc_CLion-2023.2/bin/cmake/linux/x64/bin/cmake -E remove "$ENV{DESTDIR}${file}"
            OUTPUT_VARIABLE rm_out
            RESULT_VARIABLE rm_retval
        )

        IF(NOT ${rm_retval} EQUAL 0)
            MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
        ENDIF(NOT ${rm_retval} EQUAL 0)

    ELSE(EXISTS "$ENV{DESTDIR}${file}")
        MESSAGE(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
    ENDIF(EXISTS "$ENV{DESTDIR}${file}")
ENDFOREACH(file)
