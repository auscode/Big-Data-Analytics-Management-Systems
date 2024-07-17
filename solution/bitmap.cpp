#include "bitmap.h"

/*
This function creates a new data point with a given data type and value.
It first checks if the data type is valid (INT, FLOAT, or STRING).
Then, it allocates memory for a new data point and for the value,
and copies the value to the data point. Finally, it sets the fields of
the new data point and returns a pointer to the new data point.
If there is an error in any of the steps, it returns NULL.
*/
DataPoint *createDataPoint(DataType type, void *value)
{
    // Check if data type is valid
    if (type != INT && type != FLOAT && type != STRING)
    {
        return NULL;
    }
    // Allocate memory for the new data point
    DataPoint *point = (DataPoint *)malloc(sizeof(DataPoint));
    if (point == NULL)
    {
        return NULL;
    }
    // Allocate memory for the value and copy it to the data point
    void *copy = NULL;
    switch (type)
    {
    case INT:
        copy = (int *)malloc(sizeof(int));
        if (copy == NULL)
        {
            free(point);
            return NULL;
        }
        memcpy(copy, value, sizeof(int));
        break;
    case FLOAT:
        copy = (float *)malloc(sizeof(float));
        if (copy == NULL)
        {
            free(point);
            return NULL;
        }
        memcpy(copy, value, sizeof(float));
        break;
    case STRING:
        int length = strlen((char *)value);
        copy = (char *)malloc(length + 1);
        if (copy == NULL)
        {
            free(point);
            return NULL;
        }
        memcpy(copy, value, length + 1);
        break;
    }
    // Set the fields of the new data point
    point->type = type;
    point->value = copy;
    return point;
}

/*
This function creates a data set with a specified number of data points.
It checks for invalid input size and returns NULL if the size is less than or equal to zero.
It allocates memory for the dataset and the data points. It initializes the data points to NULL
and sets the default data type to INT. Finally, it sets the data points for the dataset and returns the dataset.
*/
DataSet *createDataSet(int size)
{
    if (size <= 0)
    { // check for invalid input size
        return NULL;
    }
    DataSet *dataset = (DataSet *)malloc(sizeof(DataSet)); // allocate memory for dataset struct
    if (dataset == NULL)
    { // check for memory allocation failure
        return NULL;
    }

    dataset->size = size; // set size of dataset

    DataPoint *data = (DataPoint *)malloc(size * sizeof(DataPoint)); // allocate memory for data points
    if (data == NULL)
    { // check for memory allocation failure
        free(dataset);
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {                       // initialize data points to NULL
        data[i].type = INT; // default data type to INT
        data[i].value = NULL;
    }

    dataset->data = data; // set data points for dataset
    return dataset;
}

/*
This function adds a data point to a dataset at a specific index.
It checks if the dataset and data point are not NULL, if the index
is within the bounds of the dataset, and if the data point type
matches the dataset type. It then frees the existing data point
at the specified index, if any, sets the data point at the specified index,
and allocates memory for the data point value and copies it from the input point.
The memory allocation is based on the data type of the data point - integer, float or string.
*/
// Function to add a data point to a dataset
void addDataPoint(DataSet *dataset, int index, DataPoint *point)
{
    // Check if the dataset and point are not NULL
    if (dataset == NULL || point == NULL)
    {
        return;
    }
    // Check if the index is within the bounds of the dataset
    if (index < 0 || index >= dataset->size)
    {
        return;
    }
    // Check if the data point type matches the dataset type
    if (dataset->data[index].type != point->type)
    {
        return;
    }
    // Free the existing data point at the specified index, if any
    if (dataset->data[index].value != NULL)
    {
        free(dataset->data[index].value);
    }
    // Set the data point at the specified index
    dataset->data[index].type = point->type;
    // Allocate memory for the data point value and copy it from the input point
    switch (point->type)
    {
    case INT:
        dataset->data[index].value = malloc(sizeof(int));
        if (dataset->data[index].value != NULL)
        {
            memcpy(dataset->data[index].value, point->value, sizeof(int));
        }
        break;

    case FLOAT:
        dataset->data[index].value = malloc(sizeof(float));
        if (dataset->data[index].value != NULL)
        {
            memcpy(dataset->data[index].value, point->value, sizeof(float));
        }
        break;

    case STRING:
        // Check if the input string is NULL or empty
        if (point->value == NULL || *(char *)point->value == '\0')
        {
            return;
        }

        size_t str_len = strlen((char *)point->value) + 1;
        dataset->data[index].value = malloc(str_len);
        if (dataset->data[index].value != NULL)
        {
            memcpy(dataset->data[index].value, point->value, str_len);
        }
        break;
    }
}

/*
This function retrieves a data point from a dataset by its index.
It checks for errors such as invalid dataset or index, and returns
NULL if any errors are encountered. If the data point exists and is
of type INT, FLOAT, or STRING, it is returned, otherwise NULL is returned.
*/
// Function to get a data point from a dataset
DataPoint *getDataPoint(DataSet *dataset, int index)
{
    if (dataset == NULL)
    {
        return NULL;
    }

    if (index < 0 || index >= dataset->size)
    {
        return NULL;
    }

    DataPoint *point = &dataset->data[index];

    if (point == NULL || point->value == NULL)
    {
        return NULL;
    }

    switch (point->type)
    {
    case INT:
    case FLOAT:
    case STRING:
        return point;
    default:
        return NULL;
    }
}

/*
The function frees memory allocated for a dataset structure and all its data points.
It checks whether the dataset and its data are not NULL, and if so, it frees each
data point based on its type (integer, float, or string) and then frees the dataset struct itself.
If the dataset has no data, it just frees the dataset struct.
*/

void freeDataSet(DataSet *dataset)
{
    if (dataset == NULL)
    {
        return;
    }
    if (dataset->data == NULL)
    {
        // Dataset has no data, free the dataset struct itself
        free(dataset);
        return;
    }

    // Free each data point in the dataset
    for (int i = 0; i < dataset->size; i++)
    {
        DataPoint *point = getDataPoint(dataset, i);
        if (point != NULL)
        {
            // Free the value pointed to by the data point
            switch (point->type)
            {
            case INT:
                free((int *)point->value);
                break;
            case FLOAT:
                free((float *)point->value);
                break;
            case STRING:
                free((char *)point->value);
                break;
            }
            // Free the data point itself
            free(point);
        }
    }

    // Free the dataset struct
    free(dataset);
}

/*
This function takes a dataset and a data type as input and returns a new dataset that
contains only the data points from the original dataset that have the specified data type.
It creates a new dataset to hold the filtered data, loops through all data points in the
input dataset, and checks if each point is of the specified type. If it is, it creates a
new data point with the same type and value and adds it to the filtered dataset.
If the input dataset is NULL or the filtered dataset cannot be created, it returns NULL.
*/
DataSet *filterByType(DataSet *dataset, DataType type)
{
    // Check if dataset is NULL
    if (dataset == NULL)
    {
        return NULL;
    }
    // Create a new dataset to hold filtered data
    DataSet *filteredData = createDataSet(dataset->size);
    // Check if filteredData is NULL
    if (filteredData == NULL)
    {
        return NULL;
    }
    // Loop through all data points in the dataset
    for (int i = 0; i < dataset->size; i++)
    {
        DataPoint *point = getDataPoint(dataset, i);
        // Check if the point pointer is NULL before accessing its members
        if (point == NULL)
        {
            continue;
        }
        // Check if the data point is of the specified type
        if (point->type == type)
        {
            // Create a new data point with the same type and value
            DataPoint *newPoint = createDataPoint(type, point->value);
            // Check if the newPoint pointer is NULL before adding it to the filtered dataset
            if (newPoint == NULL)
            {
                continue;
            }
            // Check if the filteredData pointer is NULL before adding a new data point to it
            if (filteredData == NULL)
            {
                free(newPoint);
                continue;
            }
            // Add the new data point to the filtered dataset
            addDataPoint(filteredData, filteredData->size, newPoint);
        }
    }
    return filteredData;
}
