work/split-file : src/main.cpp src/sha1.cpp
	g++ -o work/split-file src/main.cpp src/sha1.cpp
  
clean:
	rm work/* -f
	
test:work/split-file
	work/split-file /boot/initrd.img-3.2.0-26-generic-pae 16 work > work/initrd.tag
	
  
