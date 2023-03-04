#!/bin/sh

make run BUILDTYPE=Release TEST_CASE=log_sorts &&\
    git add . && git commit -m "feat: logarithmic sorts testing results (retest)" && git push &&\
make run BUILDTYPE=Release TEST_CASE=radix_sorts &&\
    git add . && git commit -m "feat: radix sorts testing results" && git push &&\
    shutdown


