# Description:
#  Posix pthreads port variants of //xrtl/base/threading/ features.

package(default_visibility = ["//xrtl:internal"])

licenses(["notice"])  # Apache 2.0

cc_library(
    name = "pthreads_event",
    srcs = ["pthreads_event.cc"],
    deps = [
        ":pthreads_wait_handle",
        "//xrtl/base/threading:threading_hdrs",
    ],
    linkopts = [
        "-lpthread",
    ],
)

cc_library(
    name = "pthreads_semaphore",
    srcs = ["pthreads_semaphore.cc"],
    deps = [
        ":pthreads_wait_handle",
        "//xrtl/base/threading:threading_hdrs",
    ],
    linkopts = [
        "-lpthread",
    ],
)

cc_library(
    name = "pthreads_thread",
    srcs = ["pthreads_thread.cc"],
    deps = [
        ":pthreads_event",
        ":pthreads_wait_handle",
        "//xrtl/base:logging",
        "//xrtl/base:stopwatch",
        "//xrtl/base/threading:threading_hdrs",
    ],
    linkopts = [
        "-lpthread",
    ],
)

cc_library(
    name = "pthreads_wait_handle",
    srcs = ["pthreads_wait_handle.cc"],
    hdrs = ["pthreads_wait_handle.h"],
    deps = [
        "//xrtl/base/threading:wait_handle",
    ],
    linkopts = [
        "-lpthread",
    ],
)