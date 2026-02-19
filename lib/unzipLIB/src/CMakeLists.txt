target_sources(${UNZIPLIB_TARGET} PRIVATE
        adler32.c
        crc32.c
        inflate.c
        unzip.c
        infback.c
        zutil.c
        inftrees.c
        inffast.c
        unzipLIB.cpp
)

target_include_directories(${UNZIPLIB_TARGET}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
