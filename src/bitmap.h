#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Define enums for data types
typedef enum
{
    INT,
    FLOAT,
    STRING,
} DataType;

// Define a struct for a data point
typedef struct
{
    DataType type;
    void *value;
} DataPoint;

// Define a struct for a dataset
typedef struct
{
    int size;
    DataPoint *data;
} DataSet;

// Function to create a data point
DataPoint *createDataPoint(DataType type, void *value);

// Function to create a dataset
DataSet *createDataSet(int size);

// Function to add a data point to a dataset
void addDataPoint(DataSet *dataset, int index, DataPoint *point);

// Function to get a data point from a dataset
DataPoint *getDataPoint(DataSet *dataset, int index);

// Function to free a dataset
void freeDataSet(DataSet *dataset);

// Function to filter a dataset by a specified data type
DataSet *filterByType(DataSet *dataset, DataType type);
