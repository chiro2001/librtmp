#ifndef DEBUG
#define DEBUG
#endif

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#if defined(__WIN32__) || defined(WIN32)
#include <windows.h>
#endif

#include "rtmp.h"
#include "rtmp_packet.h"
#include "amf_packet.h"


int main(void)
{

    rtmp_client_t *rc;
    int count;
    rtmp_event_t *event;

    // rc = rtmp_client_create("rtmp://live-push.bilivideo.com/live-bvc/?streamname=live_12070196_2094942&key=2482a0019cb48b7cd4d7eb97bfe1191f&schedule=rtmp&pflag=1");
    rc = rtmp_client_create("rtmp://113.96.15.55/live-bvc/?streamname=live_12070196_2094942&key=2482a0019cb48b7cd4d7eb97bfe1191f&schedule=rtmp&pflag=1");
    if (rc == NULL) {
        printf("failed\n");
        return -1;
    }

    printf("created.\n");

    count = 2000;
    while (count--) {
        rtmp_client_process_message(rc);
        event = rtmp_client_get_event(rc);
        if (event != NULL) {
            printf("count: %5d, event: %s, %s\n", count, event->code, event->level);
            if (strcmp(event->code, "NetConnection.Connect.Success") == 0) {
                rtmp_client_create_stream(rc);
                rtmp_client_play(rc, "test.flv");
            }
            rtmp_client_delete_event(rc);
        } else {
            sleep(1);
            printf("sleep\n");
        }
    }

    rtmp_client_free(rc);

    printf("exit normally...\n");

    return 0;
}
