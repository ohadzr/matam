set(FIND_LIBMTM_PATHS
        C:/Users/ohad/ClionProjects/matam/hw4/tests
        )


find_library(LIBMTM_LIBRARY NAMES libmtm PATH_SUFFIXES tests PATHS ${FIND_LIBMTM_PATHS})