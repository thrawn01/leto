# ----------------------------------------------------------------
# Derrick Wippler 2007 (thrawn01@gmail.com) 
# ----------------------------------------------------------------

# Add the leto Library
ADD_LIBRARY(leto leto.cpp )
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

ENABLE_TESTING()

ADD_CXXTEST(letoTests letoTests.h )
TARGET_LINK_LIBRARIES(letoTests leto )

