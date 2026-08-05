#include "libnexus-bus.h"
#include <stdio.h> <errno.h>
static int p=0,f=0;
#define T(n) do{printf("  TEST: %s ... ",n);fflush(stdout);}while(0)
#define P() do{printf("PASS\n");p++;}while(0)
#define F(m) do{printf("FAIL: %s\n",m);f++;}while(0)
#define S() do{printf("SKIP\n");}while(0)
int main(void){
    printf("Nexus Bus Driver Test Suite\n");
    T("open/close");struct nexus_bus_handle *h=nexus_bus_open("/dev/nexus-bus0");if(!h){S();}else{nexus_bus_close(h);P();}
    T("gpio read");h=nexus_bus_open("/dev/nexus-bus0");if(!h){S();}else{uint32_t v;int r=nexus_bus_read(h,0,0,0,0,&v);if(r){nexus_bus_close(h);F("read");}else{nexus_bus_close(h);P();}}
    T("gpio write");h=nexus_bus_open("/dev/nexus-bus0");if(!h){S();}else{int r=nexus_bus_write(h,0,0,0,0,1);if(r){nexus_bus_close(h);F("write");}else{nexus_bus_close(h);P();}}
    T("invalid args");int r=nexus_bus_read(NULL,0,0,0,0,NULL);if(r==-EINVAL)P();else F("expected -EINVAL");
    printf("\n%d passed, %d failed\n",p,f);return f>0?1:0;
}
