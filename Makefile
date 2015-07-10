CC = gcc
CFLAGS = -g -Wall
CURL_LDFLAGS = $(shell pkg-config --libs libcurl)

c: crawler.c string_buffer.c
	$(CC) $(CFLAGS) $(CURL_LDFLAGS) -o $@ $^
