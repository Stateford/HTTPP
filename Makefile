.PHONY: test

SOURCE_FILES=src/main.cpp src/network/socket.cpp src/network/request.cpp src/network/header.cpp src/network/response.cpp src/network/url.cpp src/network/http.cpp
TEST_FILES=test/tests.cpp src/network/url.cpp
TEST_LIB=/usr/lib/libgtest.a

all:
	release

test:
	clang++ -pthread ${TEST_FILES} ${TEST_LIB} -o mytest
	clean

release:
	clang++ -Wall -Werror ${SOURCE_FILES} 

debug:
	clang++ -g -O0 -Wall -Werror ${SOURCE_FILES}

lint:
	clang-tidy-7 ${SOURCE_FILES}

run:
	release
	./a.out
	clean

clean:
	rm ./a.out
	rm ./mytest
