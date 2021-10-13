
# -lpthread 是一定要的，要不然运行会出错
all:
	g++ x.cpp x.pb.cc -lprotobuf -lpthread -o x
