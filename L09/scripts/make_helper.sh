if [ ! -d build ] ; then
    echo build is not a directory.. making directory
    mkdir build
fi

if [ ! -d documentation ] ; then
    echo documentation is not a directory.. making directory
    mkdir documentation
    cd documentation
    mkdir docs
fi
