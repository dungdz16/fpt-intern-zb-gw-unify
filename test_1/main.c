/*
    * Time: 05-11-2024
    * Author: NTKiendz
    * 
    * Brief: APP C programming language to use Unify Zigbee Gateway Zigbee2MQTT
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mosquitto.h>

/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/

// Mosquitto
struct mosquitto *mosq = NULL;

/*
*********************************************************************************************************
*                                               FUNCTIONS
*********************************************************************************************************
*/

void on_connect(struct mosquitto *mosq, void *userdata, int result) {
    if (result == 0) {
        printf("Connected successfully.\n");
        mosquitto_subscribe(mosq, NULL, "ucl/by-unid/#", 0);
    } else {
        fprintf(stderr, "Connect failed with code %d.\n", result);
    }
}

void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *msg) {
    if (strstr(msg->topic, "State")) {
        printf("Node ID: %s\n", msg->topic);
        // Extract and display node info here
    }
}


int main()
{
    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "Error: Out of memory.\n");
        return 1;
    }

    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);

    if (mosquitto_connect(mosq, "192.168.137.100", 1883, 60) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Unable to connect.\n");
        return 1;
    }

    mosquitto_loop_start(mosq);

    // Wait for node list and user selection
    char node_id[100];
    printf("Enter the node ID to control LED: ");
    if (scanf("%99s", node_id) != 1) {
        fprintf(stderr, "Error reading node ID.\n");
        mosquitto_loop_stop(mosq, true);
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return 1;
    }

    // Publish LED control command to the selected node
    char topic[200];
    snprintf(topic, sizeof(topic), "ucl/by-unid/%s/ep1/OnOff/Commands/Toggle", node_id);
    const char *payload = "{}";
    mosquitto_publish(mosq, NULL, topic, strlen(payload), payload, 0, false);

    mosquitto_loop_stop(mosq, true);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}

