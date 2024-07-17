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
}

/*
This function creates a data set with a specified number of data points.
It checks for invalid input size and returns NULL if the size is less than or equal to zero.
It allocates memory for the dataset and the data points. It initializes the data points to NULL
and sets the default data type to INT. Finally, it sets the data points for the dataset and returns the dataset.
*/
DataSet *createDataSet(int size)
{
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
}

/*
The function frees memory allocated for a dataset structure and all its data points.
It checks whether the dataset and its data are not NULL, and if so, it frees each
data point based on its type (integer, float, or string) and then frees the dataset struct itself.
If the dataset has no data, it just frees the dataset struct.
*/

void freeDataSet(DataSet *dataset)
{
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
}
