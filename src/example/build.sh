gcc -I../../include/ -lglfw -lGL ./example.c ../../build/static/nxdraw/libnxdraw.a && ./a.out
#clang++ -I../../include/ -lglfw -lGL ./example.c -lnxdraw && ./a.out

#NXD_LIB=$(realpath ${HOME}/syncthing/projects/project/c_gamestack_c/nxdraw3/build/libnxdraw.a)
##echo ${NXD_LIB}
#gcc -I../../include/ -lglfw -lGL ./example.c $NXD_LIB
