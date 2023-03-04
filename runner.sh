#!/bin/sh

make run BUILDTYPE=Release TEST_CASE=selection_sort &&\
    git add . && git commit -m "feat: selection sort full tests" && git push &&\
make run BUILDTYPE=Release TEST_CASE=bubble_sort &&\
    gut add . && git commit -m "feat: bubble sort full tests" && git push &&\
    shutdown


