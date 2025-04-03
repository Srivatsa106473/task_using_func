#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "unity.h"
#include "esp_err.h"
#include "esp_log.h"
#include <string.h>

// Define error variable for task creation
esp_err_t err;

// Define a structure to hold two string parameters for tasks
typedef struct
{
    const char *para1;
    const char *para2;
} Taskparameter;

// Instantiate a Taskparameter structure
Taskparameter parameter;

// Task function to handle different string operations
void Task1(void *pvParameters)
{
    // Cast the passed parameter to the Taskparameter structure
    Taskparameter *params = (Taskparameter *)pvParameters;

    // Case 1: Check if para1 is not NULL and matches "Dammavalam"
    if (params->para1 != NULL && strcmp(params->para1, "Dammavalam") == 0)
    {
        ESP_LOGI("Task1 function", "string 1: %s", params->para1);
        vTaskDelete(NULL); // Delete the task after execution
    }
    // Case 2: Check if para2 is not NULL and matches "Sarath Chandra"
    else if (params->para2 != NULL && strcmp(params->para2, "Sarath Chandra") == 0)
    {
        ESP_LOGI("Task1 function", "string 2: %s", params->para2);
        vTaskDelete(NULL); // Delete the task after execution
    }
    // Case 3: Concatenate both para1 and para2 if they are not NULL
    else if (params->para1 != NULL && params->para2 != NULL)
    {
        // Allocate enough memory to hold both strings and the space for the concatenation
        char concatenatedString[1024]; // Adjust size according to the maximum expected string length

        // Concatenate para1 and para2
        snprintf(concatenatedString, sizeof(concatenatedString), "%s %s", params->para1, params->para2);

        // Print the concatenated string
        ESP_LOGI("Task1 function", "Concatenated string 1 & 2: %s", concatenatedString);
        vTaskDelete(NULL); // Delete the task after execution
    }
    else
    {
        // If no valid parameters are found
        ESP_LOGI("Task1 function", "No valid parameters found!");
        vTaskDelete(NULL); // Delete the task if no valid parameters
    }
}

// Test Case 1: Running Task1 with the first string parameter (para1)
TEST_CASE("task_creation_1", "passing Task1 func argument para1, to execute first task using esp core 0")
{
    // Set para1 to "Dammavalam" and para2 to NULL
    parameter.para1 = "Dammavalam";
    parameter.para2 = NULL;

    // Create a task pinned to core 0
    err = xTaskCreatePinnedToCore(Task1, "Task1 on core 0", 8192, (void *)&parameter, 1, NULL, 0);

    // Check if the task creation was successful
    if (err != ESP_OK)
    {
        ESP_LOGE("TEST_CASE : task_creation_1", "Error creating task: %d", err);
    }
    else
    {
        ESP_LOGI("TEST_CASE : task_creation_1", "Expected string: \"Dammavalam\"");
        vTaskDelay(500);  // Allow some time for the task to run
    }
}

// Test Case 2: Running Task1 with the second string parameter (para2)
TEST_CASE("task_creation_2", "passing Task1 func argument para2, to execute second task using esp core 1")
{
    // Set para1 to NULL and para2 to "Sarath Chandra"
    parameter.para1 = NULL;
    parameter.para2 = "Sarath Chandra";

    // Create a task pinned to core 1
    err = xTaskCreatePinnedToCore(Task1, "Task1 on core 1", 8192, (void *)&parameter, 1, NULL, 1);

    // Check if the task creation was successful
    if (err != ESP_OK)
    {
        ESP_LOGE("TEST_CASE : task_creation_2", "Error creating task: %d", err);
    }
    else
    {
        ESP_LOGI("TEST_CASE : task_creation_2", "Expected string: \"Sarath Chandra\"");
        vTaskDelay(500);  // Allow some time for the task to run
    }
}

// Test Case 3: Running Task1 with both parameters (para1 and para2) to concatenate strings
TEST_CASE("task_creation_3", "creating test case 3 where concatenating both test case strings into one")
{
    // Set para1 to "Dammavalam" and para2 to "Sarath Chandra"
    parameter.para1 = "Dammavalam";
    parameter.para2 = "Sarath Chandra";

    // Create a task pinned to core 0
    err = xTaskCreatePinnedToCore(Task1, "Task1 on core 0", 8192, (void *)&parameter, 1, NULL, 0);

    // Check if the task creation was successful
    if (err != ESP_OK)
    {
        ESP_LOGE("TEST_CASE : task_creation_3", "Error creating task: %d", err);
    }
    else
    {
        ESP_LOGI("TEST_CASE : task_creation_3", "Expected string: \"Dammavalam Sarath Chandra\"");
        vTaskDelay(500);  // Allow some time for the task to run
    }
}

// Main application function to initialize logging and run tests
void app_main(void)
{
    // Set the log level to debug for detailed logs
    esp_log_level_set("*", ESP_LOG_DEBUG);

    // Log a message indicating the start of the main function
    ESP_LOGI("app_main", "starting app_main function");

    // Run the test menu to allow the user to select and run tests
    unity_run_menu();
}
