astyle --style=allman src/*/*.cpp
astyle --style=allman src/*.cpp
astyle --style=allman includes/*.hpp
find . -name "*.orig" -type f -delete
