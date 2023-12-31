/**
 * @file DataVector.h
 * @author MP-Team DECSAI
 * @note To be implemented by students 
 * 
 */
#include <string>

#ifndef DATAVECTOR
#define DATAVECTOR

#define MAX_WIDTH 500
#define FIELD_WIDTH 10
#define ITEMS_PER_ROW 15

/*
 *  int n
 *  int value[]; o double value[];
 *  string label[];
 * 
 * value[0]     value[1] ...    value[n]
 * ----------------------------------------
 * label[0]     label[1] ...    label[n]
 * 
 */

/**
 * 
 */
class DataVector {
    std::string _title, _labels[MAX_WIDTH];
    double _data[MAX_WIDTH];
    int _nData;

public:

    /**
     * @brief Main constructor
     */
    DataVector();
    /**
     * @brief Second constructor
     * @param ndata Number of data categories of the report
     */
    DataVector(int ndata);

    /**
     * @brief Clear all data previously loaded
     * @return 
     */
    DataVector & clear();
    /**
     * @brief Prepare to load @p n data values
     * @param n Number of data to load
     * @return 
     */
    DataVector alloc(int n);
    /**
     * @brief Gives the number of available data
     */
    int size() const;
    // Setters
    /**
     * @brief Defines the title of the report
     * @param title The title
     * @return 
     */
    DataVector & setTitle(const std::string &title);
    /**
     * @brief Sets a value of the report
     * @param pos Position of the value to change
     * @param value New value
     * @return 
     */
    DataVector &setValue(int pos, double value);
    /**
     * @brief Sets a label of the report
     * @param pos   Position of the label to change
     * @param label The new label
     * @return 
     */
    DataVector &setLabel(int pos, const std::string & label);
    // Load from external sources
    /**
     * @brief Loads an external set of data values
     * @param values The array of values to load. It loads 
     * the number of values previously indicated wih alloc @see alloc
     * @return 
     */
    DataVector & loadValues(const int values[]);
    /**
     * @brief Loads an external set of data values
     * @param values The array of values to load. It loads 
     * the number of values previously indicated wih alloc @see alloc
     * @return 
     */
    DataVector & loadValues(const double values[]);
    /**
     * @brief Loads an external set of labels
     * @param values The array of labels to load. It loads 
     * the number of labels previously indicated wih alloc @see alloc
     * @return 
     */
    DataVector & loadLabels(const std::string labels[]);
    /**
     * @brief Loads an external set of labels
     * @param values The array of labels to load. It loads 
     * the number of labels previously indicated wih alloc @see alloc
     * @return 
     */
    DataVector &loadLabels(const char* const labels[]);
    // adder
    DataVector & add(const std::string & label, double data);
    // Getters
    /**
     * @brief Returns the value stored at a given position
     * @param pos The position of the value
     * @return The value
     */
    double getValue(int pos) const;
    /**
     * @brief Returns the label stored at a given position
     * @param pos The position of the label
     * @return The label
     */
    std::string getLabel(int pos) const;

    // Reports
    /**
     * @brief It shows a simple table with the labels and the data, 
     * and it also displays the sum of the stored data. The table appears horizontally.
     * @param decpos Number of decimal digits to show, 0 for integer values
     * @return a string that can be directed to any stream like cout
     */
    std::string showPlainReportH(int decpos = 0) const;
    /**
     * @brief It shows a simple table with the labels and the data, 
     * and it also displays the sum of the stored data. The table appears vertically.
     * @param decpos Number of decimal digits to show, 0 for integer values
     * @return a string that can be directed to any stream like cout
     */
    std::string showPlainReportV(int decpos = 0) const;
    /**
     * @brief It shows a decorated table with the labels and the data, 
     * and it also displays the sum of the stored data. The table appears horizontally.
     * @param decpos Number of decimal digits to show, 0 for integer values
     * @return a string that can be directed to any stream like cout
     */
    std::string showFancyReportH(int decpos = 0) const;

    /**
     * @bried It serializes the data into a plain string
     * @return The serializatiion of the data contained
     */
    std::string to_string() const {
        std::string res = std::to_string(size()) + " ";
        for (int i = 0; i < size(); i++)
            res = res+ std::to_string(_data[i]) + " ";
        return res;
    }

    /**
     * @brief Shows the number of events in the EventSet and a numeric 
     * value that encodes the whole set of events
     * @return A string made up of the size of the EventSet and the
     * numeric code of its content
     * @warning please do not modify its implementation
     */
    std::string reportData() const {
        std::string result = "";
        result = std::to_string(std::hash<std::string>{}(showPlainReportH(2)));
        result = std::to_string(size()) + " " + result;
        return result;
    }

};



#endif /* DATAVECTOR */

