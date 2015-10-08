all:
	g++ -o bin/crypto src/main.cpp src/crypto.cpp -lcrypto -lssl
main_tests:
	g++ -o test/main_tests test/main_tests.cpp src/crypto.cpp -lcrypto -lssl
	./test/main_tests
