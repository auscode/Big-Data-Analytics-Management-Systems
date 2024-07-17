#include <cxxtest/TestSuite.h>
#include "../src/bitmap.h"

class SampleTestSuite : public CxxTest::TestSuite
{
public:
    void testCreateDataPointInt()
    {
        int value = 42;
        DataPoint *point = createDataPoint(INT, &value);

        TS_ASSERT(point != NULL);
        TS_ASSERT_EQUALS(point->type, DataType::INT);
        TS_ASSERT_EQUALS(*((int *)point->value), value);

        free(point->value);
        free(point);
    }

    void testCreateDataPointFloat()
    {
        float value = 3.14f;
        DataPoint *point = createDataPoint(DataType::FLOAT, &value);

        TS_ASSERT(point != NULL);
        TS_ASSERT_EQUALS(point->type, DataType::FLOAT);
        TS_ASSERT_EQUALS(*((float *)point->value), value);

        free(point->value);
        free(point);
    }

    void testCreateDataPointString()
    {
        const char *value = "hello";                                         // declare value as a const char pointer
        DataPoint *point = createDataPoint(DataType::STRING, (void *)value); // cast value to a void pointer

        TS_ASSERT(point != NULL);
        TS_ASSERT_EQUALS(point->type, DataType::STRING);
        TS_ASSERT_EQUALS(strcmp((char *)point->value, value), 0);

        free(point->value);
        free(point);
    }
    ////////////////////////////////////////////////////////////////////
    void testCreateDataSetWithPositiveSize()
    {
        DataSet *dataset = createDataSet(5);

        TS_ASSERT(dataset != NULL);
        TS_ASSERT_EQUALS(dataset->size, 5);

        for (int i = 0; i < dataset->size; i++)
        {
            TS_ASSERT_EQUALS(dataset->data[i].type, INT);
            TS_ASSERT(dataset->data[i].value == NULL);
        }

        freeDataSet(dataset);
    }

    void testCreateDataSetWithZeroSize()
    {
        DataSet *dataset = createDataSet(0);
        TS_ASSERT(dataset == NULL);
    }

    void testCreateDataSetWithNegativeSize()
    {
        DataSet *dataset = createDataSet(-5);
        TS_ASSERT(dataset == NULL);
    }
    ////////////////////////////////////////////////////////////////////
    void testAddIntegerDataPoint()
    {
        DataSet *dataset = createDataSet(3);
        int value = 10;
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
        int value = 12;
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
        int value = 6;
        int valueI = 15;
        DataPoint *point1 = createDataPoint(INT, &value);
        DataPoint *point2 = createDataPoint(INT, &valueI);
        addDataPoint(dataset, 0, point1);
        addDataPoint(dataset, 0, point2);

        // Check that the data point was added and the existing value was freed
        DataPoint *result = getDataPoint(dataset, 0);
        TS_ASSERT_EQUALS(result->type, INT);
        TS_ASSERT_EQUALS(*((int *)result->value), 15);

        // Free the dataset and data points
        freeDataSet(dataset);
        free(point1->value);
        free(point1);
        free(point2->value);
        free(point2);
    }
    ///////////////////////////////////////////////////////////

    void testGetDataPointWithNullDataset()
    {
        // Get a data point from a null dataset
        DataPoint *result = getDataPoint(NULL, 0);

        // Check that the data point was not retrieved
        TS_ASSERT(result == NULL);
    }

    void testGetDataPointFromNullDataSet()
    {
        DataSet *dataset = NULL;
        int index = 0;
        DataPoint *result = getDataPoint(dataset, index);
        TS_ASSERT(result == NULL);
    }

    void testGetDataPointWithInvalidIndex()
    {
        DataSet *dataset = createDataSet(3);
        int index = 10;
        DataPoint *result = getDataPoint(dataset, index);
        TS_ASSERT(result == NULL);

        index = 3;
        result = getDataPoint(dataset, index);
        TS_ASSERT(result == NULL);

        freeDataSet(dataset);
    }
    /////////////////////////////////////////////////////////////////
    void testFreeDataSetWithNoDataPoints()
    {
        DataSet *dataset = createDataSet(0);
        freeDataSet(dataset);
        TS_ASSERT(dataset == NULL);
    }
    void testFreeDataSetWithOneDataPoint()
    {
        DataSet *dataset = createDataSet(1);
        int value = 10;
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
        float value2 = 5.5f;
        DataPoint *point2 = createDataPoint(FLOAT, &value2);
        const char *value3 = "hello";
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
        DataSet *dataset = NULL;
        DataSet *filteredData = filterByType(dataset, DataType::INT);
        TS_ASSERT(filteredData == NULL);
    }

    void testFilterByTypeWithEmptyDataset()
    {
        DataSet *dataset = createDataSet(0);
        DataSet *filteredData = filterByType(dataset, DataType::FLOAT);
        TS_ASSERT(filteredData == NULL);
        freeDataSet(dataset);
        freeDataSet(filteredData);
    }

    void testDatasetWithNoMatchingType()
    {
        DataSet *dataset = createDataSet(3);
        int value1 = 10;
        int value2 = 20;
        float value3 = 30.0;
        addDataPoint(dataset, 0, createDataPoint(INT, &value1));
        addDataPoint(dataset, 1, createDataPoint(INT, &value2));
        addDataPoint(dataset, 2, createDataPoint(FLOAT, &value3));
        DataType type = STRING;
        DataSet *filteredData = filterByType(dataset, type);
        TS_ASSERT(filteredData != NULL);
        TS_ASSERT_EQUALS(filteredData->size, 3);
        freeDataSet(filteredData);
    }
    
};