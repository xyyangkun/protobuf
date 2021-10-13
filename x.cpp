/******************************************************************************
 *
 *       Filename:  x.cpp
 *
 *    Description:  test
 *
 *        Version:  1.0
 *        Created:  2021年10月13日 22时30分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yangkun (yk)
 *          Email:  xyyangkun@163.com
 *        Company:  yangkun.com
 *
 *****************************************************************************/
#include "x.pb.h"
#include <fstream>
int main()
{
	using namespace x;
	{
	Person p;
	p.set_name("yangkun");
	p.set_id(88);
	p.set_email("xyyangkun@163.com");
	p.set_mytest("xyyangkun@163.com");

	// 给mydata中存放一些二进制数据
	std::string mydata;
	mydata.resize(10);
	char *_p = (char *)mydata.data();
	for(int i=0; i<10; i++) {
		_p[i] = i;	
	}

	p.set_mydata(mydata);

	std::string str;
	p.SerializeToString(&str);

	// 将序列化的数据写入文件
	std::ofstream outfile ("test.bin",std::ofstream::binary);
	//outfile.write(str);
	outfile << str;
	outfile.close();
	}

	{
	// 读出文件，并还原数据
	std::ifstream infile  ("test.bin",std::ifstream::binary);
	Person x;
	std::string str;
	// get size of file
	infile.seekg (0,infile.end);
	long size = infile.tellg();
	infile.seekg (0);
	//infile >> str;
	str.resize(size);
	infile.read((char *)str.data(), size);
	infile.close();

	x.ParseFromString(str);
	std::cout << "name: " << x.name() << " id: " << x.id() << " email: " << x.email() << std::endl;
	// 读出保存的二进制数据
	if(x.has_mydata()){
		unsigned char *_p = (unsigned char *)x.mydata().data();
		for(int i=0; i<10; i++) {
			printf("i=%02x\n", _p[i]);
		}
	}
	}
}
