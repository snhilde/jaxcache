TARGET=jaxcache

CC=gcc
DRIVER=main.c

CFLAGS= -I. \
		-Wall \
		-g

@all:
	${CC} ${CFLAGS} -o ${TARGET} ${DRIVER} ${TARGET}.c
