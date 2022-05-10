all:sever client

sever:sever.c
	gcc $< -o $@

client:client.c 
	gcc $< -o $@


.PHONY:clean
clean:
	rm -f sever
	rm -f client