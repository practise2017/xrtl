#!/bin/bash
set -e

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
  export CC=clang-4.0
  export CXX=clang++-4.0
else
  export CC=clang
  export CXX=clang
fi

# Use CI-specific bazel configurations.
cp tools/ci/travis/.bazelrc .

./xtool test \
    --output_base=/tmp/.cache/bazel_root_$CONFIG/ \
    -c dbg \
    --config=$CONFIG \
    --keep_going \
    --all \
    --test_tag_filters=-requires_gui,-requires_gpu
