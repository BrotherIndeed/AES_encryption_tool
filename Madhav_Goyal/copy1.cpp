#include <iostream>
#include <openssl/sha.h>
#include <fstream>
#include <cstring>

int copyFile(char **argv)
{
	std::fstream *src = new std::fstream();
	std::fstream *dst = new std::fstream();
	src->open(argv[1], std::ios::in);
	dst->open(argv[2], std::ios::out);
	if (src->fail() || dst->fail())
	{
		std::cout << "Failed to open file" << std::endl;
		return 1;
	}
	std::cout << "File opened successfully" << std::endl;
	char buffer[1024] = {0};
	while (!src->eof())
	{
		src->read(buffer, 1024);
		// std::cout << buffer;
		for (char c : buffer)
		{
			if (c != '\0')
			{
				std::cout << c;
				dst->put(c);
			}
			else
			{
				break;
			}
		}
		*buffer = {0};
	}
	src->close();
	dst->close();
	return 0;
}

int hashCheck(char **argv)
{
	std::fstream *src = new std::fstream();
	std::fstream *dst = new std::fstream();
	src->open(argv[1], std::ios::in);
	dst->open(argv[2], std::ios::out);
	char s_buf[1024] = {0}, d_buf[1024] = {0};
	unsigned char s_hash[SHA_DIGEST_LENGTH], d_hash[SHA_DIGEST_LENGTH];

	while (!src->eof())
	{
		dst->read(d_buf, 1024);
		src->read(s_buf, 1024);
		SHA1((unsigned char *)&s_buf, strlen(s_buf), s_hash);
		SHA1((unsigned char *)&d_buf, strlen(d_buf), d_hash);
		for (auto i : s_hash){
		printf("%x", i);
		}
		printf("\n");
		for (auto i : d_hash){
		printf("%x", i);
		}
		if (s_hash!=d_hash) {
			std::cout<<"Hash error"<<std::endl;
			return 1;
		}
	}
	if (!dst -> eof()) {
		std::cout<<"Hash error"<<std::endl;
		return 1;
	}
	for (auto i : s_hash){
		printf("%x", i);
	}
	printf("\n");
	return 0;
}

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		std::cout << "Please enter the source and destination paths" << std::endl;
		return 1;
	}
	return copyFile(argv)||hashCheck(argv);

}
