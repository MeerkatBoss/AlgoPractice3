#!/bin/sh

make run BUILDTYPE=Release TEST_CASE=insertion_sort &&\
    git add . &&\
    git commit -m "feat: insertion sort tests"&&\
    git push -u origin test_results &&\
    shutdown


