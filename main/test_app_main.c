/*
 * SPDX-FileCopyrightText: 2015-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "unity.h"
#include "esp_err.h"
#include "esp_log.h"

static const char * para1 = "Dammavalam";
static const char * para2 = "Sarath Chandra";

esp_err_t err;
esp_err_t err1;
esp_err_t err2;

void Task1(void *pvParameters)
{
    char *parameter = (char *)pvParameters;
    while(1)
    {
        ESP_LOGI("Task1 function", "%s", parameter);
    }
    vTaskDelay(500);
}

TEST_CASE("task_creation_1","passing Task1 func argument para1, to execute first task using esp core 0")
{
    err1 = xTaskCreatePinnedToCore(Task1, "creating a task using parameters", 4098, (void *)para1, 1, NULL, 0);
    if(err1 != ESP_OK)
    {
        ESP_LOGE("TEST_CASE : task_creation", " error found!");
    }
    else
    {
        ESP_LOGI("TEST_CASE : task_creation", " String : ""Dammavalam"" has to print");
        vTaskDelay(500);
    }
}

TEST_CASE("task_creation_2","passing Task1 func argument para2, to execute second task using esp core 1")
{
    err2 = xTaskCreatePinnedToCore(Task1, "creating a task using parameters", 4098, (void *)para2, 1, NULL, 1);
    if(err2 != ESP_OK)
    {
        ESP_LOGE("TEST_CASE : task_creation", " error found!");
    }
    else
    {
        ESP_LOGI("TEST_CASE : task_creation", " String : ""Sarath Chandra"" has to print");
    }
}

void app_main(void)
{
    esp_log_level_set("*", ESP_LOG_DEBUG);
    ESP_LOGI("app_main","starting app_main function");
    unity_run_menu();
}