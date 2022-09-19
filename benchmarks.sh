#!/usr/bin/env bash

array_sizes='100 1000 10000 100000 500000 1000000 5000000 10000000 50000000 100000000 500000000'
float_types='float double'

for array_size in $array_sizes; do
    for float_type in $float_types; do
        make ARRAY_SIZE=$array_size FLOAT_TYPE=$float_type
    done
done
