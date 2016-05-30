#ifndef RISCV_LUT_COMPILER_WEIGHTS_H
#define  RISCV_LUT_COMPILER_WEIGHTS_H

#include "error.h"
#include "segment.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
/** Represents a single weights table as specified in weights data files.
  
  */
class WeightsTable {
  public:
    /** Represents a single entry in the weights file.
      */
    struct range_t {
      /** Start of the range */
      seg_data_t start;
      /** End of the range. 
        *
        * If this is less than or equal to the start, this range represents
        * a point.
        */
      seg_data_t end;
      /** Lua function to call with a point from this range to attain the value
        * at that point.
        */
      int    lref;


    };
  protected:
    /** The lua state used for interpreting our segment data points */
    lua_State *_l;
    
    /** Sorted list of our ranges.
      *
      * To uphold the overriding nature of succeeding ranges in weight files,
      * overlaps are resolved and intervals are split accordingly whenever
      * a new range is added.
      */
    alp::array_t<range_t> _ranges;
  public:
    /** Constructor. 
      *
      * Creates an empty weights table, evaluating to 0 everywhere.
      */
    WeightsTable();

    ~WeightsTable();
    
    /** Removes all ranges, leaving the weights table as it was right after
      * construction.*/
    void clear();
    
    /** Parses a weights file and *adds* the defined ranges to our own.
      *
      * \param ptr Pointer to the beginning of the buffer to parse.
      * \param cb Length of the buffer to parse, in bytes.
      */
    void parseWeights(const char *ptr, size_t cb);
    /** Uses parseWeights to parse a weights file.
      *
      * \param fn File name to load and parse from. 
      * \throw FileIOException The file could not be read.
      */
    void parseWeightsFile(const char *fn);
    
    /** Returns the weight value at a specific point.
      * 
      * \param p Point to compute the weight at.
      */
    seg_data_t evaluate(const seg_data_t &p);
    /** Call-by-reference version of evaluate
      * 
      * \param p Point to compute the weight at.
      * \param r Result variable.
      */
    void evaluate(const seg_data_t &p, seg_data_t &v);

};

#endif
