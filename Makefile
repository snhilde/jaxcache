TARGET=jax_cache

CC=gcc
DRIVER=jax_driver.c

CFLAGS= -I. \
		-Wall \
		-g

@all:
	${CC} ${CFLAGS} -o ${TARGET} ${DRIVER} ${TARGET}.c
