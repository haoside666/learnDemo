#!/bin/sh

gcc -g -o pool pthread_pool.c pool_test.c -lpthread
