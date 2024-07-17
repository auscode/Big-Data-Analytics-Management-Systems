#include <cxxtest/TestSuite.h>
#include "../src/bitmap.h"

class SampleTestSuite : public CxxTest::TestSuite
{
public:
    void testCreateDataPointInt1()
    {
        int value = 67;
        DataPoint *point = createDataPoint(DataType::INT, &value);

        TS_ASSERT(point != NULL);
        TS_ASSERT_EQUALS(point->type, DataType::INT);
        TS_ASSERT_EQUALS(*((int *)point->value), value);

        free(point->value);
        free(point);
    }

    void testCreateDataPointFloat1()
    {
        float value = 1.62f;
        DataPoint *point = createDataPoint(DataType::FLOAT, &value);

        TS_ASSERT(point != NULL);
        TS_ASSERT_EQUALS(point->type, DataType::FLOAT);
        TS_ASSERT_EQUALS(*((float *)point->value), value);

        free(point->value);
        free(point);
    }

    void testCreateDataPointString()
    {
        const char *value = "world";                                         // declare value as a const char pointer
        DataPoint *point = createDataPoint(DataType::STRING, (void *)value); // cast value to a void pointer

        TS_ASSERT(point != NULL);
        TS_ASSERT_EQUALS(point->type, DataType::STRING);
        TS_ASSERT_EQUALS(strcmp((char *)point->value, value), 0);

        free(point->value);
        free(point);
    }
    ///////////////////////////////////////////////////////////////////
    void testCreateDataSetWithPositiveSize()
    {
        // Create a data set of size 5
        DataSet *dataset = createDataSet(9);

        // Check that the data set is not null and its size is 5
        TS_ASSERT(dataset != NULL);
        TS_ASSERT_EQUALS(dataset->size, 9);

        // Check that each data point in the data set is of type INT and has a null value
        for (int i = 0; i < dataset->size; i++)
        {
            TS_ASSERT_EQUALS(dataset->data[i].type, INT);
            TS_ASSERT(dataset->data[i].value == NULL);
        }

        // Free the memory used by the data set
        freeDataSet(dataset);
    }

    // Test case for creating a data set with a zero size
    void testCreateDataSetWithZeroSize()
    {
        // Create a data set of size 0
        DataSet *dataset = createDataSet(0);

        // Check that the data set is null
        TS_ASSERT(dataset == NULL);
    }

    // Test case for creating a data set with a negative size
    void testCreateDataSetWithNegativeSize()
    {
        // Create a data set of size -5
        DataSet *dataset = createDataSet(-8);

        // Check that the data set is null
        TS_ASSERT(dataset == NULL);
    }
    //////////////////////////////////////////////////////////////////////
    void testAddIntegerDataPoint()
    {
        DataSet *dataset = createDataSet(3);
        int value = 20;
        DataPoint *point = createDataPoint(INT, &value);
        addDataPoint(dataset, 0, point);
        DataPoint *result = getDataPoint(dataset, 0);
        TS_ASSERT_EQUALS(result->type, INT);
        TS_ASSERT_EQUALS(*((int *)result->value), value);
        freeDataSet(dataset);
        free(point->value);
        free(point);
    }

    void testAddDataPointWithInvalidIndex()
    {
        // Create a dataset and add a data point with an invalid index
        DataSet *dataset = createDataSet(2);
        int value = 50;
        DataPoint *point = createDataPoint(INT, &value);
        addDataPoint(dataset, 2, point);

        // Check that the data point was not added
        DataPoint *result = getDataPoint(dataset, 2);
        TS_ASSERT(result == NULL);

        // Free the dataset and data point
        freeDataSet(dataset);
        free(point->value);
        free(point);
    }

    void testAddDataPointWithExistingValue()
    {
        // Create a dataset and add a data point with an existing value
        DataSet *dataset = createDataSet(1);
        int value = 50;
        int valueI = 75;
        DataPoint *point1 = createDataPoint(INT, &value);
        DataPoint *point2 = createDataPoint(INT, &valueI);
        addDataPoint(dataset, 0, point1);
        addDataPoint(dataset, 0, point2);

        // Check that the data point was added and the existing value was freed
        DataPoint *result = getDataPoint(dataset, 0);
        TS_ASSERT_EQUALS(result->type, INT);
        TS_ASSERT_EQUALS(*((int *)result->value), 75);

        // Free the dataset and data points
        freeDataSet(dataset);
        free(point1->value);
        free(point1);
        free(point2->value);
        free(point2);
    }
    ////////////////////////////////////////////////////////////////
    void testGetDataPointWithNullDataPoint()
    {
        // Create a dataset with a null data point
        DataSet *dataset = createDataSet(1);
        addDataPoint(dataset, 0, NULL);

        // Get a data point from the dataset
        DataPoint *result = getDataPoint(dataset, 0);

        // Check that the data point was not retrieved
        TS_ASSERT(result == NULL);

        // Free the dataset
        freeDataSet(dataset);
    }
    void testGetDataPointWithInvalidIndex()
    {
        // Create a dataset with 3 data points
        DataSet *dataset = createDataSet(3);

        // Try to get data points with invalid indices
        int index = 100;
        DataPoint *result = getDataPoint(dataset, index);

        // Check that the data point was not retrieved
        TS_ASSERT(result == NULL);

        index = 3;
        result = getDataPoint(dataset, index);

        // Check that the data point was not retrieved
        TS_ASSERT(result == NULL);

        // Free the dataset
        freeDataSet(dataset);
    }
    void testGetDataPointWithInvalidIndex2()
    {
        DataSet *dataset = createDataSet(4);
        int index = 50;
        DataPoint *result = getDataPoint(dataset, index);
        TS_ASSERT(result == NULL);

        index = 4;
        result = getDataPoint(dataset, index);
        TS_ASSERT(result == NULL);

        freeDataSet(dataset);
    }
    /////////////////////////////////////////////////////////////
    void testFreeDataSetWithNoDataPoints()
    {
        DataSet *dataset = createDataSet(0);
        freeDataSet(dataset);
        TS_ASSERT(dataset == NULL);
    }

    void testFreeDataSetWithOneDataPoint()
    {
        DataSet *dataset = createDataSet(1);
        int value = 20;
        DataPoint *point = createDataPoint(INT, &value);
        addDataPoint(dataset, 0, point);
        freeDataSet(dataset);
        TS_ASSERT(dataset != NULL);
    }

    void testFreeDataSetWithDifferentDataTypes()
    {
        DataSet *dataset = createDataSet(3);
        int value1 = 10;
        DataPoint *point1 = createDataPoint(INT, &value1);
        float value2 = 6.5f;
        DataPoint *point2 = createDataPoint(FLOAT, &value2);
        const char *value3 = "world";
        DataPoint *point3 = createDataPoint(STRING, (void *)value3);
        addDataPoint(dataset, 0, point1);
        addDataPoint(dataset, 1, point2);
        addDataPoint(dataset, 2, point3);
        freeDataSet(dataset);
        TS_ASSERT(dataset != NULL);
    }
    ////////////////////////////////////////////////////////////////
    void testFilterByTypeWithNullDataset()
    {
        // Test case 1: Filter by INT on NULL dataset
        DataSet *dataset = NULL;
        DataSet *filteredData = filterByType(dataset, DataType::INT);
        TS_ASSERT(filteredData == NULL);
    }

    void testFilterByTypeWithEmptyDataset()
    {
        // Test case 2: Filter by FLOAT on an empty dataset
        DataSet *dataset = createDataSet(0);
        DataSet *filteredData = filterByType(dataset, DataType::FLOAT);
        TS_ASSERT(filteredData == NULL);
        freeDataSet(dataset);
        freeDataSet(filteredData);
    }

    void testDatasetWithNoMatchingType()
    {
        // Test case 3: Filter by STRING on a dataset with no matching type
        DataSet *dataset = createDataSet(3);
        int value1 = 10;
        int value2 = 40;
        float value3 = 60.0;
        addDataPoint(dataset, 0, createDataPoint(INT, &value1));
        addDataPoint(dataset, 1, createDataPoint(INT, &value2));
        addDataPoint(dataset, 2, createDataPoint(FLOAT, &value3));
        DataType type = STRING;
        DataSet *filteredData = filterByType(dataset, type);
        TS_ASSERT(filteredData != NULL);
        TS_ASSERT_EQUALS(filteredData->size, 3); // Expect empty dataset
        freeDataSet(filteredData);
    }
};