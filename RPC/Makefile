client.o: pthread.c square_clnt.c square_clnt.o
	cc -c pthread.c -o client.o -lpthread 
	cc -c square_clnt.c -o square_clnt.o
server.o: server.c square_svc.c square_svc.o
	cc -c server.c -o server.o
	cc -c square_svc.c -o square_svc.o
client: client.o square_clnt.o square_xdr.o
	cc -o client client.o square_clnt.o square_xdr.o -lpthread
server:server.o square_svc.o square_xdr.o
	cc -o server server.o square_svc.o square_xdr.o
rpc:square.x 
	rpcgen -C square.x
clean:
	rm -f *.o