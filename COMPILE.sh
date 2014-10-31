gcc -DPAPI_CORETEMP "$@" -o read-coretemp *.c -I$PAPIDIR/include -L$PAPIDIR/lib -lpapi -lpthread -lrt
gcc -DPAPI_RAPL "$@" -o read-rapl *.c -I$PAPIDIR/include -L$PAPIDIR/lib -lpapi -lpthread -lrt
