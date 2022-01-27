#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

QueueHandle_t data_Q;
TickType_t xTimeStamp;

void task_1(void *data)
{
    while(1)
    {
    xTimeStamp = xTaskGetTickCount()*portTICK_PERIOD_MS;
    printf("%d : task 1 \n",xTimeStamp);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

}
void task_2(void *data)
{
    while(1)
    {
    xTimeStamp = xTaskGetTickCount()*portTICK_PERIOD_MS;
    printf("%d : task 2 \n",xTimeStamp);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    }

}
void task_3(void *data)
{
    while(1)
    {
    xTimeStamp = xTaskGetTickCount()*portTICK_PERIOD_MS;
    printf("%d :Task 3\n",xTimeStamp);
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    }

}

void task_4(void *data)
{
    int msg = 2;
    while(1)
    {
    printf("Task sennd\n");
    xQueueSend( data_Q, &msg,( TickType_t ) 2 );
    msg++;
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    }

}

void task_5(void *data)
{
    int buf;
    while(1)
    {
    printf("Recieving task\n");
    xQueueReceive( data_Q,&buf, 0);
    printf("recieved BUF: %d\n",buf);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    }

}

void app_main(void)
{

     data_Q = xQueueCreate( 5, sizeof(int));

    if( data_Q == NULL )
    {
        printf("Queue not created\n");          // if failed
    }else{
    xTaskCreate(task_1,"T1",2048,NULL,1,NULL);
    xTaskCreate(task_2,"T2",2048,NULL,1,NULL);
    xTaskCreate(task_3,"T3",2048,NULL,1,NULL);
    xTaskCreate(task_4,"Send",1024,NULL,1,NULL);
    xTaskCreate(task_5,"Rrecieve",2048,NULL,1,NULL);
    }
}