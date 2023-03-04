#!/bin/sh

make run BUILDTYPE=Release TEST_CASE=log_sorts &&\
    git add . && git commit -m "feat: logarithmic sorts tests" && git push &&\
    shutdown


