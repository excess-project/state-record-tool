gcc -DPAPI_CORETEMP "$@" -o read-coretemp *.c -I$PAPIDIR/include -L$PAPIDIR/lib -lpapi -lpthread -lrt
gcc -DPAPI_RAPL "$@" -o read-rapl-papi *.c -I$PAPIDIR/include -L$PAPIDIR/lib -lpapi -lpthread -lrt
gcc -DLIKWID_RAPL "$@" -o read-rapl-likwid *.c -I$LIKWIDSRC/src/includes -I$LIKWIDSRC/GCC $LIKWIDDIR/lib/liblikwid.a -lpthread -lrt -lm
