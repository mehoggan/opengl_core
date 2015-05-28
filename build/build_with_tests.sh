echo "====================================================================="
echo "Starting build with"
echo "    DEBUG=${DEBUG}"
echo "    RELEASE=${RELEASE}"
echo "    VALGRIND=${VALGRIND}."
echo "====================================================================="

if [[ ${DEBUG} == 'true' ]]; then
  echo "====================================================================="
  echo "Building debug and testing in debug."
  echo "====================================================================="
  pushd `dirname $0` > /dev/null
    SCRIPTPATH=`pwd`

    ${SCRIPTPATH}/../tools/autotools_gen.sh && \
    ./configure CPPFLAGS=-DDEBUG CXXFLAGS="-g -O0"&& \
    make clean all && \
    pushd ../tests/build/ && \
      ../../tools/autotools_gen.sh && \
      ./configure CPPFLAGS=-DDEBUG CXXFLAGS="-g -O0" && \
      make clean all && \
      if [[ ${VALGRIND} == 'true' ]]; then
        valgrind --leak-check=full \
          --suppressions=./ubuntu-14.04-nvidia-331.supp ./test_opengl_core
      else
        ./test_opengl_core
      fi
      if [[ ${?} != "0" ]]; then
        popd > /dev/null
        popd > /dev/null
        exit 1;
      fi
    popd > /dev/null
  popd > /dev/null
  for i in seq 1 5; do echo ""; done;
fi

sleep 5

if [[ ${RELEASE} == 'true' ]]; then
  for i in seq 1 5; do echo ""; done;
  echo "====================================================================="
  echo "Building release and testing in release."
  echo "====================================================================="
  pushd `dirname $0` > /dev/null
    SCRIPTPATH=`pwd`

    ${SCRIPTPATH}/../tools/autotools_gen.sh && \
    ./configure CPPFLAGS=-DNDEBUG CXXFLAGS="-O3"&& \
    make clean all && \
    pushd ../tests/build/ && \
      ../../tools/autotools_gen.sh && \
      ./configure CPPFLAGS=-DNDEBUG CXXFLAGS="-O3" && \
      make clean all && \
      if [[ ${VALGRIND} == 'true' ]]; then
        valgrind --leak-check=full \
          --suppressions=./ubuntu-14.04-nvidia-331.supp ./test_opengl_core
      else
        ./test_opengl_core
      fi
      if [[ ${?} != "0" ]]; then
        popd > /dev/null
        popd > /dev/null
        exit 1;
      fi
    popd > /dev/null
  popd > /dev/null
fi
