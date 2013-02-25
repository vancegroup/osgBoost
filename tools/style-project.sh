#!/bin/sh -e

PROJECT=$(cd $(dirname $0) && cd .. && pwd)

astyle -n "--options=${PROJECT}/tools/astylerc" \
  --recursive "${PROJECT}/osgTraits/*.h" \
  --recursive "${PROJECT}/tests/*.h" \
  --recursive "${PROJECT}/tests/*.cpp"
  
