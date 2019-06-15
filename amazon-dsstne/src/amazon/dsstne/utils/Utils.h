/*


   Copyright 2016  Amazon.com, Inc. or its affiliates. All Rights Reserved.

   Licensed under the Apache License, Version 2.0 (the "License"). You may not use this file except in compliance with the License. A copy of the License is located at

   http://aws.amazon.com/apache2.0/

   or in the "license" file accompanying this file. This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
 */
#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <ratio>
#include <string>
#include <utility>

using std::string;
using std::vector;

const string INPUT_DATASET_SUFFIX = "_input";
const string OUTPUT_DATASET_SUFFIX = "_output";
const string NETCDF_FILE_EXTENTION = ".nc";
const unsigned long FIXED_SEED = 12134ull;

class CWMetric
{
public:
    static void updateMetrics(string metric, string value);

    // This function accepts a value of any type that can be used with std::to_string.
    template <typename Value, typename = decltype(std::to_string(std::declval<Value>()))>
    static void updateMetrics(string metric, Value value) {
      updateMetrics(std::move(metric), std::to_string(value));
    }
};

char* getCmdOption(char ** , char **, const std::string & );

bool cmdOptionExists(char** , char**, const std::string& );

/**
 * Helper function to return the value of a given argument. If it isn't supplied, errors out.
 * @param argc has count of arguments
 * @param argv the command line arguments.
 * @param flag for the argument of interest.
 * @param message message in event the argument is not defined.
 * @param usage callback error function to call and exit with error code 1.
 */
string getRequiredArgValue(int argc, char** argv, string flag, string message, void (*usage)());

/**
 * Helper function to return the value of a given argument. If it isn't supplied, return the defaultValue.
 * @param argc has count of arguments
 * @param argv the command line arguments.
 * @param flag for the argument of interest.
 * @param defaultValue to return in the event it is not overridden in the arguments.
 */
string getOptionalArgValue(int argc, char** argv, string flag, string defaultValue);

/**
 * Returns true if the argument flag is defined/set.
 * @param argc has count of arguments
 * @param argv the command line arguments.
 * @param flag for the argument of interest.
 */
bool isArgSet(int argc, char** argv, string flag);

bool fileExists(const std::string &);

/**
 * Return true if the file is a NetCDF file. 
 */
bool isNetCDFfile(const string &filename);

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

std::vector<std::string> split(const std::string &s, char delim);

/**
 * Return the number of seconds elapsed between two time points.
 *
 * The two time points must be issued from the same clock -- otherwise this
 * does not make sense.
 */
template <typename Clock, typename Duration1, typename Duration2>
double elapsed_seconds(std::chrono::time_point<Clock, Duration1> start,
                       std::chrono::time_point<Clock, Duration2> end)
{
  using FloatingPointSeconds = std::chrono::duration<double, std::ratio<1>>;
  return std::chrono::duration_cast<FloatingPointSeconds>(end - start).count();
}

/**
 * Returns true iff dirname is a directory
 */
bool isDirectory(const string &dirname);

/**
 * Returns true iff filename is a file
 */
bool isFile(const string &filename);

/**
 * Adds all files (not directories) under the specified dirname into files
 * Returns 0 if success and non-zero otherwise.
 * If the recursive flag is not set, only lists the first level files. Otherwise, it recurses into
 * all sub-directories.
 */
int listFiles(const string &dirname, const bool recursive, vector<string> &files);

// sort top K by keys and return top keys with top values
template<typename Tkey, typename Tval>
void topKsort(Tkey* keys, Tval* vals, const int size, Tkey* topKkeys, Tval* topKvals, const int topK, const bool sortByKey = true);


// min max - inclusive
inline int rand(int min, int max) {
  return rand() % (max - min + 1) + min;
}

inline float rand(float min, float max) {
  float r = (float)rand() / (float)RAND_MAX;
  return min + r * (max - min);
}
