#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sensor_util.h"

const static char *TAG = "READINGS";
const static int MAX__VOLT_VAR = 10;

void app_main(void)
{
    //int inf;
    //int temp, hum;
    float ph;
    //bool water_level;

    sensors_init();

    float *ph_readings;
    ph_readings = (float*)calloc(32, sizeof(float));

    int *code, *volt;
    code = (int*)calloc(32, sizeof(int));
    volt = (int*)calloc(32, sizeof(int));

    int i = 0;
    float sum, avg;
    int sum_v, avg_v, max, min, mean;
    int mean_code;


    while(1)
    {

        //inf = infiltration_read();
        ph = ph_sensor_read(&code[i], &volt[i]);
        //hum_temp_sensor_read(&temp, &hum);
        //water_level = water_level_read();

        if(i==0)
        {
            max = min = volt[i];
            sum_v = 0;
            sum = 0;
        }

        sum_v += volt[i]; 
        ph_readings[i]=ph;
        sum+=ph;

        if(volt[i] > max)
        {
            max = volt[i];
        }
        else if(volt[i] < min)
        {
            min = volt[i];
        }

        i++;

        //hum_temp_sensor_read(&temp, &hum);
        
        if(i==32)
        {
            printf("\n------------------------------------------------\n");
            //hum_temp_sensor_read(&temp, &hum);
            
            avg_v = sum_v/32;
            avg = sum/32;

            mean = (volt[15]+volt[16])/2;
            mean_code = (code[15]+code[16])/2;

            //ESP_LOGI(TAG, "Humidity at %d", hum);
            //ESP_LOGI(TAG, "Temperature at %d", temp);
            ESP_LOGI(TAG, "Max Voltage Value = %d", max);
            ESP_LOGI(TAG, "Min Voltage Value = %d", min);
            ESP_LOGI(TAG, "Mean Voltage Value = %d", mean);
            ESP_LOGI(TAG, "Average Voltage Value = %d", avg_v);
            ESP_LOGI(TAG, "Mean Code Value = %d", mean_code);
            ESP_LOGI(TAG, "Average pH Value = %f", avg);

            if(max-min > MAX__VOLT_VAR) ESP_LOGI(TAG, "pH sensor not calibrated");
            else ESP_LOGI(TAG, "pH sensor calibrated");
            
            printf("------------------------------------------------\n\n");

            i = 0;
        }

        //ESP_LOGI(TAG, "Infiltration at %d%%", inf);
        //ESP_LOGI(TAG, "pH level at %f", ph);
        //ESP_LOGI(TAG, "Humidity at %d", hum);
        //ESP_LOGI(TAG, "Temperature at %d", temp);
        //ESP_LOGI(TAG, "Water level is %s", water_level?"true":"false");

        vTaskDelay(pdMS_TO_TICKS(1000));

    }

    

    

    



}