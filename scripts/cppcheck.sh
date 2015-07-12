cppcheck --enable=all --inconclusive --check-config --suppress=missingIncludeSystem src/ 2> errors.log;
if [ -s errors.log ]; then
    echo "ERROR : code behaviors warnings and errors, please check 'errors.log' file content."
    exit 1
fi
